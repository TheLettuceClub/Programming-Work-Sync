
use strict;
use warnings;

use LWP::Simple;
my $TAB = "\t";
my $NL = "\n";
my $symbol = 'SPY';
my $exchange = "usa";
my @symbols = ( "SPY", "AAPL", "ULTA", "GOOG" );
my @columns_I_want = ( "Symbol", "Company Name", "Last Price");

my $url = 'https://finance.yahoo.com/quotes/SPY,ulta,AAPL,%5Evix,BRKB,XOM,COP,XLNX,MSFT,GOOG,intc,amzn,csco?.tsrc=fin-srch';
my $file = 'data.html';

getstore($url, $file);