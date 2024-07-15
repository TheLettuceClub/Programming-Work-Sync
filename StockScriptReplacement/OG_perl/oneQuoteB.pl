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
my $TAB = "\t";
my $NL = "\n";
my @symbols = ();

## list of columns seem to include:
## open, year_range, success, day_range, currency, last, volume, symbol, close,
##				method, currency_set_by_fq, isodate, date, errormsg
my @columns_I_want = ( "Symbol", "Company Name", "Last Price");
@columns_I_want = ( "Symbol", "last", "close");
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
	## local $/ = undef;
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
	
	print "Array size is: " . scalar(@data_as_array) . $NL;
	
	## print "the first line was: " . $data_as_array[0] . "\n";
	foreach my $line (@data_as_array) {
		## chomp $line;
		my ($sym, $nshares);
		my @fields;
		
		if (index($line, "#") == 0) {		# skip if line starts with '#'
			push (@output_order, $line);
			next;
		}
		next if (length($line) eq 0);		## skip blank lines
		
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
	my $tab_name = $_[0];		## just one string
	my @symbol_list = ();		## start with an empty list;
	my @mf_vanguard = qw (VWIAX VWENX VMRAX VWUAX );
	my @mf_fidelity = qw (FMAGX FSDCX FGRIX FNMIX FASGX);
	
	my @mf_mesirow = qw (DFUSX DGSIX FPACX SGIIX IVWIX VGWAX );
	push @symbol_list, @mf_vanguard, @mf_fidelity, @mf_mesirow;

	return @symbol_list;
	# switch ($tab_name ) {
	#	case "mf":	@ret_val = push @mf_vanguard, @mf_fidelity, @mf_mesirow; break;
	#	
	#}
}


sub getQuote {
	my $quoter = Finance::Quote->new;      # Create the F::Q object.
	$quoter->timeout(30);	# Cancel fetch operation if it takes longer than 30 seconds.
	$quoter->failover(0);
	## @symbols = getSymbols("mf");
	print "Looking for symbols (" . scalar @symbols . "): " . join (", ", @symbols) . $NL if ($debug);

	# Grab our information and place it into %info.
	## my %info = $quoter->fetch($exchange, @symbols);
	my %info = $quoter->yahoo_json($exchange, @symbols);
	## my %info = $quoter->vanguard(@symbols);
	## my %info = $quoter->fidelity_direct(@symbols);
	
	
	## make sure the close does not have too many digits. Either truncate the string, or round the float
	## round the float
	foreach my $stock1 (@symbols) {
		my $cl = $info{$stock1, "close"};
		if (length($cl) > 6) {
			$info{$stock1, "close"} = sprintf("%.2f", $cl);
			
		}
	}
	
	return %info;
}

##
##	START HERE
##
my ($type) = @ARGV;
if (defined $type) {
	print "Parsing arguments. (type is already set to: $type)$NL";
	foreach my $arg (@ARGV) {
		print "Arg: $arg$NL";
	}
} else {
	$type = "mf";
}

my $fname = get_data_filename($type);
my @datafile_contents = read_datafile($fname, 1);
my %data = parse_datafile(@datafile_contents);

##DEBUG: print "\@output_order is size: " . scalar(@output_order) . ": " . join(", ", @output_order) . $NL;

## get the quote and show the elapsed time. It takes about 3.1 seconds to get 15 quotes
my $t0 = [gettimeofday];
my %info = getQuote();
my ($seconds, $microseconds) = gettimeofday;
my $elapsed = tv_interval ( $t0, [$seconds, $microseconds]);
printf ( "Elapsed time was: %.2f\n", $elapsed );
##DEBUG: print "Size of array quotes is: " . scalar %info . "\n";

my @columns = @columns_I_want;
my $num_columns = scalar @columns;

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
	my $stock = $line;
	##print "show data for stock: $stock$NL";
	unless ($info{$stock, "success"}) {
		warn "Lookup of $stock failed - ".$info{$stock, "errormsg"}.
		     "\n";
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

##my @k = keys %info;
##print "Keys are: $NL" . join ($TAB, @k) . $NL;
##foreach my $k (@k) {
##	print $k . $NL if !index($k, "AAPL");
##}