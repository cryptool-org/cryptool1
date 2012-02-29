# updateBuildTimeInAboutDialog.pl

#
# Essentially, this script emulates a 'unix touch' on 'DlgAbout.cpp'. As we require 
# Perl to build CrypTool anyway, this solution makes life for future developers as 
# simple as possible.
#
# The file 'DlgAbout.cpp' needs to be explicitly recompiled for the about dialog to 
# show the correct CrypTool build date. In order to always have an up-to-date build 
# time, we call this script from within Visual Studio via a custom build step. The 
# sole drawback: compilation time is slightly increased.
#
# flomar, 02/29/2012
#

use strict;

# this is a temporary variable
my @lineArray;

# the about dialog file
my $aboutDialogFile = "DlgAbout.cpp";

# open the about dialog file
open(FILE, $aboutDialogFile) or die ("Opening $aboutDialogFile: $!\n");
@lineArray = <FILE>;
close(FILE);

# re-write the about dialog file
open(FILE, ">$aboutDialogFile") or die ("Opening $aboutDialogFile $!\n");
foreach my $line(@lineArray) {
  print FILE $line;
}
close(FILE);
