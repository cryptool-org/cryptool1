#!/usr/bin/perl -w
# vim: set ts=4 sw=4:

package DG;

use Data::Dumper;

sub new {
	bless { S => {}, P => {} };
}

sub add {
	my $self = shift;
	my $a = shift;
	my $b = shift;
	$self->{S}->{$a} ||= [];
	$self->{S}->{$b} ||= [];
	push @{$self->{S}->{$a}},$b
		unless inlist($b,$self->{S}->{$a});
	$self->{P}->{$a} ||= [];
	$self->{P}->{$b} ||= [];
	push @{$self->{P}->{$b}},$a
		unless inlist($a,$self->{P}->{$b});
}

sub addlist {
	my $self = shift;
	my $l = shift;
	return unless @$l;
	$self->add("",$l->[0]);
	my $i;
	for ($i = 0; $i < @$l - 1; $i++) {
		$self->add($l->[$i],$l->[$i+1]);
	}
}

sub inlist {
	my $el = shift;
	my $l = shift;
	foreach (@$l) {
		return 1
			if $_ eq $el;
	}
	return 0;
}

sub suc {
	my $self = shift;
	my $a = shift;
	@{$self->{S}->{$a}};
}

sub pred {
	my $self = shift;
	my $a = shift;
	@{$self->{P}->{$a}};
}

sub dump {
	my $self = shift;
	print Dumper($self),"\n";
}

sub maxorundef {
	# return max of @_ if all are defined, undef otherwhise
	@_ or die "maxorundef: empty argument list";
	my $max = pop(@_);
	while (defined $max && @_) {
		my $x = pop(@_);
		$max = $x 
			if !defined($x) || $x > $max;
	}
	return $max;
}

sub maxdist {
	my $self = shift;
	my $start = shift;
	my %done = ();
	my @work = ($start);
	#my $rest = grep { $_ ne $start } keys %{$self->{S}};
	my %maxdist = ($start => 0);
	my $tries = 0;
	while (@work && $tries < @work) {
		my $n = shift @work;
		$tries++;
		my $max = maxorundef(0, map { $maxdist{$_} } $self->pred($n));
		if (defined($max)) {
			$maxdist{$n} = $max + 1;
			#print "$n: $maxdist{$n}\n";
			push @work, $self->suc($n);
			$tries = 0;
		} else {
			push @work, $n; # trie again later
			#print "U $n\n";
		}
	}
	if (@work) {
		print Dumper(\@work);
		print Dumper(\%maxdist);
		die;
	}
	return sort { $maxdist{$a} <=> $maxdist{$b} } keys %maxdist;
}
1;

package main;

use Data::Dumper;
use Getopt::Std;
our ($opt_d, $opt_i, $opt_I, $opt_l);
getopts('diIl:'); # d: detail, i: show info, 
                  # I: ID instead of text (implies -i), 
                  # l: language

$opt_i = 1 if ($opt_I);

die "ERROR: -d and -i options are mutually exclusive. Stopped" if ($opt_d && $opt_i);


my %menushort = ( 
	ASCTYPE => 'A', 
	HEXTYPE => 'H',
	PLOTTYPE => 'P',
	TEXTTYPE => 'T',
	MAINFRAME => 'M',
	CONTEXT_MENU => 'C',
	CONTEXT_MENU_PLOT => 'CP'
);
my %t = ();
my $clang;
my @cmenus;
my $id_desc = ();
my $in_stringtable = 0;
my %menuid = ();

while (<>) {
        s/\r//g;
        # escape quoted " characters (Visual Studio writes them as "", we
        # will use \" instead
        s/\"\"/\\\"/g;

	# store stringtable definitions
        if ($in_stringtable) {
	        next if (/^BEGIN/);
		if (/^END/) {
		        $in_stringtable = 0;
		        next;
		}
		my ($id, $value) = /^\s*(\S+)\s*(.*)/;
		if (! $value) {
		    $value = <>;
		    chomp($value);
		    $value =~ s/\r//g;
		    $value =~ s/^\s*//;
		}
		$value =~ s/^\"//;
		$value =~ s/\"$//;
		if (exists $id_desc->{$clang}->{$id}) {
		        print STDERR "WARNING: duplicate string definition of $id for language $clang\n";
		}
		$id_desc->{$clang}->{$id} = $value;
		next;
	}

	if (m{^LANGUAGE LANG_(\w+)}) {
		$clang = $1;
		#print "L $clang\n";
	} elsif (m{^IDR_(\w+) MENU}) {
		@cmenus = ($menushort{$1} || $1);
	} elsif (m{^\s*POPUP "(.*?)"}) {
		my $mi = clean($1);
		my $m = join('|',tail(@cmenus));
		push @{$t{$clang}->{$cmenus[0]}->{$m}},$mi;
		push @cmenus,$mi;
		my $l = @cmenus;
		#print "$l @cmenus\n";
	} elsif (m{^\s*MENUITEM (?<!\\)"(.*?)(?<!\\)"(.*)}) {
	        # This regex matches "..." quoted strings and honours \-escaped
	        # " characters properly (negative look-behind)
	        my $mi = clean($1);

	        # un-escape escaped quotes
	        $mi =~ s/\\\"/\"/g;

		# extract id
		my $id = $2;
		$id =~ s/^,\s*// if ($id); # clean leading junk
		if (! $id) {
		    $id = <>; # extract id from next line
		    chomp($id);
		    $id =~ s/^\s*//;
		    $id =~ s/\r//;
		}
		$id =~ s/,.*//;

		my $m = join('|',tail(@cmenus));
		push @{$t{$clang}->{$cmenus[0]}->{$m}}, $mi;

		# record ID for this menu item
		$menuid{$clang}->{"$m|$mi"} = $id;

		my $l = @cmenus;
		#print STDERR "$l @cmenus $mi\n";
	} elsif (m{^\s*END\s*$} && @cmenus) {
		pop @cmenus;
	} elsif (m{^\s*STRINGTABLE}) {
	        $in_stringtable = 1;
	}
}


my @line = (
	'|---',
	'|   ',
	'`---',
	'    ',
	"\n"
);
for (0..3) {
	$line[$_] = qq(<img align="center" src="$_.gif" width="30" height="24">);
}
$line[4] = "<br>\n";

my %g = ();
my %mm = (); # merged menu tree $mm{GERMAN} = ("" => ['Datei',...], "Datei" =>
my %typelist = (); # types each menu item is defined for
my %idlist = ();   # ID String replacement text for each menu item

#print "<body><font size='6' face='Arial,Helvetica'>\n";
print "<body><font size='-1' face='Arial,Helvetica'>\n";

foreach $l ($opt_l) { #(keys %t) {
	my $lt = $t{$l};
	if (0) {
	my $g = new DG;
	$g->addlist($lt->{T}->{"Ver-/Entschlüsseln|Klassisch"});
	$g->addlist($lt->{A}->{"Ver-/Entschlüsseln|Klassisch"});
	$g->addlist($lt->{H}->{"Ver-/Entschlüsseln|Klassisch"});
	$g->dump;
	print join("\n",@{$t{GERMAN}->{T}->{"Ver-/Entschlüsseln|Klassisch"}}),"\n";
	print "\n";
	print join("\n",@{$t{GERMAN}->{H}->{"Ver-/Entschlüsseln|Klassisch"}}),"\n";
	print "\nMAXDIST",join("\n",$g->maxdist(""));
	last;
	}
	$g{$l} = {};
	my $gt = $g{$l};
	my @type = qw(M A T H P); #(qw(M A H P T)) 
	foreach $m (@type) {
		my $mt = $lt->{$m};
		foreach $n (keys(%$mt)) {
			#print "\n\n>>> $l $m $n\n";
			#show($lt->{$m},"");
			#print Dumper($mt->{$n});
			$gt->{$n} ||= new DG;
			$gt->{$n}->addlist($mt->{$n});


			$typelist{$l}->{$n} ||= "";
			$typelist{$l}->{$n} .= $m unless $typelist{$l}->{$n} =~ m{$m};
			foreach (@{$mt->{$n}}) {
				my $sn = "$n|$_";
				$typelist{$l}->{$sn} ||= "";
				$typelist{$l}->{$sn} .= $m unless $typelist{$l}->{$sn} =~ m{$m};

				# get status text (or id) for this entry
				if (exists $menuid{$l}->{$sn}) {
				    my $id = $menuid{$l}->{$sn};
				    if (! $opt_I) {
					$idlist{$l}->{$sn} = $id_desc->{$l}->{$id};
				    } else {
					$idlist{$l}->{$sn} = $id;
				    }
				}

			}
		}
	}
	foreach $n (keys(%$gt)) {
		#print "\n\n> $l $n";
		eval {
			#$gt->{$n}->dump;
			my @res = $gt->{$n}->maxdist("");
			#print join("\n",@res);
			shift @res; # remove ""
			$mm{$l}->{$n} = [@res];
			#$mm{$l}->{$n} = [map { "$_ [" . $typelist{$l}->{"$n|$_"} ."]" } @res];
		};
		if ($@) {
			map { print "|$n:",join("\n",@{$lt->{$_}->{$n}}),"\n"; } @type;
			die "ERROR: Inconsistency detected. Please check the partial order of the menu entries. Stopped";
		}
	}

	if (0) {
	show($mm{$l},$opt_d ? $typelist{$l} : {},"");
	} else {
		print "<table><tr valign='top'>\n" unless $opt_i;
		foreach (@{$mm{$l}->{""}}) {
		        my $tl = "";
			my $list = {};
			if ($opt_d) {
			    $tl = "[$typelist{$l}->{$_}]";
			    $list = $typelist{$l};
			}
			if ($opt_i) {
			    $list = $idlist{$l};
			}

			print "<td nobreak>" unless $opt_i;
			print"<b>$_</b>$tl<br>\n";
			show($mm{$l}, $list,$_);
			if (! $opt_i) {
			    print "</td>\n";
			} else {
			    print "<br><br>\n";
			}
		}
		print "<td></tr></table>\n" unless $opt_i;

	}
}

sub show {
	my $lt = shift;
	my $tl = shift;
	my $m = shift;
	my $prefix = shift || '';
	my $mi = $lt->{$m};
	my $i;
	for ($i = 0; $i < @$mi; $i++) {
		my $s = $mi->[$i];
		my $last = $i + 1 == @$mi;
		my $p1 = $last ? $line[2] : $line[0];
		my $msub = $m ? "$m|$s" : $s;
		my $t = $tl->{$msub} ? "[$tl->{$msub}]" : "";
		$s=~ s/ /&nbsp;/g;
		#print ">>$msub\n";
		print "$prefix$p1$s$t$line[4]";
		if ($lt->{$msub}) {
			my $p2 = $last ? $line[3] : $line[1];
			show($lt,$tl,$msub,$prefix . $p2);
		}
	}
}

sub tail {
	shift @_;
	@_;
}

sub clean {
	my $x = shift;
	$x =~ s{\\t.*}{};
	$x =~ s{&}{}g;
	$x;
}

