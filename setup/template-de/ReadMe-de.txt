==================================================================
    CrypTool, Version 1.4.30 Beta 04 für Win32, Juli 2009  xx-xxxx
    (c) Contributors
        Dazu gehören z.B.
        Deutsche Bank AG, Frankfurt am Main,
        die Universitäten Siegen, Darmstadt, Bochum und Duisburg-Essen.
        1998-2009
    www.cryptool.de
    Bernhard Esslinger
    $Id$
==================================================================

 1. .... Kurzbeschreibung des CrypTool-Paketes
 1.1. .... Wie Sie am besten starten - Der Einstieg in CrypTool
 1.2. .... Was beinhaltet die Distribution
 1.3. .... Danke
 1.4. .... Maintainer, Hosting, Webseite und Welcome
 2. .... Was bietet CrypTool im Detail
 2.1. .... Was können Sie mit CrypTool machen
 2.2. .... Informationen für Entwickler / Wo finden Sie die Sourcen
 2.3. .... Wo finden Sie weitere Überblicke zu CrypTool
 2.4. .... Neuerungen in Version 1.4.20
 2.5. .... Neuerungen in Version 1.4.30
 3. .... Beschränkungen und Voraussetzungen
 3.1. .... Anwendungsbereich dieser Lern-, Trainings- und Awareness-Software
 3.2. .... Win32-Umgebung, Rechte bei Installation und Betrieb, Java-Runtime
 3.3. .... Interaktive Online-Hilfe unter Windows XP
 3.4. .... Unterstützung verschiedener Sprachen
 3.5. .... Einschränkungen / Features
 3.6. .... Mit älteren CrypTool-Versionen erzeugte Zertifikate und Schlüssel
 4. .... Installation / Deinstallation / Schlüsselnutzung / Betrieb
 4.1. .... Installation
 4.2. .... Deinstallation von CrypTool
 4.3. .... Wiederholte Nutzung von Schlüsseln
 4.3.1. .... Schlüssel aus vorherigen Versionen
 4.3.2. .... Schlüssel gespeichert in den Dateien des PSE-Verzeichnisses
 4.4. .... Installation in Mehrbenutzersystemen
 4.5. .... Betrieb in Mehrbenutzersystemen
 4.6. .... Installation auf einem Netzwerk-Laufwerk --> Onlinehilfe-Problem
 5. .... Liste der Dateien in der Auslieferung
 5.1. .... Überprüfen der Integrität der heruntergeladenen Dateien
 6. .... Kurze Historie der freigegebenen Hauptversionen
 7. .... Feedback und Kontaktadressen
 8. .... Verweise / Auszeichnungen
 8.1. .... Artikel über CrypTool
 8.2. .... Sonstige Referenzen auf CrypTool
 8.3. .... Weitere Freeware-Projekte (Crank, CAP, CryptoStudio, etc.)
 8.4. .... Auszeichnungen
A. .... Anhang
A.1. .... CrypTool unter Linux mit Wine
A.2. .... Neue Funktionen, Roadmap, Nachfolger-Projekte mit Java/Eclipse und C#/.NET


1. Kurzbeschreibung des CrypTool-Paketes
   -------------------------------------
Diese Readme-Datei gehört zur kostenlosen Distribution des Open-Source-
Programms CrypTool 1. Mit CrypTool kann man kryptographische Verfahren
erlernen, ausprobieren und sowohl bekannte wie unbekannte Verfahren
analysieren. Schon in der Antike wurden solche Verfahren zur Geheim-
haltung von Nachrichten entwickelt. Heutige Verfahren basieren auf
moderner Mathematik und erlauben neben der Verschlüsselung auch die
Prüfung der Integrität, die Erstellung von Signaturen, sichere
Authentisierung und Vieles mehr. CrypTool unterstützt sowohl die
Ausführung als auch die Analyse solcher Verfahren.

CrypTool wird seit 1998 entwickelt. Im Moment arbeiten über 40 Personen
weltweit daran.

Zu jedem Programmteil gibt es reichhaltige Online-Hilfe, die auch
ohne tiefes Kryptowissen verstanden werden kann.

CrypTool existiert in den vier Sprachen Deutsch, Englisch, Polnisch
und Spanisch. In Deutsch und Englisch ist das CrypTool-Paket komplett
vorhanden.
Die Spanische Programm-Version hat die gleiche Funktionalität
[übersetzt sind im Moment das Programm selbst, also die
Oberfläche (Menüs, Dialoge, ...) und die Onlinehilfe.
Die der spanischen Version beigelegte PDF-Dokumentation ist
noch in Englisch]. Ähnlich ist es bei der Polnischen Version.

Vorausgesetzt wird, dass der Benutzer mit Anwendungen in einer
Windows-Umgebung umgehen kann.

Die aktuelle Release-Version von CrypTool und den Quellcode dazu
finden Sie unter den Internet-Adressen (keine Registrierung nötig):
                http://www.CrypTool.de
                http://www.CrypTool.com
                http://www.CrypTool.es
                http://www.CrypTool.org
                http://www.CrypTool.pl

Seit Mitte 2007 werden über 3000 CrypTool1-Pakete pro Monat herunter
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

Für bisherige Benutzer von CrypTool dürften in diesem Readme vor
allem die Kapitel 2.5 (Neuerungen in CT 1.4.30) und in Kapitel A.2
(Weiterentwicklung, Roadmap) interessant sein.

Wir laden jeden herzlich ein, an CrypTool mit zu entwickeln oder
Feedback zu geben. Auch für Hinweise zu Arbeiten (Diplom-, Doktor-
oder Seminararbeiten), die man in CrypTool integrieren könnte, sind
wir sehr dankbar.
Insbesondere junge Entwickler sind eingeladen, sich zu trauen -- sie können
bei erfahrenen Entwicklern sehr viel über professionelle Software-Entwicklung
lernen. 
Kontakte: Siehe Kapitel 7 unten.


1.1. Wie Sie am besten starten - Der Einstieg in CrypTool
     ----------------------------------------------------
Beim Start von CrypTool öffnet sich zuerst im Vordergrund ein kleines
Begrüßungsfenster und dann die Arbeitsfläche von CrypTool.
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
Sie können auf der CrypTool-Arbeitsfläche aber auch eine andere
unverschlüsselte Datei aus dem Unterverzeichnis "examples" oder
irgendeine andere Datei öffnen.

Wenn Ihnen ein Menüpunkt nichts sagt oder Sie in einem Dialogfenster
nicht recht weiter wissen, sollten Sie mittels der F1-Taste ausreichend
Hilfe finden (wenn nicht, geben Sie uns bitte Feedback).

Eine 1-seitige Übersicht über alle Menüs in CrypTool (Menübaum)
finden Sie im beigelegten PDF-Skript (in dessen Anhang A1).

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
  - der cv act library der cv cryptovision GmbH (www.cryptovision.com).
 
  Die aktuell benutzten Versionen der inkludierten Bibliotheken finden
  Sie in der Dialogbox "Über CrypTool" (siehe Hilfe-Menü).

  Somit ist CrypTool auch eine hervorragende Referenzimplementierung
  für kryptographische Verfahren.

- Die Kryptoanalyse der meisten der klassischen Verfahren ist
  automatisiert.
  Die Analyse der modernen Verfahren ist eingeschränkt, so dass
  CrypTool kein Hackertool ist.

Entwicklungsziel von CrypTool war nicht, dass damit im Wirkbetrieb
eine CA (Certification Authority) betrieben wird [vergleiche Kapitel 3.1]
oder dass damit für produktive Zwecke Daten verschlüsselt oder anderweitig
gesichert werden sollten. 


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

a) Das Programm AES-Tool v 2.5 (entstanden im CrypTool-Projekt):
   Zum Erstellen selbst-entpackender Executables ist in CrypTool ein
   Programm integriert, das auch eigenständig benutzt werden kann.
   Darin wird aus einem Passwort ein Session-Key erzeugt, mit dem
   ein beliebiger Dateiinhalt AES-verschlüsselt wird.
   Dieses Verschlüsselungstool kann sowohl als Fensteranwendung als
   auch von Kommandozeile (z.B. aus einer Batchdatei) aufgerufen werden.
   Bei der Installation wird diesem Programm die Dateiendung "AES"
   zugeordnet.

b) Das Lernspiel "Der Zahlenhai" v 1.1.6 (entstanden im CrypTool-Projekt):
   Dieses Lernspiel für Schüler bringt diesen den Umgang mit
   Teilern und Primfaktoren näher.

c) Das Animationsprogramm ANIMAL (siehe http://www.algoanim.info/Animal2):
   Mit diesem an der TU Darmstadt von Dr. Rößling gepflegten Programm
   kann man die Einzelschritte von Algorithmen oder die Komponenten von
   Datenstrukturen beliebig genau modellieren, die Einzelschritte manuell
   vor und zurück abspielen oder automatisch ablaufen lassen. Damit kann
   man auch dynamisch Source-Code-Zeilen visualisieren.
   Das Animal-System erlaubt die Erstellung von Animationen mithilfe
   einer GUI, einer Skriptsprache sowie einer Java-API.
   Weitere Beispiele finden sich im ANIMAL-Repository (Datenbank):
   http://www.algoanim.info/Animal2/?q=node/284
   Hierzu wird die JRE 1.5 benötigt (siehe Kapitel 3.2).

d) Ebenso wie ANIMAL sind die ff. Programme eigenständige Java-Anwendungen
   (JAR-Dateien):
   - ECC-Demo v 1.1
     Hierzu wird auch die JRE 1.5 benötigt (siehe Kapitel 3.2).
   - AES-Flussvisualisierung
   - Das Control-Center zur Steuerung der S/MIME-Demo (diese erstellt anhand
     der Parameter eine XML-Datei, die zur Steuerung der aufgerufenen
     Flash-Animation dient).

e) Die Flash-Anwendungen:
   - "Rijndael-Animation" (visualisiert das Verschlüsselungsverfahren AES),
   - "Rijndael-Inspektor" (visualisiert die Änderungen der State-Matrix 
                           nach jedem Schritt in jeder Runde bei AES) und
   - "Enigma" (visualisiert das 2.-Weltkriegs-Krypto-Gerät Enigma).

f) Die Authorware-Anwendung "ZT" (Zahlentheorie) führt in die elementare
   Zahlentheorie ein und visualisiert viele der Verfahren und Konzepte,
   die Grundlage der modernen Public-Key-Kryptographie sind.
   Wo nötig zeigt sie auch die entsprechenden mathematischen Formeln.
   Dabei können diese mathematischen Verfahren dynamisch mit eigenen
   kleinen Zahlenbeispielen ausprobiert werden.
   Dazu gehört auch das Programm bc.exe der Free Software Foundation (FSF),
   mit dem man auf der Kommandozeile beliebig genau rechnen kann.



(4) Geschichten (mit Bezug zu Zahlentheorie und Kryptographie) und Rätsel
-------------------------------------------------------------------------
a) Als PDF-Datei sind zwei Geschichten beigelegt:
   - In "Der Dialog der Schwestern" wird eine Variante des RSA-Verfahrens
     von den Titelheldinnen benutzt, um verschlüsselt zu kommunizieren.
   - In "Das Chinesische Labyrinth" muss Marco Polo zahlentheoretische
     Aufgaben lösen, um Berater des Großen Khan zu werden.

b) Krypto-Wettbewerbe:
   Ebenfalls beigelegt sind 13 Dateien mit verschlüsselten Texten, die uns
   freundlicherweise Klaus Schmeh zur Verfügung stellte, der Autor des
   Buches "Codeknacker gegen Codemacher":
   Klaus Schmeh: "Codeknacker gegen Codemacher. Die faszinierende Geschichte
                 der Verschlüsselung", 2. Auflage, Dezember 2007, W3L-Verlag

   Diese Dateien enthalten einige historisch interessante (gelöste und
   ungelöste) Geheimtexte, die Sie als "Übungsmaterial" und Zeitvertreib
   verwenden können:
   1) Dorabella-Chiffre (ungelöst) 
   2) D’Agapeyeff-Chiffre (ungelöst)
   3) Feynman-Chiffren (3 Teile, von denen zwei ungelöst sind) 
   4) Kryptos-Skulptur (4 Teile, von denen der letzte ungelöst ist) 
   5) Doppelwürfel (erstellt von Klaus Schmeh, Quelltext englisch, ungelöst)
   6) "Die tanzenden Männchen" von Arthur Conan Doyle (Sherlock Holmes)
                   (transkribiert, gelöst)
   7) Harry-Potter-Chiffre (von Klaus Schmeh, Quelltext deutsch, ungelöst)
   8) "Mathias Sandorf" von Jules Verne (gelöst)

   Mehr Informationen dazu gibt es in der Onlinehilfe zu CrypTool (unter dem
   Indexeintrag "Krypto-Wettbewerbe") und in dem Buch von Klaus Schmeh.


Alle Einzeldateien, die bei der Installation des CrypTool-Paketes
auf Ihre Platte kopiert werden, sind in Kapitel 5 (unten in diesem
Readme) aufgeführt.



1.3. Danke
     -----
Zu CrypTool haben sehr viele verschiedene Personen (weit über 100)
beigetragen -- insbesondere auch in ihrer Freizeit.
Einige sind namentlich in der Dialogbox aufgeführt, die man erhält,
wenn man in der Dialogbox "Über CrypTool" einen Doppelklick ausführt.
Der Wohnort einiger Entwickler/Mitwirkenden ist auf der CrypTool-Webseite
per Google-Map zu finden (Menü Über -> Mitwirkende).
Herzlichen Dank an alle Mitwirkenden.

Besonders herausheben möchte ich einige Kernentwickler/-Architekten
im CrypTool 1.x-Projekt, deren hohes und langjähriges Engagement und
deren hervorragende Kompetenz und Hartnäckigkeit solche dauerhaften,
lebendigen und erfolgreichen Open-Source-Projekte erst ermöglicht:
Jörg, Henrik, Florian, Peer.

Ebenfalls danken möchte ich einigen Kernentwicklern/-Architekten in
den Nachfolger-Projekten CT2 und JCT, die mit großer Ausdauer und
Kompetenz die Schwierigkeiten mit den allerneuesten Entwicklungsumgebungen
und Software-Architekturen bewältigten:
- Philipp, Thomas, Sebastian, Arno, Martin, Timo, Soeren
- Dominik, Matthias, Tobias, Simon, Amro, David

Und natürlich den vielen Ungenannten, insbesondere Studenten und
Praktikanten, die viel dazu beitrugen und dabei noch mehr lernten
von den Experten im Projekt.

Ebenfalls beigetragen haben als Sponsoren z.B. die Deutsche Bank AG,
die Technische Universität Darmstadt und die Universität Duisburg-Essen.

Weiterhin möchten wir hier einige Mitwirkende erwähnen, für deren Input
besondere Bedingungen gelten:

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

- Dr. Guido Rößling erlaubte uns, seine Freeware ANIMAL, eine Java-basierte
  Animationssoftware, mit auszuliefern.

- Ebenfalls integrieren durften wir erweiterte Versionen von:
  - den beiden Flash-Animationen zu AES von Enrique Zabala,
  - der Flash-Animation zur Enigma von Dr. Frank Spieß,
  - dem Zahlentheorie-Lernprogramm von Martin Ramberger.
  Die über eine Verwendung außerhalb des freien CrypTool-Contextes
  hinaus gehenden Rechte verbleiben beim jeweiligen Autor.

- Die Firmen (siehe Kapitel 1.2)
  - Secude IT Security GmbH, 
  - Shamus Software Ltd und
  - cv cryptovision GmbH
  gestatteten uns großzügigerweise, ihre Krypto-Bibliotheken zu nutzen.
  Diese mit CrypTool verteilten Bibliotheken dürfen nicht in einem
  Kontext außerhalb CrypTool benutzt werden, ohne vorher die erwähnten
  Firmen zu kontaktieren und nach ihren aktuellen Lizenzbedingungen zu
  fragen.

Ebenso herzlich danken möchten wir den Open-Source-Entwicklern, die uns
mit ihrem Code Anregungen gaben oder deren Code wir nutzen dürfen, z.B.
- die Bibliotheken OpenSSL, GMP und NTL,
- die Installations-Software NSIS (http://nsis.sourceforge.net/Main_Page),
- die Texteditor-Software Scintilla (http://scintilla.sourceforge.net),
- das Hex-Control (www.codeguru.com/Cpp/controls/controls/article.php/c5287).

Bedanken möchte ich mich auch bei
- Herrn Bartosz Sawicki von der Universität Warschau, der mit seinem
  Team die erste polnische Version erstellte.
- Herrn Dr. Gonzalo Alvarez von der Universität Madrid, der mit seinen
  Kollegen die spanischen Versionen erstellte und erweiterte.


1.4. Maintainer, Hosting, Webseite und Welcome
     -----------------------------------------
Seit April 2008 hostet der Lehrstuhl für Verteilte Systeme,
Fakultät für Ingenieurwissenschaften unter Prof. Dr. Torben Weis an der
Universität Duisburg-Essen die deutsche, englische und spanische Webseite
von CrypTool und das Subversion-Repository für die Programm-Sourcen der
Nachfolger-Version CrypTool 2.

Der Lehrstuhl Sicherheit in der Informationstechnik, Fachbereich
Informatik unter Frau Prof. Dr. Claudia Eckert an der TU Darmstadt
hostet weiterhin das Subversion-Repository für die Programm-Sourcen
der Release-Version CrypTool 1.x.

Die CrypTool-Entwicklergruppe um Prof. Bernhard Esslinger fungiert
als Maintainer, d.h. sie kümmert sich um die Pflege des Codes, die
Veröffentlichung als Open Source und Freeware, und um die
Koordination der Weiterentwicklung. Die nächsten Schritte der
Roadmap sind in Kapitel A.2 und auch auf der Webseite veröffentlicht.

Die Homepage von CrypTool ist www.cryptool.org.

Wir freuen uns über jeden weiteren Entwickler, der sich an der
Weiterentwicklung von CrypTool beteiligt.
Ideen zur Weiterentwicklung finden Sie z.B. in Kapitel A.2.

Ebenfalls sehr willkommen sind uns Ideen und Infos, wie CrypTool in
Lehre, Schule und Ausbildung eingesetzt wird, damit wir dazu 
beitragen können, diese Informationen auszutauschen. Ein Mittel
dazu ist z.B. das Kryptologie-Portal für Lehrer (www.cryptoportal.org).



2. Was bietet CrypTool im Detail
   -----------------------------

2.1. Was können Sie mit CrypTool machen
     ----------------------------------
Die generellen Eigenschaften und Funktionen von CrypTool sind:

- E-Learning-Programm rund um das Thema Kryptographie und Kryptoanalyse.

- Alles in einem Programmpaket und steuerbar unter einer Oberfläche.

- Alles in CrypTool ist in Deutsch und Englisch verfügbar.
  Das Programm selbst gibt es auch in Polnisch und Spanisch.

- Viele klassische Verschlüsselungsverfahren: Und dazu teilweise manuell
  unterstützte, teilweise automatische Analysen (Known-Plaintext- und
  Ciphertext-only-Angriff).

- Codierungen wie Base64 und UU-Encode.

- Nahezu alle modernen symmetrischen Verschlüsselungsverfahren: Und dazu
  jeweils die Brute-force-Analyse
  (Beim Brute-force-Angriff auf symmetrische Algorithmen werden Jokerzeichen
   zugelassen und die erwartete Zeit wird ausgegeben. 
   Außerdem kann man die Breite für das hierbei genutzte Entropiefenster in
   den Analyseoptionen einstellen, sowie welche Erwartung man an das Alphabet
   hat, aus dem der Klartext gebildet wurde).

- Moderne (asymmetrische) Kryptoverfahren und Protokolle (Hash, RSA, ECC,
  Digitale Signatur, Hybrid-Verschlüsselung, PKCS#5, Shared Secret, ...)
  und teilweise Angriffe darauf (Geburtstagsangriff, Seitenkanalangriff, 
  Gitterbasenreduktion).

- Demo des RSA-Verfahrens (in verschiedenen Varianten) und Demo einiger 
  zugehöriger Algorithmen aus der Zahlentheorie:
  - Primzahlen generieren und testen (sowohl mit den schnellen heuristischen
    als auch mit dem deterministischen AKS-Verfahren).
  - Zahlen (schrittweise) mit verschiedenen Verfahren faktorisieren
    (die verschiedenen Verfahren laufen in parallelen Threads).
  - Das RSA-Kryptosystem transparent durchführen:
     - RSA-Schlüssel erzeugen (auch mit selbst-gewählten Primzahlen).
     - Ver-/Entschlüsseln mit dem RSA-Verfahren.
     - RSA-Signaturen erzeugen und diese verifizieren.
     - das RSA-Verfahren angreifen.

- Drei auf Gitterreduktionsverfahren basierende Angriffe gegen das 
  RSA-Verfahren, die dann greifen, wenn bestimmte Vorbedingungen 
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
  diese Verfahren implementiert wurden, kann auf Anfrage per E-Mail
  zugesandt werden (sie liegt nur in Deutsch vor).

- Visualisierungen/Animationen/Demonstrationen
  - Demo der Sensitivität von Hashverfahren.
  - Visualisierung mit Flussdiagrammen (z.B. beim Diffie-Hellman
    Schlüsselaustausch-Verfahren oder bei der Challenge-Response-Demo),
  - Animationen 
     - mit ANIMAL: für die Verschlüsselungsverfahren Caesar, Vigenère,
                   Nihilist und DES,
     - mit Flash:  für AES, Enigma und S/MIME,
     - mit Java/SWT: Punkteaddition auf Elliptischen Kurven (sowohl auf
                     diskreten wie auf reellen Kurven),
                     Flussvisualisierung von AES,
                     Control-Center von S/MIME.

- Demo zu Authentisierungsmöglichkeiten im Netz (Visualisierung von
  Challenge-Response-Verfahren):
  * von UID/PW und One-Time-Password
  * über (einseitige) Challenge-Response (symmetrisch + asymmetrisch)
  * bis zu asymmetrischer gegenseitiger Authentisierung.
  * Der Benutzer kann interaktiv steuern, wie der Angreifer vorgeht 
    (Rechner übernehmen, Verbindungen aufbauen oder trennen, lauschen).
  * Lerneffekt: Nur die gegenseitige asymmetrische Authentisierung ist
    sicher gegen Man-in-the-Middle-Angriffe.

- Demo für einen Seitenkanalangriff gegen ein typisches Hybrid-
  Verschlüsselungsprotokoll: Bei einer sub-optimalen Implementierung, 
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

- Zu jedem Fenster kann ein Dialog angezeigt werden, der alle
  wesentlichen Eigenschaften dieses Dokuments anzeigt.

- In allen Fenstern, wo die Optionen für Text und Alphabete eine Rolle
  spielen, kann man direkt per Button-Klick zum Textoptionen-Dialog
  springen.

- CrypTool kann man ohne Administratorrechte installieren und ausführen.
  Verschiedene Benutzer können am gleichen PC jeweils verschiedene
  Einstellungen haben. Details siehe Kapitel 3.2 und 4.4.

- Die gleiche Menüstruktur ist konstant sichtbar: Einträge, die für
  bestimmte Dokumenttypen nicht ausführbar sind, werden ausgegraut.

- Das eigenständige Programm AES-Tool kann selbst-entpackende
  Programme erzeugen. Damit kann man eine beliebige Datei Passwort-geschützt
  mit AES verschlüsseln (das Passwort ist als Hexadezimal-Schlüssel
  einzugeben).
  Voller Funktionsumfang auch bei einem Aufruf von der Kommandozeile.
  Erzeugt man selbst-entpackende Archive, darf das Ergebnis nicht größer
  als 4 GB werden. Erzeugt man nur die verschlüsselten AES-Dateien
  kann das Original auch deutlich größer als 4 GB sein.

- Das eigenständige Lernprogramm für die Mathematik hinter der
  asymmetrischen Kryptographie beschreibt ausführlich und interaktiv
  die elementare Zahlentheorie.

- Drei auf dem Chinesischen Restesatz beruhende Anwendungen:
  * Lösung von Systemen linearer modularer Kongruenzen am Beispiel 
    einer Planetenkonstellation im Sonnensystem.
  * Veranschaulichung des Rechnens (Addieren, Subtrahieren, 
    Multiplizieren) mit modularen Resten statt mit den (größeren)
    eigentlichen Zahlen.
  * Veranschaulichen des Shared-Secret-Verfahrens (entspricht der 
    Analogie, dass man zum Öffnen eines Tresors z.B. drei beliebige 
    von 5 Schlüsselinhabern braucht).

- Mit dem Passwort-Qualitätsmesser (PQM) kann man die Widerstandsfähigkeit
  eines Passworts mit verschiedenen Verfahren und unter Vorgabe von
  Mindestanforderungen abschätzen.

- Mit dem Passwort-Entropie-Dialog können Sie Passworte erzeugen, die eine
  ähnlich hohe Sicherheit bieten wie zufällig erzeugte Binärschlüssel für
  symmetrische Verfahren einer vorgegebenen Bitlänge. Sie können dabei
  ebenfalls das für das Passwort verwendete Alphabet festlegen.

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



2.2. Informationen für Entwickler / Wo finden Sie die Sourcen
     --------------------------------------------------------

- Die Release-Sourcen (Tag "CrypTool_1_4_30") und die aktuellen Entwickler-
  Sourcen stehen direkt im Subversion-Repository zur Verfügung.
  Darauf kann jedermann lesend zugreifen per
  svn checkout https://file.sec-tud.de/svn/CrypTool/trunk
      --username anonymous --password anonymous

- Einen Eindruck von der Größe des Projekts liefert die folgende, im
  Juni 2009 erstellte Statistik (anhand der Dateien für die deutsche,
  englische und polnische Version):

    FILE SUMMARY xxxxxxxxxxxxxxxxxxxxxxxxxxxx
    ------------
              5 .rc files
             38 .c files
            318 .cpp files
            376 .h files
             36 .java files
             10 .pl files
           1615 .html files
             18 .txt files
             35 .tex files

  
    LINES OF CODE (LoC) SUMMARY
    ---------------------------
         35.110 MFC resource code (rc)
        232.622 C/C++ source code (c cpp h)
          9.256 Java source code (java)
          1.654 Perl code (pl)
         89.683 HTML code (html hpp)
          4.118 Text files (txt)
         26.738 LaTeX code (tex)
        399.181 TOTAL

    TOTAL: 399.181 lines of code (plus of 4,4 % from 382.244 with v1.4.21)
    - Here only code written within the CrypTool project or explicitely
      dedicated to the CrypTool project is counted. Any sources used
      within the CrypTool project coming from other open source projects
      like OpenSSL, NTL, Scintilla, ... are not listed here.
      Also any automatically created files are not counted.

   Snapshot zur Anzahl von Dateien und zur Anzahl der Source-Code-Zeilen


- Details zum Compilieren, Linken und zur einheitlichen Entwicklung
  finden sich in den Sourcen in der Datei "readme-source".

- Die Sourcen wurden mit der Microsoft Entwicklungsumgebung Visual Studio 2008
  Standard Edition (VC++ v9.0) compiliert, um die aktuelle Version zu
  unterstützen.
  Die Express-Edition von VS2008 reicht nicht aus, weil CT 1.x noch die
  alte MFC-Klassenbibliothek für die GUI nutzt, die die Express-Edition
  nicht unterstützt.
  Der Wechsel von VS2003 auf VS2008 war auch deshalb erforderlich, weil nur
  damit manche Bibliotheken so compiliert werden konnten, dass sie sowohl
  unter Vista als auch XP korrekt liefen.
  Eine Komplettcompilierung aller 4 Sprachversionen (jeweils Debug und Release)
  dauert auf einem modernen PC rund 2 h.



2.3. Wo finden Sie weitere Überblicke zu CrypTool
     --------------------------------------------
Eine gute Übersicht, was CrypTool bietet, finden Sie auch
- in der beigelegten PDF-Präsentation (Titel: "Kryptologie mit CrypTool"),
- auf der CrypTool-Webseite
  (insbesondere über die Menüs "Funktionen -> CrypTool-Funktionen" und
  "Medien -> Screenshots"),
- mithilfe des Menübaums im Anhang A.1 des beigelegten CrypTool-Skripts, und
- in der Onlinehilfe (siehe "Startseite").



2.4. Neuerungen in Version 1.4.20
     ----------------------------
Dieses Kapitel listet die Erweiterungen und Bugfixes auf, die in
CrypTool 1.4.20 seit CrypTool 1.4.10 hinzugefügt wurden.

a) Entwickler-relevante Änderungen (eher Programm-technisch):

- Aufräumen des Source-Code, höhere Wiederverwendung.

- Update auf OpenSSL 0.9.8g, ANIMAL 2.3.14 and NSIS 2.37.

- Automatisierter Konsistenzcheck in der Onlinehilfe (Verweis auf Menüs,
  Dialoge, Bilder, Querverlinkung).

- Eingabefelder gegen Fuzzy-Eingaben per Clipboard stabilisiert, um
  provozierte Abstürze zu vermeiden.


b) Änderungen in der Benutzer-Dokumentation / Web-Darstellung:

- Online-Hilfe: erweitert.

- Skript: Behebung kleinerer Fehler, Menübaum in Anhang A.1 der neuen
          CrypTool-Version angepasst.

- Aktualisierte und auf 106 Seiten erweiterte Präsentation.

- Neue CrypTool-Webseite mit Joomla seit April 2008.


c) Funktionale Änderungen / Erweiterungen:

- Bugfixes:
  - Viele kleine Verbesserungen in den Masken:
    Benutzerführung; Refresh; Cursor korrekt auch nach Dialogwechsel;
    bei DH, Hill und Seitenkanalangriff einheitlich Häkchen für die Anzeige
    von Detaildialogen und die Erstellung von Logfiles.
  - AML-Datei für die DES-Animation mit ANIMAL korrigiert (in der Matrix
    K[1] war ein Bit auf 1 statt auf 0). Danke an aufmerksame Benutzer!
  - Installer behandelt schon installierte Versionen nun besser.

- Installer ordnet die Datei-Endung AES dem AES-Tool zu; und trägt das
  AES-Tool optional in das Kontextmenü "Öffnen mit ..." im Windows-
  Explorer ein.

- Das Menü "Hilfe" innerhalb der CrypTool-Anwendung enthält nun auch den
  Aufruf der CrypTool-Präsentation.

- Im Textoptionen-Dialog gibt es nun auch ein Häkchen für deutsche
  Umlaute zum Zusammenklicken des gewählten Alphabets.

- Textdateien können nun in Blöcken einstellbarer Breite dargestellt
  werden. Z.B. im Format  xxx xxx xxx  oder  xxxxx xxxxx xxxxx ...
  Auch Konversion in Groß- oder Kleinbuchstaben einstellbar.

- Erweiterung der Editoren:
  * Hex-Editor / Hex-Control / HexView:
     - Suchen und Ersetzen (incl. Hex-Nullen) auch im Hexbereich.
     - Undo/Redo.
  * Text-Editor:
     - Suchen und Ersetzen sowohl mit ASCII wie mit Hexstrings synchron.
     - Redo.

- Die ADFGVX-Chiffre kann nun das durch die Textoptionen definierte
  variable Alphabet für das Transpositionspasswort nutzen (nicht mehr
  nur die 26 Großbuchstaben).

- Erweiterung der Brute-force-Analyse symmetrischer Verfahren (Henk -- danke
  für die praktischen und didaktischen Anregungen):
  - Einstellen des Alphabets für den erwarteten Klartext, um die Suche
    nach einem möglichen richtigen Schlüssel einzuschränken.
  - Anbieten der 50 Klartexte mit den niedrigsten Entropie-Werten zur Auswahl.

- Das AES-Tool in der Version 2.5 ist bei großen Dateien schneller.
  Die Datei-Endung AES wird bei der Installation diesem Programm zugeordnet.

- Das Lernprogramm/Lernspiel "Zahlenhai" in der Version 1.1.5 wurde etwas
  korrigiert und vor allem wurde die Onlinehilfe erweitert.

- SHA2-Familie (SHA-256, SHA-512) ergänzt bei der Berechnung der Hashwerte
  des angezeigten Dokuments oder einer Datei.
  http://csrc.nist.gov/publications/fips/fips180-2/fips180-2.pdf

- Verbesserung des Passwort-Qualitätsmessers, indem neben bekannten
  PQM-Methoden wie denen aus KeyPass oder PGP eine eigene Komponente zur
  Bewertung ergänzt wurde. Hierbei wurden die aus Wörterbuch-Angriffen
  bekannten realistischen Annahmen über das Vorwissen von Angreifern
  berücksichtigt:
  - Erkennen von Serien und Mustern (nicht nur die Entropie von einzelnen
    Zeichen unabhängig bewerten)
  - Alle Verfahren sind normiert: 100 % bedeutet 128 Bit Entropie.
    Ist 100 % erreicht, werden weitere Eingaben im Passwortfeld ignoriert.
  - Einschränkungen in dieser Version:
    - Im Passwortfeld können keine Leerzeichen eingegeben werden
      (Alle Ascii-Codes <= 32 werden ignoriert).
    - Die neue PQM-Methode wertet nur die ersten 32 Zeichen des eingegebenen
      Passwortes aus.

- Der Passwort-Entropie-Dialog erlaubt es, zufällige Passworte zu erzeugen,
  die eine ähnlich hohe Sicherheit bieten wie zufällig erzeugte
  Binärschlüssel für symmetrische Verfahren bei einer vorgegebenen Bitlänge.
  Außerdem kann man das Alphabet des Passwortes vorgeben.



2.5. Neuerungen in Version 1.4.30
     ----------------------------
Dieses Kapitel listet die Erweiterungen und Bugfixes auf, die in
CrypTool 1.4.30 seit CrypTool 1.4.21 hinzugefügt wurden.

a) Entwickler-relevante Änderungen (eher Programm-technisch):

- Aufräumen des Source-Code, höhere Wiederverwendung,
  Beseitigen vieler Warnungen.

- Nun mit VS2008 compiliert.

- Update der Bibliotheken und genutzten Fremdsoftware auf ff. Versionen:
  - Scintilla 1.7.7
  - cv act library v. 1.4.6 (unterstützt auch Vista)
  - OpenSSL 0.9.8k
  - GMP ? xxxxx
  - Animal 2.3.21.


b) Änderungen in der Benutzer-Dokumentation / auf den Web-Seiten:

- Online-Hilfe: deutlich erweitert (z.B. sind nun bei allen Blockchiffren
                explizit die benutzten Modi und Padding-Varianten erläutert).

- CrypTool- Skript: Update auf aktuellen Stand,
                    Aufnahme von Sage-Programmbeispielen,
                    Behebung kleinerer Fehler,
                    Menübaum in Anhang A.1 an neue CrypTool-Version angepasst.

- Aktualisierte und auf 112 Seiten erweiterte Präsentation.

- Von der CT-Webseite wird auf die Websites der Nachfolger-Versionen JCT1
  und CT2 verwiesen, die schon die jeweils aktuelle Beta zum Download anbieten.

- Die zusätzliche Webseite CrypTool-Online ging live (www.cryptool-online.org).

- Quellcode und die Applikation CrypTool 1.x stehen nun unter der Lizenz
  Apache 2.0 (siehe http://www.apache.org/licenses/LICENSE-2.0).


c) Neue Funktionalität / Bedienung:

- Bugfixes  --> Danke an die vielen aufmerksamen Benutzer!
   - Fehler in AKS behoben, der mit den Eingaben 2^8+1 und 2^16+1 auftrat.
     Die korrekte Fassung von AKS braucht länger.
   - Fehler behoben bei weiteren Primzahltests, wenn Primfaktoren < 39
     vorkamen.
   - In der Maske "Schlüssel aus Passwort generieren (nach PKSC #5)" werden
     nun auch die Hashwerte mit führenden Nullen korrekt angezeigt.
   - Die ECC-AES-Hybrid-Ver-/Entschlüsselung läuft nun dank einer neuen
     cv act lib von cryptovision auch unter MS Vista.
   - Die auf dem CRT beruhende Secret-Sharing-Anwendung verbietet nun, dass
     n=k (somit sind alle Shareholder notwendig). Ohne diese Einschränkung
     macht der Algorithmus das ganze Geheimnis dem ersten Teilnehmer bekannt.
   - RSA-Demo: Ein eingegebener Wert für e wird auch nach Aufruf des
     Optionen-Dialogs beibehalten.
   - Korrektur der ECC-Demo:
     - Die Vorgängerversion lieferte über der Gruppe F(p) bei der Punktaddition
       unter bestimmten Umständen einen Punkt außerhalb der Kurve.
     - Die Koordinaten der Punkte, die dynamisch in der Nähe des Mauszeigers
       erscheinen, sind nun auch am rechten Rand ganz sichtbar.
     - Der Punkt im Unendlichen wird zur Gesamtzahl der Punkte hinzugezählt.
     - Das Log-Fenster ist nun amodal, größenveränderlich und der Inhalt
       ist übersichtlicher gestaltet.
     - Die Versionsnummer wurde auf 1.1 erhöht und wird nun im Titel angezeigt.
   - Korrektur bei DESX/DESXL: Nun wird die effektive Bitlänge in den
     Dialogen zur Verschlüsselung und zur Brute-force-Analyse angezeigt.
   - Korrektur bei der DESX/DESXL-Brute-force-Analyse, die Schlüssel überging,
     wenn die obersten 128 Bit des Schlüssels durchsucht wurden (das Parity-
     Bit wird bei der Brute-force-Analyse aus Performancegründen ignoriert;
     diese geht aber nur beim DES-Key-Teil des Gesamtschlüssels).
   - Beim Angriff auf den Hashwert einer elektronischen Signatur wurde bisher
     die benötigte Schrittzahl falsch ausgegeben (immer ca. 4,x*10^18).
   - Absturz gefixt, der auftrat, wenn man in den Textoptionen als Alphabet die
     Großbuchstaben plus die kleinen Umlaute definierte und dann die
     Caesar-Verschlüsselung aufrief.
   - Nun kann man in Feldern für Hexeingaben auch Hexfolgen aus dem Clipboard
     korrekt eingeben (wenn markiert, wird nur da eingefügt).
   - Der in der Textanzeige eingestellte Font wird beibehalten, auch wenn man
     zwischendurch in die Hex-Ansicht wechselt.
   - Konflikte mit den Zertifikats-Seriennummer: Bisher wurden die Seriennummern
     fortlaufend vergeben und beim Importieren eines Zertifikats in den
     Schlüsselspeicher wurde nicht geprüft, ob diese Nummer schon vergeben ist.
     Dies konnte dazu führen, dass beim Validieren das falsche Zertifikat benutzt
     wurde.
     Beides ist behoben: Die Nummern werden zufällig erzeugt und beim Import
     weiterer Zertifikate werden die mit Nummern, die schon erzeugt wurden,
     abgelehnt.

- Bei allen DES-basierten Verfahren wird nun sowohl die effektiv genutzte als
  auch die einzugebende Schlüssellänge angezeigt.

- Viele kleine Verbesserungen in den Masken, z.B. Elapsed-Time-Anzeige beim
  AKS-Test; der Text in der Aboutbox kann markiert und kopiert werden; sofortige
  Anzeige der Zeit und der Anzahl der bisherigen Faktoren bei der Faktorisierung.

- Auch externe PDFs können nun direkt aus der Onlinehilfe aufgerufen werden.

- Alle acht verfügbaren Hashverfahren werden nun angeboten in den Masken für:
  - Schlüssel aus Passwort generieren (nach PKSC #5),
  - Generieren eines Hashed Message Authentication Code (HMAC),
  - Generieren des Hashwertes einer Datei.
  Die Hash-Demo wird folgen (hier stehen bisher 6 Hashverfahren zur Auswahl).

- Im HMAC-Dialog sind die Bezeichnungen der Literatur angepasst und in der 
  Onlinehilfe sind nun die entsprechenden Quellen angegeben.
  Variante 5 der HMAC-Beispiel-Konstruktionen entspricht nun genau dem RFC 2104.
  Details:
  In CrypTool sind fünf HMAC-Varianten implementiert (H = Hash-Funktion,
  k = Schlüssel, m = Nachricht):
  1.  H ( k, m )
  2.  H ( m, k )
  3.  H ( k, m, k )
  4.  H ( k, m, k' )
  5.  H ( k , H (k, m) )
  Nur Variante 5 ist in einem Standard (RFC 2104, FIPS PUB 198) spezifiziert.
  Dieser HMAC berechnet sich wie folgt: H ( k XOR opad, H(k XOR ipad, m) )
  mit ipad = 64 Bytes je 0x36, opad = 64 Bytes je 0x5C.
  Falls der Schlüssel k länger als die Blocklänge der Hash-Funktion ist,
  wird k durch H(k) ersetzt.
  Alle diese Funktionen sind mit Hilfe von OpenSSL implementiert.

- Beim PKCS #5-Dialog können nun bis zu 100.000 Iterationen eingestellt werden.
  Außerdem werden mehr Hashverfahren unterstützt, als der ursprüngliche
  Standard vorsieht.

- Die klassischen Transpositions-Chiffren Skytale und Gartenzaun hinzugefügt
  (angeboten innerhalb eines Dialogs) incl. Schlüssel anzeigen und
  Schlüssel einfügen per Ikone.

- Die Permutationsverschlüsselung kann nun auch auf Hexdateien angewandt
  werden.

- Das Lernprogramm/Lernspiel "Zahlenhai" in der Version 1.1.6 wurde etwas
  korrigiert und vor allem wurde die Onlinehilfe erweitert.

- Wenn sich im Dialog Primzahltest ergibt, dass die zu testende Zahl
  NICHT prim ist, kann per Button direkt zum Faktorisierungsdialog
  gesprungen werden.

- Bis 1.4.21 wurden mit der Maske "Primzahlen generieren" zwei zufällig
  gewählte Primzahl innerhalb eines vordefinierten Bereichs erzeugt.
  Nun kann man damit auch alle Primzahlen innerhalb eines vorgegebenen
  Bereiches ausgeben (Primzahlmenge generieren).

- Die Checkbox "Sonderzeichen" in der Dialogbox "Textoptionen" bietet nun
  standardmäßig mehr Sonderzeichen an.

- Alle spezifischen Optionen befinden sich nun in den Dialogen der zugehörigen
  Methoden. Somit konnten wir den Menüeintrag "Weitere Optionen" entfernen.

- Eine Visualisierung der Abläufe bei sicherer E-Mail kam hinzu: Der Benutzer
  kann Daten eingeben, die signiert oder verschlüsselt werden mit Hilfe des
  S/MIME-Protokolls.

- Eine weitere Visualisierung des AES-Algorithmus kam hinzu: Flussvisualisierung
  zur Veranschaulichung der Veränderung der Bits nach jeder Runde.

- Für die einfache Spaltentransposition ist eine Known-Plaintext-Analyse
  zum Finden des Transpositionsschlüssels neu hinzugekommen.
  Diese Known-Plaintext-Analyse wurde zusammen mit der bisherigen
  Known-Plaintext-Analyse für Hill besser integriert.

- Weitere Vigenère-Analyse (nach Schrödel, für sehr kurze Chiffrate). xxxxxxxx
xxxxxxxxxxxxxxxxxxxxx




3. Beschränkungen und Voraussetzungen
   ----------------------------------

3.1. Anwendungsbereich dieser Lern-, Trainings- und Awareness-Software
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

Der Rootschlüssel der in CrypTool 1.4.30 eingebauten CA hat eine Länge
von 2048 Bit und ist 20 Jahre gültig (06.07.2006 - 06.07.2026).
Zertifikate, die mit dem alten Rootkey aus früheren CrypTool-Versionen
(1.3.05 und älter) ausgestellt wurden, können nicht in Version 1.4.30
importiert werden.

Beachten Sie also beim Umgang mit Zertifikaten, dass jedes CrypTool-
Programm eine Root-CA mit demselben Schlüsselpaar beinhaltet, mit 
der die im Programm erzeugten User-Zertifikate signiert werden. 
D.h. jeder (!), der CrypTool einsetzt, kann User-Zertifikate mit 
dieser eingebauten CA signieren.

Professionelle PKI-Software wie z.B. die OpenXPKI, die FlexiTRUST von
FlexSecure, Entrust, die Secude-CA oder die Microsoft-CA managen zusätzlich
den ganzen Lebenszyklus von Zertifikaten, bieten CRL-Handling, sorgen für
eindeutige Seriennummern und nutzen definierte Registrierungsprozesse.

Die in CrypTool vorhandenen modernen Krypto-Verfahren sind entsprechend
den internationalen Standards implementiert und genauso "gut" wie in
kommerziellen Anwendungen.


3.2. Win32-Umgebung, Rechte bei Installation und Betrieb, Java-Runtime
     -----------------------------------------------------------------
CrypTool erfordert eine Win32-Umgebung.
CrypTool 1.4.30 ist geschrieben für die Betriebssysteme Windows XP
und Windows Vista.

Einige Funktionen (ANIMAL, ECC-Demo) erfordern zusätzlich eine Java
Runtime-Umgebung JRE (>=1.5).

Die minimale Rechnerausstattung liegt bei 300 MHz CPU, 256 MByte RAM,
100 MByte Festplattenplatz (geringe Anforderungen).

Verschiedene Sprachversionen von CrypTool kann man parallel auf einem
Rechner installieren.

Verschiedene Benutzer können am gleichen PC jeweils verschiedene
Einstellungen haben (da persistente Einstellungen im Nutzer-lokalen Teil
der Registry abgelegt werden).

Weder für die Installation noch für die Benutzung sind Administrator-
Rechte notwendig:
- Bei der Installation werden persistente Daten an ff. Stellen abgelegt, für
  die der Installierende Schreibrechte haben muss:
  - für das CrypTool-Verzeichnis,
  - für den Benutzer-spezifischen Bereich der Windows-Registry.
- Bei der Benutzung braucht man Schreibrechte für:
  - Dateien im CrypTool-Verzeichnis PSE (für das PKI-Schlüsselmanagement),
  - Dateien im Nutzer-spezifischen TEMP-Verzeichnis (zur Ablage temporärer
    Dateien),
  - Einstellungen in seinem Benutzer-spezifischen Teil der Registry.

Anmerkung 1: Wo das TEMP-Verzeichnis von Windows liegt, kann man sehen,
wenn man in Windows-Explorer %TEMP% eingibt. Den Wert kann man unter
Windows XP auch ansehen und anpassen per "System --> Systemeigenschaften
--> Reiter Erweitert --> Umgebungsvariablen".
Oder indem man auf der Kommandozeile "echo %TEMP%" eingibt.

Anmerkung 2 -- Details zu den Zugriffsrechten:
a) Programm-Verzeichnis:
   Für einen erfolgreichen Installationsvorgang muss das vom Benutzer
   gewählte Installationsverzeichnis während der Installation beschreibbar
   sein.
   Für die zwei Unterverzeichnisse des Installationsverzeichnisses ("pse"
   und "examples") erhalten alle Benutzter der Gruppe "Users" Schreibrechte.
b) Windows-Registry:
   Um die Datei-Endungen .aes etc. für das Programm AES-Tool zu reservieren
   muss der folgende Teil der Registry während der Installation beschreibbar
   sein:
   HKEY_CLASSES_ROOT
   HKEY_CLASSES_ROOT\Applications

   CrypTool wird in der Liste der installierten Anwendungen (System ->
   Software) nur aufgeführt, wenn der folgende Registry-Eintrag beschreibbar
   ist:
   HKEY_LOCAL_MACHINE\Software\Microsoft\Windows\CurrentVersion\Uninstall

c) Startmenü:
   CrypTool wird im Startmenü für alle Benutzer eingetragen, wenn das 
   folgende Verzeichnis während der Installation beschreibbar ist:
   %allusersprofile%\Startmenü\Programme
   Wenn dieses Verzeichnis nicht beschreibbar ist, wird CrypTool eingetragen
   unter:
   %userprofile%\Startmenü\Programs.


3.3. Interaktive Online-Hilfe unter Windows XP
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


3.4. Unterstützung verschiedener Sprachen
     ------------------------------------
Programm, Hilfesystem und Dokumentation sind mehrsprachig aus-
gelegt (zur Zeit komplett englisch und deutsch).

In der polnischen und der spanischer Version ist das Programm inklusive
aller Masken und Menüs übersetzt. Die PDF-Dateien sind noch in Englisch.
In der polnischen Version ist auch die umfangreiche Onlinehilfe übersetzt;
in der spanischen Version liegt die englische Onlinehilfe bei.

Für jede unterstützte Sprache gibt es bei CrypTool 1.4.30 ein eigenes
Installationsprogramm (Setup).


3.5. Einschränkungen / Features
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
  Explorer (IE) auf. Version IE 6 hat manchmal Probleme, mathematische
  Zeichen wie die Gauß-Klammer darzustellen.
  Wenn bei Ihnen der IE7 voreingestellt ist, funktioniert es korrekt.
  Die zugrunde liegenden, in das CHM-File eingebundenen HTML-Dateien
  werden von IE7 und Firefox 1.5 und höher korrekt dargestellt.
  Die Gauß-Klammer wird in der Onlinehilfe zum Modulo-Operator als
  Symbol für die nächstniedrigere ganze Zahl verwendet.

- Aus Performancegründen wurde festgelegt, dass CrypTool bei der
  N-Gramm-Analyse die Länge der Dokumente beschränkt:
   - für Binärdateien auf 64 kBytes und
   - für Textdateien auf 256 kBytes.
  Werden längere Dateien geöffnet, werden sie -- nur bei dieser Art
  der Analyse -- auf die Maximal-Länge gekürzt.

- Hashwerte können von Dateien beliebiger Größe berechnet werden,
  sofern die Dateien nicht geladen werden. 

- Mit dem AES-Tool können nur Dateien bis 4 GB Größe verschlüsselt
  und als selbstextrahierende Archive abgespeichert werden.
  Erzeugt man nur die rein verschlüsselte AES-Datei ohne Selbstent-
  packungscode kann man auch "beliebig" große Dateien verschlüsseln.

  Bitte beachten Sie, dass die Ausgabe des Standalone AES-Tools nicht
  vollkommen identisch ist mit der Ausgabe, die Sie in CrypTool mit der 
  Menüfolge "Ver/Entschlüsseln \ Symmetrisch (modern) \ Rijndael (AES)"
  erhalten (auch nicht, wenn das AES-Tool eine Datei mit der Endung "aes"
  erzeugt). CrypTool selbst verwendet z.Zt. einen festen IV (0), der nicht 
  gespeichert wird. AES-Tool nutzt einen zufälligen IV und fügt diesen 
  zusammen mit dem Dateinamen hinter den verschlüsselten Daten an.


3.6. Mit älteren CrypTool-Versionen erzeugte Zertifikate und Schlüssel
     -----------------------------------------------------------------
Vergleichen Sie Kapitel 4.1, wo das Verhalten bei der Installation
beschrieben wird.



4. Installation / Deinstallation / Schlüsselnutzung / Betrieb
   ----------------------------------------------------------

4.1. Installation
     ------------
Sie installieren CrypTool, indem Sie das CrypTool-Setup-Programm an
einer geeigneten Stelle im Dateibaum auf Ihrem PC aufrufen.
Standardmäßig wird CrypTool dann in das Verzeichnis 
            "C:\Programme\CrypTool"
installiert. Das Zielverzeichnis kann in der Installationsroutine
geändert werden. Sie müssen Zugriffsrechte für das Zielverzeichnis haben.

Wenn Sie es als Administrator in "C:\Programme\CrypTool" installieren,
können Sie CrypTool danach trotzdem als normaler Benutzer ausführen.

Wenn Sie den Zielverzeichnis-Namen "CrypTool" ändern, z.B. in
"CrypTool-1.4.30-Final-D", so wird auch der Eintrag im Startmenü
der Windows-Taskleiste entsprechend geändert.


4.2. Deinstallation von CrypTool
     ---------------------------
Um CrypTool zu deinstallieren, benutzen Sie bitte das "Start"-Menu in
der Windows-Taskleiste.
Dort gehen Sie zu "Alle Programme" \ "CrypTool".
Dann klicken Sie auf "CrypTool deinstallieren".

Manchmal kann es sein, dass die JAR-Dateien nicht gelöscht werden können,
da Windows und die JRE melden, dass die Datei noch benutzt wird, obwohl
CrypTool samt aller Stand-alone-Programme beendet wurde.
Nach einem Neustart des Rechners kann man dann die JAR-Datei und das ganze
Verzeichnis löschen.


4.3. Wiederholte Nutzung von Schlüsseln
     ----------------------------------

4.3.1. Schlüssel aus vorherigen Versionen
       ----------------------------------
Besitzen Sie bereits eine frühere Version von CrypTool, so versucht das
Installationsprogramm, vor der erneuten Installation das alte CrypTool
zu deinstallieren.
Bitte beachten Sie:
- Wenn bei der Deinstallation nicht alle Verzeichnisse/Dateien im
  Programmverzeichnis (meist "C:\Programme\CrypTool") gelöscht
  werden, löschen Sie diese manuell.
- Bei der Deinstallation von CrypTool werden alle bisher erzeugten
  asymmetrischen Schlüssel und Zertifikate gelöscht.

  Wenn Sie diese Schlüssel und Zertifikate auch in der neuen Version von
  CrypTool nutzen wollen, gibt es 2 Möglichkeiten:
  a) Import aus einer alten CrypTool-Version (VOR 1.4.00):
     - Für RSA- und DSA-Schlüssel:
       Exportieren Sie diese PSEs mit Hilfe des alten CrypTools in ein
       PKCS#12-Format und importieren Sie diese Dateien im neuen CrypTool.
     - Für ECC-Schlüssel:
       Hier reicht es, die entsprechenden Dateien 
       (z.B. [da][db][EC-prime239v1][1131039030][d] )
       vom alten CrypTool\pse-Verzeichnis in das neue Verzeichnis zu
       kopieren.
  b) Alternativ, aus einer alten CrypTool-Versionen ab 1.4.00:
     Sichern Sie VOR der Deinstallation das unter dem Programmverzeichnis
     liegende Verzeichnis pse\ mit allen darin gespeicherten Dateien
     in ein anderes Verzeichnis. Alle Dateien darin können Sie dann nach
     Installation der neuen Version von CrypTool in das neue pse\-Programm-
     verzeichnis kopieren.

Für den Fall, dass mehrere Benutzer dieselbe CrypTool-Installation
verwenden wollen, müssen die Zugriffsrechte auf den Verzeichnissen
pse\ und pse\pseca\ und den darin enthaltenen
Dateien für alle Benutzer auf Vollzugriff gesetzt werden.

Der Teilbaum "pse\" sollte nicht manuell bearbeitet werden, da
bei einer inkonsistenten Struktur nur eine Neuinstallation von
CrypTool bleibt, um die zertifikatsbasierten Verfahren zu nutzen.


4.3.2. Schlüssel gespeichert in den Dateien des PSE-Verzeichnisses
       -----------------------------------------------------------
Die im Menü "PKI" erzeugten Schlüssel für die Verfahren RSA und ECC liegen
im PSE-Verzeichnis (die Schlüssel der klassischen Verfahren werden nicht
dauerhaft abgelegt).
Ab Version 1.4.20 wird als PSE-Verzeichnis ein Nutzer-spezifisches Verzeichnis
verwendet (nicht das eigentliche Installationsverzeichnis), um Rechteprobleme
in Mehrbenutzerumgebungen zu vermeiden.
CrypTool greift so standardmäßig auf asymmetrische Schlüssel und Zertifikate
im Daten-Anwendungs-Verzeichnis des Nutzers zu. Das heißt, wenn ein Benutzer
CrypTool das erste Mal aufruft, wird dieses Verzeichnis anhand der Umgebungs-
variablen APPDATA bestimmt, und das CrypTool-Programm-Verzeichnis pse\ wird
mit allen enthaltenen Schlüsseln und Zertifikaten in das Benutzer-Anwendungs-
Verzeichnis kopiert. Die Nutzer-individuellen Schlüssel und Zertifikate
bieten die Vorteile, dass
- auf das Programmverzeichnis nicht mehr schreibend zugegriffen werden muss,
- die meisten Lese- und Schreibrechtprobleme beim Betrieb in Mehrbenutzer-
  systemen gelöst sind [siehe Abschnitt 4.5.b)], und
- bei einer Neu-Installation die Nutzer-individuellen Schlüssel nicht mehr 
  automatisch überschrieben werden.  

Sie können das frühere Verhalten erzwingen, wenn Sie den Registry-Eintrag
HKEY_CURRENT_USER\Software\CrypTool\Settings\UserKeyStore\UseUserKeyStore
auf den Wert ‘0’ setzen (diese Registry-Variable ist nach dem ersten Auf-
ruf von CrypTool sichtbar).



4.4. Installation in Mehrbenutzersystemen
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


4.5. Betrieb in Mehrbenutzersystemen
     -------------------------------
a) Alle Benutzer-spezifischen Einstellungen (z.B. Optionen für Algorithmen,
   die Sie während der Benutzung änderten) werden in der lokalen, Nutzer-
   spezifischen Registry gespeichert (auch die zuletzt geöffneten Dateien).
 
b) Will der Benutzer in Mehrbenutzersystemen wie Windows XP aus CrypTool
   heraus Dateien anlegen (bzw. ändern), braucht er Schreibrechte auf das
   entsprechende Zielverzeichnis (bzw. auf die entsprechende Datei). 
   Geht das nicht, kommt eine Warnung.
   Explizit nötig sind Schreibrechte nur auf 2 Verzeichnisse:
   - das Standard-Windows-Verzeichnis für temporäre Dateien (TEMP)
     für die cry*.*-Dateien,
   - das Unterverzeichnis "CrypTool\pse", da darin die erzeugten 
     asymmetrischen Zertifikate und Schlüssel abgelegt werden.

4.6. Installation auf einem Netzwerk-Laufwerk --> Onlinehilfe-Problem
     ----------------------------------------------------------------
   Besonders in Schulen wird Lern-Software oft nur auf dem zentralen
   Rechner, z.B. auf einem Windows-Netzwerkrechner installiert; die
   Client-PCs rufen dann das Programm von dort auf.

   Das Programm CrypTool selbst läuft so auch. Wird aber die Onlinehilfe von
   einem Client-PC aus aufgerufen, wird sie mit den Standardeinstellungen
   des Windows XP-Betriebssystems nicht angezeigt. Das ist kein CrypTool-
   spezifisches Problem, sondern eines aller Windows-Onlinehilfe-Dateien.
   Die HTML-Hilfe zeigt dann normalerweise nur das Inhaltsverzeichnis oder
   den Index, aber nicht die Inhalte der Seiten.

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

   ABHILFE:
   Da das Deinstallieren von Sicherheits-Patches keine gute Idee ist, und
   da es in diesem Szenario auch nicht gewünscht ist, die CHM-Dateien lokal
   zu installieren, kann man einen bestimmten Eintrag in der Registry
   hinzufügen bzw. ändern:

   Wir nehmen an, dass die CHM-Dateien in "X:\program\CrypTool" liegen,
   wobei "X" ein Netzlaufwerk mit dem UNC-Pfad "\\server\user" ist.
   Somit wäre der vollständige UNC-Pfad zu den CHM-Dateien:
   "\\server\user\program\CrypTool".

   Rufen Sie den Registrierungs-Editor auf (Start > Run... > "regedit") und
   navigieren Sie zu "HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\HTMLHelp\1.x".
   Dort erstellen Sie einen neuen Schlüssel "ItssRestrictions",
   in welchem Sie danach eine neue Zeichenfolge "UrlAllowList" mit dem Wert
   "\\server\user\program\CrypTool;file://\\server\user\program\CrypTool;
   X:\program\CrypTool;file://X:\program\CrypTool" erstellt wird.

   Indem man in der Registry aller Client-PCs diesen Eintrag aufnimmt,
   haben alle Client-PCs Zugriff auf das Server-Laufwerk.

   ACHTUNG:
   Generell kann das Bearbeiten der Registry dazu führen, dass Windows
   nicht mehr funktioniert. Die Verantwortung für diese Änderung liegt
   allein bei Ihnen!
   Um auf einem Client-PC die Registry zu ändern, braucht man
   möglicherweise Administratorrechte.

   Weitere Infos: 
    - http://support.microsoft.com/kb/896054
    - http://www.robo-forum.de/cgi-bin/ultimatebb.cgi?ubb=get_topic;f=20;t=000065



5. Liste der Dateien in der Auslieferung
   -------------------------------------
CrypTool wird als komprimiertes, selbstextrahierendes Archiv in
drei verschiedenen Sprachversionen verteilt:

SetupCrypTool_1_4_30_en.exe    Englische Sprachversion.
SetupCrypTool_1_4_30_de.exe    Deutsche Sprachversion.
Die mit der Polnischen und Spanischen Version zusätzlich ausgelieferten
Dateien sind hier noch nicht berücksichtigt.

Diese selbstextrahierenden Archive enthalten die folgenden Dateien:

ReadMe-de.txt .... Diese Kurzanleitung (deutsch).
ReadMe-en.txt .... Diese Kurzanleitung (englisch).

md5sum.txt ....... MD5-Hashwerte aller Dateien innerhalb des CrypTool-Paketes
sha1sum.txt ...... SHA-1-Hashwerte aller dieser Dateien.

CrypTool.exe ..... Das E-Learning-Programm (deutsch + englisch).
aestool.exe ...... Ein Programm, das Dateien in sich selbst-entpackende
                   Programme verschlüsselt (D + E). Zur Entschlüsselung
                   müssen Sie das korrekte Passwort eingeben.
CrypTool-de.chm .. HTML-Hilfe-Archiv für die CrypTool-Onlinehilfe in
                   deutsch.
CrypTool-en.chm .. Die englische Version von "CrypTool-de.chm".

EC-Param.ini ..... Initialisierungsdatei für auf Elliptischen
                   Kurven basierende Public-Key-Verfahren.
TEST-Param.ini ... Initialisierungsdatei für die Zufallstests.
secude.dll ....... Bibliothek kryptographischer Funktionen von der
                   Secude IT Security GmbH.
ticket ........... Lizenz für die Secude-Bibliothek.
libxml2.dll ...... Wird benötigt von der secude.dll.
secidea.dll ...... Wird benötigt von der secude.dll für die 
                   IDEA-Verschlüsselung.
srndmskb.dll ..... Wird benötigt von der secude.dll für den
                   Entropie-Sammler zur Initialisierung des
                   Secude-Zufallsgenerators.
db.dll ........... Wird benötigt von der secude.dll.
secude.xml ....... Wird benötigt von der secude.dll.
libeay32.dll...... Bibliothek aus OpenSSL.
SciLexer.dll ..... Bibliothek mit den Routinen für den
                   Scintilla-Texteditor.
cracklib_Win32.dll .. Unterstützt die PQM-Tests.

Rijndael-Animation.exe .. Animation (Flash) des AES-Algorithmus.
Rijndael-Inspector.exe .. Animation (Flash) zu den Änderungen des
                          Datenblocks innerhalb des AES-Algorithmus.
Enigma_de.exe .... Animation (Flash) der 3-Rotor Enigma-Maschine.
Enigma_en.exe .... Die englische Version von "Enigma_de.exe".
Enigma-Help_de.html .. HTML-Onlinehilfe für  "Enigma_de.exe" (deutsch).
Enigma-Help_en.html .. Die englische Version von "Enigma-Help_de.html".
enigma_screenshot1.png .. Screenshot für die Enigma-Hilfedatei.

eccdemo.jar ...... Demo (Java) zur Punktaddition auf Elliptischen Kurven.

ZT.exe ........... Lernprogramm (Authorware) zur Zahlentheorie.
NT.exe ........... Die englische Version von "ZT.exe".
TextZahlWandler.exe ...... Hilfsprogramm zu "ZT.exe".
TextNumberConverter.exe .. Die englische Version von "TextZahlWandler.exe".
ToolBarWrapper.dll .. Notwendig für das Authorware-Programm ZT.exe

Zahlenhai.exe .... Das Programm zum Lernspiel "Der Zahlenhai".
NumberShark.exe .. Die englische Version von "Zahlenhai.exe".
NumberShark_de.chm HTML-Hilfe-Archiv für die Zahlenhai-Onlinehilfe (deutsch).
NumberShark_en.chm Die englische Version von "NumberShark_de.chm".
GameData.txt ..... Die ersten High-Scores für das Zahlenhai-Spiel.

script-de.pdf .... Ein Skript (deutsch) über Kryptographie, Primzahlen,
                   elementare Zahlentheorie und die Mathematik hinter
                   einigen Algorithmen.
script-en.pdf .... Die englische Fassung von script-de.pdf.

CrypToolPresentation_1_4_30_de.pdf .. Folien-Präsentation (deutsch)
CrypToolPresentation_1_4_30_en.pdf .. Folien-Präsentation (englisch)

DialogSchwestern.pdf .. Fantasy-Geschichte von Dr. Elsner, in der
                        eine Variante des RSA-Kryptosystems
                        beschrieben wird.
DialogueSisters.pdf ... Englische Fassung von DialogSchwestern.pdf.
rijndael-poster-a4.pdf ... Darstellung der Abläufe beim AES-Algorithmus.
ChinLab-de.pdf ... Geschichte von Dr. Elsner über zahlentheoretische
                   Probleme, die Marco Polo vom Großen Khan gestellt
                   werden.
ChinLab-en.pdf ... Englische Fassung von ChinLab-de.pdf.

Uninstall.exe .... Teil des NSIS-Installers.
license-de.rtf ... Benutzt vom Installationsprogramm. 
license-en.rtf ... Englische Fassung von license-de.rtf. 


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
                            "Rijndael-Animation.exe",
                            verarbeitet mit "CrypTool.exe". 



cryptochallenges\ ... Dieses Verzeichnis enthält Dateien mit Chiffraten.
                      Die meisten sind historischer Natur, einige davon
                      sind ungelöst.
                      Zwei Herausforderungen sind auch dabei: die
                      Doppelwürfel-Chiffre und die HarryPotter-Chiffre.

cryptochallenges\Schmeh01-Dorabella-enc.txt
                 Schmeh02-Agapeyeff-enc.txt
                 Schmeh03a-Feynman-enc.txt
                 Schmeh03b-Feynman-enc.txt
                 Schmeh03c-Feynman-enc.txt
                 Schmeh04a-Kryptos-enc.txt
                 Schmeh04b-Kryptos-enc.txt
                 Schmeh04c-Kryptos-enc.txt
                 Schmeh04d-Kryptos-enc.txt
                 Schmeh05-Doppelwuerfel-enc.txt
                 Schmeh06-SherlockHolmes-enc.txt
                 Schmeh07-HarryPotter-enc.txt
                 Schmeh08-MathiasSandorf-enc.txt



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


words\ ........... In diesem Verzeichnis liegen die Dateien, mit
                   denen die Tests auf Passwortmuster gemacht werden.

words\cracklib-words
      cracklib_dict.hwm
      cracklib_dict.pwd
      cracklib_dict.pwi


pse\ ............. In diesem Verzeichnis und in seinem
                   Unterverzeichnis pseca\ werden erzeugte
                   (asymmetrische) Schlüssel und Zertifikate abgelegt.

pse\[SideChannelAttack][Bob][RSA-512][1152179494][PIN=1234].pse
    [HybridEncryption][Bob][EC-prime239v1][1178702474][PIN=1234]
    [HybridEncryption][Bob][EC-prime239v1][1178702474][PIN=1234].pse

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

animal\Animal-2.3.14.jar
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
  \BCmin.bat
  \bruch.txt
  \calc.txt
  \dislog.txt
  \ECM.TXT
  \pi.txt
  \polynom.txt
  \Prims.txt
  \quadRest.txt
  \res.txt
  \RSA.txt
  \seed
  \sieb.txt
  \testBruch.bat
  \testPi.bat
  \testPolynom.bat
  \testRSA.bat
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
       Diese Dateien haben folgende Endungen: 
                  txt -> Textdatei-Ansicht
                  hex -> Hexadezimale (binäre) Ansicht
                  plt -> Diagramm/Plot-Ansicht (Histogramm, Autokorrelation)
                  ogl -> OpenGL-Graphics-Ansicht
                  org -> Kopie der Originaldatei nach dem Laden
                  tmp -> Temporäre Datei für Zwischenberechnungen
xxxxxxxxxxxx


5.1. Überprüfen der Integrität der heruntergeladenen Dateien
     -------------------------------------------------------
Die Integrität von Dateien kann mit Hashwerten überprüft werden.
Hashwerte sind wie Fingerabdrücke -- mit einer sehr geringen
Informationsmenge kann man ein viel größeres Objekt identifizieren.

Die Dateien vom CrypTool-Projekt kommen normalerweise dadurch auf
Ihren Computer, dass das Archiv (Setup-Datei) heruntergeladen und
die darin enthaltenen Dateien entpackt werden:
a) Herunter ladbare Dateien:
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
   Deren Hashwerte stehen in den Dateien md5sum.txt bzw. sha1sum.txt,
   die als Teil des Paketes mit entpackt werden.

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



6. Kurze Historie der freigegebenen Hauptversionen
   -----------------------------------------------

Version   Datum         Größe des Windows-Setups  Plattenplatz  Freigabe
                         Deutsch    Englisch      Bedarf        durch
1.0.01    Okt. 1999       1,3 MB      -              -            DB
1.1.01    Mai  2000       2,3 MB      -              -            DB
1.2.00    Aug. 2000       2,8 MB      -              -            DB
1.2.02    Dez. 2000       3,2 MB      -              -            DB
1.3.00    Jan. 2002       4,9 MB      4,7 MB         -            DB
1.3.02    Juni 2002       6,9 MB      6,4 MB         -            DB
1.3.03    Sep. 2002       6,9 MB      6,5 MB         -            DB
1.3.04    Juli 2003       8,6 MB      8,1 MB         -            DB
1.3.05    Aug. 2003       8,6 MB      8,1 MB         -            DB
1.4.00    Juli 2006      18,4 MB     18,2 MB         -            DB
1.4.10    Juli 2007      27,5 MB     26,7 MB         47 MB        DB
1.4.20    Juli 2008      37,1 MB     36,1 MB         74 MB        DB
1.4.21    Juli 2008      37,1 MB     36,1 MB         74 MB        DB
1.4.30    Juli 2009      42,5 MB     41,6 MB         79 MB        DB   xxxxxxxx

Bemerkungen zu den Versionen:
1.3.02   Viele neue Funktionen gegenüber 1.3.00.
1.3.03   Viele kleine Bugfixes und Verbesserungen der Dokumentation.
1.3.04   Etliche neue Funktionalität, einige kleine Bugfixes, und Verbes-
         serung und Erweiterung der Dokumentation (Online-Hilfe, Skript).
1.3.05   Kleine Bugfixes.
1.4.00-Beta10  Dez. 2005  Erste öffentliche Beta von Version 1.4.00.
1.4.00-Beta12  März 2006  Zweite öffentliche Beta von Version 1.4.00.
1.4.00-Beta14  Juli 2006  Dritte öffentliche Beta von Version 1.4.00.
1.4.00   Viele neue Funktionen gegenüber 1.3.05.
1.4.10-Beta04  Mai  2007  Erste öffentliche Beta von Version 1.4.10.
1.4.10-Beta06  Juli 2007  Zweite öffentliche Beta von Version 1.4.10.
1.4.10   Funktionsumfang und Onlinehilfe stark erweitert i.Vgl. zu 1.4.00.
1.4.20-Beta03  Mai  2008  Erste öffentliche Beta von Version 1.4.20.
1.4.20   Funktionsumfang und Onlinehilfe erweitert i.Vgl. zu 1.4.10;
         Vor allem Feinschliff und Code stabilisiert (Qualitätsrelease).
1.4.21   Patch, das auch die MSVCR71.dll enthält, da diese Datei von der
         neuen aktuellen OpenSSL-Bibliothek benutzt wird und nicht auf
         frischen Windows-Umgebungen (ohne Office) enthalten ist.
1.4.30-Beta03  März 2009  Erste öffentliche Beta von Version 1.4.30.
1.4.30-Beta04  Juli 2009  Zweite öffentliche Beta von Version 1.4.30.
1.4.30   Viele Bugfixes und erweiterter Funktionsumfang i.Vgl. zu 1.4.21.



7. Feedback und Kontaktadressen
   ----------------------------
Sollten Sie Probleme haben oder Fehler finden, wenden Sie sich
bitte mit einer ausführlichen Beschreibung des Problems (und einigen
Bildschirmbildern dazu) per E-Mail an eine hier genannten Personen.

Für Anregungen jeglicher Art bezüglich CrypTool sind wir immer
dankbar und helfen Ihnen gern, wenn es unsere Zeit erlaubt.

Auch würden wir uns freuen, wenn Sie uns mitteilen, wie und wo Sie
CrypTool einsetzen.

Kontaktadressen:
- esslinger@fb5.uni-siegen.de
- joerg-cornelius.schneider@db.com
- henrik.koy@db.com



8. Verweise / Auszeichnungen
   -------------------------

8.1. Artikel über CrypTool
     ---------------------
8.1.1. c't 14/2001
       -----------
In diesem renommierten und auflagenstarken deutsch-sprachigen
Computermagazin wurde im Juli 2001 ein 5-seitiger Artikel zu
CrypTool veröffentlicht (S. 204-208).

8.1.2. DuD Oktober 2002
       ----------------
In der deutsch-sprachigen Fachzeitschrift "DuD Datenschutz und
Datensicherheit", Ausgabe 10/2002 erschien unter dem Titel
"CrypTool - spielerischer Einstieg in klassische und moderne
Kryptographie. Neue Version - fundierte Awareness in Deutsch
und Englisch" ein 4-seitiger Artikel über CrypTool.

8.1.3. KES 2/2003 (Mai 2003)
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

8.1.4. Tagungsband 8. Deutscher IT-Sicherheitskongress des BSI (Mai 2003)
       ------------------------------------------------------------------
Auf dem BSI-Kongress 2003 in Bonn wurde von Hr. Koy der Vortrag
"Awareness in der Informationsgesellschaft: CrypTool - Kryptographie
spielerisch verstehen" gehalten. Die Textfassung dazu steht im 
Tagungsband, "IT-Sicherheit im verteilten Chaos", auf S. 485 - 500.

8.1.5. Datenschutz PRAXIS (Juni 2005)
       ------------------------------
In der deutsch-sprachigen Fachzeitschrift "Datenschutz PRAXIS",
Ausgabe Juni 2005 erschien unter dem Titel "Spielend verschlüsseln lernen
mit dem kostenlosen CrypTool" ein 2-seitiger Artikel über CrypTool von
Dr. Rainer W. Gerling.
Diesen Artikel finden Sie im Internet unter
http://www.lrz-muenchen.de/~rgerling/pdf/DatenschutzPRAXIS_2005_06_9.pdf.

8.1.6. Report Touch Briefing Information Security (Oktober 2006)
       ---------------------------------------------------------
Der "Touch Briefing Information Security"-Report 2006 enthält den Artikel
"The CrypTool Project -- Improving Awareness and Education for Cryptology".
Abrufbar im Internet unter:
  http://www.touchbriefings.com/pdf/2259/esslinger.pdf
Mit den Suchbegriffen "awareness cryptology" listeten danach sowohl
google.de wie google.com diesen Artikel auf Platz 1. 

8.1.7. DFN-Mitteilungen, Heft 73 (Dezember 2007)
       ---------------------------------------------------------
Diese Mitteilungen des Deutschen Forschungsnetzes (DFN) enthalten den
4-seitigen Artikel "CrypTool -- Ein E-Learning-Programm für Kryptologie".
Abrufbar im Internet unter:
  http://www.dfn.de/fileadmin/5Presse/DFNMitteilungen/heft73.pdf

8.1.8. KES 3/2008 (Juli 2008)
       ----------------------
In der deutsch-sprachigen Fachzeitschrift "KES - Zeitschrift für
Informations-Sicherheit", Ausgabe 3/2008 erschien unter dem Titel
"(Ver)Schlüsselerlebnisse NG" ein 3 1/3-seitiger Artikel zum
10-jährigen Jubiläum von CrypTool und zu den neuen Versionen.

8.1.9. Telepolis 8/2008 (August 2008)
       ------------------------------
Ein Artikel von Klaus Schmeh über CrypTool erschien unter dem Titel
"Werkzeugkasten für Codeknacker" in dem Online-Magazin Telepolis.
http://www.heise.de/tp/r4/artikel/28/28389/1.html

8.1.10. Eclipse Magazin 4/2008 (Oktober 2008)
        --------------------------------------
Ein Artikel von Dominik Schadow über JCrypTool erschien unter dem Titel
"JCrypTool: Kryptisch gesagt..." im "Eclipse Magazin".
Dieser Artikel kann als freier Reprint herunter geladen werden von:
http://www.trivadis.com/fileadmin/user_upload/PDFs/Trivadis_in_der_Presse/EclipseMagazin_Kryptisch_gesagt_Schadow.pdf

8.1.11. ep-Elektropraktiker Januar 2009
        -------------------------------
In der deutsch-sprachigen Fachzeitschrift "ep-Elektropraktiker", Ausgabe 01/2009 erschien unter dem Titel "CrypTool - sichere Kommunikation" ein 2-seitiger
Artikel über CrypTool von H. Möbus.
http://www.elektropraktiker.de/download/luk-2009-1-06-46867.html

8.1.12. DuD März 2009
        -------------
In der deutsch-sprachigen Fachzeitschrift "DuD Datenschutz und
Datensicherheit", Ausgabe 03/2009 erschien unter dem Titel
"CrypTool - Ein Open-Source-Projekt in der Praxis. Erfahrungsbericht
eines erfolgreichen Open-Source-Projektes" ein 6-seitiger Artikel über
CrypTool.
Abrufbar im Internet unter:
  http://www.cryptool.org/images/Artikel_in_DuD_%20Maerz2009_Final.pdf



8.2. Sonstige Referenzen auf CrypTool
     --------------------------------
8.2.1. Wirtschaftswoche Spezial (September 2000)
       -----------------------------------------
Das Spezial "Kryptographie" der Zeitschrift Wirtschaftswoche
(Rubrik Netzwelt Sept. 2000) enthielt ein Preisausschreiben:
"Knacken Sie den Text!" unter der URL
http://www.wiwo.de/wiwowwwangebot/fn/ww/sfn/buildww/cn/
cn_artikel/id/62633!100301/SH/0/depot/0/bt/1/index.html.
Wenn man sich an die Tipps der Aufgabenstellung hielt, konnte man
mit CrypTool die Aufgabe mit wenigen Mausklicks lösen.

8.2.2. BSI Bürger-CD "Ins Internet - mit Sicherheit"
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

8.2.3. BSI-Software-Suite BOSS 2.0 (Jan. 2007)
       ---------------------------------------------
Das Bundesamt für Sicherheit in der Informationstechnik (BSI) hat
CrypTool 1.4.00 als Teil der BSI-Software-Suite "BSI OSS Security
Suite 2.0 (BOSS)" mit ausgeliefert.
Siehe http://www.bsi.de/produkte/boss/index.htm


8.2.4. In Fortbildungen / Kursen (Beispiele)
       -------------------------------------
- CISSP, TISP (TeleTrusT Information Security Professional), ...

- http://www.logicalsecurity.com/education/se_PN-CPTS-01.html
  Certified Penetration Testing Specialist (CPTS)

- http://www.careeracademy.com/index.asp?PageAction=VIEWPROD&ProdID=265
  https://www.cccure.com/scp/security-certified-network-professional-scnp-strategic-infrastructure-security-sis-training/prod_11.html
  Security Certified Network Professional (SCNP) - Strategic Infrastructure Security (SIS) Training
  
- http://www.cdachyd.in/cnss/cnss_ebrochure.htm   (Dez. 2008)
  Ein 22-wöchiger Kurs über Netzwerk- und Systemsicherheit (CNSS) angeboten
  von C-DAC Hyderabad, Indien, wo auch CrypTool zum Einsatz kommt.
  Das Centre for Development of Advanced Computing (C-DAC) ist eine
  regierungsnahe Forschungs- und Entwicklungseinrichtung im EDV-Bereich.



8.2.5. Nennungen auf verschiedenen Webseiten
       -------------------------------------

a) Simon Singh hat auf seiner Webseite http://www.simonsingh.net/
   beim Schreiben seines Buches "Geheime Botschaften" (engl. "The
   Code Book") viel Material zur Kryptographie, ihrer Geschichte und
   ihrer Vermittlung zusammengetragen.

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
   mit dem Titel "CrypTool A great tool to learn more about
   cryptography".


c) Wikipedia:
   - Englisch:
     - http://en.wikipedia.org/wiki/CrypTool
     - http://en.wikipedia.org/wiki/Cryptography
     - http://en.wikipedia.org/wiki/Topics_in_Cryptography
   - Deutsch:
     - http://de.wikipedia.org/wiki/CrypTool
     - http://de.wikipedia.org/wiki/Kryptographie
     - http://de.wikipedia.org/wiki/Wikipedia:WikiProjekt_Kryptologie
   - Spanisch:
     - http://es.wikipedia.org/wiki/CrypTool
   - Polnisch:
     - http://pl.wikipedia.org/wiki/CrypTool
     - http://pl.wikipedia.org/wiki/Kryptografia
   - Französisch:
     - http://fr.wikipedia.org/wiki/CrypTool
   - Thailändisch:
     - http://th.wikipedia.org/wiki/CrypTool
   - Italienisch:
     - http://it.wikipedia.org/wiki/CrypTool


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
        (Ressource-Seite zu dem Buch "Cryptography and Network Security",
         4. Auflage von William Stallings)
   ...



8.3. Weitere Freeware-Projekte (Crank, CAP, CryptoStudio, etc.)
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
  Kryptos ist Open-Source-Projekt, das an der George Mason University begann.
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

- http://gcipher.sourceforge.net/
  GCipher ist ein kleines Verschlüsselungsprogramm für Unix, ohne Onlinehilfe
  und ohne Analysefunktionalität. Die drei klassischen Verschlüsselungs-
  verfahren können sowohl von der GUI, von der Kommandozeile wie als
  Netzwerk-Proxy ausgeführt werden.
  Die aktuelle Version 1.0 wurde im Juni 2003 von Shannon -jj Behrens
  veröffentlicht.

- http://www.nku.edu/~mcsc/mat494/uploads/CryptoHelper.jar
  Das Java-Programm CryptoHelper.JAR vom "Math and Computer Science Club"
  an der NKU ist ziemlich komplett, was klassische Chiffren angeht.
  Letzter Update: Gary Watson, 2005.

- http://www.cs.unc.edu/~stotts/145/homes/crypt/
  Cypher, geschrieben in C und FLTK (für Windows und Unix), ist ein
  Toolkit, um die Entschlüsselung klassischer Chiffren zu unterstützen
  mittels statistischer Daten und Verfahren. 
  Es wurde in einem Universitäts-Projekt von 6 (?) Studenten im Jahre
  2000 entwickelt. Die Webseite enthält die Sourcen, aber nicht die
  ausführbaren Dateien.



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

- Die Java-Anwendung CipherClerk von Wilhelm M. Plotz
  (Ver- und Entschlüsselung mit vielen klassischen Verfahren;
  letzter Update 2003)
  http://members.aon.at/cipherclerk/

- CryptoBench - GUI um Teile von Wei Dai's Crypto++ Bibliothek
  Kompakte und übersichtliche GUI zur Nutzung der Kryptofunktionen aus 
  Wei Dai's Crypto++ Bibliothek (keine Kryptoanalyse).
  Die aktuelle Version 1.0.1 der CryptoBench gibt es seit 2004.
  Wei Dai's Crypto++ Bibliothek ist Open Source, die GUI der 
  CryptoBench ist Freeware aber kein Open Source.
  http://www.addario.org/cryptobench/

- "Cryptanalysis Tools" von Steven Kohns
  Das Programm, das für den Kryptographie-Kurs an der NKU (Northern Kentucky
  University) in 2004 entstand, hilft beim Erzeugen und Brechen einfacher
  Chiffren.
  Zur Ausführung unter Windows XP muss man den "Windows 2000 compatibility mode"
  aktivieren.
  Letzter Update: Mai 02, 2004 - Uploaded Cryptanalysis Project
                  Nov 27, 2004 - Version 0.17 (laut Splash Screen)
                               - Version 0.37 (laut help file)
  http://studenthome.nku.edu/~kohuss/content/crypt.html


Falls uns hier etwas entgangen ist, würden wir uns über eine Nachricht
freuen - wir vervollständigen oder korrigieren diese Liste gerne.

Außerdem wollen wir hier ausdrücklich das Angebot machen, die
Anstrengungen für diese einzelnen Programme in ein einziges
Programm zu integrieren. Wir freuen uns über jede Kooperation!!



8.4. Auszeichnungen
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

- Ausgewählter Ort 2008 im Land-der-Ideen
  Das CrypTool-Projekt wurde bei dem bundesweiten Wettbewerb "365 Orte im
  Land der Ideen" in der Kategorie Wissenschaft und Technik ausgewählt.
  Dazu fand am 22.07.08 an der Universität Siegen ein Tag-der-offenen-Tür
  statt.




A. Anhang
   ------

A.1. .... CrypTool unter Linux mit Wine
A.1.1. .... CrypTool installieren
A.1.2. .... Wine-Konfiguration
A.1.3. .... CrypTool ausführen

A.2. .... Neue Funktionen, Roadmap, Nachfolger-Projekte mit Java/Eclipse und C#/.NET
A.2.1. .... Mögliche Punkte für eine Weiterentwicklung -- Ideen, Anfragen
A.2.1.1. .... Funktionalität: Algorithmen / Verfahren
A.2.1.2. .... Funktionalität: Analyse
A.2.1.3. .... Interne Schnittstellen / Editoren
A.2.1.4. .... User-Interface / Visualisierungen
A.2.2. .... Roadmap: Nachfolger-Projekte mit Java/Eclipse und C#/.NET
A.2.2.1. .... Design der Nachfolger-Projekte
A.2.2.2. .... Funktionen, geplant für die Nachfolger-Projekte CT2 und JCT1



A.1. CrypTool unter Linux mit Wine
     -----------------------------
Wir unternehmen keine Anstrengungen, Wine zu unterstützen.
Stattdessen läuft die plattformunabhängige Version JCT auch unter Linux
(siehe Kapitel 3.5).

Die folgenden Hinweise basieren auf Tests mit Wine 0.9.9.

Es wird nicht empfohlen, CrypTool 1.x unter Wine zu nutzen, da viele
Dinge dort nur teilweise richtig funktionieren.

A.1.1. CrypTool installieren
       ---------------------
Im letzten Schritt der Installation gibt es die Option,
CrypTool gleich zu starten. Dies funktioniert unter Wine nicht.
Bitte starten Sie CrypTool wie unten beschrieben.


A.1.2. Wine-Konfiguration
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


A.1.3. CrypTool ausführen
       ------------------

A.1.3.1. Starten
         -------
Um CrypTool zu starten, wechseln Sie in das Verzeichnis, in das
es installiert wurde, und starten es mit:

$ wine CrypTool

Wenn Sie vor dem Aufruf nicht in das Installationsverzeichnis
von CrypTool wechseln, findet CrypTool einige wichtige Dateien
nicht.


A.1.3.2. Bugs und Workarounds
         --------------------
* Die Online-Hilfe kann nicht mit F1 aus CrypTool heraus
  aufgerufen werden.
  Mit der folgenden Kommandozeile können Sie die Online-Hilfe
  anzeigen:

  $ wine winhlp32 CrypTool.hlp





A.2. Neue Funktionen, Roadmap, Nachfolger-Projekte mit Java/Eclipse und C#/.NET
     --------------------------------------------------------------------------
Generell sollen alle größeren Neuerungen ab nun in die beiden
Nachfolger-Projekte einfließen (siehe A.2.2).

In CrypTool 1.x werden weiterhin Fehler behoben bzw. Funktionen von
Mitwirkenden aufgenommen, die weiter in C/C++ implementieren wollen.


A.2.1. Mögliche Punkte für eine Weiterentwicklung -- Ideen, Anfragen
       -------------------------------------------------------------

A.2.1.1. Funktionalität: Algorithmen / Verfahren
         ---------------------------------------
- Weitere Algorithmen zu jedem Thema implementieren:
    * Codes:
       - T9 etc.  (http://de.wikipedia.org/wiki/Text_on_9_keys)
    * Verschlüsselung:
       - Klassische Verfahren (incl. Analyse): z.B.
           - Nihilist
           - Enigma, Sigaba
           - Fleißner-Schablone
           - Weitere Rotorchiffren, Hagelin, Lorenz-Maschine, Purple.
       - Symmetrische Verfahren:
           Camellia (RFC3713), RC5 und Gost (http://vipul.net/gost),
           Radio Gatun, SOSEMANUK, VSH, ...
       - Public-Key-Verfahren: McEliece, Rabin, NTRU.
       - Demonstration der Visuellen Kryptographie
       - Neue Verfahren von Ecrypt (Network of Excellence in Cryptology)
         integrieren. Siehe http://www.ecrypt.eu.org/.
    * Hashverfahren:
       - Tiger (http://www.cs.technion.ac.il/~biham/Reports/Tiger/)
       - Alle SHA-3-Kandidaten
         (http://csrc.nist.gov/groups/ST/hash/sha-3/index.html)
    * Protokolle / Protokollschwächen:
       - Visualisierung von Man-in-the-Middle-Angriffen
       - Visualisierung von SSL
       - Blind Signatures
       - Elektronische Wahlen
       - Tripartite Schlüsselvereinbarung (geplant für Java-CrypTool)
       - Kleptographie (http://www.cryptovirology.com/)

- Schnelle Auswahl der verschiedenen Verschlüsselungsverfahren
  über eine Dialogbox statt über die Menüs (Offenlegung aller
  Steuerparameter der Algorithmen) (analog CryptoBench).

- GNFS zur Faktorisierung (Ted)

- Erzeugung des Generators bei DH korrigieren (Gonzalo)(Ko)

- Erzeugung aller Hashwerte aus regulärem PW-Ausdruck (Hartmann)

- Kryptographisch starke elliptische Kurven erzeugen und damit
  Implementierung eines auf Elliptischen Kurven basierenden
  Kryptosystems. Dazu könnte man das Kryptosystem von Menezes
  und Vanstone nehmen, das 1993 von diesen Autoren vorgeschlagen
  wurde: A. Menezes and S. Vanstone,
         "Elliptic curve cryptosystems and their implementation",
         Journal of Cryptology, 6 (1993), Seite 209-224.

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
  - Nutzung der schon eingebauten 3-D-Darstellung von Zufallsdaten,
    um dem Nutzer m.H. der beim Drehen sichtbaren Hyperebenen die
    Schwächen von Zufallsgeneratoren (z.B. bei LCG) zu verdeutlichen.
  - Weitere Zufallstests (aus der Spanischen Version?)

- Weitere Standards implementieren und direkt über die Menüs bzw.
  aus der Online-Hilfe heraus an alle Stellen verzweigen, wo diese
  Standardverfahren (z.B. PKCS#5) verwendet werden (Hauptarbeit
  dabei sind das User Interface und die Dokumentation).

- Verbindung zwischen CrypTool (PKCS#12) und PGP schaffen, indem
  man PGP-Keys in CrypTool verwenden kann. Idee: Per Passwort-Eingabe
  öffnet man seinen privaten Keyring, analysiert die Struktur, holt den
  Key heraus (PGP-Sourcen sind gegeben) und nutzt diesen, um mit den in
  CrypTool implementierten Verfahren PGP-Files zu entschlüsseln oder zu
  signieren. Damit wird klar, dass auch PGP die Standard-Algorithmen nutzt.

- Testbett mit Beispielen und Lösungen erzeugen, damit man das
  Testen automatisieren kann und damit man sicherstellen kann,
  dass durch Programmänderungen nicht alte funktionierende
  Funktionalität negativ beeinflusst wird:
  a) Interface, um Testaufgaben manuell in Dialogboxen zu laden
  b) Schnittstelle schaffen, mit der sich die Testaufgaben aus
     einer Datei selbst in die Dialogboxen laden.
     Vielleicht sogar Script-Steuerung für alle Dialoge oder
     automatische Testtools vom Markt einsetzen.
  c) Commandline-Interface schaffen, das ohne Dialogboxen alle
     Aufgaben aus einer Datei per Schnittstelle ausliest und die
     Lösungen wieder in eine Datei schreibt:
     -> Abgleich automatisierbar
     -> neue Version leichter testbar.



A.2.1.2. Funktionalität: Analyse
         -----------------------
- Wünschenswert wäre, wenn insbesondere die Analyse in allen Formen und
  samt Visualisierung weiter ausgebaut werden könnte.

- Zu allen Verschlüsselungsverfahren eine (gute) Analyse anbieten, die
  (zumindest für die klassischen Verfahren besser ist als Brute-force).

- Angriff auf symmetrische Verschlüsselungsverfahren, bei denen die
  Parameter der Verschlüsselungsverfahren flexibel reduziert werden
  können.

- Differentielle Kryptoanalyse auf symmetrische Chiffren (DES, ...).

- Die Brute-force-Möglichkeiten erweitern: Nutzen von Wissen
  - um Teile des Klartextes,
  - um Teile des Schlüssels.

- Demo, wie lange eine vollständige Schlüsselsuche dauert (in Abhängigkeit
  von der Schlüssellänge).

- Analyse neu implementieren für:
   * homophone Verschlüsselung
   * Permutationen/Transpositionen
      - Known-Plaintext-Analyse der doppelten Spaltentransposition,
      - Ciphertext-only-Analyse des Doppelwürfels
   * Playfair-Verschlüsselung
      - C-Sourcen (Gunnar-Andresson) liegen uns vor.

- Analyse verbessern für:
   * monoalphabetische Substitution
      - explizite Anzeige von vertauschten Digrammen wie "ie"/"ei"
        und von Doppelzeichen wie "mm".
      - Ersetzte Buchstaben in der Dialogbox nicht nur groß, sondern
        auch in roter Schrift anzeigen.

   * Vigenère
      - Weiteres Kryptoanalyse-Verfahren insbesondere für kurze Texte
        (anhand des Cryptologia-Artikels von Tobias von Schrödel).

- Wörterbücher für alle Angriffe benutzen, nicht nur für die Substitution.

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

- Gleitende Entropie: Automatisierte Suche von Stellen in einem Dokument
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

- Aktuelle Hashangriffe darstellen (z.B. Erstellen von PS-Dokumenten nach
  Lucks oder von PDF-Dokumenten nach BSI mit gleichem Hashwert) und
  Aufzeigen der Anwendungsszenarien.

- Nutzung von Rainbow-Tabellen.

- Angriff auf WEP-Protokoll (schon implementiert in CrypTool 2).

- Weitere Angriffe auf konkrete Protokolle implementieren und/oder
  visualisieren, um zukünftige Konzepte zu verbessern.



A.2.1.3. Interne Schnittstellen / Editoren
         ---------------------------------
- Alle benutzten Schlüssel in einem Container speichern.
  Alle Schlüssel der unterschiedlichen Verschlüsselungsverfahren in einem
  Dialog anzeigen.
  Abspeichern permanent als Datei in einem Format, das für alle CrypTool-
  Versionen gemeinsam ist.

- Zumindest die den Nachfolger-Projekten: Ausgabe/Anzeige komplett von
  den Kryptomodulen trennen (dies erleichtert Portierungen und
  Fehlersuche).

- Parametrisierung, wo immer das möglich ist:
  Anbieten einer Option, um z.B. den Initialisierungsvektor,
  die Anzahl von Runden, die Schlüssel- oder Wortlänge oder
  das Padding zu setzen (z.B. für den RC5-Algorithmus - siehe
  RFC 2040).
  Diese Parameter müssen dann auch in das Format für den internen
  Schlüsselspeicher aufgenommen werden.

- Langzahl- und Krypto-Bibliotheken:
   - Unterstützung weiterer Libraries (LiDIA, FLINT/C, 
     Wei Dai's Crypto++, APFLOAT, ...).

- Vorhandene Einschränkungen in der N-Gramm-Analyse bzgl. Dateigröße
  ausdehnen (evtl. mit Benutzerfeedback und der Möglichkeit abzubrechen,
  wenn viel Zeit erforderlich).



A.2.1.4. User-Interface / Visualisierungen
         ---------------------------------
- In den Dialogen in CrypTool 1.x können Zahlen nicht immer in allen
  Darstellungsarten eingegeben werden (z.B. kann im Dialog 
  RSA-Kryptosystem die zu verschlüsselnde Nachricht als Text mit frei
  einzustellendem Alphabet und als Zahl mit 4 verschiedenen Basen) 
  eingegeben werden; die Primzahlen dagegen kann man "nur" als Zahl 
  im Zehnersystem bzw. als Ausdrücke mit Zahlen im Zehnersystem 
  eingeben). Alternative wäre ein a-modales Umrechnungsdialog-Fenster.

- Nützlich wäre es, wenn man aus CrypTool heraus einen Taschenrechner
  als a-modales Fenster aufmachen könnte, der Terme mit Zahlen 
  beliebiger Basis als Eingabe nimmt und die Ausgabe in mehreren
  Feldern in verschiedenen Zahlensystemen parallel anzeigt. Von hier
  aus sollte man dann die Zahlen per Knopfdruck ins Clipboard bringen
  können oder per Maus in die Eingabefelder der CrypTool-Dialogboxen
  ziehen können.

- Weiterhin wäre eine Anbindung an das CAS-System SAGE wünschenswert
  (http://www.sagemath.org/).

- Generelle Visualisierung der entsprechenden mathematischen Grundlagen:
  - z.B. anhand eines Lehrbuchs
  - z.B. wie mit den SAGE-Notebooks zu ECC:
    https://sage.mathematik.uni-siegen.de:8000/home/pub/45/
    Dieses Deckblatt enthält keine Berechnungen, sondern nur die Links
    zu den übrigen Teilen; zum Ausführen der folgenden Teile
    muss man sich selbst Kopien als SAGE-User anlegen.
  - z.B. wie die PascGalois Software (Group Calculator)
    (http://www.pascgalois.org/software.html)
  - z.B. http://www.martindalecenter.com/Calculators2_6_NZ.html
  - z.B. http://world.std.com/~reinhold/BigNumCalc.html
  - z.B. http://mathforum.org/library/resource_types/calculators/?keyid=28652723&start_at=301&num_to_see=50
  - z.B. http://www.hbmeyer.de/pythagen.htm
  - z.B. http://www.filebuzz.com/files/calculator_number_prime/1.html

- Für den Benutzer konfigurierbar einstellbar machen, ob neue Fenster
  wie bisher innerhalb des Hauptfensters erscheinen oder als "freie"
  (modale oder a-modale) Fenster daneben stehen.
  Einzelne Dialogboxen (z.B. N-Gramm-Analyse, Manuelle Analyse,
  Hybriddemo) als a-modale Fenster erzeugen, so dass man beliebig
  zwischen Hauptfenster und Auswertungsfenster springen kann
  (aufwändigere Steuerung, Erlauben oder Abfangen von Mehrfachauf-
  rufen derselben Dialogbox, evtl. Update nach Fokus-Wechsel bzw.
  nach Änderung der Originaldaten im Hauptfenster, ...).

- AES-Tool als eigenständiges Tool erweitern:
   - Einbinden des PKCS#5-Dialogs, um dem Benutzer seine gewohnte
    Eingabeweise zu bieten: Dabei zufällige Werte für Salz und 
    Iterationszahl voreinstellen und den User auffordern, sich
    den Hexwert zu merken oder ihn sicher aufzubewahren.
  - Auch Verschlüsseln ganzer Verzeichnisse.
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
  übernommen. AES-256 braucht dazu SHA-256.

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



A.2.2. Roadmap: Nachfolger-Projekte mit Java/Eclipse und C#/.NET
       ---------------------------------------------------------
Die Nachfolger von CrypTool 1.x nutzen State-of-the-Art-Entwicklungsumgebungen,
aktuelle Layout-Techniken und moderne Software-Architekturen.

A.2.2.1. Design der Nachfolger-Projekte
         ------------------------------
a) Generelle Wunschliste anhand des Benutzerfeedbacks.
   Dies gilt für beide Nachfolger-Versionen Java-CrypTool und CrypTool 2:
   - Moderne Pure-Plugin-Architektur.
   - Moderneres Layout, weniger Dialogboxen-Wechsel.
   - Absolute Standardkonformität in der Bedienung.
   - Mehr Benutzerinteraktion, Actionhistorie.
   - Alle Sprachen in einem Programm, einem Setup.
   - Dynamischer Wechsel den Sprachen.
   - Dynamischer Wechsel zwischen Kryptoprovidern.
   - Teil-Updates aus dem Internet.
   - Mehr Funktionen als Thread implementieren (parallel, alle abbrechbar).
   - Einfacheres Erstellen von Kaskaden zusammengestellt aus den
     existierenden Elementen.
   - Anbieten eines Recorders für Benutzereingaben.
   - Alle Dateien als Stream nutzen, um auch sehr große Dateien bearbeiten
     zu können.
   - Steuerung auch von der Kommandozeile.

b) Java-CrypTool (JCrypTool, JCT):
   - Komplett neu designtes CrypTool in Java mit Eclipse/RCP.
   - Plattform-unabhängig.
   - Nutzt strikt die Standards von Eclipse 3.5.
   - Nutzung von SWT (und Jigloo) für die GUI.
   - Verfügbar sind eine Secude-Lib, Bouncy-Castle und FlexiProvider.
   - Meilenstein 1 (August 2007) war für Entwickler und zeigte, dass die
     neuen Architektur-Konzepte umsetzbar sind.
     Milestone 2 (August 2008), 3 (Dezember 2008), 4 und 4a (Februar 2009)
     können auch schon von Endbenutzern sinnvoll verwendet werden.
   - Meilenstein 5 ist geplant für August 2009.
   - Weitere Entwickler, Architekten und Designer sind in diesem Projekt
     herzlich willkommen.
   - Für Einsteiger und zusätzlich mit Expertenmodus.
   - Enge Zusammenarbeit mit dem Lehrstuhl Prof. Buchmann, TU Darmstadt.
   - Die Update-Webseite für JCT liegt bei der Uni Duisburg-Essen.
   - Nutzung von SourceForge mit Subversion zur Sourcecode-Verwaltung:
     http://jcryptool.sourceforge.net/ .

c) CrypTool 2.0 (CT 2)
   - Komplett neu designtes CrypTool in C# mit dem .NET-Framework.
   - Nutzt strikt die Standards von Microsoft (.NET, Aussehen wie Office 2007).
   - Nutzung von Windows Presentation Foundation (WPF) zur Gestaltung
     von multimedialen Oberflächen (GUI).
   - Das gesamte Projekt lässt sich mit der kostenlosen VS2008-Express-
     Edition für C# erstellen.
   - Verfügbar sind die .NET Krypto-Provider, und Bibliotheken wie GMP und
     Crypto++ per Wrapper.
   - Die Alphaversion, veröffentlicht im April 2008, war für Entwickler.
     Beta-Versionen (für Entwickler und Nutzer) werden seit Juli 2008
     regelmäßig veröffentlicht.
     Mit der Releaseversion von CT2 wird die Weiter-Entwicklung von CrypTool 1.x
     eingestellt.
   - Weitere Entwickler und graphisch anspruchsvolle Designer sind
     in diesem neuen Projekt sehr herzlich willkommen.
   - Hoher Lerneffekt bei Einsteigern durch visuelle Programmierung.
   - Enge Zusammenarbeit mit dem Lehrstuhl Prof. Weis in Duisburg-Essen.
   - Nutzung von Subversion zur Source-Code-Verwaltung.

- Bemerkung: Portierung nach Linux
   Eine Portierung von CrypTool 1.4.x nach Linux mit Hilfe von GCC 4.x und
   Qt 4.x war außerhalb des eigentlichen CrypTool-Projektes von Einzelpersonen
   begonnen worden, aber mangels Zeit nicht/wenig fortgesetzt worden.
   - Die Bibliotheken von Secude, Miracl, NTL, OpenSSL und GMP stehen
     zur Verfügung.
   - Gesamtaufgabe in sinnvolle Teile zerlegt:
       - Oberfläche: Hier liegt die Hauptarbeit.
       - Funktionalität, implementiert in purem C/C++: ok
       - Online-Hilfe in HTML: ok.
   - Die erste Beta wurde im November 2007 veröffentlicht.
     Die zweite Beta ("still no functional version", 11 % der geplanten
     Aufgaben) wurde am 15.12.08 veröffentlicht.
   - http://www.cryptoolinux.net/




A.2.2.2. Funktionen, geplant für die Nachfolger-Projekte CT2 und JCT1
         ----------------------------------------------------------------
Die neuen Versionen (siehe Kapitel A.2.2.1) sind:
- CrypTool 2.0  (http://cryptool2.vs.uni-due.de)   und
- JCrypTool 1.0 (http://jcryptool.sourceforge.net).


Funktionen, die schon in den jetzigen Betaversionen
            (CT2 Beta-2.0.3465 and JCT1 Milestone 4a)
            implementiert und integriert sind:
- CT2  Visuelle Programmierung (Komposition von Protokollen und Workflows)
- CT2  Primzahlen-Visualisierungen
- CT2  WEP-Verschlüsselung und WEP-Analyse
- CT2  Smartcard-Plugin (sendet Kommandos an eine Chipkarte
                         mittels der PC/SC-Schnittstelle in Windows)

- JCT  Adaptive Navigationsleiste, wahlweise als Baum oder Palette,
       mit Filter
- JCT  Vigenère-Autokey-Verschlüsselung
- JCT  Visualisierung klassischer (Analyse-)Verfahren
- JCT  Einstellbarkeit aller Detail-Parameter moderner Algorithmen
       in der FlexiProvider-Perspektive
- JCT  Dragon-Verschlüsselung & LFSR


Funktionen, die für die Release-Versionen der Nachfolger-Projekte geplant sind:
- CT2  Virtuelle Kreditkartennummern (VCC) und Prüfziffern
- CT2  Bleichenbacher Angriff
- CT2  NIST Zufalls-Testsuite
- CT2  GNFS
- CT2  Alphabete auch für die klassischen Verfahren ausdehnen auf 256 Zeichen
- CT2  Massenmustersuche
- CT2  SOA-Security (SOAP-Nachrichten nach WS-Security zwischen den Beteiligten)
- CT2  Framework zum Bau und zur Analyse von LFSR-Stromchiffren
- CT2  Cube Attack gegen symmetrische Chiffren (I. Dinur und A. Shamir)

- JCT  Multi-partite Schlüsselvereinbarung
- JCT  PGP-S/MIME Interoperabilität
- JCT  Entropie-Untersuchungen
- JCT  Analyse von Transpositionschiffren mit dem ACO-Algorithmus
- JCT  Visualisierung von Zero-Knowledge-Beweisen
- JCT  Commandline-Funktionalität
- JCT  Mächtige Action-History und Kaskadierungs-Unterstützung
- JCT  Demonstrator für XML-Signaturen

Vergleiche auch die Roadmap auf der Webseite https://www.cryptool.org/content/view/21/46/lang,german.
Weitere Details:
- für CT2: https://www.cryptool.org/trac/CrypTool2
- für JCT: http://jcryptool.wiki.sourceforge.net/ReleasePlan

################################################################
