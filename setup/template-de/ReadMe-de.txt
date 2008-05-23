==================================================================
    CrypTool, Version 1.4.20 f�r Win32, Juni 2008 - Beta 03
    (c) Contributors
        Dazu geh�ren z.B.
        Deutsche Bank AG, Frankfurt am Main
        Universit�t Siegen, Darmstadt, Bochum und Duisburg-Essen
        1998-2008
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
 2.1. .... Was k�nnen Sie mit CrypTool machen
 2.2. .... Informationen f�r Entwickler / Wo finden Sie die Sourcen
 2.3. .... Wo finden Sie weitere �berblicke zu CrypTool
 2.4. .... Neuerungen in Version 1.4.20
 3. .... M�gliche Punkte f�r eine Weiterentwicklung -- Ideen, Anfragen
 3.1. .... Funktionalit�t: Algorithmen / Verfahren
 3.2. .... Funktionalit�t: Analyse
 3.3. .... Interne Schnittstellen / Editoren
 3.4. .... User-Interface / Visualisierungen
 3.5. .... Roadmap: Portierung nach Linux, 
                    Zukunftsprojekte mit Java/Eclipse und C#/.NET
 3.6. .... Sinnvolle Aufgaben f�r jemand, der neu anf�ngt mit zu entwickeln
 4. .... Beschr�nkungen und Voraussetzungen
 4.1. .... Anwendungsbereich dieser Lern-, Trainings- und Awareness-Software
 4.2. .... Win32-Umgebung und Java-Runtime
 4.3. .... Interaktive Online-Hilfe unter Windows XP
 4.4. .... Unterst�tzung verschiedener Sprachen
 4.5. .... Einschr�nkungen / Features
 4.6. .... Mit �lteren CrypTool-Versionen erzeugte Zertifikate und Schl�ssel
 5. .... Installation / Deinstallation / Betrieb
 5.1. .... Installation und Nutzung von Schl�sseln aus vorherigen Versionen
 5.2. .... Installation in Mehrbenutzersystemen
 5.5. .... Deinstallation von CrypTool
 5.4. .... Betrieb in Mehrbenutzersystemen
 6. .... Liste der Dateien in der Auslieferung
 6.1. .... �berpr�fen der Integrit�t der heruntergeladenen Dateien
 7. .... Kurze Historie der freigegebenen Hauptversionen
 8. .... Feedback
 9. .... Kontaktadressen
10. .... Verweise / Auszeichnungen
10.1. .... Artikel �ber CrypTool
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
analysieren. Schon in der Antike wurden solche Verfahren zur Geheim-
haltung von Nachrichten entwickelt. Heutige Verfahren basieren auf
moderner Mathematik und erlauben neben der Verschl�sselung auch die
Pr�fung der Integrit�t, die Erstellung von Signaturen, sichere
Authentisierung und Vieles mehr. CrypTool unterst�tzt sowohl die
Ausf�hrung als auch die Analyse solcher Verfahren.

CrypTool wird seit 1998 entwickelt. Im Moment arbeiten �ber 40 Personen
weltweit daran.

Zu jedem Programmteil gibt es reichhaltige Online-Hilfe, die auch
ohne tiefes Kryptowissen verstanden werden kann.

CrypTool existiert in den vier Sprachen Deutsch, Englisch, Polnisch
und Spanisch. In Deutsch und Englisch ist das CrypTool-Paket komplett
vorhanden.
Die Polnische Programm-Version hat die gleiche Funktionalit�t [�bersetzt
sind im Moment das Programm selbst, also die Oberfl�che (Men�s, Dialoge,
...) und die Onlinehilfe.  Die der polnischen Version beigelegte
PDF-Dokumentation ist noch in Englisch]. �hnlich ist es bei der
spanischen Version.

Vorausgesetzt wird, dass der Benutzer mit Anwendungen in einer
Windows-Umgebung umgehen kann.

Die aktuelle Release-Version von CrypTool und die Sourcen dazu
finden Sie unter den Internet-Adressen (keine Registrierung):
                http://www.CrypTool.de
                http://www.CrypTool.com
                http://www.CrypTool.org
                http://www.CrypTool.pl

Seit Mitte 2007 werden �ber 3000 CrypTool-Pakete pro Monat herunter
geladen -- mit wachsender Tendenz (davon entfallen etwas �ber 1/3
auf die englische Version).

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
allem die Kapitel 2.4 (Neuerungen) und 3 (Weiterentwicklung, Roadmap)
interessant sein.

Wir laden jeden herzlich ein, an CrypTool mit zu entwickeln oder
Feedback zu geben. Auch f�r Hinweise zu Arbeiten (Diplom-, Doktor-
oder Seminararbeiten), die man in CrypTool integrieren k�nnte, sind
wir sehr dankbar.
Insbesondere junge Entwickler sind eingeladen, sich zu trauen -- sie k�nnen
bei erfahrenen Entwicklern sehr viel �ber professionelle Software-Entwicklung
lernen. 
Kontakte: Siehe Kapitel 9 unten.


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

Einen schnellen Einstieg in die Kryptographie mittels CrypTool
finden Sie, wenn Sie einige Szenarien (Tutorials) der Online-Hilfe
durchspielen (die Szenarien stehen im Inhaltsverzeichnis der
Online-Hilfe unter "Beginn der Arbeit mit CrypTool").

Die Funktionen von CrypTool k�nnen Sie am einfachsten ausprobieren
mit der standardm��ig ge�ffneten Datei "Startbeispiel-de.txt".
Sie k�nnen auf der CrypTool-Arbeitsfl�che aber auch eine andere
unverschl�sselte Datei aus dem Unterverzeichnis "examples" oder
irgendeine andere Datei �ffnen.

Wenn Ihnen ein Men�punkt nichts sagt oder Sie in einem Dialogfenster
nicht recht weiter wissen, sollten Sie mittels der F1-Taste ausreichend
Hilfe finden (wenn nicht, geben Sie uns bitte Feedback).

Eine 1-seitige �bersicht �ber alle Men�s in CrypTool (Men�baum)
finden Sie im beigelegten PDF-Skript (im Anhang A1).

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
  - der Industrie-bew�hrten Secude-Bibliothek (http://www.secude.com/),
  - der Miracl-Bibliothek von Shamus Software (http://indigo.ie/~mscott/),
  - der OpenSSL-Bibliothek (http://www.openssl.org/),
  - der NTL-Zahlentheorie-Bibliothek von Victor Shoup
        (http://www.shoup.net/ntl/),
  - der GMP-Bibliothek f�r beliebig genaue Arithmetik
        (http://www.swox.com/gmp/) und
  - der cv act library der cv cryptovision Gmbh (www.cryptovision.com).
 
  Die aktuell benutzten Versionen der inkludierten Bibliotheken finden
  Sie in der Dialogbox "�ber CrypTool" (siehe Hilfe-Men�).

  Somit ist CrypTool auch eine hervorragende Referenzimplementierung
  f�r kryptographische Verfahren.

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
Die folgenden Programme k�nnen aus CrypTool heraus, aber auch stand-alone
aufgerufen werden:

a) Das Programm AES-Tool v 2.5 (entstanden im CrypTool-Projekt):
   Zum Erstellen selbst-entpackender Executables ist in CrypTool ein
   Programm integriert, das auch eigenst�ndig benutzt werden kann.
   Darin wird aus einem Passwort ein Session-Key erzeugt, mit dem
   ein beliebiger Dateiinhalt AES-verschl�sselt wird.
   Dieses Verschl�sselungstool kann sowohl als Fensteranwendung als
   auch von Kommandozeile (z.B. aus einer Batchdatei) aufgerufen werden.
   Bei der Installation wird diesem Programm die Dateiendung "AES"
   zugeordnet.

b) Das Lernspiel "Der Zahlenhai" v 1.1.5 (entstanden im CrypTool-Projekt):
   Dieses Lernspiel f�r Sch�ler bringt diesen den Umgang mit
   Teilern und Primfaktoren n�her.

c) Das Animationsprogramm ANIMAL (siehe http://www.algoanim.info/Animal2):
   Mit diesem an der TU Darmstadt von Dr. R��ling gepflegten Programm
   kann man die Einzelschritte von Algorithmen oder die Komponenten von
   Datenstrukturen beliebig genau modellieren, die Einzelschritte manuell
   vor und zur�ck abspielen oder automatisch ablaufen lassen. Damit kann
   man auch dynamisch Source Code-Zeilen visualisieren.
   Das Animal-System erlaubt die Erstellung von Animationen mithilfe
   einer GUI, einer Skriptsprache sowie einer Java-API.
   Weitere Beispiele finden sich im ANIMAL-Repository (Datenbank):
   http://www.algoanim.info/Animal2/?q=node/284
   Hierzu wird die JRE 1.5 ben�tigt (siehe Kapitel 4.2).

d) Ebenso wie ANIMAL ist die ECC-Demo eine eigenst�ndige Java-Anwendung
   (JAR-Datei). Hierzu wird auch die JRE 1.5 ben�tigt (siehe Kapitel 4.2).

e) Die Flash-Anwendungen:
   - "Rijndael-Animation" (visualisiert das Verschl�sselungsverfahren AES),
   - "Rijndael-Inspektor" (visualisiert die �nderungen der State-Matrix 
                           nach jedem Schritt in jeder Runde bei AES) und
   - "Enigma" (visualisiert das 2.-Weltkriegs-Krypto-Ger�t Enigma).

f) Die Authorware-Anwendung "ZT" (Zahlentheorie) f�hrt in die elementare
   Zahlentheorie ein und visualisiert viele der Verfahren und Konzepte,
   die Grundlage der modernen Public-Key-Kryptographie sind.
   Wo n�tig zeigt sie auch die entsprechenden mathematischen Formeln.
   Dabei k�nnen diese mathematischen Verfahren dynamisch mit eigenen
   kleinen Zahlenbeispielen ausprobiert werden.
   Dazu geh�rt auch das Programm bc.exe der Free Software Foundation,
   mit dem man auf der Kommandozeile beliebig genau rechnen kann.



(4) Geschichten (mit Bezug zu Zahlentheorie und Kryptographie) und R�tsel
-------------------------------------------------------------------------
a) Als PDF-Datei sind zwei Geschichten beigelegt:
   - In "Der Dialog der Schwestern" wird eine Variante des RSA-Verfahrens
     von den Titelheldinnen benutzt, um verschl�sselt zu kommunizieren.
   - In "Das Chinesische Labyrinth" muss Marco Polo zahlentheoretische
     Aufgaben l�sen, um Berater des Gro�en Khan zu werden.

b) Krypto-Wettbewerbe:
   Ebenfalls beigelegt sind 13 Dateien mit verschl�sselten Texte, die uns
   freundlicherweise Klaus Schmeh zur Verf�gung stellte, der Autor des
   Buches "Codeknacker gegen Codemacher":
   Klaus Schmeh: "Codeknacker gegen Codemacher. Die faszinierende Geschichte
                 der Verschl�sselung", 2. Auflage, Dezember 2007, W3L-Verlag

   Diese Dateien enthalten einige historisch interessante (gel�ste und
   ungel�ste) Geheimtexte, die Sie gut als "�bungsmaterial" und Zeitvertreib
   verwenden k�nnen:
   1) Dorabella-Chiffre (ungel�st) 
   2) D�Agapeyeff-Chiffre (ungel�st)
   3) Feynman-Chiffren (3 Teile, von denen zwei ungel�st sind) 
   4) Kryptos-Skulptur (4 Teile, von denen der letzte ungel�st ist) 
   5) Doppelw�rfel (erstellt von Klaus Schmeh, Quelltext englisch, ungel�st)
   6) "Die tanzenden M�nnchen" von Arthur Conan Doyle (Sherlock Holmes)
                   (transkribiert, gel�st)
   7) Harry-Potter-Chiffre (von Klaus Schmeh, Quelltext deutsch, ungel�st)
   8) "Mathias Sandorf" von Jules Verne (gel�st)

   Mehr Informationen dazu gibt es in der Onlinehilfe zu CrypTool (unter dem
   Indexeintrag "Krypto-Wettbewerbe") und im den Buch von Klaus Schmeh.


Alle Einzeldateien, die bei der Installation des CrypTool-Paketes
auf Ihre Platte kopiert werden, sind in Kapitel 6 (unten in diesem
Readme) aufgef�hrt.



1.3. Danke
     -----
Zu CrypTool haben sehr viele verschiedene Personen (weit �ber 100)
beigetragen -- insbesondere auch in ihrer Freizeit.
Einige sind namentlich in der Dialogbox aufgef�hrt, die man erh�lt,
wenn man in der Dialogbox "�ber CrypTool" einen Doppelklick ausf�hrt.
Der Wohnort einiger Entwickler/Mitwirkenden ist auf der CrypTool-Webseite
per Google-Map zu finden.
Herzlichen Dank an alle Mitwirkenden.

Besonders herausheben m�chte ich einige Kernentwickler/-Architekten
im CrypTool 1.x-Projekt, deren hohes und langj�hriges Engagement und
deren hervorragende Kompetenz und Hartn�ckigkeit solche dauerhaften,
lebendigen und erfolgreichen Open-Source-Projekte erst erm�glicht:
J�rg, Henrik, Florian, Peer.

Ebenfalls danken m�chte ich einigen Kernentwicklern/-Architekten in
den Zukunftsprojekten CT2 und JCT, die mit gro�er Ausdauer und Kompetenz
die Schwierigkeiten mit den allerneuesten Entwicklungsumgebungen und
Software-Architekturen bew�ltigten:
- Sebastian, Philipp, Arno, Martin, Thomas, Timo, Soeren
- Dominik, Tobias, Al-Akkad, David

Und nat�rlich den vielen Ungenannten, insbesondere Studenten und
Praktikanten, die viel dazu beitrugen und dabei noch mehr lernten
von den Experten im Projekt.

Ebenfalls beigetragen haben als Sponsoren z.B. die Deutsche Bank AG,
die Technische Universit�t Darmstadt und die Universit�t Duisburg-Essen.

Weiterhin m�chten wir hier einige Mitwirkende erw�hnen, f�r deren Input
besondere Bedingungen gelten:

- Dr. Carsten Elsner erlaubte uns, seine beiden Geschichten als 
  PDF-Datei beizulegen.
  Der Verfasser, als alleiniger Inhaber aller Rechte an den Werken,
  r�umt dem CrypTool-Maintainer das ausschlie�liche Vervielf�lti-
  gungs- und Verbreitungsrecht ein. Die Geschichten d�rfen nur zusammen
  mit dem CrypTool-Paket verbreitet werden.
  Die Geschichte "Der Dialog der Schwestern" wurde zuerst in dem 
  Computermagazin c't 25/1999 ver�ffentlicht. W�hrend in der c't
  eine etwas gek�rzte Fassung ver�ffentlicht wurde, liegt hier die
  Originalfassung bei.

- Dr. Guido R��ling erlaubte uns, seine Freeware ANIMAL, eine Java-basierte
  Animationssoftware, mit auszuliefern.

- Ebenfalls integrieren durften wir erweiterte Versionen von:
  - den beiden Flash-Animationen zu AES von Enrique Zabala,
  - der Flash-Animation zur Enigma von Dr. Frank Spie�,
  - dem Zahlentheorie-Lernprogramm von Martin Ramberger.
  Die �ber eine Verwendung au�erhalb des freien CrypTool-Contextes
  hinausgehenden Rechte verbleiben beim jeweiligen Autor.

- Die Firmen (siehe Kapitel 1.2)
  - Secude IT Security GmbH, 
  - Shamus Software Ltd und
  - cv cryptovision Gmbh
  gestatteten uns gro�z�gigerweise, ihre Krypto-Bibliotheken zu nutzen.
  Diese mit CrypTool verteilten Bibliotheken d�rfen nicht in einem
  Kontext au�erhalb CrypTool benutzt werden, ohne vorher die erw�hnten
  Firmen zu kontaktieren und nach ihren aktuellen Lizenzbedingungen zu
  fragen.

Ebenso herzlich danken m�chten wir den Open-Source-Entwicklern, die uns
mit ihrem Code Anregungen gaben oder deren Code wir nutzen d�rfen, z.B.
- die Bibliotheken OpenSSL, GMP und NTL,
- die Installations-Software NSIS (http://nsis.sourceforge.net/Main_Page),
- den Texteditor-Software Scintilla (http://scintilla.sourceforge.net),
- das Hex-Control (www.codeguru.com/Cpp/controls/controls/article.php/c5287).

Bedanken m�chte ich mich auch bei
- Herrn Bartosz Sawicki von der Universit�t Warschau, der mit seinem
  Team die polnische Version erstellte.
- Herrn Gonzalo Alvarez von der Universit�t Madrid, der mit seinen
  Kollegen die spanische Version erstellte.


1.4. Maintainer, Hosting, Webseite und Welcome
     -----------------------------------------
Seit April 2008 hostet der Lehrstuhl f�r Verteile Systeme,
Fakult�t f�r Ingenieurwissenschaften unter Prof. Dr. Weis an der
Universit�t Duisburg-Essen die deutsche und englische Webseite von
Cryptool und das Subversion-Repository f�r die Programm-Sourcen der
Zukunftsversion CrypTool 2.

Der Lehrstuhl Sicherheit in der Informationstechnik, Fachbereich
Informatik unter Frau Prof. Dr. Claudia Eckert an der TU Darmstadt
hostet weiterhin das Subversion-Repository f�r die Programm-Sourcen
der Release-Version CrypTool 1.x.

Die CrypTool-Entwicklergruppe unter Bernhard Esslinger fungiert als
Maintainer, d.h. sie k�mmert sich um die Pflege des Codes, die
Ver�ffentlichung als Open Source und Freeware, und um die
Koordination der Weiterentwicklung. Die n�chsten Schritte der
Roadmap sind auch auf der Webseite ver�ffentlicht.

Die Homepage von CrypTool ist www.cryptool.org.

Wir freuen uns �ber jeden weiteren Entwickler, der sich an der
Weiterentwicklung von CrypTool beteiligt.
Ideen zur Weiterentwicklung finden Sie z.B. in Kapitel 3.

Ebenfalls sehr willkommen sind uns Ideen und Infos, wie CrypTool in
Lehre, Schule und Ausbildung eingesetzt wird, damit wir dazu 
beitragen k�nnen, diese Informationen auszutauschen. Ein Mittel
dazu ist z.B. das Kryptologie-Portal f�r Lehrer (www.cryptoportal.org).



2. Was bietet CrypTool im Detail
   -----------------------------

2.1. Was k�nnen Sie mit CrypTool machen
     ----------------------------------
Die generellen Eigenschaften und Funktionen von CrypTool sind:

- E-Learning-Programm rund um das Thema Kryptographie und Kryptoanalyse.

- Alles in einem Programmpaket und steuerbar unter einer Oberfl�che.

- Alles in CrypTool ist in Deutsch und Englisch verf�gbar.
  Das Programm selbst gibt es auch in Polnisch und Spanisch.

- Viele klassische Verschl�sselungsverfahren: Und dazu teilweise manuell
  unterst�tzte, teilweise automatische Analyse (Known-Plaintext-Angriff).

- Codierungen wie Base64 und UU-Encode.

- Nahezu alle modernen symmetrischen Verschl�sselungsverfahren: Und dazu
  jeweils die Brute-force-Analyse
  (Beim Brute-force-Angriff auf symmetrische Algorithmen werden Jokerzeichen
   zugelassen und die erwartete Zeit wird ausgegeben. 
   Au�erdem kann man die Breite f�r das hierbei genutzte Entropiefenster in
   den Analyseoptionen einstellen und welche Erwartung man an das Alphabet
   hat, aus dem der Klartext gebildet wurde).

- Moderne (asymmetrische) Kryptoverfahren und Protokolle (Hash, RSA, ECC,
  Digitale Signatur, Hybrid-Verschl�sselung, PKCS#5, Shared Secret, ...)
  und teilweise Angriffe darauf (Geburtstagsangriff, Seitenkanalangriff, 
  Gitterbasenreduktion).

- Demo des RSA-Verfahrens (in verschiedenen Varianten) und Demo einiger 
  zugeh�riger Algorithmen aus der Zahlentheorie:
  - Primzahlen generieren und testen (sowohl mit den schnellen heuristischen
    als auch mit dem deterministischen AKS-Verfahren).
  - Zahlen (schrittweise) mit verschiedenen Verfahren faktorisieren
    (die verschiedenen Verfahren laufen in parallelen Threads).
  - Das RSA-Kryptosystem transparent durchf�hren:
     - RSA-Schl�ssel erzeugen (auch mit selbst-gew�hlten Primzahlen).
     - Ver-/Entschl�sseln mit dem RSA-Verfahren.
     - RSA-Signaturen erzeugen und diese verifizieren.
     - das RSA-Verfahren angreifen.

- Drei auf Gitterreduktionsverfahren basierende Angriffe gegen das 
  RSA-Verfahren, die dann greifen, wenn bestimmte Vorbedingungen 
  erf�llt sind:
  * ein Teil von einem der beiden Faktoren von N ist bekannt 
    ("Faktorisieren mit teilweise bekanntem p"),
  * ein Teil des Klartextes einer abgefangenen verschl�sselten 
    Nachricht ist bekannt und e ist klein ("Angriff auf stereotype
    Nachrichten"),
  * wenn d im Vergleich zu N zu klein gew�hlt ist, kann man N 
    faktorisieren ("Angriff auf kleine geheime Exponenten (nach
    Bl�mer/May)").
  Die Diplomarbeit von Herrn Mathias Schneider, innerhalb von der
  diese Verfahren implementiert wurden, kann auf Anfrage zugemailt
  werden (sie liegt nur in Deutsch vor).

- Visualisierungen/Animationen/Demonstrationen
  - Demo der Sensitivit�t von Hashverfahren.
  - Visualisierung mit Flussdiagrammen (z.B. beim Diffie-Hellman
    Schl�sselaustausch-Verfahren oder bei der Challenge-Response-Demo),
  - Animationen 
     - mit ANIMAL: f�r die Verschl�sselungsverfahren Caesar, Vigen�re,
                   Nihilist und DES,
     - mit Flash:  f�r AES und Enigma,
     - mit Java/SWT: Punkteaddition auf Elliptischen Kurven (sowohl auf
                     diskreten wie auf reelen Kurven).

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
  wie sie in der Realit�t vorkam, kann der Angreifer den Session-Key 
  durch Protokoll-gerechte Anfragen an den Server hoch effizient 
  berechnen.

- Hashwerte berechnen und ihre Sensitivit�t demonstrieren.

- Implementierung von MAC-Verfahren (Kombination von Hashes und 
  symmetrischen Verfahren zur Authentisierung von Nachrichten). 
  Hashverfahren wurden bisher schon von den in CrypTool implementierten
  Konzepten PKCS#5 und digitale Signaturen verwendet.

- Das Shared-Secret-Verfahren nach Shamir wurde mit vielen Optionen
  implementiert.

- Zufallszahlen:
  - Pseudozufallszahlengeneratoren und statistische Analysen f�r 
    Zufallsdaten (z.B. FIPS-140-1).
  - Der Secude-Zufallszahlengenerator bietet die M�glichkeit, Entropie
    �ber Mausbewegung und Tastatureingaben zu sammeln.
    Dies ist die Standardeinstellung f�r den ersten Aufruf des
    kryptographischen Zufallsgenerators, damit deutlich wird, dass man
    f�r gute Zufallszahlen einen zuf�lligen Input braucht.
  - Eine 3-D-Visualisierung von gro�en Mengen an Zufallszahlen mit Hilfe
    der Volume-Rendering-Engine aus OpenQVis 
    (http://openqvis.sourceforge.net/).

- PKCS#12-Export und -Import von RSA- und DSA-PSEs und damit
  von den darin gespeicherten Schl�sseln.

- Die modernen Verfahren wurden gem�� den internationalen Standards
  implementiert (Referenzimplementierung).

- Die letzte Einstellung zu einem Verfahren (Parameter, Schl�ssel oder
  Alphabet) wird Programm-intern aufbewahrt. Der Schl�ssel kann pro 
  Verfahren �ber das Schl�ssel-einf�gen-Symbol auch wieder abgerufen 
  werden, was die Bedienung beim Testen und Probieren stark erleichtert.

- Zu jedem Fenster kann ein Dialog angezeigt werden, der alle
  wesentlichen Eigenschaften dieses Dokuments anzeigt.

- In allen Fenstern, wo die Optionen f�r Text und Alphabete eine Rolle
  spielen, kann man direkt per Button-Klick zum Textoptionen-Dialog
  springen.

- Alle persistenten Daten werden im Nutzer-lokalen Teil der Registry
  abgelegt (keine INI-Datei mehr), wodurch man CrypTool ohne 
  Administratorrechte ausf�hren kann und verschiedene Benutzer
  am gleichen PC jeweils verschiedene Einstellungen haben k�nnen.
  xxxxxxxxxxxxxxxxx

- Die gleiche Men�struktur ist konstant sichtbar: Eintr�ge, die f�r
  bestimmte Dokumenttypen nicht ausf�hrbar sind, werden ausgegraut.

- Das eigenst�ndige Programm AES-Tool kann selbst-entpackende
  Programme erzeugen. Damit kann man eine beliebige Datei Passwort-gesch�tzt
  mit AES verschl�sseln (das Passwort ist als Hexadezimal-Schl�ssel
  einzugeben).
  Voller Funktionsumfang auch bei einem Aufruf von der Kommandozeile.
  Erzeugt man selbst-entpackende Archive, darf das Ergebnis nicht gr��er
  als 4 GB werden. Erzeugt man nur die verschl�sselten AES-Dateien
  kann das Original auch deutlich gr��er als 4 GB sein.

- Das eigenst�ndige Lernprogramm f�r die Mathematik hinter der
  asymmetrischen Kryptographie beschreibt ausf�hrlich und interaktiv
  die elementare Zahlentheorie.

- Drei auf dem Chinesischen Restesatz beruhende Anwendungen:
  * L�sung von Systemen linearer modularer Kongruenzen am Beispiel 
    einer Planetenkonstellation im Sonnensystem.
  * Veranschaulichung des Rechnens (Addieren, Subtrahieren, 
    Multiplizieren) mit modularen Resten statt mit den (gr��eren)
    eigentlichen Zahlen.
  * Veranschaulichen des Shared Secret-Verfahrens (entspricht der 
    Analogie, dass man zum �ffnen eines Tresors z.B. drei beliebige 
    von 5 Schl�sselinhabern braucht).

- Mit dem Passwort-Qualit�tsmesser (PQM) kann man die Widerstandsf�higkeit
  eines Passworts mit verschiedenen Verfahren und unter Vorgabe von
  Mindestanforderungen absch�tzen.

- Mit dem Passwort-Entropie-Dialog k�nnen Sie Passworte erzeugen, die eine
  �hnlich hohe Sicherheit bieten wie zuf�llig erzeugte Bin�rschl�ssel f�r
  symmetrische Verfahren einer vorgegebenen Bitl�nge. Sie k�nnen dabei
  ebenfalls das f�r das Passwort verwendete Alphabet festlegen.

- Das Lern-Spiels "Der Zahlenhai" bringt Sch�lern den Umgang mit
  Teilern und Primfaktoren n�her.

- Webseite mit den Hashwerten aller herunterladbaren CrypTool-Dateien:
  Damit kann man die Integrit�t der Dateien aus dem CrypTool-Paket, die
  sich auf dem Computer befinden, �berpr�fen.

- Umfangreiche Dokumentation (Onlinehilfe, Skript).
  Die Online-Hilfe ist im HTML-Format.
  Sie enth�lt Erl�uterungen zur Bedienung und zu allen Verfahren, einen
  �berblick �ber die Historie der Kryptographie und die Einordnung in
  weitere Sachgebiete sowie Informationen f�r eine sinnvolle Verwendung
  von Kryptographie.

- Weltweite Nutzung in Schulen, Universit�ten, Beh�rden und Firmen.



2.2. Informationen f�r Entwickler / Wo finden Sie die Sourcen
     --------------------------------------------------------

- Die Release-Sourcen (Tag "CrypTool_1_4_20") und die aktuellen Entwickler-
  Sourcen stehen direkt im Subversion-Repository zur Verf�gung.
  Darauf kann jedermann lesend zugreifen per
  svn checkout https://file.sec-tud.de/svn/CrypTool/trunk
      --username anonymous --password anonymous

- Einen Eindruck von der Gr��e des Projekts liefert die folgende, Anfang
  Juni 2008 erstellte Statistik (anhand der wichtigsten Dateien f�r die
  deutsche und englische Version):

    FILE SUMMARY xxxxxxxxxxxxxxxxxxxxxxxxxx
    ------------
        5 .rc   files
       38 .c    files
     1050 .html files
      363 .h    files
      304 .cpp  files
        8 .java files
        9 .tex  files
       22 .txt  files
  
    LINES OF CODE (LoC) SUMMARY
    ---------------------------
     25.847 MFC resource code (rc)
      1.632 LaTex code (tex)
     63.127 HTML code (html hpp)
      3.247 Java source code (java)
      4.202 Text files (txt)
    221.716 C/C++ source code (h c cpp)
  
    TOTAL: 319.771 lines of code

   Snapshot zur Anzahl von Dateien und zur Anzahl der Sourcecode-Zeilen


- Details zum Compilieren, Linken und zur einheitlichen Entwicklung
  finden sich in den Sourcen in der Datei "readme-source".

- Die Sourcen wurden mit der Microsoft Entwicklungsumgebung
  Visual Studio 2003 (VC++ v7.1) compiliert.



2.3. Wo finden Sie weitere �berblicke zu CrypTool
     --------------------------------------------
Eine gute �bersicht, was CrypTool bietet, finden Sie auch
- in der beigelegten PDF-Pr�sentation
   (Titel: "Kryptologie mit CrypTool"),
- auf der CrypTool-Webseite
   (insbesondere �ber den Eintrag "CT-Einstiegsseite" im linken Frame),
- mithilfe des Men�baums im Anhang A des beigelegten CrypTool-Skripts, und
- in der Onlinehilfe (siehe "Startseite").



2.4. Neuerungen in Version 1.4.20
     ----------------------------
Dieses Kapitel listet die Erweiterungen und Bugfixes auf, die in
CrypTool 1.4.20 seit CrypTool 1.4.10 hinzugef�gt wurden.

a) Entwickler-relevante �nderungen (eher programm-technisch):

- Aufr�umen des Sourcecode, h�here Wiederverwendung.

- Update auf OpenSSL 0.9.8g und ANIMAL 2.3.14.

- Automatisierter Konsistenzcheck in der Onlinehilfe (Verweis auf Men�s,
  Dialoge, Bilder, Querverlinkung).

- Eingabefelder gegen Fuzzy-Eingaben per Clipboard stabilisiert, um
  provozierte Abst�rze zu vermeiden.


b) �nderungen in der Benutzer-Dokumentation / Web-Darstellung:

- Online-Hilfe: erweitert.

- Skript: Behebung kleinerer Fehler, Men�baum in Anhang A2 der neuen
          CrypTool-Version angepasst.

- Aktualisierte und auf rund 120 Seiten erweiterte Pr�sentation.

- Neue CrypTool-Webseite mit Joomla seit April 2008.


c) Funktionale Erweiterungen:

- Bugfixes:
  - Viele kleine Verbesserungen in den Masken:
    Benutzerf�hrung; Refesh; Cursor korrekt auch nach Dialogwechsel;
    bei DH, Hill und Seitenkanalangriff einheitlich H�kchen f�r die Anzeige
    von Detaildialogen und die Erstellung von Logfiles.
  - AML-Datei f�r die DES-Animation mit ANIMAL korrigiert (in der Matrix
    K[1] war ein Bit auf 1 statt auf 0). Dank an aufmerksame Benutzer!
  - Installer behandelt schon installierte Versionen nun besser.

- Installer ordnet die Datei-Endung AES dem AES-Tool zu; und tr�gt das
  AES-Tool optional in das Kontextmen� "�ffnen mit ..." im Windows-
  Explorer ein.

- Das Men� "Hilfe" innerhalb der CrypTool-Anwendung enth�lt nun auch den
  Aufruf der CrypTool-Pr�sentation.

- Im Textoptionen-Dialog gibt es nun auch ein H�kchen f�r deutsche
  Umlaute zum Zusammenklicken des gew�hlten Alphabets.

- Textdateien k�nnen nun in Bl�cken einstellbarer Breite dargestellt
  werden. Z.B. im Format  xxx xxx xxx  oder  xxxxx xxxxx xxxxx ...
  Auch Konversion in Gro�- oder Kleinbuchstaben einstellbar.

- Erweiterung der Editoren:
  * Hex-Editor / Hex-Control / HexView:
     - Suchen und Ersetzen (incl. Hex-Nullen) auch im Hexbereich.
     - Undo/Redo.
  * Text-Editor:
     - Suchen und Ersetzen sowohl mit ASCII wie mit Hexstrings synchron.
     - Redo.

- Die ADFGVX-Chiffre kann nun das durch die Textoptionen definierte
  variable Alphabet nutzen (nicht mehr nur die 26 Gro�buchstaben).

- Erweiterung der Brute-Force-Analyse symmetrischer Verfahren (Henk -- danke
  f�r die praktischen und didaktischen Anregungen):
  - Einstellen des Alphabets f�r den erwarteten Klartext, um die Suche
    nach einem m�glichen richtigen Schl�ssel einzuschr�nken.
  - Anbieten der 50 Klartexte mit den niedrigsten Entropiewerten zur Auswahl.

- Das AES-Tool in der Version 2.5 ist schneller bei gro�en Dateien.

- Das Lernprogramm/Lernspiel "Zahlenhai" in der Version 1.1.5 wurde etwas
  korrigiert und vor allem die Onlinehilfe erweitert.

- SHA2-Familie (SHA-256, SHA-384, SHA-512) erg�nzt bei der Berechnung
  des Hashwertes einer Datei
  http://csrc.nist.gov/publications/fips/fips180-2/fips180-2.pdf

- Verbesserung des Passwort-Quality-Meters, indem eine eigene Komponente
  zur Bewertung mit realistischen Annahmen �ber den Angreifer erg�nzt
  wurde.

- Der Passwort-Entropie-Dialog erlaubt es, zuf�llige Passworte zu erzeugen,
  die eine �hnlich hohe Sicherheit bieten wie zuf�llig erzeugte
  Bin�rschl�ssel f�r symmetrische Verfahren bei einer vorgegebenen Bitl�nge.
  Au�erdem kann man das Alphabet des Passwortes vorgeben: neben den
  bisherigen Textoptionen gibt es z.B. das WLAN-Passwort-Alphabet.



3. M�gliche Punkte f�r eine Weiterentwicklung -- Ideen, Anfragen
   -------------------------------------------------------------

Generell sollen alle gr��eren Neuerungen ab nun in die beiden Zukunftsprojekte
einflie�en (siehe Kapitel 3.5).

In CrypTool 1.x werden weiterhin Fehler behoben bzw. Funktionen von
Mitwirkenden aufgenommen, die weiter in C/C++ implementieren wollen.

3.1. Funktionalit�t: Algorithmen / Verfahren
     ---------------------------------------
- Weitere Algorithmen zu jedem Thema implementieren:
    * Codes:
       - T9 etc.  (http://de.wikipedia.org/wiki/Text_on_9_keys)
    * Verschl�sselung:
       - Klassische Verfahren (incl. Analyse):
           - Flei�ner-Schablone
           - Weitere Rotorchiffren, Hagelin, Lorenz-Maschine, Purple.
       - Symmetrische Verfahren:
           Camellia (RFC3713), RC5 und Gost (http://vipul.net/gost),
           Radio Gatun, SOSEMANUK, VSH, ...
       - Public Key-Verfahren: McEliece, Rabin, NTRU.
       - Demonstration der Visuellen Kryptographie
       - Neue Verfahren von Ecrypt (Network of Excellence in Cryptology)
         integrieren. Siehe http://www.ecrypt.eu.org/.
    * Hashverfahren:
       - Tiger (http://www.cs.technion.ac.il/~biham/Reports/Tiger/)
    * Protokolle / Protokollschw�chen:
       - Visualisierung von Man-in-the-Middle-Angriffe
       - Blind Signatures
       - Elektronische Wahlen
       - Tripartite Schl�sselvereinbarung (geplant f�r Java-CrypTool)
       - Kleptographie (http://www.cryptovirology.com/)

- Schnelle Auswahl der verschiedenen Verschl�sselungsverfahren
  �ber eine Dialogbox statt �ber die Men�s (Offenlegung aller
  Steuerparameter der Algorithmen) (analog CryptoBench).

- Kryptographisch starke elliptische Kurven erzeugen und damit
  Implementierung eines auf Elliptischen Kurven basierenden
  Kryptosystems. Dazu k�nnte man das Kryptosystem von Menezes
  und Vanstone nehmen, das 1993 von diesen Autoren vorgeschlagen
  wurde: A. Menezes and S. Vanstone,
         "Elliptic curve cryptosystems and their implementation",
         Journal of Cryptology, 6 (1993), Seite 209-224.

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
  - Nutzung der schon eingebauten 3-D-Darstellung von Zufallsdaten,
    um dem Nutzer m.H. der beim Drehen sichtbaren Hyperebenen die
    Schw�chen von Zufallsgeneratoren (z.B. bei LCG) zu verdeutlichen.

- Weitere Standards implementieren und direkt �ber die Men�s bzw.
  aus der Online-Hilfe heraus an alle Stellen verzweigen, wo diese
  Standardverfahren (z.B. PKCS#5) verwendet werden (Hauptarbeit
  dabei sind das User Interface und die Dokumentation).

- Verbindung zwischen CrypTool (PKCS#12) und PGP schaffen, indem
  man PGP-Keys in CrypTool verwenden kann. Idee: Per Passwort-Eingabe
  �ffnet man seinen privaten Keyring, analysiert die Struktur, holt den
  Key heraus (PGP-Sourcen sind gegeben) und nutzt diesen, um mit den in
  CrypTool implementierten Verfahren PGP-Files zu entschl�sseln oder zu
  signieren. Damit wird klar, dass auch PGP die Standard-Algorithmen nutzt.

- CrypTool als Demonstrator f�r XML-Signaturen (geplant f�r Java-CrypTool).

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



3.2. Funktionalit�t: Analyse
     -----------------------
- W�nschenswert w�re, wenn insbesondere die Analyse in allen Formen und
  ihre Visualisierung weiter ausgebaut werden k�nnte.

- Zu allen Verschl�sselungsverfahren eine (gute) Analyse anbieten, die
  (zumindest f�r die klassischen Verfahren besser ist als Brute-Force).

- Angriff auf symmetrische Verschl�sselungsverfahren, bei denen die
  Parameter der Verschl�sselungsverfahren flexibel reduziert werden
  k�nnen.

- Differentielle Kryptoanalyse auf symmetrische Chiffren (DES, ...).

- Die Brute-force-M�glichkeiten erweitern: Nutzen von Wissen
  - um Teile des Klartextes
  - um Teile des Schl�ssels.

- Demo, wie lange eine vollst�ndige Schl�sselsuche dauert (in Abh�ngigkeit
  von der Schl�ssell�nge).

- Analyse neu implementieren f�r:
   * homophone Verschl�sselung
   * Permutationen/Transpositionen
   * Playfair-Verschl�sselung
      - C-Sourcen (Gunnar-Andresson) liegen uns vor.

- Analyse verbessern f�r:
   * monoalphabetische Substitution
      - explizite Anzeige von vertauschten Digrammen wie "ie"/"ei"
        und von Doppelzeichen wie "mm".
      - Ersetzte Buchstaben in der Dialogbox nicht nur gro�, sondern
        auch in roter Schrift anzeigen.
   * W�rterb�cher f�r alle Angriffe benutzen, nicht nur f�r die
     Substitution.

- Nutzung von Algorithmen aus dem Bereich KI (K�nstliche Intelligenz) und
  GP/GA (Genetic Programming/Algorithms) zur Analyse (klassischer)
  Verschl�sselungsverfahren.

- Massenmustersuche: Erweiterte hoch performante Mustersuche, die
  nach vorgegebenen normierten und regul�ren Mustern beliebiger L�nge
  sucht (z.B. um alle Patterns in einer Datei zu finden, die auch in 
  einer anderen (vorzugebenden) Datei vorkommen), oder die nach 
  unbekannten, aber mehrfach vorkommenden Mustern in Dokumenten sucht.
  K�nnte dann auch um Ersetzen erweitert werden.

- Suche nach Patterns m.H. von Normierungen (z.B. "einen" = 12313).
  C-Souren dazu liegen vor.

- Korrekturm�glichkeit einzelner Zeichen bei der Analyse von XOR,
  ADD, Vigen�re. Ausschluss unverschl�sselter Bereiche.

- Anzeigen des zweit-, dritt-, ... -besten Treffers bei der
  XOR/ADD-Analyse (dies kann zu einer k�rzeren Schl�ssell�nge
  f�hren).

- Autokorrelation: vor der �berlagerung noch Operationen auf den
  Bl�cken ausf�hren (XOR, ADD, ...). Macht das Sinn?

- Editieren der Homophonen-Schl�ssel (ben�tigt bei der Analyse
  der Homophonen Verschl�sselung).

- Gleitende Entropie: Automatische Anzeige der entsprechenden Stellen
  mit hoher Entropie.xxxxxxxxxxxxxxxxxxxx

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
    Spalten-Caesar (d.h. bei einer ermittelten Schl�ssell�nge von
    n wird das Caesar-Verfahren f�r jeden Wert von i jeweils auf die
    Zeichenmenge m[i+k*n] mit 1<=i<=n und k>=0 angewandt) die
    Grafiken Korrelation und ASCII-Histogramm erstellt.
    Zus�tzlich k�nnte man noch den Text des jeweiligen Spalten-
    Caesars ausgeben.

- Timing Attack auf RSA / Vorteile Blinding.

- Aktuelle Hashangriffe darstellen (z.B. Erstellen von PS-Dokumenten nach
  Lucks oder von PDF-Dokumenten nach BSI mit gleichem Hashwert) und
  Aufzeigen der Anwendungsszenarien.

- Nutzung von Rainbow-Tabellen.

- Angriff auf WEP-Protokoll (geplant f�r Cryptool 2).

- Weitere Angriffe auf konkrete Protokolle implementieren und/oder
  visualisieren, um zuk�nftige Konzepte zu verbessern.



3.3. Interne Schnittstellen / Editoren
     ---------------------------------
- Alle Anzeigemodule in einem konsistenten Klassenbaum
  zusammenfassen.

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

- Langzahl- und Kryptobibliotheken:
   - Unterst�tzung weiterer Libraries (LiDIA, FLINT/C, 
     Wei Dai's Crypto++, ...).

- Vorhandene Einschr�nkungen in der N-Gramm-Analyse bzgl. Dateigr��e
  ausdehnen (evtl. mit Benutzerfeedback und der M�glichkeit abzubrechen,
  wenn viel Zeit erforderlich).


3.4. User-Interface / Visualisierungen
     ---------------------------------
- In den Dialogen in CrypTool k�nnen Zahlen nicht immer in allen
  Darstellungsarten eingegeben werden (z.B. kann im Dialog 
  RSA-Kryptosystem die zu verschl�sselnde Nachricht als Text mit frei
  einzustellendem Alphabet und als Zahl mit 4 verschiedenen Basen) 
  eingegeben werden; die Primzahlen dagegen kann man "nur" als Zahl 
  im Zehnersystem bzw. als Ausdr�cke mit Zahlen im Zehnersystem 
  eingeben). Alternative w�re ein a-modales Umrechnungsdialog-Fenster.

- N�tzlich w�re es, wenn man aus CrypTool heraus einen Taschenrechner
  als a-modales Fenster aufmachen k�nnte, der Terme mit Zahlen 
  beliebiger Basis als Eingabe nimmt und die Ausgabe in mehreren
  Feldern in verschiedenen Zahlensystemen parallel anzeigt. Von hier
  aus sollte man dann die Zahlen per Knopfdruck ins Clipboard bringen
  k�nnen oder per Maus in die Eingabefelder der CrypTool-Dialogboxen
  ziehen k�nnen.

- Weiterhin w�re eine Anbindung an das CAS-System SAGE w�nschenswert
  (http://www.sagemath.org/).

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
   - Angriffe auf schwache RSA-Schl�ssel sind in der Onlinehilfe
     beschrieben: Siehe Men� Hilfe \ Szenarien (Tutorials) \
     RSA-Kryptosystem (Demonstration), unter dem Abschnitt 
     "3. Angriff auf das RSA-Verfahren", wo erkl�rt wird, dass die
     Faktorisierung des Moduls das Verfahren knacken kann.
     Dies ist implementiert, aber nicht visualisiert.
   - Angriffe auf andere asymmetrische Verfahren sind in CrypTool
     bisher noch gar nicht behandelt. Um Diffie-Hellman, DSA oder
     EC-DSA anzugreifen, muss man "diskrete Logarithmen" berechnen.
     Auch dies k�nnte man nach dem Implementieren wieder 
     visualisieren.
   - Visuelle Komposition von Protokollen und Workflows
     (geplant f�r Cryptool 2).



3.5. Roadmap: Portierung nach Linux, Zukunftsprojekte mit Java/Eclipse und C#/.NET
     -----------------------------------------------------------------------------

a) Generelle Wunschliste anhand des Benutzerfeedbacks.
   Dies gilt f�r beide Zukunftsversionen Java-CrypTool und Cryptool 2:
   - Moderne Pure-Plugin-Architektur.
   - Moderneres Layout, weniger Dialogboxen-Wechsel.
   - Absolute Standardkonformit�t in der Bedienung.
   - Mehr Benutzerinteraktion, Actionhistorie.
   - Alle Sprachen in einem Programm, einem Setup.
   - Dynamischer Wechsel den Sprachen.
   - Dynamischer Wechsel zwischen Kryptoprovidern.
   - Teil-Updates aus dem Internet.
   - Mehr Funktionen als Thread implementieren (parallel, alle abbrechbar).
   - Einfacheres Erstellen von Kaskaden zusammengestellt aus den
     existierenden Elementen.
   - Anbieten eines Recorders f�r Benutzereingaben.
   - Alle Dateien als Stream nutzen, um auch sehr gro�e Dateien bearbeiten
     zu k�nnen.
   - Steuerung auch von der Kommandozeile.

b) Java-CrypTool (JCrypTool, JCT):
   - Komplett neu designtes CrypTool in Java mit Eclipse/RCP.
   - Plattform-unabh�ngig.
   - Nutzt strikt die Standards von Eclipse.
   - Nutzung von SWT (und Jigloo) f�r die GUI.
   - Verf�gbar sind eine Secude-Lib, Bouncy-Castle und FlexiProvider.
   - Meilenstein 1, ver�ffentlicht im August 2007, war f�r Entwickler und
     zeigte, dass die Konzepte umsetzbar sind.
     Meilenstein 2 kommt im Juli 2008, und wird auch schon f�r den
     Endbenutzer sinnvoll verwendbar sein.
   - Weitere Entwickler, Architekten und Designer sind in diesem Projekt
     herzlich willkommen.
   - Hoher Lerneffekt bei Programmieranf�ngern.
   - Enge Zusammenarbeit mit dem Lehrstuhl Prof. Buchmann, TU Darmstadt.
   - Nutzung von SourceForge mit Subversion zur Sourcecode-Verwaltung:
     http://jcryptool.sourceforge.net/ .

c) Cryptool 2.0 (CT 2)
   - Komplett neu designtes CrypTool in C# mit dem .NET-Framework.
   - Nutzt strikt die Standards von Microsoft (.NET, Look wie Office 2007).
   - Nutzung von Windows Presentation Foundation (WPF) zur Gestaltung
     von multimedialen Oberfl�chen (GUI).
   - Das gesamte Projekt l�sst sich mit der kostenlosen VS2008-Express-
     Edition f�r C# erstellen.
   - Verf�gbar sind die .NET Krypto-Provider, und Bibliotheken wie GMP und
     Crypto++ per Wrapper.
   - Die Alphaversion, ver�ffentlicht im April 2008, ist f�r Entwickler.
     Die erste Betaversion (f�r Entwickler und Nutzer) ist f�r Sp�tsommer
     2008 geplant.
     Mit der Releaseversion von CT2 wird die Entwicklung von CrypTool 1.x
     eingestellt.
   - Weitere Entwickler und graphisch anspruchsvolle Designer sind
     in diesem neuen Projekt sehr herzlich willkommen.
   - Hoher Lerneffekt bei Programmieranf�ngern.
   - Enge Zusammenarbeit mit dem Lehrstuhl Prof. Weis in Duisburg-Essen.
   - Nutzung von Subversion zur Sourcecode-Verwaltung.

d) Portierung von CrypTool 1.4.x nach Linux mit Hilfe von GCC 4.x und Qt 4.x:
   - Die Bibliotheken von Secude, Miracl, NTL, OpenSSL und GMP stehen
     zur Verf�gung.
   - Trennung der Gesamtaufgabe in sinnvolle Teile:
       - Oberfl�che: Hier liegt die Hauptarbeit.
       - Funktionalit�t, implementiert in purem C/C++: ok
       - Online-Hilfe in HTML: ok.
   - Die erste Beta wurde im November 2007 ver�ffentlicht.
     Die zweite Beta ("first functional version") ist f�r Sp�tsommer 2008
     geplant.
     Danach soll CrypTooLinux auch unabh�ngig von CrypTool 1.x weiter
     entwickelt werden.
   - http://www.cryptoolinux.net/



3.6. Sinnvolle Aufgaben f�r jemand, der neu anf�ngt mit zu entwickeln
     ----------------------------------------------------------------
- Einbau weiterer klassischer Verfahren wie z.B. Autokey, Nihilist
  oder Enigma (ohne Animation).

- Einbau des RC5-Algorithmus wie oben beschrieben, um zu sehen,
  an welchen Stellen �berall die Sourcen daf�r zu erg�nzen sind
  (Funktion selbst, Optionen, Men�s + Statuszeileninfo, Online-Hilfe).

- Alle m�glichen Arten von Transpositionen und Superpositionen
  in einem ansprechenden Dialog anbieten.

- Ausgabe der pro Verschl�sselungsverfahren gespeicherten Schl�ssel
  in einer Liste.

- Pattern-Matching-Dialoge.




4. Beschr�nkungen und Voraussetzungen
   ----------------------------------

4.1. Anwendungsbereich dieser Lern-, Trainings- und Awareness-Software
     -----------------------------------------------------------------
CrypTool dient vor allem Ausbildungs- und Awareness-Zwecken. Man soll
es ohne vorherige Konfiguration sofort benutzen k�nnen.

Das Entwicklungsziel von CrypTool war also nicht, dass damit produktiv
verschl�sselt wird oder dass damit eine CA (Certification Authority)
betrieben wird -- auch wenn die Funktionen korrekt in CrypTool 
implementiert sind.

Beispielsweise steht - im Unterschied zu produktiven CA-Applikationen -
das CA-Schl�sselpaar fest in der Software (Source und Binary) und es
ist gesch�tzt mit einer ebenfalls bewusst sehr einfachen PIN f�r die
CA-PSE (Personal Security Environment).

Der Rootschl�ssel der in CrypTool 1.4.20 eingebauten CA hat eine L�nge
von 2048 Bit und ist 20 Jahre g�ltig (06.07.2006 - 06.07.2026).
Zertifikate, die mit dem alten Rootkey aus fr�heren CrypTool-Versionen
(1.3.05 und �lter) ausgestellt wurden, k�nnen nicht in Version 1.4.20
importiert werden.

Beachten Sie also beim Umgang mit Zertifikaten, dass jedes CrypTool-
Programm eine Root-CA mit demselben Schl�sselpaar beinhaltet, mit 
der die im Programm erzeugten User-Zertifikate signiert werden. 
D.h. jeder (!), der CrypTool einsetzt, kann User-Zertifikate mit 
dieser eingebauten CA signieren.

Professionelle PKI-Software wie z.B. die OpenXPKI, die FlexiTRUST von
FlexSecure, Entrust, die Secude-CA oder die Microsoft-CA managen zus�tzlich
den ganzen Lebenszyklus von Zertifikaten, bieten CRL-Handling, sorgen f�r
eindeutige Seriennummern und nutzen definierte Registrierungsprozesse.

Die in CrypTool vorhandenen modernen Krypto-Verfahren sind entsprechend
den internationalen Standards implementiert und genauso "gut" wie in
kommerziellen Anwendungen.


4.2. Win32-Umgebung und Java-Runtime
     -------------------------------
CrypTool erfordert eine Win32-Umgebung.

Einige Funktionen (ANIMAL, ECC-Demo) erfordern zus�tzlich eine Java
Runtime-Umgebung JRE 1.5.

Die minimale Rechnerausstattung liegt bei 300 MHz CPU, 256 MByte RAM,
40 MByte Festplattenplatz (geringe Anforderungen).

Die Lauff�higkeit von CrypTool 1.4.20 wird unterst�tzt f�r Windows XP
und Windows Vista.

Weder f�r die Installation noch f�r die Benutzung sind Administrator-
Rechte notwendig, aber man braucht als Benutzer Schreibrechte in dem
Verzeichnis, wo CrypTool installiert ist.

Verschiedene Sprachversionen kann man parallel auf einem Rechner
installieren.

Persistente Daten werden nur in das CrypTool-Verzeichnis, in das Standard-
Windows-Verzeichnis f�r tempor�re Dateien (TEMP-Verzeichnis) und in
den benutzerspezifischen Bereich der Windows-Registry geschrieben
(Weitere Details siehe Kapitel 2.1) (Es gibt keine INI-Dateien).
xxxxxxxxxxxxx

Anmerkung: Wo das TEMP-Verzeichnis von Windows liegt, kann man sehen,
wenn man in Windows-Explorer %TEMP% eingibt. Den Wert kann man unter
Windows XP auch ansehen und anpassen per "System --> Systemeigenschaften
--> Reiter Erweitert --> Umgebungsvariablen".

CrypTool funktioniert grunds�tzlich auch unter FreeBSD/Linux mit
Wine (mit gro�en Abstrichen an Funktionalit�t und Stabilit�t).
Siehe Anhang 11.1.


4.3. Interaktive Online-Hilfe unter Windows XP
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


4.4. Unterst�tzung verschiedener Sprachen
     ------------------------------------
Programm, Hilfesystem und Dokumentation sind mehrsprachig aus-
gelegt (zur Zeit komplett englisch und deutsch).

In der polnischen und der spanischer Version ist das Programm inklusive aller
Masken und Men�s �bersetzt. Die PDF-Dateien sind noch in Englisch.
In der polnischen Version ist auch die umfangreiche Onlinehilfe �bersetzt;
in der spanischen Version liegt die englische Onlinehilfe bei.

F�r jede unterst�tzte Sprache gibt es bei CrypTool 1.4.20 ein eigenes
Installationsprogramm (Setup).


4.5. Einschr�nkungen / Features
     --------------------------
- Zur Demonstration des RSA-Kryptosystem und zur Faktorisierung von
  Zahlen greift CrypTool auf die Langzahlarithmetik der Bibliothek
  Miracl von Shamus Software Ltd. zu. Die Bitl�nge der Zahlen wurde
  in der CrypTool-Anwendung auf 8192 beschr�nkt. 

- Von Bin�rdateien werden "nur" knapp die ersten 2 GB in den
  Hex-Editor geladen (< 0x7ffff000 = 2.147.479.552 Bytes).
  xxxxxxxxxxxxxxxxx
 
  Textdateien k�nnen dagegen in unbeschr�nkter Gr��e vom Editor geladen
  werden (sofern die Rechnerressourcen reichen).

- Beim Lesen und Speichern von Textdateien wird der Zeilenumbruch immer
  als CR/NL (wie unter Windows �blich) dargestellt. Das bedeutet,
  dass Dokumente, die aus Unix kommen und deshalb den Zeilenumbruch nur
  mit dem Zeichen LF kennzeichnen, l�nger werden [LF wird in CR/NL
  umgewandelt]. Eine Signaturpr�fung kann dadurch auch schief gehen.

- Darstellung von mathematischen Zeichen in der HTML-Hilfe:
  Die Microsoft HTML-Hilfe ruft den eingestellten Microsoft Internet
  Explorer (IE) auf. Version IE 6 hat manchmal Probleme, mathematische
  Zeichen wie die Gauss-Klammer darzustellen.
  Wenn bei Ihnen der IE7 voreingestellt ist, funktioniert es korrekt.
  Die zugrundeliegenden, in das CHM-File eingebundenen HTML-Dateien
  werden von IE7 und Firefox 1.5 und h�her korrekt dargestellt.
  Die Gauss-Klammer wird in der Onlinehilfe zum Modulo-Operator als
  Symbol f�r die n�chstniedrigere ganze Zahl verwendet.

- Aus Performancegr�nden wurde festgelegt, dass CrypTool bei der
  N-Gramm-Analyse die L�nge der Dokumente beschr�nkt:
   - f�r Bin�rdateien auf 64 kBytes und
   - f�r Textdateien auf 256 kBytes.
  Werden l�ngere Dateien ge�ffnet, werden sie -- nur bei dieser Art
  der Analyse -- auf die Maximal-L�nge gek�rzt.

- Hashwerte k�nnen von Dateien beliebiger Gr��e berechnet werden,
  sofern die Dateien nicht geladen werden. 

- Mit dem AES-Tool k�nnen nur Dateien bis 4 GB Gr��e verschl�sselt
  und als selbst-extrahierende Archive abgespeichert werden.
  Erzeugt man nur die rein verschl�sselte AES-Datei ohne Selbstent-
  packungscode kann man auch "beliebig" gro�e Dateien verschl�sseln.

  Bitte beachten Sie, dass die Ausgabe des Standalone AES-Tools nicht
  vollkommen identisch ist mit der Ausgabe, die Sie in CrypTool mit der 
  Men�folge "Ver/Entschl�sseln \ Symmetrisch (modern) \ Rijndael (AES)"
  erhalten (auch nicht, wenn das AES-Tool eine Datei mit der Endung "aes"
  erzeugt). CrypTool selbst verwendet z.Zt. einen festen IV (0), der nicht 
  gespeichert wird. AES-Tool nutzt einen zuf�lligen IV und f�gt diesen 
  zusammen mit dem Dateinamen hinter den verschl�sselten Daten an.


4.6. Mit �lteren CrypTool-Versionen erzeugte Zertifikate und Schl�ssel
     -----------------------------------------------------------------
Vergleichen Sie Kapitel 5.1, wo das Verhalten bei der Installation
beschrieben wird.



5. Installation / Deinstallation / Betrieb
   ---------------------------------------

5.1. Installation und Nutzung von Schl�sseln aus vorherigen Versionen
     ---------------------------------------------------------------
Sie installieren CrypTool, indem Sie das CrypTool-Setup-Programm an
einer geeigneten Stelle im Dateibaum auf Ihrem PC aufrufen.
Standardm��ig wird CrypTool dann in das Verzeichnis 
            "C:\Programme\CrypTool"
installiert. Das Zielverzeichnis kann in der Installationsroutine
ge�ndert werden. Sie m�ssen Zugriffsrechte f�r das Zielverzeichnis haben.

Wenn Sie es als Administrator in "C:\Programme\CrypTool" installieren,
k�nnen Sie CrypTool danach trotzdem als normaler Benutzer ausf�hren.

Wenn Sie den Zielverzeichnis-Namen "CrypTool" �ndern, z.B. in
"CrypTool-1.4.20-Final-D", so wird auch der Eintrag im Startmen�
der Windows-Taskleiste entsprechend ge�ndert.

Besitzen Sie bereits eine fr�here Version von CrypTool, so versucht das
Installationsprogramm, vor der erneuten Installation das alte CrypTool
zu deinstallieren.
Bitte beachten Sie:
- Wenn bei der Deinstallation nicht alle Verzeichnisse/Dateien im
  Programmverzeichnis (meist "C:\Programme\CrypTool") gel�scht
  werden, l�schen Sie diese manuell.
- Bei der Deinstallation von CrypTool werden alle bisher erzeugten
  asymmetrischen Schl�ssel und Zertifikate gel�scht.
  Wenn Sie diese Schl�ssel auch in der neuen Version von CrypTool nutzen
  wollen, gibt es 2 M�glichkeiten:
  a) Sichern Sie vor der Deinstallation das unter dem Programmverzeichnis
     liegende Verzeichnis pse\ mit allen darin gespeicherten Dateien
     in ein anderes Verzeichnis. Alle Dateien darin k�nnen Sie dann nach
     Installation der neuen Version von CrypTool in das neue pse\-Programm-
     verzeichnis.
  b) Alternativ k�nnen Sie RSA- und DSA-PSEs als PKCS#12-Struktur 
     exportieren bzw. importieren.
- Falls Sie Zertifikate, die mit CrypTool-Versionen VOR 1.4.00 erzeugt
  wurden, unter CrypTool 1.4.20 weiter verwenden wollen, gehen Sie bitte
  folgenderma�en vor:
  a) f�r RSA- und DSA-Schl�ssel:
     Exportieren Sie diese PSEs mit Hilfe des alten CrypTools in ein
     PKCS#12-Format und laden Sie diese Dateien im neuen CrypTool.
  b) f�r ECC-Schl�ssel:
     Hier reicht es, die entsprechenden Dateien 
     (z.B. [da][db][EC-prime239v1][1131039030][d] )
     vom alten CrypTool\pse-Verzeichnis in das neue zu kopieren.
xxxxxxxxxxxxxxxx nochmal lesen xxxxxxxxxxx

F�r den Fall, dass mehrere Benutzer dieselbe CrypTool-
Installation verwenden wollen, m�ssen die Zugriffsrechte auf den
Verzeichnissen pse\ und pse\pseca\ und den darin enthaltenen
Dateien f�r alle Benutzer auf Vollzugriff gesetzt werden.

Der Teilbaum "pse\" sollte nicht manuell bearbeitet werden, da
bei einer inkonsistenten Struktur nur eine Neuinstallation von
CrypTool bleibt, um die zertifikatsbasierten Verfahren zu nutzen.


5.2. Installation in Mehrbenutzersystemen
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
Zielverzeichnis ein so genanntes "lokales Verzeichnis" angeben (statt
"C:\Programme"). Lokal und f�r den Benutzer zug�nglich k�nnten z.B. sein:
%ALLUSERSPROFILE% (Die Standardeinstellung im deutschen Windows XP ist: 
"C:\Dokumente und Einstellungen\All Users").

Wenn Sie CrypTool ohne Administratorrechte installieren und keine
Schreibrechte auf %ALLUSERSPROFILE%\Start Menu haben, werden unter WXP
im Startmen� ("Start \ Alle Programme") die Eintr�ge zu CrypTool fehlen.
Jeder Nutzer kann diese Eintr�ge aber manuell in sein eigenes Startmen�
aufnehmen.

Anmerkung: Wie bei %TEMP% auch, k�nnen Sie sehen, wo diese Verzeichnisse
liegen, indem Sie im Windows-Explorer %ALLUSERSPROFILE% oder %userprofile%
eingeben.


5.3. Deinstallation von CrypTool
     ---------------------------
Um CrypTool zu deinstallieren, benutzen Sie bitte das "Start"-Menu in
der Windows-Taskleiste.
Dort gehen Sie zu "Alle Programme" \ "CrypTool".
Dann klicken Sie auf "CrypTool deinstallieren".

Manchmal kann es sein, dass die JAR-Dateien nicht gel�scht werden k�nnen,
da Windows und die JRE melden, dass die Datei noch benutzt wird, obwohl
CrypTool samt aller Stand-alone-Programme beendet wurde.
Nach einem Neustart des Rechners kann man dann die JAR-Datei und das ganze
Verzeichnis l�schen.


5.4. Betrieb in Mehrbenutzersystemen
     -------------------------------
a) Alle Benutzer-spezifischen Einstellungen werden in der lokalen Registry
   gespeichert (auch die zuletzt ge�ffneten Dateien).
 
b) Will der Benutzer in Mehrbenutzersystemen wie Windows XP aus CrypTool
   heraus Dateien anlegen (bzw. �ndern), braucht er Schreibrechte auf das
   entsprechende Zielverzeichnis (bzw. auf die entsprechende Datei). 
   Geht das nicht, kommt eine Warnung.
   Explizit n�tig sind Schreibrechte nur auf 2 Verzeichnisse:
   - das Standard-Windows-Verzeichnis f�r tempor�re Dateien (TEMP)
     f�r die cry*.*-Dateien,
   - das Unterverzeichnis "CrypTool\pse", da darin die erzeugten 
     asymmetrischen Zertifikate und Schl�ssel abgelegt werden.

c) Zentrale Installation auf einem Windows-Netzwerkrechner/Netzlaufwerk:

   Besonders in Schulen wird Lern-Software oft nur auf dem zentralen
   Rechner installiert; die Client-PCs rufen dann das Programm von dort auf.

   Das Programm CrypTool selbst l�uft so auch. Wird aber die Onlinehilfe von
   einem Client-PC aus aufgerufen, wird sie mit den Standardeinstellungen
   des Windows XP-Betriebssystems nicht angezeigt. Das ist kein CrypTool-
   spezifisches Problem, sondern eines aller Windows-Onlinehilfe-Dateien.
   Die HTML-Hilfe zeigt dann normalerweise nur das Inhaltsverzeichnis oder
   den Index, aber nicht die Inhalte der Seiten.

   Onlinehilfe liegt normalerweise in einer CHM-Datei vor, die die einzelnen
   HTML-Hilfeseiten b�ndelt. Innerhalb des Microsoft HTML-Hilfe-Programms
   fungiert der Internet Explorer als Anzeigeprogramm f�r die in der
   CHM-Datei geb�ndelten HTML-Dateien.

   In den ersten XP-Versionen konnte von einem Client aus auch auf 
   Hilfedateien auf einem Server zugegriffen werden. Um eine 
   Sicherheitsl�cke zu schlie�en, wurde das Windows XP-Update
   (KB896358) verbreitet.
   Leider bewirkt der Patch auch, dass die Microsoft HTML-Hilfe die
   eigentlichen Seiteninhalte nicht mehr anzeigt [dagegen werden die
   Metainformationen wie Inhalt, Index und Suchbegriffe korrekt angezeigt],
   wenn man von einem Client aus auf Hilfedateien auf einem Server zugreift.

   Abhilfe:
   Da das Deinstallieren von Sicherheits-Patches keine gute Idee ist, und
   da es in diesem Szenario auch nicht gew�nscht ist, die CHM-Dateien lokal
   zu installieren, kann man einen bestimmten Eintrag in der Registry
   hinzuf�gen bzw. �ndern:
   Wir nehmen an, dass die CHM-Dateien auf einem Server-Laufwerk X: mit
   dem UNC-Pfad "\\dir-1\\dir-2" liegen. Man kann den Client-PCs den Zugriff
   auf das Server-Laufwerk zu erlauben, indem man in der Registry aller
   Clients-PCs folgenden Eintrag aufnimmt:
   [HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\HTMLHelp\1.x\ItssRestrictions]
   "UrlAllowList"="\\dir-1\\dir-2;file://\\dir-1\\dir-2;X:\\dir-1\\dir-2;file://X:\\dir-1\\dir-2"

   ACHTUNG: Generell kann das Bearbeiten der Registry dazu f�hren, dass
   Windows nicht mehr funktioniert. Die Verantwortung f�r diese �nderung
   liegt allein bei Ihnen!
   Um auf einem Client-PC die Registry zu �ndern, braucht man
   m�glicherweise Administratorrechte.

   Weitere Infos: 
    - http://support.microsoft.com/kb/896054
    - http://www.robo-forum.de/cgi-bin/ultimatebb.cgi?ubb=get_topic;f=20;t=000065



6. Liste der Dateien in der Auslieferung
   -------------------------------------
CrypTool wird als komprimiertes, selbst-extrahierendes Archiv in
drei verschiedenen Sprachversionen verteilt:

SetupCrypTool_1_4_20_en.exe    Englische Sprachversion.
SetupCrypTool_1_4_20_de.exe    Deutsche Sprachversion.
Die mit der polnischen Version zus�tzlich ausgelieferten Dateien sind hier
noch nicht ber�cksichtigt.

Diese selbst-extrahierenden Archive enthalten die folgenden Dateien:

ReadMe-de.txt .... Diese Kurzanleitung (deutsch).
ReadMe-en.txt .... Diese Kurzanleitung (englisch).

md5sum.txt ....... MD5-Hashwerte aller Dateien innerhalb des CrypTool-Paketes
sha1sum.txt ...... SHA-1-Hashwerte aller dieser Dateien.

CrypTool.exe ..... Das E-Learning-Programm (deutsch + englisch).
aestool.exe ...... Ein Programm, das Dateien in sich selbst-entpackende
                   Programme verschl�sselt (D + E). Zur Entschl�sselung
                   m�ssen Sie das korrekte Passwort eingeben.
CrypTool-de.chm .. HTML-Hilfe-Archiv f�r die CrypTool-Onlinehilfe in
                   deutsch.
CrypTool-en.chm .. Die englische Version von "CrypTool-de.chm".

EC-Param.ini ..... Initialisierungsdatei f�r auf Elliptischen
                   Kurven basierende Public Key-Verfahren.
TEST-Param.ini ... Initialisierungsdatei f�r die Zufallstests.
secude.dll ....... Bibliothek kryptographischer Funktionen von der
                   Secude IT Security GmbH.
ticket ........... Lizenz f�r die Secude-Bibliothek.
libxml2.dll ...... Wird ben�tigt von der secude.dll.
secidea.dll ...... Wird ben�tigt von der secude.dll f�r die 
                   IDEA-Verschl�sselung.
srndmskb.dll ..... Wird ben�tigt von der secude.dll f�r den 
                   Entropiesammler zur Initialisierung des 
                   Secude-Zufallsgenerators.
db.dll ........... Wird ben�tigt von der secude.dll.
secude.xml ....... Wird ben�tigt von der secude.dll.
libeay32.dll...... Bibliothek aus OpenSSL.
SciLexer.dll ..... Bibliothek mit den Routinen f�r den 
                   Scintilla-Texteditor.

Rijndael-Animation.exe .. Animation (Flash) des AES-Algorithmus.
Rijndael-Inspector.exe .. Animation (Flash) zu den �nderung des Datenblock
                          innerhalb des AES-Algorithmus.
Enigma_de.exe .... Animation (Flash) der 3-Rotor Enigma-Maschine.
Enigma_en.exe .... Die englische Version von "Enigma_de.exe".
Enigma-Help_de.html .. HTML-Onlinehilfe f�r  "Enigma_de.exe" (deutsch).
Enigma-Help_en.html .. Die englische Version von "Enigma-Help_de.html".

eccdemo.jar ...... Demo (Java) zur Punktaddition auf Elliptischen Kurven.

ZT.exe ........... Lernprogramm (Authorware) zur Zahlentheorie.
NT.exe ........... Die englische Version von "ZT.exe".
TextZahlWandler.exe ...... Hilfsprogramm zu "ZT.exe".
TextNumberConverter.exe .. Die englische Version von "TextZahlWandler.exe".
ToolBarWrapper.dll .. Notwendig f�r das Authorware-Programm ZT.exe

Zahlenhai.exe .... Das Programm zum Lernspiel "Der Zahlenhai".
NumberShark.exe .. Die englische Version von "Zahlenhai.exe".
NumberShark_de.chm HTML-Hilfe-Archiv f�r die Zahlenhai-Onlinehilfe (deutsch).
NumberShark_en.chm Die englische Version von "NumberShark_de.chm".
GameData.txt ..... Die ersten High-Scores f�r das Zahlenhai-Spiel.

script-de.pdf .... Ein Skript (deutsch) �ber Kryptographie, Primzahlen,
                   elementare Zahlentheorie und die Mathematik hinter
                   einigen Algorithmen.
script-en.pdf .... Die englische Fassung von script-de.pdf.

CrypToolPresentation_1_4_20_de.pdf .. Folien-Pr�sentation (deutsch)
CrypToolPresentation_1_4_20_en.pdf .. Folien-Pr�sentation (englisch)

DialogSchwestern.pdf .. Fantasy-Geschichte von Dr. Elsner, in der
                        eine Variante des RSA-Kryptosystems
                        beschrieben wird.
DialogueSisters.pdf ... Englische Fassung von DialogSchwestern.pdf.
ChinLab-de.pdf.pdf .. Geschichte von Dr. Elsner �ber zahlentheoretische
                      Probleme, die Marco Polo vom Gro�en Khan gestellt
                      werden.
ChinLab-en.pdf.pdf .. Englische Fassung von ChinLab-de.pdf.

Uninstall.exe .... Teil des NSIS-Installers.


examples\ ........ Dieses Verzeichnis enth�lt unterschiedliche
                   Beispieldateien, die in den Szenarien verwendet
                   werden. Dateien mit der Endung ".txt" sind
                   Textdateien. Alle anderen Dateien sind bin�r.
                   Dateien mit dem Format "XX-enc-YY.*" sind
                   verschl�sselte Dateien. Bitte ver�ndern Sie
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
        \state2.hex ....... unverschl�sselte Beispieldaten aus ...
        \state2-enc.hex ... verschl�sselte Beispieldaten aus ...
                            "Rijndael-Animation.exe",
                            verarbeitet mit "CrypTool.exe". 



cryptochallenges\ ... Dieses Verzeichnis enth�lt Dateien mit Chiffraten.
                      Die meisten sind historischer Natur, einige davon
                      sind ungel�st.
                      Zwei Herausforderungen sind auch dabei: die
                      Doppelw�rfel-Chiffre und die HarryPotter-Chiffre.

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


pse\ ............. In diesem Verzeichnis und in seinem
                   Unterverzeichnis pseca\ werden erzeugte
                   (asymmetrische) Schl�ssel und Zertifikate abgelegt.

pse\[SideChannelAttack][Bob][RSA-512][1152179494][PIN=1234].pse

pse\pseca\calog    Diese Dateien sind f�r die Verwaltung der
         \capse    Schl�sseldatenbank notwendig.
         \CA_exts
         \cert.dir
         \cert.pag
         \CRL_exts
         \crls.dir
         \crls.pag
         \user.dir
         \user.pag


animal\ .......... Dieses Verzeichnis enth�lt die Dateien, die f�r
                   das Animationsprogramm ANIMAL n�tig sind.

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


Bc\ .............. In diesem Verzeichnis und darunter liegt das Utility
                   BC zum Rechnen mit beliebig langen Zahlen. Es geh�rt 
                   zu "ZT.exe" und kann direkt daraus gestartet werden.
                   Nur bc.exe und bc.1.txt sind im Original dabei; die
                   restlichen BC-Dateien stammen vom "ZT.exe"-Autor
                   und beinhalten Skripte mit Funktionen.

Bc\bc.1.txt
  \bc.deutsch.txt ... �bersetzung von bc.1.txt
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


xtras\ ............ Geh�rt zu Authorware, mit dem "ZT.exe" erstellt wurde.

xtras\BMPVIEW.X32
     \MIX32.X32
     \VIEWSVC.X32




W�hrend der Laufzeit von CrypTool werden die folgenden Dateien
erzeugt und verwaltet:
cry*.* ........... CrypTool schreibt tempor�re Dateien mit dem
                   Namensmuster cry*.* in das TEMP-Verzeichnis.
       Diese Dateien haben folgende Endungen: 
                   txt -> Textdatei-Ansicht
                   hex -> Hexadezimale (bin�re) Ansicht
                   plt -> Diagramm/Plot-Ansicht (Histogramm, Autokorrelation)
                   ogl -> OpenGL-Graphics-Ansicht
                   org -> Kopie der Originaldatei nach dem Laden
                   tmp -> Tempor�re Datei f�r Zwischenberechnungen


6.1. �berpr�fen der Integrit�t der heruntergeladenen Dateien
     -------------------------------------------------------
Die Integrit�t von Dateien kann mit Hashwerten �berpr�ft werden.
Hashwerte sind wie Fingerabdr�cke -- mit einer sehr geringen
Informationsmenge kann man ein viel gr��eres Objekt identifizieren.

Die Dateien vom CrypTool-Projekt kommen normalerweise dadurch auf
Ihren Computer, dass das Archiv (Setup-Datei) heruntergeladen und
die darin enthaltenen Dateien entpackt werden:
a) Herunterladbare Dateien:
   Auf der Homepage von CrypTool www.cryptool.de finden Sie
   die Hashwerte aller von der deutschen Webseite direkt
   herunterladbaren Dateien in den Dateien md5sum.txt bzw.
   in sha1sum.txt.
   Wenn man den Hashwert einer heruntergeladenen Datei neu berechnet
   und mit den Werten auf der CrypTool-Homepage vergleicht, kann man
   sehen, ob man eine unver�nderte Kopie der Originaldatei hat oder
   nicht.
   Weichen die Hashwerte voneinander ab, sollte man die Datei noch
   einmal herunterladen und evtl. die Ursache daf�r suchen, dass
   man eine ver�nderte Datei auf seinem Rechner hat.
b) Zus�tzlich k�nnen Sie auch die Dateien INNERHALB des 
   heruntergeladenen Setup-Paketes �berpr�fen:
   Deren Hashwerte stehen in den Dateien md5sum.txt bzw. sha1sum.txt,
   die als Teil des Paketes mitentpackt werden.

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



7. Kurze Historie der freigegebenen Hauptversionen
   -----------------------------------------------

Version   Datum         Gr��e des Windows-Setups  Plattenplatz  Freigabe
                         Deutsch    Englisch                     durch
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
1.4.20    Juni 2008      36,7 MB     35,9 MB         72 MB        DB

Bemerkungen zu den Versionen:
1.3.02    Viele neue Funktionen gegen�ber 1.3.00.
1.3.03    Viele kleine Bugfixes und Verbesserungen der Dokumentation.
1.3.04    Etliche neue Funktionalit�t, einige kleine Bugfixes, und Verbes-
          serung und Erweiterung der Dokumentation (Online-Hilfe, Skript).
1.3.05    Kleine Bugfixes.
1.4.00-Beta10  Dez. 2005  Erste �ffentliche Beta von Version 1.4.00.
1.4.00-Beta12  M�rz 2006  Zweite �ffentliche Beta von Version 1.4.00.
1.4.00-Beta14  Juli 2006  Dritte �ffentliche Beta von Version 1.4.00.
1.4.00    Viele neue Funktionen gegen�ber 1.3.05.
1.4.10-Beta04  Mai  2007  Erste �ffentliche Beta von Version 1.4.10.
1.4.10-Beta06  Juli 2007  Zweite �ffentliche Beta von Version 1.4.10.
1.4.10    Funktionsumfang und Onlinehilfe stark erweitert i.Vgl. zu 1.4.00.
1.4.20-Beta03  Mai  2008  Erste �ffentliche Beta von Version 1.4.20.
1.4.20    Funktionsumfang und Onlinehilfe erweitert i.Vgl. zu 1.4.10;
          Vor allem Feinschliff und Code stabilisiert.



8. Feedback
   --------
Sollten Sie Probleme haben oder Fehler finden, wenden Sie sich
bitte mit einer ausf�hrlichen Beschreibung des Problems (und einigen
Bildschirmbildern dazu) per E-Mail an eine der in Kapitel 9 genannten
Personen oder an die Mailingliste.

F�r Anregungen jeglicher Art bez�glich CrypTool sind wir immer
dankbar und helfen Ihnen gern, wenn es unsere Zeit erlaubt.

Auch w�rden wir uns freuen, wenn Sie uns mitteilen, wie und wo Sie
CrypTool einsetzen.



9. Kontaktadressen
   ---------------
- esslinger@fb5.uni-siegen.de
- joerg-cornelius.schneider@db.com
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

10.1.5. Datenschutz PRAXIS (Juni 2005)
        ------------------------------
In der deutsch-sprachigen Fachzeitschrift "Datenschutz PRAXIS",
Ausgabe Juni 2005 erschien unter dem Titel "Spielend verschl�sseln lernen
mit dem kostenlosen CrypTool" ein 2-seitiger Artikel �ber CrypTool von
Dr. Rainer W. Gerling.
Diesen Artikel finden Sie im Internet unter
http://www.interest.de/DP/ausgaben.php?art=188&ID=587903635588.

10.1.6. Report Touch Briefing Information Security (Oktober 2006)
        ---------------------------------------------------------
Der "Touch Briefing Information Security"-Report 2006 enth�lt den Artikel
"The CrypTool Project � Improving Awareness and Education for Cryptology".
Abrufbar im Internet unter:
  http://www.touchbriefings.com/pdf/2259/esslinger.pdf
Mit den Suchbegriffen "awareness cryptology" listeten danach sowohl
google.de wie google.com diesen Artikel auf Platz 1. 

10.1.7. DFN-Mitteilungen, Heft 73 (Dezember 2007)
        ---------------------------------------------------------
Diese Mitteilungen des Deutschen Forschungsnetzes (DFN) enthalten den
4-seitigen Artikel "CrypTool -- Ein E-Learning-Programm f�r Kryptologie".
Abrufbar im Internet unter:
  http://www.dfn.de/fileadmin/5Presse/DFNMitteilungen/heft73.pdf


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

10.2.3. BSI-Software-Suite BOSS 2.0 (Jan. 2007)
        ---------------------------------------------
Das Bundesamt f�r Sicherheit in der Informationstechnik (BSI) hat
CrypTool 1.4.00 als Teil der BSI-Software-Suite "BSI OSS Security
Suite 2.0 (BOSS)" mit ausgeliefert.
Siehe http://www.bsi.de/produkte/boss/index.htm



10.2.4. Nennungen auf verschiedenen Webseiten
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
     - http://de.wikipedia.org/wiki/Cryptool
     - http://de.wikipedia.org/wiki/Kryptographie
     - http://de.wikipedia.org/wiki/Wikipedia:WikiProjekt_Kryptologie
  - Franz�sisch:
     - fr.wikipedia.org/wiki/Cryptool
  - Polnisch:
     - http://pl.wikipedia.org/wiki/Kryptografia
  - Thail�ndisch:
     - http://th.wikipedia.org/wiki/Cryptool

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

Vollst�ndig mit Source-Code verf�gbar sind:

- http://freshmeat.net/projects/crank/
  Crank wurde im Januar 2001 von Matthew Russell begonnen und unter
  der GNU General Public Licence (GPL) freigegeben.
  Im Crank-Projekt sollte unter Linux ein Programm mit grafischer
  Oberfl�che erstellt werden, um das automatisierte Brechen von
  klassischen Kryptoalgorithmen zu erm�glichen.
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
  Griffon ist ein GTK+ GUI Kryptoanalyse-Paket f�r "pre-digital 
  Ciphers". Es enth�lt die folgenden klassischen Verschl�sselungs-
  verfahren: monoalphabetische Transposition, Substitution und Playfair.
  Das Tool liegt nur in englischer Sprache vor.
  Die aktuelle Version 1.0 wurde im November 2000 freigegeben und seitdem
  leider nicht mehr weiter entwickelt.

- http://www.kryptosproject.org/          (alt)
  http://kryptosproject.sourceforge.net/  (neu)
  Kryptos ist Open Source-Projekt, das an der George Mason University begann.
  Krytos ist eine Kryptographie-Lernsoftware mit einer statischen
  Oberfl�che, aber vielen modernen Algorithmen, die dynamisch aus
  verschiedenen Bibliotheken kommen k�nnen.
  Kryptos hat keine Kryptoanalyse-Funktionen.
  Die aktuelle Version Kryptos 3.01 gibt es seit Dezember 2006,
  sie erfordert .NET Framework 2.0.

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

- http://gcipher.sourceforge.net/
  GCipher ist ein kleines Verschl�sselungsprogramm f�r Unix, ohne Onlinehilfe
  und ohne Analysefunktionalit�t. Die drei klassischen Verschl�sselungs-
  verfahren k�nnen sowohl von der GUI, von der Kommandozeile wie als
  Netzwerk-Proxy ausgef�hrt werden.
  Die aktuelle Version 1.0 wurde im Juni 2003 von Shannon -jj Behrens
  ver�ffentlicht.

- http://www.nku.edu/~mcsc/mat494/uploads/CryptoHelper.jar
  Das Java-Programm CryptoHelper.JAR vom "Math and Computer Science Club"
  an der NKU ist ziemlich komplett, was klassische Chiffren angeht.
  Letzter Update: Gary Watson, 2005.


Die einzigen weiteren uns bekannten brauchbaren Programme, die
Kryptographie und Kryptoanalyse (unter einer graphischen
Oberfl�che) verbinden, sind solche, f�r die aber kein Source-Code
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
  Die aktuelle Version 1.0.1 der CryptoBench gibt es seit 2004.
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
eingesetzt wird, und dabei in Schule, Lehre und Training einen guten
Nutzen stiftet. �ber die vielen bisher erhaltenen positiven R�ckmeldungen
freuten wir uns nat�rlich sehr.

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

- Ausgew�hlter Ort 2008 im Land-der-Ideen
  Das Cryptool-Projekt wurde bei dem bundesweiten Wettbewerb "365 Orte im
  Land der Ideen" in der Kategorie Wissenschaft und Technik ausgew�hlt.
  Dazu findet am 22.7.08 an der Universit�t Siegen ein gro�er
  Tag-der-offenen-T�r statt.



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
eine Portierung m.H. von GCC und Qt4 vornimmt (siehe Kapitel 3.5).
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


