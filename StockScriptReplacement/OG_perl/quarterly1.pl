use strict;
use Finance::Quote;
use Time::HiRes qw( gettimeofday tv_interval);			## for testing/timing purposes
use Text::CSV;

## links
##	http://finance-quote.sourceforge.net/tpj/finance-quote-example
##	https://www.foo.be/docs/tpj/issues/vol5_3/tpj0503-0006.html
##
##	https://www.perl.com/article/27/2013/6/16/Perl-hash-basics-create-update-loop-delete-and-sort/


# setting TIMEOUT and PROXY is optional
$Finance::Quote::TIMEOUT = 60;
## $Finance::YahooQuote::PROXY = "http://some.where.net:8080";

my $debug = 1;			## anything but: 0, under, or ()
my $show_header = 1;
my $show_values = 1;
my $TAB = "\t";
my $NL = "\n";
my $BLANK = "#blank";
my @symbols = ();

## list of columns seem to include:
## open, year_range, success, day_range, currency, last, volume, symbol, close,
##				method, currency_set_by_fq, isodate, date, errormsg
my @columns_I_want = ( "Symbol", "last", "close");
my @columns = @columns_I_want;
my $num_columns = scalar @columns;
my $exchange = "yahoo_json";		## default was "usa"
#$exchange = "usa";
##EAS changed in May, 2023
#$exchange = "nasdaq";
#$exchange = "alphavantage";

my $data_path = "..\\data\\";		## needed double-back-slashes twice here!!
my $data_filename_suffix = ".data";
my @output_order = ();			## start with empty array (of strings)

sub Commify {
  my $text = reverse $_[0];
  $text =~ s/(\d\d\d)(?=\d)(?!\d*\.)/$1,/g;
  return scalar reverse $text;
} # Commify

sub get_data_filename {
	my $type = $_[0];		## mf, or stocks, etc
	
	return $data_path . $type . $data_filename_suffix;
}

sub read_datafile {
	my $datafile_withpath = $_[0];
	my $show_file_contents = $_[1];		## do we need to error check this first?
	
	my @data_as_array = ();
	## format: TICKER comma floating_point_number	
	open my $in, '<:encoding(UTF-8)', $datafile_withpath or
			die "Could not open '$datafile_withpath' for reading $!";
	while (my $line = <$in>) {
		chomp $line;
		if (index($line, "##") == 0) { next;}	## skip if line starts with '##'
		push  @data_as_array, $line;
		##my @fields = split "," , $line;
	}
	close $in;
		
	if ($show_file_contents) {
		## do we just print the length and first line?
		print "File: " . $datafile_withpath . " contained " . scalar(@data_as_array) . " rows.\n";
		print "the first line was: " . $data_as_array[0] . "\n";
	}
	return @data_as_array;
}

sub parse_datafile {
	my @data_as_array = @_;
	my %data;
	my $csv = Text::CSV->new({ sep_char => ',' });
	
	##DEBUG: print "Array size is: " . scalar(@data_as_array) . $NL;
	## print "the first line was: " . $data_as_array[0] . "\n";
	foreach my $line (@data_as_array) {
		## chomp $line;
		my ($sym, $nshares);
		my @fields;
		
		if (index($line, "#") == 0) {		# skip if line starts with '#'
			push (@output_order, $line);
			next;
		}
		if (length($line) eq 0) {
			push (@output_order, $BLANK);		## skip blank lines
			next;
		}
		
		if ($csv->parse($line)) {
			@fields = $csv->fields();
			($sym, $nshares) = @fields;		## double assignment
		} else {
			warn "Line could not be parsed: $line\n";
		}

		##DEBUG: print "\@fields are: " . @fields . $NL . ">$sym<$TAB>$nshares<$NL";
		if (( ($sym eq undef) ||  ($nshares eq undef))) {
			print "Could not find pattern on line: " . $line . $NL;
			# printf ("1: %vd\n", $line);
			# $line =~s/(.)/ord($1) /eg;
			# print "2: " . $line . $NL;
			
		} else {
			$data{$sym} = $nshares;
			push (@symbols, $sym);			## append this to array of symbols
			push (@output_order, $sym);
			##DEBUG: print "Saving Nshares for symbol: " . $sym . $NL;
		}
	}
	return %data;
}


sub getSymbols {
	die ("getSymbols() does not exist any more!!");
}

sub getCrumb {
	my $cookie_in_header = $_[0];
	my $ua = $_[1];
	
	my $url2='https://query2.finance.yahoo.com/v1/test/getcrumb';

	my $request2 = 
		new HTTP::Request('GET' => $url2, HTTP::Headers->new('Cookie'=> $cookie_in_header));
	my $response2 = $ua->request($request2);
	my $content2 = $response2->content();
	#print "content2 (our crumb) is: $content2\n\n";
	return $content2;
}

sub getCookie {
	my $ua = $_[0];
	
	my $url1='https://fc.yahoo.com/';

	my $request = new HTTP::Request('GET', $url1);
	#EAS do not need to debug this any more: print "Sending request: $url1\n";
	my $response = $ua->request($request);
	my $content = $response->content();

	# ignore_discard => 1 tells it to keep session cookies?
	my $cookie_jar = HTTP::Cookies->new(ignore_discard => 1);
	my $cookie_hash = $cookie_jar->extract_cookies( $response );

	my $index = '_headers';
	my $header_cookies = $cookie_hash->{$index};

	my $cookie_to_find = 'set-cookie';
	my $cookie_in_header = $header_cookies->{$cookie_to_find};
	#print "Cookie in header is: $cookie_in_header\n";
	return $cookie_in_header;
}

sub getQuote {
	my $quoter = Finance::Quote->new;      # Create the F::Q object.
	$quoter->timeout(30);	# Cancel fetch operation if it takes longer than 30 seconds.
	$quoter->failover(0);
	##EAS: added this line in May, 2023
	$quoter->alphavantage({API_KEY => 'RKO5B82AH10CX1LG'});
	## DEBUG: print "Looking for symbols (" . scalar @symbols . "): " .join (", ", @symbols) .$NL;
	
	## EAS added 2 new params in May, 2023
	my $ua = new LWP::UserAgent;
	$ua->timeout(30);
	## EAS no longer needed, since June 12, 2023 when the moved from v7 to v11
	#my $cookie = getCookie($ua);
	#print "EAS: setting cookie to $cookie\n";
	#$quoter->cookie($cookie);
	#my $crumb = getCrumb($cookie , $ua);
	#print "EAS: setting crumb to $crumb\n";
	#$quoter->crumb($crumb);
	

	# Grab our information and place it into %info.
	##EAS: changed this in May, 2023 from: 
	##my %info = $quoter->yahoo_json($exchange, @symbols);
	my %info = $quoter->fetch($exchange, @symbols);
	##DEBUG: print "INFO:\n" . %info . "\nEND\n";

	## make sure the close does not have too many digits. Truncate the string, iff needed
	## round the float
	foreach my $stock1 (@symbols) {
		my $cl = $info{$stock1, "close"};
		if (length($cl) > 6) {
			$info{$stock1, "close"} = sprintf("%.2f", $cl);
		}
	}
	return %info;
}

sub showList {
	## show list of files
	my $path = $data_path;
	my @return_list = ();		## empty list
	opendir(my $dh, $path) || die "Can't open $path: $!";
	## print header
	print "List of data files is:$NL";
	while (my $f = readdir $dh) {
		##print "$path/$f\n";
		next if (substr($f,0,1) eq '.');		## skip .-things
		my $len = length($f);
	#DEBUG: print "Compariing \"data\" to " . substr($f,$len-4) . $NL;
		if (qw(data) eq substr($f,$len-4)) {
			push (@return_list, $f);
			print $TAB . substr($f,0,$len-5) . $NL;
		}
		#DEBUG: else { print ("Ingoring file: $f$NL"); }
	}
	closedir $dh;
	return @return_list;
}

##
##	START HERE
##
##	iff no args, or 'list', then show the list and exit
##	otherwise, the arg1 is the data file to use
my ($type) = @ARGV;
if (defined $type) {
	#DEBUG: print "Parsing arguments. (type is already set to: $type)$NL";
	foreach my $arg (@ARGV) {
		; #DEBUG: print "Arg: $arg$NL";
	}
} else {
	$type = "list";
}

if ($type eq "list")	{ showList(); exit; }		## exit no matter the return code
	
my $fname = get_data_filename($type);
my @datafile_contents = read_datafile($fname);		## add Arg2 if we want to show the file contents
my %data = parse_datafile(@datafile_contents);

##DEBUG:  print "\@output_order is size: " . scalar(@output_order) . ": " . join(", ", @output_order) . $NL;

## get the quote and show the elapsed time. It takes about 3.1 seconds to get 15 quotes
#time: my $t0 = [gettimeofday];
my %info = getQuote();
#time: my ($seconds, $microseconds) = gettimeofday;
#time: my $elapsed = tv_interval ( $t0, [$seconds, $microseconds]);
#time: printf ( "Elapsed time was: %.2f\n", $elapsed );
##DEBUG: print "Size of array quotes is: " . scalar %info . "\n";


## printer optional header, then the data we gathered
if ($show_header) {
	for (my $i = 0; $i < $num_columns; $i++) {
		print ucfirst $columns_I_want[$i] . $TAB;
	}
	print "Nshares${TAB}Value";
	print $NL;
}
##foreach my $stock (@symbols) {
##
##}

##
## alternate output
foreach my $line (@output_order) {
	if (index($line, "#") eq 0) {
		print $line . $NL;
		next;
	}
	next if ($line eq $BLANK);
	my $stock = $line;
	##DEBUG: 	print "show data for stock: $stock$NL";
	unless ($info{$stock, "success"}) {
		warn "Lookup of $stock failed - ".$info{$stock, "errormsg"}. $NL;
		print "Full info is: \n" . join(", ", $info{$stock}) . "END\n";
		exit;
		next;
	}
	my $shares_and_value = "";
	if (%data{$stock} != undef) {
		my $v = Commify(sprintf("%.2f", $info{$stock, "last"} * %data{$stock}));
		$shares_and_value = %data{$stock} . $TAB . $v . $TAB;
	} else {
		$shares_and_value = "n/a$TAB";
	}
	
	if ($show_header) {
		print "$stock$TAB",
##	      $info{$stock, "volume"}, $TAB,
		$info{$stock, "last"}, $TAB,
		$info{$stock, "close"}, $TAB,
		$shares_and_value , $TAB,
		$NL;

	} else {
		print "$stock$TAB",
##	      "Volume: ", $info{$stock, "volume"}, $NL,
		"Close: " , $info{$stock, "close"}, $NL,
		"Last: " , $info{$stock, "last"}, $NL,
		$shares_and_value ,
		$NL;
	}
}

# iff $show_values, then output just the values again
if ($show_values) {
	foreach my $line (@output_order) {
		if ($line eq $BLANK) {
			print $NL;
			next;
		}
		if (index($line, "#") eq 0) {
			print $line . $NL;
			next;
		}
		my $stock = $line;
	##print "show data for stock: $stock$NL";
		unless ($info{$stock, "success"}) {
			##warn "Lookup of $stock failed - ".$info{$stock, "errormsg"}. $NL;
			next;
		}
		my $value = "";
		if (%data{$stock} != undef) {
			my $v = Commify(sprintf("%.2f", $info{$stock, "last"} * %data{$stock}));
			$value = $v;
		} else {
			$value = "n/a";
		}
		print "$value$NL";
	}
}
