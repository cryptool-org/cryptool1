# CheckHelp.pl
#
# This script does a variety of consistency checks for the online help 
# of the CrypTool project. 
#
# Initially, the script locates all existing help files within the help 
# directory and parses the CrypTool resource file for resource identifiers. 
# Afterwards, this information is processed in a single consistency check.
#
# INVOCATION
#
#   perl CheckHelp.pl [LANGUAGE] [HELP DIRECTORY] [[DEBUG]] [[RESOLVE]]
#
# EXAMPLES
#
#   perl CheckHelp.pl GERMAN hlp_de
#   perl CheckHelp.pl ENGLISH hlp_en DEBUG
#   perl CheckHelp.pl POLISH hlp_pl DEBUG RESOLVE
#
# DETAILED DESCRIPTION
#
#   The first parameter specifies the language for wich the help is supposed 
#   to be checked. As of now, valid values are GERMAN, ENGLISH and POLISH. 
#   There might be further languages possible in future releases.
#
#   The second parameter specifies the help directory in which the script 
#   is searching for help files. Valid values are hlp_de, hlp_en and hlp_pl, 
#   according to the supported languages.
#
#   The third parameter is optional. If the debug parameter is passed to 
#   the script, you get a much more detailed output in comparison to what 
#   is summarized in non-debug mode. By default we are in non-debug mode. 
#   Since this script is integrated in the build process of CrypTool, 
#   some programmers not directly working with the online help might 
#   find the output annoying.
#
#   The fourth parameter is optional. If the resolve parameter is passed 
#   to the script, conflicts due to missing menu or dialog identifiers are 
#   resolved automatically: missing help files are created, and their names 
#   are registered with the corresponding help project file.
#
# 
# Florian Marchal, 02/22/2008 (florian@marchal.de)
# 
#
# ADDITIONS
#
#   03/02/2008: Integrated a check for Wikipedia links. If a link to 
#               Wikipedia is detected, the script checks if it points 
#               to the correct language. As of now, only the value pairs 
#               (GERMAN, de), (ENGLISH, en) and (POLISH, pl) are working.
#               In case the link points to the wrong language, a warning 
#               is dumped.
#


use strict;
use File::Find;
use HTML::LinkExtor;

# variables
my %menuIdentifiers = ();
my %dialogIdentifiers = ();
my %missingMenuIdentifiers = ();
my %missingDialogIdentifiers = ();
my %aliasedIdentifiers = ();
my %helpFiles = ();
my %helpFilesHTML = ();
my $helpDirectory = ();
my %possibleLinks = ();

# some more variables
my $language = $ARGV[0] || 0;
my $helpDirectory = $ARGV[1] || 0;
my $debug = $ARGV[2] || 0;
my $resourceFile = "CrypTool.rc";
my $aliasFile = "CrypTool_Alias.h";
my $resolve = $ARGV[3] || 0;

# remove trailing slash from help directory, if necessary
$helpDirectory =~ s/\/$//;

# collect all help files in the help file directory
collectHelpFiles($helpDirectory);

# find out which identifiers should be ignored since they are aliased
collectAliasedIdentifiers($helpDirectory);

# collect all menu identifiers in the resource file
collectMenuIdentifiers();
# collect all dialog identifiers in the resource file
collectDialogIdentifiers();

# run the consistency check
runConsistencyCheck($language, $helpDirectory);

# resolve conflicts (if desired)
resolveMissingHTMLFiles() if($resolve);



#
# ***************************************************************************
# *** SUB FUNCTIONS *********************************************************
# ***************************************************************************
#

# This callback function finds all kinds of help files
sub callbackFindHelpFiles() {
   if("\L$File::Find::name" =~ /\.html$/ ||
      "\L$File::Find::name" =~ /\.htm$/ ||
      "\L$File::Find::name" =~ /\.gif$/ ||
      "\L$File::Find::name" =~ /\.jpg$/ || 
      "\L$File::Find::name" =~ /\.png$/ ||
      "\L$File::Find::name" =~ /\.css$/ || 
      "\L$File::Find::name" =~ /\.txt$/ ||
      "\L$File::Find::name" =~ /\.pdf$/ ||
      "\L$File::Find::name" =~ /\.js$/ ) {
       my $lowercasename = "\L$File::Find::name";
       $lowercasename =~ s/\\/\//g; # windows?
       # add file to regular help file pool
       ${$helpFiles{$helpDirectory}}{"$lowercasename"} = "FOUND";
       # add file to .html help file pool, if necessary
       if($lowercasename =~ /\.html$/) {
           ${$helpFilesHTML{$helpDirectory}}{"$lowercasename"} = "FOUND";
       }
   }
}

# This function collects all help files for the 
# help directory given as parameter (i.e. "hlp_de")
sub collectHelpFiles() {
   $helpDirectory = shift;
   find(\&callbackFindHelpFiles, $helpDirectory);
}

# This function is used to collect all identifiers that should 
# be ignored since they are aliased by CrypTool; it takes the 
# directory as parameter in which to search for the alias file
sub collectAliasedIdentifiers() {
   my $helpDirectory = shift;
   my $aliasFile = "$helpDirectory/$aliasFile";
   open(FILE, $aliasFile) or die ("Opening $aliasFile: $!\n");
   my @fileArray = <FILE>;
   foreach my $line(@fileArray) {
       if($line =~ /H([a-zA-Z0-9_]+)\s*=\s*([a-zA-Z0-9_\-])/) {
           $aliasedIdentifiers{"\L$1"} = "\L$2";  
       }
   }
   close(FILE);
}

# This function collects all menu identifiers for
# the language given as parameter (i.e. "GERMAN")
sub collectMenuIdentifiers() {
   my $ignore = 1;
   my $found = 0;
   my $menu = 0;
   my $depth = 0;
   open(FILE, $resourceFile) or die ("Opening $resourceFile: $!\n");
   my @fileArray = <FILE>;
   foreach my $line(@fileArray) {
       if($line =~ /^LANGUAGE\s+LANG_$language,/) {
         $ignore = 0;
         $found = 1;
         next;
       }
       if($ignore == 0) {
           if($line =~ /^LANGUAGE\s+LANG_/) {  
               $ignore = 1;
               next;
           }
           if($line =~ /^IDR_MAINFRAME\s+MENU\s+$/) {
               $menu = 1;
           }
           if($line =~ /^END\s+$/ && $menu == 1 && $depth == 0) {
               $menu = 0;
           }
           # at this point we are within the desired menu; now try to 
           # identify all menu item identifiers that need a help file
           if($line =~ /MENUITEM\s+[^,]+,\s+([a-zA-Z0-9_]+)/) {
               my $identifier = $1;
               # ignore identifiers that were aliased, but dump a warning
               if(defined $aliasedIdentifiers{"\L$identifier"}) {
                   print "  WARNING: menu identifier $identifier was aliased, hence it is ignored\n" if($debug);
                   next;
               }
               # ignore identifiers that are connected to the system, but dump a warning
               if("\L$identifier" =~ m{ \A \s* afx }xms) {
                   print "  WARNING: menu identifier $identifier seems to be connected to the system, hence it is ignored\n" if($debug);
                   next;
               }
               push(@{$menuIdentifiers{$language}}, $identifier);
           }
       }
   }
   if($found == 0) {
       print "  WARNING: menu identifiers for language \"$language\" could not be found\n" if($debug);
   }
   close(FILE);
}

# This function collects all dialog identifiers for 
# the language given as parameter (i.e. "GERMAN") 
sub collectDialogIdentifiers() {
   my $ignore = 1;
   my $found = 0;
   open(FILE, $resourceFile) or die ("Opening $resourceFile: $!\n");
   my @fileArray = <FILE>;
   foreach my $line(@fileArray) {
       if($line =~ /^LANGUAGE\s+LANG_$language,/) {
         $ignore = 0;
         $found = 1;
         next;
       }
       if($ignore == 0) {
           if($line =~ /^LANGUAGE\s+LANG_/) {
               $ignore = 1;
               next;
           } 
           if($line =~ /^([a-zA-Z0-9_]+)\s+DIALOG/) {
               my $identifier = $1;
               # ignore identifiers that were aliased, but dump a warning
               if(defined $aliasedIdentifiers{"\L$identifier"}) {
                   print "  WARNING: dialog identifier $identifier was aliased, hence it is ignored\n" if ($debug);
                   next;
               }
               # ignore identifiers that are connected to the system, but dump a warning
               if("\L$identifier" =~ m{ \A \s* afx }xms) {
                   print "  WARNING: menu identifier $identifier seems to be connected to the system, hence it is ignored\n" if($debug);
                   next;
               }
               push(@{$dialogIdentifiers{$language}}, $identifier);
           }
       }
   }
   if($found == 0) {
       print "  WARNING: dialog identifiers for language \"$language\" could not be found\n" if($debug);
   }
   close(FILE);
}

# This function checks if there is a valid .html help file for 
# each identifier found in the resource file; furthermore, this 
# function checks all .html help files for dead links; the first 
# parameter is the language, the second parameter is the help 
# directory (i.e. "GERMAN" and "hlp_de")
sub runConsistencyCheck() {
   my $language = shift;
   my $directory = shift;

   my $numberOfMissingDialogIdentifiers = 0;
   my $numberOfMissingMenuIdentifiers = 0;
   my $numberOfDeadLinks = 0;

   if(not defined $helpFilesHTML{$directory}) {
       die "ABORTING: there seem to be no .html help files in directory $directory\n";
   }

   my %hashHTMLHelpFiles = %{$helpFilesHTML{$directory}};
   
   # check help files for menu identifiers
   if(defined $menuIdentifiers{$language}) {
       my @arrayMenuIdentifiers = @{$menuIdentifiers{$language}};
       print "Checking help files for menu items (language \"$language\")\n" if($debug);
       foreach(@arrayMenuIdentifiers) {
           my $identifier = $_;
           my $filename = "\L$helpDirectory/h$identifier.html";
           if(not defined $hashHTMLHelpFiles{$filename}) {
               # make sure we haven't already marked this identifier as missing; this small fix 
               # is needed due to the fact that the CrypTool resource file contains multiple menus
               if(not defined $missingMenuIdentifiers{$filename}) {
                   print "  WARNING: $filename seems to be missing (menu identifier is $identifier)\n" if($debug);
                   $numberOfMissingMenuIdentifiers++;
                   $missingMenuIdentifiers{"\Lh$identifier.html"} = "FOUND";
               }
           }
       }
   }

   # check help files for dialog identifiers
   if(defined $dialogIdentifiers{$language}) {
       my @arrayDialogIdentifiers = @{$dialogIdentifiers{$language}};
       print "Checking help files for dialogs (language \"$language\")\n" if($debug);
       foreach(@arrayDialogIdentifiers) {
           my $identifier = $_;
           my $filename = "\L$helpDirectory/h$identifier.html";
           if(not defined $hashHTMLHelpFiles{$filename}) {
               print "  WARNING: $filename seems to be missing (dialog identifier is $identifier)\n" if($debug);
               $numberOfMissingDialogIdentifiers++;
               $missingDialogIdentifiers{"\Lh$identifier.html"} = "FOUND";
           }
       }
   }

   # check for (possibly) obsolete help files
   # TODO...    

   # check for dead links
   if(defined $helpFiles{$directory}) {
       print "Checking help files for dead links (language \"$language\")\n" if($debug);
       my $extractor = HTML::LinkExtor->new();
       foreach my $file (keys %{$helpFiles{$directory}})
       {
           if($file =~ /\.html$/) { 
               $file = "$file";
               $extractor->parse_file($file);
               for ($extractor->links() ) {
                   my ($tag, $type, $linkname) = @{$_};
                   $linkname = "\L$linkname";
                   # special Wikipedia check: 
                   # print warning if there's a link to Wikipedia in the wrong language 
                   if($linkname =~ /^http\:\/\/([a-z]+)\.wikipedia\.org/) {
				       my $languageIdentifier = $1;
				       if(($language eq "GERMAN" && $languageIdentifier ne "de") ||
				          ($language eq "ENGLISH" && $languageIdentifier ne "en") ||
				          ($language eq "POLISH" && $languageIdentifier ne "pl") ) {
				           print "  WARNING: Wikipedia link $linkname points to wrong language (referenced in file $file)\n" if($debug);         
				       }			       
                   }
                   # omit links beginning with '#'
                   next if($linkname =~ /^#/);
                   # omit external links beginning with 'http'
                   next if($linkname =~ /^http/);
                   # omit external links beginning with 'mailto'
                   next if($linkname =~ /^mailto/);
                   # discard the part of links that contain internal references ('#')
                   if($linkname =~ /(.*)#.*/) {
                       $linkname = $1;
                   } 
                   # build full link name (with full path)
                   $linkname = "\L$helpDirectory/$linkname";
                   $linkname =~ s/\\/\//g; # windows?
                   $possibleLinks{"$linkname"} = "$file";
               }
           }
       }
   
       foreach my $possibleLink (keys %possibleLinks) {
           if(not exists ${helpFiles{$helpDirectory}}{"$possibleLink"}) {
               print "  WARNING: file $possibleLink is missing (referenced in $possibleLinks{$possibleLink})\n" if($debug);
               $numberOfDeadLinks++;
           }
       }
   }

   print "\nSUMMARY (language \"$language\")\n";
   print "- $numberOfMissingDialogIdentifiers missing help files for dialog identifiers\n";
   print "- $numberOfMissingMenuIdentifiers missing help files for menu identifiers\n";
   print "- $numberOfDeadLinks dead links\n";
   print "\n(run CheckHelp.pl manually in debug mode for further details)\n\n" if(not $debug);
}

# This function modifies the project file so that it contains all necessary file names
sub resolveMissingHTMLFiles {

    # first off, we want to create dummy HTML files if necessary; we do that for all 
    # files in %missingMenuIdentifiers and %missingDialogIdentifiers 
    my %newlyCreatedFiles = ();
    foreach my $filename (sort keys %missingMenuIdentifiers) {
        my $content = createDummyHTMLContent($filename);
        my $fullPath = "\L$helpDirectory/$filename";
        open(FILE, ">$fullPath") or die("Could not open $fullPath: $!\n");
        print FILE $content;
        close(FILE);
        $newlyCreatedFiles{$filename} = "CREATED";
    }
    foreach my $filename (keys %missingDialogIdentifiers) {
        my $content = createDummyHTMLContent($filename);
        my $fullPath = "\L$helpDirectory/$filename";
        open(FILE, ">$fullPath") or die("Could not open $fullPath: $!\n");
        print FILE $content;
        close(FILE);
        $newlyCreatedFiles{$filename} = "CREATED";
    }

    # read the project file (extract all existing files, one file name per line)
    my $projectFilename = "\L$helpDirectory/CrypTool.hhp";
    open(FILE, "<$projectFilename") or die("Could not open $projectFilename: $!\n");
    my @array = <FILE>;
    close(FILE);

    # find the "[FILES]" section (so we know what we keep and what we throw away)
    my $currentPosition = 0;
    my $filesSectionStart = undef;
    my $filesSectionEnd = undef;
    foreach my $line (@array) {
        if($line =~ m{ \A \s* \[FILES\] }xms && not defined $filesSectionStart && not defined $filesSectionEnd) {
            $filesSectionStart = $currentPosition;
            next;
        }
        if($line =~ m{ \A \s* \[ \w+ \] }xms && defined $filesSectionStart && not defined $filesSectionEnd) {
            $filesSectionEnd = $currentPosition;
            next;
        }
        $currentPosition++;
    }

    # extract project file names (one file name per line)
    $filesSectionStart++;
    my @projectFilenames = @array[$filesSectionStart..$filesSectionEnd];

    # we transform these names into a hash because we don't want duplicates
    my %projectFilenames = ();
    foreach my $filename (@projectFilenames) {
        chomp($filename);
        $projectFilenames{"\L$filename"} = "TRANSFORMED";
    }

    # now we add the files from %newlyCreatedFiles to %projectFilenames
    foreach my $filename (keys %newlyCreatedFiles) {
        chomp($filename);
        $projectFilenames{"\L$filename"} = "TRANSFORMED";
    }

    # we have everything in place now: construct the new project file
    my @linesProjectFile;  
    $filesSectionStart--; 
 
    push @linesProjectFile, @array[0..$filesSectionStart];

    foreach my $line (sort keys %projectFilenames) {
        push @linesProjectFile, "$line\n";
    }

    my $arrayEnd = @array;
    push @linesProjectFile, @array[$filesSectionEnd..$arrayEnd];

    # write the new project file
    open(FILE, ">$projectFilename") or die("Could not open $projectFilename: $!\n");
    foreach my $line (@linesProjectFile) {
        print FILE "$line";
    }
    close(FILE);
}

# This function returns the content of a dummy HTML help file;
# it is used if there's no help file yet for a specific help 
# identifier (dialogs and menu items)
sub createDummyHTMLContent {
   my $filename = shift;

   my $title = undef;
   my $heading = undef;
   my $body = undef;

   # we consider "GERMAN" as the sole special case, by default we go with "ENGLISH"
   if($language eq "GERMAN") {
       $title = "HTML-Datei nicht verfügbar";
       $heading = "HTML-Datei nicht verfügbar";
       $body = "Leider ist die HTML-Datei <b>$filename</b> nicht verfügbar.";       
   }
   else {
       $title = "HTML file not available";
       $heading = "HTML file not available";
       $body = "Unfortunately, the HTML file <b>$filename</b> is not available.";
   }

   my $content = "";

   # create the default dummy structure
   $content .= "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 3.2 Final//EN\">\n";
   $content .= "<HTML>\n";
   $content .= "<HEAD>\n";
   $content .= "<META HTTP-EQUIV=\"Content-Type\" Content=\"text/html; charset=Windows-1252\">\n";
   $content .= "<TITLE>$title</TITLE>\n";
   $content .= "<link rel=\"stylesheet\" type=\"text/css\" href=\"CrypTool_Help.css\">\n";
   $content .= "</HEAD>\n";
   $content .= "\n";
   $content .= "<!-- multiple keywords for CrypTool HTML help index -->\n";
   $content .= "<OBJECT TYPE=\"application/x-oleobject\" CLASSID=\"clsid:1e2a7bd0-dab9-11d0-b93a-00c04fc99f9e\" VIEWASTEXT ID=\"Object1\">\n";
   $content .= "<!-- <PARAM NAME=\"Keyword\" VALUE=\"CRYPTOOLONLINEHELPKEYWORD\"> -->\n";
   $content .= "</OBJECT>\n";
   $content .= "\n";
   $content .= "<BODY>\n";
   $content .= "\n";
   $content .= "<h3>$heading</h3>\n";
   $content .= "\n";
   $content .= "<P>$body</P>\n";
   $content .= "\n";
   $content .= "<!-- TODO/FIXME: remove this comment if all the dummy content is replaced -->";
   $content .= "\n";
   $content .= "</BODY>\n";
   $content .= "</HTML>\n";

   return $content;
}