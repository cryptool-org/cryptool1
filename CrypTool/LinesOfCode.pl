# !~/usr/local/bin/perl

# LinesOfCode.pl

use strict;
use File::Find;

# Directories to be included in source code search: (below "trunk")
my @subdirectories = (
    "aes",
    "aestool",
    "CrypTool",
    "dialoguesisters",
    "eccdemo",
    "libanalyse",
    "libec",
    "libVolRen",
    "NumberShark",
    "RijndaelAnimation"
);

# this is the root directory from where the search is started (deprecated)
my $directory = $ARGV[0] || "../.";


# EDIT THIS HASH TO ASSIGN DEFAULT VALUES FOR FILE TYPES TO LOOK FOR
my %fileTypes = (
    "C/C++ source code" => "h c cpp",
    "MFC resource code" => "rc",
    "Java source code" => "java",
    "HTML code" => "html hpp",
    "LaTex code" => "tex",
    "Text files" => "txt" 
);


# this hash stores the lines of code for each file, i.e. "sourcefile.cpp => 10 lines of code"
my %fileLOC = ( );
# this hash stores the lines of code for each file type, i.e. ".cpp => 2000 lines of code"
my %filesLOC = ( );
# this hash stores the number of files for each file type, i.e. ".cpp => 250 files"
my %fileTypeCount = ( );



#######################################
#######################################
# find the desired files...
find( \&findFiles, $directory );
# count lines of code for each file...
countLOC( );
# dump results...
dumpResult();
#######################################
#######################################



# callback function used to find specific files
sub findFiles() {
    # only find files with specific extension    
    foreach my $fileType ( keys %fileTypes ) {
        my @extensions = split ( " ", $fileTypes{ $fileType } );
        foreach my $extension ( @extensions ) {
            if( $File::Find::name =~ /\.$extension$/ ) {
                if ( not defined $fileLOC{$File::Find::name} ) {
		    # see whether we are in a valid sub directory
		    foreach my $subdirectory ( @subdirectories ) {
			if ( $File::Find::dir =~ m/$subdirectory/ ) {
			    # file found; store it for later processing
	                    $fileLOC{$File::Find::name} = 0;
        	            if ( not defined $fileTypeCount{$extension} ) {
	                        # file counter for this file type not yet created
                        	$fileTypeCount{$extension} = 0;
                    	    }
		            # increase counter for this file type
                            $fileTypeCount{$extension}++;

			}
		    }
                }
            }              
        }
    }
}

# function used to count the lines of code in all files that were found
sub countLOC() {
    # count lines of code for each file we found previously
    foreach my $key ( keys %fileLOC ) {
        open ( FILE, $key ) or die "cannot open $key: $!";
        my $loc = 0;
        while ( <FILE> ) {
            $loc++;
        }
        close FILE;
	# save lines of code for this file
        $fileLOC{$key} = $loc;
    }
}

# dumps the result to STDOUT
sub dumpResult() {
    foreach my $key ( keys %fileLOC ) {
        foreach my $fileType ( keys %fileTypes ) {
            my @extensions = split ( " ", $fileTypes{ $fileType } );
            foreach my $extension ( @extensions ) {
                if( $key =~ /.$extension$/ ) {
		    # add up all lines of code for a specific file type
                    $filesLOC{$fileType} += $fileLOC{$key};
                }
            }
        }
    }           

    # how many files of each file type were found?
    print "\nFILE SUMMARY\n";
    print "------------\n";
    foreach my $extension ( keys %fileTypeCount ) {
        print "$fileTypeCount{$extension} .$extension files\n";
    }

    # how many lines of code were found?
    print "\nLINES OF CODE SUMMARY\n";
    print "---------------------\n";

    foreach my $key ( keys %filesLOC ) {
        print "$key ($fileTypes{$key}): $filesLOC{$key} lines of code\n";
    }
     
    print "\nTOTAL: ";
    my $locTotal = 0;
    foreach my $key ( keys %filesLOC ) {
        $locTotal += $filesLOC{$key};
    }
    print "$locTotal lines of code\n\n";
}

__END__

=head1 NAME

LinesOfCode.pl - Count source lines of code for various file types and source folders

=head1 SYNOPSIS

TODO TODO TODO

LinesOfCode.pl -e extensions -f folders

 Options:
   -e extensions	a string of (file) extensions to search for
   -f folders		a string of folders to search in
