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

		##DEBUG:
		print "\@fields are: " . @fields . $NL . ">$sym<$TAB>$nshares<$NL";
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

sub getQuote {
	my $quoter = Finance::Quote->new;      # Create the F::Q object.
	$quoter->timeout(30);	# Cancel fetch operation if it takes longer than 30 seconds.
	$quoter->failover(0);
	## DEBUG:  	print "Looking for symbols (" . scalar @symbols . "): " .join (", ", @symbols) .$NL

	# Grab our information and place it into %info.
	my %info = $quoter->yahoo_json($exchange, @symbols);

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
	#DEBUG: 
	print "Compariing \"data\" to " . substr($f,$len-4) . $NL;
		if (qw(data) eq substr($f,$len-4)) {
			push (@return_list, $f);
			print $TAB . substr($f,0,$len-5) . $NL;
		}
		#DEBUG:
		else { print ("Ingoring file: $f$NL"); }
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

##DEBUG: 
print "\@output_order is size: " . scalar(@output_order) . ": " . join(", ", @output_order) . $NL;

## get the quote and show the elapsed time. It takes about 3.1 seconds to get 15 quotes
#time: my $t0 = [gettimeofday];
my %info = getQuote();
#time: my ($seconds, $microseconds) = gettimeofday;
#time: my $elapsed = tv_interval ( $t0, [$seconds, $microseconds]);
#time: printf ( "Elapsed time was: %.2f\n", $elapsed );
##DEBUG:
 print "Size of array quotes is: " . scalar %info . "\n";

