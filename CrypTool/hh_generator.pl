#! perl -w

# Skript, dass die automatisch mit makehm.exe erstellte Datei CrypTool.hm HtmlHelp-kompatibel konvertiert zu CrypTool_helpIDs.h
# 	- in .h umbenennen
# 	- #define statements allen HIDs voranstellen

# aktuelles Hilfeverzeichnis

# die .hm Datei öffnen
open(HMFILE, "< CrypTool.hm") or die "Couldn't open CrypTool.hm for reading: $!\n";

# die .h Datei erzeugen oder zum überschreiben öffnen
open(HFILE, "> CrypTool_helpIDs.h") or die "Couldn't open CrypTool_helpIDs.h for writing: $!\n";

# Zeilen in der .hm Datei mit HID erkennen und in .h Datei mit vorangestelltem #define schreiben

while(defined($line = <HMFILE>))    
	{
		if($line =~ /HID/) 	# falls HID in der Zeile vorkommt, wird #define vorangestellt 
					# falls nicht wird Zeile ohne Veränderung übernommen
			{
				print HFILE "#define ".$line;				
			}
		else
			{
				print HFILE $line;
			}		
	}
close(HMFILE);
close(HFILE);

