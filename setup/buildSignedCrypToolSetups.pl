# buildSignedCrypToolSetups.pl

#
# Please define all required paths and values (see "ATTENTION" markers below) 
# before executing this script. All other input for the build configuration 
# is gathered from STDIN after executing this script. You can press ENTER 
# three times to go with the default build configuration.
#
# flomar, May 2017
#

use strict;
use Cwd qw/abs_path/;
use Term::ReadKey;
use Win32::Process;

my $absoluteScriptPath = getAbsoluteScriptPath();

# ATTENTION: this path must point to the VS2008 "devenv.exe"
my $devenvPath = "C:\\Program Files (x86)\\Microsoft Visual Studio 9.0\\Common7\\IDE\\devenv.exe";
# ATTENTION: this path must point to the Windows "signtool.exe"
my $signtoolPath = "C:\\Program Files\\Microsoft SDKs\\Windows\\v6.0A\\Bin\\signtool.exe";
# ATTENTION: this path must point to your #PKCS12 certificate file; 
# you can either define an absolute path or a relative one using 
# the following pattern: $absoluteScriptPath . "mycert.pfx"
my $certificateFilename = undef;
# ATTENTION: this value must contain the certificate password
my $certificatePassword = undef;

my @supportedLanguages = ( "de", "en", "es", "fr", "pl", "rs" );

my $configuration = undef;
while(not defined $configuration) {
	print("\n");
	$configuration = requestConfiguration();
	print("\n");
}
buildCrypTool();
createCrypToolSetupDirectories();
signCrypToolSetupDirectories() if($configuration->{"SIGN"} == 1);
createCrypToolSetupExecutables();
signCrypToolSetupExecutables() if($configuration->{"SIGN"} == 1);

sub getAbsoluteScriptPath() {
	my $file = $0;
	my $path = abs_path($0);
	if($path =~ m/(.*)$file/g) {
		return $1;
	}
	return "";
}

sub printScriptName() {
	print("$0\n");
	print("\n");
}

sub requestConfiguration() {
	my %configuration;
	$configuration{"LANGUAGES"} = requestLanguageConfiguration();
	return undef if(not defined $configuration{"LANGUAGES"});
	$configuration{"REBUILD"} = requestRebuildConfiguration();
	return undef if(not defined $configuration{"REBUILD"});
	$configuration{"SIGN"} = requestSignConfiguration();
	return undef if(not defined $configuration{"SIGN"});
	return \%configuration;
}

sub requestLanguageConfiguration() {
	print("LANGUAGES.....[ ");
	foreach my $language (@supportedLanguages) {
		print("$language ");
	}
	print("]: ");
	chomp(my $input = <STDIN>);
	$input =~ s/^\s+|\s+$//g;
	if(length($input) == 0) {
		return \@supportedLanguages;
	}
	my @languages = ( );
	my @inputLanguages = split(" ", $input);
	foreach my $inputLanguage (@inputLanguages) {
		$inputLanguage =~ s/^\s+|\s+$//g;
		if(grep(/^$inputLanguage$/, @supportedLanguages)) {
			push(@languages, $inputLanguage);
		}
	}
	if(scalar(@languages) > 0) {
		return \@languages;
	}
	return undef;
}

sub requestRebuildConfiguration() {
	print("REBUILD.......[ yes ]: ");
	chomp(my $input = <STDIN>);
	$input =~ s/^\s+|\s+$//g;
	if(length($input) == 0) {
		return 1;
	}
	if(lc($input) eq "y" or lc($input) eq "yes") {
		return 1;
	}
	return 0;
}

sub requestSignConfiguration() {
	print("SIGN..........[ yes ]: ");
	chomp(my $input = <STDIN>);
	$input =~ s/^\s+|\s+$//g;
	if(length($input) == 0) {
		return 1;
	}
	if(lc($input) eq "y" or lc($input) eq "yes") {
		return 1;
	}
	return 0;
}

sub buildCrypTool() {
	my @filesToBeTouched = ( $absoluteScriptPath . "..\\CrypTool\\CrypTool.rc", $absoluteScriptPath . "..\\CrypTool\\CrypToolApp.cpp", $absoluteScriptPath . "..\\CrypTool\\DlgAbout.cpp" );
	foreach my $fileToBeTouched (@filesToBeTouched) {
		utime(undef, undef, $fileToBeTouched);
	}
	my $solutionPath = $absoluteScriptPath . "..\\CrypTool\\CrypTool-VS2008.sln";
	my $buildMode = $configuration->{"REBUILD"} == 0 ? "/Build" : "/Rebuild";
	foreach my $language (@{$configuration->{"LANGUAGES"}}) {
		print("Building CrypTool_$language...\n");
		my $process = undef;
		Win32::Process::Create($process, $devenvPath, "devenv $solutionPath $buildMode Release_$language", 1, Win32::Process::CREATE_NO_WINDOW(), ".") or print Win32::FormatMessage(Win32::GetLastError());
		$process->Wait(INFINITE);
	}
	print("\n");
}

sub createCrypToolSetupDirectories() {
	my $setupPath = $absoluteScriptPath . "..\\setup";
	my $batchPath = $absoluteScriptPath . "..\\setup\\createsetupdir1lang.bat";
	foreach my $language (@{$configuration->{"LANGUAGES"}}) {
		print("Creating CrypTool_$language setup directory...\n");
		my $process = undef;
		Win32::Process::Create($process, $batchPath, "createsetupdir1lang $language", 1, Win32::Process::CREATE_NO_WINDOW(), $setupPath) or print Win32::FormatMessage(Win32::GetLastError());
		$process->Wait(INFINITE);
	}
	print("\n");
}

sub signCrypToolSetupDirectories() {
	foreach my $language (@{$configuration->{"LANGUAGES"}}) {
		print("Signing CrypTool_$language setup directory...\n");
		my $filesToBeSigned = getFilesToBeSigned($language);
		foreach my $fileToBeSigned (@{$filesToBeSigned}) {
			my $process = undef;
			Win32::Process::Create($process, $signtoolPath, "signtool sign /f $certificateFilename /t http://timestamp.verisign.com/scripts/timstamp.dll /p $certificatePassword $fileToBeSigned", 1, Win32::Process::CREATE_NO_WINDOW(), ".") or print Win32::FormatMessage(Win32::GetLastError());
			$process->Wait(INFINITE);
		}
	}
	print("\n");
}

sub createCrypToolSetupExecutables() {
	my $setupPath = $absoluteScriptPath . "..\\setup";
	my $batchPath = $absoluteScriptPath . "..\\setup\\createsetupexe1lang.bat";
	foreach my $language (@{$configuration->{"LANGUAGES"}}) {
		print("Creating CrypTool_$language setup executable...\n");
		my $process = undef;
		Win32::Process::Create($process, $batchPath, "createsetupexe1lang $language", 1, Win32::Process::CREATE_NO_WINDOW(), $setupPath) or print Win32::FormatMessage(Win32::GetLastError());
		$process->Wait(INFINITE);
	}
	print("\n");
}

sub signCrypToolSetupExecutables {
	my $setupPath = $absoluteScriptPath . "..\\setup";
	foreach my $language (@{$configuration->{"LANGUAGES"}}) {
		print("Signing CrypTool_$language setup executable...\n");
		my $setupsToBeSigned = getSetupsToBeSigned($language);
		foreach my $setupToBeSigned (@{$setupsToBeSigned}) {
			my $process = undef;
			Win32::Process::Create($process, $signtoolPath, "signtool sign /f $certificateFilename /t http://timestamp.verisign.com/scripts/timstamp.dll /p $certificatePassword $setupToBeSigned", 1, Win32::Process::CREATE_NO_WINDOW(), ".") or print Win32::FormatMessage(Win32::GetLastError());
			$process->Wait(INFINITE);
		}
	}
	print("\n");
}

sub getFilesToBeSigned() {
	my ($language) = @_;
	my $setupPath = $absoluteScriptPath . "..\\setup\\setup-$language";
	my @extensions = ( "dll", "exe" );
	my @filesToBeSigned = ( );
	foreach my $extension (@extensions) {
		my @files = glob "$setupPath\\*.$extension";
		foreach my $file (@files) {
			push(@filesToBeSigned, $file);
		}
	}
	return \@filesToBeSigned;
}

sub getSetupsToBeSigned() {
	my ($language) = @_;
	my $setupPath = $absoluteScriptPath . "..\\setup";
	my @setupsToBeSigned = glob "$setupPath\\SetupCrypTool_*_$language.exe";
	return \@setupsToBeSigned;
}