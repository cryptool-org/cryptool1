# usage perl -p subst.pl marker src dst...
# subtitute in dst... each occurence of marker with the content of file src
BEGIN {
	$marker = shift @ARGV;
	my $file = shift @ARGV;
	local $/;
	undef $/;
	open F,"<$file" or die "open $file: $!";
	$content = <F>;
	close F;
}

s/$marker/$content/g;
