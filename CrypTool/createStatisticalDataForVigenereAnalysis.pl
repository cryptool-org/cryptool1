#!/usr/bin/perl

# createStatisticalDataForVigenereAnalysis.pl
#
# This script creates digrams and trigrams for the Vigenere analysis 
# according to Schroedel. The success of the analysis is tied to the 
# quality of the underlying statistical data. This script can be used 
# to quickly generate the aforementioned data based on a random text.
#
# For your information: This script converts the text to uppercase 
# and ignores every character that is not part of [a-zäöüß]. [äöü] 
# and [ß] are implicitly converted to "aeoeue" and "ss" BEFORE the 
# text is evaluated.
#
# INVOCATION
#
#   You need to pass at least one parameter to this script: the text 
#   file used to generate the statistical data. The script dumps 
#   both, digrams and trigrams, into the files
#     "VigenereAnalysisSchroedelDigrams.txt" and 
#     "VigenereAnalysisSchroedelTrigrams.txt".
# 
# Florian Marchal, 11/16/2009 (florian@marchal.de)

use strict;
use warnings;

#####################################################################

my $fileDigrams = "VigenereAnalysisSchroedelDigrams.txt";
my $fileTrigrams = "VigenereAnalysisSchroedelTrigrams.txt";

# exit if we have not exactly ONE argument
my $numberOfArguments = $#ARGV + 1;
if(not $numberOfArguments == 1) {
	print STDERR "Please specify exactly one filename as argument!\n";
	exit(-1);
}

# set the filename
my $filename = $ARGV[0];

# read file contents into an array
open(FILE, "<$filename") or die("Could not open $1\n");
my @lines = <FILE>;
close(FILE);

# put all lines into one string
my $contents = "";
foreach my $line(@lines) {
	$contents .= $line;
}

# capitalize contents
$contents = uc($contents);

# transform umlauts and other special characters
$contents =~ s/Ã„/AE/g;
$contents =~ s/Ã–/OE/g;
$contents =~ s/Ãœ/UE/g;
$contents =~ s/Ã¤/AE/g;
$contents =~ s/Ã¶/OE/g;
$contents =~ s/Ã¼/UE/g;
$contents =~ s/ÃŸ/SS/g;

# remove all words that contain characters not part of [A-Z\s]
$contents =~ s/[^A-Z\s]+//g;

# isolate words
my @words = split(" ", $contents);

my $alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

# hash for digrams
my %digrams = ();
# init hash
for(my $i=0; $i<26; $i++) {
	for(my $j=0; $j<26; $j++) {
		my $digram = "";
		$digram .= substr($alphabet, $i, 1);
		$digram .= substr($alphabet, $j, 1);
		$digrams{$digram} = 0;
	}
}

# hash for trigrams
my %trigrams = ();
# init hash
for(my $i=0; $i<26; $i++) {
	for(my $j=0; $j<26; $j++) {
		for(my $k=0; $k<26; $k++) {
			my $trigram = "";
			$trigram .= substr($alphabet, $i, 1);
			$trigram .= substr($alphabet, $j, 1);
			$trigram .= substr($alphabet, $k, 1);
			$trigrams{$trigram} = 0;
		}
	}
}

# count digrams and trigrams for each word
foreach my $word (@words) {
	# count digrams
	countDigrams($word);
	# count trigrams
	countTrigrams($word);
}

# print some information
my $numberOfDigrams = keys %digrams;
my $numberOfTrigrams = keys %trigrams;

open(FILE, ">$fileDigrams") or die("Could not open $1\n");
 foreach my $key (sort keys %digrams) {
	print FILE "$key;$digrams{$key}\n";
}
close(FILE);

open(FILE, ">$fileTrigrams") or die("Could not open $1\n");
foreach my $key (sort keys %trigrams) {
	print FILE "$key;$trigrams{$key}\n";
}
close(FILE);



sub countDigrams {
	my $word = shift;
	# ignore words shorter than two characters
	return if(length($word) < 2);
	# count digrams
	for(my $i=0; $i+1<length($word); $i++) {
		my $digram = substr($word, $i, 2);
		if(exists($digrams{$digram})) {
			$digrams{$digram} = $digrams{$digram} + 1;
		}
		else {
			$digrams{$digram} = 1;
		}
	}
}

sub countTrigrams {
	my $word = shift;
	# ignore words shorter than three characters
	return if(length($word) < 3);
	# count trigrams
	for(my $i=0; $i+2<length($word); $i++) {
		my $trigram = substr($word, $i, 3);
		if(exists($trigrams{$trigram})) {
			$trigrams{$trigram} = $trigrams{$trigram} + 1;
		}
		else {
			$trigrams{$trigram} = 1;
		}
	}
}