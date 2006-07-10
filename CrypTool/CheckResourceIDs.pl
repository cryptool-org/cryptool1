# This scripts does some conistency checks on CrypTool.rc
# - do the english and german IDs match for dialogs, bitmaps, icons and stringtables
# - have some popup menus changed (details and background: see CrypToolPopupIDs.txt)
# usage: perl CheckResourceIDs.pl CrypToolPopupIDs.txt CheckResourceIDs.log
# this script is invoked by the custom build step of CrypToolPopupIDs.txt
# Any questions -> ask Jörg js@joergschneider.com

sub clean {
  local($_) = shift;
  s/[\W_]//g; # remove any non alphanumerical chars
  $_;
}

@stack = ();
%rcmenu = ();  
%filemenu = ();
%id = (); #$id{lang}{id} = $lno
%dialog = (); #$dialog{lang}{dialogid}{elementid} = $lno
$nwarning = 0;
$lno = 0;

my $MID = $ARGV[0] || "CrypToolPopupMenuIDs.txt";
my $RC = "CrypTool.rc";
my $OKLOG = $ARGV[1];
my $instringtable = 0;
my $indialog = 0;
my $cont = ''; # handle continuation lines in dialogs

if (!defined $OKLOG) {
	$OKLOG = $0;
	$OKLOG  =~ s/\.[^.]*//;
	$OKLOG  .= ".log";
}
open RC,"<$RC" or die "open $RC: $!\n";

foreach (<RC>) {
	$lno++;
	if (m{LANGUAGE LANG_(\w*)}) {
		die "$0: menu stack not empty on language change" 
			if (@stack);
		$lang = $1 ;
	}

	if (m{^\s*(\w+)\s+(DIALOG|DIALOGEX|BITMAP|ICON)\s+}) {
		$id{$lang}{$1} = $lno;
		$indialog = $1 if $2 eq 'DIALOG' || $2 eq 'DIALOGEX';
		next;
	}
	if ($indialog) {
		if (m{^\s*END\s*}) {
			$indialog = '';
			next;
		}
		if ($cont) { # handle continuation lines
			$_ = $cont . $_;
			$cont = '';
		}
		if (m{[,|]\s*$}) { # handle continuation lines
			chomp;
			$cont = $_;
			next;
		}
		if (m{^\s*([a-zA-Z]+)\s+(\"(?:[^\"]|\"\")*\"\s*,\s*)?(-1|([a-zA-Z]\w*))\s*,}) {
			my $id = $3 eq '-1' ? IDC_STATIC : $3;
			#next if $3 =~ m{^IDC_STATIC};
			#next if $1 =~ m{EDITTEXT|CONTROL|DEFPUSHBUTTON|PUSHBUTTON|LTEXT|GROUPBOX|CTEXT|COMBOBOX|RTEXT|SCROLLBAR|LISTBOX};
			#print "$indialog\{$1}{$2}{$3} $_";
			$dialog{$lang}{$indialog}{$id} = $lno;
			next;
		}
	}
	
	if (m{^\s*STRINGTABLE}) {
		$instringtable = 1;
	}
	if ($instringtable) {
		if (m{^\s*END\s*}) {
			$instringtable = 0;
			next;
		}
		if (m{^\s*(\w+)}) {
			$id{$lang}{$1} = $lno;
			next;
		}
	}

	pop @stack
		if (m{^\s*END\s*});
	
	next unless m{POPUP "(.*)"}; 
	chomp;
	$_ = $1;
	s/\\t.*//; #remove keyboard accelerators
	next if m/^ *$/;

	push @stack,$_;
    my $id = join('_',map { clean $_ } @stack);
	my $index = "$lang:$id";
	my $text = join("|",@stack);
	if (defined($rcmenu{$index}) && $text ne $rcmenu{$index}) {
	    print STDERR "$RC($lno) : warning: This menu entry is the same as an earlier one ($rcmenu{$index}) except for non alpha-numerical characters. Both will be treated the same w.r.t. F1\n";
		$nwarning++;
	}
	$rcmenu{$index} = $text;
	$rcmenuline{$index} = $lno;
}
close RC;
$lno = 0;

if (0) {
foreach (sort keys %rcmenu) {
	my ($lang,$id) = split(':',$_);
	my $menu = $rcmenu{$_};
	print "$lang\t$id\t# ",$menu,"\n";
}
}

open MID,"<$MID" or die "open $MID: $!\n";

foreach (<MID>) {
	$lno++;
	next if m{^\s*#} || m{^\s*$};
	chomp;
	die "$MID($lno) : error: malformed line ($_)\n" 
		unless m{^\s*(\w+)\s+(\w+)\s+#\s?(.*)};

	my $lang = $1;
	my $id = $2;
	my $comment = $3;
	my $index = "$lang:$id";
	$filemenu{$index} = [split("|",$comment)];
	if (defined $rcmenu{$index}) {
		if ($comment ne $rcmenu{$index}) {
			print STDERR "$MID($lno) : warning: Menu text was changed in $RC:$rcmenuline{$index}? Please update $MID($lno) to ... # $rcmenu{$index}\n";
			$nwarning++;
		}
	} else {
		print STDERR "$MID($lno) : warning: Popup menu deleted from $RC? Please check and possibly delete line $lno from $MID\n";
		$nwarning++;
	}
}
close MID;

foreach (sort keys %rcmenu) {
	if (!defined $filemenu{$_}) {
		my ($lang,$id) = split(':',$_);
		print STDERR "$RC($rcmenuline{$_}) : warning: New menu entry? Please update $MID by adding the following line: $lang\t$id # $rcmenu{$_}\n";
		$nwarning++;
	}
}

my $iden = $id{ENGLISH};
my $idde = $id{GERMAN};
foreach (sort keys %$iden) {
	unless (defined $idde->{$_}) {
		print "$RC($iden->{$_}) : warning: $_ is missing in german language ressources\n";
		$nwarning++;
	}
}
foreach (sort keys %$idde) {
	unless (defined $iden->{$_}) {
		print "$RC($idde->{$_}) : warning: $_ is missing in english language ressources\n";
		$nwarning++;
	}
}

my $id;
my $dialogen = $dialog{ENGLISH};
my $dialogde = $dialog{GERMAN};
foreach $id (sort keys %$dialogen) {
	next unless defined $dialogde->{$id};
	my $iden = $dialogen->{$id};
	my $idde = $dialogde->{$id};
	foreach (sort keys %$iden) {
		unless (defined $idde->{$_}) {
			print "$RC($iden->{$_}) : warning: $_ (dialog $id) is missing in german language ressources\n";
			$nwarning++;
		}
	}
	foreach (sort keys %$idde) {
		unless (defined $iden->{$_}) {
			print "$RC($idde->{$_}) : warning: $_ (dialog $id) is missing in english language ressources\n";
			$nwarning++;
		}
	}
}

if ($nwarning == 0) {
	#update time stamp
	open OKLOG ,">$OKLOG " or die "open $OKLOG : $!\n";
	print OKLOG  "$RC and $MID checked successfully.\n\nThis file can be safely removed.\n";
	close OKLOG ;
} else {
	unlink($OKLOG);
}

exit(0);
