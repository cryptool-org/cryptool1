==================================================================
              CrypTool, Version 1.3.01x, April 2002
                  (c) Deutsche Bank AG 1998-2002
                  (c) Universit�t Siegen und Karlsruhe
                         Frankfurt am Main
==================================================================



                       Inhalt

 1. .... Kurzbeschreibung
 1.1. .... Was beinhaltet die Distribution?
 1.2. .... Danke
 1.3. .... Neuer Maintainer in der Zukunft
 2. .... Beschr�nkungen und Voraussetzungen
 2.1. .... Installation unter Windows 95
 2.2. .... Interaktive Online-Hilfe unter Windows XP
 2.3. .... Unterst�tzung verschiedener Sprachen
 2.4. .... Einschr�nkungen in den verwendeten Bibliotheken
 3. .... Installation
 4. .... Dateiliste
 4.1. ..   �berpr�fen der Integrit�t der heruntergeladenen Dateien
 5. .... Wie Sie starten...
 6. .... Neuerungen in CrypTool 1.3.00
 6.1. .... Klassische Verfahren
 6.2. .... Symmetrische Verfahren
 6.3. .... Asymmetrische Verfahren
 6.4. .... Formatierung / Anzeige / Navigation
 6.5. .... Hilfe / PDF-Skript
 6.6. .... Sonstiges
 6.7. .... �nderungen von Version 1.3.00 zu Version 1.3.01
 6.8. .... Geplante �nderungen von Vers. 1.3.01 zu Vers. 1.3.02
 7. .... M�gliche Punkte f�r eine Weiterentwicklung
 8. .... Kurze Historie der Hauptversionen
 9. .... Roadmap
10. .... Feedback bei Fehlern
11. .... Kontaktadressen
12. .... Verweise
12.1. .... Wirtschaftswoche Spezial
12.2. .... c't 14/2001, S. 204-208
12.3. .... BSI B�rger-CD "Ins Internet - mit Sicherheit"
12.4. .... Freeware-Projekt Crank
13. .... Anhang
13.1. .... CrypTool unter Linux mit Wine



1. Kurzbeschreibung
   ----------------
Dieses Readme geh�rt zur kostenlosen Distribution von CrypTool,
einem Programm, mit dem man kryptographische Funktionen leicht
demonstrieren, aber auch bekannte und unbekannte Verfahren
analysieren kann.

Zu jedem Programmteil gibt es reichhaltige Hilfe.

Vorausgesetzt wird, dass der Benutzer mit Anwendungen in einer
Windows-Umgebung umgehen kann.

Die jeweils aktuelle Version von CrypTool finden Sie unter den
Internet-Adressen:   http://www.CrypTool.de
                     http://www.CrypTool.com
                     http://www.CrypTool.org

Ziel von CrypTool ist es, kryptographische Mechanismen anschaulich
zu machen, die Verwendung und die Grenzen einzelner Mechanismen
aufzuzeigen.

Die Lizenz- und Nutzungsbestimmungen werden bei der Installation
und auf der Einstiegsseite der Onlinehilfe erl�utert.

1.1. Was beinhaltet die Distribution?
     --------------------------------
Neben dem Programm selbst gibt es eine umfangreiche Dokumentation,
die aus 4 Teilen besteht:
a) dieser Readme-Datei
b) Online-Hilfe (Programm-bezogen, mit Beispiel-Szenarien)
c) Skript (zum Thema Kryptographie, beigelegt als PDF-Datei)
d) Demos (Programmteile, die Einzelthemen/Grundlagen erl�utern).

CrypTool ist keine Applikation, mittels derer im Wirkbetrieb Daten
verschl�sselt oder anderweitig gesichert werden sollten. Es ist
eine reine Demonstration, die vor allem f�r Ausbildungszwecke
eingesetzt wird.

- Dazu beinhaltet CrypTool eine sehr umfangreiche Sammlung krypto-
  graphischer Algorithmen, die hervorragend dokumentiert ist.
  Somit ist CrypTool sehr gut geeignet zur Ausbildung und zur
  Mitarbeiter-Sensibilisierung f�r IT-Sicherheit.

- Die meisten der krytographischen Basisalgorithmen stammen von:
  - der Industrie-bew�hrten Secude-Bibliothek (Version 5.4.15)
    (www.secude.com) und von 
  - der Miracl-Bibliothek (Version 4.4.3) 
    (http://indigo.ie/~mscott/).
  Somit ist CrypTool auch eine hervorragende Referenzimplemen-
  tierung.

- Die Kryptoanalyse der meisten der implementierten klassischen
  Verfahren ist automatisiert. Die Analyse der modernen Verfahren
  ist eingeschr�nkt, so da� CrypTool nicht als Hackertool
  eingesetzt werden kann.

- Zum Erstellen selbstentpackender Executables ist in CrypTool
  ein Programm integriert, das auch eigenst�ndig benutzt werden
  kann.
  Darin wird aus einem Passwort ein Session-Key erzeugt, mit dem
  ein beliebiger Dateiinhalt AES-verschl�sselt wird.

1.2. Danke
     -----
Zu CrypTool haben viele verschiedene Personen - insbesondere auch
in ihrer Freizeit - beigetragen. Herzlichen Dank.

Dr. Carsten Elsner erlaubte uns, seine Geschichte "Der Dialog der
Schwestern" als PDF-Datei beizulegen.
Der Verfasser, als alleiniger Inhaber aller Rechte an dem Werk, 
r�umt dem CrypTool-Maintainer das ausschlie�liche Vervielf�lti-
gungs- und Verbreitungsrecht ein. Die Geschichte darf nur zusammen
mit dem CrypTool-Paket verbreitet werden. 


1.3. Neuer Maintainer in der Zukunft
     -------------------------------
Wie geplant wird CrypTool ein akademisches Zuhause erhalten, wo
es in Zukunft als Open Source weitergepflegt wird.
Die bisherigen Sponsoren von CrypTool waren die Deutsche Bank,
Secude GmbH und FZI Karlsruhe. 1.3.0x ist die letzte Version, 
die die Deutsche Bank als Maintainer herausbringt.
Ab Mai 2002 ist der Lehrstuhl Sicherheit in der Informations-
technik, Fachbereich Informatik unter Frau Prof. Dr. Claudia 
Eckert an der TU Darmstadt der neue Maintainer.

Wir w�rden uns sehr freuen, wenn sich nicht nur die bisherigen 
Entwickler, sondern auch viele neue an der Weiterentwicklung von
CrypTool beteiligen.
Die Homepage von CrypTool bleibt weiterhin www.cryptool.de.



2. Beschr�nkungen und Voraussetzungen
   ----------------------------------
CrypTool erfordert eine Win32 Umgebung, wie sie unter Windows 95,
Windows 98, Windows Me, Windows NT (ab 4.0), Windows 2000 und 
Windows XP gegeben ist.

CrypTool funktioniert grunds�tzlich auch unter FreeBSD/Linux mit
Wine (mit Abstrichen an Funktionalit�t und Stabilit�t).
Siehe Anhang 13.1.


2.1. Installation unter Windows 95
     -----------------------------
Bei �lteren Windows 95 Systemen erhalten Sie beim Aufruf von
CrypTool die Meldung "kann 'secude.dll' nicht finden". In diesem
Fall k�nnen Sie CrypTool nur eingeschr�nkt nutzen.

Die Algorithmen der Secude-Bibliothek werden beim Start von
CrypTool mit Hilfe der Bibliothek "msvcrt.dll" dynamisch geladen.
Leider unterst�tzt unter Windows 95 nicht jede Version von
"msvcrt.dll" das Einbinden der Secude-Bibliothek. Zu dem
Lieferumfang verschiedener Programme geh�rt eine neuere Version
von "msvcrt.dll" - kopieren Sie diese Datei in das Windows-
Verzeichnis oder in das Verzeichnis von CrypTool.


2.2. Interaktive Online-Hilfe unter Windows XP
     -----------------------------------------
Unter Windows XP ist der Aufruf der interaktiven Online-Hilfe �ber
die F1-Taste in einem Spezialfall nicht m�glich: betroffen sind
nur Men�s, die noch Untermen�s haben. Das Problem tritt nur auf,
wenn das Untermen� aufgeklappt ist. F1 bewirkt dann gar nichts.

Normalerweise kann bei CrypTool auch Hilfe zu einem Men�eintrag 
angefordert werden, der selbst weitere Untermen�s hat. 
Unter Windows XP erh�lt man die Online-Hilfe dazu nur, wenn das
Popup-Fenster der untergeordneten Men�punkte nicht aufgeklappt 
ist. 
Bei den anderen Windows-Versionen spielt das keine Rolle, dort ist
nur wichtig, dass das Men� den Fokus hat.

Workaround anhand eines Beispiels: Einzelverfahren / RSA-Demo
Wenn hier das Untermen� zu "RSA-Demo" aufklappt, Sie aber die 
Hilfe zum Men�eintrag "RSA-Demo" haben wollen, m�ssen Sie - nur
unter Windows XP - das Untermen� von "RSA-Demo" erst mit Escape
(Esc) oder den Pfeiltasten wieder einklappen, dann funktioniert 
das Aufrufen der Online-Hilfe mit F1 auch unter Windows XP.


2.3. Unterst�tzung verschiedener Sprachen
     ------------------------------------
Programm, Hilfesystem und Dokumentation sind mehrsprachig aus-
gelegt (zur Zeit englisch und deutsch).

F�r jede unterst�tzte Sprache gibt es ein eigenes Setup mit dem
entsprechenden ausf�hrbaren Programm (der Versuch, alle Sprachen
in ein einziges Executable einzubinden wurde wieder aufgegeben,
da die automatische Spracheinstellung beim Anwender (anhand seiner
Systemeinstellungen) nur unter Windows 4.0, nicht aber unter 
Win9x, korrekt funktionierte).


2.4. Einschr�nkungen in den verwendeten Bibliotheken
     -----------------------------------------------
Die beigelegte Secude-Lib ist durch das Ticketfile bei den 
asymmetrischen Verfahren auf eine Schl�ssell�nge von 768 Bits 
beschr�nkt und die Unterst�tzung von Smartcards ist deaktiviert. 
Falls Sie eine Lizenz der Secude-Lib besitzen, k�nnen Sie mit 
Hilfe Ihres Ticketfiles die asymmetrischen Verfahren auch mit 
gr��eren Schl�ssell�ngen benutzen. Die Verwendung der Secude-Lib
au�erhalb von CrypTool ist lizenzpflichtig.

Zur Demonstration des RSA-Kryptosystem und zur Faktorisierung von 
Zahlen greift CrypTool auf die Langzahlarithmetik der Bibliothek 
Miracl von Shamus Software Ltd. zu. Die Bitl�nge der Zahlen wurde
in der CrypTool-Anwendung auf 1024 beschr�nkt.



3. Installation
   ------------
Durch Aufruf des CrypTool-Setups an einer geeigneten Stelle im
Dateibaum auf Ihrem PC wird CrypTool installiert.
Als Standardwert ist das Verzeichnis "C:\Programme\CrypTool"
vorgesehen. Das Zielverzeichnis kann in der Installationsroutine
ge�ndert werden.

Besitzen Sie bereits eine fr�here Version von CrypTool, so
empfiehlt es sich, vor der erneuten Installation das alte CrypTool
zu deinstallieren, da unter Umst�nden nicht alle alten
Dateien �berschrieben werden. Bitte beachten Sie:
- Wenn bei der Deinstallation nicht alle Verzeichnisse/Dateien im
  Programmverzeichnis (meist C:\Programme\CrypTool) gel�scht 
  werden, l�schen Sie diese manuell.
- Bei der Deinstallation von CrypTool werden alle bisher erzeugten
  asymmetrischen Schl�ssel gel�scht. Wenn Sie diese Schl�ssel auch
  in der neuen Version von CrypTool nutzen wollen, dann sichern 
  Sie vor der Deinstallation das unter dem Programmverzeichnis 
  liegende Verzeichnis pse\ mit allen darin gespeicherten Dateien
  in ein anderes Verzeichnis.
  Nachdem die neue Version von CrypTool installiert wurde, 
  kopieren Sie das gesicherte pse\-Verzeichnis in das neue
  Programmverzeichnis.
  Ab Version 1.3.00 k�nnen Sie RSA- und DSA-PSEs als PKCS#12-
  Struktur exportieren bzw. importieren.

F�r den Fall, dass mehrere Benutzer dieselbe CrypTool- 
Installation verwenden wollen, m�ssen die Zugriffsrechte auf den
Verzeichnissen pse\ und pse\pseca\ und den darin enthaltenen
Dateien f�r alle Benutzer auf Vollzugriff gesetzt werden.

Der Teilbaum "pse\" sollte nicht manuell bearbeitet werden, da bei
einer inkonsistenten Struktur nur eine Neuinstallation von
CrypTool bleibt.



4. Dateiliste
   ----------
CrypTool wird als komprimiertes, selbstextrahierendes Archiv in 
zwei Sprachversionen verteilt:

SetupCrypTool_1_3_en.exe Sprachversion nur englisch.
SetupCrypTool_1_3_de.exe Sprachversion nur deutsch.

Diese Archive enthalten die folgenden Dateien:

ReadMe-de.txt..... Kopie dieser Kurzanweisung (deutsch).
ReadMe-en.txt..... Kopie dieser Kurzanweisung (englisch).
CrypTool-de.cnt .. Indexliste f�r das Hilfesystem zu CrypTool
CrypTool-en.cnt .. Die englische Fassung von CrypTool-de.cnt
CrypTool.exe...... Das ausf�hrbare Programm.
aestool.exe....... Ein Programm, das Dateien in sich selbst
                   entpackende Programme verschl�sselt. Zur
                   Entschl�sselung m�ssen Sie das korrekte
                   Pa�wort eingeben.
CrypTool-de.hlp... Hilfesystem zu CrypTool mit Beispielszenarien.
CrypTool-en.hlp .. Die englische Fassung von CrypTool-de.hlp
EC-Param.ini...... Initialisierungsdatei f�r auf Elliptischen
                   Kurven basierende Public Key-Verfahren.
secude.dll........ Bibliothek kryptographischer Funktionen von der
                   SECUDE GmbH.
ticket............ Lizenz f�r die SECUDE-Bibliothek.
irunin.*.......... Diese Dateien sind n�tig f�r Installation und
                   Deinstallation von CrypTool.

script-de.pdf..... Ein Skript (deutsch) �ber Kryptographie,
                   Primzahlen, Zahlentheorie und die Mathematik
                   hinter einigen Algorithmen.
script-en.pdf..... Die englische Fassung von script-de.pdf
DialogSchwestern.pdf.... Fantasy-Geschichte von Dr. Elsner, in der
                         eine Variante des RSA-Kryptosystems 
                         beschrieben wird.

Referenztexte\.... Dieses Verzeichnis enth�lt Textdateien in den
                   Sprachen Deutsch, Englisch, Franz�sisch,
                   Spanisch und Latein. Diese Dateien werden
                   standardm��ig als Referenz f�r die Analyse von
                   Chiffretexten herangezogen.
                   Diese Dateien sind schreibgesch�tzt.

Referenztexte\deutsch.txt // Auszug aus dem Umsatzsteuergesetz
             \english.txt // Auszug aus der Agenda 21[UN-Dokument]
             \genesis-de.txt  // Buch Genesis in den Sprachen 
             \genesis-en.txt  // deutsch, englisch, franz�sisch,
             \genesis-fr.txt  // spanisch und lateinisch.
             \genesis-es.txt
             \genesis-lt.txt

Beispieldateien\.. Dieses Verzeichnis enth�lt unterschiedliche
                   Beispieldateien, die in den Szenarien verwendet
                   werden. Dateien mit der Endung ".txt" sind
                   Textdateien. Alle anderen Dateien sind bin�r.
                   Dateien mit dem Format "XX-enc-YY.*" sind
                   verschl�sselte Dateien. Bitte ver�ndern Sie
                   diese Dateien nicht, da sie in den
                   verschiedenen Szenarien der Hilfe verwendet
                   werden.

Beispieldateien\CrypTool.bmp
               \CrypTool-de.txt
               \CrypTool-en.txt
               \Playfair-enc-de.txt
               \probetext-de.txt
               \psion-enc.hex
               \vernam.txt

pse\.............. In diesem Verzeichnis und seinem
                   Unterverzeichnis pseca\ werden erzeugte
                   (asymmetrische) Schl�ssel und Zertifikate
                   abgelegt. Die folgenden Dateien sind f�r die
                   Verwaltung der Schl�sseldatenbank notwendig.

pse\pseca\calog
         \CA_exts
         \cert.dir
         \cert.pag
         \crls.dir
         \crls.pag
         \pseca
         \user.dir
         \user.pag

W�hrend der Laufzeit von CrypTool werden die folgenden Dateien
erzeugt und verwaltet:

CrypTool.GID...... Das Hilfesystem erzeugt und verwaltet diese
                   Datei.
cry*.*............ CrypTool schreibt tempor�re Dateien mit dem 
                   Namensmuster cry*.* in das Temp-Verzeichnis.
CrypTool.ini...... Diese Datei befindet sich im Windows-
                   Verzeichnis und enth�lt die Dateinamen der
                   zuletzt bearbeiteten Dateien.


4.1. �berpr�fen der Integrit�t der heruntergeladenen Dateien
     -------------------------------------------------------
Die Integrit�t von Dateien kann mit Hashwerten �berpr�ft
werden. Hashwerte sind wie Fingerabdr�cke: wenn man den 
Hashwert einer heruntergeladenen Datei neu berechnet und mit
den Werten auf der CrypTool-Homepage vergleicht, kann man
sehen, ob man eine Kopie der Originaldatei hat oder nicht. 
Weichen die Hashwerte voneinander ab, sollte man die Datei 
nochmal herunterladen und evtl. die Ursache daf�r suchen, dass
man eine ver�nderte Datei auf seinem Rechner hat.

a) Herunterladbare Dateien
Auf der Homepage von CrypTool www.cryptool.de finden Sie
die Hashwerte aller von der deutschen Seite direkt 
herunterladbaren Dateien in den Dateien md5sum.txt bzw. 
in sha1sum.txt.
Mit weit verbreiteten Tools wie MD5SUM und SHA1SUM kann
die �berpr�fung vorgenommen werden.

b) Auch die Dateien INNERHALB des heruntergeladenen 
Setup-Paketes k�nnen �berpr�ft werden. 
Dazu stehen deren Hashwerte hier im Readme:

XXXXXXXXXX             RIPEMD-160     SHA-1       MD5
Verzeichnis Cryptool:
aestool.exe
CrypTool-de.cnt
CrypTool-de.FTS
CrypTool-de.hlp
CrypTool.exe
deutsch.txt
DialogSchwestern.pdf
EC-Param.ini
english.txt
irunin.dat
irunin.ini
irunin.lng
ReadMe-de.txt
script-de.pdf
secude.dll
TEST-Param.ini
ticket

Verzeichnis cryptool\Beispieldateien:
CrypTool-de.txt
CrypTool.bmp
Playfair-enc-de.txt
probetext-de.txt
psion-enc.hex
vernam.txt

Verzeichnis cryptool\pse\pseca:
calog
CA_exts
cert.dir
cert.pag
crls.dir
crls.pag
pseca
user.dir
user.pag

Verzeichnis cryptool\Referenzdateien:
genesis-de.txt
genesis-en.txt
genesis-es.txt
genesis-fr.txt
genesis-lt.txt

Zur �berpr�fung k�nnen Sie die oben genannten Tools verwenden
oder das Programm CrypTool selbst.

Ab Version 1.3.01 kann man die Hashwerte von "externen"
Dateien berechnen lassen, ohne sie in CrypTool zu laden:
- Men� Einzelverfahren / Hashwerte / Hashwert einer Datei...
- �ffnen der entsprechenden Datei
- Vergleich mit dem Wert hier (richtiger Hashalgorithmus!).

Aus Sicherheitsgr�nden empfiehlt sich der Vergleich bei 
Bin�rdateien (EXE, DLL, PDF, ...), wenn Sie nicht ganz sicher
sind, dass Ihr Rechner unber�hrt ist.




5. Wie Sie starten...
   ------------------
Wenn Sie CrypTool starten, �ffnen sich zugleich die Arbeitsfl�che
von CrypTool und im Vordergrund ein kleines Begr��ungsfenster,
von dem aus Sie auch sofort auf die Einstiegsseite der Hilfe
verzweigen k�nnen.
Lesen Sie die Hinweise und Tips der Hilfe-Einstiegsseite und
�ffnen Sie dann auf der CrypTool-Arbeitsfl�che eine
unverschl�sselte Datei aus dem Unterverzeichnis "Beispieldateien".
Sie k�nnen jetzt viele der Funktionen von CrypTool an dieser Datei
ausprobieren.

Einen schnellen Einstieg in CrypTool finden Sie, wenn Sie einige
Szenarien der Hilfe durchspielen (die Szenarien stehen im
Inhaltsverzeichnis der Hilfe unter "Beginn der Arbeit mit
CrypTool").

Wir w�nschen viel Spa� beim Ausprobieren der vielen Funktionen von
CrypTool.



6. Neuerungen in CrypTool 1.3.00
   -----------------------------
Seit CrypTool 1.202 (Dez. 2000) kamen folgende Erweiterungen und
Bugfixes hinzu:
- CrypTool ist nun komplett in gleicher Weise in deutsch und
  englisch.
- Alle Dialoge wurden im Hinblick auf Konsistenz und
  Verst�ndlichkeit �berarbeitet.
- Die bisherigen Einschr�nkungen (maximale Datengr��e 64 Kb) f�r
  die Windows-Versionen Win95 und Win98 wurden aufgehoben.
- die letzte Einstellung zu einem Verfahren (wie gew�hlter
  Schl�ssel oder Alphabet) wird Programm-intern aufbewahrt.

6.1. Klassische Verfahren
     --------------------
+ Homophone Verschl�sselung neu
+ Permutationsverschl�sselung neu
+ Zufallsdaten erzeugen neu
  Die folgenden "Pseudozufallsgeneratoren" werden angeboten:
  - der von der SECUDE-Lib bereitgestellte Zufallsgenerator
  - ein durch den Parameter N einzustellender "x^2 mod N"
    Zufallsgenerator
  - Linearer Kongruenz-Generator
  - Inverser Linearer Kongruenz-Generator
+ Statistische Analysen f�r Zufallsdaten (z.B. FIPS-140-1) neu
+ Periodenanalyse verbessert
+ N-Gramm-Analyse erg�nzt (mit der M�glichkeit, die Ergebnisse
  abzuspeichern)
  Die N-Gramm Analyse ist f�r Bin�rdateien auf 64 kBytes und f�r
  Textdateien auf 256 kBytes beschr�nkt (l�ngere Eingaben werden
  auf die maximale Eingabel�nge gek�rzt).
+ Fehler bei Vigenere und Caesar behoben (beliebige Textdateien)
+ Playfairanalyse verbessert

6.2. Symmetrische Verfahren
     ----------------------
+ ein eigenst�ndiges Programm kann selbstentpackende Programme
  erzeugen.
  Damit kann man eine beliebige Datei Pa�wort-gesch�tzt mit AES
  verschl�sseln (durch Eingabe eines Hexadezimal-Schl�ssels).
+ Veranschaulichen, wie ein Schl�ssel aus einem Pa�wort nach
  PKCS#5 generiert wird [aus der Texteingabe (Pa�wort) wird ein
  Hexadezimal-Schl�ssel erzeugt, der gegen W�rterbuchangriffe
  resistent ist. Parameter: Ausgabe-Schl�ssell�nge, Saat f�r den
  Zufallsgenerator, Anzahl der "Hash"-Iterationen,
  Hashverfahren (MD2, MD5, SHA-1)].

6.3. Asymmetrische Verfahren
     -----------------------
+ Demo zur Zahlentheorie und zum RSA-Verfahren neu
   - Primzahlen generieren
   - Zahlen (schrittweise) und mit verschiedenen Verfahren
     faktorisieren
   - das RSA-Kryptosystem transparent durchf�hren (auch f�r
     selbst-gew�hlte Primzahlen) (damit kann auch der "Dialog
     der Schwestern" aus der c't 25/1999 nachvollzogen werden)

6.4. Formatierung / Anzeige / Navigation
     -----------------------------------
+ intern werden die Keys/Eigenschaften aller Verfahren
  getrennt gespeichert. Speicherung und Abruf der dabei
  eingegebenen Schl�ssel erfolgt �ber 2 Buttons. Dadurch
  wird die Wiederverwendung deutlich einfacher, wenn
  wie in klassischen Verfahren wie Playfair sehr spezifische
  Formate verwendet werden.
+ Das Umschalten von Hexanzeige nach Textanzeige f�r
  Nicht-Textdateien ist unterbunden.
+ Beim Anzeigewechsel das "Vater"-Fenster beibehalten.
+ Hotkeys zur Verzweigung in das PDF-Skript eingef�gt.

6.5. Hilfe / PDF-Skript
     --------------------
+ Erg�nzung des Skripts um eine Einf�hrung in die elementare
  Zahlentheorie mit vielen Beispielen.

6.6. Sonstiges
     ---------
+ PKCS#12-Export und -Import von RSA- und DSA-PSEs und damit
  von den darin gespeicherten Schl�sseln. 
+ Neue Webseite
   - zus�tzliche Infos: Pr�sentation auf deutsch und englisch.


6.7. �nderungen von Version 1.3.00 zu Version 1.3.01
     -----------------------------------------------
Source:
+ �berarbeitung des Quelltextes f�r die �bergabe an den neuen
  Maintainer.
+ Weitere Automatisierung beim Erzeugen des Setup-Paketes
Webseite:
+ Enth�lt die Hashwerte der herunterladbaren Dateien und
  erm�glicht so einen Check der Integrit�t der auf dem
  Computer befindlichen Dateien.
Dokumentation:
+ Einheitliche CrypTool-Pr�sentation zu 1.3.01 (keine Trennung
  mehr in Features von 1.2.xx und Neuerungen in 1.3.xx).
+ Online-Hilfe verbessert und erweitert (z.B. Hilfe f�r die
  neuen Funktionen und Einbau einer Zeittafel).
Funktionalit�t:
+ Ist ein Men�eintrag selektiert, der noch ein Untermen� hat,
  und man dr�ckt F1, gelangt man nun auf die entsprechende
  Hilfeseite der Online-Hilfe zum ganzen Men�.
+ Hashwerte von Dateien berechnen, ohne sie zu laden.
+ Visualisierung der einzelnen Schritte / Abh�ngigkeiten bei
  der Hybridverschl�sselung und -Entschl�sselung.
+ Die schrittweise Verifikation einer RSA-Signatur ist nun auch
  m�glich (dabei werden wie bei der Visualisierung der Hybrid-
  Entschl�sselung die schon vorhandenen Masken wiederverwendet).
+ Verbesserung bei der Faktorisierung zusammengesetzter Zahlen:
   - Ausgabe der Details pro abgespaltenem Faktor.
   - Abfangen, wenn das Quadratic Sieve-Verfahren f�r die
     gegebene Zahl mehr Speicher braucht als verf�gbar ist.
+ Erweiterung der Funktionalit�t im RSA-Kryptosystem
  - interaktive Nutzung der Faktorisierung, wenn nur die
    �ffentlichen Parameter bekannt sind,
  - Eingabe von Hexwerten m�glich.
+ Verbesserungen beim AES-Tool.
+ Bei der Hillverschl�sselung k�nnen die Details zur aktuellen 
  Schl�sselmatrix in einer Textdatei ausgegeben werden:
  - das aktuell in Optionen/Textoptionen gew�hlte Alphabet,
  - die Hill-Schl�sselmatrix, auch kodiert in Zahlen und 
  - eine Beispiel-Ver-/Entschl�sselung, berechnet im Detail. 
+ Langfassung des "Dialoges der Schwestern" in Deutsch und
  Englisch beigelegt (darin wird ein in der RSA-Demo 
  behandelter Sonderfall des RSA-Verfahrens beschrieben) 
  - vielen Dank an den Autor, Herrn Dr. Carsten Elsner.
+ Visualisierung 
  - der einzelnen Schritte / Abh�ngigkeiten bei der
    Erzeugung einer elektronischen Signatur.


6.8. Geplante �nderungen von Version 1.3.01 zu Version 1.3.02
     --------------------------------------------------------
Funktionalit�t:
+ Visualisierung 
  - der Wirkung von Text�nderungen auf den Hashwert 
    (Sensitivit�t von Hashverfahren)


7. M�gliche Punkte f�r eine Weiterentwicklung
   ------------------------------------------
+ Weitere Algorithmen zu jedem Thema der Verschl�sselung oder
  Analyse hinzuf�gen, 
  z.B. ADFGVX bei den klassischen Verfahren,
  RC5 und Ghost bei den symmetrischen Verfahren oder 
  Rabin bei den Public Key-Verfahren.
+ wo immer Algorithmen parametrisiert werden k�nnen: Anbieten
  einer Option, um z.B. den Initialisierungsvektor, die Anzahl
  von Runden, die Schl�ssel- oder Wortl�nge oder das Padding
  zu setzen. Dies muss dann als Beschreibung dieses speziellen
  Algorithmus in den internen Schl�sselspeicher aufgenommen
  werden (z.B. f�r den RC5-Algorithmus - siehe RFC 2040).
+ W�rterbuch f�r alle Angriffe benutzen, nicht nur f�r die
  Substitution.
+ Einbau von normierter Mustersuche
+ Analyse neu 
  - der homophonen Verschl�sselung
  - f�r asymmetrische Kryptoverfahren.
+ Analyse verbessern (nicht performant und stark genug bisher)
  - der monoalphabetischen Substitution
  - der Playfair-Verschl�sselung
+ Alle Anzeigemodule in einem konsistenten Klassenbaum
  zusammenfassen.
+ Die Sourcen so umstellen, da� die Ausgabe/Anzeige komplett von 
  den Kryptomodulen getrennt ist (erleichtert Portierungen und
  Fehlersuche)
+ In der Anzeige f�r Grafiken eine Vergr��erungsfunktion einbauen
  und / oder die Koordinaten anzeigen, an denen sich die Maus
  befindet.
+ Korrekturm�glichkeit einzelner Zeichen bei der Analyse von XOR,
  ADD, Vigenere.
+ Anzeigen des zweit-, dritt-, ... -besten Treffers bei der
  XOR/ADD Analyse (dies kann zu einer k�rzeren Schl�ssell�nge
  f�hren).
+ Autokorrelation: vor der �berlagerung noch Operationen auf den
  Bl�cken ausf�hren (XOR, ADD, ...); macht das Sinn?
+ Editieren der Homophonen-Schl�ssel (wird insbesondere
  zur Analyse der Homophonen Verschl�sselung ben�tigt).
+ Bei gleitender Entropie: Automatische Anzeige der
  entsprechenden Stellen mit hoher Entropie.
+ Hillverfahren: Schl�sselmatrix transponieren.
+ Hillverfahren: Eingabe von Zahlen in die Schl�sselmatrix.
+ Update der Miracl-Lib auf eine neuere Version als 4.4.3.
+ Portierung nach Linux (eine SECUDE-Lib bzw. Miracl-Lib stehen
  zur Verf�gung).
+ Portierung nach Java (eine SECUDE-Lib daf�r steht zur
  Verf�gung).
+ Diffie-Hellman Schl�sselaustausch visualisieren.
+ Kryptographisch starke elliptische Kurven erzeugen und damit
  Implementierung eines auf Elliptischen Kurven basierenden
  Kryptosystems. Dazu k�nnte man das Kryptosystem von Menezes
  und Vanstone nehmen, das 1993 von diesen Autoren vorgeschlagen
  wurde: A. Menezes and S. Vanstone,
         "Elliptic curve cryptosystems and their implementation",
         Journal of Cryptology, 6 (1993), Seiten 209-224.
+ Weil kryptographische Strukturen und Formate h�ufig ASN.1-
  kodiert sind: Integration eines ASN.1 Dekodier-Tools. 
+ Angriff auf Hash-Verfahren basierend auf dem "Geburtstags 
  Paradoxon".
+ Generell Visualisierung der Abh�ngigkeiten und Abl�ufe bei
  Protokollen (nicht nur bei "einfachen" Algorithmen).
+ Erweiterung um die deutschen Standards zur Validierung von 
  Zufallszahlen.
+ Weitere Standards implementieren und direkt �ber die Men�s
  bzw. aus der Online-Hilfe an alle Stellen verzweigen, wo diese
  Standardverfahren verwendet werden (Hauptarbeit UI und Doku).
+ CrypTool als Frontend f�r zahlentheoretische Funktionen und 
  Werte erweitern.


7.1 Sinnvolle Aufgaben f�r die Einarbeitung des neuen Maintainers
     ------------------------------------------------------------
+ Einbau des RC5-Algorithmus wie oben beschrieben, um zu sehen,
  an welchen Stellen �berall die Sourcen daf�r zu erg�nzen sind.
+ alle m�glichen Arten von Transpostionen f�r den Inhalt von
  Textfenstern in einem ansprechenden Dialog anbieten.
+ Testbett mit Beispielen und L�sungen erzeugen, damit man das
  Testen automatisieren kann und man sicherstellt, dass Programm-
  �nderungen nicht alte Funktionalit�t negativ beeinflussen:
  a) Interface, um Testaufgaben manuell in Dialogboxen zu laden
  b) Schnittstelle schaffen, mit der sich die Testaufgaben aus
     einer Datei selbst in die Dialogboxen laden.
     Vielleicht sogar Script-Steuerung f�r alle Dialoge oder
     automatische Testtool vom Markt einsetzen.
  c) Commandline-Interface schaffen (am besten nachdem Krypto und
     Anzeige im Code getrennt wurden), das ohne Dialogboxen alle
     Aufgaben aus einer Datei per Schnittstelle ausliest und die
     L�sungen wieder in eine Datei schreibt:
     -> Abgleich automatisierbar
     -> neue Version leichter testbar.




8. Kurze Historie der Hauptversionen
   ---------------------------------

Version         Datum
1.0.01          Okt. 1999
1.1.01          Mai  2000
1.2.00          Aug. 2000
1.2.02          Dez. 2000
1.3.00          Jan. 2002
1.3.01x         Apr. 2002
1.3.02          Juni 2002 (Plan)



9. Roadmap
   -------
Wann die neue CrypTool-Version 1.4 kommt, entscheidet der neue
Maintainer.

Dann ist auch geplant ist, die Sourcen von CrypTool als Open
Source f�r die Internet-Gemeinschaft freizugeben.



10. Feedback bei Fehlern
   ---------------------------
Sollten Sie Probleme haben oder Fehler finden, wenden Sie sich
bitte mit einer Beschreibung des Problems per e-mail an
- joerg-cornelius.schneider@db.com  oder
- bernhard.esslinger@db.com / besslinger@web.de

F�r Anregungen jeglicher Art bez�glich CrypTool sind wir immer
dankbar.
Auch w�rden wir uns freuen, wenn Sie uns mitteilen, wie und wo Sie
CrypTool einsetzen.



11. Kontaktadressen
    ---------------
- joerg-cornelius.schneider@db.com
- bernhard.esslinger@db.com
- besslinger@web.de
- henrik.koy@db.com
- peer.wichmann@fzi.de



12. Verweise
    --------
12.1. Wirtschaftswoche Spezial
      ------------------------
In dem Spezial "Kryptographie" der Wirtschaftswoche finden Sie ein
Preisausschreiben: "Knacken Sie den Text!". Das Preisausschreiben
erhalten Sie unter der URL
http://wiwo.de/WirtschaftsWoche/Wiwo_CDA/0,1702,12723_47642,00.html
Wenn Sie sich an die Tipps der Aufgabenstellung halten, knacken
Sie mit CrypTool die Aufgabe in wenigen Mausklicks.

12.2. c't 14/2001, S. 204-208
      -----------------------
In diesem renommierten und auflagenstarken deutsch-sprachigen
Computermagazin wurde im Juli 2001 ein 5-seitiger Artikel zu
CrypTool ver�ffentlicht.
Au�erdem wurde in c't 25/1999 die Fantasy-Geschichte
"Der Dialog der Schwestern" ver�ffentlicht. Die darin verwendete
Variante von RSA kann mit CrypTool v1.3.00 nachvollzogen werden.

12.3. BSI B�rger-CD "Ins Internet - mit Sicherheit"
      ---------------------------------------------
Das Bundesamt f�r Sicherheit in der Informationstechnik (BSI) hat
zusammen mit dem Deutschen Bundesinnenministerium zur CeBIT 2002
eine CD ver�ffentlicht, die die B�rger aufkl�rt, wie man mit
Computer und Internet umgeht und wie man sich sicher im Internet
bewegen kann.
Auf dieser CD ist auch CrypTool enthalten, um das Verst�ndnis der 
kryptographischen Sicherheitsfunktionen zu verbessern.
Von dieser CD sind mehr als 500.000 St�ck produziert worden.

12.4. Freeware-Projekt Crank
      ----------------------
http://freshmeat.net/projects/crank/

Crank wurde im Januar 2001 von Matthew Russell begonnen und unter
der GNU General Public Licence (GPL) freigegeben.
Im Crank-Projekt soll unter Linux ein Programm mit graphischer
Oberfl�che erstellt werden, das das m�glichst automatisierte
Brechen von klassischen Kryptoalgorithmen erm�glicht.
Initial liegt der Fokus auf der Analyse monoalphabetischer
Substitutions-Chiffren und der Entwicklung generischer und
flexibler Analysetools.
Auf dieser Seite gibt es auch einige sehr interessante Links �ber
klassische Kryptoanalyse.




13. Anhang
    ------

13.1. CrypTool unter Linux mit Wine
13.1.1. ......... CrypTool installieren
13.1.2. ......... Wine-Konfiguration
13.1.3. ......... CrypTool ausf�hren



13.1. CrypTool unter Linux mit Wine
      -----------------------------

Diese Hinweise basieren auf Tests mit Wine 2001-11-29.

13.1.1 CrypTool installieren
       ---------------------
Im letzten Schritt der Installation gibt es die Option,
CrypTool gleich zu starten. Dies funktioniert unter Wine nicht.
Bitte starten Sie CrypTool wie unten beschrieben.


13.1.2 Wine-Konfiguration
       ------------------
CrypTool funktioniert nicht mit der in Wine eingebauten Version
von riched32.dll. Wenn Sie unter CrypTool eine Datei �ffnen und
die falsche Version von riched32.dll benutzt wird, erscheint ein
leeres Fenster.
Wahrscheinlich taucht das Problem nicht auf, wenn Wine eine
existierende Windows-Partition benutzen kann.
Wenn Sie Wine ohne Windows benutzen, k�nnen Sie das Problem mit 
folgenden Schritten l�sen:
 - installieren sie CrypTool unter Wine.
 - besorgen Sie sich riched32.dll (z.B. Version 5.0.1458.47).
   und kopieren Sie die Datei in das Installationsverzeichnis
   von CrypTool. Evtl. m�ssen sie analog mit weiteren DLLs,
   verfahren, die von riched32.dll benutzt werden. Beachten Sie 
   bitte die Fehlerausgaben von Wine.
 - Konfigurieren Sie Wine so, dass es diese Datei nutzt. In der
   Standard-Konfiguration ist das so. Funktioniert das bei
   Ihnen nicht, schreiben Sie folgende Zeile in die
   [DllOverrides]-Sektion der Wine-Konfigurationsdatei:
   "riched32" = "native,builtin"


13.1.3 CrypTool ausf�hren
       ------------------

13.1.3.1 Starten
         -------
Um CrypTool zu starten, wechseln Sie in das Verzeichnis, in das
es installiert wurde, und starten es mit:

$ wine CrypTool

Wenn Sie vor dem Aufruf nicht in das Installationsverzeichnis
von CrypTool wechseln, findet CrypTool einige wichtige Dateien
nicht.


13.1.3.2 Bugs und Work-arounds
         ---------------------
* Die Online-Hilfe kann nicht mit F1 aus CrypTool heraus
  aufgerufen werden.
  Mit der folgenden Kommandozeile k�nnen Sie die Online-Hilfe
  anzeigen:

  $ wine winhlp32 CrypTool.hlp

