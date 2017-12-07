# updateBuildInformation.pl

#
# This script is called as pre-build and as post-build 
# task from within Visual Studio. It updates a couple of 
# static variables in "CrypToolApp.cpp" (i.e. build time 
# and SVN revision) and some resources in "CrypTool.rc"
# (i.e. the IDE version in the window title) if invoked 
# with the "PRE" parameter, and it reverts those changes 
# when invoked after the build with the "POST" parameter.
# The "IDE" parameter is optional.
#
# flomar, 03/04/2012
#

use strict;

#############################################################
#                                                           #
# CrypTool versions are displayed as follows:               #
# [MAJOR].[MINOR].[REVISION] [ADDITION] [IDE]               #
#                                                           #
# The [MAJOR], [MINOR] and [REVISION] parameters (see       #
# below) must be defined, [ADDITION] and [IDE] (defined     #
# through command-line parameters) are optional. However,   #
# if the "RELEASE" variable is defined, both the [ADDITION] # 
# as well as the [IDE] parameters are completely ignored.   #
#                                                           #
#############################################################

my $RELEASE = 1;

my $CrypToolVersionMajor = "1";
my $CrypToolVersionMinor = "4";
my $CrypToolVersionRevision = "41";
my $CrypToolVersionAddition = "";

#############################################################
#                                                           #
#############################################################

my $mode = undef;
my $ide = undef;

my $fileCrypToolApp = "CrypToolApp.cpp";
my $fileCrypToolRC = "CrypTool.rc";

my $fileCrypToolApp_BACKUP = "CrypToolApp-BACKUP.cpp";
my $fileCrypToolRC_BACKUP = "CrypTool-BACKUP.rc";

# some error checking
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
}

# mode PRE: we update the files
if($mode eq "PRE") {

	print "Updating CrypTool build information...\n";
	
	# check if all necessary parameters are defined
	if(	not defined $CrypToolVersionMajor or 
		not defined $CrypToolVersionMinor or
		not defined $CrypToolVersionRevision) {
		print "WARNING: CrypTool version invalid";
		exit;
	}
	
	#
	# build the CrypTool version (used throught the CrypTool application);
	# if we have a non-release version (read: $RELEASE is undefined), we 
	# also append the IDE information; format looks as follows:
	# 	"CrypTool 1.4.31 Beta 5"
	#
	my $CrypToolVersion = $CrypToolVersionMajor . "." . $CrypToolVersionMinor . "." . $CrypToolVersionRevision;
	my $CrypToolVersionFull = $CrypToolVersion;
	# use a version string with an additional tag and IDE information (if existent)
	if(not defined $RELEASE && defined $CrypToolVersionAddition) {
		$CrypToolVersionFull .= " " . $CrypToolVersionAddition;
		if(not defined $RELEASE && defined $ide) {
			$CrypToolVersionFull .= " " . "[" . $ide . "]";
		}
	}
	
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
		# inserting i.e. "CrypTool 1.4.31 Beta 5 [VS2008]" (full version)
		if($line =~ m{ \[CRYPTOOL_VERSION_FULL\] }xms) {
			$line = "IDR_MAINFRAME \"CrypTool $CrypToolVersionFull\"\n";
		}
		# inserting i.e. "1.4.31"
		if($line =~ m{ FileVersion }xms and $line =~ m{ \[CRYPTOOL_VERSION\] }xms) {
			$line = "VALUE \"FileVersion\", \"$CrypToolVersion\"\n";
		}
		# inserting i.e. "1.4.31"
		if($line =~ m{ ProductVersion }xms and $line =~ m{ \[CRYPTOOL_VERSION\] }xms) {
			$line = "VALUE \"ProductVersion\", \"$CrypToolVersion\"\n";
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
	print "Reverting CrypTool build information changes...\n";
	# copy from backup files
	system("copy $fileCrypToolApp_BACKUP $fileCrypToolApp");
	system("copy $fileCrypToolRC_BACKUP $fileCrypToolRC");
	# remove backup files
	system("del $fileCrypToolApp_BACKUP");
	system("del $fileCrypToolRC_BACKUP");
}

