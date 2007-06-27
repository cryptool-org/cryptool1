# This script checks the CrypTool file <resource.h> for duplicate resource IDs.
# It is invoked during the CrypTool build process. If duplicate IDs are found, 
# a warning is print to STDOUT and the problems are fixed automatically.

# usage: perl CheckForResourceIDDuplicates.pl resource.h newresource.h

# Florian Marchal, 27.06.2007

use strict;

my $resourceFileName = $ARGV[0] || "resource.h";
my $newResourceFileName = $ARGV[1] || "newresource.h";
my %cleanResourceIDs = ();
my %duplicateResourceIDs = ();
my $numberOfDuplicatesFound = 0;


open FILE, "<$resourceFileName" or die "open $resourceFileName: $!\n";

foreach (<FILE>) {
    # check whether there's a valid resource ID pattern...
    if( m{^\s*#define\s+([a-zA-Z0-9]+[a-zA-Z0-9\_]+)\s+([0-9]+)\s*$} ) {
        # check whether the resource ID is already in use...
        if( exists $cleanResourceIDs{$2} ) {
            print "Duplicate resource ID: $2\n";
            $duplicateResourceIDs{$1} = $2;
            $numberOfDuplicatesFound++;
        }
        else {
            $cleanResourceIDs{$2} = $1;
        }       
    }
}

close FILE;

if ( $numberOfDuplicatesFound != 0 ) {
    print "WARNING: $numberOfDuplicatesFound duplicates found!\n";
    print "  Assigning new resource IDs...\n";

    foreach my $key ( keys %duplicateResourceIDs ) {
        my $id = 1;
        while ( exists $cleanResourceIDs{$id} ) {
           $id++;
        }
        $cleanResourceIDs{$id} = $key;
    } 

    print "writing new resource file <newresource.h>...\n";

    

    open NEWRESOURCEFILE, ">$newResourceFileName" or die "open $newResourceFileName: $!\n";

    foreach my $key ( keys %cleanResourceIDs ) {
        print NEWRESOURCEFILE "#define $cleanResourceIDs{$key} $key\n";
    }

    close NEWRESOURCEFILE;
}
else {
    print "Resource file $resourceFileName is looking good...\n";
}