# This scripts does some conistency checks on CrypTool.rc
# - do the english and german IDs match for dialogs, bitmaps, icons and stringtables
# - have some popup menus changed (details and background: see CrypToolPopupIDs.txt)
# usage: perl CheckResourceIDs.pl CrypToolPopupIDs.txt CheckResourceIDs.log
# this script is invoked by the custom build step of CrypToolPopupIDs.txt
# Any questions -> ask J�rg js@joergschneider.com

sub clean {
  local($_) = shift;
  s/[\W_]//g; # remove any non alphanumerical chars
  $_;
}

@stack = ();
%rcmenu = ();  
%filemenu = ();
$nerror = 0;
$lno = 0;

my $MID = $ARGV[0] || "CrypToolPopupMenuIDs.txt";
my $RC = "CrypTool.rc";
my $OKLOG = $ARGV[1];
my $instringtable = 0;

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

	if (m{^\s*(\w+)\s+(DIALOG|BITMAP|ICON)\s+}) {
		$id{$lang}{$1} = $lno;
		next;
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
	    print STDERR "$RC($lno) : error: This menu entry is the same as an earlier one ($rcmenu{$index}) except for non alpha-numerical characters. Both will be treated the same w.r.t. F1\n";
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
			print STDERR "$MID($lno) : error: Menu text was changed in $RC:$rcmenuline{$index}? Please update $MID($lno) to ... # $rcmenu{$index}\n";
			$nerror++;
		}
	} else {
		print STDERR "$MID($lno) : error: Popup menu deleted from $RC? Please check and possibly delete line $lno from $MID\n";
		$nerror++;
	}
}
close MID;

foreach (sort keys %rcmenu) {
	if (!defined $filemenu{$_}) {
		my ($lang,$id) = split(':',$_);
		print STDERR "$RC($rcmenuline{$_}) : error: New menu entry? Please update $MID by adding the following line: $lang\t$id # $rcmenu{$_}\n";
		$nerror++;
	}
}

my $iden = $id{ENGLISH};
my $idde = $id{GERMAN};
foreach (sort keys %$iden) {
	print "$RC($iden->{$_}) : warning: $_ is missing in german language ressources\n"
		unless defined $idde->{$_};
}
foreach (sort keys %$idde) {
	print "$RC($idde->{$_}) : warning: $_ is missing in english language ressources\n"
		unless defined $iden->{$_};
}

if ($nerror == 0) {
	#update time stamp
	open OKLOG ,">$OKLOG " or die "open $OKLOG : $!\n";
	print OKLOG  "$RC and $MID checked successfully.\n\nThis file can be safely removed.\n";
	close OKLOG ;
} else {
	unlink($OKLOG);
}

exit($nerror ? 1 : 0);
