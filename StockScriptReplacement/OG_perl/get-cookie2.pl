use strict;
# use Finance::Quote;
# use Time::HiRes qw( gettimeofday tv_interval);			## for testing/timing purposes
# use Text::CSV;
use CGI;
use CGI::Cookie;

use strict;
# use LWP::Simple;
use LWP::UserAgent;
use HTTP::Cookies;

my $url_get_crumb = 'https://query2.finance.yahoo.com/v1/test/getcrumb';
my $url_get_quote = 'https://query1.finance.yahoo.com/v7/finance/quote?symbols=AAPL';

my $ua = new LWP::UserAgent;
$ua->timeout(120);
my $url1=$url_get_crumb;
# $url1='https://fc.yahoo.com/';

print "\>\>Making request of: $url1\n";
my $request = new HTTP::Request('GET', $url1);
my $response = $ua->request($request);
my $content = $response->content();
print "Content: $content\n";
print "Response: $response\n";

foreach my $var (keys %{$response}) {
    print "response $var has value: $response->{$var}\n";
}
my $cookie_jar = HTTP::Cookies->new(ignore_discard => 1);
my $cookie_hash = $cookie_jar->extract_cookies( $response);
my $header_cookies;
foreach my $var (keys %{$cookie_hash}) {
    print "Cookie $var has value: $cookie_hash->{$var}\n";
}

print "Saving _headers from cookie_hash into \$index\n";
my $index = '_headers';
$header_cookies = $cookie_hash->{$index};
print "\nPrinting Cookies in header\n";
foreach my $var (keys %{$header_cookies}) {
    #print"In the loop \n";
    print "header_cookies $var has value: $header_cookies->{$var}\n";
}
print "\n-----------------\n\n";
#############################################################

my $crumb = 'lAongQaZRJB';
my $url2=$url_get_quote;
$url2 .= '&crumb=' . $crumb;

print "\>\>Sending request: $url2\n";

my $ua2 = new LWP::UserAgent;
$ua2->timeout(120);
my $request2 = new HTTP::Request('GET', $url2);
my $response2 = $ua2->request($request2);
my $content2 = $response2->content();
print "Content: $content2\n";
print "Response: $response2\n\n";
foreach my $var(keys %{$response2}) {
    print "response2 $var has value: $response2->{$var}\n";
}
print "\n-----------------\n\n";


# ignore_discard => 1 tells it to keep session cookies?
my $cookie_jar2 = HTTP::Cookies->new(ignore_discard => 1);
my $cookie_hash2 = $cookie_jar2->extract_cookies( $response2 );
my $header_cookies2;

foreach my $var (keys %{$cookie_hash2}) {
    print "Cookie $var has value: $cookie_hash2->{$var}\n";
}

print "Saving _headers from cookie_hash into \$index\n";
my $index = '_headers';
$header_cookies2 = $cookie_hash2->{$index};
print "\nPrinting Cookies in header\n";
foreach my $var2 (keys %{$header_cookies2}) {
    #print"In the loop \n";
    print "header_cookies2 $var2 has value: $header_cookies2->{$var2}\n";
}


my $cookie_to_find = 'set-cookie';
my $cookie_in_header = $header_cookies->{$cookie_to_find};
print "Re-using set-cookie: $cookie_in_header\n";

my $url2='https://query2.finance.yahoo.com/v1/test/getcrumb';
#my $url2a = $url2 . '&cookie=' . $cookie_in_header;
$url2 .= '&cookies=' . $cookie_in_header;

print "\>\>Sending request: $url2\n";
my $ua2 = new LWP::UserAgent;
$ua2->timeout(120);
my $request3 = new HTTP::Request('GET', $url2);
my $response3 = $ua2->request($request3);
my $content3 = $response3->content();

# ignore_discard => 1 tells it to keep session cookies?
my $cookie_jar3 = HTTP::Cookies->new(ignore_discard => 1);
$cookie_jar3->extract_cookies( $response3 );
my $cookie_hash3 = $cookie_jar3->extract_cookies( $response3 );
my $header_cookies3;
print "response3 is $response3\n\n";
$header_cookies3 = $cookie_hash->{$index};
print "\nPrinting Cookies in header\n";
foreach my $var3 (keys %{$header_cookies3}){
    #print"In the loop \n";
    print "header_cookies3 $var3 has value: $header_cookies->{$var3}\n";
}


exit;



# foreach my $key ( keys %$cookie_hash ) { 
#   print $key, " => ", $cookie_hash->{$key},"\n";
#}



#foreach my $name (@cookie_hash) {
#	print "Cookie: " . $name . " = " . $response->cookie($name)."\n";
#   }



   #my $query = CGI->new();
   my $query = $ua;

#- Retrieving old cookies from the incoming request
   my $text = "";
   my @cookies = $query->cookie();
   $text .= (scalar @cookies).' Cookies received from request:'."\n";

   my $count = 0;
   foreach my $name (@cookies) {
      $count++;
      $text .= '   '.$name.' = '.$query->cookie($name)."\n";
   }

#- Creating new cookies
   $count++;
   my $cookie1 = CGI::Cookie->new(-name=>'Chocolate_'.$count,
      -value=>'Another chocolate cookie for you!');
   $count++;
   my $cookie2 = CGI::Cookie->new(-name=>'Sugar_'.$count,
      -value=>'Another sugar cookie for you!');

#- Setting new cookies to the outgoing response
   print $query->header(-cookie=>[$cookie1, $cookie2]);
   print $query->start_html(-title=>'CGI-pm-Manage-Cookies.pl');
   print $query->pre($text);
   print $query->end_html();
