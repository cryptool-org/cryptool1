#!/usr/bin/perl

use strict;
use warnings;
use Pod::Usage;
use Getopt::Long;

my $readme;
my $template;
my $outfile;
my $pattern = '__BODY__';

pod2usage(1)
	if !GetOptions(
		'i=s' => \$readme,
		't=s' => \$template,
		'o=s' => \$outfile,
		'p=s' => \$pattern
		);

pod2usage(1)
	if grep { !defined($_) } ($readme, $template, $outfile);





sub readfile { 
	local $/; 
	my $f = shift; open(F,"<$f") or die "open $f: $!\n";
        $f = <F>; close F; $f;
}

if (!-e $readme) {
	print STDERR "$0: can't find $readme; falling back to ";
	$readme =~ s{-..([./\\])}{-en$1}g;
	print STDERR "$readme.\n";
}

$_ = readfile($readme);

s{&}{\&amp;}g;
s{<}{\&lt;}g;
s{>}{\&gt;}g;
s{^( *)([.A-Z0-9]+)( +\.\.\.\.? +)(.*)$}{$1$2$3<a href="#s$2">$4</a>}gm;
s{^([.A-Z0-9]+\.) ([^.].*)}{<h2><a name="s$1">$1</a> $2</h2>}gm;
s{----*}{}g;
my $f = readfile($template);
$f =~ s{__BODY__}{$_};

print "Deleting $outfile...\n";
unlink($outfile);

open(F,">$outfile") or die "open $outfile: $!";
print F $f;
close(F);

if( -e $outfile ) {
    print "Creation of $outfile SUCCESSFUL!\n";
}
else {
    print "Creation of $outfile FAILED!\n";
}

__END__
=head1 NAME

readme.pl - htmlify text only readme and plug it into a HTML template

=head1 SYNOPSIS

readme.pl -t template -i readme -o outfile [-p pattern]

 Options:
   -t template	HTML template file containing pattern
   -i readme	the text only readme file
   -o outfile	ouput file
   -p pattern	the pattern (regex) to substitute in the HTML template
   		default: __BODY__

