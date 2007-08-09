#!/usr/bin/perl

# $Id: getcryptool.pl,v 1.14 2004/07/28 13:15:42 bunti Exp $
# $Log: getcryptool.pl,v $
# Revision 1.14  2004/07/28 13:15:42  bunti
# Abstimmungsskript fuer die Wahl der Programmiersprache
# getcryptool.pl erweitert fuer absimmung bei den downloads
#
# Revision 1.13  2004/03/15 13:12:33  bunti
# Testlogging abgeschlossen und Code deaktiviert
#
# Revision 1.12  2004/03/15 12:34:51  bunti
# Testlogger von bunti
#
# Revision 1.11  2004/03/12 14:17:56  bunti
# Testlogger von bunti
#
# Revision 1.10  2004/03/12 13:58:51  bunti
# Testlogger von bunti
#
# Revision 1.9  2004/03/09 16:07:45  bunti
# kleiner fehler, fixed
#
# Revision 1.8  2004/03/09 16:05:31  bunti
# Der Grund des Downloads wird geloggt, die Aufforderung wird aber noch nicht
# online gestellt.
#
# Revision 1.7  2004/02/17 17:02:26  clausius
# *** empty log message ***
#
# Revision 1.6  2003/08/04 17:17:48  clausius
# Download wieder gangbar gemacht
#
# Revision 1.5  2003/08/04 16:37:24  clausius
# Testing
#
# Revision 1.4  2003/07/17 15:30:36  schneider
# release 1.3.04
#
# Revision 1.3  2002/11/07 15:42:53  clausius
# Perl und Verzeichnispfade angepasst
#
# Revision 1.2  2002/11/05 13:20:27  clausius
# Update auf Version 1.3.03
#
# Revision 1.6  2002/04/25 06:48:39  bdf100
# PATH_INFO encoding bug
#
# Revision 1.5  2002/02/26 12:49:55  bdf100
# content-disposition behaviour documented
#
# Revision 1.4  2002/02/08 15:29:06  bdf100
# fix month (+1) in log
#
# Revision 1.3  2002/02/04 16:19:35  bdf100
# logfile: fix for sec min order
#
# Revision 1.2  2002/01/28 19:05:31  bdf100
# removed regexpr again
#
# Revision 1.2  2001/12/21 14:12:21  bdf100
# Multi version capability
#
#
#CGI parameters
#nolicence=URL to redirect if licence is not accepted
#file = the file to download, must be listed in $filelist
#licence=y|n

$downloadpath = '/www/cryptool/downloads/'; #must be empty or end with '/'
$downloads = "etc/downloads";
$logname = "var/cryptool.log";

sub escape {
  my $toencode = shift;
  return undef unless defined($toencode);
  $toencode=~s/([^a-zA-Z0-9_.-])/uc sprintf("%%%02x",ord($1))/eg;
  return $toencode;
}

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

sub relocate {
  my $where = shift;
  die "relocation path must be absolute: $where" unless $where =~ m{^/};
  #print STDERR "Status: 301 look here\r\nLocation: http://$ENV{HTTP_HOST}$where\r\n\r\n";
  "Status: 301 look here\r\nLocation: http://$ENV{HTTP_HOST}$where\r\n\r\n";
}

if (defined($ENV{PATH_INFO})) {
  # PATH_INFO is create by a self redirect (see below)
  # PATH_INFO format: /QUERY_STRING-before-redirect/download-file-name
  # HACK: get QUERY_STRING from PATH_INFO
  $ENV{PATH_INFO} =~ m{^/([^/]*)/} or die "malformed PATH_INFO: $ENV{PATH_INFO}";
  $ENV{QUERY_STRING} = unescape($1);
}

%p = parse_params($ENV{QUERY_STRING});

open(F,"<$downloads") or die "cannot open $downloads";
%downloads = ();
foreach (grep(!/^\#/,<F>)) {
  chomp;
  my ($n,$f) = split("\t");
  $downloads{$n} = $f || '';
}
close F;

$file = $p{file} or die "parameter file not defined";
$purpose = $p{src_interest} or $purpose="NONE";
$prog_lang = $p{devel} or $prog_lang = "NONE";

# open LOG, ">>var/test.log";
# foreach (keys %p) {
#     print LOG $_,": ", $p{$_},"\n";
# }

# print LOG "\n\n";
# close LOG;

$needlicence = $downloads{$file};

if (!defined $needlicence) {
  print STDERR "contents of download:\n";
  foreach (keys %downloads) {
    print STDERR "$_\n";
  }
}
die "not in $downloads: $p{file}" unless defined($needlicence);

$nolicence = $p{nolicence};
die "nolicence not defined" if $needlicence && ! defined($nolicence);

$licence = $p{licence} || '';

if ($needlicence && $licence !~ m{^[yj]$})
{
  print relocate($nolicence);
  exit;
#  print "needlicence";
}


if (!$ENV{PATH_INFO}) {
  # make a self redirect with the file name to download as last path component.
  # this gives browsers a hint which name to use for saving the file
  my $q = escape(escape($ENV{QUERY_STRING})); # one 'escape' will be decoded by apache
  my $f = $file;		              # the other by the code above marked (1)
  $f =~ s{.*/}{};
  # we encode the query string in the path before the file name
  # it used to be appended like "$f?$q" to the end, but this does not work with ie
  print relocate("$ENV{SCRIPT_NAME}/$q/$f");
  exit;
}

open(SETUP,"<$downloadpath$file") ||
  die("Kann Datei $downloadpath$file nicht öffnen: $!");
seek(SETUP,0,2);
$len = tell(SETUP);  
print "Content-Type: application/octet-stream\r\ncontent-length: ",$len,
  "\r\n\r\n";
#  "\r\nContent-Disposition: attachment; filename=\"$file\"\r\n\r\n"; #does not work with IE 5.5
seek(SETUP,0,0);
while (<SETUP>) {print ;};
close(SETUP);
open(LOG,">>$logname") ||exit;
use Socket;
@TIME=(localtime(time));
$host = gethostbyaddr(inet_aton($ENV{'REMOTE_ADDR'}),AF_INET) || '';
$t = sprintf("%d-%02d-%02dT%02d:%02d:%02d",$TIME[5]+1900,$TIME[4]+1,$TIME[3],$TIME[2],$TIME[1],$TIME[0]);

print LOG $t,
    " [$file] ",
    $ENV{'REMOTE_ADDR'},"(",$host,") ", 
    "UserAgent ",$ENV{'HTTP_USER_AGENT'}," ",
    "Version $version ",
    "[src: ", $purpose, "] ",
    "[lang: ", $prog_lang, " ]\n";
close(LOG);

exit;

