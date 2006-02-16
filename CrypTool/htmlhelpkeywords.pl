#!/usr/bin/perl -sn

# Any questions -> ask Jörg js@joergschneider.com

use strict;
use warnings;

our ($h,$sort,@sort);

BEGIN { 
	my %sv = map { $_ => 1 } qw(filename title keyword langkeyword);
	@sort = split(',',$sort) if $sort;
	if ($h || @ARGV == 0 || @sort < 1 || @sort > 2 || !$sv{$sort[0]} || $sort[1] && !$sv{$sort[1]}) {
		print STDERR <<EOF;
usage: $0 -sort=... *.htm*
	-sort=filename
	-sort=filename,keyword
	-sort=title
	-sort=title,keyword
	-sort=keyword
	-sort=keyword,title
	-sort=keyword,filename
	-sort=filename,langkeyword
	-sort=langkeyword,filename
EOF
		exit 1;
	}
	@ARGV = map { m{[*?]} ? glob($_) : $_ } @ARGV;
}

our %kwfile; # keyword => [filename1, filename2, ...]
our %filekw; # filename => [kw1, kw2, ...]
our %filetitle; # filename => title

my $filename = $ARGV;
if (m{param\s+name="keyword"\s+value="(.*?)">}i) {
	my $kw = $1;
	if (@sort > 1 && $sort[1] eq 'langkeyword' && $ARGV =~ m{_(..)[/\\]}) {
		$kw = "$1:$kw";
		$filename =~ s{.*[/\\]}{};
	}
	push @{$kwfile{$kw}}, $filename;
	push @{$filekw{$filename}}, $kw;
	#print "Keyword: $ARGV -> $kw\n";
} elsif (m{<title>(.*?)</title>}i) {
	my $title = $1;
	if (@sort > 1 && $sort[1] eq 'langkeyword' && $ARGV =~ m{_(..)[/\\]}) {
		$filename =~ s{.*[/\\]}{};
	}
	$filetitle{$filename} = $title;
	#print "Title: $ARGV -> $title\n";
}

END {
	if ($sort[0] =~ m{^filename|title$}) {
		my @files = ($sort[0] eq 'title') 
			? sort { $filetitle{$a} cmp $filetitle{$b} } keys %filetitle
			: sort keys %filetitle;
		foreach my $file (@files) {
			print $sort[0] eq 'title'
				? "$filetitle{$file} ($file)\n"
				: "$file: $filetitle{$file}\n";
			if (@sort > 1) {
				print map { "\t$_\n" } 
					sort @{$filekw{$file}}
						if $filekw{$file};
			}
		} 
	}
	if ($sort[0] eq 'keyword') {
		foreach my $kw (sort keys %kwfile) {
			print "$kw\n";
			if (@sort > 1 && $sort[1] =~ m{^filename|title$}) {
				my @files = ($sort[1] eq 'title') 
					? sort { $filetitle{$a} cmp $filetitle{$b} } @{$kwfile{$kw}}
					: sort @{$kwfile{$kw}};
				print map { "\t$filetitle{$_} ($_)\n" } @files;
			}
		}
	}
}
