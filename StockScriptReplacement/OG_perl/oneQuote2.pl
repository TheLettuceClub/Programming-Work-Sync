##
## Links to think about:
##
##	https://metacpan.org/pod/Finance::YahooQuote
##	https://metacpan.org/pod/Finance::Quote
##	http://finance-quote.sourceforge.net/tpj/finance-quote.txt
##

use strict;
use Finance::Quote;

my $TAB = "\t";
my $NL = "\n";
my $symbol = 'SPY';
my $exchange = "usa";
my @symbols = ( "SPY", "AAPL", "ULTA", "GOOG" );
## @columns_I_want = ( "Symbol", "Company Name", "Last Price");
my @columns_I_want = ( "close");
my $print_titles = 1;


my $quoter = Finance::Quote->new;	# Create the F::Q object.

$quoter->timeout(30);		# Cancel fetch operation if it takes
				# longer than 30 seconds.

# Grab our information and place it into %info.
my %info = $quoter->fetch($exchange, @symbols);

if ($print_titles != 0) {
	print "Symbol" . $TAB . ucfirst join($TAB, @columns_I_want) . $NL;
}

## print "Listing all keys..." . $NL;
## print join(", ", keys %info) . $NL;


foreach my $stock (@symbols) {
	unless ($info{$stock,"success"}) {
		warn "Lookup of $stock failed - ".$info{$stock,"errormsg"}. "\n";
		next;
	}

	my @row = @info{$stock};
	print "$stock\t";
	foreach my $column (@columns_I_want) {
		print $info{$stock,$column},"\t";
	}  print $NL;
}