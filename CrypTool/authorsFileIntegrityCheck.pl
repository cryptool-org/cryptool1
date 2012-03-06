# authorsFileIntegrityCheck.pl

#
# This script ensures integrity of the "authors.txt" file rolled out with CrypTool. It 
# is called implicitly at build time by Visual Studio.
#
# Upon execution, this script calculates the sha-1 hash value of the "authors.txt" file.
# Then it checks the "DlgAuthors.cpp" implementation file for the hard-coded hash value 
# that corresponds to the "authors.txt" file. If the two hash values differ, the old hash 
# value in "DlgAuthors.cpp" is replaced with the hash value that was just calculated.
#
# Florian Marchal, 10/08/2009, florian(at)marchal(dot)de
#

use strict;
use Digest::SHA1  qw(sha1_hex);

print "Checking integrity of \"authors.txt\" file...\n";

# this is a temporary variable
my @lineArray;
# this variable indicates if the hash value was replaced
my $replaced = 0;

# the authors.txt file
my $authorsTextFile = "../setup/template/authors.txt";

# open the authors.txt file (in binary mode)
open(FILE, $authorsTextFile) or die ("Opening $authorsTextFile: $!\n");
binmode(FILE);
my @lineArray = <FILE>;
close(FILE);

# the hash of the authors.txt file
my $authorsTextFileHash = sha1_hex(@lineArray);

# the authors dialog file
my $authorsDialogFile = "DlgAuthors.cpp";

# open the authors dialog file
open(FILE, $authorsDialogFile) or die ("Opening $authorsDialogFile: $!\n");
@lineArray = <FILE>;
foreach my $line(@lineArray) {
  if($line =~ m{ static \s+ const \s+ CString \s+ authorsFileHash \s+ = \s+ \" (.*) \" }xms) {
    print "EXPECTED HASH......: $authorsTextFileHash\n";
    print "FOUND HASH.........: $1\n";

    # replace the found hash with the expected hash
    if($1 ne $authorsTextFileHash) {
      $line =~ s/$1/$authorsTextFileHash/;
      print "HASH WAS SUCCESSFULLY REPLACED!\n";
      $replaced = 1;
    }
  }
}
close(FILE);

# exit if there was nothing to be replaced
if($replaced == 0) {
  exit(0);
}

# write the new dialog file (containing the new hash value)
open(FILE, ">$authorsDialogFile") or die ("Opening $authorsDialogFile $!\n");
foreach my $line(@lineArray) {
  print FILE $line;
}
close(FILE);
