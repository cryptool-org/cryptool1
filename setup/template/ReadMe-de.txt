==================================================================
              CrypTool, Version 1.3.01x, April 2002
                  (c) Deutsche Bank AG 1998-2002
                  (c) Universität Siegen und Karlsruhe
                         Frankfurt am Main
==================================================================



                       Inhalt

 1. .... Kurzbeschreibung
 1.1. .... Was beinhaltet die Distribution?
 1.2. .... Danke
 1.3. .... Neuer Maintainer in der Zukunft
 2. .... Beschränkungen und Voraussetzungen
 2.1. .... Installation unter Windows 95
 2.2. .... Interaktive Online-Hilfe unter Windows XP
 2.3. .... Unterstützung verschiedener Sprachen
 2.4. .... Einschränkungen in den verwendeten Bibliotheken
 3. .... Installation
 4. .... Dateiliste
 4.1. ..   Überprüfen der Integrität der heruntergeladenen Dateien
 5. .... Wie Sie starten...
 6. .... Neuerungen in CrypTool 1.3.00
 6.1. .... Klassische Verfahren
 6.2. .... Symmetrische Verfahren
 6.3. .... Asymmetrische Verfahren
 6.4. .... Formatierung / Anzeige / Navigation
 6.5. .... Hilfe / PDF-Skript
 6.6. .... Sonstiges
 6.7. .... Änderungen von Version 1.3.00 zu Version 1.3.01
 6.8. .... Geplante Änderungen von Vers. 1.3.01 zu Vers. 1.3.02
 7. .... Mögliche Punkte für eine Weiterentwicklung
 8. .... Kurze Historie der Hauptversionen
 9. .... Roadmap
10. .... Feedback bei Fehlern
11. .... Kontaktadressen
12. .... Verweise
12.1. .... Wirtschaftswoche Spezial
12.2. .... c't 14/2001, S. 204-208
12.3. .... BSI Bürger-CD "Ins Internet - mit Sicherheit"
12.4. .... Freeware-Projekt Crank
13. .... Anhang
13.1. .... CrypTool unter Linux mit Wine



1. Kurzbeschreibung
   ----------------
Dieses Readme gehört zur kostenlosen Distribution von CrypTool,
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
und auf der Einstiegsseite der Onlinehilfe erläutert.

1.1. Was beinhaltet die Distribution?
     --------------------------------
Neben dem Programm selbst gibt es eine umfangreiche Dokumentation,
die aus 4 Teilen besteht:
a) dieser Readme-Datei
b) Online-Hilfe (Programm-bezogen, mit Beispiel-Szenarien)
c) Skript (zum Thema Kryptographie, beigelegt als PDF-Datei)
d) Demos (Programmteile, die Einzelthemen/Grundlagen erläutern).

CrypTool ist keine Applikation, mittels derer im Wirkbetrieb Daten
verschlüsselt oder anderweitig gesichert werden sollten. Es ist
eine reine Demonstration, die vor allem für Ausbildungszwecke
eingesetzt wird.

- Dazu beinhaltet CrypTool eine sehr umfangreiche Sammlung krypto-
  graphischer Algorithmen, die hervorragend dokumentiert ist.
  Somit ist CrypTool sehr gut geeignet zur Ausbildung und zur
  Mitarbeiter-Sensibilisierung für IT-Sicherheit.

- Die meisten der krytographischen Basisalgorithmen stammen von:
  - der Industrie-bewährten Secude-Bibliothek (Version 5.4.15)
    (www.secude.com) und von 
  - der Miracl-Bibliothek (Version 4.4.3) 
    (http://indigo.ie/~mscott/).
  Somit ist CrypTool auch eine hervorragende Referenzimplemen-
  tierung.

- Die Kryptoanalyse der meisten der implementierten klassischen
  Verfahren ist automatisiert. Die Analyse der modernen Verfahren
  ist eingeschränkt, so daß CrypTool nicht als Hackertool
  eingesetzt werden kann.

- Zum Erstellen selbstentpackender Executables ist in CrypTool
  ein Programm integriert, das auch eigenständig benutzt werden
  kann.
  Darin wird aus einem Passwort ein Session-Key erzeugt, mit dem
  ein beliebiger Dateiinhalt AES-verschlüsselt wird.

1.2. Danke
     -----
Zu CrypTool haben viele verschiedene Personen - insbesondere auch
in ihrer Freizeit - beigetragen. Herzlichen Dank.

Dr. Carsten Elsner erlaubte uns, seine Geschichte "Der Dialog der
Schwestern" als PDF-Datei beizulegen.
Der Verfasser, als alleiniger Inhaber aller Rechte an dem Werk, 
räumt dem CrypTool-Maintainer das ausschließliche Vervielfälti-
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

Wir würden uns sehr freuen, wenn sich nicht nur die bisherigen 
Entwickler, sondern auch viele neue an der Weiterentwicklung von
CrypTool beteiligen.
Die Homepage von CrypTool bleibt weiterhin www.cryptool.de.



2. Beschränkungen und Voraussetzungen
   ----------------------------------
CrypTool erfordert eine Win32 Umgebung, wie sie unter Windows 95,
Windows 98, Windows Me, Windows NT (ab 4.0), Windows 2000 und 
Windows XP gegeben ist.

CrypTool funktioniert grundsätzlich auch unter FreeBSD/Linux mit
Wine (mit Abstrichen an Funktionalität und Stabilität).
Siehe Anhang 13.1.


2.1. Installation unter Windows 95
     -----------------------------
Bei älteren Windows 95 Systemen erhalten Sie beim Aufruf von
CrypTool die Meldung "kann 'secude.dll' nicht finden". In diesem
Fall können Sie CrypTool nur eingeschränkt nutzen.

Die Algorithmen der Secude-Bibliothek werden beim Start von
CrypTool mit Hilfe der Bibliothek "msvcrt.dll" dynamisch geladen.
Leider unterstützt unter Windows 95 nicht jede Version von
"msvcrt.dll" das Einbinden der Secude-Bibliothek. Zu dem
Lieferumfang verschiedener Programme gehört eine neuere Version
von "msvcrt.dll" - kopieren Sie diese Datei in das Windows-
Verzeichnis oder in das Verzeichnis von CrypTool.


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

Workaround anhand eines Beispiels: Einzelverfahren / RSA-Demo
Wenn hier das Untermenü zu "RSA-Demo" aufklappt, Sie aber die 
Hilfe zum Menüeintrag "RSA-Demo" haben wollen, müssen Sie - nur
unter Windows XP - das Untermenü von "RSA-Demo" erst mit Escape
(Esc) oder den Pfeiltasten wieder einklappen, dann funktioniert 
das Aufrufen der Online-Hilfe mit F1 auch unter Windows XP.


2.3. Unterstützung verschiedener Sprachen
     ------------------------------------
Programm, Hilfesystem und Dokumentation sind mehrsprachig aus-
gelegt (zur Zeit englisch und deutsch).

Für jede unterstützte Sprache gibt es ein eigenes Setup mit dem
entsprechenden ausführbaren Programm (der Versuch, alle Sprachen
in ein einziges Executable einzubinden wurde wieder aufgegeben,
da die automatische Spracheinstellung beim Anwender (anhand seiner
Systemeinstellungen) nur unter Windows 4.0, nicht aber unter 
Win9x, korrekt funktionierte).


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
  Ab Version 1.3.00 können Sie RSA- und DSA-PSEs als PKCS#12-
  Struktur exportieren bzw. importieren.

Für den Fall, dass mehrere Benutzer dieselbe CrypTool- 
Installation verwenden wollen, müssen die Zugriffsrechte auf den
Verzeichnissen pse\ und pse\pseca\ und den darin enthaltenen
Dateien für alle Benutzer auf Vollzugriff gesetzt werden.

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
CrypTool-de.cnt .. Indexliste für das Hilfesystem zu CrypTool
CrypTool-en.cnt .. Die englische Fassung von CrypTool-de.cnt
CrypTool.exe...... Das ausführbare Programm.
aestool.exe....... Ein Programm, das Dateien in sich selbst
                   entpackende Programme verschlüsselt. Zur
                   Entschlüsselung müssen Sie das korrekte
                   Paßwort eingeben.
CrypTool-de.hlp... Hilfesystem zu CrypTool mit Beispielszenarien.
CrypTool-en.hlp .. Die englische Fassung von CrypTool-de.hlp
EC-Param.ini...... Initialisierungsdatei für auf Elliptischen
                   Kurven basierende Public Key-Verfahren.
secude.dll........ Bibliothek kryptographischer Funktionen von der
                   SECUDE GmbH.
ticket............ Lizenz für die SECUDE-Bibliothek.
irunin.*.......... Diese Dateien sind nötig für Installation und
                   Deinstallation von CrypTool.

script-de.pdf..... Ein Skript (deutsch) über Kryptographie,
                   Primzahlen, Zahlentheorie und die Mathematik
                   hinter einigen Algorithmen.
script-en.pdf..... Die englische Fassung von script-de.pdf
DialogSchwestern.pdf.... Fantasy-Geschichte von Dr. Elsner, in der
                         eine Variante des RSA-Kryptosystems 
                         beschrieben wird.

Referenztexte\.... Dieses Verzeichnis enthält Textdateien in den
                   Sprachen Deutsch, Englisch, Französisch,
                   Spanisch und Latein. Diese Dateien werden
                   standardmäßig als Referenz für die Analyse von
                   Chiffretexten herangezogen.
                   Diese Dateien sind schreibgeschützt.

Referenztexte\deutsch.txt // Auszug aus dem Umsatzsteuergesetz
             \english.txt // Auszug aus der Agenda 21[UN-Dokument]
             \genesis-de.txt  // Buch Genesis in den Sprachen 
             \genesis-en.txt  // deutsch, englisch, französisch,
             \genesis-fr.txt  // spanisch und lateinisch.
             \genesis-es.txt
             \genesis-lt.txt

Beispieldateien\.. Dieses Verzeichnis enthält unterschiedliche
                   Beispieldateien, die in den Szenarien verwendet
                   werden. Dateien mit der Endung ".txt" sind
                   Textdateien. Alle anderen Dateien sind binär.
                   Dateien mit dem Format "XX-enc-YY.*" sind
                   verschlüsselte Dateien. Bitte verändern Sie
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
                   Namensmuster cry*.* in das Temp-Verzeichnis.
CrypTool.ini...... Diese Datei befindet sich im Windows-
                   Verzeichnis und enthält die Dateinamen der
                   zuletzt bearbeiteten Dateien.


4.1. Überprüfen der Integrität der heruntergeladenen Dateien
     -------------------------------------------------------
Die Integrität von Dateien kann mit Hashwerten überprüft
werden. Hashwerte sind wie Fingerabdrücke: wenn man den 
Hashwert einer heruntergeladenen Datei neu berechnet und mit
den Werten auf der CrypTool-Homepage vergleicht, kann man
sehen, ob man eine Kopie der Originaldatei hat oder nicht. 
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

Zur Überprüfung können Sie die oben genannten Tools verwenden
oder das Programm CrypTool selbst.

Ab Version 1.3.01 kann man die Hashwerte von "externen"
Dateien berechnen lassen, ohne sie in CrypTool zu laden:
- Menü Einzelverfahren / Hashwerte / Hashwert einer Datei...
- Öffnen der entsprechenden Datei
- Vergleich mit dem Wert hier (richtiger Hashalgorithmus!).

Aus Sicherheitsgründen empfiehlt sich der Vergleich bei 
Binärdateien (EXE, DLL, PDF, ...), wenn Sie nicht ganz sicher
sind, dass Ihr Rechner unberührt ist.




5. Wie Sie starten...
   ------------------
Wenn Sie CrypTool starten, öffnen sich zugleich die Arbeitsfläche
von CrypTool und im Vordergrund ein kleines Begrüßungsfenster,
von dem aus Sie auch sofort auf die Einstiegsseite der Hilfe
verzweigen können.
Lesen Sie die Hinweise und Tips der Hilfe-Einstiegsseite und
öffnen Sie dann auf der CrypTool-Arbeitsfläche eine
unverschlüsselte Datei aus dem Unterverzeichnis "Beispieldateien".
Sie können jetzt viele der Funktionen von CrypTool an dieser Datei
ausprobieren.

Einen schnellen Einstieg in CrypTool finden Sie, wenn Sie einige
Szenarien der Hilfe durchspielen (die Szenarien stehen im
Inhaltsverzeichnis der Hilfe unter "Beginn der Arbeit mit
CrypTool").

Wir wünschen viel Spaß beim Ausprobieren der vielen Funktionen von
CrypTool.



6. Neuerungen in CrypTool 1.3.00
   -----------------------------
Seit CrypTool 1.202 (Dez. 2000) kamen folgende Erweiterungen und
Bugfixes hinzu:
- CrypTool ist nun komplett in gleicher Weise in deutsch und
  englisch.
- Alle Dialoge wurden im Hinblick auf Konsistenz und
  Verständlichkeit überarbeitet.
- Die bisherigen Einschränkungen (maximale Datengröße 64 Kb) für
  die Windows-Versionen Win95 und Win98 wurden aufgehoben.
- die letzte Einstellung zu einem Verfahren (wie gewählter
  Schlüssel oder Alphabet) wird Programm-intern aufbewahrt.

6.1. Klassische Verfahren
     --------------------
+ Homophone Verschlüsselung neu
+ Permutationsverschlüsselung neu
+ Zufallsdaten erzeugen neu
  Die folgenden "Pseudozufallsgeneratoren" werden angeboten:
  - der von der SECUDE-Lib bereitgestellte Zufallsgenerator
  - ein durch den Parameter N einzustellender "x^2 mod N"
    Zufallsgenerator
  - Linearer Kongruenz-Generator
  - Inverser Linearer Kongruenz-Generator
+ Statistische Analysen für Zufallsdaten (z.B. FIPS-140-1) neu
+ Periodenanalyse verbessert
+ N-Gramm-Analyse ergänzt (mit der Möglichkeit, die Ergebnisse
  abzuspeichern)
  Die N-Gramm Analyse ist für Binärdateien auf 64 kBytes und für
  Textdateien auf 256 kBytes beschränkt (längere Eingaben werden
  auf die maximale Eingabelänge gekürzt).
+ Fehler bei Vigenere und Caesar behoben (beliebige Textdateien)
+ Playfairanalyse verbessert

6.2. Symmetrische Verfahren
     ----------------------
+ ein eigenständiges Programm kann selbstentpackende Programme
  erzeugen.
  Damit kann man eine beliebige Datei Paßwort-geschützt mit AES
  verschlüsseln (durch Eingabe eines Hexadezimal-Schlüssels).
+ Veranschaulichen, wie ein Schlüssel aus einem Paßwort nach
  PKCS#5 generiert wird [aus der Texteingabe (Paßwort) wird ein
  Hexadezimal-Schlüssel erzeugt, der gegen Wörterbuchangriffe
  resistent ist. Parameter: Ausgabe-Schlüssellänge, Saat für den
  Zufallsgenerator, Anzahl der "Hash"-Iterationen,
  Hashverfahren (MD2, MD5, SHA-1)].

6.3. Asymmetrische Verfahren
     -----------------------
+ Demo zur Zahlentheorie und zum RSA-Verfahren neu
   - Primzahlen generieren
   - Zahlen (schrittweise) und mit verschiedenen Verfahren
     faktorisieren
   - das RSA-Kryptosystem transparent durchführen (auch für
     selbst-gewählte Primzahlen) (damit kann auch der "Dialog
     der Schwestern" aus der c't 25/1999 nachvollzogen werden)

6.4. Formatierung / Anzeige / Navigation
     -----------------------------------
+ intern werden die Keys/Eigenschaften aller Verfahren
  getrennt gespeichert. Speicherung und Abruf der dabei
  eingegebenen Schlüssel erfolgt über 2 Buttons. Dadurch
  wird die Wiederverwendung deutlich einfacher, wenn
  wie in klassischen Verfahren wie Playfair sehr spezifische
  Formate verwendet werden.
+ Das Umschalten von Hexanzeige nach Textanzeige für
  Nicht-Textdateien ist unterbunden.
+ Beim Anzeigewechsel das "Vater"-Fenster beibehalten.
+ Hotkeys zur Verzweigung in das PDF-Skript eingefügt.

6.5. Hilfe / PDF-Skript
     --------------------
+ Ergänzung des Skripts um eine Einführung in die elementare
  Zahlentheorie mit vielen Beispielen.

6.6. Sonstiges
     ---------
+ PKCS#12-Export und -Import von RSA- und DSA-PSEs und damit
  von den darin gespeicherten Schlüsseln. 
+ Neue Webseite
   - zusätzliche Infos: Präsentation auf deutsch und englisch.


6.7. Änderungen von Version 1.3.00 zu Version 1.3.01
     -----------------------------------------------
Source:
+ Überarbeitung des Quelltextes für die Übergabe an den neuen
  Maintainer.
+ Weitere Automatisierung beim Erzeugen des Setup-Paketes
Webseite:
+ Enthält die Hashwerte der herunterladbaren Dateien und
  ermöglicht so einen Check der Integrität der auf dem
  Computer befindlichen Dateien.
Dokumentation:
+ Einheitliche CrypTool-Präsentation zu 1.3.01 (keine Trennung
  mehr in Features von 1.2.xx und Neuerungen in 1.3.xx).
+ Online-Hilfe verbessert und erweitert (z.B. Hilfe für die
  neuen Funktionen und Einbau einer Zeittafel).
Funktionalität:
+ Ist ein Menüeintrag selektiert, der noch ein Untermenü hat,
  und man drückt F1, gelangt man nun auf die entsprechende
  Hilfeseite der Online-Hilfe zum ganzen Menü.
+ Hashwerte von Dateien berechnen, ohne sie zu laden.
+ Visualisierung der einzelnen Schritte / Abhängigkeiten bei
  der Hybridverschlüsselung und -Entschlüsselung.
+ Die schrittweise Verifikation einer RSA-Signatur ist nun auch
  möglich (dabei werden wie bei der Visualisierung der Hybrid-
  Entschlüsselung die schon vorhandenen Masken wiederverwendet).
+ Verbesserung bei der Faktorisierung zusammengesetzter Zahlen:
   - Ausgabe der Details pro abgespaltenem Faktor.
   - Abfangen, wenn das Quadratic Sieve-Verfahren für die
     gegebene Zahl mehr Speicher braucht als verfügbar ist.
+ Erweiterung der Funktionalität im RSA-Kryptosystem
  - interaktive Nutzung der Faktorisierung, wenn nur die
    öffentlichen Parameter bekannt sind,
  - Eingabe von Hexwerten möglich.
+ Verbesserungen beim AES-Tool.
+ Bei der Hillverschlüsselung können die Details zur aktuellen 
  Schlüsselmatrix in einer Textdatei ausgegeben werden:
  - das aktuell in Optionen/Textoptionen gewählte Alphabet,
  - die Hill-Schlüsselmatrix, auch kodiert in Zahlen und 
  - eine Beispiel-Ver-/Entschlüsselung, berechnet im Detail. 
+ Langfassung des "Dialoges der Schwestern" in Deutsch und
  Englisch beigelegt (darin wird ein in der RSA-Demo 
  behandelter Sonderfall des RSA-Verfahrens beschrieben) 
  - vielen Dank an den Autor, Herrn Dr. Carsten Elsner.
+ Visualisierung 
  - der einzelnen Schritte / Abhängigkeiten bei der
    Erzeugung einer elektronischen Signatur.


6.8. Geplante Änderungen von Version 1.3.01 zu Version 1.3.02
     --------------------------------------------------------
Funktionalität:
+ Visualisierung 
  - der Wirkung von Textänderungen auf den Hashwert 
    (Sensitivität von Hashverfahren)


7. Mögliche Punkte für eine Weiterentwicklung
   ------------------------------------------
+ Weitere Algorithmen zu jedem Thema der Verschlüsselung oder
  Analyse hinzufügen, 
  z.B. ADFGVX bei den klassischen Verfahren,
  RC5 und Ghost bei den symmetrischen Verfahren oder 
  Rabin bei den Public Key-Verfahren.
+ wo immer Algorithmen parametrisiert werden können: Anbieten
  einer Option, um z.B. den Initialisierungsvektor, die Anzahl
  von Runden, die Schlüssel- oder Wortlänge oder das Padding
  zu setzen. Dies muss dann als Beschreibung dieses speziellen
  Algorithmus in den internen Schlüsselspeicher aufgenommen
  werden (z.B. für den RC5-Algorithmus - siehe RFC 2040).
+ Wörterbuch für alle Angriffe benutzen, nicht nur für die
  Substitution.
+ Einbau von normierter Mustersuche
+ Analyse neu 
  - der homophonen Verschlüsselung
  - für asymmetrische Kryptoverfahren.
+ Analyse verbessern (nicht performant und stark genug bisher)
  - der monoalphabetischen Substitution
  - der Playfair-Verschlüsselung
+ Alle Anzeigemodule in einem konsistenten Klassenbaum
  zusammenfassen.
+ Die Sourcen so umstellen, daß die Ausgabe/Anzeige komplett von 
  den Kryptomodulen getrennt ist (erleichtert Portierungen und
  Fehlersuche)
+ In der Anzeige für Grafiken eine Vergrößerungsfunktion einbauen
  und / oder die Koordinaten anzeigen, an denen sich die Maus
  befindet.
+ Korrekturmöglichkeit einzelner Zeichen bei der Analyse von XOR,
  ADD, Vigenere.
+ Anzeigen des zweit-, dritt-, ... -besten Treffers bei der
  XOR/ADD Analyse (dies kann zu einer kürzeren Schlüssellänge
  führen).
+ Autokorrelation: vor der Überlagerung noch Operationen auf den
  Blöcken ausführen (XOR, ADD, ...); macht das Sinn?
+ Editieren der Homophonen-Schlüssel (wird insbesondere
  zur Analyse der Homophonen Verschlüsselung benötigt).
+ Bei gleitender Entropie: Automatische Anzeige der
  entsprechenden Stellen mit hoher Entropie.
+ Hillverfahren: Schlüsselmatrix transponieren.
+ Hillverfahren: Eingabe von Zahlen in die Schlüsselmatrix.
+ Update der Miracl-Lib auf eine neuere Version als 4.4.3.
+ Portierung nach Linux (eine SECUDE-Lib bzw. Miracl-Lib stehen
  zur Verfügung).
+ Portierung nach Java (eine SECUDE-Lib dafür steht zur
  Verfügung).
+ Diffie-Hellman Schlüsselaustausch visualisieren.
+ Kryptographisch starke elliptische Kurven erzeugen und damit
  Implementierung eines auf Elliptischen Kurven basierenden
  Kryptosystems. Dazu könnte man das Kryptosystem von Menezes
  und Vanstone nehmen, das 1993 von diesen Autoren vorgeschlagen
  wurde: A. Menezes and S. Vanstone,
         "Elliptic curve cryptosystems and their implementation",
         Journal of Cryptology, 6 (1993), Seiten 209-224.
+ Weil kryptographische Strukturen und Formate häufig ASN.1-
  kodiert sind: Integration eines ASN.1 Dekodier-Tools. 
+ Angriff auf Hash-Verfahren basierend auf dem "Geburtstags 
  Paradoxon".
+ Generell Visualisierung der Abhängigkeiten und Abläufe bei
  Protokollen (nicht nur bei "einfachen" Algorithmen).
+ Erweiterung um die deutschen Standards zur Validierung von 
  Zufallszahlen.
+ Weitere Standards implementieren und direkt über die Menüs
  bzw. aus der Online-Hilfe an alle Stellen verzweigen, wo diese
  Standardverfahren verwendet werden (Hauptarbeit UI und Doku).
+ CrypTool als Frontend für zahlentheoretische Funktionen und 
  Werte erweitern.


7.1 Sinnvolle Aufgaben für die Einarbeitung des neuen Maintainers
     ------------------------------------------------------------
+ Einbau des RC5-Algorithmus wie oben beschrieben, um zu sehen,
  an welchen Stellen überall die Sourcen dafür zu ergänzen sind.
+ alle möglichen Arten von Transpostionen für den Inhalt von
  Textfenstern in einem ansprechenden Dialog anbieten.
+ Testbett mit Beispielen und Lösungen erzeugen, damit man das
  Testen automatisieren kann und man sicherstellt, dass Programm-
  änderungen nicht alte Funktionalität negativ beeinflussen:
  a) Interface, um Testaufgaben manuell in Dialogboxen zu laden
  b) Schnittstelle schaffen, mit der sich die Testaufgaben aus
     einer Datei selbst in die Dialogboxen laden.
     Vielleicht sogar Script-Steuerung für alle Dialoge oder
     automatische Testtool vom Markt einsetzen.
  c) Commandline-Interface schaffen (am besten nachdem Krypto und
     Anzeige im Code getrennt wurden), das ohne Dialogboxen alle
     Aufgaben aus einer Datei per Schnittstelle ausliest und die
     Lösungen wieder in eine Datei schreibt:
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
Source für die Internet-Gemeinschaft freizugeben.



10. Feedback bei Fehlern
   ---------------------------
Sollten Sie Probleme haben oder Fehler finden, wenden Sie sich
bitte mit einer Beschreibung des Problems per e-mail an
- joerg-cornelius.schneider@db.com  oder
- bernhard.esslinger@db.com / besslinger@web.de

Für Anregungen jeglicher Art bezüglich CrypTool sind wir immer
dankbar.
Auch würden wir uns freuen, wenn Sie uns mitteilen, wie und wo Sie
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
CrypTool veröffentlicht.
Außerdem wurde in c't 25/1999 die Fantasy-Geschichte
"Der Dialog der Schwestern" veröffentlicht. Die darin verwendete
Variante von RSA kann mit CrypTool v1.3.00 nachvollzogen werden.

12.3. BSI Bürger-CD "Ins Internet - mit Sicherheit"
      ---------------------------------------------
Das Bundesamt für Sicherheit in der Informationstechnik (BSI) hat
zusammen mit dem Deutschen Bundesinnenministerium zur CeBIT 2002
eine CD veröffentlicht, die die Bürger aufklärt, wie man mit
Computer und Internet umgeht und wie man sich sicher im Internet
bewegen kann.
Auf dieser CD ist auch CrypTool enthalten, um das Verständnis der 
kryptographischen Sicherheitsfunktionen zu verbessern.
Von dieser CD sind mehr als 500.000 Stück produziert worden.

12.4. Freeware-Projekt Crank
      ----------------------
http://freshmeat.net/projects/crank/

Crank wurde im Januar 2001 von Matthew Russell begonnen und unter
der GNU General Public Licence (GPL) freigegeben.
Im Crank-Projekt soll unter Linux ein Programm mit graphischer
Oberfläche erstellt werden, das das möglichst automatisierte
Brechen von klassischen Kryptoalgorithmen ermöglicht.
Initial liegt der Fokus auf der Analyse monoalphabetischer
Substitutions-Chiffren und der Entwicklung generischer und
flexibler Analysetools.
Auf dieser Seite gibt es auch einige sehr interessante Links über
klassische Kryptoanalyse.




13. Anhang
    ------

13.1. CrypTool unter Linux mit Wine
13.1.1. ......... CrypTool installieren
13.1.2. ......... Wine-Konfiguration
13.1.3. ......... CrypTool ausführen



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
von riched32.dll. Wenn Sie unter CrypTool eine Datei öffnen und
die falsche Version von riched32.dll benutzt wird, erscheint ein
leeres Fenster.
Wahrscheinlich taucht das Problem nicht auf, wenn Wine eine
existierende Windows-Partition benutzen kann.
Wenn Sie Wine ohne Windows benutzen, können Sie das Problem mit 
folgenden Schritten lösen:
 - installieren sie CrypTool unter Wine.
 - besorgen Sie sich riched32.dll (z.B. Version 5.0.1458.47).
   und kopieren Sie die Datei in das Installationsverzeichnis
   von CrypTool. Evtl. müssen sie analog mit weiteren DLLs,
   verfahren, die von riched32.dll benutzt werden. Beachten Sie 
   bitte die Fehlerausgaben von Wine.
 - Konfigurieren Sie Wine so, dass es diese Datei nutzt. In der
   Standard-Konfiguration ist das so. Funktioniert das bei
   Ihnen nicht, schreiben Sie folgende Zeile in die
   [DllOverrides]-Sektion der Wine-Konfigurationsdatei:
   "riched32" = "native,builtin"


13.1.3 CrypTool ausführen
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
  Mit der folgenden Kommandozeile können Sie die Online-Hilfe
  anzeigen:

  $ wine winhlp32 CrypTool.hlp

