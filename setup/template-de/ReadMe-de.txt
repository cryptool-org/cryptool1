==================================================================
    CrypTool, Version 1.4.10 für Win32, April 2007
    (c) Contributors
        Dazu gehören z.B.
        Deutsche Bank AG, Frankfurt am Main
        Universität Siegen und Darmstadt
        1998-2007
    www.cryptool.de
    Bernhard Esslinger
    $Id$
==================================================================

 1. .... Kurzbeschreibung des CrypTool-Paketes
 1.1. .... Wie Sie am besten starten - Der Einstieg in CrypTool
 1.2. .... Was beinhaltet die Distribution
 1.3. .... Danke
 1.4. .... Maintainer und Hosting
 2. .... Was bietet CrypTool im Detail
 2.1. .... Was können Sie mit CrypTool machen?
 2.2. .... Neuerungen in Version 1.4.10
 3. .... Mögliche Punkte für eine Weiterentwicklung -- Ideen, Anfragen
 3.1. .... Funktionalität: Algorithmen / Verfahren
 3.2. .... Funktionalität: Analyse
 3.3. .... Interne Schnittstellen / Editoren
 3.4. .... User-Interface / Visualisierungen
 3.5. .... Portierung nach Linux, Java und VS2005/WPF
 3.6. .... Sinnvolle Aufgaben für jemand, der neu anfängt mitzuentwickeln
 4. .... Beschränkungen und Voraussetzungen
 4.1. .... Anwendungsbereich dieser Lern-, Trainings- und Awareness-Software
 4.2. .... Win32-Umgebung und Roadmap
 4.3. .... Interaktive Online-Hilfe unter Windows XP
 4.4. .... Unterstützung verschiedener Sprachen
 4.5. .... Einschränkungen / Features
 4.6. .... Zertifikate, die mit älteren CrypTool-Versionen erzeugt wurden
 5. .... Installation / Deinstallation / Betrieb
 5.1. .... Installation und Nutzung von Schlüsseln aus vorherigen Versionen
 5.2. .... Installation in Mehrbenutzersystemen
 5.5. .... Deinstallation von CrypTool
 5.4. .... Betrieb in Mehrbenutzersystemen
 6. .... Liste der Dateien in der Auslieferung
 6.1. .... Überprüfen der Integrität der heruntergeladenen Dateien
 7. .... Kurze Historie der freigegebenen Hauptversionen
 8. .... Feedback
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
analysieren. Schon in der Antike wurden solche Verfahren zur Geheim-
haltung von Nachrichten entwickelt. Heutige Verfahren basieren auf
moderner Mathematik und erlauben neben der Verschlüsselung auch die
Prüfung der Integrität, die Erstellung von Signaturen, sichere
Authentisierung und Vieles mehr. CrypTool unterstützt sowohl die
Ausführung als auch die Analyse solcher Verfahren.

CrypTool wird seit 1998 entwickelt. Im Moment arbeiten über 30 Personen
weltweit daran.

Zu jedem Programmteil gibt es reichhaltige Online-Hilfe, die auch
ohne tiefes Kryptowissen verstanden werden kann.

CrypTool ist komplett in Deutsch und Englisch vorhanden.
Die Polnische Version hat die gleiche Funktionalität [übersetzt ist
im Moment aber nur das Programm selbst, also die Oberfläche (Menüs,
Dialoge, ...). Die der polnischen Version beigelegte Dokumentation
ist noch in Englisch].

Vorausgesetzt wird, dass der Benutzer mit Anwendungen in einer
Windows-Umgebung umgehen kann.

Die aktuelle Release-Version von CrypTool und die Sourcen dazu
finden Sie unter den Internet-Adressen (keine Registrierung):
                http://www.CrypTool.de
                http://www.CrypTool.com
                http://www.CrypTool.org
                http://www.CrypTool.pl

Seit Mitte 2006 werden rund 3000 CrypTool-Pakete pro Monat herunter
geladen -- mit wachsender Tendenz (davon entfallen etwas über 1/3
auf die englische Version).

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
Kontakte: Siehe Kapitel 9 unten.


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

Einen schnellen Einstieg in die Kryptographie mittels CrypTool
finden Sie, wenn Sie einige Szenarien (Tutorials) der Online-Hilfe
durchspielen (die Szenarien stehen im Inhaltsverzeichnis der
Online-Hilfe unter "Beginn der Arbeit mit CrypTool").

Die Funktionen von CrypTool können Sie am einfachsten ausprobieren
mit der standardmäßig geöffneten Datei "Startbeispiel-de.txt".
Sie können aber auch eine andere unverschlüsselte Datei aus dem 
Unterverzeichnis "examples" oder irgendeine andere Datei auf der 
CrypTool-Arbeitsfläche öffnen.

Wenn Ihnen ein Menüpunkt nichts sagt oder Sie in einem Dialogfenster
nicht recht weiter wissen, sollten Sie mittels der F1-Taste ausreichend
Hilfe finden (wenn nicht, geben Sie uns bitte Feedback).

Eine 1-seitige Übersicht über alle Menüs in CrypTool (Menübaum)
finden Sie im beigelegten PDF-Skript (siehe Anhang A1).

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
  - der Industrie-bewährten Secude-Bibliothek (http://www.secude.com/),
  - der Miracl-Bibliothek von Shamus Software (http://indigo.ie/~mscott/),
  - der OpenSSL-Bibliothek (http://www.openssl.org/),
  - der NTL-Zahlentheorie-Bibliothek von Victor Shoup
    (http://www.shoup.net/ntl/),
  - der GMP-Bibliothek für beliebig genaue Arithmetik
    (http://www.swox.com/gmp/) und
  - der cv act library der cv cryptovision Gmbh (www.cryptovision.com).
 
  Die aktuell benutzten Versionen der inkludierten Bibliotheken finden
  Sie in der Dialogbox "Über CrypTool" (siehe Hilfe-Menü).

  Somit ist CrypTool auch eine hervorragende Referenzimplementierung.

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
Die folgenden Programme können aus CrypTool heraus, aber auch stand-alone
aufgerufen werden:

a) Das Programm AES-Tool v 2.4 (entstanden im CrypTool-Projekt)
   Zum Erstellen selbst-entpackender Executables ist in CrypTool ein
   Programm integriert, das auch eigenständig benutzt werden kann.
   Darin wird aus einem Passwort ein Session-Key erzeugt, mit dem
   ein beliebiger Dateiinhalt AES-verschlüsselt wird.
   Dieses Verschlüsselungstool kann sowohl als Fensteranwendung als
   auch von Kommandozeile (z.B. aus einer Batchdatei) aufgerufen werden.
   Dateien können bis zu einer Größe von 4 GB verschlüsselt werden.
   Bei der Installation wird diesem Programm die Dateiendung "AES"
   zugeordnet.

b) Das Lernspiel "Der Zahlenhai" v 1.1 (entstanden im CrypTool-Projekt)
   Dieses Lernspiel für Schüler bringt diesen den Umgang mit
   Teilern und Primfaktoren näher.

c) Das Animationsprogramm ANIMAL (siehe http://www.animal.ahrgr.de)
   Mit diesem an der TU Darmstadt von Dr. Rößling gepflegten Programm
   kann man die Einzelschritte von Algorithmen oder die Komponenten von
   Datenstrukturen beliebig genau modellieren, diese manuell vor und 
   zurück abspielen oder automatisch ablaufen lassen. Damit kann man
   auch dynamisch Source Code-Zeilen visualisieren.
   Das Animal-System erlaubt die Erstellung von Animationen mithilfe
   einer GUI, einer Skriptsprache sowie einer Java-API.
   Weitere Beispiele finden sich im ANIMAL-Repository (Datenbank):
   http://www.animal.ahrgr.de/animations.php3?tool=Animal&lang=de

d) Die Flash-Anwendungen "Rijndael" (visualisiert das Verschlüsselungs-
   verfahren AES) und "Enigma" (visualisiert das 2.-Weltkriegs Krypto-
   Gerät Enigma).

e) Die Authorware-Anwendung "ZT" (Zahlentheorie) führt in die elementare
   Zahlentheorie ein und visualisiert viele der Verfahren und Konzepte,
   die Grundlage der modernen Public-Key-Kryptographie sind.
   Wo nötig zeigt sie auch die entsprechenden mathematischen Formeln.
   Dabei können diese mathematischen Verfahren dynamisch mit eigenen
   kleinen Zahlenbeispielen ausprobiert werden.
   Dazu gehört auch das Programm bc.exe der Free Software Foundation,
   mit dem man auf der Kommandozeile beliebig genau rechnen kann.


(4) Geschichten mit Bezug zu Zahlentheorie und Kryptographie
------------------------------------------------------------
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
Zu CrypTool haben sehr viele verschiedene Personen beigetragen --
insbesondere auch in ihrer Freizeit (einige sind namentlich in der
Dialogbox aufgeführt, die man erhält, wenn man in der Dialogbox 
"Über CrypTool" einen Doppelklick ausführt). Herzlichen Dank.

Ebenfalls beigetragen haben als Sponsoren z.B. die Deutsche Bank AG
und die Technische Universität Darmstadt.

Ohne vollständig sein zu wollen, möchten wir hier einige Mitwirkende
erwähnen (und evtl. besondere Bedingungen aufführen):

- Dr. Carsten Elsner erlaubte uns, seine beiden Geschichten als 
  PDF-Datei beizulegen.
  Der Verfasser, als alleiniger Inhaber aller Rechte an den Werken,
  räumt dem CrypTool-Maintainer das ausschließliche Vervielfälti-
  gungs- und Verbreitungsrecht ein. Die Geschichten dürfen nur zusammen
  mit dem CrypTool-Paket verbreitet werden.
  Die Geschichte "Der Dialog der Schwestern" wurde zuerst in dem 
  Computermagazin c't 25/1999 veröffentlicht. Während in der c't
  eine etwas gekürzte Fassung veröffentlicht wurde, liegt hier die
  Originalfassung bei.

- Dr. Guido Rößling erlaubte uns seine Freeware ANIMAL, eine Java-basierte
  Animationssoftware mit auszuliefern.

- Ebenfalls integrieren durften wir erweiterte Versionen von:
  - der Flash-Animation zu AES von Enrique Zabala,
  - der Flash-Animation zur Enigma von Dr. Frank Spieß,
  - dem Zahlentheorie-Lernprogramm von Martin Ramberger.
  Die über eine Verwendung außerhalb des freien CrypTool-Contextes
  hinausgehenden Rechte verbleiben beim jeweiligen Autor.

- Die Firmen (siehe Kapitel 1.2)
  - Secude IT Security GmbH, 
  - Shamus Software Ltd und
  - cv cryptovision Gmbh
  gestatteten uns großzügigerweise, ihre Krypto-Bibliotheken zu nutzen.
  Diese mit CrypTool verteilten Bibliotheken dürfen nicht in einem
  Kontext außerhalb CrypTool benutzt werden, ohne vorher die erwähnten
  Firmen zu kontaktieren und nach ihren aktuellen Lizenzbedingungen zu
  fragen.

Ebenso herzlich danken möchten wir den Open-Source-Entwicklern, die uns
mit ihrem Code Anregungen gaben oder deren Code wir nutzen dürfen
(z.B. die Bibliotheken OpenSSL, GMP und NTL, die Installations-Software
NSIS, die Texteditorsoftware Scintilla).

Bedanken möchte ich mich auch bei Herrn Bartosz Sawicki von der
Universität Warschau, der mit seinem Team die gesamte polnische
Version erstellte.


1.4. Maintainer und Hosting
     ----------------------
Seit Oktober 2002 hostet der Lehrstuhl Sicherheit in der Informations-
technik, Fachbereich Informatik unter Frau Prof. Dr. Claudia Eckert
an der TU Darmstadt die deutsche und englische Webseite von CrypTool
und das Subversion-Repository-System für die Programm-Sourcen.

Die CrypTool-Entwicklergruppe unter Bernhard Esslinger fungiert auch
weiterhin als Maintainer, d.h. sie kümmert sich um die Pflege des
Codes, die Veröffentlichung als Open Source und Freeware, und um
die Koordination der Weiterentwicklung. Die nächsten Schritte der
Roadmap werden auch auf der Webseite veröffentlicht.

Die Homepage von CrypTool ist www.cryptool.de.

Wir freuen uns über jeden weiteren Entwickler, der sich an der
Weiterentwicklung von CrypTool beteiligt.
Ideen zur Weiterentwicklung finden Sie in Kapitel 3.

Ebenfalls sehr willkommen sind uns Ideen und Infos, wie CrypTool in
Lehre, Schule und Ausbildung eingesetzt wurde, damit wir dazu 
beitragen können, diese Informationen auszutauschen.



2. Was bietet CrypTool im Detail
   -----------------------------

2.1. Was können Sie mit CrypTool machen
     ----------------------------------
Die generellen Eigenschaften und Funktionen von CrypTool sind:

- E-Learning-Programm rund um das Thema Kryptographie und Kryptoanalyse.

- Alles in einem Programmpaket und steuerbar unter einer Oberfläche.

- Alles in CrypTool ist in Deutsch und Englisch verfügbar.
  Das Programm selbst gibt es auch in Polnisch.

- Viele klassische Verschlüsselungsverfahren: Und dazu teilweise manuell
  unterstützte, teilweise automatische Analyse (Known-Plaintext-Angriff).

- Codierungen wie Base64 und UU-Encode.

- Nahezu alle modernen symmetrischen Verschlüsselungsverfahren: Und dazu
  jeweils die Brute-force-Analyse
  (Bei der Brute-force-Attacke auf symmetrische Algorithmen werden
   Jokerzeichen zugelassen und die erwartete Zeit wird ausgegeben. 
   Außerdem kann man die Breite für das hierbei genutzte
   Entropiefenster in den Analyseoptionen einstellen).

- Moderne (asymmetrische) Kryptoverfahren und Protokolle (Hash, RSA, ECC,
  Digitale Signatur, Hybrid-Verschlüsselung, PKCS#5, Shared Secret, ...)
  und teilweise Angriffe darauf (Geburtstagsangriff, Seitenkanalangriff, 
  Gitterbasenreduktion).

- Demo des RSA-Verfahrens (in verschiedenen Varianten) und einiger 
  zugehöriger Algorithmen der Zahlentheorie:
  - Primzahlen generieren und testen (incl. dem deterministischen
    AKS-Verfahren).
  - Zahlen (schrittweise) mit verschiedenen Verfahren faktorisieren
    (die verschiedenen Verfahren laufen in parallelen Threads).
  - Das RSA-Kryptosystem transparent durchführen:
     - RSA-Schlüssel erzeugen (auch mit selbst-gewählten Primzahlen).
     - Ver-/Entschlüsseln mit dem RSA-Verfahren.
     - RSA-Signaturen erzeugen und diese verifizieren.
     - das RSA-Verfahren angreifen.

- Drei auf Gitterreduktionsverfahren basierende Angriffe gegen das 
  RSA-Verfahren, die darauf beruhen, dass bestimmte Vorbedingungen 
  erfüllt sind:
  * ein Teil von einem der beiden Faktoren von N ist bekannt 
    ("Faktorisieren mit teilweise bekanntem p"),
  * ein Teil des Klartextes einer abgefangenen verschlüsselten 
    Nachricht ist bekannt und e ist klein ("Angriff auf stereotype
    Nachrichten"),
  * wenn d im Vergleich zu N zu klein gewählt ist, kann man N 
    faktorisieren ("Angriff auf kleine geheime Exponenten (nach
    Blömer/May)").
  Die Diplomarbeit von Herrn Mathias Schneider, innerhalb von der
  diese Verfahren implementiert wurden, kann auf Anfrage zugemailt
  werden (sie liegt nur in Deutsch vor).

- Visualisierungen/Animationen/Demonstrationen
  - Demo der Sensitivität von Hashverfahren.
  - Visualisierung mit Flussdiagrammen (z.B. beim Diffie-Hellman
    Schlüsselaustausch-Verfahren oder bei der Challenge-Response-Demo),
  - Animationen 
     - mit ANIMAL (z.B. bei DES) oder
     - mit Flash (AES, Enigma).
     - mit Java/SWT: Punkteaddition auf Elliptischen Kurven (sowohl auf
                     diskreten wie auf reelen Kurven).

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
  wie sie in der Realität vorkam, kann der Angreifer den Session-Key 
  durch Protokoll-gerechte Anfragen an den Server hoch effizient 
  berechnen.

- Hashwerte berechnen und ihre Sensitivität demonstrieren.

- Implementierung von MAC-Verfahren (Kombination von Hashes und 
  symmetrischen Verfahren zur Authentisierung von Nachrichten). 
  Hashverfahren wurden bisher schon von den in CrypTool implementierten
  Konzepten PKCS#5 und digitale Signaturen verwendet.

- Das Shared-Secret-Verfahren nach Shamir wurde mit vielen Optionen
  implementiert.

- Zufallszahlen:
  - Pseudozufallszahlengeneratoren und statistische Analysen für 
    Zufallsdaten (z.B. FIPS-140-1).
  - Der Secude-Zufallszahlengenerator bietet die Möglichkeit, Entropie
    über Mausbewegung und Tastatureingaben zu sammeln.
    Dies ist die Standardeinstellung für den ersten Aufruf des
    kryptographischen Zufallsgenerators, damit deutlich wird, dass man
    für gute Zufallszahlen einen zufälligen Input braucht.
  - Eine 3-D-Visualisierung von großen Mengen an Zufallszahlen mit Hilfe
    der Volume-Rendering-Engine aus OpenQVis 
    (http://openqvis.sourceforge.net/).

- PKCS#12-Export und -Import von RSA- und DSA-PSEs und damit
  von den darin gespeicherten Schlüsseln.

- Die modernen Verfahren wurden gemäß den internationalen Standards
  implementiert (Referenzimplementierung).

- Die letzte Einstellung zu einem Verfahren (Parameter, Schlüssel oder
  Alphabet) wird Programm-intern aufbewahrt. Der Schlüssel kann pro 
  Verfahren über das Schlüssel-einfügen-Symbol auch wieder abgerufen 
  werden, was die Bedienung beim Testen und Probieren stark erleichtert.

- Zu jedem Fenster kann nun ein Dialog angezeigt werden, der alle
  wesentlichen Eigenschaften dieses Dokuments anzeigt.

- Alle persistenten Daten werden im Nutzer-lokalen Teil der Registry
  abgelegt (keine INI-Datei mehr), wodurch man CrypTool ohne 
  Administratorrechte ausführen kann und verschiedene Benutzer
  am gleichen PC jeweils verschiedene Einstellungen haben können.

- Die gleiche Menüstruktur ist konstant sichtbar: Einträge, die für
  bestimmte Dokumenttypen nicht ausführbar sind, werden ausgegraut,
  aber nicht mehr ganz entfernt.

- Das eigenständige Programm AES-Tool kann selbstentpackende
  Programme erzeugen. Damit kann man eine beliebige Datei ( < 4 GB)
  Passwort-geschützt mit AES verschlüsseln (durch Eingabe eines 
  Hexadezimal-Schlüssels).
  Voller Funktionsumfang auch bei einem Aufruf von der Kommandozeile.

- Das eigenständige Lernprogramm für die Mathematik hinter der
  asymmetrischen Kryptographie beschreibt ausführlich und interaktiv
  die elementare Zahlentheorie.

- Drei auf dem Chinesischen Restesatz beruhende Anwendungen:
  * Lösung von Systemen linearer modularer Kongruenzen am Beispiel 
    einer Planetenkonstellation im Sonnensystem.
  * Veranschaulichung des Rechnens (Addieren, Subtrahieren, 
    Multiplizieren) mit modularen Resten statt mit den (größeren)
    eigentlichen Zahlen.
  * Veranschaulichen des Shared Secret-Verfahrens (entspricht der 
    Analogie, dass man zum Öffnen eines Tresors z.B. drei beliebige 
    von 5 Schlüsselinhabern braucht).

- Das Lern-Spiels "Der Zahlenhai" bringt Schülern den Umgang mit
  Teilern und Primfaktoren näher.

- Webseite mit den Hashwerten aller herunterladbaren CrypTool-Dateien:
  Damit kann man die Integrität der Dateien aus dem CrypTool-Paket, die
  sich auf dem Computer befinden, überprüfen.

- Umfangreiche Dokumentation (Onlinehilfe, Skript).
  Die Online-Hilfe ist im HTML-Format.
  Sie enthält Erläuterungen zur Bedienung und zu allen Verfahren, einen
  Überblick über die Historie der Kryptographie und die Einordnung in
  weitere Sachgebiete sowie Informationen für eine sinnvolle Verwendung
  von Kryptographie.

- Weltweite Nutzung in Schulen, Universitäten, Behörden und Firmen.

- Die Sourcen des Releases stehen auf der CrypTool-Webseite zum Download.
  Auf die aktuellen Entwicklersourcen im Subversion-Repository kann
  man lesend per
  svn checkout https://file.sec-tud.de/svn/CrypTool/trunk
      --username anonymous --password anonymous
  zugreifen.


Eine gute Übersicht, was CrypTool bietet, finden Sie auch
- in der beigelegten Powerpoint-Präsentation
   (Titel: "Kryptographie mit CrypTool"),
- auf der CrypTool-Webseite
   (insbesondere über den Eintrag "CT-Einstiegsseite" im linken Frame) oder
- in der Onlinehilfe (siehe "Startseite").



2.2. Neuerungen in Version 1.4.10
   ----------------------------
Kapitel 2.2 listet die Erweiterungen und Bugfixes auf, die in
CrypTool 1.4.10 seit CrypTool 1.4.00 hinzugefügt wurden.

a) Entwickler-relevante Änderungen (eher programm-technisch):

- Details zum Compilieren, Linken und zur einheitlichen Entwicklung
  finden sich in den Sourcen in der Datei "readme-source".

- Die Sourcen wurden mit der Microsoft Entwicklungsumgebung
  Visual Studio 2003 (VC++ v7.1) compiliert.

  Es gibt schon einen Sourcezweig im Subversion-System, der sich
  auch mit VS2005 (VC++ v8.0) übersetzen lässt. Dies wird später
  offiziell unterstützt.

- Die Editoren für Text- und Binärdaten sind Open-Source:
  * Hex-Editor / Hex-Control / HexView:
    Link: http://www.codeguru.com/Cpp/controls/controls/article.php/c5287
    Erweitert: - Einfügen und Kopieren unterscheidet zwischen ASCII-
                 und Hex-Codierung (rechte und mittlere Spalte).
                 - Beim Herauskopieren wird gefragt, ob der markierte
                   Text codiert oder als Hexzeichen ins Clipboard gelegt
                   werden soll.
                 - Beim Einfügen kommt eine Rückfrage, wenn im Clipboard
                   nur Hexzeichen (eine gerade Anzahl!) enthalten sind: ob
                   das als Hexdarstellung oder als eigentliche
                   ASCII-Zeichen interpretiert werden soll.
    Für Hex-Dateien ist derzeit keine Suche implementiert.
  * Text-Editor:
    Link: http://scintilla.sourceforge.net/ScintillaDownload.html
    Erweitert: - Man kann diejenigen Zeichen ausgrauen, die nicht zum
                 aktuellen Alphabet gehören.
               - Suchen und Ersetzen unterstützt nun reguläre Ausdrücke.
                   xxxxxxxxxxx

- Ab 1.4.10 wird NSIS als Installationstool verwendet
  (siehe http://nsis.sourceforge.net/Main_Page).



b) Änderungen in der Benutzer-Dokumentation:

- Online-Hilfe: verbessert, stark erweitert, Index neu strukturiert.

- Im Skript: Behebung kleinerer Fehler, kleinere Erweiterungen,
  etliche Aktualisierungen (z.B. Rekord in der Lösung einer konkreten
  Diskreten-Logarithmus-Problems), neues Kapitel über die Zukunft der
  Kryptographie vom Lehrstuhl Prof. Buchmann. xxxxxxxxxxx

- Aktualisierte und auf knapp 100 Seiten erweiterte Präsentation.


c) Funktionale Erweiterungen:

- Bugfixes:
  - Viele kleine Verbesserungen in den Masken (Benutzerführung),
    z.B. ist in allen Schlüsseleingabemasken der klassischen Verfahren nun
    ein Button zu den Textoptionen, so dass man das benutzte Alphabet
    einstellen kann. Diese Verknüpfung wurde auch in der Analysemaske
    zur Berechnung der N-Gramme eingeführt, die vorher auf ein fixes
    Alphabet ausgelegt war.
  - Hashwert einer Datei berechnen: Race-Condition beseitigt.
  - Solitaire für einen Spezialfall (war die Ausgabe-Karte ein Joker,
    wurde sie nicht ausgegeben) korrigiert.
  - Rijndael für Schlüssellängen > 128 Bit korrigiert.

- Das AES-Tool in der Version 2.4 prüft, dass der eingegebene Schlüssel
  nicht länger als 256 Bit ist. Außerdem kann man nun auch per Maus die
  zu verschlüsselnde Datei aus dem Windows-Explorer in das Eingabefeld
  ziehen.

- Die Schlüsseleingabemasken für klassische Verfahren enthalten
  nun einen Button, so dass man auch von hier aus direkt das Alphabet
  (Textoption) einstellen kann (wenn sinnvoll).

- Das Hill-Verschlüsselungsverfahren wurde um einige Varianten erweitert:
  - einstellbar sind nun die Matrixmultiplikation (von rechts oder links)
    und der Wert des ersten Alphabetbuchstabens.
  - Auch Eingabe von Zahlen statt nur Buchstaben in die Schlüsselmatrix.
  - Die Detail-Ausgabe zur Erläuterung des Verfahrens ist nun deutlich
    ausführlicher. Sie nimmt nun dynamisch die ersten Werte aus dem
    Klartext (statt mit einem festen String zu arbeiten).

- Zu den modernen symmetrischen Verschlüsselungsverfahren kamen hinzu
  die DES-Varianten DESX (Rivest), DESL und DESXL (Ruhr-Uni Bochum).

- Elliptische Kurven-Verfahren werden nun nach den Signaturen auch
  bei der Hybrid-Verschlüsselung (ECC-AES) eingesetzt.
  Außerdem gibt es eine Demonstration zur der Punkteaddition auf 
  Elliptischen Kurven (sowohl auf diskreten Kurven wie auf reellen).

- Das Lernprogramm/Lernspiel "Zahlenhai" wurde etwas erweitert.

- Hinzu kamen die Flash-Animationen zu AES und Enigma.

- Hinzu kam das Authorware-Lernprogramm, das die Verfahren der
  elementaren Zahlentheorie erläutert und visualisiert.



3. Mögliche Punkte für eine Weiterentwicklung -- Ideen, Anfragen
   -------------------------------------------------------------

3.1. Funktionalität: Algorithmen / Verfahren
     ---------------------------------------
- Weitere Algorithmen zu jedem Thema implementieren:
    * Codes:
       - T9
    * Verschlüsselung:
       - Klassische Verfahren: Fleißner-Schablone (incl. Analyse).
       - Symmetrische Verfahren:
           Camellia (RFC3713), RC5 und Gost (http://vipul.net/gost).
       - Public Key-Verfahren: McEliece, Rabin, NTRU.
       - Demonstration der Visuellen Kryptographie.
    * Hashverfahren:
       - SHA-256, SHA-384, SHA-512
         http://csrc.nist.gov/publications/fips/fips180-2/fips180-2.pdf
       - Tiger (http://www.cs.technion.ac.il/~biham/Reports/Tiger/)
    * Protokolle / Protokollschwächen:
       - Visualisierung von Man-in-the-Middle-Angriffe.
       - Blind Signatures.
       - Elektronische Wahlen.
       - Tripartite Schlüsselvereinbarung.

- Schnelle Auswahl der verschiedenen Verschlüsselungsverfahren
  über eine Dialogbox statt über die Menüs (Offenlegung aller
  Steuerparameter der Algorithmen) (analog CryptoBench).

- Kryptographisch starke elliptische Kurven erzeugen und damit
  Implementierung eines auf Elliptischen Kurven basierenden
  Kryptosystems. Dazu könnte man das Kryptosystem von Menezes
  und Vanstone nehmen, das 1993 von diesen Autoren vorgeschlagen
  wurde: A. Menezes and S. Vanstone,
         "Elliptic curve cryptosystems and their implementation",
         Journal of Cryptology, 6 (1993), Seite 209-224.

- Hillverfahren
   - Schlüsselmatrix transponieren.

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
  signieren. Damit wird klar, dass auch PGP nur mit Standard-Algorithmen
  arbeitet.

- CrypTool als Demonstrator für XML-Signaturen.

- Veranschaulichen der Passwortgüte und der Passwortqualität mit Hilfe
  eines Passwort-Quality-Meters.



3.2. Funktionalität: Analyse
     -----------------------
- Wünschenswert wäre, wenn insbesondere die Analyse in allen Formen und
  ihre Visualisierung weiter ausgebaut werden könnte.

- Zu allen Verschlüsselungsverfahren eine (gute) Analyse anbieten
  (zumindest für die klassischen Verfahren besser als Brute-Force).

- Angriff auf symmetrische Verschlüsselungsverfahren, bei denen die
  Parameter der Verschlüsselungsverfahren flexibel reduziert werden
  können.

- Differentielle Kryptoanalyse auf symmetrische Chiffren (DES, ...).

- Die Brute-force-Möglichkeiten erweitern: Nutzen von Wissen
  - um Teile des Klartextes
  - um Teile des Schlüssels

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

- Nutzung von Algorithmen aus dem Bereich KI (Künstliche Intelligenz) und
  GP/GA (Genetic Programming/Algorithms) zur Analyse (klassischer)
  Verschlüsselungsverfahren.

- Massenmustersuche: Erweiterte hoch performante Mustersuche, die
  nach vorgegebenen normierten und regulären Mustern beliebiger Länge
  sucht (z.B. um alle Patterns in einer Datei zu finden, die auch in 
  einer anderen (vorzugebenden) Datei vorkommen), oder die nach 
  unbekannten, aber mehrfach vorkommenden Mustern in Dokumenten sucht.
  Könnte dann auch um Ersetzen erweitert werden.

- Suche nach Patterns m.H. von Normierungen (z.B. "einen" = 12313).
  C-Souren dazu liegen vor.

- Korrekturmöglichkeit einzelner Zeichen bei der Analyse von XOR,
  ADD, Vigenère. Ausschluss unverschlüsselter Bereiche.

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
    Spalten-Caesar (d.h. bei einer ermittelten Schlüssellänge von
    n wird das Caesar-Verfahren für jeden Wert von i jeweils auf die
    Zeichenmenge m[i+k*n] mit 1<=i<=n und k>=0 angewandt) die
    Grafiken Korrelation und ASCII-Histogramm erstellt.
    Zusätzlich könnte man noch den Text des jeweiligen Spalten-
    Caesars ausgeben.

- Timing Attack auf RSA / Vorteile Blinding.

- Aktuelle Hashangriffe darstellen (Erstellen von PS-Dokumenten nach
  Lucks oder von PDF-Dokumenten nach BSI mit gleichem Hashwert) und
  Aufzeigen der Anwendungsszenarien.

- Angriff auf WEP-Protokoll.

- Weitere Angriffe auf konkrete Protokolle implementieren und/oder
  visualisieren, um zukünftige Konzepte zu verbessern.



3.3. Interne Schnittstellen / Editoren
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

- Langzahl- und Kryptobibliotheken:
   - Unterstützung weiterer Libraries (LiDIA, FLINT/C, 
     Wei Dai's Crypto++, ...).

- Vorhandene Einschränkungen in der N-Gramm-Analyse bzgl. Dateigröße
  ausdehnen (evtl. mit Benutzerfeedback und der Möglichkeit abzubrechen,
  wenn viel Zeit erforderlich).


3.4. User-Interface / Visualisierungen
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
   - Angriffe auf schwache RSA-Schlüssel sind in der Onlinehilfe
     beschrieben: Siehe Menü Hilfe \ Szenarien (Tutorials) \
     RSA-Kryptosystem (Demonstration), unter dem Abschnitt 
     "3. Angriff auf das RSA-Verfahren", wo erklärt wird, dass die
     Faktorisierung des Moduls das Verfahren knacken kann.
     Dies ist implementiert, aber nicht visualisiert.
   - Angriffe auf andere asymmetrische Verfahren sind in CrypTool
     bisher noch gar nicht behandelt. Um Diffie-Hellman, DSA oder
     EC-DSA anzugreifen, muss man "diskrete Logarithmen" berechnen.
     Auch dies könnte man nach dem Implementieren wieder 
     visualisieren.



3.5. Portierung nach Linux, Java und VS2005/WPF
     ------------------------------------------

- Wunschliste für eine Future Version (2.0):
  - Alle Sprachen in einem Programm, einem Setup.
  - Moderneres Layout.
  - Mehr Benutzerinteraktion, Actionhistorie.
  - Dynamischer Wechsel zwischen Kryptoprovidern und Sprachen.
  - Teil-Updates aus dem Internet.
  - Mehr Funktionen als Thread implementieren.
  - Einfacheres Erstellen von Kaskaden zusammengestellt aus den
    existierenden Elementen.
  - Anbieten eines Recorders für Benutzereingaben.


- Portierung nach Linux mit Hilfe von GCC 4.x und Qt 4.x:
   - Die Bibliotheken von Secude, Miracl, NTL, OpenSSL und GMP stehen
     zur Verfügung.
   - Trennung der Gesamtaufgabe in sinnvolle Teile:
       - Oberfläche: Hier liegt die Hauptarbeit.
       - Funktionalität, implementiert in purem C/C++: ok
       - Online-Hilfe in HTML: ok.
   - Im Moment gibt es nur erste Versuche.

- Komplett neu designtes CrypTool in Java (JCrypTool JCT):
   - Ein größeres Teilprojekt, das CrypTool nach Java portieren soll.
   - Eine Secude-Lib, Bouncy-Castle und FlexiProvider stehen zur
     Verfügung.
   - Nutzung von Eclipse, SWT (und Jigloo) zur Entwicklung.
   - Plug-in basierte Architektur.
   - Weitere Entwickler für dieses Teilprojekt sind SEHR willkommen.
   - Erste Konzepte und Sourcen existieren.
   - Die hier bisher aktiven Entwickler nutzen SourceForge mit Subversion
     zur Source-Verwaltung: http://jcryptool.sourceforge.net/ .

- Portierung auf Windows Vista mit Visual Studio 2005 und .NET.
  Nutzung der neuen GUI-API Windows Presentation Foundation (WPF)
  zur Gestaltung von multimedialen Oberflächen.
   - Nutzen des .NET-Frameworks (kein MFC mehr)
   - Nutzen von VS2005 (nicht mehr VS2003),
     mit dem Ziel, dass das gesamte Projekt sich mit der kostenlosen
     VS2005-Express-Edition für C++/C# erstellen lässt.
   - Ein Prototyp ist schon verfügbar in einem extra Sourcezweig im
     CrypTool Subversion-Repository, auf den jedermann mit dem User
     "anonymous" lesenden Zugriff hat.
   - Weitere Entwickler und graphisch anspruchsvolle Designer sind
     in diesem neuen Projekt sehr herzlich willkommen.



3.6. Sinnvolle Aufgaben für jemand, der neu anfängt mitzuentwickeln
     --------------------------------------------------------------
- Einbau weiterer klassischer Verfahren wie z.B. Autokey, Nihilist
  oder Enigma (ohne Animation).

- Einbau des RC5-Algorithmus wie oben beschrieben, um zu sehen,
  an welchen Stellen überall die Sourcen dafür zu ergänzen sind
  (Funktion selbst, Optionen, Menüs + Statuszeileninfo, Online-Hilfe).

- Alle möglichen Arten von Transpositionen und Superpositionen
  in einem ansprechenden Dialog anbieten.

- Ausgabe der pro Verschlüsselungsverfahren gespeicherten Schlüssel
  in einer Liste.

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




4. Beschränkungen und Voraussetzungen
   ----------------------------------

4.1. Anwendungsbereich dieser Lern-, Trainings- und Awareness-Software
     -----------------------------------------------------------------
CrypTool dient vor allem Ausbildungs- und Awareness-Zwecken. Man soll
es ohne vorherige Konfiguration sofort benutzen können.

Das Entwicklungsziel von CrypTool war also nicht, dass damit produktiv
verschlüsselt wird oder dass damit eine CA (Certification Authority)
betrieben wird -- auch wenn die Funktionen korrekt in CrypTool 
implementiert sind.

Beispielsweise steht - im Unterschied zu produktiven CA-Applikationen -
das CA-Schlüsselpaar fest in der Software (Source und Binary) und es
ist geschützt mit einer ebenfalls bewusst sehr einfachen PIN für die
CA-PSE (Personal Security Environment).

Der Rootschlüssel der in CrypTool 1.4.10 eingebauten CA hat eine Länge
von 2048 Bit und ist 20 Jahre gültig (06.07.2006 - 06.07.2026).
Zertifikate, die mit dem alten Rootkey aus früheren CrypTool-Versionen
(1.3.05 und älter) ausgestellt wurden, können nicht in Version 1.4.10
importiert werden.

Beachten Sie also beim Umgang mit Zertifikaten, dass jedes CrypTool-
Programm eine Root-CA mit demselben Schlüsselpaar beinhaltet, mit 
der die im Programm erzeugten User-Zertifikate signiert werden. 
D.h. jeder (!), der CrypTool einsetzt, kann User-Zertifikate mit 
dieser eingebauten CA signieren.

Professionelle PKI-Software wie z.B. die OpenXPKI, Entrust, die
Secude-CA oder die Microsoft-CA managen zusätzlich den ganzen
Lebenszyklus von Zertifikaten, bieten CRL-Handling, sorgen für
eindeutige Seriennummern und nutzen definierte Registrierungsprozesse.

Die in CrypTool vorhandenen modernen Krypto-Verfahren sind entsprechend
den internationalen Standards implementiert und genauso "gut" wie in
kommerziellen Anwendungen.


4.2. Win32-Umgebung und Roadmap
     --------------------------
CrypTool erfordert eine Win32-Umgebung.

Einige Funktionen erfordern zusätzlich eine Java Runtime-Umgebung
(>= Version 1.4).

Die minimale Rechnerausstattung liegt bei 300 MHz CPU, 256 MByte RAM,
40 MByte Festplattenplatz (geringe Anforderungen).

CrypTool 1.4.10 unterstützt Windows 2000, Windows XP and Windows Vista.

Weder für die Installation noch für die Benutzung sind Administrator-
Rechte notwendig.

Persistente Daten werden nur im CrypTool-Verzeichnis, in das Standard-
Windows-Verzeichnis für temporäre Dateien (TEMP-Verzeichnis) und in
den benutzerspezifischen Bereich der Windows-Registry geschrieben
(Details siehe Kapitel 3) (Es gibt keine INI-Dateien mehr).

Anmerkung: Wo das TEMP-Verzeichnis von Windows liegt, kann man sehen,
wenn man in Windows-Explorer %TEMP% eingibt. Den Wert kann man unter
Windows XP auch ansehen und anpassen per "System --> Systemeigenschaften
--> Reiter Erweitert --> Umgebungsvariablen".

CrypTool funktioniert grundsätzlich auch unter FreeBSD/Linux mit
Wine (mit großen Abstrichen an Funktionalität und Stabilität).
Siehe Anhang 11.1.

Eine Portierung auf Linux oder Java und die Erstellung einer Version 2.0,
die Windows WPF nutzt, sind weitere Ziele (siehe Kapitel 3.5).


4.3. Interaktive Online-Hilfe unter Windows XP
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


4.4. Unterstützung verschiedener Sprachen
     ------------------------------------
Programm, Hilfesystem und Dokumentation sind mehrsprachig aus-
gelegt (zur Zeit komplett englisch und deutsch).

In der aktuellen polnischen Version sind im Moment das Programm inclusive
aller Masken und Menüs in Polnisch; Hilfesystem und Dokumentation sind
noch in Englisch (wird bis Ende 2007 geändert).

Für jede unterstützte Sprache gibt es derzeit ein eigenes Setup.


4.5. Einschränkungen / Features
     --------------------------
- Zur Demonstration des RSA-Kryptosystem und zur Faktorisierung von
  Zahlen greift CrypTool auf die Langzahlarithmetik der Bibliothek
  Miracl von Shamus Software Ltd. zu. Die Bitlänge der Zahlen wurde
  in der CrypTool-Anwendung auf 8192 beschränkt. 

- Von Binärdateien werden "nur" knapp die ersten 2 GB in den
  Hex-Editor geladen (< 0x7ffff000 = 2.147.479.552 Bytes).
 
  Textdateien können dagegen in unbeschränkter Größe vom Editor geladen
  werden (sofern die Rechnerressourcen reichen).

- Beim Lesen und Speichern von Textdateien wird der Zeilenumbruch immer
  als CR/NL (wie unter Windows üblich) dargestellt. Das bedeutet,
  dass Dokumente, die aus Unix kommen und deshalb den Zeilenumbruch nur
  mit dem Zeichen LF kennzeichnen, länger werden [LF wird in CR/NL
  umgewandelt]. Eine Signaturprüfung kann dadurch auch schief gehen.

- Darstellung von mathematischen Zeichen in der HTML-Hilfe:
  Die Microsoft HTML-Hilfe ruft den eingestellten Microsoft Internet
  Explorer (IE) auf. Version IE 6 hat manchmal Probleme, mathemathische
  Zeichen wie die Gauss-Klammer darzustellen.
  Wenn bei Ihnen der IE7 voreingestellt ist, funktioniert es korrekt.
  Die zugrundeliegenden, in das CHM-File eingebundenen HTML-Dateien
  werden von IE7 und Firefox 1.5 und 2.0 korrekt dargestellt.
  Die Gauss-Klammer wird in der Onlinehilfe zum Modulo-Operator als
  Symbol für die nächstniedrigere ganze Zahl verwendet.

- Aus Performancegründen wurde festgelegt, dass CrypTool bei der
  N-Gramm-Analyse die Dokumente beschränkt:
   - für Binärdateien auf 64 kBytes und
   - für Textdateien auf 256 kBytes beschränkt.
  Werden längere Dateien geöffnet, werden sie -- nur bei dieser Art
  der Analyse -- auf den maximalen Eingabewert gekürzt.

- Hashwerte können von Dateien beliebiger Größe berechnet werden,
  sofern die Dateien nicht geladen werden. 

- Mit dem AES-Tool können nur Dateien bis 4 GB Größe verschlüsselt
  und archiviert werden (solange mit VS2003 compiliert wird).

  Bitte beachten Sie, dass die Ausgabe des Standalone AES-Tools nicht
  vollkommen identisch ist mit der Ausgabe, die Sie in CrypTool mit der 
  Menüfolge "Ver/Entschlüsseln \ Symmetrisch (modern) \ Rijndael (AES)"
  erhalten (auch nicht, wenn das AES-Tool eine Datei mit der Endung "aes"
  erzeugt). CrypTool selbst verwendet z.Zt. einen festen IV (0), der nicht 
  gespeichert wird. AES-Tool nutzt einen zufälligen IV und fügt diesen 
  zusammen mit dem Dateinamen hinter den verschlüsselten Daten an.


4.6. Zertifikate, die mit älteren CrypTool-Versionen erzeugt wurden
     --------------------------------------------------------------
Falls Sie Zertifikate, die mit CrypTool-Versionen vor 1.4.00 erzeugt
wurden, unter CrypTool 1.4.10 weiter verwenden wollen, gehen Sie bitte
folgendermaßen vor:
  a) für RSA- und DSA-Schlüssel:
     Exportieren Sie diese PSEs mit Hilfe des alten CrypTools in ein
     PKCS#12-Format und laden Sie diese Dateien im neuen CrypTool.
  b) für ECC-Schlüssel:
     Hier reicht es, die entsprechenden Dateien 
     (z.B. [da][db][EC-prime239v1][1131039030][d] )
     vom alten CrypTool\pse-Verzeichnis in das neue zu kopieren.



5. Installation / Deinstallation / Betrieb
   ---------------------------------------

5.1. Installation und Nutzung von Schlüsseln aus vorherigen Versionen
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
  in ein anderes Verzeichnis. Vergleiche auch Kapitel 4.6.
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


5.2. Installation in Mehrbenutzersystemen
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
Zielverzeichnis ein so genanntes "lokales Verzeichnis" angeben (statt
"C:\Programme"). Lokal und für den Benutzer zugänglich könnten z.B. sein:
%ALLUSERSPROFILE% (Die Standardeinstellung im deutschen Windows XP ist: 
"C:\Dokumente und Einstellungen\All Users").

Wenn Sie CrypTool ohne Administratorrechte installieren und keine
Schreibrechte auf %ALLUSERSPROFILE%\Start Menu haben, werden unter WXP
im Startmenü ("Start \ Alle Programme") die Einträge zu CrypTool fehlen.
Jeder Nutzer kann diese Einträge aber manuell in sein eigenes Startmenü
aufnehmen.

Anmerkung: Wie bei %TEMP% auch, können Sie sehen, wo diese Verzeichnisse
liegen, indem Sie im Windows-Explorer %ALLUSERSPROFILE% oder %userprofile%
eingeben.



5.3. Deinstallation von CrypTool
     ---------------------------
Um CrypTool zu deinstallieren, benutzen Sie bitte das "Start"-Menu in
der Windows-Taskleiste.
Dort gehen Sie zu "Alle Programme" \ "CrypTool".
Dann klicken Sie auf "CrypTool deinstallieren".


5.4. Betrieb in Mehrbenutzersystemen
     -------------------------------
a) Ab Version 1.4.10 werden alle Benutzer-spezifischen Einstellungen in
   der lokalen Registry gespeichert (auch die zuletzt geöffneten Dateien):
   Dadurch braucht man keine ini-Datei mehr im Windows-Verzeichnis und
   unterstützt den Betrieb in Mehrbenutzersystemen.
 
b) Will der Benutzer in Mehrbenutzersystemen wie Windows XP aus CrypTool
   heraus Dateien anlegen (bzw. ändern), braucht er Schreibrechte auf das
   entsprechende Zielverzeichnis (bzw. auf die entsprechende Datei). 
   Geht das nicht, kommt eine Warnung.
   Explizit nötig sind Schreibrechte nur auf 2 Verzeichnisse:
   - das Standard-Windows-Verzeichnis für temporäre Dateien (TEMP)
     für die cry*.*-Dateien,
   - das Unterverzeichnis "CrypTool\pse", da darin die erzeugten 
     asymmetrischen Zertifikate und Schlüssel abgelegt werden.

c) Zentrale Installation auf einem Windows-Netzwerkrechner:

   Besonders in Schulen wird Lern-Software oft nur auf dem zentralen
   Rechner installiert; die Client-PC rufen das Programm von dort dann auf.

   Das Programm CrypTool selbst läuft so auch. Wird aber die Onlinehilfe von
   einem Client-PC aus aufgerufen, wird sie mit den Standardeinstellungen
   des Windows XP-Betriebssystems nicht angezeigt. Das ist kein CrypTool-
   spezifisches Problem, sondern eines aller Windows-Onlinehilfe-Dateien.

   Onlinehilfe liegt normalerweise in einer CHM-Datei vor, die die einzelnen
   HTML-Hilfeseiten bündelt. Innerhalb des Microsoft HTML-Hilfe-Programms
   fungiert der Internet Explorer als Anzeigeprogramm für die in der
   CHM-Datei gebündelten HTML-Dateien.

   In den ersten XP-Versionen konnte von einem Client aus auch auf 
   Hilfedateien auf einem Server zugegriffen werden. Um eine 
   Sicherheitslücke zu schließen, wurde das Windows XP-Update
   (KB896358) verbreitet.
   Leider bewirkt der Patch auch, dass die Microsoft HTML-Hilfe die
   eigentlichen Seiteninhalte nicht mehr anzeigt [dagegen werden die
   Metainformationen wie Inhalt, Index und Suchbegriffe korrekt angezeigt],
   wenn man von einem Client aus auf Hilfedateien auf einem Server zugreift.

   Abhilfe:
   Da das Deinstallieren von Sicherheits-Patches keine gute Idee ist, und
   da es in diesem Szenario auch nicht gewünscht ist, die CHM-Dateien lokal
   zu installieren, kann man einen bestimmten Eintrag in der Registry
   hinzufügen bzw. ändern:
   Wir nehmen an, dass die CHM-Dateien auf einem Server-Laufwerk X: mit
   dem UNC-Pfad "\\dir-1\\dir-2" liegen. Man kann den Client-PCs den Zugriff
   auf das Server-Laufwerk zu erlauben, indem man in der Registry aller
   Clients-PCs folgenden Eintrag aufnimmt:
   [HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\HTMLHelp\1.x\ItssRestrictions]
   "UrlAllowList"="\\dir-1\\dir-2;file://\\dir-1\\dir-2;X:\\dir-1\\dir-2;file://X:\\dir-1\\dir-2"

   ACHTUNG: Generell kann das Bearbeiten der Registry dazu führen, dass
   Windows nicht mehr funktioniert. Die Verantwortung für diese Änderung
   liegt allein bei Ihnen!
   Um auf einem Client-PC die Registry zu ändern, braucht man
   möglicherweise Administratorrechte.

   Weitere Infos: 
    - http://support.microsoft.com/kb/896054
    - http://www.robo-forum.de/cgi-bin/ultimatebb.cgi?ubb=get_topic;f=10;t=000065



6. Liste der Dateien in der Auslieferung
   -------------------------------------
CrypTool wird als komprimiertes, selbst-extrahierendes Archiv in
zwei verschiedenen Sprachversionen verteilt:

SetupCrypTool_1_4_00_en.exe    Englische Sprachversion.
SetupCrypTool_1_4_00_de.exe    Deutsche Sprachversion.

Diese Archive enthalten die folgenden Dateien:

ReadMe-de.txt .... Diese Kurzanleitung (deutsch).
ReadMe-en.txt .... Diese Kurzanleitung (englisch).

md5sum.txt ....... MD5-Hashwerte aller Dateien innerhalb des CrypTool-
                   Paketes (selbst-extrahierendes Archiv).
sha1sum.txt ...... SHA-1-Hashwerte aller dieser Dateien.

CrypTool.exe ..... Das E-Learning-Programm (deutsch + englisch).
aestool.exe ...... Ein Programm, das Dateien in sich selbst-entpackende
                   Programme verschlüsselt (D + E). Zur Entschlüsselung
                   müssen Sie das korrekte Passwort eingeben.
CrypTool-de.chm .. HTML-Hilfe-Archiv für die CrypTool-Onlinehilfe in
                   deutsch.
CrypTool-en.chm .. Die englische Version von "CrypTool-de.chm".

EC-Param.ini ..... Initialisierungsdatei für auf Elliptischen
                   Kurven basierende Public Key-Verfahren.
TEST-Param.ini ... Initialisierungsdatei für die Zufallstests.
secude.dll ....... Bibliothek kryptographischer Funktionen von der
                   Secude IT Security GmbH.
ticket ........... Lizenz für die Secude-Bibliothek.
libxml2.dll ...... Wird benötigt von der secude.dll.
secidea.dll ...... Wird benötigt von der secude.dll für die 
                   IDEA-Verschlüsselung.
srndmskb.dll ..... Wird benötigt von der secude.dll für den 
                   Entropiesammler zur Initialisierung des 
                   Secude-Zufallsgenerators.
db.dll ........... Wird benötigt von der secude.dll.
secude.xml ....... Wird benötigt von der secude.dll.
libeay32.dll...... Bibliothek aus OpenSSL.
SciLexer.dll ..... Bibliothek mit den Routinen für den 
                   Scintilla-Texteditor.

Rijndael-Animation.exe .. Animation (Flash) des AES-Algorithmus.
Enigma_de.exe .... Animation (Flash) der 3-Rotor Enigma-Maschine.
Enigma_en.exe .... Die englische Version von "Enigma_de.exe".
Enigma-Help_de.html .. HTML-Onlinehilfe für  "Enigma_de.exe" (deutsch).
Enigma-Help_en.html .. Die englische Version von "Enigma-Help_de.html".

eccdemo.jar ...... Demo (Java) zur Punktaddition auf Elliptischen Kurven.
ZT.exe ........... Lernprogramm (Authorware) zur Zahlentheorie.
NT.exe ........... Die englische Version von "ZT.exe".
TextZahlWandler.exe ...... Hilfsprogramm zu "ZT.exe".
TextNumberConverter.exe .. Die englische Version von "TextZahlWandler.exe".

ToolBarWrapper.dll .. xxxxxxxxxxxxxxxxx

Zahlenhai.exe .... Das Programm zum Lernspiel "Der Zahlenhai".
NumberShark.exe .. Die englische Version von "Zahlenhai.exe".
NumberShark_de.chm HTML-Hilfe-Archiv für die Zahlenhai-Onlinehilfe (deutsch).
NumberShark_en.chm Die englische Version von "NumberShark_de.chm".
GameData.txt ..... Die ersten High-Scores für das Zahlenhai-Spiel.

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

Uninstall.exe .... Teil des NSIS-Installers.


examples\ ........ Dieses Verzeichnis enthält unterschiedliche
                   Beispieldateien, die in den Szenarien verwendet
                   werden. Dateien mit der Endung ".txt" sind
                   Textdateien. Alle anderen Dateien sind binär.
                   Dateien mit dem Format "XX-enc-YY.*" sind
                   verschlüsselte Dateien. Bitte verändern Sie
                   diese Dateien nicht.

examples\CrypTool-de.txt
        \CrypTool-en.txt
        \CrypTool.bmp
        \Playfair-enc-de.txt
        \probetext-de.txt
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
        \state2.hex ....... unverschlüsselte Beispieldaten aus ...
        \state2-enc.hex ... verschlüsselte Beispieldaten aus ...
                            "Rijndael-Animation.exe", verarbeitet mit "CrypTool.exe". 


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


pse\ ............. In diesem Verzeichnis und in seinem
                   Unterverzeichnis pseca\ werden erzeugte
                   (asymmetrische) Schlüssel und Zertifikate abgelegt.

pse\[SideChannelAttack][Bob][RSA-512][1152179494][PIN=1234].pse

pse\pseca\calog    Diese Dateien sind für die Verwaltung der
         \capse    Schlüsseldatenbank notwendig.
         \CA_exts
         \cert.dir
         \cert.pag
         \CRL_exts
         \crls.dir
         \crls.pag
         \user.dir
         \user.pag


animal\ .......... Dieses Verzeichnis enthält die Dateien, die für
                   das Animationsprogramm ANIMAL nötig sind.

animal\Animal-2.0.2.jar
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


Bc\ .............. In diesem Verzeichnis und darunter liegt das Utility
                   BC zum Rechnen mit beliebig langen Zahlen. Es gehört 
                   zu "ZT.exe" und kann direkt daraus gestartet werden.
                   Nur bc.exe und bc.1.txt sind im Original dabei; die
                   restlichen BC-Dateien stammen vom "ZT.exe"-Autor
                   und beinhalten Skripte mit Funktionen.

Bc\bc.1.txt
  \bc.deutsch.txt ... Übersetzung von bc.1.txt
  \Bc.exe
  \BCmax.bat
  \bruch.txt
  \calc.txt
  \dislog.txt
  \ECM.TXT
  \pi.txt
  \polynom.txt
  \Prims.txt
  \quadRest.txt
  \res.txt
  \seed
  \sieb.txt
  \testBruch.bat
  \testPi.bat
  \testPolynom.bat
  \testSieb.bat

Bc\contrib\Authors
          \bc-1.06.README
          \ChangeLog
          \COPYING
          \COPYING.LIB
          \FAQ
          \INSTALL
          \install-sh
          \News
          \README

\Bc\manifest\bc-1.06-bin.mft
            \bc-1.06-bin.ver


xtras\ ............ Gehört zu Authorware, mit dem "ZT.exe" erstellt wurde.

xtras\BMPVIEW.X32
     \MIX32.X32
     \VIEWSVC.X32




Während der Laufzeit von CrypTool werden die folgenden Dateien
erzeugt und verwaltet:
cry*.* ........... CrypTool schreibt temporäre Dateien mit dem
                   Namensmuster cry*.* in das TEMP-Verzeichnis.
       Diese haben folgende Endungen: 
                   txt -> Textdatei-Ansicht
                   hex -> Hexadezimale (binäre) Ansicht
                   plt -> Diagramm/Plot-Ansicht (Histogramm, Autokorrelation)
                   ogl -> OpenGL-Graphics-Ansicht
                   org -> Kopie der Originaldatei nach dem Laden
                   tmp -> Temporäre Datei für Zwischenberechnungen


6.1. Überprüfen der Integrität der heruntergeladenen Dateien
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
   Weichen die Hashwerte voneinander ab, sollte man die Datei noch
   einmal herunterladen und evtl. die Ursache dafür suchen, dass
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
1.4.00    Juli 2006	18,4 MB		18,2 MB		DB
1.4.10    Apr. 2007	xx,4 MB		xx,2 MB		DB

Bemerkungen zu den Versionen:
1.3.02    Viele neue Funktionen gegenüber 1.3.00.
1.3.03    Viele kleine Bugfixes und Verbesserungen der Dokumentation.
1.3.04    Etliche neue Funktionalität, einige kleine Bugfixes, und
          Verbesserung und Erweiterung der Dokumentation (Online-Hilfe, Skript).
1.3.05    Kleine Bugfixes.
1.4.00-Beta10  Dez. 2005  Erste öffentliche Beta von Version 1.4.00.
1.4.00-Beta12  März 2006  Zweite öffentliche Beta von Version 1.4.00.
1.4.00-Beta14  Juli 2006  Dritte öffentliche Beta von Version 1.4.00.
1.4.00    Viele neue Funktionen gegenüber 1.3.05.
1.4.10-Beta04  April 2007  Erste öffentliche Beta von Version 1.4.10.
1.4.10    Funktionsumfang und Onlinehilfe stark erweitert i.Vgl zu 1.4.00.



8. Feedback
   --------
Sollten Sie Probleme haben oder Fehler finden, wenden Sie sich
bitte mit einer ausführlichen Beschreibung des Problems (und einigen
Bildschirmbildern dazu) per E-Mail an eine der in Kapitel 9 genannten
Personen oder an die Mailingliste.

Für Anregungen jeglicher Art bezüglich CrypTool sind wir immer
dankbar und helfen Ihnen gern, wenn es unsere Zeit erlaubt.

Auch würden wir uns freuen, wenn Sie uns mitteilen, wie und wo Sie
CrypTool einsetzen.



9. Kontaktadressen
   ---------------
- esslinger@fb5.uni-siegen.de
- joerg-cornelius.schneider@db.com
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

10.1.5. Datenschutz PRAXIS (Juni 2005)
        ------------------------------
In der deutsch-sprachigen Fachzeitschrift "Datenschutz PRAXIS",
Ausgabe Juni 2005 erschien unter dem Titel "Spielend verschlüsseln lernen
mit dem kostenlosen CrypTool" ein 2-seitiger Artikel über CrypTool von
Dr. Rainer W. Gerling.
Diesen Artikel finden Sie im Internet unter
http://www.interest.de/DP/ausgaben.php?art=188&ID=587903635588.

10.1.6. Report Touch Briefing Information Security (Oktober 2006)
        ---------------------------------------------------------
Der "Touch Briefing Information Security"-Report 2006 enthält den Artikel
"The CrypTool Project – Improving Awareness and Education for Cryptology".
Abrufbar im Internet unter:
  http://www.touchbriefings.com/pdf/2259/esslinger.pdf
Mit den Suchbegriffen "awareness cryptology" listeten danach sowohl
google.de wie google.com diesen Artikel auf Platz 1. 


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

10.2.3. BSI-Software-Suite BOSS 2.0 (Jan. 2007)
        ---------------------------------------------
Das Bundesamt für Sicherheit in der Informationstechnik (BSI) hat
CrypTool 1.4.00 als Teil der BSI-Software-Suite "BSI OSS Security
Suite 2.0 (BOSS)" mit ausgeliefert.
Siehe http://www.bsi.de/produkte/boss/index.htm



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
   http://williamstallings.com/Crypto/Crypto4e.html 
        (Resource-Seite zu dem Buch "Cryptography and Network Security",
         4. Auflage von William Stallings)
   ...



10.3. Weitere Freeware-Projekte (Crank, CAP, CryptoStudio, etc.)
      ----------------------------------------------------------

Vollständig mit Source-Code verfügbar sind:

- http://freshmeat.net/projects/crank/
  Crank wurde im Januar 2001 von Matthew Russell begonnen und unter
  der GNU General Public Licence (GPL) freigegeben.
  Im Crank-Projekt sollte unter Linux ein Programm mit grafischer
  Oberfläche erstellt werden, um das automatisierte Brechen von
  klassischen Kryptoalgorithmen zu ermöglichen.
  Der Fokus lag auf der Analyse monoalphabetischer Substitutions-Chiffren
  und der Entwicklung generischer und flexibler Analysetools.
  Das Tool liegt nur in englischer Sprache vor.
  Die aktuelle Version 0.2.1 wurde im August 2001 freigegeben und seitdem
  leider nicht mehr weiter entwickelt.
  Auf der Projekt-Webseite gibt es auch einige interessante Links
  zu klassischer Kryptoanalyse.

- http://freshmeat.net/projects/griffon/
  Griffon wurde im Jahre 2000 von Adrian Mulvaney begonnen und unter
  der GNU General Public Licence (GPL) freigegeben.
  Griffon ist ein GTK+ GUI Kryptoanalyse-Paket für "pre-digital 
  Ciphers". Es enthält die folgenden klassischen Verschlüsselungs-
  verfahren: monoalphabetische Transposition, Substitution und Playfair.
  Das Tool liegt nur in englischer Sprache vor.
  Die aktuelle Version 1.0 wurde im November 2000 freigegeben und seitdem
  leider nicht mehr weiter entwickelt.

- http://www.kryptosproject.org/          (alt)
  http://kryptosproject.sourceforge.net/  (neu)
  Kryptos ist Open Source-Projekt, das an der George Mason University begann.
  Krytos ist eine Kryptographie-Lernsoftware mit einer statischen
  Oberfläche, aber vielen modernen Algorithmen, die dynamisch aus
  verschiedenen Bibliotheken kommen können.
  Kryptos hat keine Kryptoanalyse-Funktionen.
  Die aktuelle Version Kryptos 3.01 gibt es seit Dezember 2006,
  sie erfordert .NET Framework 2.0.

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
Oberfläche) verbinden, sind solche, für die aber kein Source-Code
freigegeben ist:

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
  Die aktuelle Version 1.0.1 der CryptoBench gibt es seit 2004.
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
eingesetzt wird, und dabei in Schule, Lehre und Training einen guten
Nutzen stiftet. Über die vielen bisher erhaltenen positiven Rückmeldungen
freuten wir uns natürlich sehr.

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
eine Portierung m.H. von GCC und Qt4 vornimmt (siehe Kapitel 3.6).
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

