==================================================================
    CrypTool, Version 1.3.04, Mai 2003
    (c) Deutsche Bank AG 1998-2003, Frankfurt am Main
    (c) Universit�t Siegen und Darmstadt
    $Id$
==================================================================

                       Inhalt

 1. .... Kurzbeschreibung des CrypTool-Paketes
 1.1. .... Wie Sie am besten starten - Der Einstieg in CrypTool
 1.2. .... Was beinhaltet die Distribution?
 1.3. .... Danke
 1.4. .... Neuer Maintainer in Zukunft - Roadmap
 2. .... Beschr�nkungen und Voraussetzungen
 2.1. .... Installation unter Windows 95
 2.2. .... Interaktive Online-Hilfe unter Windows XP
 2.3. .... Unterst�tzung verschiedener Sprachen
 2.4. .... Einschr�nkungen in den verwendeten Bibliotheken
 3. .... Installation
 4. .... Dateiliste
 4.1. ..   �berpr�fen der Integrit�t der heruntergeladenen Dateien
 5. .... Neuerungen in CrypTool bis 1.3.04
 5.1. .... �nderungen von Version 1.2.02 zu Version 1.3.00
 5.1.1. .... Klassische Verfahren
 5.1.2. .... Symmetrische Verfahren
 5.1.3. .... Asymmetrische Verfahren
 5.1.4. .... Formatierung / Anzeige / Navigation
 5.1.5. .... Hilfe / PDF-Skript
 5.1.6. .... Sonstiges
 5.2. .... �nderungen von Version 1.3.00 zu Version 1.3.04
 5.3. .... Geplante �nderungen nach Version 1.3.04
 6. .... M�gliche Punkte f�r eine Weiterentwicklung
 6.1. .... Sinnvolle Aufgaben f�r die Einarbeitung des neuen Maintainers
 7. .... Kurze Historie der freigegebenen Hauptversionen
 8. .... Feedback bei Fehlern
 9. .... Kontaktadressen
10. .... Verweise
10.1. .... Wirtschaftswoche Spezial
10.2. .... c't 14/2001, S. 204-208
10.3. .... DuD Oktober 2002
10.4. .... BSI B�rger-CD "Ins Internet - mit Sicherheit"
10.5. .... Freeware-Projekte Crank, CAP, CryptAid, etc.
11. .... Anhang
11.1. .... CrypTool unter Linux mit Wine



1. Kurzbeschreibung des CrypTool-Paketes
   -------------------------------------
Dieses Readme geh�rt zur kostenlosen Distribution von CrypTool,
einem Programm, mit dem man kryptographische Funktionen leicht
demonstrieren, aber auch bekannte und unbekannte Verfahren
analysieren kann.

Zu jedem Programmteil gibt es reichhaltige Online-Hilfe, die auch
ohne tiefes Kryptowissen verstanden werden kann.

CrypTool ist komplett in Deutsch und Englisch vorhanden.

Vorausgesetzt wird, dass der Benutzer mit Anwendungen in einer
Windows-Umgebung umgehen kann.

Die jeweils aktuelle Version von CrypTool finden Sie unter den
Internet-Adressen:  http://www.CrypTool.de
                    http://www.CrypTool.com
                    http://www.CrypTool.org

Seit Anfang 2002 bewegt sich die Downloadrate bei rund 800
CrypTool-Paketen pro Monat -- mit wachsender Tendenz.

Ziel von CrypTool ist es, kryptographische Mechanismen anschaulich
zu machen und die Verwendung und die Grenzen einzelner Mechanismen
aufzuzeigen. In CrypTool sind fast alle State-of-the-art-Krypto-
funktionen implementiert. Dies erm�glicht einen "spielerischen"
Einstieg in die moderne und klassische Kryptographie -- unter
einer einheitlichen Oberfl�che.

CrypTool wird eingesetzt
- in Unternehmen sowohl zur Mitarbeiter-Sensibilisierung bez�glich
  IT-Sicherheit (Awareness) als auch zur Ausbildung,
- im Schulunterricht und
- in der Lehre an mehreren Hochschulen.

Bitte beachten Sie die Lizenz- und Nutzungsbestimmungen f�r
CrypTool. Diese werden bei der Installation und auf der
Einstiegsseite der Online-Hilfe erl�utert.


1.1. Wie Sie am besten starten - Der Einstieg in CrypTool
     ----------------------------------------------------
Beim Start von CrypTool �ffnen sich zugleich die Arbeitsfl�che
von CrypTool und im Vordergrund ein kleines Begr��ungsfenster.
Wenn Sie hier die F1-Taste dr�cken, erscheint die Startseite der
Online-Hilfe.
Diese Startseite ist ein guter Ausgangspunkt, um alle wesentlichen
Inhalte von CrypTool kennen zu lernen (z.B. mit Hilfe der Links auf
dieser Startseite).

Lesen Sie die Hinweise und Tipps der Hilfe-Startseite und
�ffnen Sie dann auf der CrypTool-Arbeitsfl�che eine
unverschl�sselte Datei aus dem Unterverzeichnis "examples".
Sie k�nnen jetzt viele der Funktionen von CrypTool an dieser Datei
ausprobieren.

Einen schnellen Einstieg in CrypTool finden Sie, wenn Sie einige
Szenarien (Tutorials) der Online-Hilfe durchspielen (die Szenarien
stehen im Inhaltsverzeichnis der Hilfe unter "Beginn der Arbeit
mit CrypTool").

Wir w�nschen viel Spa� beim Ausprobieren der Funktionen von
CrypTool.


1.2. Was beinhaltet die Distribution?
     --------------------------------
Das CrypTool-Paket enth�lt die folgenden vier Hauptbestandteile:

(1) Das Programm CrypTool
-------------------------
Hauptteil des CrypTool-Paketes ist das Programm CrypTool selbst.
Entwicklungsziel von CrypTool war nicht, dass damit im Wirkbetrieb
Daten verschl�sselt oder anderweitig gesichert werden sollten. 
Es ist eine Demonstration, die vor allem f�r Ausbildungszwecke
eingesetzt wird:

- In CrypTool ist eine umfangreiche Sammlung kryptographischer
  Algorithmen implementiert, die hervorragend dokumentiert ist.
  Somit ist CrypTool sehr gut geeignet zur Ausbildung und zur
  Mitarbeiter-Sensibilisierung f�r IT-Sicherheit.

- Die meisten der kryptographischen Basisalgorithmen stammen von:
  - der Industrie-bew�hrten Secude-Bibliothek (Version 5.4.15)
    (www.secude.com) und von
  - der Miracl-Bibliothek (Version 4.4.3)
    (http://indigo.ie/~mscott/).
  Somit ist CrypTool auch eine hervorragende Referenzimplemen-
  tierung.

- Die Kryptoanalyse der meisten der klassischen Verfahren ist
  automatisiert.
  Die Analyse der modernen Verfahren ist eingeschr�nkt, so dass
  CrypTool nicht als Hackertool eingesetzt werden kann.

(2) Dokumentation
-----------------
Zum Programm geh�rt eine umfangreiche Dokumentation, die aus vier
Teilen besteht:
a) Readme-Datei (diese Datei),
b) Online-Hilfe
   - Kontext-bezogen zur Bedienung des Programms und mit
     weiterreichenden Erl�uterungen,
   - Demos bzw. Beispiel-Szenarien (hier werden Einzelverfahren
     Schritt f�r Schritt erl�utert)
c) Skript (zum Thema Kryptographie, beigelegt als PDF-Datei),
d) Pr�sentation, die auf Folien die M�glichkeiten von CrypTool
   kurz aufzeigt (beigelegt als PDF-Datei).

(3) Das Programm AES-Tool
-------------------------
Zum Erstellen selbstentpackender Executables ist in CrypTool ein
Programm integriert, das auch eigenst�ndig benutzt werden kann.
Darin wird aus einem Passwort ein Session-Key erzeugt, mit dem
ein beliebiger Dateiinhalt AES-verschl�sselt wird.
Dieses Verschl�sselungstool kann sowohl als Fenster als auch von
Kommandozeile (z.B. aus einer Batchdatei) aufgerufen werden.

(4) Die Geschichte "Der Dialog der Schwestern" als PDF-Datei
------------------------------------------------------------
Hierin wird eine Variante des RSA-Verfahren von den Titelheldinnen
benutzt, um verschl�sselt zu kommunizieren.

Alle Einzeldateien, die bei der Installation des CrypTool-Paketes
auf Ihre Platte kopiert werden, sind in Kapitel 4 (unten in diesem
Readme) aufgef�hrt.



1.3. Danke
     -----
Zu CrypTool haben viele verschiedene Personen beigetragen -
insbesondere auch in ihrer Freizeit (einige sind in der Dialogbox
zu sehen, die man erh�lt, wenn man in der Dialogbox "�ber CrypTool"
einen Doppelklick ausf�hrt). Herzlichen Dank.

Dr. Carsten Elsner erlaubte uns, seine Geschichte "Der Dialog der
Schwestern" als PDF-Datei beizulegen.
Diese Geschichte wurde in dem Computermagazin c't 25/1999
ver�ffentlicht. W�hrend in der c't 25/99 eine etwas gek�rzte Fassung
ver�ffentlicht wurde, liegt hier die Originalfassung bei.
Der Verfasser, als alleiniger Inhaber aller Rechte an dem Werk,
r�umt dem CrypTool-Maintainer das ausschlie�liche Vervielf�lti-
gungs- und Verbreitungsrecht ein. Die Geschichte darf nur zusammen
mit dem CrypTool-Paket verbreitet werden.

Die Firmen Secude GmbH und Shamus Software Ltd. (siehe oben) gestatteten
uns gro�z�gigerweise, ihre Krypto-Bibliotheken zu nutzen.
Diese mit CrypTool verteilten Bibliotheken d�rfen nicht in einem
Kontext au�erhalb CrypTool benutzt werden, ohne vorher die erw�hnten
Firmen zu kontaktieren und nach ihren aktuellen Lizenzbedingungen zu
fragen.


1.4. Neuer Maintainer in Zukunft - Roadmap
     -------------------------------------
Wie geplant hat CrypTool ein akademisches Zuhause erhalten, wo
es in Zukunft als Open Source weitergepflegt wird.

Die bisherigen Sponsoren von CrypTool waren die Deutsche Bank AG,
Secude GmbH und FZI Karlsruhe. 1.3.04 ist voraussichtlich die letzte
Version, die die Deutsche Bank als Maintainer herausbringt.

Ab Oktober 2002 hat der Lehrstuhl Sicherheit in der Informations-
technik, Fachbereich Informatik unter Frau Prof. Dr. Claudia
Eckert an der TU Darmstadt die Rechte an CrypTool.
Sie machen die Sourcen von CrypTool als Open Source f�r die 
Internet-Gemeinschaft verf�gbar.

Die Homepage von CrypTool bleibt weiterhin www.cryptool.de.

Wir w�rden uns sehr freuen, wenn sich nicht nur die bisherigen
Entwickler, sondern auch viele neue an der Weiterentwicklung von
CrypTool beteiligen. Ideen dazu finden Sie in Kapitel 5.3 und 6. 



2. Beschr�nkungen und Voraussetzungen
   ----------------------------------
CrypTool erfordert eine Win32 Umgebung, wie sie unter Windows 95,
Windows 98, Windows Me, Windows NT (ab 4.0), Windows 2000 und
Windows XP gegeben ist.

CrypTool funktioniert grunds�tzlich auch unter FreeBSD/Linux mit
Wine (mit Abstrichen an Funktionalit�t und Stabilit�t).
Siehe Anhang 11.1.


2.1. Installation unter Windows 95
     -----------------------------
Bei �lteren Windows 95 Systemen erhalten Sie beim Aufruf von
CrypTool die Meldung "Kann 'secude.dll' nicht finden". In diesem
Fall k�nnen Sie CrypTool nur eingeschr�nkt nutzen.

Die Algorithmen der Secude-Bibliothek werden beim Start von
CrypTool mit Hilfe der Bibliothek "msvcrt.dll" dynamisch geladen.

Die Datei "msvcrt.dll" wird standardm��ig mit Windows 98,
Windows NT etc. ausgeliefert, aber nicht mit Windows 95.
Zum Lieferumfang verschiedener Anwendungs-Programme geh�rt eine
(nicht immer ausreichend neue) Version von "msvcrt.dll".
Kopieren Sie diese Datei in das Windows-Verzeichnis oder in das
Verzeichnis von CrypTool.
Alternativ k�nnen Sie eine selbstentpackende Datei von Microsoft
herunterladen, die "msvcrt.dll" enth�lt:
    ftp://ftp.microsoft.com/softlib/mslfiles/msvcrt.exe
Speichern Sie diese Datei in einem tempor�ren Verzeichnis und
extrahieren Sie die Dateien durch Doppelklick. Weitere
Anweisungen stehen in der dort mitgelieferten Readme-Datei.


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

Workaround anhand eines Beispiels: Einzelverfahren \ RSA-Demo
Wenn hier das Untermen� zu "RSA-Demo" aufklappt, Sie aber die
Hilfe zum Men�eintrag "RSA-Demo" haben wollen, m�ssen Sie - nur
unter Windows XP - das Untermen� von "RSA-Demo" erst mit Escape
(Esc) oder den Pfeiltasten wieder einklappen, dann funktioniert
das Aufrufen der Online-Hilfe mit F1 auch unter Windows XP.


2.3. Unterst�tzung verschiedener Sprachen
     ------------------------------------
Programm, Hilfesystem und Dokumentation sind mehrsprachig aus-
gelegt (zur Zeit englisch und deutsch).

F�r jede unterst�tzte Sprache gibt es ein eigenes Setup (der
Versuch, alle Sprachen in ein einziges Executable einzubinden
wurde wieder aufgegeben, da die automatische Spracheinstellung
beim Anwender (anhand seiner Systemeinstellungen) nur unter
Windows 4.0, nicht aber unter Win9x, korrekt funktionierte).


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
  Ab Version 1.3.00 k�nnen Sie alternativ RSA- und DSA-PSEs
  als PKCS#12-Struktur exportieren bzw. importieren.

F�r den Fall, dass mehrere Benutzer dieselbe CrypTool-
Installation verwenden wollen, m�ssen die Zugriffsrechte auf den
Verzeichnissen pse\ und pse\pseca\ und den darin enthaltenen
Dateien f�r alle Benutzer auf Vollzugriff gesetzt werden.

Der Teilbaum "pse\" sollte nicht manuell bearbeitet werden, da
bei einer inkonsistenten Struktur nur eine Neuinstallation von
CrypTool bleibt.



4. Dateiliste
   ----------
CrypTool wird als komprimiertes, selbstextrahierendes Archiv in
zwei Sprachversionen verteilt:

SetupCrypTool_1-3-04_en.exe    Englische Sprachversion.
SetupCrypTool_1-3-04_de.exe    Deutsche Sprachversion.

Diese Archive enthalten die folgenden Dateien:

ReadMe-de.txt..... Kopie dieser Kurzanweisung (deutsch).
ReadMe-en.txt..... Kopie dieser Kurzanweisung (englisch).
CrypTool-de.cnt .. Indexliste f�r das Hilfesystem zu CrypTool.
CrypTool-en.cnt .. Die englische Fassung von CrypTool-de.cnt.
CrypTool.exe...... Das ausf�hrbare Programm.
aestool.exe....... Ein Programm, das Dateien in sich selbst
                   entpackende Programme verschl�sselt. Zur
                   Entschl�sselung m�ssen Sie das korrekte
                   Passwort eingeben.
CrypTool-de.hlp... Hilfesystem zu CrypTool mit Beispielszenarien.
CrypTool-en.hlp .. Die englische Fassung von CrypTool-de.hlp
EC-Param.ini...... Initialisierungsdatei f�r auf Elliptischen
                   Kurven basierende Public Key-Verfahren.
secude.dll........ Bibliothek kryptographischer Funktionen von der
                   Secude GmbH.
ticket............ Lizenz f�r die Secude-Bibliothek.
libeay32.dll...... Bibliothek aus OpenSSL 0.96.
irunin.*.......... Diese Dateien sind n�tig f�r Installation und
                   Deinstallation von CrypTool.

script-de.pdf..... Ein Skript (deutsch) �ber Kryptographie,
                   Primzahlen, Zahlentheorie und die Mathematik
                   hinter einigen Algorithmen.
script-en.pdf..... Die englische Fassung von script-de.pdf.
CrypToolPresentation_1_3_04_de.pdf... Folien-Pr�sentation
CrypToolPresentation_1_3_04_en.pdf... Englische Fassung der Pr�s.
DialogSchwestern.pdf.. Fantasy-Geschichte von Dr. Elsner, in der
                       eine Variante des RSA-Kryptosystems
                       beschrieben wird.
DialogueSisters.pdf... Englische Fassung von DialogSchwestern.pdf.

references\....... Dieses Verzeichnis enth�lt Textdateien in den
                   Sprachen Deutsch, Englisch, Franz�sisch,
                   Spanisch und Latein. Diese Dateien werden
                   standardm��ig als Referenz f�r die Analyse von
                   Chiffretexten herangezogen.
                   Diese Dateien sind schreibgesch�tzt.

references\deutsch.txt // Auszug aus dem dt. Umsatzsteuergesetz
          \english.txt // Auszug aus der Agenda 21[UN-Dokument]
          \genesis-de.txt  // Buch Genesis in den Sprachen
          \genesis-en.txt  // deutsch, englisch, franz�sisch,
          \genesis-es.txt  // spanisch und lateinisch.
          \genesis-fr.txt  // Die 2-Buchstabencodes entsprechen
          \genesis-la.txt  // den ISO 639 Language Codes.

examples\.. Dieses Verzeichnis enth�lt unterschiedliche
            Beispieldateien, die in den Szenarien verwendet
            werden. Dateien mit der Endung ".txt" sind
            Textdateien. Alle anderen Dateien sind bin�r.
            Dateien mit dem Format "XX-enc-YY.*" sind
            verschl�sselte Dateien. Bitte ver�ndern Sie
            diese Dateien nicht, da diese in den
            verschiedenen Szenarien der Hilfe verwendet
            werden.

examples\CrypTool.bmp
        \CrypTool-de.txt
        \CrypTool-en.txt
        \Playfair-enc-de.txt
        \Probetext-de.txt
        \psion-enc.hex
        \vernam.txt
        \Startbeispiel-de.txt
        \Startingsample-en.txt

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
                   Namensmuster cry*.* in das Temp-Verzeichnis
                   (Endungen: asc, hex, org, plt, tmp, txt).
CrypTool.ini...... Diese Datei befindet sich im Windows-
                   Verzeichnis und enth�lt neben der Einstellung,
                   ob der Begr��ungsdialog angezeigt werden soll,
                   die Dateinamen der zuletzt bearbeiteten
                   Dateien.


4.1. �berpr�fen der Integrit�t der heruntergeladenen Dateien
     -------------------------------------------------------
Die Integrit�t von Dateien kann mit Hashwerten �berpr�ft
werden. Hashwerte sind wie Fingerabdr�cke: wenn man den
Hashwert einer heruntergeladenen Datei neu berechnet und mit
den Werten auf der CrypTool-Homepage vergleicht, kann man
sehen, ob man eine unver�nderte Kopie der Originaldatei hat
oder nicht.
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

MD5-Hashwert                      Name
XXXmd5sumXXX

SHA1-Hashwert                          Name
XXXsha1sumXXX


Zur �berpr�fung k�nnen Sie die oben genannten Tools verwenden
oder das Programm CrypTool selbst.

Die Hashwerte von "externen" Dateien k�nnen Sie auch berechnen,
ohne diese in CrypTool zu laden:
- Men� Einzelverfahren \ Hashwerte \ Hashwert einer Datei...
  (MD5 oder SHA1 als Hashalgorithmus w�hlen!)
- �ffnen der entsprechenden Datei
- Vergleich mit dem Wert hier.

Aus Sicherheitsgr�nden empfiehlt sich der Vergleich bei
Bin�rdateien (EXE, DLL, PDF, ...), wenn Sie nicht ganz sicher
sind, dass Ihr Rechner unber�hrt ist.



5. Neuerungen in CrypTool bis 1.3.04
   ---------------------------------
 
5.1. �nderungen von Version 1.2.02 zu Version 1.3.00
     -----------------------------------------------
Seit CrypTool 1.202 (Dez. 2000) wurden folgende Erweiterungen und
Bugfixes in Version 1.3.00 hinzugef�gt (aufgelistet bis 5.1.6):
- CrypTool ist nun komplett in gleicher Weise in deutsch und
  englisch.
- Alle Dialoge wurden im Hinblick auf Konsistenz und
  Verst�ndlichkeit �berarbeitet.
- Die bisherigen Einschr�nkungen (maximale Datengr��e 64 KB) f�r
  die Windows-Versionen Win95 und Win98 wurden aufgehoben.
  Aus Performancegr�nden wurde festgelegt, dass CrypTool
  - von Textdateien nur 4 MB und
  - von Bin�rdateien nur 1 MB l�dt.
  Mit dem AES-Tool k�nnen Dateien beliebiger Gr��e verschl�sselt
  werden.
- die letzte Einstellung zu einem Verfahren (wie gew�hlter
  Schl�ssel oder Alphabet) wird Programm-intern aufbewahrt.

5.1.1. Klassische Verfahren
       --------------------
+ Homophone Verschl�sselung neu
+ Permutationsverschl�sselung neu
+ Zufallsdaten erzeugen neu
  Die folgenden "Pseudozufallsgeneratoren" werden angeboten:
  - der von der Secude-Lib bereitgestellte Zufallsgenerator
  - ein durch den Parameter N einzustellender "x^2 mod N"
    Zufallsgenerator
  - Linearer Kongruenz-Generator
  - Inverser Linearer Kongruenz-Generator
+ Statistische Analysen f�r Zufallsdaten (z.B. FIPS-140-1) neu
+ Periodenanalyse verbessert
+ N-Gramm-Analyse erg�nzt (mit der M�glichkeit, die Ergebnisse
  abzuspeichern)
  Die N-Gramm-Analyse ist f�r Bin�rdateien auf 64 kBytes und f�r
  Textdateien auf 256 kBytes beschr�nkt (l�ngere Eingaben werden
  auf die maximale Eingabel�nge gek�rzt).
+ Fehler bei Vigenere und Caesar behoben (beliebige Textdateien)
+ Playfairanalyse verbessert.

5.1.2. Symmetrische Verfahren
       ----------------------
+ das eigenst�ndige Programm AES-Tool kann selbstentpackende
  Programme erzeugen.
  Damit kann man eine beliebige Datei Passwort-gesch�tzt mit AES
  verschl�sseln (durch Eingabe eines Hexadezimal-Schl�ssels).
+ Veranschaulichen, wie ein Schl�ssel aus einem Passwort nach
  PKCS#5 generiert wird [aus der Texteingabe (Passwort) wird ein
  Hexadezimal-Schl�ssel erzeugt, der gegen W�rterbuchangriffe
  resistent ist. Parameter: Ausgabe-Schl�ssell�nge, Saat f�r den
  Zufallsgenerator, Anzahl der "Hash"-Iterationen,
  Hashverfahren (MD2, MD5, SHA-1)].

5.1.3. Asymmetrische Verfahren
       -----------------------
+ Demo zur Zahlentheorie und zum RSA-Verfahren neu
  - Primzahlen generieren
  - Zahlen (schrittweise) und mit verschiedenen Verfahren
    faktorisieren
  - das RSA-Kryptosystem transparent durchf�hren (auch f�r
    selbst-gew�hlte Primzahlen).
    Damit kann z.B. auch der "Dialog der Schwestern"
    nachvollzogen werden.

5.1.4. Formatierung / Anzeige / Navigation
       -----------------------------------
+ intern werden die Schl�ssel und Eigenschaften aller Verfahren
  getrennt gespeichert. Speicherung und Abruf der dabei
  eingegebenen Schl�ssel erfolgt �ber 2 Buttons. Dadurch
  wird die Wiederverwendung deutlich einfacher, wenn
  wie in klassischen Verfahren wie Playfair sehr spezifische
  Formate verwendet werden.
+ Das Umschalten von Hexanzeige nach Textanzeige f�r
  Nicht-Textdateien ist unterbunden.
+ Beim Anzeigewechsel wird das "Vater"-Fenster beibehalten.
+ Hotkeys zur Verzweigung in das PDF-Skript eingef�gt.

5.1.5. Hilfe / PDF-Skript
       --------------------
+ Erg�nzung des Skripts um eine Einf�hrung in die elementare
  Zahlentheorie mit vielen Beispielen.

5.1.6. Sonstiges
       ---------
+ PKCS#12-Export und -Import von RSA- und DSA-PSEs und damit
  von den darin gespeicherten Schl�sseln.
+ Neue Webseite
  - zus�tzliche Infos: Pr�sentation auf deutsch und englisch.


5.2. �nderungen von Version 1.3.00 zu Version 1.3.04
     -----------------------------------------------
Zu folgenden Themen gab es Verbesserungen/Erweiterungen:

Sourcecode:
===========
+ �berarbeitung des Quelltextes f�r die �bergabe an den neuen
  Maintainer.
+ Weitere Automatisierung beim Erzeugen des Setup-Paketes.

Webseite:
=========
+ Enth�lt die Hashwerte der herunterladbaren Dateien und
  erm�glicht so einen Check der Integrit�t der auf dem
  Computer befindlichen Dateien.
+ F�r 1.3.04 wurden aufgenommen:
  + Frame-Eintrag, der zu einer Seite mit Links f�hrt
  + Frame-Eintrag, der direkt zu der CrypTool-Pr�sentation f�hrt

Dokumentation:
==============
+ Im Skript:
  - Der Artikel "Einf�hrung in die elementare Zahlentheorie"
    (Kapitel 3) wurde erg�nzt um
    - einen Anhang, der die Beispielaufrufe f�r den Zahlentheorie-
      Interpreter PARI-GP enth�lt (damit k�nnen Sie die Beispiele
      nicht nur mit Mathematica, sondern auch mit einem kostenlosen
      Mathematik-Paket durchf�hren) und um
    - Kapitel 3.11: Informationen zur aktuellen Diskussion �ber
      die Sicherheit des RSA-Verfahrens (vgl. Bernstein).
  - neu sind Kapitel 5.1 und 5.2 zu speziellen Signaturen.
  - neu in Kapitel 6 sind Informationen zur Motivation und
    Interoperabilit�t von Elliptischen Kurven.
  - neu in 1.3.04: 
    aktueller Stand der Kryptoanalyse von AES und RC5,
    aktuelle Entwicklungen bei der Faktorisierung (TWIRL) und
    in der Zahlentheorie ("Primes in P") erg�nzt.
+ Einheitliche CrypTool-Pr�sentation zu 1.3.0x (keine Trennung
  mehr in Features von 1.2.xx und Neuerungen in 1.3.xx).
+ Online-Hilfe verbessert und erweitert (z.B. Hilfe f�r die
  neuen Funktionen und Einbau einer Zeittafel der Kryptographie).
  In 1.3.04 wurde z.B. der Abschnitt zu PGP / GnuPP aktualisiert.

Funktionalit�t:
===============
+ Ist ein Men�eintrag selektiert, der noch ein Untermen� hat,
  und man dr�ckt F1, gelangt man nun auf die entsprechende
  Hilfeseite der Online-Hilfe zum ganzen Men�.
+ Hashwerte von Dateien berechnen, ohne die Dateien zu laden.
+ Verbesserung bei der Faktorisierung zusammengesetzter Zahlen:
  - Ausgabe der Details pro abgespaltenem Faktor.
  - Abfangen, wenn das Quadratic Sieve-Verfahren f�r die
    gegebene Zahl mehr Speicher braucht als verf�gbar ist.
+ Erweiterung der Funktionalit�t im RSA-Kryptosystem:
  - interaktive Nutzung der Faktorisierung, wenn nur die
    �ffentlichen Parameter bekannt sind (ohne h�ndisch Ergebnisse
    aus einem extra-Faktorisierungsschritt zu �bertragen),
  - Eingabe von Hexwerten m�glich.
+ Verbesserungen im AES-Tool
  (die mit 1.3.03 ausgelieferte Version des AES-Tools wurde stark
  �berarbeitet und ist nicht mehr kompatibel zu den Vorg�nger-
  versionen):
  - Das AES-Tool bietet nun den vollen Funktionsumfang auch bei
    einem Aufruf von der Kommandozeile.
    Es kann entweder selbst�ndig oder �ber die Men�folge 
    Ver/Entschl�sseln \ Symmetrisch \ AES (selbstextrahierend)
    aus Cryptool heraus aufgerufen werden.
  - Der Dateityp (Exe oder Aes) stellt sich weitgehend selbst ein.
  - Bitte beachten Sie, dass die Ausgabe des AES-Tools auch bei der
    Dateiendung "Aes" nicht vollkommen identisch ist mit dem Ausgabe,
    die Sie erhalten mit der Men�folge
    Ver/Entschl�sseln \ Symmetrisch \ Rijndael (AES).
+ Bei der Hill-Verschl�sselung k�nnen die Details zur aktuellen
  Schl�sselmatrix in einer Textdatei ausgegeben werden:
  - das aktuell in Optionen \ Textoptionen gew�hlte Alphabet,
  - die Hill-Schl�sselmatrix, auch kodiert in Zahlen und
  - eine Beispiel-Ver-/Entschl�sselung, berechnet im Detail.
+ Bei der Permutationsverschl�sselung (Doppelw�rfel) wird nun
  der inverse Permutationsschl�ssel berechnet und angezeigt.
+ Bei der manuellen Analyse der Substitutionsverschl�sselung kann
  man sich nun per Button zwischen seinen letzten �nderungen hin-
  und her bewegen.
  Au�erdem kann man sich den Schl�ssel, der als Ergebnis der
  manuellen Analyse entstand, tempor�r abspeichern, um ihn sp�ter
  wieder zu verwenden.
+ Langfassung des "Dialogs der Schwestern" in Deutsch und
  Englisch beigelegt (darin wird ein in der RSA-Demo
  behandelter Sonderfall des RSA-Verfahrens beschrieben).
+ Die Ausgabe bei der Entropie-Berechnung ist nun ausf�hrlicher.
+ Bei der Anzeige des Zertifikatsinhalts wird nun auch der
  Public Key mit ausgegeben.
+ Visualisierung der einzelnen Schritte / Abh�ngigkeiten bei der
    -> Erzeugung einer elektronischen Signatur,
    -> Hybridverschl�sselung und -Entschl�sselung,
    -> Wirkung von Text�nderungen auf den Hashwert (Hash-Demo)
       (Sensitivit�t von Hashverfahren).
+ In den Datenflussdiagrammen zur Visualisierung sehen Sie,
  welche Schritte in welcher Reihenfolge gemacht werden k�nnen.
  Wenn Sie einen Schritt anklicken, dessen Voraussetzungen noch
  nicht erf�llt sind, wird dies in einer Hilfebox erl�utert.
+ Die schrittweise Verifikation einer RSA-Signatur ist nun auch
  m�glich (dabei werden wie bei der Visualisierung der Hybrid-
  Entschl�sselung die schon vorhandenen Masken wiederverwendet).
+ Einf�hrung des Men�punktes Startoptionen.
+ Klarere Aufstellung des Analyse-Men�s.
+ Speichert der Benutzer einen Fensterinhalt ab, wird nicht mehr
  ein tempor�rer Dateiname vorgeschlagen, sondern ein inhaltlich
  passender Name: Cry-<Verfahren>-<Quelldateiname>.*
  Bei bewusst abgespeicherten Dokumenten wird dann der Dateiname
  im Fenstertitel angezeigt (anstatt der Beschreibung).

Ganz neu in 1.3.04 sind:
------------------------
+ Das Men� zu CrypTool im Windows Start\Programme-Men� enth�lt
  nun auch einen Verweis auf die Readme-Datei.
+ In den Visualisierungsdialogen wurde der Hintergrund anders
  gesetzt, um auch bei neuen Windows XP-Templates deutlich
  sichtbar zu sein.
+ Bei der Brute-Force-Attacke auf symmetrische Algorithmen werden
  nun mehr als 5 Jokerzeichen (bisher 20 Bit) zugelassen und die
  erwartete Zeit wird ausgegeben. Au�erdem kann man die Breite f�r
  das hierbei genutzte Entropiefenster per Analyseoptionen einstellen.
+ Hochperformante Implementierung zum Suchen von Hash-Kollisionen 
  (Anwendung des Geburtstagsparadoxons). Damit kann man einen
  eingeschr�nkten Angriff auf Hash- bzw. Signatur-Verfahren 
  praktisch und f�r konkrete Dateien zeigen.
+ Visualisierung des Diffie-Hellman Schl�sselaustausch-Verfahrens.


5.3. Geplante �nderungen nach Version 1.3.04
     ---------------------------------------
Funktionalit�t:
+ Eine hochperformante Mustersuche, um entweder mehrfach vorkommende
  Muster beliebiger L�nge in einer Datei zu finden oder um alle Patterns
  in einer Datei zu finden, die auch in einer anderen (vorzugebenden)
  Datei vorkommen.
+ Eine pure Kommandozeilenversion des AES-Tools auch f�r die
  Betriebssysteme OS/2 und Linux (aestool-os2; aestool-linux).
+ Visualisierung von Challenge-Response-Verfahren.
+ Visualisierung von Man-in-the-Middle-Attacks.


6. M�gliche Punkte f�r eine Weiterentwicklung
   ------------------------------------------
+ Weitere Algorithmen zu jedem Thema der Verschl�sselung oder
  Analyse hinzuf�gen, z.B.
  - ADFGVX bei den klassischen Verfahren,
  - RC5 und Ghost bei den symmetrischen Verfahren oder
  - Rabin bei den Public Key-Verfahren.
+ Parametrisierung, wo immer das m�glich ist:
  Anbieten einer Option, um z.B. den Initialisierungsvektor,
  die Anzahl von Runden, die Schl�ssel- oder Wortl�nge oder
  das Padding zu setzen (z.B. f�r den RC5-Algorithmus - siehe
  RFC 2040).
  Diese Parameter m�ssen dann auch in das Format f�r den internen
  Schl�sselspeicher aufgenommen werden.
+ Ganz bewusst sind bei CrypTool die Schl�ssel f�r die modernen
  Verschl�sselungsverfahren in Hex-Zeichen einzugeben. 
  Es ist Absicht, dass man in CrypTool zun�chst sieht, welche Art
  Schl�ssel die verschiedenen Algorithmen erwarten: bei den 
  klassischen Verfahren besteht der Schl�ssel aus dem zugrunde
  liegenden Alphabet, bei den modernen Verfahren sind es 
  Bin�rdaten von 56 Bit bis 256 Bit L�nge.
  Andererseits sind Benutzer gewohnt, ihre Eingaben per ASCII-Zeichen
  zu machen. Da in einer produktiven Anwendung der Schl�ssel nicht
  aus ASCII-Zeichen bestehen sollte, ist es besser, wenn man schon
  ein ASCII-Passwort als Grundlage verwendet, daraus mit einem 
  vern�nftigen Verfahren einen Schl�ssel herzuleiten. 
  In CrypTool k�nnte man die Anforderung "ASCII-Schl�sseleingabe" und
  Zeigen, dass gute Hex-Keys zu verwenden sind, folgenderma�en 
  miteinander verbinden:
  In dem HEX-Schl�sseleingabe-Dialog sollte man per Button die Funktion 
  "Einzelverfahren \ Schl�ssel aus Passwort erzeugen" aufrufen k�nnen. 
  Der Dialog ist dann mit der richtigen Schl�ssell�nge parametrisiert 
  und der generierte Schl�ssel wird in die HEX-Schl�sseleingabe �bernommen. 
  Damit dies auch f�r AES-256 funktioniert, m�sste noch die SHA-256-
  Hashfunktion eingebaut werden.
+ In den Dialogen in CrypTool k�nnen Zahlen nicht immer in allen
  Darstellungsarten eingegeben werden (z.B. kann im Dialog RSA-Kryptosystem
  die zu verschl�sselnde Nachricht als Text mit frei einzustellendem 
  Alphabet und als Zahl mit 4 verschiedenen Basen) eingegeben werden,
  die Primzahlen dagegen kann man "nur" als Zahl im Zehnersystem bzw. als
  Ausdr�cke mit Zahlen im Zehnersystem eingegeben).
  N�tzlich w�re es, wenn man aus CrypTool heraus einen Taschenrechner
  als a-modales Fenster aufmachen k�nnte, der Terme mit Zahlen beliebiger
  Basis als Eingabe nimmt und die Ausgabe in mehreren Feldern in 
  verschiedenen Zahlensystemen parallel anzeigt. Von hier aus sollte
  man dann die Zahlen per Knopfdruck ins Clipboard bringen k�nnen oder
  per Maus in die Eingabefelder der CrypTool-Dialogboxen ziehen k�nnen.
+ W�rterbuch f�r alle Angriffe benutzen, nicht nur f�r die
  Substitution.
+ Einbau einer erweiterten Mustersuche (Suche mit vorgegebenen normierten
  und regul�ren Mustern und Suche nach unbekannten, aber mehrfach
  vorkommenden Mustern im Dokument, ...), indem der Dialog zum
  Massen-Vergleich mit bekannten Mustern in einer anderen Datei
  entsprechend erweitert wird.
  Zur Suche k�nnte man auch Ersetzen erg�nzen.
+ Analyse neu implementieren f�r
  - homophone Verschl�sselung.
+ Analyse verbessern (nicht performant und korrekt genug bisher) f�r
  - monoalphabetische Substitution
    (plus explizite Anzeige von vertauschten Digrammen wie "ie"/"ei"
    und von Doppelzeichen wie "mm"),
  - Playfair-Verschl�sselung,
  - asymmetrische Kryptoverfahren.
+ Alle Anzeigemodule in einem konsistenten Klassenbaum
  zusammenfassen.
+ Entsprechend der MFC-Vorgehensweise f�r verschiedene Fenstertypen
  gibt es f�r Text- und Bin�rdateien verschiedene Men�b�ume.
  Da diese Typen nicht so sehr unterschiedlich sind, k�nnte
  man die Anzeigeform als View betrachten und die entsprechenden
  Funktionen auf beide anwenden (und z.B. beim Versuch der Playfair-
  Verschl�sselung mit einem Nicht-Textfile alle Buchstaben au�erhalb
  des Alphabets ignorieren) oder in einer gemeinsamen Men�struktur
  die Men�eintr�ge dynamisch ein-/ausblenden. 
+ Die Sourcen so umstellen, dass die Ausgabe/Anzeige komplett von
  den Kryptomodulen getrennt ist (erleichtert Portierungen und
  Fehlersuche).
+ F�r den Benutzer konfigurierbar einstellbar machen, ob neue Fenster
  wie bisher innerhalb des Hauptfensters erscheinen oder als "freie"
  Fenster danebenstehen.
+ F�r den Benutzer konfigurierbar einstellbar machen, wie gro� die
  Text- und Bin�rdateien sein k�nnen, die CrypTool laden kann.
+ In der Anzeige f�r Grafiken eine Vergr��erungsfunktion einbauen
  und / oder die Koordinaten anzeigen, an denen sich die Maus
  befindet.
+ Korrekturm�glichkeit einzelner Zeichen bei der Analyse von XOR,
  ADD, Vigenere.
+ Anzeigen des zweit-, dritt-, ... -besten Treffers bei der
  XOR/ADD-Analyse (dies kann zu einer k�rzeren Schl�ssell�nge
  f�hren).
+ Einzelne Dialogboxen (z.B. N-Gramm-Analyse, Manuelle Analysen,
  Hybriddemo) als amodale Fenster erzeugen, so dass man beliebig
  zwischen Hauptfenster und Auswertungsfenster springen kann
  (aufwendigere Steuerung, Erlauben oder Abfangen von Mehrfachauf-
  rufen derselben Dialogbox, evtl. Update nach Fokus-Wechsel bzw.
  nach �nderung der Originaldaten im Hauptfenster, ...).
+ Autokorrelation: vor der �berlagerung noch Operationen auf den
  Bl�cken ausf�hren (XOR, ADD, ...); macht das Sinn?
+ Editieren der Homophonen-Schl�ssel (ben�tigt bei der Analyse
  der Homophonen Verschl�sselung).
+ Bei gleitender Entropie: Automatische Anzeige der
  entsprechenden Stellen mit hoher Entropie.
+ Hillverfahren: Schl�sselmatrix transponieren.
+ Hillverfahren: Eingabe von Zahlen in die Schl�sselmatrix.
+ Update der Miracl-Lib auf eine neuere Version als 4.4.3.,
  sofern dies eine Performance-Verbesserung bringt.
+ Portierung nach Linux (eine Secude-Lib bzw. Miracl-Lib stehen
  zur Verf�gung). Danach besteht eine gro�e Nachfrage.
+ Portierung nach Java (eine Secude-Lib daf�r steht zur
  Verf�gung).
+ Kryptographisch starke elliptische Kurven erzeugen und damit
  Implementierung eines auf Elliptischen Kurven basierenden
  Kryptosystems. Dazu k�nnte man das Kryptosystem von Menezes
  und Vanstone nehmen, das 1993 von diesen Autoren vorgeschlagen
  wurde: A. Menezes and S. Vanstone,
         "Elliptic curve cryptosystems and their implementation",
         Journal of Cryptology, 6 (1993), Seiten 209-224.
+ Weil kryptographische Strukturen und Formate h�ufig ASN.1-
  kodiert sind: Integration eines ASN.1 Dekodier-Tools.
+ Visualisierung:
  - Generell ist die Visualisierung der Abh�ngigkeiten und Abl�ufe
    bei Protokollen (nicht nur bei "einfachen" Algorithmen) eine
    sinnvolle Erweiterung.
  - Angriffe auf schwache RSA-Schl�ssel werden in der Online-Hilfe 
    per Hilfe\Szenarien\RSA-Kryptosystem (Demonstration), unter 
    "3.) Der Angriff auf das RSA-Verfahren" beschrieben: durch
    Faktorisieren des Moduls kann man das Verfahren knacken.
    Dies ist auch implementiert, aber noch nicht visualisiert.
  - Angriffe auf andere asymmetrische Verfahren sind in CrypTool
    bisher noch gar nicht behandelt. Um Diffie-Hellman, DSA oder
    EC-DSA anzugreifen, muss "diskrete Logarithmen" berechnen.
    Auch dies k�nnte man nach dem Implementieren wieder 
    visualisieren.
+ Zufallszahlen:
  - Bisher konzentriert sich CrypTool auf kryptographisch starke 
    Pseudozufallzahlgeneratoren. Nur im Secude-Generators wird
    eine "echte" Zufallsquelle einbezogen. 
    Die Gewinnung "echter" Zufallsdaten �ber Mausbewegungen etc.
    w�re eine gute Erg�nzung f�r CrypTool (Yarrow, PGP, ...). 
  - In Deutschland wird die Evaluierung von deterministischen 
    Zufallszahlengeneratoren durch die AIS 20 (seit Dezember 1999;
    AIS = Anwendungshinweise und Interpretationen zum Schema) und 
    die Evaluierung von physikalischen Zufallszahlengeneratoren 
    durch die AIS 31 (seit September 2001) geregelt. 
    Vor allem die AIS 31 ist auch au�erhalb Deutschlands auf 
    gro�es Interesse gesto�en.
    Die AIS 20 und AIS 31 befinden sich in deutscher und englischer
    Sprache auf der BSI-Website:
    http://www.bsi.bund.de/zertifiz/zert/interpr/ais20.pdf   
    http://www.bsi.bund.de/zertifiz/zert/interpr/ais31.pdf   
    http://www.bsi.bund.de/zertifiz/zert/interpr/trngkr31.pdf
    Es w�re eine gute Erg�nzung f�r CrypTool, diese Standard-
    anforderungen zur Evaluierung von Zufallszahlen  
    einzubauen und dies auch zu visualisieren.
+ Weitere Standards implementieren und direkt �ber die Men�s
  bzw. aus der Online-Hilfe an alle Stellen verzweigen, wo diese
  Standardverfahren (z.B. PKCS#5) verwendet werden (Hauptarbeit
  dabei sind nur User Interface und Dokumentation).
+ �hnlich wie CrypTool "gute" Schl�ssel aus Passworten generiert (PKCS#5),
  sollte eine DOKUMENTIERTE Schnittstelle da sein zu den verschiedenen
  Verfahren, die gute Passworte generieren.
+ CrypTool als Frontend f�r zahlentheoretische Funktionen und
  Werte erweitern.


6.1. Sinnvolle Aufgaben f�r die Einarbeitung des neuen Maintainers
     ------------------------------------------------------------
+ Einbau des RC5-Algorithmus wie oben beschrieben, um zu sehen,
  an welchen Stellen �berall die Sourcen daf�r zu erg�nzen sind.
+ alle m�glichen Arten von Transpositionen und Superpositionen
  f�r den Inhalt von Textfenstern in einem ansprechenden Dialog
  anbieten.
+ Testbett mit Beispielen und L�sungen erzeugen, damit man das
  Testen automatisieren kann und damit man sicherstellen kann,
  dass durch Programm�nderungen nicht alte funktionierende
  Funktionalit�t negativ beeinflusst wird:
  a) Interface, um Testaufgaben manuell in Dialogboxen zu laden
  b) Schnittstelle schaffen, mit der sich die Testaufgaben aus
     einer Datei selbst in die Dialogboxen laden.
     Vielleicht sogar Script-Steuerung f�r alle Dialoge oder
     automatische Testtools vom Markt einsetzen.
  c) Commandline-Interface schaffen (am besten nachdem Krypto und
     Anzeige im Code getrennt wurden), das ohne Dialogboxen alle
     Aufgaben aus einer Datei per Schnittstelle ausliest und die
     L�sungen wieder in eine Datei schreibt:
     -> Abgleich automatisierbar
     -> neue Version leichter testbar.




7. Kurze Historie der freigegebenen Hauptversionen
   -----------------------------------------------

Version   Datum		Gr��e des Windows-Setups	Freigabe durch
			Deutsch		Englisch
1.0.01    Okt. 1999	1,3 MB		-		DB
1.1.01    Mai  2000	2,3 MB		-		DB
1.2.00    Aug. 2000	2,8 MB		-		DB
1.2.02    Dez. 2000	3,2 MB		-		DB
1.3.00    Jan. 2002	4,9 MB		4,7 MB		DB
1.3.02    Juni 2002	6,9 MB		6,4 MB		DB
1.3.03    Sep. 2002	6,9 MB		6,5 MB		DB
1.3.04    Mai  2003	xxx MB		xxx MB		DB

Bemerkung zu den aktuellen Versionen:
1.3.02    viele neue Funktionen gegen�ber 1.3.00
1.3.03    viele kleine Bugfixes und Verbesserungen der
          Dokumentation.
1.3.04    einige neue Funktionalit�t (siehe Kapitel 5.2), einige
          kleine Bugfixes (Absturz bei Playfair-, N-Gramm-Analyse, RSA),
          und Verbesserung und Erweiterung der Dokumentation.



8. Feedback bei Fehlern
   --------------------
Sollten Sie Probleme haben oder Fehler finden, wenden Sie sich
bitte mit einer Beschreibung des Problems per e-mail an
- joerg-cornelius.schneider@db.com  oder
- bernhard.esslinger@db.com / besslinger@web.de oder
- an die Mailingliste: cryptool-list@sec.informatik.tu-darmstadt.de

F�r Anregungen jeglicher Art bez�glich CrypTool sind wir immer
dankbar und helfen Ihnen gern, wenn es unsere Zeit erlaubt.

Auch w�rden wir uns freuen, wenn Sie uns mitteilen, wie und wo Sie
CrypTool einsetzen.



9. Kontaktadressen
   ---------------
- joerg-cornelius.schneider@db.com
- bernhard.esslinger@db.com
- besslinger@web.de
- henrik.koy@db.com
- cryptool-list@sec.informatik.tu-darmstadt.de
- peer.wichmann@web.de



10. Verweise
    --------
10.1. Wirtschaftswoche Spezial
      ------------------------
Das Spezial "Kryptographie" der Zeitschrift Wirtschaftswoche
(Rubrik Netzwelt Sept. 2000) enthielt ein Preisausschreiben:
"Knacken Sie den Text!" unter der URL
http://www.wiwo.de/wiwowwwangebot/fn/ww/sfn/buildww/cn/
cn_artikel/id/62633!100301/SH/0/depot/0/bt/1/index.html.
Wenn man sich an die Tipps der Aufgabenstellung hielt, konnte man
mit CrypTool die Aufgabe mit wenigen Mausklicks l�sen.

10.2. c't 14/2001, S. 204-208
      -----------------------
In diesem renommierten und auflagenstarken deutsch-sprachigen
Computermagazin wurde im Juli 2001 ein 5-seitiger Artikel zu
CrypTool ver�ffentlicht.

10.3. DuD Oktober 2002
      ----------------
In der deutsch-sprachigen Fachzeitschrift "DuD Datenschutz und
Datensicherheit", Ausgabe 10/2002 erschien unter dem Titel
"CrypTool - spielerischer Einstieg in klassische und moderne
Kryptographie. Neue Version - fundierte Awareness in Deutsch
und Englisch" ein 4-seitiger Artikel �ber CrypTool.

10.4. BSI B�rger-CD "Ins Internet - mit Sicherheit"
      ---------------------------------------------
Das Bundesamt f�r Sicherheit in der Informationstechnik (BSI) hat
zusammen mit dem Deutschen Bundesinnenministerium zur CeBIT 2002
eine CD ver�ffentlicht, die die B�rger aufkl�rt, wie man mit
Computern und Internet umgeht und wie man sich sicher im Internet
bewegen kann.
Auf dieser CD ist auch CrypTool enthalten, um das Verst�ndnis der
kryptographischen Sicherheitsfunktionen zu verbessern.
Von dieser CD sind mehr als 600.000 St�ck produziert und
zum Beispiel mit der Zeitschrift PC-Welt 8/02 verteilt worden.
Der Inhalt dieser CD floss ein in das BSI Sicherheits-Portal
"f�r unerfahrene Internet-Nutzer" (http://www.bsi-fuer-buerger.de).

10.5. Freeware-Projekte Crank, Griffon, CAP, CryptAid, etc.
      ------------------------------------------------------
Available with source code are:
- http://freshmeat.net/projects/crank/
  Crank wurde im Januar 2001 von Matthew Russell begonnen und unter
  der GNU General Public Licence (GPL) freigegeben.
  Im Crank-Projekt soll unter Linux ein Programm mit grafischer
  Oberfl�che erstellt werden, das das m�glichst automatisierte
  Brechen von klassischen Kryptoalgorithmen erm�glicht.
  Initial liegt der Fokus auf der Analyse monoalphabetischer
  Substitutions-Chiffren und der Entwicklung generischer und
  flexibler Analysetools.
  Das Tool liegt nur in englischer Sprache vor.
  Die aktuelle Version 0.2.1 wurde im August 2001 freigegeben.
  Auf der Projekt-Webseite gibt es auch einige sehr interessante Links
  zu klassischer Kryptoanalyse.

- http://freshmeat.net/projects/griffon/
  Griffon wurde im Jahre 2000 von Adrian Mulvaney begonnen und unter
  der GNU General Public Licence (GPL) freigegeben.
  Griffon ist ein GTK+ GUI Kryptoanalyse-Paket f�r Pre-digital Ciphers.
  Es enth�lt monoalphabetische Transposistion, Substitution und Playfair.
  Das Tool liegt nur in englischer Sprache vor.
  Die aktuelle Version 1.0 wurde im November 2000 freigegeben.

Die einzigen weiteren uns bekannten brauchbaren Programme, die
Kryptographie und Kryptoanalyse (unter einer graphischen
Oberfl�che) verbinden, f�r die aber kein Source-Code freigegeben ist,
sind:
- CAP von Dr. Richard Spillman
  Die aktuelle Version 4 gibt es seit November(?) 2002.
  http://www.cs.plu.edu/courses/privacy/index.htm
- CryptAid von David Lovelock
  (wahrscheinlich seit 1997 nicht mehr weitergepflegt)
  http://archives.math.utk.edu/software/msdos/miscellaneous/cryptaid/.html
- das Visual Basic-Programm "Cryptological Mathematics" von Prof. R.E. Lewand
  (anschauliche Darstellung einiger zahlentheoretischer Funktionen und
  Funktionen zur Ver- und Entschl�sselung;
  keine Funktionen zur Kryptoanalyse; Software zu seinem Buch)
  http://faculty.goucher.edu/blewand/cryptomath/companion_software.htm
- John Trafton's studentisches Cryptography-Projekt in Java
  (einzelne statistische Funktionen und klassische Verschl�sselungs-
  verfahren; verf�gbar seit Dezember 2002)
  http://phoenix.goucher.edu/~jtrafton/Crypto.

Falls uns hier etwas entgangen ist, w�rden wir uns �ber eine Nachricht
freuen - wir vervollst�ndigen oder korrigieren diese Liste gerne.

Au�erdem wollen wir hier ausdr�cklich das Angebot machen, die
Anstrengungen f�r diese einzelnen Programme in ein einziges
Programm zu integrieren. Wir freuen uns �ber jede Kooperation!!




11. Anhang
    ------

11.1. CrypTool unter Linux mit Wine
11.1.1. .... CrypTool installieren
11.1.2. .... Wine-Konfiguration
11.1.3. .... CrypTool ausf�hren



11.1. CrypTool unter Linux mit Wine
      -----------------------------
Diese Hinweise basieren auf Tests mit Wine 2001-11-29.

11.1.1. CrypTool installieren
        ---------------------
Im letzten Schritt der Installation gibt es die Option,
CrypTool gleich zu starten. Dies funktioniert unter Wine nicht.
Bitte starten Sie CrypTool wie unten beschrieben.


11.1.2. Wine-Konfiguration
        ------------------
CrypTool funktioniert nicht mit der in Wine eingebauten Version
von riched32.dll. Wenn Sie unter CrypTool eine Datei �ffnen und
die falsche Version von riched32.dll benutzt wird, erscheint ein
leeres Fenster.
Wahrscheinlich taucht das Problem nicht auf, wenn Wine eine
existierende Windows-Partition benutzen kann.
Wenn Sie Wine ohne Windows benutzen, k�nnen Sie das Problem mit
folgenden Schritten l�sen:
 - Installieren Sie CrypTool unter Wine.
 - Besorgen Sie sich riched32.dll (z.B. Version 5.0.1458.47)
   und kopieren Sie die Datei in das Installationsverzeichnis
   von CrypTool. Eventuell m�ssen sie analog mit weiteren DLLs
   verfahren, die von riched32.dll benutzt werden. Beachten Sie
   bitte die Fehlerausgaben von Wine.
 - Konfigurieren Sie Wine so, dass es diese Datei nutzt.
   In der Standard-Konfiguration ist das so.
   Funktioniert das bei Ihnen nicht, schreiben Sie folgende Zeile
   in die [DllOverrides]-Sektion der Wine-Konfigurationsdatei:
   "riched32" = "native,builtin"


11.1.3. CrypTool ausf�hren
        ------------------

11.1.3.1. Starten
          -------
Um CrypTool zu starten, wechseln Sie in das Verzeichnis, in das
es installiert wurde, und starten es mit:

$ wine CrypTool

Wenn Sie vor dem Aufruf nicht in das Installationsverzeichnis
von CrypTool wechseln, findet CrypTool einige wichtige Dateien
nicht.


11.1.3.2. Bugs und Work-arounds
          ---------------------
* Die Online-Hilfe kann nicht mit F1 aus CrypTool heraus
  aufgerufen werden.
  Mit der folgenden Kommandozeile k�nnen Sie die Online-Hilfe
  anzeigen:

  $ wine winhlp32 CrypTool.hlp

