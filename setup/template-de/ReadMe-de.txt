==================================================================
    CrypTool, Version 1.3.04, Mai 2003
    (c) Deutsche Bank AG 1998-2003, Frankfurt am Main
    (c) Universität Siegen und Darmstadt
    $Id$
==================================================================

                       Inhalt

 1. .... Kurzbeschreibung des CrypTool-Paketes
 1.1. .... Wie Sie am besten starten - Der Einstieg in CrypTool
 1.2. .... Was beinhaltet die Distribution?
 1.3. .... Danke
 1.4. .... Neuer Maintainer in Zukunft - Roadmap
 2. .... Beschränkungen und Voraussetzungen
 2.1. .... Installation unter Windows 95
 2.2. .... Interaktive Online-Hilfe unter Windows XP
 2.3. .... Unterstützung verschiedener Sprachen
 2.4. .... Einschränkungen in den verwendeten Bibliotheken
 3. .... Installation
 4. .... Dateiliste
 4.1. ..   Überprüfen der Integrität der heruntergeladenen Dateien
 5. .... Neuerungen in CrypTool bis 1.3.04
 5.1. .... Änderungen von Version 1.2.02 zu Version 1.3.00
 5.1.1. .... Klassische Verfahren
 5.1.2. .... Symmetrische Verfahren
 5.1.3. .... Asymmetrische Verfahren
 5.1.4. .... Formatierung / Anzeige / Navigation
 5.1.5. .... Hilfe / PDF-Skript
 5.1.6. .... Sonstiges
 5.2. .... Änderungen von Version 1.3.00 zu Version 1.3.04
 5.3. .... Geplante Änderungen nach Version 1.3.04
 6. .... Mögliche Punkte für eine Weiterentwicklung
 6.1. .... Sinnvolle Aufgaben für die Einarbeitung des neuen Maintainers
 7. .... Kurze Historie der freigegebenen Hauptversionen
 8. .... Feedback bei Fehlern
 9. .... Kontaktadressen
10. .... Verweise
10.1. .... Wirtschaftswoche Spezial
10.2. .... c't 14/2001, S. 204-208
10.3. .... DuD Oktober 2002
10.4. .... BSI Bürger-CD "Ins Internet - mit Sicherheit"
10.5. .... Freeware-Projekte Crank, CAP, CryptAid, etc.
11. .... Anhang
11.1. .... CrypTool unter Linux mit Wine



1. Kurzbeschreibung des CrypTool-Paketes
   -------------------------------------
Dieses Readme gehört zur kostenlosen Distribution von CrypTool,
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
funktionen implementiert. Dies ermöglicht einen "spielerischen"
Einstieg in die moderne und klassische Kryptographie -- unter
einer einheitlichen Oberfläche.

CrypTool wird eingesetzt
- in Unternehmen sowohl zur Mitarbeiter-Sensibilisierung bezüglich
  IT-Sicherheit (Awareness) als auch zur Ausbildung,
- im Schulunterricht und
- in der Lehre an mehreren Hochschulen.

Bitte beachten Sie die Lizenz- und Nutzungsbestimmungen für
CrypTool. Diese werden bei der Installation und auf der
Einstiegsseite der Online-Hilfe erläutert.


1.1. Wie Sie am besten starten - Der Einstieg in CrypTool
     ----------------------------------------------------
Beim Start von CrypTool öffnen sich zugleich die Arbeitsfläche
von CrypTool und im Vordergrund ein kleines Begrüßungsfenster.
Wenn Sie hier die F1-Taste drücken, erscheint die Startseite der
Online-Hilfe.
Diese Startseite ist ein guter Ausgangspunkt, um alle wesentlichen
Inhalte von CrypTool kennen zu lernen (z.B. mit Hilfe der Links auf
dieser Startseite).

Lesen Sie die Hinweise und Tipps der Hilfe-Startseite und
öffnen Sie dann auf der CrypTool-Arbeitsfläche eine
unverschlüsselte Datei aus dem Unterverzeichnis "examples".
Sie können jetzt viele der Funktionen von CrypTool an dieser Datei
ausprobieren.

Einen schnellen Einstieg in CrypTool finden Sie, wenn Sie einige
Szenarien (Tutorials) der Online-Hilfe durchspielen (die Szenarien
stehen im Inhaltsverzeichnis der Hilfe unter "Beginn der Arbeit
mit CrypTool").

Wir wünschen viel Spaß beim Ausprobieren der Funktionen von
CrypTool.


1.2. Was beinhaltet die Distribution?
     --------------------------------
Das CrypTool-Paket enthält die folgenden vier Hauptbestandteile:

(1) Das Programm CrypTool
-------------------------
Hauptteil des CrypTool-Paketes ist das Programm CrypTool selbst.
Entwicklungsziel von CrypTool war nicht, dass damit im Wirkbetrieb
Daten verschlüsselt oder anderweitig gesichert werden sollten. 
Es ist eine Demonstration, die vor allem für Ausbildungszwecke
eingesetzt wird:

- In CrypTool ist eine umfangreiche Sammlung kryptographischer
  Algorithmen implementiert, die hervorragend dokumentiert ist.
  Somit ist CrypTool sehr gut geeignet zur Ausbildung und zur
  Mitarbeiter-Sensibilisierung für IT-Sicherheit.

- Die meisten der kryptographischen Basisalgorithmen stammen von:
  - der Industrie-bewährten Secude-Bibliothek (Version 5.4.15)
    (www.secude.com) und von
  - der Miracl-Bibliothek (Version 4.4.3)
    (http://indigo.ie/~mscott/).
  Somit ist CrypTool auch eine hervorragende Referenzimplemen-
  tierung.

- Die Kryptoanalyse der meisten der klassischen Verfahren ist
  automatisiert.
  Die Analyse der modernen Verfahren ist eingeschränkt, so dass
  CrypTool nicht als Hackertool eingesetzt werden kann.

(2) Dokumentation
-----------------
Zum Programm gehört eine umfangreiche Dokumentation, die aus vier
Teilen besteht:
a) Readme-Datei (diese Datei),
b) Online-Hilfe
   - Kontext-bezogen zur Bedienung des Programms und mit
     weiterreichenden Erläuterungen,
   - Demos bzw. Beispiel-Szenarien (hier werden Einzelverfahren
     Schritt für Schritt erläutert)
c) Skript (zum Thema Kryptographie, beigelegt als PDF-Datei),
d) Präsentation, die auf Folien die Möglichkeiten von CrypTool
   kurz aufzeigt (beigelegt als PDF-Datei).

(3) Das Programm AES-Tool
-------------------------
Zum Erstellen selbstentpackender Executables ist in CrypTool ein
Programm integriert, das auch eigenständig benutzt werden kann.
Darin wird aus einem Passwort ein Session-Key erzeugt, mit dem
ein beliebiger Dateiinhalt AES-verschlüsselt wird.
Dieses Verschlüsselungstool kann sowohl als Fenster als auch von
Kommandozeile (z.B. aus einer Batchdatei) aufgerufen werden.

(4) Die Geschichte "Der Dialog der Schwestern" als PDF-Datei
------------------------------------------------------------
Hierin wird eine Variante des RSA-Verfahren von den Titelheldinnen
benutzt, um verschlüsselt zu kommunizieren.

Alle Einzeldateien, die bei der Installation des CrypTool-Paketes
auf Ihre Platte kopiert werden, sind in Kapitel 4 (unten in diesem
Readme) aufgeführt.



1.3. Danke
     -----
Zu CrypTool haben viele verschiedene Personen beigetragen -
insbesondere auch in ihrer Freizeit (einige sind in der Dialogbox
zu sehen, die man erhält, wenn man in der Dialogbox "Über CrypTool"
einen Doppelklick ausführt). Herzlichen Dank.

Dr. Carsten Elsner erlaubte uns, seine Geschichte "Der Dialog der
Schwestern" als PDF-Datei beizulegen.
Diese Geschichte wurde in dem Computermagazin c't 25/1999
veröffentlicht. Während in der c't 25/99 eine etwas gekürzte Fassung
veröffentlicht wurde, liegt hier die Originalfassung bei.
Der Verfasser, als alleiniger Inhaber aller Rechte an dem Werk,
räumt dem CrypTool-Maintainer das ausschließliche Vervielfälti-
gungs- und Verbreitungsrecht ein. Die Geschichte darf nur zusammen
mit dem CrypTool-Paket verbreitet werden.

Die Firmen Secude GmbH und Shamus Software Ltd. (siehe oben) gestatteten
uns großzügigerweise, ihre Krypto-Bibliotheken zu nutzen.
Diese mit CrypTool verteilten Bibliotheken dürfen nicht in einem
Kontext außerhalb CrypTool benutzt werden, ohne vorher die erwähnten
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
Sie machen die Sourcen von CrypTool als Open Source für die 
Internet-Gemeinschaft verfügbar.

Die Homepage von CrypTool bleibt weiterhin www.cryptool.de.

Wir würden uns sehr freuen, wenn sich nicht nur die bisherigen
Entwickler, sondern auch viele neue an der Weiterentwicklung von
CrypTool beteiligen. Ideen dazu finden Sie in Kapitel 5.3 und 6. 



2. Beschränkungen und Voraussetzungen
   ----------------------------------
CrypTool erfordert eine Win32 Umgebung, wie sie unter Windows 95,
Windows 98, Windows Me, Windows NT (ab 4.0), Windows 2000 und
Windows XP gegeben ist.

CrypTool funktioniert grundsätzlich auch unter FreeBSD/Linux mit
Wine (mit Abstrichen an Funktionalität und Stabilität).
Siehe Anhang 11.1.


2.1. Installation unter Windows 95
     -----------------------------
Bei älteren Windows 95 Systemen erhalten Sie beim Aufruf von
CrypTool die Meldung "Kann 'secude.dll' nicht finden". In diesem
Fall können Sie CrypTool nur eingeschränkt nutzen.

Die Algorithmen der Secude-Bibliothek werden beim Start von
CrypTool mit Hilfe der Bibliothek "msvcrt.dll" dynamisch geladen.

Die Datei "msvcrt.dll" wird standardmäßig mit Windows 98,
Windows NT etc. ausgeliefert, aber nicht mit Windows 95.
Zum Lieferumfang verschiedener Anwendungs-Programme gehört eine
(nicht immer ausreichend neue) Version von "msvcrt.dll".
Kopieren Sie diese Datei in das Windows-Verzeichnis oder in das
Verzeichnis von CrypTool.
Alternativ können Sie eine selbstentpackende Datei von Microsoft
herunterladen, die "msvcrt.dll" enthält:
    ftp://ftp.microsoft.com/softlib/mslfiles/msvcrt.exe
Speichern Sie diese Datei in einem temporären Verzeichnis und
extrahieren Sie die Dateien durch Doppelklick. Weitere
Anweisungen stehen in der dort mitgelieferten Readme-Datei.


2.2. Interaktive Online-Hilfe unter Windows XP
     -----------------------------------------
Unter Windows XP ist der Aufruf der interaktiven Online-Hilfe über
die F1-Taste in einem Spezialfall nicht möglich: betroffen sind
nur Menüs, die noch Untermenüs haben. Das Problem tritt nur auf,
wenn das Untermenü aufgeklappt ist. F1 bewirkt dann gar nichts.

Normalerweise kann bei CrypTool auch Hilfe zu einem Menüeintrag
angefordert werden, der selbst weitere Untermenüs hat.
Unter Windows XP erhält man die Online-Hilfe dazu nur, wenn das
Popup-Fenster der untergeordneten Menüpunkte nicht aufgeklappt
ist.
Bei den anderen Windows-Versionen spielt das keine Rolle, dort ist
nur wichtig, dass das Menü den Fokus hat.

Workaround anhand eines Beispiels: Einzelverfahren \ RSA-Demo
Wenn hier das Untermenü zu "RSA-Demo" aufklappt, Sie aber die
Hilfe zum Menüeintrag "RSA-Demo" haben wollen, müssen Sie - nur
unter Windows XP - das Untermenü von "RSA-Demo" erst mit Escape
(Esc) oder den Pfeiltasten wieder einklappen, dann funktioniert
das Aufrufen der Online-Hilfe mit F1 auch unter Windows XP.


2.3. Unterstützung verschiedener Sprachen
     ------------------------------------
Programm, Hilfesystem und Dokumentation sind mehrsprachig aus-
gelegt (zur Zeit englisch und deutsch).

Für jede unterstützte Sprache gibt es ein eigenes Setup (der
Versuch, alle Sprachen in ein einziges Executable einzubinden
wurde wieder aufgegeben, da die automatische Spracheinstellung
beim Anwender (anhand seiner Systemeinstellungen) nur unter
Windows 4.0, nicht aber unter Win9x, korrekt funktionierte).


2.4. Einschränkungen in den verwendeten Bibliotheken
     -----------------------------------------------
Die beigelegte Secude-Lib ist durch das Ticketfile bei den
asymmetrischen Verfahren auf eine Schlüssellänge von 768 Bits
beschränkt und die Unterstützung von Smartcards ist deaktiviert.
Falls Sie eine Lizenz der Secude-Lib besitzen, können Sie mit
Hilfe Ihres Ticketfiles die asymmetrischen Verfahren auch mit
größeren Schlüssellängen benutzen. Die Verwendung der Secude-Lib
außerhalb von CrypTool ist lizenzpflichtig.

Zur Demonstration des RSA-Kryptosystem und zur Faktorisierung von
Zahlen greift CrypTool auf die Langzahlarithmetik der Bibliothek
Miracl von Shamus Software Ltd. zu. Die Bitlänge der Zahlen wurde
in der CrypTool-Anwendung auf 1024 beschränkt.



3. Installation
   ------------
Durch Aufruf des CrypTool-Setups an einer geeigneten Stelle im
Dateibaum auf Ihrem PC wird CrypTool installiert.
Als Standardwert ist das Verzeichnis "C:\Programme\CrypTool"
vorgesehen. Das Zielverzeichnis kann in der Installationsroutine
geändert werden.

Besitzen Sie bereits eine frühere Version von CrypTool, so
empfiehlt es sich, vor der erneuten Installation das alte CrypTool
zu deinstallieren, da unter Umständen nicht alle alten
Dateien überschrieben werden. Bitte beachten Sie:
- Wenn bei der Deinstallation nicht alle Verzeichnisse/Dateien im
  Programmverzeichnis (meist C:\Programme\CrypTool) gelöscht
  werden, löschen Sie diese manuell.
- Bei der Deinstallation von CrypTool werden alle bisher erzeugten
  asymmetrischen Schlüssel gelöscht. Wenn Sie diese Schlüssel auch
  in der neuen Version von CrypTool nutzen wollen, dann sichern
  Sie vor der Deinstallation das unter dem Programmverzeichnis
  liegende Verzeichnis pse\ mit allen darin gespeicherten Dateien
  in ein anderes Verzeichnis.
  Nachdem die neue Version von CrypTool installiert wurde,
  kopieren Sie das gesicherte pse\-Verzeichnis in das neue
  Programmverzeichnis.
  Ab Version 1.3.00 können Sie alternativ RSA- und DSA-PSEs
  als PKCS#12-Struktur exportieren bzw. importieren.

Für den Fall, dass mehrere Benutzer dieselbe CrypTool-
Installation verwenden wollen, müssen die Zugriffsrechte auf den
Verzeichnissen pse\ und pse\pseca\ und den darin enthaltenen
Dateien für alle Benutzer auf Vollzugriff gesetzt werden.

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
CrypTool-de.cnt .. Indexliste für das Hilfesystem zu CrypTool.
CrypTool-en.cnt .. Die englische Fassung von CrypTool-de.cnt.
CrypTool.exe...... Das ausführbare Programm.
aestool.exe....... Ein Programm, das Dateien in sich selbst
                   entpackende Programme verschlüsselt. Zur
                   Entschlüsselung müssen Sie das korrekte
                   Passwort eingeben.
CrypTool-de.hlp... Hilfesystem zu CrypTool mit Beispielszenarien.
CrypTool-en.hlp .. Die englische Fassung von CrypTool-de.hlp
EC-Param.ini...... Initialisierungsdatei für auf Elliptischen
                   Kurven basierende Public Key-Verfahren.
secude.dll........ Bibliothek kryptographischer Funktionen von der
                   Secude GmbH.
ticket............ Lizenz für die Secude-Bibliothek.
libeay32.dll...... Bibliothek aus OpenSSL 0.96.
irunin.*.......... Diese Dateien sind nötig für Installation und
                   Deinstallation von CrypTool.

script-de.pdf..... Ein Skript (deutsch) über Kryptographie,
                   Primzahlen, Zahlentheorie und die Mathematik
                   hinter einigen Algorithmen.
script-en.pdf..... Die englische Fassung von script-de.pdf.
CrypToolPresentation_1_3_04_de.pdf... Folien-Präsentation
CrypToolPresentation_1_3_04_en.pdf... Englische Fassung der Präs.
DialogSchwestern.pdf.. Fantasy-Geschichte von Dr. Elsner, in der
                       eine Variante des RSA-Kryptosystems
                       beschrieben wird.
DialogueSisters.pdf... Englische Fassung von DialogSchwestern.pdf.

references\....... Dieses Verzeichnis enthält Textdateien in den
                   Sprachen Deutsch, Englisch, Französisch,
                   Spanisch und Latein. Diese Dateien werden
                   standardmäßig als Referenz für die Analyse von
                   Chiffretexten herangezogen.
                   Diese Dateien sind schreibgeschützt.

references\deutsch.txt // Auszug aus dem dt. Umsatzsteuergesetz
          \english.txt // Auszug aus der Agenda 21[UN-Dokument]
          \genesis-de.txt  // Buch Genesis in den Sprachen
          \genesis-en.txt  // deutsch, englisch, französisch,
          \genesis-es.txt  // spanisch und lateinisch.
          \genesis-fr.txt  // Die 2-Buchstabencodes entsprechen
          \genesis-la.txt  // den ISO 639 Language Codes.

examples\.. Dieses Verzeichnis enthält unterschiedliche
            Beispieldateien, die in den Szenarien verwendet
            werden. Dateien mit der Endung ".txt" sind
            Textdateien. Alle anderen Dateien sind binär.
            Dateien mit dem Format "XX-enc-YY.*" sind
            verschlüsselte Dateien. Bitte verändern Sie
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
                   (asymmetrische) Schlüssel und Zertifikate
                   abgelegt. Die folgenden Dateien sind für die
                   Verwaltung der Schlüsseldatenbank notwendig.

pse\pseca\calog
         \CA_exts
         \cert.dir
         \cert.pag
         \crls.dir
         \crls.pag
         \pseca
         \user.dir
         \user.pag

Während der Laufzeit von CrypTool werden die folgenden Dateien
erzeugt und verwaltet:

CrypTool.GID...... Das Hilfesystem erzeugt und verwaltet diese
                   Datei.
cry*.*............ CrypTool schreibt temporäre Dateien mit dem
                   Namensmuster cry*.* in das Temp-Verzeichnis
                   (Endungen: asc, hex, org, plt, tmp, txt).
CrypTool.ini...... Diese Datei befindet sich im Windows-
                   Verzeichnis und enthält neben der Einstellung,
                   ob der Begrüßungsdialog angezeigt werden soll,
                   die Dateinamen der zuletzt bearbeiteten
                   Dateien.


4.1. Überprüfen der Integrität der heruntergeladenen Dateien
     -------------------------------------------------------
Die Integrität von Dateien kann mit Hashwerten überprüft
werden. Hashwerte sind wie Fingerabdrücke: wenn man den
Hashwert einer heruntergeladenen Datei neu berechnet und mit
den Werten auf der CrypTool-Homepage vergleicht, kann man
sehen, ob man eine unveränderte Kopie der Originaldatei hat
oder nicht.
Weichen die Hashwerte voneinander ab, sollte man die Datei
nochmal herunterladen und evtl. die Ursache dafür suchen, dass
man eine veränderte Datei auf seinem Rechner hat.

a) Herunterladbare Dateien
Auf der Homepage von CrypTool www.cryptool.de finden Sie
die Hashwerte aller von der deutschen Seite direkt
herunterladbaren Dateien in den Dateien md5sum.txt bzw.
in sha1sum.txt.
Mit weit verbreiteten Tools wie MD5SUM und SHA1SUM kann
die Überprüfung vorgenommen werden.

b) Auch die Dateien INNERHALB des heruntergeladenen
Setup-Paketes können überprüft werden.
Dazu stehen deren Hashwerte hier im Readme:

MD5-Hashwert                      Name
XXXmd5sumXXX

SHA1-Hashwert                          Name
XXXsha1sumXXX


Zur Überprüfung können Sie die oben genannten Tools verwenden
oder das Programm CrypTool selbst.

Die Hashwerte von "externen" Dateien können Sie auch berechnen,
ohne diese in CrypTool zu laden:
- Menü Einzelverfahren \ Hashwerte \ Hashwert einer Datei...
  (MD5 oder SHA1 als Hashalgorithmus wählen!)
- Öffnen der entsprechenden Datei
- Vergleich mit dem Wert hier.

Aus Sicherheitsgründen empfiehlt sich der Vergleich bei
Binärdateien (EXE, DLL, PDF, ...), wenn Sie nicht ganz sicher
sind, dass Ihr Rechner unberührt ist.



5. Neuerungen in CrypTool bis 1.3.04
   ---------------------------------
 
5.1. Änderungen von Version 1.2.02 zu Version 1.3.00
     -----------------------------------------------
Seit CrypTool 1.202 (Dez. 2000) wurden folgende Erweiterungen und
Bugfixes in Version 1.3.00 hinzugefügt (aufgelistet bis 5.1.6):
- CrypTool ist nun komplett in gleicher Weise in deutsch und
  englisch.
- Alle Dialoge wurden im Hinblick auf Konsistenz und
  Verständlichkeit überarbeitet.
- Die bisherigen Einschränkungen (maximale Datengröße 64 KB) für
  die Windows-Versionen Win95 und Win98 wurden aufgehoben.
  Aus Performancegründen wurde festgelegt, dass CrypTool
  - von Textdateien nur 4 MB und
  - von Binärdateien nur 1 MB lädt.
  Mit dem AES-Tool können Dateien beliebiger Größe verschlüsselt
  werden.
- die letzte Einstellung zu einem Verfahren (wie gewählter
  Schlüssel oder Alphabet) wird Programm-intern aufbewahrt.

5.1.1. Klassische Verfahren
       --------------------
+ Homophone Verschlüsselung neu
+ Permutationsverschlüsselung neu
+ Zufallsdaten erzeugen neu
  Die folgenden "Pseudozufallsgeneratoren" werden angeboten:
  - der von der Secude-Lib bereitgestellte Zufallsgenerator
  - ein durch den Parameter N einzustellender "x^2 mod N"
    Zufallsgenerator
  - Linearer Kongruenz-Generator
  - Inverser Linearer Kongruenz-Generator
+ Statistische Analysen für Zufallsdaten (z.B. FIPS-140-1) neu
+ Periodenanalyse verbessert
+ N-Gramm-Analyse ergänzt (mit der Möglichkeit, die Ergebnisse
  abzuspeichern)
  Die N-Gramm-Analyse ist für Binärdateien auf 64 kBytes und für
  Textdateien auf 256 kBytes beschränkt (längere Eingaben werden
  auf die maximale Eingabelänge gekürzt).
+ Fehler bei Vigenere und Caesar behoben (beliebige Textdateien)
+ Playfairanalyse verbessert.

5.1.2. Symmetrische Verfahren
       ----------------------
+ das eigenständige Programm AES-Tool kann selbstentpackende
  Programme erzeugen.
  Damit kann man eine beliebige Datei Passwort-geschützt mit AES
  verschlüsseln (durch Eingabe eines Hexadezimal-Schlüssels).
+ Veranschaulichen, wie ein Schlüssel aus einem Passwort nach
  PKCS#5 generiert wird [aus der Texteingabe (Passwort) wird ein
  Hexadezimal-Schlüssel erzeugt, der gegen Wörterbuchangriffe
  resistent ist. Parameter: Ausgabe-Schlüssellänge, Saat für den
  Zufallsgenerator, Anzahl der "Hash"-Iterationen,
  Hashverfahren (MD2, MD5, SHA-1)].

5.1.3. Asymmetrische Verfahren
       -----------------------
+ Demo zur Zahlentheorie und zum RSA-Verfahren neu
  - Primzahlen generieren
  - Zahlen (schrittweise) und mit verschiedenen Verfahren
    faktorisieren
  - das RSA-Kryptosystem transparent durchführen (auch für
    selbst-gewählte Primzahlen).
    Damit kann z.B. auch der "Dialog der Schwestern"
    nachvollzogen werden.

5.1.4. Formatierung / Anzeige / Navigation
       -----------------------------------
+ intern werden die Schlüssel und Eigenschaften aller Verfahren
  getrennt gespeichert. Speicherung und Abruf der dabei
  eingegebenen Schlüssel erfolgt über 2 Buttons. Dadurch
  wird die Wiederverwendung deutlich einfacher, wenn
  wie in klassischen Verfahren wie Playfair sehr spezifische
  Formate verwendet werden.
+ Das Umschalten von Hexanzeige nach Textanzeige für
  Nicht-Textdateien ist unterbunden.
+ Beim Anzeigewechsel wird das "Vater"-Fenster beibehalten.
+ Hotkeys zur Verzweigung in das PDF-Skript eingefügt.

5.1.5. Hilfe / PDF-Skript
       --------------------
+ Ergänzung des Skripts um eine Einführung in die elementare
  Zahlentheorie mit vielen Beispielen.

5.1.6. Sonstiges
       ---------
+ PKCS#12-Export und -Import von RSA- und DSA-PSEs und damit
  von den darin gespeicherten Schlüsseln.
+ Neue Webseite
  - zusätzliche Infos: Präsentation auf deutsch und englisch.


5.2. Änderungen von Version 1.3.00 zu Version 1.3.04
     -----------------------------------------------
Zu folgenden Themen gab es Verbesserungen/Erweiterungen:

Sourcecode:
===========
+ Überarbeitung des Quelltextes für die Übergabe an den neuen
  Maintainer.
+ Weitere Automatisierung beim Erzeugen des Setup-Paketes.

Webseite:
=========
+ Enthält die Hashwerte der herunterladbaren Dateien und
  ermöglicht so einen Check der Integrität der auf dem
  Computer befindlichen Dateien.
+ Für 1.3.04 wurden aufgenommen:
  + Frame-Eintrag, der zu einer Seite mit Links führt
  + Frame-Eintrag, der direkt zu der CrypTool-Präsentation führt

Dokumentation:
==============
+ Im Skript:
  - Der Artikel "Einführung in die elementare Zahlentheorie"
    (Kapitel 3) wurde ergänzt um
    - einen Anhang, der die Beispielaufrufe für den Zahlentheorie-
      Interpreter PARI-GP enthält (damit können Sie die Beispiele
      nicht nur mit Mathematica, sondern auch mit einem kostenlosen
      Mathematik-Paket durchführen) und um
    - Kapitel 3.11: Informationen zur aktuellen Diskussion über
      die Sicherheit des RSA-Verfahrens (vgl. Bernstein).
  - neu sind Kapitel 5.1 und 5.2 zu speziellen Signaturen.
  - neu in Kapitel 6 sind Informationen zur Motivation und
    Interoperabilität von Elliptischen Kurven.
  - neu in 1.3.04: 
    aktueller Stand der Kryptoanalyse von AES und RC5,
    aktuelle Entwicklungen bei der Faktorisierung (TWIRL) und
    in der Zahlentheorie ("Primes in P") ergänzt.
+ Einheitliche CrypTool-Präsentation zu 1.3.0x (keine Trennung
  mehr in Features von 1.2.xx und Neuerungen in 1.3.xx).
+ Online-Hilfe verbessert und erweitert (z.B. Hilfe für die
  neuen Funktionen und Einbau einer Zeittafel der Kryptographie).
  In 1.3.04 wurde z.B. der Abschnitt zu PGP / GnuPP aktualisiert.

Funktionalität:
===============
+ Ist ein Menüeintrag selektiert, der noch ein Untermenü hat,
  und man drückt F1, gelangt man nun auf die entsprechende
  Hilfeseite der Online-Hilfe zum ganzen Menü.
+ Hashwerte von Dateien berechnen, ohne die Dateien zu laden.
+ Verbesserung bei der Faktorisierung zusammengesetzter Zahlen:
  - Ausgabe der Details pro abgespaltenem Faktor.
  - Abfangen, wenn das Quadratic Sieve-Verfahren für die
    gegebene Zahl mehr Speicher braucht als verfügbar ist.
+ Erweiterung der Funktionalität im RSA-Kryptosystem:
  - interaktive Nutzung der Faktorisierung, wenn nur die
    öffentlichen Parameter bekannt sind (ohne händisch Ergebnisse
    aus einem extra-Faktorisierungsschritt zu übertragen),
  - Eingabe von Hexwerten möglich.
+ Verbesserungen im AES-Tool
  (die mit 1.3.03 ausgelieferte Version des AES-Tools wurde stark
  überarbeitet und ist nicht mehr kompatibel zu den Vorgänger-
  versionen):
  - Das AES-Tool bietet nun den vollen Funktionsumfang auch bei
    einem Aufruf von der Kommandozeile.
    Es kann entweder selbständig oder über die Menüfolge 
    Ver/Entschlüsseln \ Symmetrisch \ AES (selbstextrahierend)
    aus Cryptool heraus aufgerufen werden.
  - Der Dateityp (Exe oder Aes) stellt sich weitgehend selbst ein.
  - Bitte beachten Sie, dass die Ausgabe des AES-Tools auch bei der
    Dateiendung "Aes" nicht vollkommen identisch ist mit dem Ausgabe,
    die Sie erhalten mit der Menüfolge
    Ver/Entschlüsseln \ Symmetrisch \ Rijndael (AES).
+ Bei der Hill-Verschlüsselung können die Details zur aktuellen
  Schlüsselmatrix in einer Textdatei ausgegeben werden:
  - das aktuell in Optionen \ Textoptionen gewählte Alphabet,
  - die Hill-Schlüsselmatrix, auch kodiert in Zahlen und
  - eine Beispiel-Ver-/Entschlüsselung, berechnet im Detail.
+ Bei der Permutationsverschlüsselung (Doppelwürfel) wird nun
  der inverse Permutationsschlüssel berechnet und angezeigt.
+ Bei der manuellen Analyse der Substitutionsverschlüsselung kann
  man sich nun per Button zwischen seinen letzten Änderungen hin-
  und her bewegen.
  Außerdem kann man sich den Schlüssel, der als Ergebnis der
  manuellen Analyse entstand, temporär abspeichern, um ihn später
  wieder zu verwenden.
+ Langfassung des "Dialogs der Schwestern" in Deutsch und
  Englisch beigelegt (darin wird ein in der RSA-Demo
  behandelter Sonderfall des RSA-Verfahrens beschrieben).
+ Die Ausgabe bei der Entropie-Berechnung ist nun ausführlicher.
+ Bei der Anzeige des Zertifikatsinhalts wird nun auch der
  Public Key mit ausgegeben.
+ Visualisierung der einzelnen Schritte / Abhängigkeiten bei der
    -> Erzeugung einer elektronischen Signatur,
    -> Hybridverschlüsselung und -Entschlüsselung,
    -> Wirkung von Textänderungen auf den Hashwert (Hash-Demo)
       (Sensitivität von Hashverfahren).
+ In den Datenflussdiagrammen zur Visualisierung sehen Sie,
  welche Schritte in welcher Reihenfolge gemacht werden können.
  Wenn Sie einen Schritt anklicken, dessen Voraussetzungen noch
  nicht erfüllt sind, wird dies in einer Hilfebox erläutert.
+ Die schrittweise Verifikation einer RSA-Signatur ist nun auch
  möglich (dabei werden wie bei der Visualisierung der Hybrid-
  Entschlüsselung die schon vorhandenen Masken wiederverwendet).
+ Einführung des Menüpunktes Startoptionen.
+ Klarere Aufstellung des Analyse-Menüs.
+ Speichert der Benutzer einen Fensterinhalt ab, wird nicht mehr
  ein temporärer Dateiname vorgeschlagen, sondern ein inhaltlich
  passender Name: Cry-<Verfahren>-<Quelldateiname>.*
  Bei bewusst abgespeicherten Dokumenten wird dann der Dateiname
  im Fenstertitel angezeigt (anstatt der Beschreibung).

Ganz neu in 1.3.04 sind:
------------------------
+ Das Menü zu CrypTool im Windows Start\Programme-Menü enthält
  nun auch einen Verweis auf die Readme-Datei.
+ In den Visualisierungsdialogen wurde der Hintergrund anders
  gesetzt, um auch bei neuen Windows XP-Templates deutlich
  sichtbar zu sein.
+ Bei der Brute-Force-Attacke auf symmetrische Algorithmen werden
  nun mehr als 5 Jokerzeichen (bisher 20 Bit) zugelassen und die
  erwartete Zeit wird ausgegeben. Außerdem kann man die Breite für
  das hierbei genutzte Entropiefenster per Analyseoptionen einstellen.
+ Hochperformante Implementierung zum Suchen von Hash-Kollisionen 
  (Anwendung des Geburtstagsparadoxons). Damit kann man einen
  eingeschränkten Angriff auf Hash- bzw. Signatur-Verfahren 
  praktisch und für konkrete Dateien zeigen.
+ Visualisierung des Diffie-Hellman Schlüsselaustausch-Verfahrens.


5.3. Geplante Änderungen nach Version 1.3.04
     ---------------------------------------
Funktionalität:
+ Eine hochperformante Mustersuche, um entweder mehrfach vorkommende
  Muster beliebiger Länge in einer Datei zu finden oder um alle Patterns
  in einer Datei zu finden, die auch in einer anderen (vorzugebenden)
  Datei vorkommen.
+ Eine pure Kommandozeilenversion des AES-Tools auch für die
  Betriebssysteme OS/2 und Linux (aestool-os2; aestool-linux).
+ Visualisierung von Challenge-Response-Verfahren.
+ Visualisierung von Man-in-the-Middle-Attacks.


6. Mögliche Punkte für eine Weiterentwicklung
   ------------------------------------------
+ Weitere Algorithmen zu jedem Thema der Verschlüsselung oder
  Analyse hinzufügen, z.B.
  - ADFGVX bei den klassischen Verfahren,
  - RC5 und Ghost bei den symmetrischen Verfahren oder
  - Rabin bei den Public Key-Verfahren.
+ Parametrisierung, wo immer das möglich ist:
  Anbieten einer Option, um z.B. den Initialisierungsvektor,
  die Anzahl von Runden, die Schlüssel- oder Wortlänge oder
  das Padding zu setzen (z.B. für den RC5-Algorithmus - siehe
  RFC 2040).
  Diese Parameter müssen dann auch in das Format für den internen
  Schlüsselspeicher aufgenommen werden.
+ Ganz bewusst sind bei CrypTool die Schlüssel für die modernen
  Verschlüsselungsverfahren in Hex-Zeichen einzugeben. 
  Es ist Absicht, dass man in CrypTool zunächst sieht, welche Art
  Schlüssel die verschiedenen Algorithmen erwarten: bei den 
  klassischen Verfahren besteht der Schlüssel aus dem zugrunde
  liegenden Alphabet, bei den modernen Verfahren sind es 
  Binärdaten von 56 Bit bis 256 Bit Länge.
  Andererseits sind Benutzer gewohnt, ihre Eingaben per ASCII-Zeichen
  zu machen. Da in einer produktiven Anwendung der Schlüssel nicht
  aus ASCII-Zeichen bestehen sollte, ist es besser, wenn man schon
  ein ASCII-Passwort als Grundlage verwendet, daraus mit einem 
  vernünftigen Verfahren einen Schlüssel herzuleiten. 
  In CrypTool könnte man die Anforderung "ASCII-Schlüsseleingabe" und
  Zeigen, dass gute Hex-Keys zu verwenden sind, folgendermaßen 
  miteinander verbinden:
  In dem HEX-Schlüsseleingabe-Dialog sollte man per Button die Funktion 
  "Einzelverfahren \ Schlüssel aus Passwort erzeugen" aufrufen können. 
  Der Dialog ist dann mit der richtigen Schlüssellänge parametrisiert 
  und der generierte Schlüssel wird in die HEX-Schlüsseleingabe übernommen. 
  Damit dies auch für AES-256 funktioniert, müsste noch die SHA-256-
  Hashfunktion eingebaut werden.
+ In den Dialogen in CrypTool können Zahlen nicht immer in allen
  Darstellungsarten eingegeben werden (z.B. kann im Dialog RSA-Kryptosystem
  die zu verschlüsselnde Nachricht als Text mit frei einzustellendem 
  Alphabet und als Zahl mit 4 verschiedenen Basen) eingegeben werden,
  die Primzahlen dagegen kann man "nur" als Zahl im Zehnersystem bzw. als
  Ausdrücke mit Zahlen im Zehnersystem eingegeben).
  Nützlich wäre es, wenn man aus CrypTool heraus einen Taschenrechner
  als a-modales Fenster aufmachen könnte, der Terme mit Zahlen beliebiger
  Basis als Eingabe nimmt und die Ausgabe in mehreren Feldern in 
  verschiedenen Zahlensystemen parallel anzeigt. Von hier aus sollte
  man dann die Zahlen per Knopfdruck ins Clipboard bringen können oder
  per Maus in die Eingabefelder der CrypTool-Dialogboxen ziehen können.
+ Wörterbuch für alle Angriffe benutzen, nicht nur für die
  Substitution.
+ Einbau einer erweiterten Mustersuche (Suche mit vorgegebenen normierten
  und regulären Mustern und Suche nach unbekannten, aber mehrfach
  vorkommenden Mustern im Dokument, ...), indem der Dialog zum
  Massen-Vergleich mit bekannten Mustern in einer anderen Datei
  entsprechend erweitert wird.
  Zur Suche könnte man auch Ersetzen ergänzen.
+ Analyse neu implementieren für
  - homophone Verschlüsselung.
+ Analyse verbessern (nicht performant und korrekt genug bisher) für
  - monoalphabetische Substitution
    (plus explizite Anzeige von vertauschten Digrammen wie "ie"/"ei"
    und von Doppelzeichen wie "mm"),
  - Playfair-Verschlüsselung,
  - asymmetrische Kryptoverfahren.
+ Alle Anzeigemodule in einem konsistenten Klassenbaum
  zusammenfassen.
+ Entsprechend der MFC-Vorgehensweise für verschiedene Fenstertypen
  gibt es für Text- und Binärdateien verschiedene Menübäume.
  Da diese Typen nicht so sehr unterschiedlich sind, könnte
  man die Anzeigeform als View betrachten und die entsprechenden
  Funktionen auf beide anwenden (und z.B. beim Versuch der Playfair-
  Verschlüsselung mit einem Nicht-Textfile alle Buchstaben außerhalb
  des Alphabets ignorieren) oder in einer gemeinsamen Menüstruktur
  die Menüeinträge dynamisch ein-/ausblenden. 
+ Die Sourcen so umstellen, dass die Ausgabe/Anzeige komplett von
  den Kryptomodulen getrennt ist (erleichtert Portierungen und
  Fehlersuche).
+ Für den Benutzer konfigurierbar einstellbar machen, ob neue Fenster
  wie bisher innerhalb des Hauptfensters erscheinen oder als "freie"
  Fenster danebenstehen.
+ Für den Benutzer konfigurierbar einstellbar machen, wie groß die
  Text- und Binärdateien sein können, die CrypTool laden kann.
+ In der Anzeige für Grafiken eine Vergrößerungsfunktion einbauen
  und / oder die Koordinaten anzeigen, an denen sich die Maus
  befindet.
+ Korrekturmöglichkeit einzelner Zeichen bei der Analyse von XOR,
  ADD, Vigenere.
+ Anzeigen des zweit-, dritt-, ... -besten Treffers bei der
  XOR/ADD-Analyse (dies kann zu einer kürzeren Schlüssellänge
  führen).
+ Einzelne Dialogboxen (z.B. N-Gramm-Analyse, Manuelle Analysen,
  Hybriddemo) als amodale Fenster erzeugen, so dass man beliebig
  zwischen Hauptfenster und Auswertungsfenster springen kann
  (aufwendigere Steuerung, Erlauben oder Abfangen von Mehrfachauf-
  rufen derselben Dialogbox, evtl. Update nach Fokus-Wechsel bzw.
  nach Änderung der Originaldaten im Hauptfenster, ...).
+ Autokorrelation: vor der Überlagerung noch Operationen auf den
  Blöcken ausführen (XOR, ADD, ...); macht das Sinn?
+ Editieren der Homophonen-Schlüssel (benötigt bei der Analyse
  der Homophonen Verschlüsselung).
+ Bei gleitender Entropie: Automatische Anzeige der
  entsprechenden Stellen mit hoher Entropie.
+ Hillverfahren: Schlüsselmatrix transponieren.
+ Hillverfahren: Eingabe von Zahlen in die Schlüsselmatrix.
+ Update der Miracl-Lib auf eine neuere Version als 4.4.3.,
  sofern dies eine Performance-Verbesserung bringt.
+ Portierung nach Linux (eine Secude-Lib bzw. Miracl-Lib stehen
  zur Verfügung). Danach besteht eine große Nachfrage.
+ Portierung nach Java (eine Secude-Lib dafür steht zur
  Verfügung).
+ Kryptographisch starke elliptische Kurven erzeugen und damit
  Implementierung eines auf Elliptischen Kurven basierenden
  Kryptosystems. Dazu könnte man das Kryptosystem von Menezes
  und Vanstone nehmen, das 1993 von diesen Autoren vorgeschlagen
  wurde: A. Menezes and S. Vanstone,
         "Elliptic curve cryptosystems and their implementation",
         Journal of Cryptology, 6 (1993), Seiten 209-224.
+ Weil kryptographische Strukturen und Formate häufig ASN.1-
  kodiert sind: Integration eines ASN.1 Dekodier-Tools.
+ Visualisierung:
  - Generell ist die Visualisierung der Abhängigkeiten und Abläufe
    bei Protokollen (nicht nur bei "einfachen" Algorithmen) eine
    sinnvolle Erweiterung.
  - Angriffe auf schwache RSA-Schlüssel werden in der Online-Hilfe 
    per Hilfe\Szenarien\RSA-Kryptosystem (Demonstration), unter 
    "3.) Der Angriff auf das RSA-Verfahren" beschrieben: durch
    Faktorisieren des Moduls kann man das Verfahren knacken.
    Dies ist auch implementiert, aber noch nicht visualisiert.
  - Angriffe auf andere asymmetrische Verfahren sind in CrypTool
    bisher noch gar nicht behandelt. Um Diffie-Hellman, DSA oder
    EC-DSA anzugreifen, muss "diskrete Logarithmen" berechnen.
    Auch dies könnte man nach dem Implementieren wieder 
    visualisieren.
+ Zufallszahlen:
  - Bisher konzentriert sich CrypTool auf kryptographisch starke 
    Pseudozufallzahlgeneratoren. Nur im Secude-Generators wird
    eine "echte" Zufallsquelle einbezogen. 
    Die Gewinnung "echter" Zufallsdaten über Mausbewegungen etc.
    wäre eine gute Ergänzung für CrypTool (Yarrow, PGP, ...). 
  - In Deutschland wird die Evaluierung von deterministischen 
    Zufallszahlengeneratoren durch die AIS 20 (seit Dezember 1999;
    AIS = Anwendungshinweise und Interpretationen zum Schema) und 
    die Evaluierung von physikalischen Zufallszahlengeneratoren 
    durch die AIS 31 (seit September 2001) geregelt. 
    Vor allem die AIS 31 ist auch außerhalb Deutschlands auf 
    großes Interesse gestoßen.
    Die AIS 20 und AIS 31 befinden sich in deutscher und englischer
    Sprache auf der BSI-Website:
    http://www.bsi.bund.de/zertifiz/zert/interpr/ais20.pdf   
    http://www.bsi.bund.de/zertifiz/zert/interpr/ais31.pdf   
    http://www.bsi.bund.de/zertifiz/zert/interpr/trngkr31.pdf
    Es wäre eine gute Ergänzung für CrypTool, diese Standard-
    anforderungen zur Evaluierung von Zufallszahlen  
    einzubauen und dies auch zu visualisieren.
+ Weitere Standards implementieren und direkt über die Menüs
  bzw. aus der Online-Hilfe an alle Stellen verzweigen, wo diese
  Standardverfahren (z.B. PKCS#5) verwendet werden (Hauptarbeit
  dabei sind nur User Interface und Dokumentation).
+ Ähnlich wie CrypTool "gute" Schlüssel aus Passworten generiert (PKCS#5),
  sollte eine DOKUMENTIERTE Schnittstelle da sein zu den verschiedenen
  Verfahren, die gute Passworte generieren.
+ CrypTool als Frontend für zahlentheoretische Funktionen und
  Werte erweitern.


6.1. Sinnvolle Aufgaben für die Einarbeitung des neuen Maintainers
     ------------------------------------------------------------
+ Einbau des RC5-Algorithmus wie oben beschrieben, um zu sehen,
  an welchen Stellen überall die Sourcen dafür zu ergänzen sind.
+ alle möglichen Arten von Transpositionen und Superpositionen
  für den Inhalt von Textfenstern in einem ansprechenden Dialog
  anbieten.
+ Testbett mit Beispielen und Lösungen erzeugen, damit man das
  Testen automatisieren kann und damit man sicherstellen kann,
  dass durch Programmänderungen nicht alte funktionierende
  Funktionalität negativ beeinflusst wird:
  a) Interface, um Testaufgaben manuell in Dialogboxen zu laden
  b) Schnittstelle schaffen, mit der sich die Testaufgaben aus
     einer Datei selbst in die Dialogboxen laden.
     Vielleicht sogar Script-Steuerung für alle Dialoge oder
     automatische Testtools vom Markt einsetzen.
  c) Commandline-Interface schaffen (am besten nachdem Krypto und
     Anzeige im Code getrennt wurden), das ohne Dialogboxen alle
     Aufgaben aus einer Datei per Schnittstelle ausliest und die
     Lösungen wieder in eine Datei schreibt:
     -> Abgleich automatisierbar
     -> neue Version leichter testbar.




7. Kurze Historie der freigegebenen Hauptversionen
   -----------------------------------------------

Version   Datum		Größe des Windows-Setups	Freigabe durch
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
1.3.02    viele neue Funktionen gegenüber 1.3.00
1.3.03    viele kleine Bugfixes und Verbesserungen der
          Dokumentation.
1.3.04    einige neue Funktionalität (siehe Kapitel 5.2), einige
          kleine Bugfixes (Absturz bei Playfair-, N-Gramm-Analyse, RSA),
          und Verbesserung und Erweiterung der Dokumentation.



8. Feedback bei Fehlern
   --------------------
Sollten Sie Probleme haben oder Fehler finden, wenden Sie sich
bitte mit einer Beschreibung des Problems per e-mail an
- joerg-cornelius.schneider@db.com  oder
- bernhard.esslinger@db.com / besslinger@web.de oder
- an die Mailingliste: cryptool-list@sec.informatik.tu-darmstadt.de

Für Anregungen jeglicher Art bezüglich CrypTool sind wir immer
dankbar und helfen Ihnen gern, wenn es unsere Zeit erlaubt.

Auch würden wir uns freuen, wenn Sie uns mitteilen, wie und wo Sie
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
mit CrypTool die Aufgabe mit wenigen Mausklicks lösen.

10.2. c't 14/2001, S. 204-208
      -----------------------
In diesem renommierten und auflagenstarken deutsch-sprachigen
Computermagazin wurde im Juli 2001 ein 5-seitiger Artikel zu
CrypTool veröffentlicht.

10.3. DuD Oktober 2002
      ----------------
In der deutsch-sprachigen Fachzeitschrift "DuD Datenschutz und
Datensicherheit", Ausgabe 10/2002 erschien unter dem Titel
"CrypTool - spielerischer Einstieg in klassische und moderne
Kryptographie. Neue Version - fundierte Awareness in Deutsch
und Englisch" ein 4-seitiger Artikel über CrypTool.

10.4. BSI Bürger-CD "Ins Internet - mit Sicherheit"
      ---------------------------------------------
Das Bundesamt für Sicherheit in der Informationstechnik (BSI) hat
zusammen mit dem Deutschen Bundesinnenministerium zur CeBIT 2002
eine CD veröffentlicht, die die Bürger aufklärt, wie man mit
Computern und Internet umgeht und wie man sich sicher im Internet
bewegen kann.
Auf dieser CD ist auch CrypTool enthalten, um das Verständnis der
kryptographischen Sicherheitsfunktionen zu verbessern.
Von dieser CD sind mehr als 600.000 Stück produziert und
zum Beispiel mit der Zeitschrift PC-Welt 8/02 verteilt worden.
Der Inhalt dieser CD floss ein in das BSI Sicherheits-Portal
"für unerfahrene Internet-Nutzer" (http://www.bsi-fuer-buerger.de).

10.5. Freeware-Projekte Crank, Griffon, CAP, CryptAid, etc.
      ------------------------------------------------------
Available with source code are:
- http://freshmeat.net/projects/crank/
  Crank wurde im Januar 2001 von Matthew Russell begonnen und unter
  der GNU General Public Licence (GPL) freigegeben.
  Im Crank-Projekt soll unter Linux ein Programm mit grafischer
  Oberfläche erstellt werden, das das möglichst automatisierte
  Brechen von klassischen Kryptoalgorithmen ermöglicht.
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
  Griffon ist ein GTK+ GUI Kryptoanalyse-Paket für Pre-digital Ciphers.
  Es enthält monoalphabetische Transposistion, Substitution und Playfair.
  Das Tool liegt nur in englischer Sprache vor.
  Die aktuelle Version 1.0 wurde im November 2000 freigegeben.

Die einzigen weiteren uns bekannten brauchbaren Programme, die
Kryptographie und Kryptoanalyse (unter einer graphischen
Oberfläche) verbinden, für die aber kein Source-Code freigegeben ist,
sind:
- CAP von Dr. Richard Spillman
  Die aktuelle Version 4 gibt es seit November(?) 2002.
  http://www.cs.plu.edu/courses/privacy/index.htm
- CryptAid von David Lovelock
  (wahrscheinlich seit 1997 nicht mehr weitergepflegt)
  http://archives.math.utk.edu/software/msdos/miscellaneous/cryptaid/.html
- das Visual Basic-Programm "Cryptological Mathematics" von Prof. R.E. Lewand
  (anschauliche Darstellung einiger zahlentheoretischer Funktionen und
  Funktionen zur Ver- und Entschlüsselung;
  keine Funktionen zur Kryptoanalyse; Software zu seinem Buch)
  http://faculty.goucher.edu/blewand/cryptomath/companion_software.htm
- John Trafton's studentisches Cryptography-Projekt in Java
  (einzelne statistische Funktionen und klassische Verschlüsselungs-
  verfahren; verfügbar seit Dezember 2002)
  http://phoenix.goucher.edu/~jtrafton/Crypto.

Falls uns hier etwas entgangen ist, würden wir uns über eine Nachricht
freuen - wir vervollständigen oder korrigieren diese Liste gerne.

Außerdem wollen wir hier ausdrücklich das Angebot machen, die
Anstrengungen für diese einzelnen Programme in ein einziges
Programm zu integrieren. Wir freuen uns über jede Kooperation!!




11. Anhang
    ------

11.1. CrypTool unter Linux mit Wine
11.1.1. .... CrypTool installieren
11.1.2. .... Wine-Konfiguration
11.1.3. .... CrypTool ausführen



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
von riched32.dll. Wenn Sie unter CrypTool eine Datei öffnen und
die falsche Version von riched32.dll benutzt wird, erscheint ein
leeres Fenster.
Wahrscheinlich taucht das Problem nicht auf, wenn Wine eine
existierende Windows-Partition benutzen kann.
Wenn Sie Wine ohne Windows benutzen, können Sie das Problem mit
folgenden Schritten lösen:
 - Installieren Sie CrypTool unter Wine.
 - Besorgen Sie sich riched32.dll (z.B. Version 5.0.1458.47)
   und kopieren Sie die Datei in das Installationsverzeichnis
   von CrypTool. Eventuell müssen sie analog mit weiteren DLLs
   verfahren, die von riched32.dll benutzt werden. Beachten Sie
   bitte die Fehlerausgaben von Wine.
 - Konfigurieren Sie Wine so, dass es diese Datei nutzt.
   In der Standard-Konfiguration ist das so.
   Funktioniert das bei Ihnen nicht, schreiben Sie folgende Zeile
   in die [DllOverrides]-Sektion der Wine-Konfigurationsdatei:
   "riched32" = "native,builtin"


11.1.3. CrypTool ausführen
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
  Mit der folgenden Kommandozeile können Sie die Online-Hilfe
  anzeigen:

  $ wine winhlp32 CrypTool.hlp

