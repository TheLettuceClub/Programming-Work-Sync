use Finance::YahooQuote;
# setting TIMEOUT and PROXY is optional
$Finance::YahooQuote::TIMEOUT = 60;
## $Finance::YahooQuote::PROXY = "http://some.where.net:8080";

$TAB = "\t";
$NL = "\n";
$symbol = 'SPY';
@symbols = ( "SPY", "AAPL", "ULTA", "GOOG" );
@columns_I_want = ( "Symbol", "Company Name", "Last Price");

function getSymbols($tab_name) {
	my @mf_vanguard = qw (VWIAX VWENX VMRAX VWUAX );
	my @mf_fidelity = qw (FMAGX FSDCX);
	
	my @mf_mesirow = qw (DFUSX DGSIX FPACX SGIIX IVWIX VGWAX );

	return push @mf_vanguard, @mf_fidelity, @mf_mesirow;
	# switch ($tab_name ) {
	#	case "mf":	@ret_val = push @mf_vanguard, @mf_fidelity, @mf_mesirow; break;
	#	
	#}
}

function getShares($symbol) {
	## return an array of integers; shares of each security
	
	my %shares = (	VWIAX => 100,
					VWENX => 100,
					VMRAX => 100,
					VWUAX => 100
	);
	
	my $ret_val = undef;
	if exists ($shares{$symbol} {
		$ret_val = $shares{$symbol};
	}
	return $ret_val;
}


@quote = getonequote $symbol; # Get a quote for a single symbol
@quotes = getquote @symbols;  # Get quotes for a bunch of symbols
##	useExtendedQueryFormat();     # switch to extended query format
##	useRealtimeQueryFormat();     # switch to real-time query format
##	@quotes0 = getquote @symbols;  # Get quotes for a bunch of symbols
##	@quotes1 = getcustomquote(["DELL","IBM"], # using custom format
##                         ["Name","Book Value"]); # note array refs


## now to print something
@columns = @columns_I_want;
$num_columns = scalar @columns;

print "Size of array quote is: " . scalar @quote . "\n";
print "Size of array quotes is: " . scalar @quotes . "\n";

print '\@quotes is: ' . "\n";
foreach ( @quotes ) {
	print ">" . $_ . "<";
}
for ( $i = 0; $i < $num_columns; $i++) {
	print $quote[$i];
} print $NL;

### for now the single stock:
#foreach ( @columns) {
#	print $quote[$_] . "\t";
#}

## print header/column names
foreach ( @columns ) {
	print "$_\t";
} print $NL;

## now get each quote from the array of quotes...
foreach (@quotes) {
	@q = @_;
	print "This quote is of size: " . scalar @q . $NL;
	print $q . $NL;
	print $q[0] . $TAB . $q[1] . $NL;
}

print 'A' . $NL;
#foreach my $row (@quotes) {
#    foreach my $element (@$row) {
#        print $element, "\n";
#    }
#}

print 'B' . $NL;
foreach (@quotes) {
    @row = @$_;
    print "Row size is: " . scalar @row . $NL;
    foreach $val (@row) {
        # do your processing here
	print ">" . $_ . "<" . $TAB;
    } print $NL;
}

print " 0 0 " . $quotes[0][0]. "<" . $NL;
print " 1 1 " . $quotes[1][1]. "<" . $NL;
print " 2 2 " . $quotes[2][2]. "<" . $NL;
