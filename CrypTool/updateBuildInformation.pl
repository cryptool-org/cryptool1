# updateBuildInformation.pl

#
# This script is called as pre-build and as post-build 
# task from within Visual Studio. It updates a couple of 
# static variables in "CrypToolApp.cpp" (i.e. build time 
# and SVN revision) if invoked with the "PRE" parameter, 
# and it reverts those changes when invoked after the 
# build with the "POST" parameter.
#
# flomar, 03/04/2012
#

use strict;

print "Updating CrypTool build time and SVN revision...\n";

my $mode = undef;
my $file = "CrypToolApp.cpp";

if(scalar @ARGV != 1) {
	print "Please supply exactly one argument, either PRE or POST! Exiting...\n";
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
		print "Please supply exactly one argument, either PRE or POST! Exiting...\n";
		exit;
	}	
}

# mode PRE: we update "$file"
if($mode eq "PRE") {
	my $buildTime = undef;
	my $svnRevision = undef;

	# determine the current time
	my ($sec,$min,$hour,$day,$month,$yr19,@rest) = localtime(time);
	$buildTime = (1900+$yr19) . "-" . ($month+1) . "-" . ($day);

	# determine the current SVN revision
	my $line = `svnversion .`;
	chomp($line);
	if($line =~ m{ \d+ : (\d+) .* }xms) {
		$svnRevision = $1;
	}

	# open the file
	my @lineArray;
	open(FILE, "<$file") or die ("Opening $file: $!\n");
	@lineArray = <FILE>;
	close(FILE);

	# update the file content (with build time and current SVN revision)
	foreach my $line(@lineArray) {
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
	open(FILE, ">$file") or die ("Opening $file $!\n");
	foreach my $line(@lineArray) {
	  print FILE $line;
	}
	close(FILE);
}

# mode POST: restore initial state of the file
if($mode eq "POST") {
	
	# open the file
	my @lineArray;
	open(FILE, "<$file") or die ("Opening $file: $!\n");
	@lineArray = <FILE>;
	close(FILE);
	
	# update the file content (with default values for build time and current SVN revision)
	foreach my $line(@lineArray) {
		if($line =~ m{ \#define \s+ CRYPTOOL_BUILD_TIME }xms) {
			$line = "#define CRYPTOOL_BUILD_TIME \"[BUILD TIME]\"\n";
		}
		if($line =~ m{ \#define \s+ CRYPTOOL_SVN_REVISION }xms) {
			$line = "#define CRYPTOOL_SVN_REVISION \"[SVN REVISION]\"\n";
		}
	}
	
	# re-write the file
	open(FILE, ">$file") or die ("Opening $file $!\n");
	foreach my $line(@lineArray) {
	  print FILE $line;
	}
	close(FILE);
}

