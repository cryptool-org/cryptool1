use strict;
use warnings;
use IO::File;
use File::Find;
use Digest::MD5;
use Digest::SHA1;

my $digestalg = shift || die "usage: $0 MD5|SHA-1 directory ...";
my $ctx = 
	$digestalg =~ m{md5}i ? Digest::MD5->new() :
	$digestalg =~ m{sha-?1}i ? Digest::SHA1->new() :
	die "can't find $digestalg, use md5 or sha1\n";

find({ wanted => \&process }, @ARGV);

sub process {
	return if -d $_;
	my $fh;
	open $fh,"<",$_ or die "open $File::Find::name: $!\n";
	binmode $fh;
	$ctx->reset();
	$ctx->addfile($fh);
	$File::Find::name =~ tr{\\}{/};
	$File::Find::name =~ s{^\./}{};
	print $ctx->hexdigest()," *$File::Find::name\n";

}
