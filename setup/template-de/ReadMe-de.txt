==================================================================
    CrypTool, Version 1.4.00 f�r Win32, Juli 2006
    (c) Deutsche Bank AG, Frankfurt am Main
    (c) Universit�t Siegen und Darmstadt
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
 2. .... Beschr�nkungen und Voraussetzungen
 2.1. .... Lern-, Trainings- und Awareness-Software
 2.2. .... Win32-Umgebung
 2.3. .... Installation unter Windows 95
 2.4. .... Interaktive Online-Hilfe unter Windows XP
 2.5. .... Unterst�tzung verschiedener Sprachen
 2.6. .... Einschr�nkungen
 2.7. .... Zertifikate, die mit �lteren CrypTool-Versionen erzeugt wurden
 3. .... Installation / Deinstallation / Betrieb
 3.1. .... Installation und Nutzung von Schl�sseln aus vorherigen Versionen
 3.2. .... Installation in Mehrbenutzersystemen
 3.3. .... Deinstallation of CrypTool
 3.4. .... Betrieb in Mehrbenutzersystemen
 4. .... Liste der Dateien in der Auslieferung
 4.1. .... �berpr�fen der Integrit�t der heruntergeladenen Dateien
 5. .... Neuerungen in CrypTool 1.4.00
 5.1. .... Was bietet CrypTool generell
 5.2. .... Neuerungen in Version 1.4.00
 6. .... M�gliche Punkte f�r eine Weiterentwicklung -- Ideen, Anfragen
 6.1. .... Funktionalit�t: Algorithmen / Verfahren
 6.2. .... Funktionalit�t: Analyse
 6.3. .... Interne Schnittstellen / Editoren
 6.4. .... User-Interface / Visualisierungen
 6.5. .... Erweiterung um zahlentheoretische Funktionen
 6.6. .... Portierung nach Linux, Java und VS2005/WPF
 6.7. .... Sinnvolle Aufgaben f�r jemand, der neu anf�ngt mitzuentwickeln
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
Diese Readme-Datei geh�rt zur kostenlosen Distribution des Open-Source
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
entfallen etwas �ber 1/3 auf die englische Version).

Ziel von CrypTool ist es, kryptographische Mechanismen anschaulich
zu machen und die Verwendung und die Grenzen einzelner Verfahren
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
CrypTool. Diese werden z.B. auf der Webseite, bei der Installation und
auf der Einstiegsseite der Online-Hilfe erl�utert.

F�r bisherige Benutzer von CrypTool d�rften in diesem Readme sind vor
allem die Kapitel 5 (Neuerungen) und 6 (Weiterentwicklung) interessant
sein.

Wir laden jeden herzlich ein, an CrypTool mit zu entwickeln oder
Feedback zu geben. Auch f�r Hinweise zu Arbeiten (Diplom-, Doktor-
oder Seminararbeiten), die man in CrypTool integrieren k�nnte, sind
wir sehr dankbar. 
Kontakte: Siehe Kapitel 8 und 9 unten.


1.1. Wie Sie am besten starten - Der Einstieg in CrypTool
     ----------------------------------------------------
Beim Start von CrypTool �ffnen sich zugleich die Arbeitsfl�che
von CrypTool und im Vordergrund ein kleines Begr��ungsfenster.
Wenn Sie im Begr��ungsfenster gleich die F1-Taste dr�cken, erscheint
zus�tzlich die Startseite der Online-Hilfe.

Diese Startseite ist ein guter Ausgangspunkt, um alle wesentlichen
Inhalte von CrypTool kennen zu lernen (z.B. mit Hilfe der Links auf
dieser Startseite).
Bitte lesen Sie die Hinweise und Tipps der Hilfe-Startseite.

Einen schnellen Einstieg in CrypTool finden Sie, wenn Sie einige
Szenarien (Tutorials) der Online-Hilfe durchspielen (die Szenarien
stehen im Inhaltsverzeichnis der Online-Hilfe unter "Beginn der 
Arbeit mit CrypTool").

Die Funktionen von CrypTool k�nnen Sie am einfachsten ausprobieren
mit der standardm��ig ge�ffneten Datei "Startbeispiel-de.txt".
Sie k�nnen aber auch eine andere unverschl�sselte Datei aus dem 
Unterverzeichnis "examples" oder irgendeine andere Datei auf der 
CrypTool-Arbeitsfl�che �ffnen.

Wenn Ihnen ein Men�punkt nichts sagt oder Sie in einem Dialogfenster
nicht recht weiter wissen, sollten Sie mittels der F1-Taste ausreichend
Hilfe finden (wenn nicht, geben Sie uns bitte Feedback).

Wir w�nschen viel Spa� beim Lernen und beim Ausprobieren der Funktionen
von CrypTool.


1.2. Was beinhaltet die Distribution
     -------------------------------
Das CrypTool-Paket enth�lt die folgenden vier Hauptbestandteile:

(1) Das Programm CrypTool
-------------------------
Hauptteil des CrypTool-Paketes ist das Programm CrypTool selbst.
CrypTool ist eine Demonstration, die vor allem f�r Ausbildungszwecke
eingesetzt wird:

- In CrypTool ist eine umfangreiche Sammlung kryptographischer
  Algorithmen und Protokolle implementiert, die hervorragend 
  dokumentiert und teilweise visualisiert sind.
  Somit ist CrypTool sehr gut geeignet zur Ausbildung und zur
  Mitarbeiter-Sensibilisierung f�r IT-Sicherheit.

- Die meisten der kryptographischen Basisalgorithmen stammen aus:
  - der Industrie-bew�hrten Secude-Bibliothek (Version SDK 7.4.60C)
    (www.secude.com),
  - der Miracl-Bibliothek (Version 4.4.3) (http://indigo.ie/~mscott/),
  - der OpenSSL-Bibliothek (Version 0.9.8),
  - der NTL-Zahlentheorie-Bibliothek von Victor Shoup (Version 5.4) und
  - der GMP-Bibliothek f�r beliebig genaue Arithmetik (Version 4.2.1)
    (http://www.swox.com/gmp/).
 
  Somit ist CrypTool auch eine hervorragende Referenzimplemen-
  tierung.

- Die Kryptoanalyse der meisten der klassischen Verfahren ist
  automatisiert.
  Die Analyse der modernen Verfahren ist eingeschr�nkt, so dass
  CrypTool kein Hackertool ist.

Entwicklungsziel von CrypTool war nicht, dass damit im Wirkbetrieb
eine CA (Certification Authority) betrieben wird oder dass damit 
f�r produktive Zwecke Daten verschl�sselt oder anderweitig gesichert
werden sollten. 


(2) Dokumentation
-----------------
Zum Programm geh�rt eine umfangreiche Dokumentation, die ebenfalls
aus vier Teilen besteht:
a) Readme-Datei (diese Datei),
b) Online-Hilfe
    - Kontext-bezogen zur Bedienung des Programms und mit
      weiterreichenden Erl�uterungen,
    - Demos bzw. Beispiel-Szenarien (hier werden Einzelverfahren
      Schritt f�r Schritt erl�utert)
c) Skript zum Thema Kryptographie (beigelegt als PDF-Datei),
d) Pr�sentation, die auf Folien die M�glichkeiten von CrypTool
   aufzeigt (beigelegt als PDF-Datei).


(3) Eigenst�ndige Programme
---------------------------
Alle diese Programme k�nnen aus CrypTool heraus, aber auch stand-alone
aufgerufen werden.
a) Das Programm AES-Tool (entstanden im CrypTool-Projekt)
   Zum Erstellen selbstentpackender Executables ist in CrypTool ein
   Programm integriert, das auch eigenst�ndig benutzt werden kann.
   Darin wird aus einem Passwort ein Session-Key erzeugt, mit dem
   ein beliebiger Dateiinhalt AES-verschl�sselt wird.
   Dieses Verschl�sselungstool kann sowohl als Fenster als auch von
   Kommandozeile (z.B. aus einer Batchdatei) aufgerufen werden.
b) Das Lernspiel "Der Zahlenhai" (entstanden im CrypTool-Projekt)
   Dieses Lernspiel f�r Sch�ler bringt diesen den Umgang mit
   Teilern und Primfaktoren n�her.
c) Das Animationsprogramm ANIMAL (siehe http://www.animal.ahrgr.de)
   Mit diesem an der TU Darmstadt von Dr. R��ling gepflegten Programm
   kann man die Einzelschritte von Algorithmen oder die Komponenten von
   Datenstrukturen beliebig genau modellieren, diese manuell vor und 
   zur�ck abspielen oder automatisch ablaufen lassen. Das Animal-System
   erlaubt die Erstellung von Animationen mithilfe einer GUI, einer 
   Skriptsprache sowie einer Java-API.


(4) Geschichten mit Bezug zur Zahlentheorie und Kryptographie
-------------------------------------------------------------
Als PDF-Datei sind zwei Geschichten beigelegt:
- In "Der Dialog der Schwestern" wird eine Variante des RSA-Verfahrens
  von den Titelheldinnen benutzt, um verschl�sselt zu kommunizieren.
- In "Das Chinesische Labyrinth" muss Marco Polo zahlentheoretische
  Aufgaben l�sen, um Berater des Gro�en Khan zu werden.

Alle Einzeldateien, die bei der Installation des CrypTool-Paketes
auf Ihre Platte kopiert werden, sind in Kapitel 4 (unten in diesem
Readme) aufgef�hrt.



1.3. Danke
     -----
Zu CrypTool haben viele verschiedene Personen beigetragen --
insbesondere auch in ihrer Freizeit (einige sind namentlich in der
Dialogbox aufgef�hrt, die man erh�lt, wenn man in der Dialogbox 
"�ber CrypTool" einen Doppelklick ausf�hrt). Herzlichen Dank.

Ebenfalls beigetragen haben als Sponsoren die Deutsche Bank AG und
die Technische Universit�t Darmstadt.

Dr. Carsten Elsner erlaubte uns, seine beiden Geschichten als 
PDF-Datei beizulegen.
Der Verfasser, als alleiniger Inhaber aller Rechte an den Werken,
r�umt dem CrypTool-Maintainer das ausschlie�liche Vervielf�lti-
gungs- und Verbreitungsrecht ein. Die Geschichten d�rfen nur zusammen
mit dem CrypTool-Paket verbreitet werden.
Die Geschichte "Der Dialog der Schwestern" wurde zuerst in dem 
Computermagazin c't 25/1999 ver�ffentlicht. W�hrend in der c't
eine etwas gek�rzte Fassung ver�ffentlicht wurde, liegt hier die
Originalfassung bei.

Die Firmen Secude GmbH und Shamus Software Ltd. (siehe oben) 
gestatteten uns gro�z�gigerweise, ihre Krypto-Bibliotheken zu nutzen.
Diese mit CrypTool verteilten Bibliotheken d�rfen nicht in einem
Kontext au�erhalb CrypTool benutzt werden, ohne vorher die erw�hnten
Firmen zu kontaktieren und nach ihren aktuellen Lizenzbedingungen zu
fragen.

Ebenso danken m�chten wir den Open-Source-Entwicklern, deren Code wir
nutzen d�rfen (z.B. die Bibliotheken OpenSSL und NTL) oder die uns
mit ihrem Code Anregungen gaben.


1.4. Maintainer, Hosting und Roadmap
     -------------------------------
Wie geplant hat CrypTool ein akademisches Zuhause erhalten:
Seit Oktober 2002 hostet der Lehrstuhl Sicherheit in der Informations-
technik, Fachbereich Informatik unter Frau Prof. Dr. Claudia Eckert
an der TU Darmstadt die deutsche und englische Webseite von CrypTool
und das CVS-System f�r die Programm-Sourcen.

Die CrypTool-Entwicklergruppe unter Bernhard Esslinger fungiert auch
weiterhin als Maintainer, d.h. sie k�mmert sich um die Pflege des
Codes, die Ver�ffentlichung als Open Source und Freeware, und um
die Koordination der Weiterentwicklung. Die n�chsten Schritte der
Roadmap werden auf der Webseite ver�ffentlicht.

Die Homepage von CrypTool bleibt weiterhin www.cryptool.de.

Wir w�rden uns sehr freuen, wenn sich nicht nur die bisherigen
Entwickler, sondern auch viele neue an der Weiterentwicklung von
CrypTool beteiligen. Ideen dazu finden Sie in Kapitel 6.

Ebenfalls sehr willkommen sind uns Ideen und Infos, wie CrypTool in
Lehre, Schule und Ausbildung eingesetzt wurde, damit wir dazu 
beitragen k�nnen, diese Informationen auszutauschen.



2. Beschr�nkungen und Voraussetzungen
   ----------------------------------

2.1. Lern-, Trainings- und Awareness-Software
     ----------------------------------------
CrypTool dient vor allem Ausbildungs- und Awareness-Zwecken. Man soll
es ohne vorherige Konfiguration sofort benutzen k�nnen.

Das Entwicklungsziel von CrypTool war also nicht, dass damit produktiv
verschl�sselt wird oder dass damit eine CA (Certification Authority)
betrieben wird -- auch wenn die Funktionen korrekt in CrypTool 
implementiert sind.

Beispielsweise steht - im Unterschied zu produktiven CA-Applikationen -
das CA-Schl�sselpaar fest in der Software (Source und Binary) und es
ist gesch�tzt mit einer ebenfalls bewusst sehr einfachen PIN f�r 
die CA-PSE (Personal Security Environment).

Der Rootschl�ssel der in CrypTool 1.4.00 eingebauten CA hat eine L�nge
von 2048 Bit und ist 20 Jahre g�ltig (06.07.2006 - 06.07.2026).
Mit dem alten Rootkey in fr�heren CrypTool-Versionen (1.3.05 und �lter)
ausgestellte Zertifikate k�nnen nicht in Version 1.4.00 importiert werden.

Beachten Sie also beim Umgang mit Zertifikaten, dass jedes CrypTool-
Programm eine Root-CA mit demselben Schl�sselpaar beinhaltet, mit 
der die im Programm erzeugten User-Zertifikate signiert werden. 
D.h. jeder (!), der CrypTool einsetzt, kann User-Zertifikate mit 
dieser eingebauten CA signieren.

Professionelle PKI-Software wie die z.B. die OpenXPKI, Entrust, die
Secude-CA oder die Microsoft-CA managen zus�tzlich den ganzen
Lebenszyklus von Zertifikaten und bieten CRL-Handling, sorgen f�r
eindeutige Seriennummern und nutzen definierte Registrierungsprozesse.

Die in CrypTool vorhandenen Verfahren selbst sind entsprechend den
internationalen Standards implementiert und genauso "gut" wie in
kommerziellen Anwendungen.


2.2. Win32-Umgebung
     --------------
CrypTool erfordert eine Win32-Umgebung, wie sie unter Windows 95,
Windows 98, Windows Me, Windows NT (ab 4.0), Windows 2000 und
Windows XP gegeben ist.

Seit Version 1.4.00 sind weder f�r die Installation noch f�r die
Benutzung Administrator-Rechte notwendig. Persistente Daten werden
nur im CrypTool-Verzeichnis, in das Standard-Windows-Verzeichnis f�r
tempor�re Dateien (TEMP-Verzeichnis) und in den benutzerspezifischen
Bereich der Windows-Registry geschrieben (Details siehe Kapitel 3).

Anmerkung: Wo das TEMP-Verzeichnis von Windows liegt, kann man sehen,
wenn man in Windows-Explorer %TEMP% eingibt. Den Wert kann man unter
Windows XP auch ansehen und anpassen per "System --> Systemeigenschaften
--> Reiter Erweitert --> Umgebungsvariablen".

CrypTool funktioniert grunds�tzlich auch unter FreeBSD/Linux mit
Wine (mit gro�en Abstrichen an Funktionalit�t und Stabilit�t).
Siehe Anhang 11.1.

Eine Portierung auf Linux oder ein Neudesign mit Java oder eine
Vorbereitung auf Windows Vista/Avalon sind weitere Ziele (siehe
Kapitel 6).


2.3. Installation unter Windows 95
     -----------------------------
Bei �lteren Windows 95-Systemen erhalten Sie beim Aufruf von
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


2.4. Interaktive Online-Hilfe unter Windows XP
     -----------------------------------------
Unter Windows XP ist der Aufruf der interaktiven Online-Hilfe �ber
die F1-Taste in einem Spezialfall nicht m�glich: Betroffen sind
nur Men�s, die noch Untermen�s haben. Das Problem tritt nur auf,
wenn das Untermen� aufgeklappt ist. F1 bewirkt dann gar nichts.

Normalerweise kann bei CrypTool auch Hilfe zu einem Men�eintrag
angefordert werden, der selbst weitere Untermen�s hat -- unabh�ngig
davon, ob das Untermen� aufgeklappt ist oder nicht.
Unter Windows XP erh�lt man die Online-Hilfe dazu nur, wenn das
Popup-Fenster der untergeordneten Men�punkte nicht aufgeklappt
ist.
Bei den anderen Windows-Versionen spielt das keine Rolle, dort ist
nur wichtig, dass das Men� den Fokus hat.

Workaround anhand eines Beispiels: 
Markieren Sie den Men�eintrag "Einzelverfahren \ RSA-Kryptosystem":
Wenn das Untermen� zu "RSA-Kryptosystem" aufgeklappt ist und Sie die
Hilfe zum Men�eintrag "RSA-Kryptosystem" selbst haben wollen, 
m�ssen Sie - nur unter Windows XP - erst das Untermen� von 
"RSA-Kryptosystem" mit Escape (Esc) oder der Links-Pfeiltaste wieder
einklappen: Dann funktioniert das Aufrufen der Online-Hilfe mit F1 
auch unter Windows XP.


2.5. Unterst�tzung verschiedener Sprachen
     ------------------------------------
Programm, Hilfesystem und Dokumentation sind mehrsprachig aus-
gelegt (zur Zeit englisch und deutsch).

F�r jede unterst�tzte Sprache gibt es ein eigenes Setup (der
Versuch, alle Sprachen in ein einziges Executable einzubinden
wurde wieder aufgegeben, da die automatische Spracheinstellung
beim Anwender (anhand seiner Systemeinstellungen) nur unter
Windows NT 4.0, nicht aber unter Win9x, korrekt funktionierte).


2.6. Einschr�nkungen
     ---------------
- Zur Demonstration des RSA-Kryptosystem und zur Faktorisierung von
  Zahlen greift CrypTool auf die Langzahlarithmetik der Bibliothek
  Miracl von Shamus Software Ltd. zu. Die Bitl�nge der Zahlen wurde
  in der CrypTool-Anwendung auf 8192 beschr�nkt. 

- Von Bin�rdateien werden "nur" knapp die ersten 2 GB in den
  Hex-Editor geladen (< 0x7ffff000 = 2.147.479.552 Bytes).
 
- Textdateien k�nnen in unbeschr�nkter Gr��e vom Editor geladen werden
  (sofern die Rechnerressourcen reichen).

- Aus Performancegr�nden wurde festgelegt, dass CrypTool bei der
  N-Gramm-Analyse die Dokumente beschr�nkt:
   - f�r Bin�rdateien auf 64 kBytes und
   - f�r Textdateien auf 256 kBytes beschr�nkt.
  Werden l�ngere Dateien ge�ffnet, werden sie -- nur bei dieser Art
  der Anayse -- auf den maximalen Eingabewert gek�rzt.

- Hashwerte k�nnen von Dateien beliebiger Gr��e berechnet werden,
  sofern die Dateien nicht geladen werden. 

- Mit dem AES-Tool k�nnen nur Dateien bis 4 GB Gr��e verschl�sselt
  und archiviert werden (solange mit VS2003 compiliert).

  Bitte beachten Sie, dass die Ausgabe des Standalone AES-Tools nicht
  vollkommen identisch ist mit der Ausgabe, die Sie in CrypTool mit der 
  Men�folge "Ver/Entschl�sseln \ Symmetrisch (modern) \ Rijndael (AES)"
  erhalten (auch nicht, wenn das AES-Tool eine Datei mit der Endung "aes"
  erzeugt). CrypTool selbst verwendet z.Zt. einen festen IV (0), der nicht 
  gespeichert wird. AES-Tool nutzt einen zuf�lligen IV und f�gt diesen 
  zusammen mit dem Dateinamen hinter den verschl�sselten Daten an.


2.7. Zertifikate, die mit �lteren CrypTool-Versionen erzeugt wurden
     --------------------------------------------------------------
Falls Sie Zertifikate, die mit �lteren Versionen von CrypTool erzeugt
wurden, unter CrypTool 1.4.00 weiter verwenden wollen, gehen Sie bitte
folgenderma�en vor:
  a) f�r RSA- und DSA-Schl�ssel:
     Exportieren Sie diese PSEs mit Hilfe des alten CrypTools in ein
     PKCS#12-Format und laden Sie diese Dateien im neuen CrypTool.
  b) f�r ECC-Schl�ssel:
     Hier reicht es, die entsprechenden Dateien 
     (z.B. [da][db][EC-prime239v1][1131039030][d] )
     vom alten CrypTool\pse-Verzeichnis in das neue zu kopieren.



3. Installation / Deinstallation / Betrieb
   ---------------------------------------

3.1. Installation und Nutzung von Schl�sseln aus vorherigen Versionen
     ---------------------------------------------------------------
Sie installieren CrypTool, indem Sie das CrypTool-Setup-Programm an
einer geeigneten Stelle im Dateibaum auf Ihrem PC aufrufen.
Standardm��ig wird CrypTool dann in das Verzeichnis 
            "C:\Programme\CrypTool"
installiert. Das Zielverzeichnis kann in der Installationsroutine
ge�ndert werden.

Besitzen Sie bereits eine fr�here Version von CrypTool, so
empfiehlt es sich, vor der erneuten Installation das alte CrypTool
zu deinstallieren, da unter Umst�nden nicht alle alten
Dateien �berschrieben werden. Bitte beachten Sie:
- Wenn bei der Deinstallation nicht alle Verzeichnisse/Dateien im
  Programmverzeichnis (meist "C:\Programme\CrypTool") gel�scht
  werden, l�schen Sie diese manuell.
- Bei der Deinstallation von CrypTool werden alle bisher erzeugten
  asymmetrischen Schl�ssel gel�scht. Wenn Sie diese Schl�ssel auch
  in der neuen Version von CrypTool nutzen wollen, dann sichern
  Sie vor der Deinstallation das unter dem Programmverzeichnis
  liegende Verzeichnis pse\ mit allen darin gespeicherten Dateien
  in ein anderes Verzeichnis. Vergleiche auch Kapitel 2.7.
  Nachdem die neue Version von CrypTool installiert wurde,
  kopieren Sie das gesicherte pse\-Verzeichnis in das neue
  Programmverzeichnis.
  Alternativ k�nnen Sie RSA- und DSA-PSEs als PKCS#12-Struktur 
  exportieren bzw. importieren.

F�r den Fall, dass mehrere Benutzer dieselbe CrypTool-
Installation verwenden wollen, m�ssen die Zugriffsrechte auf den
Verzeichnissen pse\ und pse\pseca\ und den darin enthaltenen
Dateien f�r alle Benutzer auf Vollzugriff gesetzt werden.

Der Teilbaum "pse\" sollte nicht manuell bearbeitet werden, da
bei einer inkonsistenten Struktur nur eine Neuinstallation von
CrypTool bleibt, um die zertifikatsbasierten Verfahren zu nutzen.


3.2. Installation in Mehrbenutzersystemen
     ------------------------------------
In Mehrbenutzersystemen wie Windows XP hat der Administrator vollen
Zugriff auf das ganze Dateisystem, die restlichen Benutzer k�nnen/sollten
eingeschr�nkt sein.

Zur Installation braucht der Benutzer Schreibrechte f�r das 
Verzeichnis, in das CrypTool installiert werden soll:
- z.B. f�r das Verzeichnis %ProgramFiles% (C:\Programme), 
  falls das Unterverzeichnis "CrypTool" noch nicht angelegt ist,  oder
- f�r das Verzeichnis %ProgramFiles%\CrypTool (C:\Programme\CrypTool),
  falls dieses schon angelegt ist).
Hat er diese Rechte nicht, bricht die Installation ab.

Deshalb sollten Sie als normaler Benutzer ohne Administratorrechte als 
Zielverzeichnis ein sogenanntes "lokales Verzeichnis" angeben (statt
"C:\Programme"). Lokal und f�r den Benutzer zug�nglich k�nnten z.B. sein:
%ALLUSERSPROFILE% (Die standardeinstellung in deutschem Windows XP ist: 
"C:\Dokumente und Einstellungen\All Users").

Wenn Sie CrypTool ohne Administratorrechte installieren und keine
Schreibrechte auf %ALLUSERSPROFILE%\Start Menu haben, werden unter WXP
im Startmen� ("Start \ Alle Programme") die Eintr�ge zu CrypTool fehlen.
Jeder Nutzer kann diese Eintr�ge aber manuell in sein eigenes Startmen�
aufnehmen.

Anmerkung: Wie bei %TEMP% auch, k�nnen Sie sehen, wo diese Verzeichnisse
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
der lokalen Registry gespeichert (z.B. die zuletzt ge�ffneten Dateien):
Dadurch braucht man keine ini-Datei mehr im Windows-Verzeichnis und 
unterst�tzt den Betrieb in Mehrbenutzersystemen.
 
Will der Benutzer in Mehrbenutzersystemen wie Windows XP aus CrypTool
heraus Dateien anlegen (bzw. �ndern), braucht er Schreibrechte auf das
entsprechende Zielverzeichnis (bzw. auf die entsprechende Datei). 
Geht das nicht, kommt eine Warnung.
Explizit n�tig sind Schreibrechte nur auf 2 Verzeichnissen:
- das Standard-Windows-Verzeichnis f�r tempor�re Dateien (TEMP)
  f�r die cry*.*-Dateien,
- das Unterverzeichnis "CrypTool\pse", da darin die erzeugten 
  asymmetrischen Zertifikate und Schl�ssel abgelegt werden (siehe
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

CrypTool.exe ..... Das ausf�hrbare Programm.
aestool.exe ...... Ein Programm, das Dateien in sich selbst entpackende
                   Programme verschl�sselt. Zur Entschl�sselung m�ssen
                   Sie das korrekte Passwort eingeben.
CrypTool-de.chm .. HTML-Hilfe-Archiv f�r die CrypTool-Onlinehilfe in
                   deutsch.
CrypTool-en.chm .. HTML-Hilfe-Archiv f�r die Onlinehilfe (englisch).

EC-Param.ini ..... Initialisierungsdatei f�r auf Elliptischen
                   Kurven basierende Public Key-Verfahren.
secude.dll ....... Bibliothek kryptographischer Funktionen von der
                   Secude GmbH.
ticket ........... Lizenz f�r die Secude-Bibliothek.
libxml2.dll ...... Wird ben�tigt von der secude.dll.
secidea.dll ...... Wird ben�tigt von der secude.dll f�r die 
                   IDEA-Verschl�sselung.
srndmskb.dll ..... Wird ben�tigt von der secude.dll f�r den 
                   Entropiesammler zur Initialisierung des 
                   Secude-Zufallsgenerators.
db.dll ........... Wird ben�tigt von der secude.dll.
libeay32.dll...... Bibliothek aus OpenSSL.
SciLexer.dll ..... Bibliothek mit den Routinen f�r den 
                   Scintilla-Texteditor.
TEST-Param.ini ... Initialisierungsdatei f�r die Zufallstests.
irunin.* ......... Diese Dateien sind n�tig f�r Installation und
                   Deinstallation von CrypTool.

script-de.pdf .... Ein Skript (deutsch) �ber Kryptographie, Primzahlen,
                   elementare Zahlentheorie und die Mathematik hinter
                   einigen Algorithmen.
script-en.pdf .... Die englische Fassung von script-de.pdf.
CrypToolPresentation_1_4_00_de.pdf .. Folien-Pr�sentation (deutsch)
CrypToolPresentation_1_4_00_en.pdf .. Folien-Pr�sentation (englisch)
DialogSchwestern.pdf .. Fantasy-Geschichte von Dr. Elsner, in der
                        eine Variante des RSA-Kryptosystems
                        beschrieben wird.
DialogueSisters.pdf ... Englische Fassung von DialogSchwestern.pdf.
ChinLab-de.pdf.pdf .. Geschichte von Dr. Elsner �ber zahlentheoretische
                      Probleme, die Marco Polo vom Gro�en Khan gestellt
                      werden.
ChinLab-en.pdf.pdf .. Englische Fassung von ChinLab-de.pdf.


examples\ ........ Dieses Verzeichnis enth�lt unterschiedliche
                   Beispieldateien, die in den Szenarien verwendet
                   werden. Dateien mit der Endung ".txt" sind
                   Textdateien. Alle anderen Dateien sind bin�r.
                   Dateien mit dem Format "XX-enc-YY.*" sind
                   verschl�sselte Dateien. Bitte ver�ndern Sie
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
        \Original.txt ..... "Harmlose" Beispieldatei f�r die 
                            Hashkollision-Demo
        \original.txt ..... Englische Fassung von Original.txt
        \Faelschung.txt ... "Gef�hrliche" Beispieldatei f�r die
                            Hashkollision-Demo
        \fake.txt ......... Englische Fassung von Faelschung.txt
        \letterFromAliceToBob-DECRYPTED-de.txt .. Beispieldateien
        \letterFromAliceToBob-DECRYPTED-en.txt .. f�r die Demo
        \letterFromAliceToBob-ENCRYPTED-de.hex .. des Seitenkanal-
        \letterFromAliceToBob-ENCRYPTED-en.hex .. angriffs


reference\ ....... Dieses Verzeichnis enth�lt Textdateien in den
                   Sprachen Deutsch, Englisch, Franz�sisch,
                   Spanisch und Latein. Diese Dateien werden
                   standardm��ig als Referenz f�r die Analyse von
                   Chiffretexten herangezogen.
                   Diese Dateien sind schreibgesch�tzt.

reference\deutsch.txt  // Auszug aus dem dt. Umsatzsteuergesetz
         \english.txt  // Auszug aus der Agenda 21[UN-Dokument]
         \genesis-de.txt  // Buch Genesis in den Sprachen
         \genesis-en.txt  // deutsch, englisch, franz�sisch,
         \genesis-es.txt  // spanisch und lateinisch.
         \genesis-fr.txt  // Die 2-Buchstabencodes entsprechen
         \genesis-la.txt  // den ISO 639 Language Codes.


animal\ .......... Dieses Verzeichnis enth�lt die Dateien, die f�r
                   das Animationsprogramm ANIMAL n�tig sind.

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

animal\anims ..... Dieses Verzeichnis enth�lt AML-Dateien. 
                   In jeder AML-Datei ist die Beschreibung zu einer
                   Animation f�r ein Verschl�sselungsverfahren
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
                   (asymmetrische) Schl�ssel und Zertifikate abgelegt.

pse\[Bob][SideChannelAttack][RSA-512][1126252192][PIN=1234].pse

pse\pseca\calog    Diese Dateien sind f�r die Verwaltung der
         \CA_exts  Schl�sseldatenbank notwendig.
         \cert.dir
         \cert.pag
         \crls.dir
         \crls.pag
         \pseca
         \user.dir
         \user.pag


W�hrend der Laufzeit von CrypTool werden die folgenden Dateien
erzeugt und verwaltet:
cry*.* ........... CrypTool schreibt tempor�re Dateien mit dem
                   Namensmuster cry*.* in das TEMP-Verzeichnis.
                   Es gibt folgende Endungen: 
                   hex -> hexadezimale (bin�re) Inhalte
                   org -> xxxxxxxxxx
                   plt -> Diagrammausgabe (Histogramm, Autokorrelation)
                   tmp -> xxxxxxxxxx
                   txt -> Textdateien
                   ogl -> OpenGL-Beschreibungen.


4.1. �berpr�fen der Integrit�t der heruntergeladenen Dateien
     -------------------------------------------------------
Die Integrit�t von Dateien kann mit Hashwerten �berpr�ft
werden. Hashwerte sind wie Fingerabdr�cke -- mit einer sehr geringen
Informationsmenge kann man ein viel gr��eres Objekt identifizieren.

Dateien vom CrypTool-Projekt k�nnen auf folgende beiden Arten auf Ihren
Computer gelangen: entweder durch direktes Herunterladen oder durch 
Entpacken einer heruntergeladenen Datei:
a) Herunterladbare Dateien:
   Auf der Homepage von CrypTool www.cryptool.de finden Sie
   die Hashwerte aller von der deutschen Webseite direkt
   herunterladbaren Dateien in den Dateien md5sum.txt bzw.
   in sha1sum.txt.
   Wenn man den Hashwert einer heruntergeladenen Datei neu berechnet
   und mit den Werten auf der CrypTool-Homepage vergleicht, kann man
   sehen, ob man eine unver�nderte Kopie der Originaldatei hat oder
   nicht.
   Weichen die Hashwerte voneinander ab, sollte man die Datei
   nochmal herunterladen und evtl. die Ursache daf�r suchen, dass
   man eine ver�nderte Datei auf seinem Rechner hat.
b) Zus�tzlich k�nnen Sie auch die Dateien INNERHALB des 
   heruntergeladenen Setup-Paketes �berpr�fen:
   Deren Hashwerte stehen ebenfalls in den Dateien md5sum.txt bzw.
   in sha1sum.txt.

Zur �berpr�fung der Integrit�t der heruntergeladenen oder entpackten
Dateien k�nnen Sie weit verbreitete Tools wie MD5SUM und SHA1SUM
verwenden.

Alternativ k�nnen Sie auch das Programm CrypTool selbst verwenden:
  Die Hashwerte von "externen" Dateien k�nnen Sie mit CrypTool
  berechnen, auch ohne die Dateien vorher in CrypTool zu laden:
  - Men� "Einzelverfahren \ Hashverfahren \ Hashwert einer Datei"
    anklicken,
  - �ffnen der entsprechenden Datei,
  - Auswahl von MD5 oder SHA1 als Hashalgorithmus,
  - Vergleich mit dem Wert in den Dateien md5sum.txt oder SHA1sum.txt.

Aus Sicherheitsgr�nden empfiehlt sich der Vergleich bei
Bin�rdateien (EXE, DLL, PDF, ...), wenn Sie nicht ganz sicher
sind, dass Ihr Rechner unber�hrt ist.



5. Neuerungen in CrypTool 1.4.00
   -----------------------------

Kapitel 5 listet die Erweiterungen und Bugfixes auf, die in
CrypTool 1.4.00 seit CrypTool 1.3.05 hinzugef�gt wurden.

5.1. Was bietet CrypTool generell
     ----------------------------
Hier vorab noch mal die generellen Eigenschaften von CrypTool:
- eLearning-Programm rund um das Thema Kryptographie.
- Kryptographie und Kryptoanalyse unter einer Oberfl�che.
- Alles in Deutsch und Englisch.
- Klassische Verschl�sselungsverfahren, und daf�r teilweise manuell
  unterst�tzte, teilweise automatische Analyse.
- Moderne symmetrische Verschl�sselungsverfahren, und die
  Brute-Force-Analyse dazu
  (Bei der Brute-Force-Attacke auf symmetrische Algorithmen werden
   Jokerzeichen zugelassen und die erwartete Zeit wird ausgegeben. 
   Au�erdem kann man die Breite f�r das hierbei genutzte
   Entropiefenster in den Analyseoptionen einstellen).
- Moderne Kryptoverfahren und Protokolle (Hash, RSA, ECC, Digitale
  Signatur, Hybrid-Verschl�sselung, PKCS#5, Shared Secret, ...) und
  teilweise Angriffe darauf (Geburtstagsangriff, Seitenkanalangriff, 
  Gitterbasenreduktion).
- Hashwerte berechnen und ihre Sensitivit�t demonstrieren.
- Pseudozufallszahlengeneratoren und statistische Analysen f�r 
  Zufallsdaten (z.B. FIPS-140-1).
- Demo zur Zahlentheorie und zum RSA-Verfahren:
  - Primzahlen generieren und testen.
  - Zahlen (schrittweise) mit verschiedenen Verfahren faktorisieren
    (die verschiedenen Verfahren laufen in parallelen Threats).
  - Das RSA-Kryptosystem transparent durchf�hren:
     - RSA-Schl�ssel erzeugen (auch mit selbst-gew�hlte Primzahlen).
     - Ver-/Entschl�sseln mit dem RSA-Verfahren.
     - RSA-Signaturen erzeugen und diese verifizieren.
     - das RSA-Verfahren angreifen.
- PKCS#12-Export und -Import von RSA- und DSA-PSEs und damit
  von den darin gespeicherten Schl�sseln.
- Visualisierung durch Flussdiagramm (z.B. beim Diffie-Hellman
  Schl�sselaustausch-Verfahren) oder mit ANIMAL.
- Die modernen Verfahren wurden gem�� den internationalen Standards
  implementiert (Referenzimplementierung).
- Das eigenst�ndige Programm AES-Tool kann selbstentpackende
  Programme erzeugen. Damit kann man eine beliebige Datei ( < 4 GB)
  Passwort-gesch�tzt mit AES verschl�sseln (durch Eingabe eines 
  Hexadezimal-Schl�ssels).
  Voller Funktionsumfang auch bei einem Aufruf von der Kommandozeile.
- Die letzte Einstellung zu einem Verfahren (Parameter, Schl�ssel oder
  Alphabet) wird Programm-intern aufbewahrt. Der Schl�ssel kann pro 
  Verfahren �ber das Schl�sseleinf�gen-Symbol auch wieder abgerufen 
  werden.
- Umfangreiche Dokumentation (Onlinehilfe, Skript).
- Webseite mit den Hashwerten aller herunterladbaren CrypTool-Dateien:
  Damit kann man die Integrit�t der Dateien aus dem CrypTool-Paket, die
  sich auf dem Computer befinden, �berpr�fen.
- Weltweite Nutzung in Schulen, Universit�ten, Beh�rden und Firmen.

Eine gute �bersicht liefern auch
- die beigelegte Powerpoint-Pr�sentation
   (Titel: "Kryptographie mit CrypTool") und
- die CrypTool-Webseite 
   (insbesondere �ber den Eintrag "CT-Einstiegsseite" im linken Frame).


5.2. Neuerungen in Version 1.4.00
     ----------------------------

a) Entwickler-relevante �nderungen (eher programm-technisch):

- Die Sourcen von CrypTool 1.4.00 k�nnen ebenfalls von der CrypTool-
  Homepage heruntergeladen werden (keine Registrierung).

- Details zum Compilieren, Linken und zur einheitlichen Entwicklung
  finden sich in den Sourcen in der Datei "readme-source".

- Die Sourcen lassen sich nun mit der Microsoft Entwicklungsumgebung
  Visual Studio 2003 (VC++ v7.1) compilieren.
  Der Support von VC++ v6.0 wurde aufgegeben (neben einigen Inkompatibili-
  t�ten zwischen den Compiliern konnte man vor allem die GMP nicht damit
  compilieren).

  Es gibt schon einen Sourcezweig in unserem Subversion-System, der sich
  auch mit VS2005 (VC++ v8.0) �bersetzen l�sst. Dies wird nach 1.4.00
  offiziell unterst�tzt.

- Nach der Secude- und der Miracl-Bibliothek werden auch die 
  Bibliotheken von OpenSSL, NTL und GMP eingebunden.

- Die Editoren f�r Text- und Bin�rdaten wurden durch Open-Source-
  Editoren mit besserer Funktionalit�t ausgetauscht und deren Code
  wurde stellenweise erweitert: Dadurch ist der Anzeigevorgang
  schneller und es k�nnen gr��ere Dateien geladen werden.

  Hex-Editor / Hex-Control / HexView:
  Link: http://www.codeguru.com/Cpp/controls/controls/article.php/c5287
  -> Erweitert: Einf�gen, beim Markieren wird sowohl die Hex- als auch
                die ASCII-Darstellung markiert.

  Text-Editor:
  Link: http://scintilla.sourceforge.net/ScintillaDownload.html

  Au�erdem kann man nun auch Dateien, die nicht druckbare Zeichen
  enthalten, im Text-Modus anschauen.

  Mit dem Men�eintrag "Ansicht" \ "Schriftart" kann man schnell
  sinnvolle Gr��en und den Fonttyp (monospace oder proportional)
  einstellen.
  So ist "Courier 10" z.B. gut, um sich den Output der ADFGVX-Chiffre
  anzusehen.

  F�r Textdateien wurde Suchen und Ersetzen um regul�re Ausdr�cke 
  erweitert. In Hex-Dateien funktioniert derzeit nur die einfache
  Suche. xxxxxxxxxxxxx

- Die Men�struktur wurde klarer gegliedert und enth�lt mehr Eintr�ge.

  Die Men�struktur ist konstant sichtbar: Eintr�ge, die f�r bestimmte
  Dokumenttypen nicht ausf�hrbar sind, werden ausgegraut, aber nicht
  mehr ganz entfernt (h�ufiger Benutzerwunsch).

- Zu jedem Fenster kann nun ein Dialog angezeigt werden, der alle
  wesentlichen Eigenschaften dieses Dokuments anzeigt.

- Die Online-Hilfe ist im HTML-Format (statt wie bisher in Winhelp).

- Alle persistenten Daten werden im Nutzer-lokalen Teil der Registry
  abgelegt (keine INI-Datei mehr), wodurch man CrypTool ohne 
  Administratorrechte ausf�hren kann und verschiedene Benutzer
  am gleichen PC jeweils verschiedene Einstellungen haben k�nnen.

- Mit Hilfe der ANIMAL-Software lassen sich Abl�ufe visualisieren:
  - Link: http://www.animal.ahrgr.de
  - Weitere Beispiele im ANIMAL-Repository (Datenbank):
    http://www.animal.ahrgr.de/animations.php3?tool=Animal&lang=de


b) �nderungen in der Benutzer-Dokumentation:

- Online-Hilfe verbessert und stark erweitert.

- Im Skript: Behebung kleinerer Fehler, neues Kapitel zu Papier-
  und Bleistiftverfahren, Infos zu Kryptographie in Filmen und
  Belletristk, und etliche Aktualisierungen.

- Weitere Fantasy-Geschichte: In "Das Chinesische Labyrinth" von Dr. 
  Carsten Elsner muss Marco Polo zahlentheoretische Aufgaben l�sen.

- Aktualisierte und auf knapp 90 Seiten erweiterte Pr�sentation.


c) Funktionale Erweiterungen:

- Die Schl�sseleingabemasken f�r Caesar und monoalphabetische 
  Substitution sind ausf�hrlicher und beinhalten als Option auch 
  gleich die Spezialf�lle ROT13 und Atbash.

- Das Verschl�sselungsverfahren Solitaire als Beispiel eines Papier-
  und Bleistiftverfahrens und eine Analyse dazu.

- Die Implementierung und Analyse von ADFGVX als Beispiel einer 
  kaskadierenden Chiffre.

- Eine verbesserte Analyse der monoalphabetischen Substitution.

- Implementierung der Base64- und der UU-Codierung.

- In der Hash-Demo, die die Sensitivit�t von Hashverfahren
  demonstriert, k�nnen nun alle in CrypTool vorhandenen Hashfunktionen
  benutzt werden (nicht nur wie bisher MD2, MD5 und SHA-1).

- Demo zu Authentisierungsm�glichkeiten im Netz (Visualisierung von
  Challenge-Response-Verfahren):
  * von UID/PW und One-Time-Password
  * �ber (einseitige) Challenge-Response (symmetrisch + asymmetrisch)
  * bis zu asymmetrischer gegenseitiger Authentisierung.
  * Der Benutzer kann interaktiv steuern, wie der Angreifer vorgeht 
    (Rechner �bernehmen, Verbindungen aufbauen oder trennen, lauschen).
  * Lerneffekt: nur die gegenseitige asymmetrische Authentisierung ist
    sicher gegen Man-in-the-middle-Angriffe.

- Demo f�r einen Seitenkanalangriff gegen ein typisches Hybrid-
  verschl�sselungsprotokoll: Bei einer sub-optimalen Implementierung, 
  wie sie in der Realit�t vorkam, kann der Angreifer den Sessionkey 
  durch Protokoll-gerechte Anfragen an den Server hoch effizient 
  berechnen.

- Drei auf Gitterreduktionsverfahren basierende Angriffe gegen das 
  RSA-Verfahren, die darauf beruhen, dass bestimmte Vorbedingungen 
  erf�llt sind:
  * ein Teil von einem der beiden Faktoren von N ist bekannt 
    ("Faktorisieren mit teilweise bekanntem p"),
  * ein Teil des Klartextes einer abgefangenen verschl�sselten 
    Nachricht ist bekannt und e ist klein ("Angriff auf stereotype
    Nachrichten"),
  * wenn d im Vergleich zu N zu klein gew�hlt ist, kann man N 
    faktorisieren ("Angriff auf kleine geheime Exponenten").
  Die Diplomarbeit, innerhalb von der diese Verfahren implementiert
  wurden, kann auf Anfrage zugemailt werden (diese Diplomarbeit von
  Herrn Mathias Schneider existiert nur auf Deutsch).

- Implementierung von MAC-Verfahren (Kombination von Hashes und 
  symmetrischen Verfahren zur Authentisierung von Nachrichten). 
  Hashverfahren wurden bisher schon von den in CrypTool implementierten
  Konzepten PKCS#5 und digitale Signaturen verwendet.

- Drei auf dem Chinesischen Restesatz beruhende Anwendungen:
  * L�sung von Systemen linearer modularer Kongruenzen am Beispiel 
    einer Planetenkonstellation im Sonnensystem.
  * Veranschaulichung des Rechnens (Addieren, Subtrahieren, 
    Multiplizieren) mit modularen Resten statt mit den (gr��eren)
    eigentlichen Zahlen.
  * Veranschaulichen des Shared Secret-Verfahrens (entspricht der 
    Analogie, dass man zum �ffnen eines Tresors z.B. drei beliebige 
    von 5 Schl�sselinhabern braucht).

- Veranschaulichen von Algorithmen (Caesar, Vigen�re, Nihilist und DES)
  mit Hilfe der Animationssoftware ANIMAL 2.0 (Java-Applikation, die 
  es erlaubt, die Einzelschritte von Algorithmen oder die Komponenten 
  von Datenstrukturen beliebig genau zu modellieren, diese manuell vor
  und zur�ck abzuspielen oder automatisch ablaufen zu lassen). 
  Das Animal-System erlaubt die Erstellung von Animationen mithilfe 
  einer GUI, einer Skriptsprache sowie einer Java-API.

- Eine 3-D-Visualisierung von gro�en Mengen an Zufallszahlen mit Hilfe
  der Volume-Rendering-Engine aus OpenQVis 
  (Java, http://openqvis.sourceforge.net/).

- Die Erg�nzung des Secude-Zufallszahlengenerators um die M�glichkeit,
  Entropie auch �ber Mausbewegung und Tastatureingaben zu sammeln.
  Dies ist die neue Standardeinstellung f�r den ersten Aufruf des
  kryptografischen Zufallsgenerators, damit deutlich wird, dass man
  f�r gute Zufallszahlen einen zuf�lligen Input braucht.

- Das AES-Tool kann nun Dateien bis zu 4 GB ver- und entschl�sseln
  (die alte Grenze lag bei 256 MB).

- Das Shared Secret-Verfahren nach Shamir wurde mit vielen Optionen
  implementiert.

- Bei den asymmetrischen Verfahren RSA und DSA k�nnen nun Schl�ssel auch
  bis zu 8192 Bit L�nge generiert werden (vorher maximal 1024 Bit).

- Zu den Primzahltestverfahren kam explizit das deterministische
  AKS-Verfahren hinzu.

- Einbindung eines Lern-Spiels f�r Sch�ler, das diesen den Umgang mit
  Teilern und Primfaktoren n�her bringt ("Der Zahlenhai").



6. M�gliche Punkte f�r eine Weiterentwicklung -- Ideen, Anfragen
   -------------------------------------------------------------

6.1. Funktionalit�t: Algorithmen / Verfahren
     ---------------------------------------
- Weitere Algorithmen zu jedem Thema implementieren:
    * Verschl�sselung:
       - Flei�ner-Schablone bei den klassischen Verfahren.
       - Symmetrische Verfahren:
         Camellia (RFC3713), RC5 und Gost (http://vipul.net/gost).
       - Public Key-Verfahren: McElice und Rabin.
       - Implementieren des NTRU-Verschl�sselungssystems.
       - Demonstration der Visuellen Kryptographie.
    * Hashverfahren:
       - SHA-256, SHA-384, SHA-512
         http://csrc.nist.gov/publications/fips/fips180-2/fips180-2.pdf
       - Tiger (http://www.cs.technion.ac.il/~biham/Reports/Tiger/)
    * Protokolle / Protokollschw�chen:
       - Visualisierung von Man-in-the-Middle-Angriffe.
       - Blind Signatures.
       - Elektronische Wahlen.

- Schnelle Auswahl der verschiedenen Verschl�sselungsverfahren
  �ber eine Dialogbox statt �ber die Men�s (Offenlegung aller
  Steuerparameter der Algorithmen).

- Kryptographisch starke elliptische Kurven erzeugen und damit
  Implementierung eines auf Elliptischen Kurven basierenden
  Kryptosystems. Dazu k�nnte man das Kryptosystem von Menezes
  und Vanstone nehmen, das 1993 von diesen Autoren vorgeschlagen
  wurde: A. Menezes and S. Vanstone,
         "Elliptic curve cryptosystems and their implementation",
         Journal of Cryptology, 6 (1993), Seite 209-224.
  W�nschenswert w�re auch:
    * Eine ECC-Demo, die zeigt, wie man in diskreten und in reellen 
      R�umen Punkte auf einer elliptischen Kurve addiert und 
      multipliziert (als Java-Applikation).
    * Die Implementierung der ECC-AES-Hybrid-Verschl�sselung (in C++)
      z.B. mithilfe der Krypto-Bibliothek von cryptovision.

- Hillverfahren
   - Schl�sselmatrix transponieren
   - Eingabe von Zahlen statt Buchstaben in die Schl�sselmatrix.

- ADFGVX
   - Eingabe von gegebenen Passworten und Schl�sselmasken vereinfachen.

- Weil kryptographische Strukturen und Formate h�ufig ASN.1-
  kodiert sind: Integration eines ASN.1 Dekodier-Tools.

- Zufallszahlen:
  - In Deutschland wird die Evaluierung von deterministischen 
    Zufallszahlengeneratoren durch die AIS 20 (seit Dezember 1999;
    AIS = Anwendungshinweise und Interpretationen zum Schema) und 
    die Evaluierung von physikalischen Zufallszahlengeneratoren 
    durch die AIS 31 (seit September 2001) geregelt. 
    Vor allem die AIS 31 ist auch au�erhalb Deutschlands auf 
    gro�es Interesse gesto�en: darin wird nicht nur wie in FIPS-140
    die G�te des Outputs untersucht, sondern auch das Design des
    Generators selbst!
    Die AIS 20 und AIS 31 befinden sich in deutscher und englischer
    Sprache auf der BSI-Website:
    http://www.bsi.bund.de/zertifiz/zert/interpr/ais20.pdf   
    http://www.bsi.bund.de/zertifiz/zert/interpr/ais31.pdf   
    http://www.bsi.bund.de/zertifiz/zert/interpr/trngkr31.pdf
    Es w�re eine gute Erg�nzung f�r CrypTool, diese Standard-
    anforderungen zur Evaluierung von Zufallszahlen  
    einzubauen und dies auch zu visualisieren.

- Weitere Standards implementieren und direkt �ber die Men�s bzw.
  aus der Online-Hilfe heraus an alle Stellen verzweigen, wo diese
  Standardverfahren (z.B. PKCS#5) verwendet werden (Hauptarbeit
  dabei sind das User Interface und die Dokumentation).

- Verbindung zwischen CrypTool (PKCS#12) und PGP schaffen, indem
  man PGP-Keys in CrypTool verwenden kann. Idee: Per Passwort-Eingabe
  �ffnet man seinen privaten Keyring, analysiert die Struktur, holt den
  Key heraus (PGP-Sourcen sind gegeben) und nutzt diesen, um mit den in
  CrypTool implementierten Verfahren PGP-Files zu entschl�sseln oder zu
  signieren. Damit wird klar, dass PGP nur mit Standard-Algorithmen
  arbeitet.

- CrypTool als Demonstrator f�r XML-Signaturen.

- Veranschaulichen der Passwortg�te und der Passwortqualit�t mit Hilfe
  eines Passwort-Quality-Meters.

- Eine pure Kommandozeilenversion des AES-Tools (auch f�r weitere
  Betriebssysteme).


6.2. Funktionalit�t: Analyse
     -----------------------
- W�nschenswert w�re, wenn insbesondere die Analyse und ihre
  Visualisierung weiter ausgebaut werden k�nnte.

- Zu allen Verschl�sselungsverfahren eine (gute) Analyse anbieten
  (zumindest f�r die klassischen Verfahren besser als Brute-Force).

- Aktuelle Hashangriffe darstellen (Erstellen von PS-Dokumenten nach
  Lucks oder von PDF-Dokumenten nach BSI mit gleichem Hashwert) und
  Aufzeigen der Anwendungsszenarien.

- Analyse neu implementieren f�r:
   * homophone Verschl�sselung
   * Permutationen/Transpositionen
   * Playfair-Verschl�sselung
      - Reine C-Sourcen (Gunnar-Andresson) liegen uns vor. 

- Analyse verbessern f�r:
   * monoalphabetische Substitution
      - explizite Anzeige von vertauschten Digrammen wie "ie"/"ei"
        und von Doppelzeichen wie "mm".
      - Ersetzte Buchstaben in der Dialogbox nicht nur gro�, sondern
        auch in roter Schrift anzeigen.
   * W�rterbucher f�r alle Angriffe benutzen, nicht nur f�r die
     Substitution.

- Massenmustersuche: Erweiterte hoch performante Mustersuche, die
  nach vorgegebenen normierten und regul�ren Mustern beliebiger L�nge
  sucht (z.B. um alle Patterns in einer Datei zu finden, die auch in 
  einer anderen (vorzugebenden) Datei vorkommen), oder die nach 
  unbekannten, aber mehrfach vorkommenden Mustern im Dokumenten sucht.
  K�nnte dann auch um Ersetzen erweitert werden.

- Suche nach Patterns m.H. von Normierungen (z.B. "einen" = 12313).
  C-Souren dazu liegen vor.

- Korrekturm�glichkeit einzelner Zeichen bei der Analyse von XOR,
  ADD, Vigen�re. Ausschluss unverschl�sseler Bereiche.

- Anzeigen des zweit-, dritt-, ... -besten Treffers bei der
  XOR/ADD-Analyse (dies kann zu einer k�rzeren Schl�ssell�nge
  f�hren).

- Autokorrelation: vor der �berlagerung noch Operationen auf den
  Bl�cken ausf�hren (XOR, ADD, ...). Macht das Sinn?

- Editieren der Homophonen-Schl�ssel (ben�tigt bei der Analyse
  der Homophonen Verschl�sselung).

- Gleitende Entropie: Automatische Anzeige der entsprechenden Stellen
  mit hoher Entropie.

- Vigen�re-Analyse noch weiter veranschaulichen:
  - bei den Keyl�ngen die Eingabe eines Bereiches statt eines Einzel-
    wertes erm�glichen (z.B. "2-9") und dann in der Folgemaske auch
    f�r jede L�nge den statistisch wahrscheinlichen Schl�ssel ausgeben.
    Evtl. die Top-10 wahrscheinlichsten Keys f�r eine bestimmte L�nge
    anzeigen.
    Per Klick auf einen der angezeigten Keys erh�lt man die jeweilige
    Entschl�sselung. Per Klick auf einen weiteren Button werden f�r
    alle Keys die Entschl�sselungen angeboten.
  - mit der Analyseoption "Basischiffre anzeigen" werden z.Zt. pro
    Spaltencaesar (d.h. bei einer ermittelten Schl�ssell�nge von
    n wird das Caesarverfahren f�r jeden Wert von i jeweils auf die
    Zeichenmenge m[i+k*n] mit 1<=i<=n und k>=0 angewandt) die
    Grafiken Korrelation und ASCII-Histogramm erstellt.
    Zus�tzlich k�nnte man noch den Text des jeweiligen Spalten-
    Caesars ausgeben.

- Timing Attack auf RSA / Vorteile Blinding.

- Angriff auf WEP-Protokoll.

- Angriff auf symmetrische Verschl�sselungsverfahren, bei denen die
  Parameter flexibel reduziert werden k�nnen.


6.3. Interne Schnittstellen / Editoren
     ---------------------------------
- Alle Anzeigemodule in einem konsistenten Klassenbaum
  zusammenfassen.

- Beliebige Textdateien in Bl�cken einstellbarer Breite darstellen:
  z.B. im Format  xxx xxx xxx  oder  xxxxx xxxxx xxxxx ...

- Die Sourcen so umstellen, dass die Ausgabe/Anzeige komplett von
  den Kryptomodulen getrennt ist (erleichtert Portierungen und
  Fehlersuche).

- Parametrisierung, wo immer das m�glich ist:
  Anbieten einer Option, um z.B. den Initialisierungsvektor,
  die Anzahl von Runden, die Schl�ssel- oder Wortl�nge oder
  das Padding zu setzen (z.B. f�r den RC5-Algorithmus - siehe
  RFC 2040).
  Diese Parameter m�ssen dann auch in das Format f�r den internen
  Schl�sselspeicher aufgenommen werden.

- Libraries:
   - Unterst�tzung weiterer Libraries (LiDIA, FLINT/C, 
     Wei Dai's Crypto++, ...).

- Vorhandene Einschr�nkungen in der N-Gramm-Analyse bzgl. Dateigr��e
  ausdehnen (evtl. mit Benutzerfeedback, wenn viel Zeit erforderlich)
  (vgl. 5.2.a oben).


6.4. User-Interface / Visualisierungen
     ---------------------------------
- In den Dialogen in CrypTool k�nnen Zahlen nicht immer in allen
  Darstellungsarten eingegeben werden (z.B. kann im Dialog 
  RSA-Kryptosystem die zu verschl�sselnde Nachricht als Text mit frei
  einzustellendem Alphabet und als Zahl mit 4 verschiedenen Basen) 
  eingegeben werden; die Primzahlen dagegen kann man "nur" als Zahl 
  im Zehnersystem bzw. als Ausdr�cke mit Zahlen im Zehnersystem 
  eingeben).
  N�tzlich w�re es, wenn man aus CrypTool heraus einen Taschenrechner
  als a-modales Fenster aufmachen k�nnte, der Terme mit Zahlen 
  beliebiger Basis als Eingabe nimmt und die Ausgabe in mehreren
  Feldern in verschiedenen Zahlensystemen parallel anzeigt. Von hier
  aus sollte man dann die Zahlen per Knopfdruck ins Clipboard bringen
  k�nnen oder per Maus in die Eingabefelder der CrypTool-Dialogboxen
  ziehen k�nnen.

- F�r den Benutzer konfigurierbar einstellbar machen, ob neue Fenster
  wie bisher innerhalb des Hauptfensters erscheinen oder als "freie"
  (modale oder a-modale) Fenster daneben stehen.
  Einzelne Dialogboxen (z.B. N-Gramm-Analyse, Manuelle Analyse,
  Hybriddemo) als a-modale Fenster erzeugen, so dass man beliebig
  zwischen Hauptfenster und Auswertungsfenster springen kann
  (aufw�ndigere Steuerung, Erlauben oder Abfangen von Mehrfachauf-
  rufen derselben Dialogbox, evtl. Update nach Fokus-Wechsel bzw.
  nach �nderung der Originaldaten im Hauptfenster, ...).

- AES-Tool:
  - Portierung nach Linux, ...
  - Einbinden des PKCS#5-Dialogs, um dem Benutzer seine gewohnte
    Eingabeweise zu bieten: Dabei zuf�llige Werte f�r Salz und 
    Iterationszahl voreinstellen und den User auffordern, sich
    den Hexwert zu merken oder ihn sicher aufzubewahren.
  Generell sind bei CrypTool die Schl�ssel ganz bewusst f�r die
  modernen Verschl�sselungsverfahren in Hex-Zeichen einzugeben. 
  Es ist Absicht, dass man in CrypTool zun�chst sieht, welche Art
  Schl�ssel die verschiedenen Algorithmen erwarten: bei den 
  klassischen Verfahren besteht der Schl�ssel aus dem zugrunde
  liegenden Alphabet, bei den modernen symmetrischen Verfahren sind
  es Bin�rdaten von 56 Bit bis 256 Bit L�nge.
  Andererseits sind Benutzer gewohnt, ihre Eingaben per ASCII-Zeichen
  zu machen. Da in einer produktiven Anwendung der Schl�ssel nicht
  aus ASCII-Zeichen bestehen sollte, ist es besser, wenn man ein
  ASCII-Passwort als Grundlage verwendet, um daraus mit einem 
  vern�nftigen Verfahren einen Schl�ssel herzuleiten. 
  In CrypTool k�nnte man die Anforderung "ASCII-Schl�sseleingabe" und
  "Zeigen, dass gute Hex-Keys zu verwenden sind", folgenderma�en 
  miteinander verbinden:
  In dem Hex-Schl�sseleingabe-Dialog sollte man per Button die 
  Funktion "Einzelverfahren \ Hashverfahren \ Schl�ssel aus Passwort
  generieren (PKCS#5)" aufrufen k�nnen. 
  Der Dialog ist dann mit der richtigen Schl�ssell�nge parametrisiert 
  und der generierte Schl�ssel wird in die Hex-Schl�sseleingabe 
  �bernommen. Damit dies auch f�r AES-256 funktioniert, m�sste noch
  die SHA-256-Hashfunktion eingebaut werden.

- F�r den Benutzer konfigurierbar einstellbar machen, wie gro� die
  Teile von Text- und Bin�rdateien sein k�nnen, die CrypTool laden
  kann.

- In der Anzeige f�r Grafiken eine Vergr��erungsfunktion einbauen
  und / oder die Koordinaten anzeigen, an denen sich die Maus
  befindet.

- Visualisierung:
   - Generell ist die Visualisierung der Abh�ngigkeiten und Abl�ufe
     bei Protokollen (nicht nur bei "einfachen" Algorithmen) eine
     sinnvolle Erweiterung.
   - Angriffe auf andere asymmetrische Verfahren sind in CrypTool
     bisher noch gar nicht behandelt. Um Diffie-Hellman, DSA oder
     EC-DSA anzugreifen, muss man "diskrete Logarithmen" berechnen.
     Auch dies k�nnte man nach dem Implementieren wieder 
     visualisieren.


6.5. Erweiterung um zahlentheoretische Funktionen
     --------------------------------------------
- Dialoge in CrypTool implementieren, so dass man CrypTool als Frontend
  f�r zahlentheoretische Funktionen und Werte nutzen kann.


6.6. Portierung nach Linux, Java und VS2005/WPF
     ------------------------------------------
- Portierung nach Linux mit Hilfe von GCC 4.x und Qt 4.x:
   - Die Libs von Secude, Miracl, NTL, OpenSSL und GMP stehen zur
     Verf�gung.
   - Trennung der Gesamtaufgabe in sinnvolle Teile:
       - Oberfl�che: hier liegt die Hauptarbeit.
       - Funktionalit�t, implementiert in purem C/C++: ok
       - Online-Hilfe in HTML: ok.

- Komplett neu designtes CrypTool in Java (JCrypTool):
   - Ein gr��eres Teilprojekt, das CrypTool nach Java portieren soll
   - Eine Secude-Lib und Bouncy-Castle stehen zur Verf�gung.
   - Nutzung von Eclipse, SWT (und Jigloo) zur Entwicklung.
   - Plug-in basierte Architektur.
   - Weitere Entwickler f�r dieses Teilprojekt sind willkommen
     (Die bisher aktiven Entwickler nutzen ein Wiki zur Kommunikation
     und Subversion zur Source-Verwaltung).

- Portierung auf Windows Vista mit Visual Studio 2005 und .NET.
  Nutzung der neuen GUI-API Windows Presentation Foundation (WPF)
  zur Gestaltung von multimedialen Oberfl�chen.
   - Nutzen des .NET-Frameworks (kein MFC mehr)
   - Nutzen des VS2005 (nicht mehr VS2003 und nicht mehr VC++6.0),
     sofern sich mit der kostenlosen VS2005-Express-Edition f�r
     C++ auch das gesamte Projekt bearbeiten l�sst.



6.7. Sinnvolle Aufgaben f�r jemand, der neu anf�ngt mitzuentwickeln
     --------------------------------------------------------------
- Einbau des RC5-Algorithmus wie oben beschrieben, um zu sehen,
  an welchen Stellen �berall die Sourcen daf�r zu erg�nzen sind
  (Funktion selbst, Optionen, Men�s + Statuszeileninfo, Online-Hilfe).

- Alle m�glichen Arten von Transpositionen und Superpositionen
  in einem ansprechenden Dialog anbieten.

- Pattern-Matching-Dialoge.

- Testbett mit Beispielen und L�sungen erzeugen, damit man das
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
1.3.02    Viele neue Funktionen gegen�ber 1.3.00.
1.3.03    Viele kleine Bugfixes und Verbesserungen der Dokumentation.
1.3.04    Etliche neue Funktionalit�t, einige kleine Bugfixes (Absturz
          bei Playfair-, N-Gramm-Analyse, RSA), und Verbesserung und 
          Erweiterung der Dokumentation (Online-Hilfe, Skript).
1.3.05    Kleine Bugfixes.
1.4.00-Beta10  Dez. 2005  Erste �ffentliche Beta von Version 1.4.00.
1.4.00-Beta12  M�rz 2006  Zweite �ffentliche Beta von Version 1.4.00.
1.4.00    Viele neue Funktionen gegen�ber 1.3.05.



8. Feedback bei Fehlern
   --------------------
Sollten Sie Probleme haben oder Fehler finden, wenden Sie sich
bitte mit einer Beschreibung des Problems per e-mail an
- joerg-cornelius.schneider@db.com   oder
- esslinger@fb5.uni-siegen.de        oder
- an die Mailingliste: cryptool-list@sec.informatik.tu-darmstadt.de

F�r Anregungen jeglicher Art bez�glich CrypTool sind wir immer
dankbar und helfen Ihnen gern, wenn es unsere Zeit erlaubt.

Auch w�rden wir uns freuen, wenn Sie uns mitteilen, wie und wo Sie
CrypTool einsetzen.



9. Kontaktadressen
   ---------------
- joerg-cornelius.schneider@db.com
- esslinger@fb5.uni-siegen.de
- henrik.koy@db.com
- cryptool-list@sec.informatik.tu-darmstadt.de



10. Verweise / Auszeichnungen
    -------------------------

10.1. Artikel �ber CrypTool
      ---------------------
10.1.1. c't 14/2001
        -----------
In diesem renommierten und auflagenstarken deutsch-sprachigen
Computermagazin wurde im Juli 2001 ein 5-seitiger Artikel zu
CrypTool ver�ffentlicht (S. 204-208).

10.1.2. DuD Oktober 2002
        ----------------
In der deutsch-sprachigen Fachzeitschrift "DuD Datenschutz und
Datensicherheit", Ausgabe 10/2002 erschien unter dem Titel
"CrypTool - spielerischer Einstieg in klassische und moderne
Kryptographie. Neue Version - fundierte Awareness in Deutsch
und Englisch" ein 4-seitiger Artikel �ber CrypTool.

10.1.3. KES 2/2003 (Mai 2003)
        ---------------------
In der deutsch-sprachigen Fachzeitschrift "KES - Zeitschrift f�r
Informations-Sicherheit", Ausgabe 2/2003 erschien unter dem Titel
"(Ver)Schl�sselerlebnisse - CrypTool unterst�tzt Verst�ndnis f�r
die Grundlagen der Internetsicherheit" ein 6-seitiger Artikel
�ber CrypTool.
Diesen Artikel finden Sie im HTML-Format auch auf der KES-Homepage
http://www.kes.info/index.html per Suchbegriff "CrypTool" unter
"Artikel aus der Maiausgabe 2003": "VerSchl�sselerlebnisse: CrypTool
unterst�tzt Verst�ndnis f�r die Grundlagen der Internetsicherheit" oder
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
mit CrypTool die Aufgabe mit wenigen Mausklicks l�sen.

10.2.2. BSI B�rger-CD "Ins Internet - mit Sicherheit"
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
   21.09.2005 unter der �berschrift "eLearning Program for Cryptology":
   http://www.professionalsecuritytesters.org/modules.php?name=Forums&
   file=viewtopic&t=34

   Ein �hnliches Post gab es am 22.09.2005 auf der "CISSP, SSCP, CISM, 
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
  - Franz�sisch:
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

Vollst�ndig mit Source-Code verf�gbar sind:

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
  Griffon ist ein GTK+ GUI Kryptoanalyse-Paket f�r "pre-digital 
  Ciphers". Es enth�lt die folgenden klassischen Verschl�sselungs-
  verfahren: monoalphabetische Transposition, Substitution und Playfair.
  Das Tool liegt nur in englischer Sprache vor.
  Die aktuelle Version 1.0 wurde im November 2000 freigegeben.

- http://www.kryptosproject.org/
  Kryptos ist Open Source-Projekt der George Mason University.
  Krytos ist eine Kryptographie-Lernsoftware mit einer statischen
  Oberfl�che, aber vielen modernen Algorithmen. 
  Kryptos hat keine Kryptoanalyse-Funktionen.
  Die aktuelle Version Kryptos 2.0 gibt es seit April 2005.

- http://cryptostudio.sourceforge.net/
  CryptoStudio von Prof. Marco Russo
  Die aktuelle Version 1.0 gibt es seit Juni 2005. Sie ist in Englisch
  und Italienisch verf�gbar.
  CryptoStudio ist eine GUI (angeglichen an das Aussehen von Microsofts
  Visual Studio), die Funktionen aus der Open-Source Krypto-Bibliothek
  OpenSSL und seinen Kommandozeilentools nutzt. Daher hei�t es auf der
  CryptoStudio-Webseite auch: "Many of the CryptoStudio functionalities
  are a mere GUI wrapper of OpenSSL tools, intended to make those tools
  available also to uninitiated users". Man findet darin auch
  M�glichkeiten zur Datei-Verschl�sselung oder zum Basis-S/MIME-Mail-
  Handling, aber keine Kryptoanalyse.


Die einzigen weiteren uns bekannten brauchbaren Programme, die
Kryptographie und Kryptoanalyse (unter einer graphischen
Oberfl�che) verbinden, f�r die aber kein Source-Code freigegeben
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
  theoretischer Funktionen und Funktionen zur Ver- und Entschl�sselung;
  keine Funktionen zur Kryptoanalyse; Software zu seinem Buch;
  wahrscheinlich aus dem Jahre 2001)
  http://faculty.goucher.edu/blewand/cryptomath/companion_software.htm

- John Trafton's studentisches Cryptography-Projekt in Java
  (einzelne statistische Funktionen und klassische Verschl�sselungs-
  verfahren; verf�gbar seit Dezember 2002)
  http://phoenix.goucher.edu/~jtrafton/Crypto

- Wilhelm M. Plotz' Java-Anwendung CipherClerk
  (Ver- und Entschl�sselung mit vielen klassischen Verfahren;
  letzter Update 2003)
  http://members.aon.at/cipherclerk/

- CryptoBench - GUI um Wei Dai's Crypto++ Bibliothek
  Kompakte und �bersichtliche GUI zur Nutzung der Kryptofunktionen aus 
  Wei Dai's Crypto++ Bibliothek (keine Kryptoanalyse).
  Die aktuelle Version 1.0.1 gibt es seit 2004.
  Wei Dai's Crypto++ Bibliothek ist Open Source, die GUI der 
  CryptoBench ist Freeware aber kein Open Source.
  http://www.addario.org/cryptobench/


Falls uns hier etwas entgangen ist, w�rden wir uns �ber eine Nachricht
freuen - wir vervollst�ndigen oder korrigieren diese Liste gerne.

Au�erdem wollen wir hier ausdr�cklich das Angebot machen, die
Anstrengungen f�r diese einzelnen Programme in ein einziges
Programm zu integrieren. Wir freuen uns �ber jede Kooperation!!


10.4. Auszeichnungen
      --------------
Generell ist es f�r uns die gr��te Auszeichnung, wenn CrypTool
eingesetzt wird, und dabei in Schule, Lehre und Training Nutzen
stiftet. �ber die vielen positiven R�ckmeldungen freuen wir uns
nat�rlich sehr.

CrypTool erhielt u.a. folgende explizite Auszeichnungen (s. Webseite):

- TeleTrusT-F�rderpreis 2004
  Der TeleTrusT-F�rderpreis wurde f�r die Vermittlung von Wissen und 
  die F�rderung der Akzeptanz von kryptographischen Verfahren auf der 
  ISSE-Konferenz verliehen.

- European Information Security Award 2004
  Das CrypTool-Projekt war Finalist beim European Information Security 
  Award (EISA 2004) in der Kategorie "Education and Training", 
  verliehen auf der RSA-Konferenz Europe.

- IT-Sicherheitspreis NRW 2004
  Der IT-Sicherheitspreis NRW in der Kategorie Bildung (eLearning / 
  Wissensvermittlung Kryptographie) ging an das vom Institut f�r 
  Wirtschaftsinformatik Siegen vorangetriebene CrypTool-Projekt.




11. Anhang
    ------

11.1. CrypTool unter Linux mit Wine
11.1.1. .... CrypTool installieren
11.1.2. .... Wine-Konfiguration
11.1.3. .... CrypTool ausf�hren


11.1. CrypTool unter Linux mit Wine
      -----------------------------
Diese Hinweise basieren auf Tests mit Wine 0.9.9.

Es wird nicht empfohlen, CrypTool unter Wine zu nutzen, da viele
Dinge dort nur teilweise richtig funktionieren. Eine vollst�ndige
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

