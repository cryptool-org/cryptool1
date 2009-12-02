# !~/usr/local/bin/perl

# LinesOfCode.pl

use strict;
use File::Find;
use Pod::Usage;

# Directories to be included in source code search: (below "trunk")
my @subdirectories = (
    'aes',
    'AES_flow_visualisation',
    'aestool',
    'ChallengeResponse',
    'CrypTool',
    'dialoguesisters',
    'eccdemo',
    'libanalyse',
    'libec',
    'libVolRen',
    'NumberShark',
    'Rijndael-Animation',
    'smimedemo',
    'script',
    'setup/template(-..)?',
);

my $verbose;
if ($ARGV[0] && $ARGV[0] eq '-h') {
	pod2usage();
	exit;
}
if ($ARGV[0] && $ARGV[0] eq '-v') {
	shift;
	$verbose = 1;
}

# this is the root directory from where the search is started (deprecated)
my $directory = $ARGV[0] || "../.";


# EDIT THIS HASH TO ASSIGN DEFAULT VALUES FOR FILE TYPES TO LOOK FOR
my @fileTypes = (
    "MFC resource code" => "rc",
    "C/C++ source code" => "c cpp h",
    "Java source code" => "java",
    "Perl code" => "pl",
    "HTML code" => "html hpp",
    "Text files" => "txt",
    "LaTeX code" => "tex",
    "Sage code" => "sage",
);
my %fileTypes = @fileTypes; 
my @fileTypesKeys = @fileTypes[grep { $_ % 2 == 0 } (0 .. $#fileTypes)];
@fileTypes = undef;

# this hash stores the lines of code for each file, i.e. "sourcefile.cpp => 10 lines of code"
my %fileLOC = ( );
# this hash stores the lines of code for each file type, i.e. ".cpp => 2000 lines of code"
my %filesLOC = ( );
# this hash stores the number of files for each file type, i.e. ".cpp => 250 files"
my %fileTypeCount = ( );
my @fileTypeCountKeys = ( map { split(/ /) } @fileTypes{ @fileTypesKeys });



#######################################
#######################################
chdir $directory or die "cannot chdir to $directory";
# find the desired files...
find( \&findFiles, '.' );
# count lines of code for each file...
countLOC( );
# dump results...
dumpResult();
#######################################
#######################################



# callback function used to find specific files
sub findFiles() {
    # only find files with specific extension    
    foreach my $fileType ( @fileTypesKeys ) {
        my @extensions = split ( " ", $fileTypes{ $fileType } );
        foreach my $extension ( @extensions ) {
            if( $File::Find::name =~ /\.$extension$/ ) {
                if ( not defined $fileLOC{$File::Find::name} ) {
		    # see whether we are in a valid sub directory
		    foreach my $subdirectory ( @subdirectories ) {
			if ( $File::Find::dir =~ m/^\.\/$subdirectory(\/|$)/ ) {
			    # file found; store it for later processing
			    die "file $File::Find::name counted more than once!" 
				if defined $fileLOC{$File::Find::name};
	                    $fileLOC{$File::Find::name} = 0;
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
    foreach my $key ( sort keys %fileLOC ) {
	print "$fileLOC{$key}\t$key\n" if $verbose;
        foreach my $fileType ( @fileTypesKeys ) {
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
    my $fileTotal = 0;
    foreach my $extension ( @fileTypeCountKeys ) {
	$fileTotal += $fileTypeCount{$extension};
        printf "%7d %s\n", $fileTypeCount{$extension}, ".$extension files"
		if $fileTypeCount{$extension};
    }
    printf "%7d TOTAL\n", $fileTotal;

    # how many lines of code were found?
    print "\nLINES OF CODE SUMMARY\n";
    print "---------------------\n";

    my $locTotal = 0;
    foreach my $key ( @fileTypesKeys ) {
        $locTotal += $filesLOC{$key};
        printf "%7d %s\n", $filesLOC{$key}, "$key ($fileTypes{$key})";
    }
    printf "%7d %s\n\n", $locTotal, "TOTAL";
}

__END__

=head1 NAME

LinesOfCode.pl - Count source lines of code for various file types and source folders

=head1 SYNOPSIS

LinesOfCode.pl [-h|-v] ...\trunk

-h	usage help

-v	verbose, i.e. output all files with their 
