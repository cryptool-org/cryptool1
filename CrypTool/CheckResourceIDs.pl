# This scripts does some conistency checks on CrypTool.rc
# - do the english and german IDs match for dialogs, bitmaps, icons and stringtables
# - have some popup menus changed (details and background: see CrypToolPopupIDs.txt)
# usage: perl CheckResourceIDs.pl CrypToolPopupIDs.txt CheckResourceIDs.log
# this script is invoked by the custom build step of CrypToolPopupIDs.txt
# Any questions -> ask Jörg js@joergschneider.com

use strict;
use warnings;
use Data::Dumper;
use Carp;

sub clean {
  local($_) = shift;
  s/[\W_]//g; # remove any non alphanumerical chars
  $_;
}

my $lang; # current language
my $menu; # current top level menu ID (IDR_...)

my @stack = (); # current list of nested POPUP menu names (without short cuts), i.e.
	# list of POPUP names of which the corresponding END has not been seen yet. e.g.
	# ("A&nalyse", "Symmetrische Verschlüsselung (&klassisch)", "&Ciphertext only")

my %rcmenu = ();  
my %rcmenuline = ();  
my %menutree = (); #$menutree{$lang}{$menu} = [$menuitem_0, $menuitem_1, ...]
	# while $RC is parsed, $menutree{$lang}{$menu} is a stack of current sub menus:
	# [$finishedmenuitem_0, ..., $unfishisedmenuitem_1, [...],  $unfishisedmenuitem_1, [...]]
# menuitem_i = { # can be a MENUITEM, SEPARATOR or POPUP (see also sub menutype)
# 	line => 1234,	# line number in $RC (mandatory)
# 	name => "&Neu\tStrg+N",	# display name incl. accelerators and short cuts 
# 		# mandatory except for SEPARATORs
# 	id => ID_FILE_OPEN,	# ID of the menu item (mandatory only for MENUITEM)
# 	sub => [$menuitem_0, $menuitem_1, ...],	# list of sub menu items
#	separator => 1,	# only for SEPARATORs
# }

my %filemenu = ();
my %id = (); #$id{lang}{id} = $lno
my %dialog = (); #$dialog{lang}{dialogid}{elementid} = $lno
my $nwarning = 0;
my $lno = 0;

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


	if ($cont) { # handle memorized continuation lines
		$_ = $cont . $_;
		$cont = '';
	}
	if (m{[,|]\s*$}) { # memorize continuation lines
		chomp;
		$cont = $_;
		next;
	}

	if (m{LANGUAGE LANG_(\w*)}) {
		die "$0: menu stack not empty on language change" 
			if (@stack);
		$lang = $1 ;
		next;
	}

	if (m{^\s*(\w+)\s+MENU\s*$}) {
		$menu = $1;
		$menutree{$lang}{$menu} = [];
		next;
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
		if (m{^\s*([a-zA-Z]+)\s+(\"(?:[^\"]|\"\")*\"\s*,\s*)?(-1|([a-zA-Z]\w*))\s*,}) {
			my $id = $3 eq '-1' ? 'IDC_STATIC' : $3;
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

	if (m{^\s*END\s*}) {

		next if !@stack; # consider only END relating to POPUP

		pop @stack;

		# remove list of menuitems and corresponding POPUP item from end current list
		my $submenu = pop @{$menutree{$lang}{$menu}};
		my $m = pop @{$menutree{$lang}{$menu}};
		# insert list into POPUP item
		$m->{submenu} = $submenu;
		
		if (@stack) {
			# add to the end of the last sublist
			push @{$menutree{$lang}{$menu}->[-1]}, $m;
		} else {
			# top level, add to the end of the list
				push @{$menutree{$lang}{$menu}},$m;
		}
		
		next;
	}

	
	if (m{POPUP "(.*)"}) {
		chomp;
		$_ = $1;
		s/\\t.*//; #remove keyboard accelerators

		push @{$menutree{$lang}{$menu}}, { name => $_, line => $lno }, [ ];

		push @stack,$_;
		
		next if m/^ *$/;

		my $id = join('_',map { clean $_ } @stack);
		my $index = "$lang:$id";
		my $text = join("|",@stack);
		if (defined($rcmenu{$index}) && $text ne $rcmenu{$index}) {
		    print STDERR "$RC($lno) : warning: This menu entry is the same as an earlier one ($rcmenu{$index}) except for non alpha-numerical characters. Both will be treated the same w.r.t. F1\n";
		    print STDERR "$RC($rcmenuline{$index}) : warning: (other location)\n";
			$nwarning++;
		}
		$rcmenu{$index} = $text;
		$rcmenuline{$index} = $lno;

		next;
	}

	if (m{MENUITEM "(.*)",\s*(\w+)}) {
		chomp;
		my $name = $1;
		my $id = $2;
		$name =~ s{""}{"};
		push @{$menutree{$lang}{$menu}->[-1]}, { name => $name, id => $id, line => $lno };
		next;
	}
	if (m{MENUITEM SEPARATOR}) {
		push  @{$menutree{$lang}{$menu}->[-1]}, { separator => 1, line => $lno };
		next;
	}
}
close RC;
$lno = 0;

#print Dumper(\%menutree);

if (0) {
foreach (sort keys %rcmenu) {
	my ($lang,$id) = split(':',$_);
	my $menu = $rcmenu{$_};
	print "$lang\t$id\t# ",$menu,"\n";
}
}

# check generated POPUP IDs against $MID
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
		print STDERR "$RC($rcmenuline{$_}) : warning: New popup menu? Please update $MID by adding the following line: $lang\t$id # $rcmenu{$_}\n";
		$nwarning++;
	}
}

my @languages = sort keys %id;
# @languages = (qw(ENGLISH GERMAN POLISH SERBIAN SPANISH)); # FIXME
my %idall = map { %$_ } values %id; # keys %ids: union of ids for all languages; values %ids: line number of one of the ids (any)
# check IDs between languages
foreach (sort keys %idall) {
	foreach $lang (@languages) {
		unless (defined $id{$lang}->{$_}) {
			print STDERR "$RC($idall{$_}) : warning: $_ is missing in $lang language ressources\n";
			$nwarning++;
		}
	}
}

# check dialog IDs between languages
my $id;
# $dialog{lang}{dialogid}{elementid} = $lno
my %dialogids = map { %$_ } values %dialog; # keys %dialogids = all dialog ids
my %dialogall = (); # $dialogall{dialogid}{elementid} = $lno
foreach $id (keys %dialogids) {
	$dialogall{$id} = { map { $_->{$id} ? %{$_->{$id}} : () } values %dialog };
}

foreach $id (sort keys %dialogids) {
	my %dialogall = # $dialogall{$elementid} = $lno
		map { $dialog{$_}->{$id} ? %{$dialog{$_}->{$id}} : () } @languages;
	foreach (sort keys %dialogall) { 
		foreach $lang (@languages) {
			if (defined $dialog{$lang}->{$id} &&
				!defined $dialog{$lang}->{$id}->{$_}) {
				print STDERR "$RC($dialogall{$_}) : warning: $_ (dialog $id) is missing in $lang language ressources\n";
				$nwarning++;
			}
		}
	}
}

# compare menu trees
my $idr;
my %idrs = map { %$_ } values %menutree;
%idrs or die "$RC : error: no MENU IDR_... found";
my $refidr = 'IDR_TEXTTYPE';
$idrs{$refidr} or die "$RC : error: $refidr not found";

foreach $idr (sort keys %idrs) {
	foreach $lang (@languages) {
		if (!$menutree{$lang}{$idr}) {
			print STDERR "$RC : warning: MENU $idr is missing in $lang language ressources\n";
			$nwarning++;
		}
	}
}


foreach $idr (sort keys %idrs) {

	foreach $lang (@languages) {
		if (!$menutree{$lang}{$idr}) {
			print STDERR "$RC : warning: MENU $idr is missing in $lang language ressources\n";
			$nwarning++;
			next;
		}
		$nwarning += comparemenu($menutree{$lang}{$refidr},$menutree{$lang}{$idr},
			"$lang/$refidr","$lang/$idr")
			if ($idr ne $refidr && $idr !~ m{_CONTEXT});
		
		$nwarning += comparemenu($menutree{$languages[0]}{$idr},$menutree{$lang}{$idr},
			"$languages[0]/$idr","$lang/$idr","ignorenames")
			if ($lang ne $languages[0]);
	}
		
}
if ($nwarning == 0) {
	#update time stamp
	open OKLOG ,">$OKLOG " or die "open $OKLOG : $!\n";
	print OKLOG  "$RC and $MID checked successfully.\n\nThis file can be safely removed.\n";
	close OKLOG ;
} else {
	print STDERR "$RC : warning: =================\n";
	print STDERR "$RC : warning: Doubleclicking on the above warnings will show you the line with the problem in $RC.\n";
	print STDERR "$RC : warning: This will ONLY work if you first open $RC with 'File \\ Open \\ File \\ Open WITH \\ Source Code (Text) Editor'.\n";
	print STDERR "$RC : warning: 'Open WITH' is important here. It can be found by clicking on the down arrow next to 'Open'.\n";
	print STDERR "$RC : warning: =================\n";
	unlink($OKLOG);
}

exit(0);


# Compare two lists of menu items
# Return value: # of warnings found
# Args
# 	$mlist1 list reference containing menuitems
# 	$mlist2 list reference containing menuitems
#	$ctx1	descriptive text of $mlist1 context, e.g. GERMAN/IDR_MAINFRAME
#	$ctx2	dito for $mlist2
#	$ignorenames	if true menu names are ignored and only IDs are matched, useful to compare menus of different languages

sub comparemenu {
	my ($mlist1,$mlist2,$ctx1,$ctx2,$ignorenames) = @_;
	my $warnings = 0;
	my $fake1 = { line => @$mlist1 ? $mlist1->[-1]->{line} : -1 }; # line # of last entry
	my $fake2 = { line => @$mlist2 ? $mlist2->[-1]->{line} : -1 }; # line # of last entry
	foreach my $i (0 .. (@$mlist1 > @$mlist2 ? @$mlist1 : @$mlist2) - 1) {
		$warnings += comparemenuitem($mlist1->[$i] || $fake1,$mlist2->[$i] || $fake2,
				$ctx1,$ctx2,$ignorenames);
	}

	return $warnings;
}

# Compare two menu items
# Return value: # of warnings found
# Args
# 	$m1 	menuitem (see %menutree comment above)
# 	$m2 	menuitem
#	$ctx1	descriptive text of $m1 context, e.g. GERMAN/IDR_MAINFRAME
#	$ctx2	dito for $mt2
#	$ignorenames	if true menu names are ignored and only IDs are matched, useful to compare menus of different languages
sub comparemenuitem {
	my ($m1,$m2,$ctx1,$ctx2,$ignorenames) = @_;
	my $type1 = menutype($m1);
	my $type2 = menutype($m2);
	if (!defined $type1) {
		my $idorname2 = $m2->{id} || $m2->{name} || '';
		print STDERR "$RC($m2->{line}) : warning: $type2 $idorname2 from $ctx2 is missing in the corresponding position in $ctx1\n";
			print STDERR "$RC($m1->{line}) : warning: (other location)\n";
		return 1;
	}
	if (!defined $type2) {
		my $idorname1 = $m1->{id} || $m1->{name} || '';
		print STDERR "$RC($m1->{line}) : warning: $type1 $idorname1 from $ctx1 is missing in the corresponding position in $ctx2\n";
			print STDERR "$RC($m2->{line}) : warning: (other location)\n";
		return 1;
	}
	if ($type1 ne $type2) {
		my $idorname1 = $m1->{id} || $m1->{name} || '';
		my $idorname2 = $m2->{id} || $m2->{name} || '';
		print STDERR "\n$type1\t$idorname1\t$ctx1\n";
		print STDERR "$type2\t$idorname2\t$ctx2\n";
		print STDERR "$RC($m1->{line}) : warning: $idorname1 from $ctx1 is a $type1, while $idorname2 from $ctx2 in the corresponding position is a $type2\n";
		print STDERR "$RC($m2->{line}) : warning: (other location)\n";
		return 1;
	}
	if ($type1 eq 'MENUITEM') {
		if ($m1->{id} ne $m2->{id}) {
			print STDERR "$RC($m1->{line}) : warning: $type1 $m1->{id} from $ctx1 has a different id than $type2 $m2->{id} from $ctx2 in the corresponding position\n";
			print STDERR "$RC($m2->{line}) : warning: (other location)\n";
			return 1;
		}
		if (!$ignorenames && $m1->{name} ne $m2->{name}) {
			print STDERR "$RC($m1->{line}) : warning: $type1 $m1->{id} \"$m1->{name}\" from $ctx1 has a different text than $type2 $m2->{id} \"$m2->{name}\" from $ctx2 in the corresponding position\n";
			print STDERR "$RC($m2->{line}) : warning: (other location)\n";
			return 1;
		}
	} elsif ($type1 eq 'POPUP') {
		if (!$ignorenames && $m1->{name} ne $m2->{name}) {
			print STDERR "$RC($m1->{line}) : warning: $type1 \"$m1->{name}\" from $ctx1 has a different text than $type2 \"$m2->{name}\" from $ctx2 in the corresponding position\n";
			print STDERR "$RC($m2->{line}) : warning: (other location)\n";
			return 1;
		}
		return comparemenu($m1->{submenu},$m2->{submenu},$ctx1,$ctx2,$ignorenames);
	}

	return 0;
}

# Figure out type of a menu item
# Return value: one of qw(MENUITEM POPUP SPARATOR) or undef
# Args
# 	$m	menu item
sub menutype {
	my ($m) = @_;
	return 
		$m->{id} 	? 'MENUITEM' :
		$m->{submenu} 	? 'POPUP' :
	        $m->{separator} ? 'SEPARATOR' :
		                  undef;
}
