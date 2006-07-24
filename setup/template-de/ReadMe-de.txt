==================================================================
    CrypTool, Version 1.4.00 für Win32, Juli 2006
    (c) Deutsche Bank AG, Frankfurt am Main
    (c) Universität Siegen und Darmstadt
    (c) 1998-2006
    Bernhard Esslinger
    $Id$
==================================================================

                       Inhalt

 1. .... Kurzbeschreibung des CrypTool-Paketes
 1.1. .... Wie Sie am besten starten - Der Einstieg in CrypTool
 1.2. .... Was beinhaltet die Distribution
 1.3. .... Danke
 1.4. .... Maintainer, Hosting und Roadmap
 2. .... Beschränkungen und Voraussetzungen
 2.1. .... Lern-, Trainings- und Awareness-Software
 2.2. .... Win32-Umgebung
 2.3. .... Installation unter Windows 95
 2.4. .... Interaktive Online-Hilfe unter Windows XP
 2.5. .... Unterstützung verschiedener Sprachen
 2.6. .... Einschränkungen
 2.7. .... Zertifikate, die mit älteren CrypTool-Versionen erzeugt wurden
 3. .... Installation / Deinstallation / Betrieb
 3.1. .... Installation und Nutzung von Schlüsseln aus vorherigen Versionen
 3.2. .... Installation in Mehrbenutzersystemen
 3.3. .... Deinstallation of CrypTool
 3.4. .... Betrieb in Mehrbenutzersystemen
 4. .... Liste der Dateien in der Auslieferung
 4.1. .... Überprüfen der Integrität der heruntergeladenen Dateien
 5. .... Neuerungen in CrypTool 1.4.00
 5.1. .... Was bietet CrypTool generell
 5.2. .... Neuerungen in Version 1.4.00
 6. .... Mögliche Punkte für eine Weiterentwicklung -- Ideen, Anfragen
 6.1. .... Funktionalität: Algorithmen / Verfahren
 6.2. .... Funktionalität: Analyse
 6.3. .... Interne Schnittstellen / Editoren
 6.4. .... User-Interface / Visualisierungen
 6.5. .... Erweiterung um zahlentheoretische Funktionen
 6.6. .... Portierung nach Linux, Java und VS2005/WPF
 6.7. .... Sinnvolle Aufgaben für jemand, der neu anfängt mitzuentwickeln
 7. .... Kurze Historie der freigegebenen Hauptversionen
 8. .... Feedback bei Fehlern
 9. .... Kontaktadressen
10. .... Verweise
10.1. .... Artikel zu CrypTool
10.2. .... Sonstige Referenzen auf CrypTool
10.3. .... Weitere Freeware-Projekte (Crank, CAP, CryptoStudio, etc.)
10.4. .... Auszeichnungen
11. .... Anhang
11.1. .... CrypTool unter Linux mit Wine



1. Kurzbeschreibung des CrypTool-Paketes
   -------------------------------------
Diese Readme-Datei gehört zur kostenlosen Distribution des Open-Source
Programms CrypTool. Mit CrypTool kann man kryptographische Verfahren
erlernen, ausprobieren und sowohl bekannte wie unbekannte Verfahren
analysieren.

Zu jedem Programmteil gibt es reichhaltige Online-Hilfe, die auch
ohne tiefes Kryptowissen verstanden werden kann.

CrypTool ist komplett in Deutsch und Englisch vorhanden.

Vorausgesetzt wird, dass der Benutzer mit Anwendungen in einer
Windows-Umgebung umgehen kann.

Die jeweils aktuelle Version von CrypTool finden Sie unter den
Internet-Adressen:  http://www.CrypTool.de
                    http://www.CrypTool.com
                    http://www.CrypTool.org

Seit Anfang 2006 bewegt sich die Downloadrate bei rund 2000
CrypTool-Paketen pro Monat -- mit wachsender Tendenz (davon
entfallen etwas über 1/3 auf die englische Version).

Ziel von CrypTool ist es, kryptographische Mechanismen anschaulich
zu machen und die Verwendung und die Grenzen einzelner Verfahren
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
CrypTool. Diese werden z.B. auf der Webseite, bei der Installation und
auf der Einstiegsseite der Online-Hilfe erläutert.

Für bisherige Benutzer von CrypTool dürften in diesem Readme sind vor
allem die Kapitel 5 (Neuerungen) und 6 (Weiterentwicklung) interessant
sein.

Wir laden jeden herzlich ein, an CrypTool mit zu entwickeln oder
Feedback zu geben. Auch für Hinweise zu Arbeiten (Diplom-, Doktor-
oder Seminararbeiten), die man in CrypTool integrieren könnte, sind
wir sehr dankbar. 
Kontakte: Siehe Kapitel 8 und 9 unten.


1.1. Wie Sie am besten starten - Der Einstieg in CrypTool
     ----------------------------------------------------
Beim Start von CrypTool öffnen sich zugleich die Arbeitsfläche
von CrypTool und im Vordergrund ein kleines Begrüßungsfenster.
Wenn Sie im Begrüßungsfenster gleich die F1-Taste drücken, erscheint
zusätzlich die Startseite der Online-Hilfe.

Diese Startseite ist ein guter Ausgangspunkt, um alle wesentlichen
Inhalte von CrypTool kennen zu lernen (z.B. mit Hilfe der Links auf
dieser Startseite).
Bitte lesen Sie die Hinweise und Tipps der Hilfe-Startseite.

Einen schnellen Einstieg in CrypTool finden Sie, wenn Sie einige
Szenarien (Tutorials) der Online-Hilfe durchspielen (die Szenarien
stehen im Inhaltsverzeichnis der Online-Hilfe unter "Beginn der 
Arbeit mit CrypTool").

Die Funktionen von CrypTool können Sie am einfachsten ausprobieren
mit der standardmäßig geöffneten Datei "Startbeispiel-de.txt".
Sie können aber auch eine andere unverschlüsselte Datei aus dem 
Unterverzeichnis "examples" oder irgendeine andere Datei auf der 
CrypTool-Arbeitsfläche öffnen.

Wenn Ihnen ein Menüpunkt nichts sagt oder Sie in einem Dialogfenster
nicht recht weiter wissen, sollten Sie mittels der F1-Taste ausreichend
Hilfe finden (wenn nicht, geben Sie uns bitte Feedback).

Wir wünschen viel Spaß beim Lernen und beim Ausprobieren der Funktionen
von CrypTool.


1.2. Was beinhaltet die Distribution
     -------------------------------
Das CrypTool-Paket enthält die folgenden vier Hauptbestandteile:

(1) Das Programm CrypTool
-------------------------
Hauptteil des CrypTool-Paketes ist das Programm CrypTool selbst.
CrypTool ist eine Demonstration, die vor allem für Ausbildungszwecke
eingesetzt wird:

- In CrypTool ist eine umfangreiche Sammlung kryptographischer
  Algorithmen und Protokolle implementiert, die hervorragend 
  dokumentiert und teilweise visualisiert sind.
  Somit ist CrypTool sehr gut geeignet zur Ausbildung und zur
  Mitarbeiter-Sensibilisierung für IT-Sicherheit.

- Die meisten der kryptographischen Basisalgorithmen stammen aus:
  - der Industrie-bewährten Secude-Bibliothek (Version SDK 7.4.60C)
    (www.secude.com),
  - der Miracl-Bibliothek (Version 4.4.3) (http://indigo.ie/~mscott/),
  - der OpenSSL-Bibliothek (Version 0.9.8),
  - der NTL-Zahlentheorie-Bibliothek von Victor Shoup (Version 5.4) und
  - der GMP-Bibliothek für beliebig genaue Arithmetik (Version 4.2.1)
    (http://www.swox.com/gmp/).
 
  Somit ist CrypTool auch eine hervorragende Referenzimplemen-
  tierung.

- Die Kryptoanalyse der meisten der klassischen Verfahren ist
  automatisiert.
  Die Analyse der modernen Verfahren ist eingeschränkt, so dass
  CrypTool kein Hackertool ist.

Entwicklungsziel von CrypTool war nicht, dass damit im Wirkbetrieb
eine CA (Certification Authority) betrieben wird oder dass damit 
für produktive Zwecke Daten verschlüsselt oder anderweitig gesichert
werden sollten. 


(2) Dokumentation
-----------------
Zum Programm gehört eine umfangreiche Dokumentation, die ebenfalls
aus vier Teilen besteht:
a) Readme-Datei (diese Datei),
b) Online-Hilfe
    - Kontext-bezogen zur Bedienung des Programms und mit
      weiterreichenden Erläuterungen,
    - Demos bzw. Beispiel-Szenarien (hier werden Einzelverfahren
      Schritt für Schritt erläutert)
c) Skript zum Thema Kryptographie (beigelegt als PDF-Datei),
d) Präsentation, die auf Folien die Möglichkeiten von CrypTool
   aufzeigt (beigelegt als PDF-Datei).


(3) Eigenständige Programme
---------------------------
Alle diese Programme können aus CrypTool heraus, aber auch stand-alone
aufgerufen werden.
a) Das Programm AES-Tool (entstanden im CrypTool-Projekt)
   Zum Erstellen selbstentpackender Executables ist in CrypTool ein
   Programm integriert, das auch eigenständig benutzt werden kann.
   Darin wird aus einem Passwort ein Session-Key erzeugt, mit dem
   ein beliebiger Dateiinhalt AES-verschlüsselt wird.
   Dieses Verschlüsselungstool kann sowohl als Fenster als auch von
   Kommandozeile (z.B. aus einer Batchdatei) aufgerufen werden.
b) Das Lernspiel "Der Zahlenhai" (entstanden im CrypTool-Projekt)
   Dieses Lernspiel für Schüler bringt diesen den Umgang mit
   Teilern und Primfaktoren näher.
c) Das Animationsprogramm ANIMAL (siehe http://www.animal.ahrgr.de)
   Mit diesem an der TU Darmstadt von Dr. Rößling gepflegten Programm
   kann man die Einzelschritte von Algorithmen oder die Komponenten von
   Datenstrukturen beliebig genau modellieren, diese manuell vor und 
   zurück abspielen oder automatisch ablaufen lassen. Das Animal-System
   erlaubt die Erstellung von Animationen mithilfe einer GUI, einer 
   Skriptsprache sowie einer Java-API.


(4) Geschichten mit Bezug zur Zahlentheorie und Kryptographie
-------------------------------------------------------------
Als PDF-Datei sind zwei Geschichten beigelegt:
- In "Der Dialog der Schwestern" wird eine Variante des RSA-Verfahrens
  von den Titelheldinnen benutzt, um verschlüsselt zu kommunizieren.
- In "Das Chinesische Labyrinth" muss Marco Polo zahlentheoretische
  Aufgaben lösen, um Berater des Großen Khan zu werden.

Alle Einzeldateien, die bei der Installation des CrypTool-Paketes
auf Ihre Platte kopiert werden, sind in Kapitel 4 (unten in diesem
Readme) aufgeführt.



1.3. Danke
     -----
Zu CrypTool haben viele verschiedene Personen beigetragen --
insbesondere auch in ihrer Freizeit (einige sind namentlich in der
Dialogbox aufgeführt, die man erhält, wenn man in der Dialogbox 
"Über CrypTool" einen Doppelklick ausführt). Herzlichen Dank.

Ebenfalls beigetragen haben als Sponsoren die Deutsche Bank AG und
die Technische Universität Darmstadt.

Dr. Carsten Elsner erlaubte uns, seine beiden Geschichten als 
PDF-Datei beizulegen.
Der Verfasser, als alleiniger Inhaber aller Rechte an den Werken,
räumt dem CrypTool-Maintainer das ausschließliche Vervielfälti-
gungs- und Verbreitungsrecht ein. Die Geschichten dürfen nur zusammen
mit dem CrypTool-Paket verbreitet werden.
Die Geschichte "Der Dialog der Schwestern" wurde zuerst in dem 
Computermagazin c't 25/1999 veröffentlicht. Während in der c't
eine etwas gekürzte Fassung veröffentlicht wurde, liegt hier die
Originalfassung bei.

Die Firmen Secude GmbH und Shamus Software Ltd. (siehe oben) 
gestatteten uns großzügigerweise, ihre Krypto-Bibliotheken zu nutzen.
Diese mit CrypTool verteilten Bibliotheken dürfen nicht in einem
Kontext außerhalb CrypTool benutzt werden, ohne vorher die erwähnten
Firmen zu kontaktieren und nach ihren aktuellen Lizenzbedingungen zu
fragen.

Ebenso danken möchten wir den Open-Source-Entwicklern, deren Code wir
nutzen dürfen (z.B. die Bibliotheken OpenSSL und NTL) oder die uns
mit ihrem Code Anregungen gaben.


1.4. Maintainer, Hosting und Roadmap
     -------------------------------
Wie geplant hat CrypTool ein akademisches Zuhause erhalten:
Seit Oktober 2002 hostet der Lehrstuhl Sicherheit in der Informations-
technik, Fachbereich Informatik unter Frau Prof. Dr. Claudia Eckert
an der TU Darmstadt die deutsche und englische Webseite von CrypTool
und das CVS-System für die Programm-Sourcen.

Die CrypTool-Entwicklergruppe unter Bernhard Esslinger fungiert auch
weiterhin als Maintainer, d.h. sie kümmert sich um die Pflege des
Codes, die Veröffentlichung als Open Source und Freeware, und um
die Koordination der Weiterentwicklung. Die nächsten Schritte der
Roadmap werden auf der Webseite veröffentlicht.

Die Homepage von CrypTool bleibt weiterhin www.cryptool.de.

Wir würden uns sehr freuen, wenn sich nicht nur die bisherigen
Entwickler, sondern auch viele neue an der Weiterentwicklung von
CrypTool beteiligen. Ideen dazu finden Sie in Kapitel 6.

Ebenfalls sehr willkommen sind uns Ideen und Infos, wie CrypTool in
Lehre, Schule und Ausbildung eingesetzt wurde, damit wir dazu 
beitragen können, diese Informationen auszutauschen.



2. Beschränkungen und Voraussetzungen
   ----------------------------------

2.1. Lern-, Trainings- und Awareness-Software
     ----------------------------------------
CrypTool dient vor allem Ausbildungs- und Awareness-Zwecken. Man soll
es ohne vorherige Konfiguration sofort benutzen können.

Das Entwicklungsziel von CrypTool war also nicht, dass damit produktiv
verschlüsselt wird oder dass damit eine CA (Certification Authority)
betrieben wird -- auch wenn die Funktionen korrekt in CrypTool 
implementiert sind.

Beispielsweise steht - im Unterschied zu produktiven CA-Applikationen -
das CA-Schlüsselpaar fest in der Software (Source und Binary) und es
ist geschützt mit einer ebenfalls bewusst sehr einfachen PIN für 
die CA-PSE (Personal Security Environment).

Der Rootschlüssel der in CrypTool 1.4.00 eingebauten CA hat eine Länge
von 2048 Bit und ist 20 Jahre gültig (06.07.2006 - 06.07.2026).
Mit dem alten Rootkey in früheren CrypTool-Versionen (1.3.05 und älter)
ausgestellte Zertifikate können nicht in Version 1.4.00 importiert werden.

Beachten Sie also beim Umgang mit Zertifikaten, dass jedes CrypTool-
Programm eine Root-CA mit demselben Schlüsselpaar beinhaltet, mit 
der die im Programm erzeugten User-Zertifikate signiert werden. 
D.h. jeder (!), der CrypTool einsetzt, kann User-Zertifikate mit 
dieser eingebauten CA signieren.

Professionelle PKI-Software wie die z.B. die OpenXPKI, Entrust, die
Secude-CA oder die Microsoft-CA managen zusätzlich den ganzen
Lebenszyklus von Zertifikaten und bieten CRL-Handling, sorgen für
eindeutige Seriennummern und nutzen definierte Registrierungsprozesse.

Die in CrypTool vorhandenen Verfahren selbst sind entsprechend den
internationalen Standards implementiert und genauso "gut" wie in
kommerziellen Anwendungen.


2.2. Win32-Umgebung
     --------------
CrypTool erfordert eine Win32-Umgebung, wie sie unter Windows 95,
Windows 98, Windows Me, Windows NT (ab 4.0), Windows 2000 und
Windows XP gegeben ist.

Seit Version 1.4.00 sind weder für die Installation noch für die
Benutzung Administrator-Rechte notwendig. Persistente Daten werden
nur im CrypTool-Verzeichnis, in das Standard-Windows-Verzeichnis für
temporäre Dateien (TEMP-Verzeichnis) und in den benutzerspezifischen
Bereich der Windows-Registry geschrieben (Details siehe Kapitel 3).

Anmerkung: Wo das TEMP-Verzeichnis von Windows liegt, kann man sehen,
wenn man in Windows-Explorer %TEMP% eingibt. Den Wert kann man unter
Windows XP auch ansehen und anpassen per "System --> Systemeigenschaften
--> Reiter Erweitert --> Umgebungsvariablen".

CrypTool funktioniert grundsätzlich auch unter FreeBSD/Linux mit
Wine (mit großen Abstrichen an Funktionalität und Stabilität).
Siehe Anhang 11.1.

Eine Portierung auf Linux oder ein Neudesign mit Java oder eine
Vorbereitung auf Windows Vista/Avalon sind weitere Ziele (siehe
Kapitel 6).


2.3. Installation unter Windows 95
     -----------------------------
Bei älteren Windows 95-Systemen erhalten Sie beim Aufruf von
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


2.4. Interaktive Online-Hilfe unter Windows XP
     -----------------------------------------
Unter Windows XP ist der Aufruf der interaktiven Online-Hilfe über
die F1-Taste in einem Spezialfall nicht möglich: Betroffen sind
nur Menüs, die noch Untermenüs haben. Das Problem tritt nur auf,
wenn das Untermenü aufgeklappt ist. F1 bewirkt dann gar nichts.

Normalerweise kann bei CrypTool auch Hilfe zu einem Menüeintrag
angefordert werden, der selbst weitere Untermenüs hat -- unabhängig
davon, ob das Untermenü aufgeklappt ist oder nicht.
Unter Windows XP erhält man die Online-Hilfe dazu nur, wenn das
Popup-Fenster der untergeordneten Menüpunkte nicht aufgeklappt
ist.
Bei den anderen Windows-Versionen spielt das keine Rolle, dort ist
nur wichtig, dass das Menü den Fokus hat.

Workaround anhand eines Beispiels: 
Markieren Sie den Menüeintrag "Einzelverfahren \ RSA-Kryptosystem":
Wenn das Untermenü zu "RSA-Kryptosystem" aufgeklappt ist und Sie die
Hilfe zum Menüeintrag "RSA-Kryptosystem" selbst haben wollen, 
müssen Sie - nur unter Windows XP - erst das Untermenü von 
"RSA-Kryptosystem" mit Escape (Esc) oder der Links-Pfeiltaste wieder
einklappen: Dann funktioniert das Aufrufen der Online-Hilfe mit F1 
auch unter Windows XP.


2.5. Unterstützung verschiedener Sprachen
     ------------------------------------
Programm, Hilfesystem und Dokumentation sind mehrsprachig aus-
gelegt (zur Zeit englisch und deutsch).

Für jede unterstützte Sprache gibt es ein eigenes Setup (der
Versuch, alle Sprachen in ein einziges Executable einzubinden
wurde wieder aufgegeben, da die automatische Spracheinstellung
beim Anwender (anhand seiner Systemeinstellungen) nur unter
Windows NT 4.0, nicht aber unter Win9x, korrekt funktionierte).


2.6. Einschränkungen
     ---------------
- Zur Demonstration des RSA-Kryptosystem und zur Faktorisierung von
  Zahlen greift CrypTool auf die Langzahlarithmetik der Bibliothek
  Miracl von Shamus Software Ltd. zu. Die Bitlänge der Zahlen wurde
  in der CrypTool-Anwendung auf 8192 beschränkt. 

- Von Binärdateien werden "nur" knapp die ersten 2 GB in den
  Hex-Editor geladen (< 0x7ffff000 = 2.147.479.552 Bytes).
 
- Textdateien können in unbeschränkter Größe vom Editor geladen werden
  (sofern die Rechnerressourcen reichen).

- Aus Performancegründen wurde festgelegt, dass CrypTool bei der
  N-Gramm-Analyse die Dokumente beschränkt:
   - für Binärdateien auf 64 kBytes und
   - für Textdateien auf 256 kBytes beschränkt.
  Werden längere Dateien geöffnet, werden sie -- nur bei dieser Art
  der Anayse -- auf den maximalen Eingabewert gekürzt.

- Hashwerte können von Dateien beliebiger Größe berechnet werden,
  sofern die Dateien nicht geladen werden. 

- Mit dem AES-Tool können nur Dateien bis 4 GB Größe verschlüsselt
  und archiviert werden (solange mit VS2003 compiliert).

  Bitte beachten Sie, dass die Ausgabe des Standalone AES-Tools nicht
  vollkommen identisch ist mit der Ausgabe, die Sie in CrypTool mit der 
  Menüfolge "Ver/Entschlüsseln \ Symmetrisch (modern) \ Rijndael (AES)"
  erhalten (auch nicht, wenn das AES-Tool eine Datei mit der Endung "aes"
  erzeugt). CrypTool selbst verwendet z.Zt. einen festen IV (0), der nicht 
  gespeichert wird. AES-Tool nutzt einen zufälligen IV und fügt diesen 
  zusammen mit dem Dateinamen hinter den verschlüsselten Daten an.


2.7. Zertifikate, die mit älteren CrypTool-Versionen erzeugt wurden
     --------------------------------------------------------------
Falls Sie Zertifikate, die mit älteren Versionen von CrypTool erzeugt
wurden, unter CrypTool 1.4.00 weiter verwenden wollen, gehen Sie bitte
folgendermaßen vor:
  a) für RSA- und DSA-Schlüssel:
     Exportieren Sie diese PSEs mit Hilfe des alten CrypTools in ein
     PKCS#12-Format und laden Sie diese Dateien im neuen CrypTool.
  b) für ECC-Schlüssel:
     Hier reicht es, die entsprechenden Dateien 
     (z.B. [da][db][EC-prime239v1][1131039030][d] )
     vom alten CrypTool\pse-Verzeichnis in das neue zu kopieren.



3. Installation / Deinstallation / Betrieb
   ---------------------------------------

3.1. Installation und Nutzung von Schlüsseln aus vorherigen Versionen
     ---------------------------------------------------------------
Sie installieren CrypTool, indem Sie das CrypTool-Setup-Programm an
einer geeigneten Stelle im Dateibaum auf Ihrem PC aufrufen.
Standardmäßig wird CrypTool dann in das Verzeichnis 
            "C:\Programme\CrypTool"
installiert. Das Zielverzeichnis kann in der Installationsroutine
geändert werden.

Besitzen Sie bereits eine frühere Version von CrypTool, so
empfiehlt es sich, vor der erneuten Installation das alte CrypTool
zu deinstallieren, da unter Umständen nicht alle alten
Dateien überschrieben werden. Bitte beachten Sie:
- Wenn bei der Deinstallation nicht alle Verzeichnisse/Dateien im
  Programmverzeichnis (meist "C:\Programme\CrypTool") gelöscht
  werden, löschen Sie diese manuell.
- Bei der Deinstallation von CrypTool werden alle bisher erzeugten
  asymmetrischen Schlüssel gelöscht. Wenn Sie diese Schlüssel auch
  in der neuen Version von CrypTool nutzen wollen, dann sichern
  Sie vor der Deinstallation das unter dem Programmverzeichnis
  liegende Verzeichnis pse\ mit allen darin gespeicherten Dateien
  in ein anderes Verzeichnis. Vergleiche auch Kapitel 2.7.
  Nachdem die neue Version von CrypTool installiert wurde,
  kopieren Sie das gesicherte pse\-Verzeichnis in das neue
  Programmverzeichnis.
  Alternativ können Sie RSA- und DSA-PSEs als PKCS#12-Struktur 
  exportieren bzw. importieren.

Für den Fall, dass mehrere Benutzer dieselbe CrypTool-
Installation verwenden wollen, müssen die Zugriffsrechte auf den
Verzeichnissen pse\ und pse\pseca\ und den darin enthaltenen
Dateien für alle Benutzer auf Vollzugriff gesetzt werden.

Der Teilbaum "pse\" sollte nicht manuell bearbeitet werden, da
bei einer inkonsistenten Struktur nur eine Neuinstallation von
CrypTool bleibt, um die zertifikatsbasierten Verfahren zu nutzen.


3.2. Installation in Mehrbenutzersystemen
     ------------------------------------
In Mehrbenutzersystemen wie Windows XP hat der Administrator vollen
Zugriff auf das ganze Dateisystem, die restlichen Benutzer können/sollten
eingeschränkt sein.

Zur Installation braucht der Benutzer Schreibrechte für das 
Verzeichnis, in das CrypTool installiert werden soll:
- z.B. für das Verzeichnis %ProgramFiles% (C:\Programme), 
  falls das Unterverzeichnis "CrypTool" noch nicht angelegt ist,  oder
- für das Verzeichnis %ProgramFiles%\CrypTool (C:\Programme\CrypTool),
  falls dieses schon angelegt ist).
Hat er diese Rechte nicht, bricht die Installation ab.

Deshalb sollten Sie als normaler Benutzer ohne Administratorrechte als 
Zielverzeichnis ein sogenanntes "lokales Verzeichnis" angeben (statt
"C:\Programme"). Lokal und für den Benutzer zugänglich könnten z.B. sein:
%ALLUSERSPROFILE% (Die standardeinstellung in deutschem Windows XP ist: 
"C:\Dokumente und Einstellungen\All Users").

Wenn Sie CrypTool ohne Administratorrechte installieren und keine
Schreibrechte auf %ALLUSERSPROFILE%\Start Menu haben, werden unter WXP
im Startmenü ("Start \ Alle Programme") die Einträge zu CrypTool fehlen.
Jeder Nutzer kann diese Einträge aber manuell in sein eigenes Startmenü
aufnehmen.

Anmerkung: Wie bei %TEMP% auch, können Sie sehen, wo diese Verzeichnisse
liegen, indem Sie im Windows-Explorer %ALLUSERSPROFILE% oder %userprofile%
eingeben.



3.3. Deinstallation von CrypTool
     ---------------------------
Um CrypTool zu deinstallieren, benutzen Sie bitte das "Start"-Menu in
der Windows Taskleiste.
Dort gehen Sie zu "Alle Programme" \ "CrypTool".
Dann klicken Sie auf "CrypTool deinstallieren".


3.4. Betrieb in Mehrbenutzersystemen
     -------------------------------
Ab Version 1.4.00 werden alle Benutzer-spezifischen Einstellungen in
der lokalen Registry gespeichert (z.B. die zuletzt geöffneten Dateien):
Dadurch braucht man keine ini-Datei mehr im Windows-Verzeichnis und 
unterstützt den Betrieb in Mehrbenutzersystemen.
 
Will der Benutzer in Mehrbenutzersystemen wie Windows XP aus CrypTool
heraus Dateien anlegen (bzw. ändern), braucht er Schreibrechte auf das
entsprechende Zielverzeichnis (bzw. auf die entsprechende Datei). 
Geht das nicht, kommt eine Warnung.
Explizit nötig sind Schreibrechte nur auf 2 Verzeichnissen:
- das Standard-Windows-Verzeichnis für temporäre Dateien (TEMP)
  für die cry*.*-Dateien,
- das Unterverzeichnis "CrypTool\pse", da darin die erzeugten 
  asymmetrischen Zertifikate und Schlüssel abgelegt werden (siehe
  Kapitel 3 oben).


4. Liste der Dateien in der Auslieferung
   -------------------------------------
CrypTool wird als komprimiertes, selbstextrahierendes Archiv in
zwei verschiedenen Sprachversionen verteilt:

SetupCrypTool_1_4_00_en.exe    Englische Sprachversion.
SetupCrypTool_1_4_00_de.exe    Deutsche Sprachversion.

Diese Archive enthalten die folgenden Dateien:

ReadMe-de.txt .... Diese Kurzanweisung (deutsch).
ReadMe-en.txt .... Diese Kurzanweisung (englisch).
md5sum.txt ....... MD5-Hashwerte aller Dateien innerhalb des CrypTool-
                   Paketes (selbstextrahierendes Archiv).
sha1sum.txt ...... SHA-1-Hashwerte aller dieser Dateien.

CrypTool.exe ..... Das ausführbare Programm.
aestool.exe ...... Ein Programm, das Dateien in sich selbst entpackende
                   Programme verschlüsselt. Zur Entschlüsselung müssen
                   Sie das korrekte Passwort eingeben.
CrypTool-de.chm .. HTML-Hilfe-Archiv für die CrypTool-Onlinehilfe in
                   deutsch.
CrypTool-en.chm .. HTML-Hilfe-Archiv für die Onlinehilfe (englisch).

EC-Param.ini ..... Initialisierungsdatei für auf Elliptischen
                   Kurven basierende Public Key-Verfahren.
secude.dll ....... Bibliothek kryptographischer Funktionen von der
                   Secude GmbH.
ticket ........... Lizenz für die Secude-Bibliothek.
libxml2.dll ...... Wird benötigt von der secude.dll.
secidea.dll ...... Wird benötigt von der secude.dll für die 
                   IDEA-Verschlüsselung.
srndmskb.dll ..... Wird benötigt von der secude.dll für den 
                   Entropiesammler zur Initialisierung des 
                   Secude-Zufallsgenerators.
db.dll ........... Wird benötigt von der secude.dll.
libeay32.dll...... Bibliothek aus OpenSSL.
SciLexer.dll ..... Bibliothek mit den Routinen für den 
                   Scintilla-Texteditor.
TEST-Param.ini ... Initialisierungsdatei für die Zufallstests.
irunin.* ......... Diese Dateien sind nötig für Installation und
                   Deinstallation von CrypTool.

script-de.pdf .... Ein Skript (deutsch) über Kryptographie, Primzahlen,
                   elementare Zahlentheorie und die Mathematik hinter
                   einigen Algorithmen.
script-en.pdf .... Die englische Fassung von script-de.pdf.
CrypToolPresentation_1_4_00_de.pdf .. Folien-Präsentation (deutsch)
CrypToolPresentation_1_4_00_en.pdf .. Folien-Präsentation (englisch)
DialogSchwestern.pdf .. Fantasy-Geschichte von Dr. Elsner, in der
                        eine Variante des RSA-Kryptosystems
                        beschrieben wird.
DialogueSisters.pdf ... Englische Fassung von DialogSchwestern.pdf.
ChinLab-de.pdf.pdf .. Geschichte von Dr. Elsner über zahlentheoretische
                      Probleme, die Marco Polo vom Großen Khan gestellt
                      werden.
ChinLab-en.pdf.pdf .. Englische Fassung von ChinLab-de.pdf.


examples\ ........ Dieses Verzeichnis enthält unterschiedliche
                   Beispieldateien, die in den Szenarien verwendet
                   werden. Dateien mit der Endung ".txt" sind
                   Textdateien. Alle anderen Dateien sind binär.
                   Dateien mit dem Format "XX-enc-YY.*" sind
                   verschlüsselte Dateien. Bitte verändern Sie
                   diese Dateien nicht.

examples\CrypTool.bmp
        \CrypTool-de.txt
        \CrypTool-en.txt
        \Playfair-enc-de.txt
        \Probetext-de.txt
        \psion-enc.hex
        \vernam.txt
        \Startbeispiel-de.txt
        \Startingexample-en.txt
        \Original.txt ..... "Harmlose" Beispieldatei für die 
                            Hashkollision-Demo
        \original.txt ..... Englische Fassung von Original.txt
        \Faelschung.txt ... "Gefährliche" Beispieldatei für die
                            Hashkollision-Demo
        \fake.txt ......... Englische Fassung von Faelschung.txt
        \letterFromAliceToBob-DECRYPTED-de.txt .. Beispieldateien
        \letterFromAliceToBob-DECRYPTED-en.txt .. für die Demo
        \letterFromAliceToBob-ENCRYPTED-de.hex .. des Seitenkanal-
        \letterFromAliceToBob-ENCRYPTED-en.hex .. angriffs


reference\ ....... Dieses Verzeichnis enthält Textdateien in den
                   Sprachen Deutsch, Englisch, Französisch,
                   Spanisch und Latein. Diese Dateien werden
                   standardmäßig als Referenz für die Analyse von
                   Chiffretexten herangezogen.
                   Diese Dateien sind schreibgeschützt.

reference\deutsch.txt  // Auszug aus dem dt. Umsatzsteuergesetz
         \english.txt  // Auszug aus der Agenda 21[UN-Dokument]
         \genesis-de.txt  // Buch Genesis in den Sprachen
         \genesis-en.txt  // deutsch, englisch, französisch,
         \genesis-es.txt  // spanisch und lateinisch.
         \genesis-fr.txt  // Die 2-Buchstabencodes entsprechen
         \genesis-la.txt  // den ISO 639 Language Codes.


animal\ .......... Dieses Verzeichnis enthält die Dateien, die für
                   das Animationsprogramm ANIMAL nötig sind.

animal\Animal-2.0.3.jar
      \animal.bat
      \animal.properties
      \AnimalResources
      \AnimalResources.de
      \AnimalResources.de_DE
      \AnimalResources.en
      \AnimalResources.en_US
      \AnimalResources.es
      \AnimalResources.es_SP
      \animList.txt
      \anmTypes.dat
      \default.properties
      \Editors.dat
      \elementDefinitions
      \exporters.dat
      \figTypes.dat
      \handlers.dat
      \imgTypes.dat
      \importers.dat
      \languages.dat
      \languages.default
      \parser.config
      \txtTypes.dat
      \types.dat

animal\anims ..... Dieses Verzeichnis enthält AML-Dateien. 
                   In jeder AML-Datei ist die Beschreibung zu einer
                   Animation für ein Verschlüsselungsverfahren
                   abgelegt.

animal\anims\caesar_de.aml
            \caesar_en.aml
            \des_de.aml
            \des_en.aml
            \nihilist_de.aml
            \nihilist_en.aml
            \vigenere_de.aml
            \vigenere_en.aml


pse\ ............. In diesem Verzeichnis und in seinem
                   Unterverzeichnis pseca\ werden erzeugte
                   (asymmetrische) Schlüssel und Zertifikate abgelegt.

pse\[Bob][SideChannelAttack][RSA-512][1126252192][PIN=1234].pse

pse\pseca\calog    Diese Dateien sind für die Verwaltung der
         \CA_exts  Schlüsseldatenbank notwendig.
         \cert.dir
         \cert.pag
         \crls.dir
         \crls.pag
         \pseca
         \user.dir
         \user.pag


Während der Laufzeit von CrypTool werden die folgenden Dateien
erzeugt und verwaltet:
cry*.* ........... CrypTool schreibt temporäre Dateien mit dem
                   Namensmuster cry*.* in das TEMP-Verzeichnis.
                   Es gibt folgende Endungen: 
                   hex -> hexadezimale (binäre) Inhalte
                   org -> xxxxxxxxxx
                   plt -> Diagrammausgabe (Histogramm, Autokorrelation)
                   tmp -> xxxxxxxxxx
                   txt -> Textdateien
                   ogl -> OpenGL-Beschreibungen.


4.1. Überprüfen der Integrität der heruntergeladenen Dateien
     -------------------------------------------------------
Die Integrität von Dateien kann mit Hashwerten überprüft
werden. Hashwerte sind wie Fingerabdrücke -- mit einer sehr geringen
Informationsmenge kann man ein viel größeres Objekt identifizieren.

Dateien vom CrypTool-Projekt können auf folgende beiden Arten auf Ihren
Computer gelangen: entweder durch direktes Herunterladen oder durch 
Entpacken einer heruntergeladenen Datei:
a) Herunterladbare Dateien:
   Auf der Homepage von CrypTool www.cryptool.de finden Sie
   die Hashwerte aller von der deutschen Webseite direkt
   herunterladbaren Dateien in den Dateien md5sum.txt bzw.
   in sha1sum.txt.
   Wenn man den Hashwert einer heruntergeladenen Datei neu berechnet
   und mit den Werten auf der CrypTool-Homepage vergleicht, kann man
   sehen, ob man eine unveränderte Kopie der Originaldatei hat oder
   nicht.
   Weichen die Hashwerte voneinander ab, sollte man die Datei
   nochmal herunterladen und evtl. die Ursache dafür suchen, dass
   man eine veränderte Datei auf seinem Rechner hat.
b) Zusätzlich können Sie auch die Dateien INNERHALB des 
   heruntergeladenen Setup-Paketes überprüfen:
   Deren Hashwerte stehen ebenfalls in den Dateien md5sum.txt bzw.
   in sha1sum.txt.

Zur Überprüfung der Integrität der heruntergeladenen oder entpackten
Dateien können Sie weit verbreitete Tools wie MD5SUM und SHA1SUM
verwenden.

Alternativ können Sie auch das Programm CrypTool selbst verwenden:
  Die Hashwerte von "externen" Dateien können Sie mit CrypTool
  berechnen, auch ohne die Dateien vorher in CrypTool zu laden:
  - Menü "Einzelverfahren \ Hashverfahren \ Hashwert einer Datei"
    anklicken,
  - Öffnen der entsprechenden Datei,
  - Auswahl von MD5 oder SHA1 als Hashalgorithmus,
  - Vergleich mit dem Wert in den Dateien md5sum.txt oder SHA1sum.txt.

Aus Sicherheitsgründen empfiehlt sich der Vergleich bei
Binärdateien (EXE, DLL, PDF, ...), wenn Sie nicht ganz sicher
sind, dass Ihr Rechner unberührt ist.



5. Neuerungen in CrypTool 1.4.00
   -----------------------------

Kapitel 5 listet die Erweiterungen und Bugfixes auf, die in
CrypTool 1.4.00 seit CrypTool 1.3.05 hinzugefügt wurden.

5.1. Was bietet CrypTool generell
     ----------------------------
Hier vorab noch mal die generellen Eigenschaften von CrypTool:
- eLearning-Programm rund um das Thema Kryptographie.
- Kryptographie und Kryptoanalyse unter einer Oberfläche.
- Alles in Deutsch und Englisch.
- Klassische Verschlüsselungsverfahren, und dafür teilweise manuell
  unterstützte, teilweise automatische Analyse.
- Moderne symmetrische Verschlüsselungsverfahren, und die
  Brute-Force-Analyse dazu
  (Bei der Brute-Force-Attacke auf symmetrische Algorithmen werden
   Jokerzeichen zugelassen und die erwartete Zeit wird ausgegeben. 
   Außerdem kann man die Breite für das hierbei genutzte
   Entropiefenster in den Analyseoptionen einstellen).
- Moderne Kryptoverfahren und Protokolle (Hash, RSA, ECC, Digitale
  Signatur, Hybrid-Verschlüsselung, PKCS#5, Shared Secret, ...) und
  teilweise Angriffe darauf (Geburtstagsangriff, Seitenkanalangriff, 
  Gitterbasenreduktion).
- Hashwerte berechnen und ihre Sensitivität demonstrieren.
- Pseudozufallszahlengeneratoren und statistische Analysen für 
  Zufallsdaten (z.B. FIPS-140-1).
- Demo zur Zahlentheorie und zum RSA-Verfahren:
  - Primzahlen generieren und testen.
  - Zahlen (schrittweise) mit verschiedenen Verfahren faktorisieren
    (die verschiedenen Verfahren laufen in parallelen Threats).
  - Das RSA-Kryptosystem transparent durchführen:
     - RSA-Schlüssel erzeugen (auch mit selbst-gewählte Primzahlen).
     - Ver-/Entschlüsseln mit dem RSA-Verfahren.
     - RSA-Signaturen erzeugen und diese verifizieren.
     - das RSA-Verfahren angreifen.
- PKCS#12-Export und -Import von RSA- und DSA-PSEs und damit
  von den darin gespeicherten Schlüsseln.
- Visualisierung durch Flussdiagramm (z.B. beim Diffie-Hellman
  Schlüsselaustausch-Verfahren) oder mit ANIMAL.
- Die modernen Verfahren wurden gemäß den internationalen Standards
  implementiert (Referenzimplementierung).
- Das eigenständige Programm AES-Tool kann selbstentpackende
  Programme erzeugen. Damit kann man eine beliebige Datei ( < 4 GB)
  Passwort-geschützt mit AES verschlüsseln (durch Eingabe eines 
  Hexadezimal-Schlüssels).
  Voller Funktionsumfang auch bei einem Aufruf von der Kommandozeile.
- Die letzte Einstellung zu einem Verfahren (Parameter, Schlüssel oder
  Alphabet) wird Programm-intern aufbewahrt. Der Schlüssel kann pro 
  Verfahren über das Schlüsseleinfügen-Symbol auch wieder abgerufen 
  werden.
- Umfangreiche Dokumentation (Onlinehilfe, Skript).
- Webseite mit den Hashwerten aller herunterladbaren CrypTool-Dateien:
  Damit kann man die Integrität der Dateien aus dem CrypTool-Paket, die
  sich auf dem Computer befinden, überprüfen.
- Weltweite Nutzung in Schulen, Universitäten, Behörden und Firmen.

Eine gute Übersicht liefern auch
- die beigelegte Powerpoint-Präsentation
   (Titel: "Kryptographie mit CrypTool") und
- die CrypTool-Webseite 
   (insbesondere über den Eintrag "CT-Einstiegsseite" im linken Frame).


5.2. Neuerungen in Version 1.4.00
     ----------------------------

a) Entwickler-relevante Änderungen (eher programm-technisch):

- Die Sourcen von CrypTool 1.4.00 können ebenfalls von der CrypTool-
  Homepage heruntergeladen werden (keine Registrierung).

- Details zum Compilieren, Linken und zur einheitlichen Entwicklung
  finden sich in den Sourcen in der Datei "readme-source".

- Die Sourcen lassen sich nun mit der Microsoft Entwicklungsumgebung
  Visual Studio 2003 (VC++ v7.1) compilieren.
  Der Support von VC++ v6.0 wurde aufgegeben (neben einigen Inkompatibili-
  täten zwischen den Compiliern konnte man vor allem die GMP nicht damit
  compilieren).

  Es gibt schon einen Sourcezweig in unserem Subversion-System, der sich
  auch mit VS2005 (VC++ v8.0) übersetzen lässt. Dies wird nach 1.4.00
  offiziell unterstützt.

- Nach der Secude- und der Miracl-Bibliothek werden auch die 
  Bibliotheken von OpenSSL, NTL und GMP eingebunden.

- Die Editoren für Text- und Binärdaten wurden durch Open-Source-
  Editoren mit besserer Funktionalität ausgetauscht und deren Code
  wurde stellenweise erweitert: Dadurch ist der Anzeigevorgang
  schneller und es können größere Dateien geladen werden.

  Hex-Editor / Hex-Control / HexView:
  Link: http://www.codeguru.com/Cpp/controls/controls/article.php/c5287
  -> Erweitert: Einfügen, beim Markieren wird sowohl die Hex- als auch
                die ASCII-Darstellung markiert.

  Text-Editor:
  Link: http://scintilla.sourceforge.net/ScintillaDownload.html

  Außerdem kann man nun auch Dateien, die nicht druckbare Zeichen
  enthalten, im Text-Modus anschauen.

  Mit dem Menüeintrag "Ansicht" \ "Schriftart" kann man schnell
  sinnvolle Größen und den Fonttyp (monospace oder proportional)
  einstellen.
  So ist "Courier 10" z.B. gut, um sich den Output der ADFGVX-Chiffre
  anzusehen.

  Für Textdateien wurde Suchen und Ersetzen um reguläre Ausdrücke 
  erweitert. In Hex-Dateien funktioniert derzeit nur die einfache
  Suche. xxxxxxxxxxxxx

- Die Menüstruktur wurde klarer gegliedert und enthält mehr Einträge.

  Die Menüstruktur ist konstant sichtbar: Einträge, die für bestimmte
  Dokumenttypen nicht ausführbar sind, werden ausgegraut, aber nicht
  mehr ganz entfernt (häufiger Benutzerwunsch).

- Zu jedem Fenster kann nun ein Dialog angezeigt werden, der alle
  wesentlichen Eigenschaften dieses Dokuments anzeigt.

- Die Online-Hilfe ist im HTML-Format (statt wie bisher in Winhelp).

- Alle persistenten Daten werden im Nutzer-lokalen Teil der Registry
  abgelegt (keine INI-Datei mehr), wodurch man CrypTool ohne 
  Administratorrechte ausführen kann und verschiedene Benutzer
  am gleichen PC jeweils verschiedene Einstellungen haben können.

- Mit Hilfe der ANIMAL-Software lassen sich Abläufe visualisieren:
  - Link: http://www.animal.ahrgr.de
  - Weitere Beispiele im ANIMAL-Repository (Datenbank):
    http://www.animal.ahrgr.de/animations.php3?tool=Animal&lang=de


b) Änderungen in der Benutzer-Dokumentation:

- Online-Hilfe verbessert und stark erweitert.

- Im Skript: Behebung kleinerer Fehler, neues Kapitel zu Papier-
  und Bleistiftverfahren, Infos zu Kryptographie in Filmen und
  Belletristk, und etliche Aktualisierungen.

- Weitere Fantasy-Geschichte: In "Das Chinesische Labyrinth" von Dr. 
  Carsten Elsner muss Marco Polo zahlentheoretische Aufgaben lösen.

- Aktualisierte und auf knapp 90 Seiten erweiterte Präsentation.


c) Funktionale Erweiterungen:

- Die Schlüsseleingabemasken für Caesar und monoalphabetische 
  Substitution sind ausführlicher und beinhalten als Option auch 
  gleich die Spezialfälle ROT13 und Atbash.

- Das Verschlüsselungsverfahren Solitaire als Beispiel eines Papier-
  und Bleistiftverfahrens und eine Analyse dazu.

- Die Implementierung und Analyse von ADFGVX als Beispiel einer 
  kaskadierenden Chiffre.

- Eine verbesserte Analyse der monoalphabetischen Substitution.

- Implementierung der Base64- und der UU-Codierung.

- In der Hash-Demo, die die Sensitivität von Hashverfahren
  demonstriert, können nun alle in CrypTool vorhandenen Hashfunktionen
  benutzt werden (nicht nur wie bisher MD2, MD5 und SHA-1).

- Demo zu Authentisierungsmöglichkeiten im Netz (Visualisierung von
  Challenge-Response-Verfahren):
  * von UID/PW und One-Time-Password
  * über (einseitige) Challenge-Response (symmetrisch + asymmetrisch)
  * bis zu asymmetrischer gegenseitiger Authentisierung.
  * Der Benutzer kann interaktiv steuern, wie der Angreifer vorgeht 
    (Rechner übernehmen, Verbindungen aufbauen oder trennen, lauschen).
  * Lerneffekt: nur die gegenseitige asymmetrische Authentisierung ist
    sicher gegen Man-in-the-middle-Angriffe.

- Demo für einen Seitenkanalangriff gegen ein typisches Hybrid-
  verschlüsselungsprotokoll: Bei einer sub-optimalen Implementierung, 
  wie sie in der Realität vorkam, kann der Angreifer den Sessionkey 
  durch Protokoll-gerechte Anfragen an den Server hoch effizient 
  berechnen.

- Drei auf Gitterreduktionsverfahren basierende Angriffe gegen das 
  RSA-Verfahren, die darauf beruhen, dass bestimmte Vorbedingungen 
  erfüllt sind:
  * ein Teil von einem der beiden Faktoren von N ist bekannt 
    ("Faktorisieren mit teilweise bekanntem p"),
  * ein Teil des Klartextes einer abgefangenen verschlüsselten 
    Nachricht ist bekannt und e ist klein ("Angriff auf stereotype
    Nachrichten"),
  * wenn d im Vergleich zu N zu klein gewählt ist, kann man N 
    faktorisieren ("Angriff auf kleine geheime Exponenten").
  Die Diplomarbeit, innerhalb von der diese Verfahren implementiert
  wurden, kann auf Anfrage zugemailt werden (diese Diplomarbeit von
  Herrn Mathias Schneider existiert nur auf Deutsch).

- Implementierung von MAC-Verfahren (Kombination von Hashes und 
  symmetrischen Verfahren zur Authentisierung von Nachrichten). 
  Hashverfahren wurden bisher schon von den in CrypTool implementierten
  Konzepten PKCS#5 und digitale Signaturen verwendet.

- Drei auf dem Chinesischen Restesatz beruhende Anwendungen:
  * Lösung von Systemen linearer modularer Kongruenzen am Beispiel 
    einer Planetenkonstellation im Sonnensystem.
  * Veranschaulichung des Rechnens (Addieren, Subtrahieren, 
    Multiplizieren) mit modularen Resten statt mit den (größeren)
    eigentlichen Zahlen.
  * Veranschaulichen des Shared Secret-Verfahrens (entspricht der 
    Analogie, dass man zum Öffnen eines Tresors z.B. drei beliebige 
    von 5 Schlüsselinhabern braucht).

- Veranschaulichen von Algorithmen (Caesar, Vigenère, Nihilist und DES)
  mit Hilfe der Animationssoftware ANIMAL 2.0 (Java-Applikation, die 
  es erlaubt, die Einzelschritte von Algorithmen oder die Komponenten 
  von Datenstrukturen beliebig genau zu modellieren, diese manuell vor
  und zurück abzuspielen oder automatisch ablaufen zu lassen). 
  Das Animal-System erlaubt die Erstellung von Animationen mithilfe 
  einer GUI, einer Skriptsprache sowie einer Java-API.

- Eine 3-D-Visualisierung von großen Mengen an Zufallszahlen mit Hilfe
  der Volume-Rendering-Engine aus OpenQVis 
  (Java, http://openqvis.sourceforge.net/).

- Die Ergänzung des Secude-Zufallszahlengenerators um die Möglichkeit,
  Entropie auch über Mausbewegung und Tastatureingaben zu sammeln.
  Dies ist die neue Standardeinstellung für den ersten Aufruf des
  kryptografischen Zufallsgenerators, damit deutlich wird, dass man
  für gute Zufallszahlen einen zufälligen Input braucht.

- Das AES-Tool kann nun Dateien bis zu 4 GB ver- und entschlüsseln
  (die alte Grenze lag bei 256 MB).

- Das Shared Secret-Verfahren nach Shamir wurde mit vielen Optionen
  implementiert.

- Bei den asymmetrischen Verfahren RSA und DSA können nun Schlüssel auch
  bis zu 8192 Bit Länge generiert werden (vorher maximal 1024 Bit).

- Zu den Primzahltestverfahren kam explizit das deterministische
  AKS-Verfahren hinzu.

- Einbindung eines Lern-Spiels für Schüler, das diesen den Umgang mit
  Teilern und Primfaktoren näher bringt ("Der Zahlenhai").



6. Mögliche Punkte für eine Weiterentwicklung -- Ideen, Anfragen
   -------------------------------------------------------------

6.1. Funktionalität: Algorithmen / Verfahren
     ---------------------------------------
- Weitere Algorithmen zu jedem Thema implementieren:
    * Verschlüsselung:
       - Fleißner-Schablone bei den klassischen Verfahren.
       - Symmetrische Verfahren:
         Camellia (RFC3713), RC5 und Gost (http://vipul.net/gost).
       - Public Key-Verfahren: McElice und Rabin.
       - Implementieren des NTRU-Verschlüsselungssystems.
       - Demonstration der Visuellen Kryptographie.
    * Hashverfahren:
       - SHA-256, SHA-384, SHA-512
         http://csrc.nist.gov/publications/fips/fips180-2/fips180-2.pdf
       - Tiger (http://www.cs.technion.ac.il/~biham/Reports/Tiger/)
    * Protokolle / Protokollschwächen:
       - Visualisierung von Man-in-the-Middle-Angriffe.
       - Blind Signatures.
       - Elektronische Wahlen.

- Schnelle Auswahl der verschiedenen Verschlüsselungsverfahren
  über eine Dialogbox statt über die Menüs (Offenlegung aller
  Steuerparameter der Algorithmen).

- Kryptographisch starke elliptische Kurven erzeugen und damit
  Implementierung eines auf Elliptischen Kurven basierenden
  Kryptosystems. Dazu könnte man das Kryptosystem von Menezes
  und Vanstone nehmen, das 1993 von diesen Autoren vorgeschlagen
  wurde: A. Menezes and S. Vanstone,
         "Elliptic curve cryptosystems and their implementation",
         Journal of Cryptology, 6 (1993), Seite 209-224.
  Wünschenswert wäre auch:
    * Eine ECC-Demo, die zeigt, wie man in diskreten und in reellen 
      Räumen Punkte auf einer elliptischen Kurve addiert und 
      multipliziert (als Java-Applikation).
    * Die Implementierung der ECC-AES-Hybrid-Verschlüsselung (in C++)
      z.B. mithilfe der Krypto-Bibliothek von cryptovision.

- Hillverfahren
   - Schlüsselmatrix transponieren
   - Eingabe von Zahlen statt Buchstaben in die Schlüsselmatrix.

- ADFGVX
   - Eingabe von gegebenen Passworten und Schlüsselmasken vereinfachen.

- Weil kryptographische Strukturen und Formate häufig ASN.1-
  kodiert sind: Integration eines ASN.1 Dekodier-Tools.

- Zufallszahlen:
  - In Deutschland wird die Evaluierung von deterministischen 
    Zufallszahlengeneratoren durch die AIS 20 (seit Dezember 1999;
    AIS = Anwendungshinweise und Interpretationen zum Schema) und 
    die Evaluierung von physikalischen Zufallszahlengeneratoren 
    durch die AIS 31 (seit September 2001) geregelt. 
    Vor allem die AIS 31 ist auch außerhalb Deutschlands auf 
    großes Interesse gestoßen: darin wird nicht nur wie in FIPS-140
    die Güte des Outputs untersucht, sondern auch das Design des
    Generators selbst!
    Die AIS 20 und AIS 31 befinden sich in deutscher und englischer
    Sprache auf der BSI-Website:
    http://www.bsi.bund.de/zertifiz/zert/interpr/ais20.pdf   
    http://www.bsi.bund.de/zertifiz/zert/interpr/ais31.pdf   
    http://www.bsi.bund.de/zertifiz/zert/interpr/trngkr31.pdf
    Es wäre eine gute Ergänzung für CrypTool, diese Standard-
    anforderungen zur Evaluierung von Zufallszahlen  
    einzubauen und dies auch zu visualisieren.

- Weitere Standards implementieren und direkt über die Menüs bzw.
  aus der Online-Hilfe heraus an alle Stellen verzweigen, wo diese
  Standardverfahren (z.B. PKCS#5) verwendet werden (Hauptarbeit
  dabei sind das User Interface und die Dokumentation).

- Verbindung zwischen CrypTool (PKCS#12) und PGP schaffen, indem
  man PGP-Keys in CrypTool verwenden kann. Idee: Per Passwort-Eingabe
  öffnet man seinen privaten Keyring, analysiert die Struktur, holt den
  Key heraus (PGP-Sourcen sind gegeben) und nutzt diesen, um mit den in
  CrypTool implementierten Verfahren PGP-Files zu entschlüsseln oder zu
  signieren. Damit wird klar, dass PGP nur mit Standard-Algorithmen
  arbeitet.

- CrypTool als Demonstrator für XML-Signaturen.

- Veranschaulichen der Passwortgüte und der Passwortqualität mit Hilfe
  eines Passwort-Quality-Meters.

- Eine pure Kommandozeilenversion des AES-Tools (auch für weitere
  Betriebssysteme).


6.2. Funktionalität: Analyse
     -----------------------
- Wünschenswert wäre, wenn insbesondere die Analyse und ihre
  Visualisierung weiter ausgebaut werden könnte.

- Zu allen Verschlüsselungsverfahren eine (gute) Analyse anbieten
  (zumindest für die klassischen Verfahren besser als Brute-Force).

- Aktuelle Hashangriffe darstellen (Erstellen von PS-Dokumenten nach
  Lucks oder von PDF-Dokumenten nach BSI mit gleichem Hashwert) und
  Aufzeigen der Anwendungsszenarien.

- Analyse neu implementieren für:
   * homophone Verschlüsselung
   * Permutationen/Transpositionen
   * Playfair-Verschlüsselung
      - Reine C-Sourcen (Gunnar-Andresson) liegen uns vor. 

- Analyse verbessern für:
   * monoalphabetische Substitution
      - explizite Anzeige von vertauschten Digrammen wie "ie"/"ei"
        und von Doppelzeichen wie "mm".
      - Ersetzte Buchstaben in der Dialogbox nicht nur groß, sondern
        auch in roter Schrift anzeigen.
   * Wörterbucher für alle Angriffe benutzen, nicht nur für die
     Substitution.

- Massenmustersuche: Erweiterte hoch performante Mustersuche, die
  nach vorgegebenen normierten und regulären Mustern beliebiger Länge
  sucht (z.B. um alle Patterns in einer Datei zu finden, die auch in 
  einer anderen (vorzugebenden) Datei vorkommen), oder die nach 
  unbekannten, aber mehrfach vorkommenden Mustern im Dokumenten sucht.
  Könnte dann auch um Ersetzen erweitert werden.

- Suche nach Patterns m.H. von Normierungen (z.B. "einen" = 12313).
  C-Souren dazu liegen vor.

- Korrekturmöglichkeit einzelner Zeichen bei der Analyse von XOR,
  ADD, Vigenère. Ausschluss unverschlüsseler Bereiche.

- Anzeigen des zweit-, dritt-, ... -besten Treffers bei der
  XOR/ADD-Analyse (dies kann zu einer kürzeren Schlüssellänge
  führen).

- Autokorrelation: vor der Überlagerung noch Operationen auf den
  Blöcken ausführen (XOR, ADD, ...). Macht das Sinn?

- Editieren der Homophonen-Schlüssel (benötigt bei der Analyse
  der Homophonen Verschlüsselung).

- Gleitende Entropie: Automatische Anzeige der entsprechenden Stellen
  mit hoher Entropie.

- Vigenère-Analyse noch weiter veranschaulichen:
  - bei den Keylängen die Eingabe eines Bereiches statt eines Einzel-
    wertes ermöglichen (z.B. "2-9") und dann in der Folgemaske auch
    für jede Länge den statistisch wahrscheinlichen Schlüssel ausgeben.
    Evtl. die Top-10 wahrscheinlichsten Keys für eine bestimmte Länge
    anzeigen.
    Per Klick auf einen der angezeigten Keys erhält man die jeweilige
    Entschlüsselung. Per Klick auf einen weiteren Button werden für
    alle Keys die Entschlüsselungen angeboten.
  - mit der Analyseoption "Basischiffre anzeigen" werden z.Zt. pro
    Spaltencaesar (d.h. bei einer ermittelten Schlüssellänge von
    n wird das Caesarverfahren für jeden Wert von i jeweils auf die
    Zeichenmenge m[i+k*n] mit 1<=i<=n und k>=0 angewandt) die
    Grafiken Korrelation und ASCII-Histogramm erstellt.
    Zusätzlich könnte man noch den Text des jeweiligen Spalten-
    Caesars ausgeben.

- Timing Attack auf RSA / Vorteile Blinding.

- Angriff auf WEP-Protokoll.

- Angriff auf symmetrische Verschlüsselungsverfahren, bei denen die
  Parameter flexibel reduziert werden können.


6.3. Interne Schnittstellen / Editoren
     ---------------------------------
- Alle Anzeigemodule in einem konsistenten Klassenbaum
  zusammenfassen.

- Beliebige Textdateien in Blöcken einstellbarer Breite darstellen:
  z.B. im Format  xxx xxx xxx  oder  xxxxx xxxxx xxxxx ...

- Die Sourcen so umstellen, dass die Ausgabe/Anzeige komplett von
  den Kryptomodulen getrennt ist (erleichtert Portierungen und
  Fehlersuche).

- Parametrisierung, wo immer das möglich ist:
  Anbieten einer Option, um z.B. den Initialisierungsvektor,
  die Anzahl von Runden, die Schlüssel- oder Wortlänge oder
  das Padding zu setzen (z.B. für den RC5-Algorithmus - siehe
  RFC 2040).
  Diese Parameter müssen dann auch in das Format für den internen
  Schlüsselspeicher aufgenommen werden.

- Libraries:
   - Unterstützung weiterer Libraries (LiDIA, FLINT/C, 
     Wei Dai's Crypto++, ...).

- Vorhandene Einschränkungen in der N-Gramm-Analyse bzgl. Dateigröße
  ausdehnen (evtl. mit Benutzerfeedback, wenn viel Zeit erforderlich)
  (vgl. 5.2.a oben).


6.4. User-Interface / Visualisierungen
     ---------------------------------
- In den Dialogen in CrypTool können Zahlen nicht immer in allen
  Darstellungsarten eingegeben werden (z.B. kann im Dialog 
  RSA-Kryptosystem die zu verschlüsselnde Nachricht als Text mit frei
  einzustellendem Alphabet und als Zahl mit 4 verschiedenen Basen) 
  eingegeben werden; die Primzahlen dagegen kann man "nur" als Zahl 
  im Zehnersystem bzw. als Ausdrücke mit Zahlen im Zehnersystem 
  eingeben).
  Nützlich wäre es, wenn man aus CrypTool heraus einen Taschenrechner
  als a-modales Fenster aufmachen könnte, der Terme mit Zahlen 
  beliebiger Basis als Eingabe nimmt und die Ausgabe in mehreren
  Feldern in verschiedenen Zahlensystemen parallel anzeigt. Von hier
  aus sollte man dann die Zahlen per Knopfdruck ins Clipboard bringen
  können oder per Maus in die Eingabefelder der CrypTool-Dialogboxen
  ziehen können.

- Für den Benutzer konfigurierbar einstellbar machen, ob neue Fenster
  wie bisher innerhalb des Hauptfensters erscheinen oder als "freie"
  (modale oder a-modale) Fenster daneben stehen.
  Einzelne Dialogboxen (z.B. N-Gramm-Analyse, Manuelle Analyse,
  Hybriddemo) als a-modale Fenster erzeugen, so dass man beliebig
  zwischen Hauptfenster und Auswertungsfenster springen kann
  (aufwändigere Steuerung, Erlauben oder Abfangen von Mehrfachauf-
  rufen derselben Dialogbox, evtl. Update nach Fokus-Wechsel bzw.
  nach Änderung der Originaldaten im Hauptfenster, ...).

- AES-Tool:
  - Portierung nach Linux, ...
  - Einbinden des PKCS#5-Dialogs, um dem Benutzer seine gewohnte
    Eingabeweise zu bieten: Dabei zufällige Werte für Salz und 
    Iterationszahl voreinstellen und den User auffordern, sich
    den Hexwert zu merken oder ihn sicher aufzubewahren.
  Generell sind bei CrypTool die Schlüssel ganz bewusst für die
  modernen Verschlüsselungsverfahren in Hex-Zeichen einzugeben. 
  Es ist Absicht, dass man in CrypTool zunächst sieht, welche Art
  Schlüssel die verschiedenen Algorithmen erwarten: bei den 
  klassischen Verfahren besteht der Schlüssel aus dem zugrunde
  liegenden Alphabet, bei den modernen symmetrischen Verfahren sind
  es Binärdaten von 56 Bit bis 256 Bit Länge.
  Andererseits sind Benutzer gewohnt, ihre Eingaben per ASCII-Zeichen
  zu machen. Da in einer produktiven Anwendung der Schlüssel nicht
  aus ASCII-Zeichen bestehen sollte, ist es besser, wenn man ein
  ASCII-Passwort als Grundlage verwendet, um daraus mit einem 
  vernünftigen Verfahren einen Schlüssel herzuleiten. 
  In CrypTool könnte man die Anforderung "ASCII-Schlüsseleingabe" und
  "Zeigen, dass gute Hex-Keys zu verwenden sind", folgendermaßen 
  miteinander verbinden:
  In dem Hex-Schlüsseleingabe-Dialog sollte man per Button die 
  Funktion "Einzelverfahren \ Hashverfahren \ Schlüssel aus Passwort
  generieren (PKCS#5)" aufrufen können. 
  Der Dialog ist dann mit der richtigen Schlüssellänge parametrisiert 
  und der generierte Schlüssel wird in die Hex-Schlüsseleingabe 
  übernommen. Damit dies auch für AES-256 funktioniert, müsste noch
  die SHA-256-Hashfunktion eingebaut werden.

- Für den Benutzer konfigurierbar einstellbar machen, wie groß die
  Teile von Text- und Binärdateien sein können, die CrypTool laden
  kann.

- In der Anzeige für Grafiken eine Vergrößerungsfunktion einbauen
  und / oder die Koordinaten anzeigen, an denen sich die Maus
  befindet.

- Visualisierung:
   - Generell ist die Visualisierung der Abhängigkeiten und Abläufe
     bei Protokollen (nicht nur bei "einfachen" Algorithmen) eine
     sinnvolle Erweiterung.
   - Angriffe auf andere asymmetrische Verfahren sind in CrypTool
     bisher noch gar nicht behandelt. Um Diffie-Hellman, DSA oder
     EC-DSA anzugreifen, muss man "diskrete Logarithmen" berechnen.
     Auch dies könnte man nach dem Implementieren wieder 
     visualisieren.


6.5. Erweiterung um zahlentheoretische Funktionen
     --------------------------------------------
- Dialoge in CrypTool implementieren, so dass man CrypTool als Frontend
  für zahlentheoretische Funktionen und Werte nutzen kann.


6.6. Portierung nach Linux, Java und VS2005/WPF
     ------------------------------------------
- Portierung nach Linux mit Hilfe von GCC 4.x und Qt 4.x:
   - Die Libs von Secude, Miracl, NTL, OpenSSL und GMP stehen zur
     Verfügung.
   - Trennung der Gesamtaufgabe in sinnvolle Teile:
       - Oberfläche: hier liegt die Hauptarbeit.
       - Funktionalität, implementiert in purem C/C++: ok
       - Online-Hilfe in HTML: ok.

- Komplett neu designtes CrypTool in Java (JCrypTool):
   - Ein größeres Teilprojekt, das CrypTool nach Java portieren soll
   - Eine Secude-Lib und Bouncy-Castle stehen zur Verfügung.
   - Nutzung von Eclipse, SWT (und Jigloo) zur Entwicklung.
   - Plug-in basierte Architektur.
   - Weitere Entwickler für dieses Teilprojekt sind willkommen
     (Die bisher aktiven Entwickler nutzen ein Wiki zur Kommunikation
     und Subversion zur Source-Verwaltung).

- Portierung auf Windows Vista mit Visual Studio 2005 und .NET.
  Nutzung der neuen GUI-API Windows Presentation Foundation (WPF)
  zur Gestaltung von multimedialen Oberflächen.
   - Nutzen des .NET-Frameworks (kein MFC mehr)
   - Nutzen des VS2005 (nicht mehr VS2003 und nicht mehr VC++6.0),
     sofern sich mit der kostenlosen VS2005-Express-Edition für
     C++ auch das gesamte Projekt bearbeiten lässt.



6.7. Sinnvolle Aufgaben für jemand, der neu anfängt mitzuentwickeln
     --------------------------------------------------------------
- Einbau des RC5-Algorithmus wie oben beschrieben, um zu sehen,
  an welchen Stellen überall die Sourcen dafür zu ergänzen sind
  (Funktion selbst, Optionen, Menüs + Statuszeileninfo, Online-Hilfe).

- Alle möglichen Arten von Transpositionen und Superpositionen
  in einem ansprechenden Dialog anbieten.

- Pattern-Matching-Dialoge.

- Testbett mit Beispielen und Lösungen erzeugen, damit man das
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
1.0.01    Okt. 1999	 1,3 MB		 -		DB
1.1.01    Mai  2000	 2,3 MB		 -		DB
1.2.00    Aug. 2000	 2,8 MB		 -		DB
1.2.02    Dez. 2000	 3,2 MB		 -		DB
1.3.00    Jan. 2002	 4,9 MB		 4,7 MB		DB
1.3.02    Juni 2002	 6,9 MB		 6,4 MB		DB
1.3.03    Sep. 2002	 6,9 MB		 6,5 MB		DB
1.3.04    Juli 2003	 8,6 MB		 8,1 MB		DB
1.3.05    Aug. 2003	 8,6 MB		 8,1 MB		DB
1.4.00    xxx. 2006	14,0 MB		13,5 MB		DB  xxxxxxxxx

Bemerkungen zu den Versionen:
1.3.02    Viele neue Funktionen gegenüber 1.3.00.
1.3.03    Viele kleine Bugfixes und Verbesserungen der Dokumentation.
1.3.04    Etliche neue Funktionalität, einige kleine Bugfixes (Absturz
          bei Playfair-, N-Gramm-Analyse, RSA), und Verbesserung und 
          Erweiterung der Dokumentation (Online-Hilfe, Skript).
1.3.05    Kleine Bugfixes.
1.4.00-Beta10  Dez. 2005  Erste öffentliche Beta von Version 1.4.00.
1.4.00-Beta12  März 2006  Zweite öffentliche Beta von Version 1.4.00.
1.4.00    Viele neue Funktionen gegenüber 1.3.05.



8. Feedback bei Fehlern
   --------------------
Sollten Sie Probleme haben oder Fehler finden, wenden Sie sich
bitte mit einer Beschreibung des Problems per e-mail an
- joerg-cornelius.schneider@db.com   oder
- esslinger@fb5.uni-siegen.de        oder
- an die Mailingliste: cryptool-list@sec.informatik.tu-darmstadt.de

Für Anregungen jeglicher Art bezüglich CrypTool sind wir immer
dankbar und helfen Ihnen gern, wenn es unsere Zeit erlaubt.

Auch würden wir uns freuen, wenn Sie uns mitteilen, wie und wo Sie
CrypTool einsetzen.



9. Kontaktadressen
   ---------------
- joerg-cornelius.schneider@db.com
- esslinger@fb5.uni-siegen.de
- henrik.koy@db.com
- cryptool-list@sec.informatik.tu-darmstadt.de



10. Verweise / Auszeichnungen
    -------------------------

10.1. Artikel über CrypTool
      ---------------------
10.1.1. c't 14/2001
        -----------
In diesem renommierten und auflagenstarken deutsch-sprachigen
Computermagazin wurde im Juli 2001 ein 5-seitiger Artikel zu
CrypTool veröffentlicht (S. 204-208).

10.1.2. DuD Oktober 2002
        ----------------
In der deutsch-sprachigen Fachzeitschrift "DuD Datenschutz und
Datensicherheit", Ausgabe 10/2002 erschien unter dem Titel
"CrypTool - spielerischer Einstieg in klassische und moderne
Kryptographie. Neue Version - fundierte Awareness in Deutsch
und Englisch" ein 4-seitiger Artikel über CrypTool.

10.1.3. KES 2/2003 (Mai 2003)
        ---------------------
In der deutsch-sprachigen Fachzeitschrift "KES - Zeitschrift für
Informations-Sicherheit", Ausgabe 2/2003 erschien unter dem Titel
"(Ver)Schlüsselerlebnisse - CrypTool unterstützt Verständnis für
die Grundlagen der Internetsicherheit" ein 6-seitiger Artikel
über CrypTool.
Diesen Artikel finden Sie im HTML-Format auch auf der KES-Homepage
http://www.kes.info/index.html per Suchbegriff "CrypTool" unter
"Artikel aus der Maiausgabe 2003": "VerSchlüsselerlebnisse: CrypTool
unterstützt Verständnis für die Grundlagen der Internetsicherheit" oder
direkt per http://www.kes.info/archiv/online/03-2-018.htm.

10.1.4. Tagungsband 8. Deutscher IT-Sicherheitskongress des BSI (Mai 2003)
        ------------------------------------------------------------------
Auf dem BSI-Kongress 2003 in Bonn wurde von Hr. Koy der Vortrag
"Awareness in der Informationsgesellschaft: CrypTool - Kryptographie
spielerisch verstehen" gehalten. Die Textfassung dazu steht im 
Tagungsband, "IT-Sicherheit im verteilten Chaos", auf S. 485 - 500.


10.2. Sonstige Referenzen auf CrypTool
      --------------------------------
10.2.1. Wirtschaftswoche Spezial (September 2000)
        -----------------------------------------
Das Spezial "Kryptographie" der Zeitschrift Wirtschaftswoche
(Rubrik Netzwelt Sept. 2000) enthielt ein Preisausschreiben:
"Knacken Sie den Text!" unter der URL
http://www.wiwo.de/wiwowwwangebot/fn/ww/sfn/buildww/cn/
cn_artikel/id/62633!100301/SH/0/depot/0/bt/1/index.html.
Wenn man sich an die Tipps der Aufgabenstellung hielt, konnte man
mit CrypTool die Aufgabe mit wenigen Mausklicks lösen.

10.2.2. BSI Bürger-CD "Ins Internet - mit Sicherheit"
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



10.2.3. Nennungen auf verschiedenen Webseiten
        -------------------------------------

a) Simon Singh hat auf seiner Webseite http://www.simonsingh.net/
   nach dem Schreiben an seinem Buch "Geheime Botschaften" (engl. "The
   Code Book") viel Material zur Kryptographie, ihrer Geschichte und
   Ihrer Vermittlung zusammengetragen.

   In seinem Newsletter (http://www.simonsingh.net/Newsletter_13.html) 
   vom 11.2.2004 nennt er CrypTool als eines von vier weltweit
   empfohlenen Seiten ("4. Crypto tutorials"):
   - www.simonsingh.net/The_Black_Chamber/home.html
   - www.cryptoclub.math.uic.edu/indexmain.html
   - www.antilles.k12.vi.us/math/cryptotut/home.htm
   - www.cryptool.com


b) Auf der Professional Security Testers Warehouse (PST) postete
   Jaganmohan Kataru, CISSP, MCSE in das Security News Dashboard am
   21.09.2005 unter der Überschrift "eLearning Program for Cryptology":
   http://www.professionalsecuritytesters.org/modules.php?name=Forums&
   file=viewtopic&t=34

   Ein ähnliches Post gab es am 22.09.2005 auf der "CISSP, SSCP, CISM, 
   CISA, ISSPCS, and SANS GIAC GCFW Open Study Guides Web site" for 
   Cryptography: http://www.cccure.org/modules.php?name=News&new_topic=51
   mit dem Titel "Cryptool A great tool to learn more about
   cryptography".


c) Wikipedia:
   - Englisch:
     - http://en.wikipedia.org/wiki/Cryptool
     - http://en.wikipedia.org/wiki/Cryptography
     - http://en.wikipedia.org/wiki/Topics_in_Cryptography
   - Deutsch:
     - http://de.wikipedia.org/wiki/CrypTool
     - http://de.wikipedia.org/wiki/Kryptographie
     - http://de.wikipedia.org/wiki/Wikipedia:WikiProjekt_Kryptologie
  - Französisch:
     - fr.wikipedia.org/wiki/Cryptool

d) Eine kleine Auswahl weiterer Seiten:
   http://www.pki-page.org/
   http://www.bsi-fuer-buerger.de/toolbox/tb08.htm
   http://www.itejas.com/index.php/2005/09/22/learn_cryptography_with_cryptool
   http://www.privacycom.net/pwatch/viewArticle.php?article=48
   https://www.a-i3.org/content/view/415/28/
   http://www.fh-lueneburg.de/mathe-lehramt/krypto/krypto.htm
   http://www.kryptographiespielplatz.de/
   http://www.tinohempel.de/info/info/kryptografie/index.htm
   http://www.edsb.ch/e/themen/sicherheit/tipps/kap4.htm
   http://www.roehri.ch/~sr/links/crypto.html
   ...



10.3. Weitere Freeware-Projekte (Crank, CAP, CryptoStudio, etc.)
      ----------------------------------------------------------

Vollständig mit Source-Code verfügbar sind:

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
  Griffon ist ein GTK+ GUI Kryptoanalyse-Paket für "pre-digital 
  Ciphers". Es enthält die folgenden klassischen Verschlüsselungs-
  verfahren: monoalphabetische Transposition, Substitution und Playfair.
  Das Tool liegt nur in englischer Sprache vor.
  Die aktuelle Version 1.0 wurde im November 2000 freigegeben.

- http://www.kryptosproject.org/
  Kryptos ist Open Source-Projekt der George Mason University.
  Krytos ist eine Kryptographie-Lernsoftware mit einer statischen
  Oberfläche, aber vielen modernen Algorithmen. 
  Kryptos hat keine Kryptoanalyse-Funktionen.
  Die aktuelle Version Kryptos 2.0 gibt es seit April 2005.

- http://cryptostudio.sourceforge.net/
  CryptoStudio von Prof. Marco Russo
  Die aktuelle Version 1.0 gibt es seit Juni 2005. Sie ist in Englisch
  und Italienisch verfügbar.
  CryptoStudio ist eine GUI (angeglichen an das Aussehen von Microsofts
  Visual Studio), die Funktionen aus der Open-Source Krypto-Bibliothek
  OpenSSL und seinen Kommandozeilentools nutzt. Daher heißt es auf der
  CryptoStudio-Webseite auch: "Many of the CryptoStudio functionalities
  are a mere GUI wrapper of OpenSSL tools, intended to make those tools
  available also to uninitiated users". Man findet darin auch
  Möglichkeiten zur Datei-Verschlüsselung oder zum Basis-S/MIME-Mail-
  Handling, aber keine Kryptoanalyse.


Die einzigen weiteren uns bekannten brauchbaren Programme, die
Kryptographie und Kryptoanalyse (unter einer graphischen
Oberfläche) verbinden, für die aber kein Source-Code freigegeben
ist, sind:

- CAP von Dr. Richard J. Spillman
  Die aktuelle Version 4.1 gibt es seit 2004 zum Download.
  Diese Software gibt es nur auf Englisch.
  Unter den uns bekannten Programmen hat CAP neben CrypTool die
  umfangreichsten Funktionen zur Kryptoanalyse.
  http://www.cs.plu.edu/courses/privacy/index.htm

- CryptAid von David Lovelock
  (wahrscheinlich seit 1997 nicht mehr weitergepflegt)
  http://archives.math.utk.edu/software/msdos/miscellaneous/cryptaid/.html

- Das Visual Basic-Programm "Cryptological Mathematics" von 
  Prof. R.E. Lewand (anschauliche Darstellung einiger zahlen-
  theoretischer Funktionen und Funktionen zur Ver- und Entschlüsselung;
  keine Funktionen zur Kryptoanalyse; Software zu seinem Buch;
  wahrscheinlich aus dem Jahre 2001)
  http://faculty.goucher.edu/blewand/cryptomath/companion_software.htm

- John Trafton's studentisches Cryptography-Projekt in Java
  (einzelne statistische Funktionen und klassische Verschlüsselungs-
  verfahren; verfügbar seit Dezember 2002)
  http://phoenix.goucher.edu/~jtrafton/Crypto

- Wilhelm M. Plotz' Java-Anwendung CipherClerk
  (Ver- und Entschlüsselung mit vielen klassischen Verfahren;
  letzter Update 2003)
  http://members.aon.at/cipherclerk/

- CryptoBench - GUI um Wei Dai's Crypto++ Bibliothek
  Kompakte und übersichtliche GUI zur Nutzung der Kryptofunktionen aus 
  Wei Dai's Crypto++ Bibliothek (keine Kryptoanalyse).
  Die aktuelle Version 1.0.1 gibt es seit 2004.
  Wei Dai's Crypto++ Bibliothek ist Open Source, die GUI der 
  CryptoBench ist Freeware aber kein Open Source.
  http://www.addario.org/cryptobench/


Falls uns hier etwas entgangen ist, würden wir uns über eine Nachricht
freuen - wir vervollständigen oder korrigieren diese Liste gerne.

Außerdem wollen wir hier ausdrücklich das Angebot machen, die
Anstrengungen für diese einzelnen Programme in ein einziges
Programm zu integrieren. Wir freuen uns über jede Kooperation!!


10.4. Auszeichnungen
      --------------
Generell ist es für uns die größte Auszeichnung, wenn CrypTool
eingesetzt wird, und dabei in Schule, Lehre und Training Nutzen
stiftet. Über die vielen positiven Rückmeldungen freuen wir uns
natürlich sehr.

CrypTool erhielt u.a. folgende explizite Auszeichnungen (s. Webseite):

- TeleTrusT-Förderpreis 2004
  Der TeleTrusT-Förderpreis wurde für die Vermittlung von Wissen und 
  die Förderung der Akzeptanz von kryptographischen Verfahren auf der 
  ISSE-Konferenz verliehen.

- European Information Security Award 2004
  Das CrypTool-Projekt war Finalist beim European Information Security 
  Award (EISA 2004) in der Kategorie "Education and Training", 
  verliehen auf der RSA-Konferenz Europe.

- IT-Sicherheitspreis NRW 2004
  Der IT-Sicherheitspreis NRW in der Kategorie Bildung (eLearning / 
  Wissensvermittlung Kryptographie) ging an das vom Institut für 
  Wirtschaftsinformatik Siegen vorangetriebene CrypTool-Projekt.




11. Anhang
    ------

11.1. CrypTool unter Linux mit Wine
11.1.1. .... CrypTool installieren
11.1.2. .... Wine-Konfiguration
11.1.3. .... CrypTool ausführen


11.1. CrypTool unter Linux mit Wine
      -----------------------------
Diese Hinweise basieren auf Tests mit Wine 0.9.9.

Es wird nicht empfohlen, CrypTool unter Wine zu nutzen, da viele
Dinge dort nur teilweise richtig funktionieren. Eine vollständige
CrypTool-Version unter Linux wird von dem Teilprojekt erwartet, das
eine Portierung m.H. von GCC und Qt4 vornimmt (siehe Kapitel 6.6).
Jeder Entwickler, der hier beitragen kann, ist herzlich willkommen.

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

