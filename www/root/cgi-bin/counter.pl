#!/usr/bin/perl
# $Id: counter.pl,v 1.15 2004/02/17 17:16:26 clausius Exp $
# File: .../cgi-bin/burnsCount.cgi
# Purpose: Simple access counter
# Author: Joe Burns
# Retrieved from URL: http://www.htmlgoodies.com/countcgi.html
# Modified by George Corliss, MArquette University MSCS, 11-Jul-1997

# important for sysopen constants
use Fcntl;  

$minLen = 6;

#This is absolute path of the directory where the counter
#files are stored. Must be global-writeable.
#$counterdir = "/directory/sub/sub/sub/counts/";
$counterdir = "var/";
$counterlockdir = "/tmp/";

$lockWait = 5;

#umask 0777;
&ReadParse;
&initialize;
&loadbitmaps;
&incrementCount;
&generateBitmap;
&writeBitmap;
exit(0);


# SUBROUTINES:

sub writeBitmap {
  print "Cache-Control: no-cache\n";
  print "Content-type: image/x-xbitmap\n\n";
  print "#define count_width ",$len*8,"\n#define count_height 16\n";
  print "static char count_bits[] = {\n";
  for($i = 0; $i < ($#bytes + 1); $i++) {
    print "0x$bytes[$i]";
    if ($i != $#bytes) {
      print ",";
      if (($i+1) % 7 == 0) {
        print "\n" ;
      }
    }
  }
  print "};\n";
}

sub generateBitmap {
  $count = $totalReads;
  @bytes = ();
  $len = length($count) > $minLen ? length($count) : $minLen;
  $outtext = sprintf("%0${len}d",$count);
  for ($i = 0; $i < $len*3; $i++ ) {
    push(@bytes,"ff");
  }
  for ($y=0; $y < 10; $y++) {
    for ($x=0; $x < $len; $x++) {
      push(@bytes,substr($chars{substr($outtext,$x,1)},$y*3,2));
    }
  }
  for ($i = 0; $i < $len*3; $i++ ) {
    push(@bytes,"ff");
  }
}


sub initialize {
  if ($#in < 0) {
    $scriptURL = "http://" . $ENV{'SERVER_NAME'} . ":"
          . $ENV{'SERVER_PORT'} . $ENV{'SCRIPT_NAME'};
    print <<FINIS;
Content-type: text/html

<HTML><HEAD><TITLE>Visitor counter</TITLE></HEAD>
<BODY>

<h1>counter.xbm</h1>

To put a visitor counter like this
<IMG SRC = "$scriptURL?unique_id">
on your web page, put an image tag in your HTML document like:
<dd>&lt;IMG SRC = "$scriptURL?unique_id"&gt;<br>
where "unique_id" is a unique identifier for your counter.

<p>
When creating a new counter, you can set the starting value by adding
a count parameter to the URL.  If the counter "qwerty" didn t exist,
accessing the URL
<dd>$scriptURL?qwerty&COUNT=1234<br>
will create a new counter called "qwerty" with its counter set to
1234.  The counter can only be set when creating a new counter.

</BODY>
</HTML>
FINIS
    exit;
  }
  else {
    $countername = $in[0];
    $countername =~ s/\W//g;
    $counterFile = $counterdir . $countername;
    $counterLockFile = $counterdir . $countername . ".lock";
    if (!( -f $counterFile )) {
      $start = $in{'COUNT'} -1;
      open(CNTRFILE,">$counterFile");
      print CNTRFILE "$start\n";
      close(CNTRFILE);
    }
  }
}

sub incrementCount {
  if (&lockFile == 1) {
    $count = "0";
    return;
  }
  &incrementTotalReads;
  &unlockFile;
}

sub removeStaleLockFile{
    my ($dev,$ino,$mode,$nlink,$uid,$gid,$rdev,$size,
	$atime,$mtime,$ctime,$blksize,$blocks) = stat "$counterFile.lock";
    unlockFile if ( (time-$mtime) > 60);
}

sub unlockFile {
  unlink($counterLockFile);
}

sub lockFile {
  $lockCount = 0;
  &removeStaleLockFile if (-f "$counterLockFile");
  while (-f $counterLockFile) {
    if ($lockCount > $lockWait) {
      $count = 0;
      return 1;
    }
    sleep 1;
    $lockCount++;
  }
  sysopen(LOCK,$counterLockFile, O_CREAT | O_EXCL)
        || die("Can't open $counterLockFile: $!\n");
  return 0;
}

sub incrementTotalReads {
  if (-e $counterFile) {
    open(COUNT,"$counterFile") || die("Can't open $counterFile: $!\n");
  }
  $totalReads = <COUNT>;
  chop $totalReads;
  close(COUNT);
  $totalReads++;
  open(COUNT,">$counterFile") || die "$0: can\'t open $counterFile: $!\n";
  print (COUNT "$totalReads\n");
  close(COUNT);
}

sub loadbitmaps {
  $chars{'0'} = "c3 99 99 99 99 99 99 99 99 c3";
  $chars{'1'} = "cf c7 cf cf cf cf cf cf cf c7";
  $chars{'2'} = "c3 99 9f 9f cf e7 f3 f9 f9 81";
  $chars{'3'} = "c3 99 9f 9f c7 9f 9f 9f 99 c3";
  $chars{'4'} = "cf cf c7 c7 cb cb cd 81 cf 87";
  $chars{'5'} = "81 f9 f9 f9 c1 9f 9f 9f 99 c3";
  $chars{'6'} = "c7 f3 f9 f9 c1 99 99 99 99 c3";
  $chars{'7'} = "81 99 9f 9f cf cf e7 e7 f3 f3";
  $chars{'8'} = "c3 99 99 99 c3 99 99 99 99 c3";
  $chars{'9'} = "c3 99 99 99 99 83 9f 9f cf e3";
}

# Perl Routines to Manipulate CGI input
# Copyright 1993 Steven E. Brenner
sub ReadParse {
  if (@_) {
    local (*in) = @_;
  }

  local ($i, $loc, $key, $val);

  # Read in text
  if ($ENV{'REQUEST_METHOD'} eq "GET") {
    $in = $ENV{'QUERY_STRING'};
  } elsif ($ENV{'REQUEST_METHOD'} eq "POST") {
    for ($i = 0; $i < $ENV{'CONTENT_LENGTH'}; $i++) {
      $in .= getc;
    }
  }

  @in = split(/&/,$in);

  foreach $i (0 .. $#in) {
    # Convert plus's to spaces
    $in[$i] =~ s/\+/ /g;

    # Convert %XX from hex numbers to alphanumeric
    $in[$i] =~ s/%(..)/pack("c",hex($1))/ge;

    # Split into key and value.
    $loc = index($in[$i],"=");
    $key = substr($in[$i],0,$loc);
    $val = substr($in[$i],$loc+1);
    $in{$key} .= '\0' if (defined($in{$key})); # \0 is the multiple separator
    $in{$key} .= $val;
  }

  return 1;
}

END { unlink($counterLockFile); }
