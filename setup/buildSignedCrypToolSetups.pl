# buildSignedCrypToolSetups.pl

#
# Be aware that this script doesn't run as-is due to hard-coded paths 
# to the "devenv.exe" and the "signtool.exe". Apart from that, the 
# script accepts two possible arguments: "noSign" and "noRebuild". 
# If these arguments are omitted, the script tries to sign the 
# resulting archives and CrypTool is fully rebuilt for each language.
#
# flomar, March 2017
#

use strict;
use Cwd qw/abs_path/;
use Term::ReadKey;
use Win32::Process;

my @languages = ( "de", "en", "es", "fr", "pl", "rs" );

my $noSign = undef;
my $noRebuild = undef;

my $absoluteScriptPath = getAbsoluteScriptPath();

my $certificateFilename = $absoluteScriptPath . "certificate.pfx";
my $certificatePassword = undef;

applyArguments();
printIntroductoryInformation();
printCertificateInformation() if($noSign == 0);
$certificatePassword = requestPassword() if($noSign == 0);
buildCrypTool();
createCrypToolSetupDirectories();
signCrypToolSetupDirectories() if($noSign == 0);
createCrypToolSetupExecutables();
signCrypToolSetupExecutables() if($noSign == 0);

sub getAbsoluteScriptPath() {
	my $file = $0;
	my $path = abs_path($0);
	if($path =~ m/(.*)$file/g) {
		return $1;
	}
	return "";
}

sub applyArguments() {
	$noSign = 0;
	$noRebuild = 0;
	foreach my $argument (@ARGV) {
		if($argument eq "noSign") {
			$noSign = 1;
		}
		if($argument eq "noRebuild") {
			$noRebuild = 1;
		}
	}
}

sub printIntroductoryInformation() {
	print("$0\n");
	print("\n");
	print("CrypTool will be built in the following languages:\n");
	print(" - " . join(", ", @languages) . ".\n");
	print("\n");
}

sub printCertificateInformation() {
	print("The following PKCS#12 file will be used for the signing process:\n");
	print(" - " . $certificateFilename . "\n");
	print("\n");
}

sub requestPassword() {
	print("Please specify the password for the PKCS#12 file: ");
	ReadMode("noecho");
	chomp(my $password = <STDIN>);
	ReadMode(0);
	print("\n");
	print("\n");
	return $password;
}

sub buildCrypTool() {
	my @filesToBeTouched = ( $absoluteScriptPath . "..\\CrypTool\\CrypTool.rc", $absoluteScriptPath . "..\\CrypTool\\CrypToolApp.cpp", $absoluteScriptPath . "..\\CrypTool\\DlgAbout.cpp" );
	foreach my $fileToBeTouched (@filesToBeTouched) {
		utime(undef, undef, $fileToBeTouched);
	}
	my $VS2008IdePath = "C:\\Program Files (x86)\\Microsoft Visual Studio 9.0\\Common7\\IDE\\devenv.exe";
	my $VS2008SolutionPath = $absoluteScriptPath . "..\\CrypTool\\CrypTool-VS2008.sln";
	my $buildMode = $noRebuild == 0 ? "/Build" : "/Rebuild";
	foreach my $language (@languages) {
		print("Building CrypTool_$language...\n");
		my $process = undef;
		Win32::Process::Create($process, $VS2008IdePath, "devenv $VS2008SolutionPath $buildMode Release_$language", 1, Win32::Process::CREATE_NO_WINDOW(), ".") or print Win32::FormatMessage(Win32::GetLastError());
		$process->Wait(INFINITE);
	}
	print("\n");
}

sub createCrypToolSetupDirectories() {
	my $setupPath = $absoluteScriptPath . "..\\setup";
	my $batchPath = $absoluteScriptPath . "..\\setup\\createsetupdir1lang.bat";
	foreach my $language (@languages) {
		print("Creating CrypTool_$language setup directory...\n");
		my $process = undef;
		Win32::Process::Create($process, $batchPath, "createsetupdir1lang $language", 1, Win32::Process::CREATE_NO_WINDOW(), $setupPath) or print Win32::FormatMessage(Win32::GetLastError());
		$process->Wait(INFINITE);
	}
	print("\n");
}

sub signCrypToolSetupDirectories() {
	my $signtoolPath = "C:\\Program Files\\Microsoft SDKs\\Windows\\v6.0A\\Bin\\signtool.exe";
	foreach my $language (@languages) {
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
	foreach my $language (@languages) {
		print("Creating CrypTool_$language setup executable...\n");
		my $process = undef;
		Win32::Process::Create($process, $batchPath, "createsetupexe1lang $language", 1, Win32::Process::CREATE_NO_WINDOW(), $setupPath) or print Win32::FormatMessage(Win32::GetLastError());
		$process->Wait(INFINITE);
	}
	print("\n");
}

sub signCrypToolSetupExecutables {
	my $signtoolPath = "C:\\Program Files\\Microsoft SDKs\\Windows\\v6.0A\\Bin\\signtool.exe";
	my $setupPath = $absoluteScriptPath . "..\\setup";
	foreach my $language (@languages) {
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