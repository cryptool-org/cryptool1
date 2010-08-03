#!/usr/bin/perl
use strict;
use warnings;

my $clang = '';
my $sort;
if (@ARGV && $ARGV[0] eq '-s') {
	shift;
	$sort = 1;
}
my $lang = lc(shift) or 
	die "Extract text strings from *.rc file for spell checking\n\nusage:\nrcspformat.pl [-s] german|english|polish|spanish|serbian CrypTool.rc >CrypTool.txt\n-s\tsort strings alphabetically\n";
my %s = ();

my @l = ();
while (<>) {
	$clang = lc($1) if m{^LANGUAGE +LANG_(\w+)};
	next if $clang ne $lang;
	next if m{^(#|//|FONT|STYLE)};
	next if m{^\w+\s+(BITMAP|GIF|CURSOR|ICON)\s+};
	s{&}{}g;
	s{\\[rn]}{ }g;
	my @s =  m{"(?:""|[^"])*"}g;
	@s = grep { !$s{$_}; } @s;
	next if @s == 0;
	foreach (@s) {
		$s{$_}++;
	}
	push @l, @s;
}
@l = sort @l if $sort;
foreach (@l) {
	print $_,"\n";
}
