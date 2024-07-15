use strict;

#use CGI;
#use CGI::Cookie;
#use Data::Dumper;

use LWP::UserAgent;
use HTTP::Cookies;

my $ua = new LWP::UserAgent;
$ua->timeout(120);
my $url1='https://fc.yahoo.com/';

my $request = new HTTP::Request('GET', $url1);
print "Sending request: $url1\n";
my $response = $ua->request($request);
#my $content = $response->content();

# ignore_discard => 1 tells it to keep session cookies?
my $cookie_jar = HTTP::Cookies->new(ignore_discard => 1);
my $cookie_hash = $cookie_jar->extract_cookies( $response );

my $index = '_headers';
my $header_cookies = $cookie_hash->{$index};

my $cookie_to_find = 'set-cookie';
my $cookie_in_header = $header_cookies->{$cookie_to_find};
print "Re-using set-cookie: $cookie_in_header\n";
print "\n-----------------\n\n";

my $url2='https://query2.finance.yahoo.com/v1/test/getcrumb';
print "\n\>\>Sending request: $url2\n";

my $request2 = new HTTP::Request('GET' => $url2, 
								HTTP::Headers->new('Cookie'=> $cookie_in_header) 
				);
my $response2 = $ua->request($request2);
my $content2 = $response2->content();

print "content2 (our crumb) is: $content2\n\n";
my $crumb = $content2;
#print "response2 is $response2\n\n";

my $url3 = 'https://query1.finance.yahoo.com/v7/finance/quote?' .
		'crumb=' . $crumb . '&symbols=AAPL';

my $request3 = new HTTP::Request('GET' => $url3, 
								HTTP::Headers->new('Cookie'=> $cookie_in_header) 
				);
my $response3 = $ua->request($request3);
my $content3 = $response3->content();

#print "response3 is: $response3\n";
print "content3 is: $content3\n";
print "\n-----------------\n\n";

my $url4 = 'https://query1.finance.yahoo.com/v7/finance/quote?' .
		'crumb=' . $crumb . '&Cookie=' . $cookie_in_header .
		'&symbols=AAPL';

my $request4 = new HTTP::Request('GET' => $url4 );
print "\n\>\>Sending request: $url4\n";
my $response4 = $ua->request($request4);
my $content4 = $response4->content();

#print "response4 is: $response4\n";
print "content4 is: $content4\n";
