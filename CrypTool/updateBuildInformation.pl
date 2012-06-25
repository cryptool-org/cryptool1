# updateBuildInformation.pl

#
# This script is called as pre-build and as post-build 
# task from within Visual Studio. It updates a couple of 
# static variables in "CrypToolApp.cpp" (i.e. build time 
# and SVN revision) and some resources in "CrypTool.rc"
# (i.e. the IDE version in the window title) if invoked 
# with the "PRE" parameter, and it reverts those changes 
# when invoked after the build with the "POST" parameter.
# The "VS2008" or "VS2010" parameters are optional.
#
# flomar, 03/04/2012
#

use strict;

print "Updating CrypTool build time and SVN revision...\n";

my $mode = undef;
my $ide = undef;

my $CrypToolVersion = "1.4.31 Beta 4";

my $fileCrypToolApp = "CrypToolApp.cpp";
my $fileCrypToolRC = "CrypTool.rc";

my $fileCrypToolApp_BACKUP = "CrypToolApp-BACKUP.cpp";
my $fileCrypToolRC_BACKUP = "CrypTool-BACKUP.rc";

if(scalar @ARGV < 1) {
	print "Please supply at least one argument, either PRE or POST! Exiting...\n";
	exit;
}
else {
	if($ARGV[0] eq "PRE") {
		$mode = "PRE";
	}
	elsif($ARGV[0] eq "POST") {
		$mode = "POST";
	}
	else {
		print "Please supply at least one argument, either PRE or POST! Exiting...\n";
		exit;
	}
	if($ARGV[1] eq "VS2008") {
		$ide = "VS2008";
	}
	if($ARGV[1] eq "VS2010") {
		$ide = "VS2010";
	}
}

# mode PRE: we update the files
if($mode eq "PRE") {

	# copy the original files
	system("copy $fileCrypToolApp $fileCrypToolApp_BACKUP");
	system("copy $fileCrypToolRC $fileCrypToolRC_BACKUP");

	my $buildTime = undef;
	my $svnRevision = undef;
	
	# determine the current time
	my ($sec,$min,$hour,$day,$month,$yr19,@rest) = localtime(time);
	$buildTime = (1900+$yr19) . "-" . ($month+1) . "-" . ($day);

	# determine the current SVN revision
	my $line = `svnversion .`;
	chomp($line);
	if($line =~ m{ \d+ : (\d+) .* }xms or $line =~ m{ (\d+) .* }xms) {
		$svnRevision = $1;
	}

	# open the file (fileCrypToolApp)
	my @lineArrayFileCrypToolApp;
	open(FILE, "<$fileCrypToolApp") or die ("Opening $fileCrypToolApp: $!\n");
	@lineArrayFileCrypToolApp = <FILE>;
	close(FILE);

	# update the file content (with build time and current SVN revision)
	foreach my $line(@lineArrayFileCrypToolApp) {
		if($line =~ m{ \#define \s+ CRYPTOOL_BUILD_TIME }xms) {
			if(defined $buildTime) {
				$line = "#define CRYPTOOL_BUILD_TIME \"$buildTime\"\n";
			}
		}
		if($line =~ m{ \#define \s+ CRYPTOOL_SVN_REVISION }xms) {
			if(defined $svnRevision) {
				$line = "#define CRYPTOOL_SVN_REVISION \"$svnRevision\"\n";
			}
		}
	}

	# re-write the file
	open(FILE, ">$fileCrypToolApp") or die ("Opening $fileCrypToolApp $!\n");
	foreach my $line(@lineArrayFileCrypToolApp) {
	  print FILE $line;
	}
	close(FILE);
	
	# open the file (fileCrypToolRC)
	my @lineArrayFileCrypToolRC;
	open(FILE, "<$fileCrypToolRC") or die ("Opening $fileCrypToolRC: $!\n");
	@lineArrayFileCrypToolRC = <FILE>;
	close(FILE);
	
	# update the file content (with build time and current SVN revision)
	foreach my $line(@lineArrayFileCrypToolRC) {
		if($line =~ m{ \[CRYPTOOLVERSION_AND_IDE\] }xms) {
			if(defined $ide) {
				$line = "IDR_MAINFRAME \"CrypTool $CrypToolVersion [$ide]\"\n";
			}
			else {
				$line = "IDR_MAINFRAME \"CrypTool $CrypToolVersion\"\n";
			}
		}
	}

	# re-write the file
	open(FILE, ">$fileCrypToolRC") or die ("Opening $fileCrypToolRC $!\n");
	foreach my $line(@lineArrayFileCrypToolRC) {
	  print FILE $line;
	}
	close(FILE);
}

# mode POST: restore initial state of the file
if($mode eq "POST") {
	# copy from backup files
	system("copy $fileCrypToolApp_BACKUP $fileCrypToolApp");
	system("copy $fileCrypToolRC_BACKUP $fileCrypToolRC");
	# remove backup files
	system("del $fileCrypToolApp_BACKUP");
	system("del $fileCrypToolRC_BACKUP");
}

