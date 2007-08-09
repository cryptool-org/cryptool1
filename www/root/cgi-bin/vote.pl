#!/usr/bin/perl

# $Id: vote.pl,v
# $Log: vote.pl,v $
# Revision 1.4  2004/08/26 09:16:32  bunti
# freitextfeld
#   eingaben werden in separater logdatei voteft.log gespeichert
#
# Revision 1.3  2004/08/04 07:36:35  bunti
# Umfrage für die Weiterentwicklung
#
# Revision 1.2  2004/07/28 13:50:35  bunti
# warning entfernt
# log format verbessert
#
# Revision 1.1  2004/07/28 13:15:42  bunti
# Abstimmungsskript fuer die Wahl der Programmiersprache
#

$logname = "var/vote.log";
$logname_freetext = "var/voteft.log";

# sub escape {
#   my $toencode = shift;
#   return undef unless defined($toencode);
#   $toencode=~s/([^a-zA-Z0-9_.-])/uc sprintf("%%%02x",ord($1))/eg;
#   return $toencode;
# }

sub unescape {
  my $todecode = shift;
  return undef
    unless defined($todecode);
  $todecode =~ tr/+/ /;
  $todecode =~ s/%([0-9a-fA-F]{2})/chr hex($1)/ge;
  return $todecode;
}

sub parse_params {
  my $tosplit = shift;
    my(@pairs) = split(/[&;]/,$tosplit);
    my($param,$value);
    my(%p) = ();
    foreach (@pairs) {
        ($param,$value) = split('=',$_,2);
        $value ||= '';
	$p{unescape($param)} = unescape($value);
    }
    return %p;
}

# if (defined($ENV{PATH_INFO})) {
#   # PATH_INFO is create by a self redirect (see below)
#   # PATH_INFO format: /QUERY_STRING-before-redirect/download-file-name
#   # HACK: get QUERY_STRING from PATH_INFO
#   $ENV{PATH_INFO} =~ m{^/([^/]*)/} or die "malformed PATH_INFO: $ENV{PATH_INFO}";
#   $ENV{QUERY_STRING} = unescape($1);
# }

%p = parse_params($ENV{QUERY_STRING});

$prog_lang = $p{devel} or $prog_lang = "NONE";
$lang = $p{lang} or $lang="en";

open(LOG,">>$logname") ||exit;
use Socket;
@TIME=(localtime(time));
$host = gethostbyaddr(inet_aton($ENV{'REMOTE_ADDR'}),AF_INET) || '';
$t = sprintf("%d-%02d-%02dT%02d:%02d:%02d",$TIME[5]+1900,$TIME[4]+1,$TIME[3],$TIME[2],$TIME[1],$TIME[0]);

print LOG $t," ", 
    $ENV{'REMOTE_ADDR'},"(",$host,") ", 
    "UserAgent ",$ENV{'HTTP_USER_AGENT'}," ",
    "[lang: ", $prog_lang, " ]\n";
close(LOG);

open (LOG, ">>$logname_freetext") || exit;
@TIME=(localtime(time));
$host = gethostbyaddr(inet_aton($ENV{'REMOTE_ADDR'}),AF_INET) || '';
$t = sprintf("%d-%02d-%02dT%02d:%02d:%02d",$TIME[5]+1900,$TIME[4]+1,$TIME[3],$TIME[2],$TIME[1],$TIME[0]);

print LOG $t," ",
    $ENV{'REMOTE_ADDR'},"(",$host,")\n",
    "$comments\n";
close(LOG);


print "Content-type: text/html\n\n";
print '<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">', "\n";
print "<html><head><title>CrypTool</title></head><body>\n";
if ($lang eq "de") {
    print "<p>Vielen Dank, dass Sie an der Umfrage teilgenommen haben.</p>\n";
} else {
    print "<p>Thank You for participating in the survey.</p>\n";
}
print "</body></html>\n";

exit;

