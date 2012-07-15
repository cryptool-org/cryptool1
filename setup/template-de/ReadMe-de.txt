==================================================================
    CrypTool, Version 1.4.31 f�r Win32, Juli 2012 (Beta 05) xxx
    (c) Contributors
        Dazu geh�ren z.B.
        Deutsche Bank AG, Frankfurt am Main, und die
        Universit�ten Siegen, Darmstadt, Bochum, Duisburg-Essen und Kassel.
        1998-2012
    Freie Software und Open Source gem�� der Apache Lizenz 2.0
    www.cryptool.org
    Prof. Bernhard Esslinger
    $Id$
==================================================================

 1. ... Kurzbeschreibung des CrypTool-1-Paketes
 1.1. ... Wie Sie als Benutzer am besten starten - Der Einstieg in CrypTool 1
 1.2. ... Was beinhaltet die CT1-Distribution
 1.3. ... Danke
 1.4. ... Maintainer, Hosting, Webseite und Welcome
 2. ... Was bietet CT1 im Detail
 2.1. ... Was k�nnen Sie mit CrypTool 1 machen
 2.2. ... Informationen f�r Entwickler / Wo finden Sie die Sourcen
 2.3. ... Wo finden Sie weitere �berblicke zu CrypTool
 2.4. ... Neuerungen in Version 1.4.20 / 1.4.21
 2.5. ... Neuerungen in Version 1.4.30
 2.6. ... Neuerungen in Version 1.4.31
 3. ... Beschr�nkungen und Voraussetzungen
 3.1. ... Anwendungsbereich dieser Lern-, Trainings- und Awareness-Software
 3.2. ... Win32-Umgebung, Rechte bei Installation und Betrieb, Java-Runtime
 3.3. ... Interaktive Online-Hilfe unter Windows XP
 3.4. ... Unterst�tzung verschiedener Sprachen
 3.5. ... Einschr�nkungen / Features / Tipps
 3.6. ... Mit �lteren CrypTool-Versionen erzeugte Zertifikate und Schl�ssel
 4. ... Installation / Deinstallation / Schl�sselnutzung / Betrieb
 4.1. ... Installation
 4.2. ... Deinstallation von CrypTool
 4.3. ... Wiederholte Nutzung von Schl�sseln
 4.3.1. ... Schl�ssel aus vorherigen Versionen
 4.3.2. ... Schl�ssel gespeichert in den Dateien des PSE-Verzeichnisses
 4.4. ... Installation in Mehrbenutzersystemen
 4.5. ... Betrieb in Mehrbenutzersystemen
 4.6. ... Installation auf einem Netzwerk-Laufwerk --> Onlinehilfe-Problem
 5. ... Liste der Dateien in der Auslieferung
 5.1. ... �berpr�fen der Integrit�t der heruntergeladenen Dateien
 6. ... Kurze Historie der freigegebenen Hauptversionen von CT1
 7. ... Feedback und Kontaktadressen
 8. ... Verweise / Auszeichnungen
 8.1. ... Artikel �ber CrypTool
 8.2. ... Sonstige Referenzen auf CrypTool
 8.3. ... Weitere Freeware-Projekte (Crank, CAP, CryptoStudio, SAGE, etc.)
 8.4. ... Auszeichnungen
A. ... Anhang
A.1. .... Roadmap nach CT 1.4.31
A.2. .... Nachfolger-Projekte mit Java/Eclipse und C#/.NET
A.3. .... M�gliche Punkte f�r eine Weiterentwicklung -- Neue Funktionen, Ideen
A.4. .... CrypTool v1 unter Linux


Benutzte Abk�rzungen:
CT1  CrypTool 1 = CrypTool-Version 1 (diese Version enth�lt diese Readme-Datei)
CT2  CrypTool 2 = CrypTool-Version 2 (l�uft unter .NET)
JCT  JCrypTool  = Java-CrypTool (l�uft unter Win32, Linux und MacOS)


1. Kurzbeschreibung des CrypTool-1-Paketes
   ---------------------------------------
Diese Readme-Datei geh�rt zur Distribution des Programms CrypTool 1.
CrypTool ist Open-Source und kostenlos. Mit CrypTool kann man kryptographische
Verfahren erlernen, ausprobieren und sowohl bekannte wie unbekannte Verfahren
analysieren.
Schon in der Antike wurden solche Verfahren zur Geheimhaltung von Nachrichten
entwickelt. Heutige Verfahren basieren auf moderner Mathematik und erlauben
neben der Verschl�sselung auch die Pr�fung der Integrit�t, die Erstellung von
Signaturen, sichere Authentisierung und Vieles mehr. CrypTool unterst�tzt
sowohl die Ausf�hrung als auch die Analyse solcher Verfahren.

CrypTool 1 wird seit 1998 entwickelt. Im CrypTool-Projekt arbeiten �ber 60
Personen weltweit und ehrenamtlich mit.

Zu jedem Programmteil gibt es reichhaltige Online-Hilfe, die auch
ohne tiefes Kryptowissen verstanden werden kann.

CrypTool 1 existiert in den f�nf Sprachen
- Deutsch,
- Englisch,
- Polnisch,
- Serbisch und
- Spanisch.

In allen Sprach-Versionen hat das Programm die gleiche und volle
Funktionalit�t -- �bersetzt und lokalisiert sind also jeweils die
Oberfl�che (Men�s, Dialoge, etc.) der Programme CrypTool, AES-Tool
und Zahlenhai.

Hier eine Auflistung der restlichen Komponenten des CrypTool-1-Paketes,
die bisher nicht in allen Sprachversionen lokalisiert werden konnten:
                        DE     EN    ES     PL    RS
Onlinehilfe (html)      ja     ja    nein   nein  nein
Readme-Datei (txt)      ja     ja    nein   nein  nein
CT-Skript (pdf)         ja     ja    nein   nein  nein
CT-Pr�sentation (pdf)   ja     ja    ja     nein  nein
Elsner-Stories (pdf)    ja     ja    nein   nein  nein

Im Deutschen und Englischen liegen alle Komponenten von CrypTool 1 �bersetzt
vor. Wenn etwas in einer Sprachversion nicht vorliegt, wird die englische
Komponente beigelegt.

Weitere Sprachversionen (griechisch, russisch, ukrainisch, franz�sisch,...)
sind in Arbeit.

Die aktuelle Release-Version von CrypTool und den Quellcode dazu finden Sie
unter den folgenden Internet-Adressen (dazu ist keine Registrierung n�tig):
                http://www.CrypTool.org
                http://www.CrypTool.de
                http://www.CrypTool.com
                http://www.CrypTool.es
                http://www.CrypTool.pl

Seit Anfang 2010 werden �ber 6000 CrypTool-1-Pakete pro Monat herunter
geladen -- mit wachsender Tendenz (davon entfallen etwas �ber die H�lfte
auf die englische Version).

Zu CT1 gibt es zwei Nachfolger-Versionen, genannt CT2 und JCT.
Deren Download-Zahlen betragen: xxxxxxxxxxxxxxxxxx
               JCT: ca. 1000 / Mt.
               CT2: ca. 3000 / Mt.
Die Nachfolger-Versionen von CT1 bieten einen deutlich gr��eren Funktionsumfang
als von CrypTool 1.

Ziel aller CrypTool-Versionen ist es, kryptographische Mechanismen anschaulich
zu machen und die Verwendung und die Grenzen einzelner Verfahren aufzuzeigen.
In CrypTool 1 sind fast alle State-of-the-art-Krypto-
funktionen implementiert. Dies erm�glicht einen "spielerischen"
Einstieg in die moderne und klassische Kryptographie -- unter
einer einheitlichen Oberfl�che.

CrypTool wird weltweit eingesetzt
- in Unternehmen sowohl zur Mitarbeiter-Sensibilisierung bez�glich
  IT-Sicherheit (Awareness) als auch zur Ausbildung,
- im Schulunterricht und
- in der Lehre an vielen Hochschulen.

Bitte beachten Sie die Lizenz- und Nutzungsbestimmungen f�r
CrypTool. Diese werden z.B. auf der Webseite, bei der Installation und
auf der Einstiegsseite der Online-Hilfe erl�utert.

F�r bisherige Benutzer von CrypTool 1 d�rften in diesem Readme vor
allem die Kapitel 2.6 (Neuerungen in CT 1.4.31) und in Kapitel A.1
(Roadmap nach CT 1.4.31) interessant sein.

Wir laden jeden herzlich ein, an CrypTool mit zu entwickeln oder
Feedback zu geben. Auch f�r Hinweise zu Arbeiten (Diplom-, Doktor-,
Seminar- oder Projektarbeiten), die man in CrypTool integrieren k�nnte,
sind wir sehr dankbar.
Insbesondere junge Entwickler sind eingeladen, sich zu trauen -- sie k�nnen
bei erfahrenen Entwicklern sehr viel �ber professionelle Software-Entwicklung
lernen.
Kontakte: Siehe Kapitel 7 unten.


1.1. Wie Sie als Benutzer am besten starten - Der Einstieg in CrypTool 1
     -------------------------------------------------------------------
Vorausgesetzt wird, dass der Benutzer mit Anwendungen in einer
Windows-Umgebung umgehen kann.

Beim Start von CrypTool 1 �ffnet sich zuerst im Vordergrund ein kleines
Begr��ungsfenster und dann die Arbeitsfl�che von CrypTool.
Wenn Sie im Begr��ungsfenster gleich die F1-Taste dr�cken, erscheint
zus�tzlich die Startseite der Online-Hilfe.

Diese Startseite der Online-Hilfe ist ein guter Ausgangspunkt, um alle
wesentlichen Inhalte von CrypTool kennen zu lernen (z.B. indem man den
Links auf dieser Startseite folgt).
Bitte lesen Sie die Hinweise und Tipps der Hilfe-Startseite.

Einen schnellen Einstieg in die Kryptographie mittels CrypTool
erhalten Sie, wenn Sie einige Szenarien (Tutorials) der Online-Hilfe
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
finden Sie im beigelegten CrypTool-Skript (im Anhang A1 dieser PDF-Datei).

Eine �bersicht �ber alle Funktionen in den verschiedenen CrypTool-Programmen
finden Sie auf der Webseite des CT-Portals (www.cryptool.org) unter dem Men�
"Dokumentation --> CT-Funktionen" oder direkt via:
   http://www.cryptool.org/de/ctp-dokumentation/ctp-functions

Wir w�nschen viel Spa� beim Lernen und beim Ausprobieren der Funktionen
von CrypTool.


1.2. Was beinhaltet die CT1-Distribution
     -----------------------------------
Das CrypTool-1-Paket enth�lt die folgenden vier Hauptbestandteile:

(1) Das Programm CrypTool 1
---------------------------
Hauptteil des CrypTool-1-Paketes ist das Programm CrypTool 1 selbst:

- In CrypTool ist eine umfangreiche Sammlung kryptographischer
  Algorithmen und Protokolle implementiert, die hervorragend
  dokumentiert und teilweise visualisiert sind.
  Somit ist CrypTool sehr gut geeignet zur Ausbildung und zur
  Mitarbeiter-Sensibilisierung f�r IT-Sicherheit.

- Die meisten der kryptographischen Basisalgorithmen stammen aus:
  - der Secude-Bibliothek (http://www.secude.com/),
  - der Miracl-Bibliothek von DCU/CertiVox (vormals Shamus Software)
        (http://www.compapp.dcu.ie/~mike/shamus.html),
  - der OpenSSL-Bibliothek (http://www.openssl.org/),
  - der NTL-Zahlentheorie-Bibliothek von Victor Shoup
        (http://www.shoup.net/ntl/),
  - der APFLOAT-Bibliothek von Mikko Tommila (http://www.apfloat.org/apfloat),
  - der MPIR-Bibliothek f�r beliebig genaue Arithmetik (entstanden aus GMP)
        (www.mpir.org) und
  - der cv act library der cv cryptovision GmbH (www.cryptovision.com).

  Die aktuell benutzten Versionen der inkludierten Bibliotheken finden
  Sie in der Dialogbox "�ber CrypTool" (siehe Hilfe-Men�).

  Somit ist CrypTool auch eine hervorragende Referenzimplementierung
  f�r kryptographische Verfahren.

- Die Kryptoanalyse der meisten der klassischen Verfahren ist
  automatisiert.
  Die Analyse der modernen Verfahren ist eingeschr�nkt, so dass
  CrypTool kein Hackertool ist.

Entwicklungsziel von CrypTool war nicht, dass damit im Wirkbetrieb
eine CA (Certification Authority) betrieben wird [vergleiche Kapitel 3.1]
oder dass damit f�r produktive Zwecke Daten verschl�sselt oder anderweitig
gesichert werden sollten.


(2) Dokumentation
-----------------
Zum Programm geh�rt eine umfangreiche Dokumentation, die ebenfalls
aus vier Teilen besteht:
a) Readme-Datei (diese Datei),
b) Online-Hilfe
    - Kontext-bezogen zur Bedienung des Programms und mit
      weiterreichenden Erl�uterungen,
    - Demos und Beispiel-Szenarien (hier werden Einzelverfahren
      Schritt f�r Schritt erl�utert)
c) Skript zum Thema Kryptographie (beigelegt als PDF-Datei),
d) Pr�sentation, die auf Folien die M�glichkeiten von CrypTool
   aufzeigt (beigelegt als PDF-Datei).


(3) Eigenst�ndige Programme
---------------------------
Die folgenden Programme k�nnen aus CrypTool heraus, aber auch stand-alone
aufgerufen werden:

a) Das Programm AES-Tool v 2.6 (entstanden im CrypTool-Projekt):
   Zum Erstellen selbst-entpackender Executables ist in CrypTool ein
   Programm integriert, das auch eigenst�ndig benutzt werden kann.
   AES-Tool verschl�sselt mit einem Session-Key den Inhalt einer beliebigen
   Dateiinhalt mit dem AES-128 Bit-Verfahren.
   Dieses Verschl�sselungstool kann sowohl als Fensteranwendung als auch
   von der Kommandozeile (z.B. aus einer Batchdatei) aufgerufen werden.
   Bei der CrypTool-Installation wird diesem Programm die Dateiendung "AES"
   zugeordnet.

b) Das Lernspiel "Der Zahlenhai" v 1.2.1 (entstanden im CrypTool-Projekt):
   Dieses Lernspiel bringt Sch�lern den Umgang mit Teilern und Primfaktoren
   n�her.

c) Das Animationsprogramm ANIMAL (siehe http://www.algoanim.info/Animal2):
   Mit diesem an der TU Darmstadt von Dr. R��ling gepflegten Programm
   kann man die Einzelschritte von Algorithmen oder die Komponenten von
   Datenstrukturen beliebig genau modellieren, die Einzelschritte manuell
   vor und zur�ck abspielen oder automatisch ablaufen lassen. Damit kann
   man auch dynamisch Source-Code-Zeilen visualisieren.
   Das Animal-System erlaubt die Erstellung von Animationen mithilfe
   einer GUI, einer Skriptsprache sowie einer Java-API.
   Leider stockt die Weiterentwicklung von Animal seit 2011.
   Weitere Beispiele f�r Animationen finden sich im ANIMAL-Repository:
   http://www.algoanim.info/Animal2/?q=node/284
   Hierzu wird JRE 1.6 ben�tigt (siehe Kapitel 3.2).

d) Ebenso wie ANIMAL sind die ff. Programme eigenst�ndige Java-Anwendungen
   (JAR-Dateien). Hierzu wird jeweils JRE 1.5 ben�tigt (siehe Kapitel 3.2).
   - ECC-Demo v 1.1.1
   - AES-Flussvisualisierung
   - Das Control-Center zur Steuerung der S/MIME-Demo (diese erstellt anhand
     der Parameter eine XML-Datei, die zur Steuerung der aufgerufenen
     Flash-Animation dient).

e) Die Flash-Anwendungen:
   - Rijndael-Animation (visualisiert das Verschl�sselungsverfahren AES),
   - Rijndael-Inspektor (visualisiert die �nderungen der State-Matrix
                         nach jedem Schritt in jeder Runde bei AES),
   - S/MIME-Demo und
   - Enigma (visualisiert das 2.-Weltkriegs-Krypto-Ger�t Enigma).

f) Die Authorware-Anwendung "ZT" (Zahlentheorie) f�hrt in die elementare
   Zahlentheorie ein und visualisiert viele der Verfahren und Konzepte,
   die Grundlage der modernen Public-Key-Kryptographie sind.
   Wo n�tig zeigt sie auch die entsprechenden mathematischen Formeln.
   Dabei k�nnen diese mathematischen Verfahren dynamisch mit eigenen
   kleinen Zahlenbeispielen ausprobiert werden.
   Dazu geh�rt auch das Programm bc v1.06 der Free Software Foundation (FSF),
   mit dem man auf der Kommandozeile beliebig genau rechnen kann.



(4) Geschichten (mit Bezug zu Zahlentheorie und Kryptographie) und R�tsel
-------------------------------------------------------------------------
a) Als PDF-Datei sind zwei Geschichten beigelegt:
   - In "Der Dialog der Schwestern" wird von den beiden Titelheldinnen eine
     Variante des RSA-Verfahrens benutzt, um verschl�sselt zu kommunizieren.
   - In "Das Chinesische Labyrinth" muss Marco Polo zahlentheoretische
     Aufgaben l�sen, um Berater des Gro�en Khan zu werden.

b) Krypto-Wettbewerbe / Krypto-R�tsel:
   Ebenfalls beigelegt sind 13 Dateien mit verschl�sselten Texten, die uns
   freundlicherweise Klaus Schmeh zur Verf�gung stellte, der Autor des
   Buches "Codeknacker gegen Codemacher":
   Klaus Schmeh: "Codeknacker gegen Codemacher. Die faszinierende Geschichte
                 der Verschl�sselung", 2. Auflage, Dezember 2007, W3L-Verlag

   Diese Dateien enthalten einige historisch interessante (gel�ste und
   ungel�ste) Geheimtexte, die Sie als "�bungsmaterial" und Zeitvertreib
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
   Indexeintrag "Krypto-Wettbewerbe") und in dem Buch von Klaus Schmeh.

   Weitere R�tsel und Herausforderungen (Challenges) finden sich auch
   - auf den Seiten von CrypTool-Online und
   - auf den Seiten des Krypto-Wettbewerb "MysteryTwister C3":
     http://www.mysterytwisterc3.org


Alle Einzeldateien, die bei der Installation des CrypTool-Paketes
auf Ihre Platte kopiert werden, sind in Kapitel 5 (unten in diesem
Readme) aufgef�hrt.



1.3. Danke
     -----
Zu CrypTool haben sehr viele verschiedene Personen (�ber 300)
beigetragen -- insbesondere auch ehrenamtlich in ihrer Freizeit.
Einige sind namentlich in der Dialogbox aufgef�hrt, die man erh�lt,
wenn man in der Dialogbox "�ber CrypTool" einen Doppelklick ausf�hrt.
Der Wohnort einiger Entwickler/Mitwirkenden ist auf der CrypTool-Webseite
per Google-Map zu finden (Men� Team).
Herzlichen Dank an alle Mitwirkenden.

Besonders herausheben m�chte ich einige Kernentwickler/-Architekten
im CrypTool 1.x-Projekt, deren hohes und langj�hriges Engagement und
deren hervorragende Kompetenz und Hartn�ckigkeit solche dauerhaften,
lebendigen und erfolgreichen Open-Source-Projekte erst erm�glicht:
J�rg, Henrik, Florian, Peer.

Ebenfalls danken m�chte ich einigen Kernentwicklern/-Architekten in
den Nachfolger-Projekten CT2 und JCT, die mit gro�er Ausdauer und
Kompetenz die Schwierigkeiten mit den allerneuesten Entwicklungsumgebungen
und Software-Architekturen bew�ltigten:
- Arno, Philipp, Thomas, Sebastian, Martin, Timo, Soeren, ...
- Dominik, Matthias, Tobias, Simon, Amro, David, ...

Und nat�rlich den vielen Ungenannten, insbesondere Studenten und
Praktikanten, die viel dazu beitrugen -- und dabei noch mehr lernten
von den Experten im Projekt.

Ebenfalls beigetragen haben z.B. die Deutsche Bank AG, die Technische
Universit�t Darmstadt und die Universit�t Duisburg-Essen.

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
  hinaus gehenden Rechte verbleiben beim jeweiligen Autor.

- Die Firmen (siehe Kapitel 1.2)
  - Secude IT Security GmbH,
  - Shamus Software Ltd und
  - cv cryptovision GmbH
  gestatteten uns gro�z�gigerweise, ihre Krypto-Bibliotheken zu nutzen.
  Diese mit CrypTool 1 verteilten Bibliotheken d�rfen nicht in einem
  Kontext au�erhalb von CrypTool 1 benutzt werden, ohne vorher die erw�hnten
  Firmen zu kontaktieren und nach ihren aktuellen Lizenzbedingungen zu
  fragen.

Ebenso m�chten wir den Open-Source-Entwicklern herzlich danken, die uns
mit ihrem Code Anregungen gaben oder deren Code wir nutzen d�rfen, z.B.
- die Bibliotheken OpenSSL, GMP/MPIR, APFLOAT und NTL,
- die Installations-Software NSIS (http://nsis.sourceforge.net/Main_Page),
- die Texteditor-Software Scintilla (http://scintilla.sourceforge.net),
- das Hex-Control (www.codeguru.com/Cpp/controls/controls/article.php/c5287).

Bedanken m�chte ich mich auch bei
- Herrn Bartosz Sawicki von der Universit�t Warschau, der mit seinem
  Team die erste polnische Version erstellte.
- Herrn Dr. Gonzalo Alvarez von der Universit�t Madrid, der mit seinen
  Kollegen die erste spanische Version erstellte.
- Bojan Dimitrovski von der Universit�t Belgrad, der mit seinen
  Kollegen die erste serbische Version erstellte.
- Greek xxxxxxxxxxxxx
- French xxxxxxxxxxx
- Russian xxxxxxxxxx



1.4. Maintainer, Hosting, Webseite und Welcome
     -----------------------------------------
Der Lehrstuhl f�r Verteilte Systeme, Fakult�t f�r Ingenieurwissenschaften
unter Prof. Dr. Torben Weis an der Universit�t Duisburg-Essen hostet seit
April 2008
- die Webseite von CrypTool,
- das Subversion-Repository f�r die Programm-Sourcen der Release-Version
  CrypTool 1.x, und
- das Subversion-Repository f�r die Programm-Sourcen der Nachfolger-Version
  CrypTool 2.

Die CrypTool-Entwicklergruppe um Prof. Bernhard Esslinger fungiert
als Maintainer von CT1, d.h. sie k�mmert sich um die Pflege des Codes, die
Ver�ffentlichung als Open Source und Freeware, und um die
Koordination der Weiterentwicklung. Die n�chsten Schritte der
Roadmap sind in Kapitel A.1 und auch auf der Webseite ver�ffentlicht.

Die Homepage von CrypTool ist www.cryptool.org.

Wir freuen uns �ber jeden weiteren Entwickler, der sich an der
Weiterentwicklung von CrypTool beteiligt.
Ideen zur Weiterentwicklung finden Sie z.B. in Kapitel A.3.

Ebenfalls sehr willkommen sind uns Ideen und Infos, wie CrypTool in
Lehre, Schule und Ausbildung eingesetzt wird, damit wir dazu
beitragen k�nnen, diese Informationen auszutauschen. Ein Mittel
dazu ist z.B. das Kryptologie-Portal f�r Lehrer (www.cryptoportal.org).



2. Was bietet CT1 im Detail
   ------------------------

2.1. Was k�nnen Sie mit CrypTool 1 machen
     ------------------------------------
Die generellen Eigenschaften und Funktionen von CrypTool 1 sind:

- E-Learning-Programm rund um das Thema Kryptographie und Kryptoanalyse.

- Alles in einem Programmpaket und steuerbar unter einer Oberfl�che.

- Viele klassische Verschl�sselungsverfahren: Und dazu teilweise manuell
  unterst�tzte, teilweise automatische Analysen (Known-Plaintext- und
  Ciphertext-Only-Angriff).

- Codierungen wie Base64 und UU-Encode.

- Nahezu alle modernen symmetrischen Verschl�sselungsverfahren: Und dazu
  jeweils die Brute-Force-Analyse
  (Beim Brute-Force-Angriff auf symmetrische Algorithmen werden Jokerzeichen
   zugelassen und die erwartete Zeit wird ausgegeben.
   Au�erdem kann man die Breite f�r das hierbei genutzte Entropiefenster in
   den Analyseoptionen einstellen, sowie welche Erwartung man an das Alphabet
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
  diese Verfahren implementiert wurden, kann auf Anfrage per E-Mail
  zugesandt werden (sie liegt nur in Deutsch vor).

- Visualisierungen/Animationen/Demonstrationen
  - Demo der Sensitivit�t von Hashverfahren.
  - Visualisierung mit Flussdiagrammen (z.B. beim Diffie-Hellman
    Schl�sselaustausch-Verfahren oder bei der Challenge-Response-Demo),
  - Animationen
     - mit ANIMAL: f�r die Verschl�sselungsverfahren Caesar, Vigen�re,
                   Nihilist und DES,
     - mit Flash:  f�r AES, Enigma und S/MIME,
     - mit Java/SWT: - Punktaddition auf Elliptischen Kurven
                       (sowohl auf diskreten wie auf reellen Kurven),
                     - Flussvisualisierung von AES,
                     - Control-Center von S/MIME.

- Demo zu Authentisierungsm�glichkeiten im Netz (Visualisierung von
  Challenge-Response-Verfahren):
  * von UID/PW und One-Time-Password
  * �ber (einseitige) Challenge-Response (symmetrisch + asymmetrisch)
  * bis zu asymmetrischer gegenseitiger Authentisierung.
  * Der Benutzer kann interaktiv steuern, wie der Angreifer vorgeht
    (Rechner �bernehmen, Verbindungen aufbauen oder trennen, lauschen).
  * Lerneffekt: Nur die gegenseitige asymmetrische Authentisierung ist
    sicher gegen Man-in-the-Middle-Angriffe.

- Demo f�r einen Seitenkanalangriff gegen ein typisches Hybrid-
  Verschl�sselungsprotokoll: Bei einer sub-optimalen Implementierung,
  wie sie in der Realit�t vorkam, kann der Angreifer den Session-Key
  durch Protokoll-gerechte Anfragen an den Server hoch effizient
  berechnen.

- Hashwerte berechnen und ihre Sensitivit�t demonstrieren.

- Implementierung von HMAC-Verfahren (Kombination von Hashes und
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

- In allen klassischen Algorithmen, wo die Alphabete der zu bearbeitenden
  Texte eine Rolle spielen, wird nun das im zentralen Dialog "Textoptionen"
  eingestellte Alphabet benutzt.
  Damit wurde die Transparenz und Bedienbarkeit verbessert:
  Um sofort bei der Schl�sseleingabe sichtbar zu machen, welche Verfahren
  darauf reagieren, enth�lt jede passende Schl�sseleingabe-Maske einen
  zus�tzlichen Button "Textoptionen", der direkt zum Dialog "Textoptionen"
  f�hrt (man muss also nicht mehr erst an der Stelle, wo man die Textoptionen
  am ehesten braucht, den Schl�sseleingabe-Dialog wieder schlie�en und
  �ber das Hauptmen� zu den Textoptionen gehen).
  Dieser Aufruf mit einem Klick auf den Button "Textoptionen" ist implementiert
  in den Schl�sseleingabe-Masken f�r Caesar, monoalphabetische Substitution,
  Vigen�re, Skytale, Permutation und Homophone.

- CrypTool kann man ohne Administratorrechte ausf�hren.
  Verschiedene Benutzer k�nnen am gleichen PC jeweils verschiedene
  Einstellungen haben. Details siehe Kapitel 3.2 und 4.4.

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
  * Veranschaulichen des Shared-Secret-Verfahrens (entspricht der
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

- Die Release-Sourcen (Tag "CrypTool_1_4_31") und die aktuellen Entwickler-
  Sourcen stehen direkt im Subversion-Repository zur Verf�gung.
  Darauf kann jedermann lesend (ohne Angabe eines Passworts) zugreifen per
  svn checkout http://www.cryptool.com/svn/CrypTool/trunk --username anonymous

- Einen Eindruck von der Gr��e des CT1-Projekts liefert die folgende, im
  Juli 2012 erstellte Statistik (anhand der Dateien f�r die Version
  1.4.31 Beta 05):

    FILE SUMMARY (Anzahl der Dateien anhand ihrer Dateinamenserweiterung)
    ------------
              4 .rc files
             36 .c files
            325 .cpp files
            379 .h files
             36 .java files
             14 .pl files
           1146 .html files
             44 .txt files
             39 .tex files
              4 .sage files
          2.027 TOTAL


    LINES OF CODE (LoC) SUMMARY
    ---------------------------
         60.458 MFC resource code (rc)
        260.412 C/C++ source code (c cpp h)
          9.795 Java source code (java)
          2.257 Perl code (pl)
         65.958 HTML code (html hpp)
          7.889 Text files (txt)
         35.025 LaTeX code (tex)
            825 Sage code (sage)
        442.619 TOTAL

    TOTAL: 442.619 Code-Zeilen (plus von 15,8 % gegen�ber 382.244 bei v1.4.21)
    - In den TOTAL-Wert gehen nur Sourcen ein, die innerhalb des
      CrypTool-Projektes entwickelt wurden oder dem CT-Projekt gewidmet wurden.
      Die Sourcen anderer Open-Source-Projekte, die innerhalb von CrypTool
      benutzt werden (wie OpenSSL, NTL, Scintilla) werden nicht gez�hlt.
      Ebenso wenig werden automatisch erzeugte Dateien oder Wortlisten gez�hlt.

  Snapshot zur Anzahl von Dateien und zur Anzahl der Source-Code-Zeilen


- Details zum Compilieren, Linken und zur einheitlichen Entwicklung
  finden sich in den Sourcen in der Datei "readme-source.txt".

- Die Sourcen wurden mit der Microsoft Entwicklungsumgebung Visual Studio 2008
  Standard Edition (VC++ v9.0) compiliert, um die neueste Microsoft
  Entwicklungsumgebung zu unterst�tzen.
  Die Express-Edition von VS2008 reicht nicht aus, weil CT 1.x noch die
  alte MFC-Klassenbibliothek f�r die GUI nutzt, die die Express-Edition
  im Gegensatz zur Standard-Edition nicht unterst�tzt.
  Der Wechsel von VS2003 auf VS2008 war auch deshalb erforderlich, weil nur
  damit manche Bibliotheken so compiliert werden konnten, dass sie sowohl
  unter Windows Vista als auch Windows XP korrekt liefen.
  Eine Komplett-Compilierung aller 5 Sprachversionen (jeweils Debug und Release)
  dauert auf einem modernen PC rund 2 h.



2.3. Wo finden Sie weitere �berblicke zu CrypTool
     --------------------------------------------
Eine gute �bersicht, was CrypTool bietet, finden Sie auch
- in der Onlinehilfe (siehe "Startseite")
- in der beigelegten PDF-Pr�sentation (Titel: "Kryptologie mit CrypTool"),
- mithilfe des Men�baums im Anhang A.1 des beigelegten CrypTool-Skripts,
- auf der Webseite des CrypTool-Portals unter
          "Dokumentation" -> "CT-Funktionsumfang" und
- auf der Webseite der CT1-Seite unter
          "Dokumentation" -> "Funktionen von CrypTool 1.4.3x" und
          "Screenshots" -> "Screenshots".



2.4. Neuerungen in Version 1.4.20 / 1.4.21
     -------------------------------------
Dieses Kapitel listet die Erweiterungen und Bugfixes auf, die in
CrypTool 1.4.20 und 1.4.21 seit CrypTool 1.4.10 hinzugef�gt wurden.

a) Entwickler-relevante �nderungen (eher Programm-technisch):

- Aufr�umen des Source-Code, h�here Wiederverwendung.

- Update auf OpenSSL 0.9.8g, ANIMAL 2.3.14 and NSIS 2.37.

- Automatisierter Konsistenzcheck in der Onlinehilfe (Verweis auf Men�s,
  Dialoge, Bilder, Querverlinkung).

- Eingabefelder gegen Fuzzy-Eingaben per Clipboard stabilisiert, um
  provozierte Abst�rze zu vermeiden.


b) �nderungen in der Benutzer-Dokumentation / Web-Darstellung:

- Online-Hilfe: erweitert.

- Skript: Behebung kleinerer Fehler, Men�baum in Anhang A.1 der neuen
          CrypTool-Version angepasst.

- Aktualisierte und auf �ber 100 Seiten erweiterte Pr�sentation.

- Neue CrypTool-Webseite mit Joomla seit April 2008.


c) Funktionale �nderungen / Erweiterungen:

- Bugfixes:
  - Viele kleine Verbesserungen in den Masken:
    Benutzerf�hrung; Refresh; Cursor korrekt auch nach Dialogwechsel;
    bei DH, Hill und Seitenkanalangriff einheitlich H�kchen f�r die Anzeige
    von Detaildialogen und die Erstellung von Logfiles.
  - AML-Datei f�r die DES-Animation mit ANIMAL korrigiert (in der Matrix
    K[1] war ein Bit auf 1 statt auf 0). Danke an aufmerksame Benutzer!
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
  variable Alphabet f�r das Transpositions-Passwort nutzen (nicht mehr
  nur die 26 Gro�buchstaben).

- Erweiterung der Brute-Force-Analyse symmetrischer Verfahren (Henk -- danke
  f�r die praktischen und didaktischen Anregungen):
  - Einstellen des Alphabets f�r den erwarteten Klartext, um die Suche
    nach einem m�glichen richtigen Schl�ssel einzuschr�nken.
  - Anbieten der 50 Klartexte mit den niedrigsten Entropie-Werten zur Auswahl.

- Das AES-Tool in der Version 2.5 ist bei gro�en Dateien schneller.
  Die Datei-Endung AES wird bei der Installation diesem Programm zugeordnet.

- Das Lernprogramm/Lernspiel "Zahlenhai" in der Version 1.1.5 wurde etwas
  korrigiert und vor allem wurde die Onlinehilfe erweitert.

- SHA2-Familie (SHA-256, SHA-512) erg�nzt bei der Berechnung der Hashwerte
  des angezeigten Dokuments oder einer Datei.
  http://csrc.nist.gov/publications/fips/fips180-2/fips180-2.pdf

- Verbesserung des Passwort-Qualit�tsmessers, indem neben bekannten
  PQM-Methoden wie denen aus KeyPass oder PGP eine eigene Komponente zur
  Bewertung erg�nzt wurde. Hierbei wurden die aus W�rterbuch-Angriffen
  bekannten realistischen Annahmen �ber das Vorwissen von Angreifern
  ber�cksichtigt:
  - Erkennen von Serien und Mustern (nicht nur die Entropie von einzelnen
    Zeichen unabh�ngig bewerten)
  - Alle Verfahren sind normiert: 100 % bedeutet 128 Bit Entropie.
    Ist 100 % erreicht, werden weitere Eingaben im Passwortfeld ignoriert.
  - Einschr�nkungen in dieser Version:
    - Im Passwortfeld k�nnen keine Leerzeichen eingegeben werden
      (Alle Ascii-Codes <= 32 werden ignoriert).
    - Die neue PQM-Methode wertet nur die ersten 32 Zeichen des eingegebenen
      Passwortes aus.

- Der Passwort-Entropie-Dialog erlaubt es, zuf�llige Passworte zu erzeugen,
  die eine �hnlich hohe Sicherheit bieten wie zuf�llig erzeugte
  Bin�rschl�ssel f�r symmetrische Verfahren bei einer vorgegebenen Bitl�nge.
  Au�erdem kann man das Alphabet des Passwortes vorgeben.



2.5. Neuerungen in Version 1.4.30
     ----------------------------
Dieses Kapitel listet die Erweiterungen und Bugfixes auf, die in
CrypTool 1.4.30 seit CrypTool 1.4.21 hinzugef�gt wurden.

Die Version 1.4.30 wurde zeitgleich in Deutsch, Englisch, Polnisch, Serbisch und
Spanisch released.

a) Entwickler-relevante �nderungen (eher Programm-technisch):

- Aufr�umen des Source-Code, h�here Wiederverwendung,
  Beseitigen vieler Warnungen.
  Z.B. wurde die Hill-Verschl�sselung samt GUI neu geschrieben. Dabei wurden
  rund 6000 Zeilen C++-Code eingespart und dennoch Funktionalit�t und
  Performance verbessert!

- Das Begr��ungsfenster wurde neu erstellt, so dass leichter die Texte
  verschiedener Sprachen dar�ber gelegt werden k�nnen.

- Nun mit VS2008 compiliert.

- Update der Bibliotheken und genutzten Fremdsoftware auf ff. Versionen:
  - Scintilla 1.7.7
  - cv act library v. 1.4.6 (unterst�tzt auch Windows Vista)
  - OpenSSL 0.9.8k
  - MPIR 1.3.1 (hergeleitet aus GMP-Version 4.2.1) statt GMP 4.1
  - APFLOAT 2.41
  - Animal 2.3.21.

- Quellcode und die Applikation CrypTool 1.x stehen nun unter der Lizenz
  Apache 2.0 (siehe http://www.apache.org/licenses/LICENSE-2.0).


b) �nderungen in der Benutzer-Dokumentation / auf den Web-Seiten:

- Online-Hilfe: deutlich erweitert (z.B. sind nun bei allen Blockchiffren
                explizit die benutzten Modi und Padding-Varianten erl�utert).

- CrypTool-Skript: Umfangreiche �berarbeitung:
                  - Erweiterungen und Update auf aktuellen Stand,
                  - Aufnahme von vielen Sage-Programmbeispielen,
                    Auslieferung des Sage-Codes als Datei,
                  - Behebung kleinerer Fehler,
                  - Men�baum in Anhang A.1 an neue CrypTool-Version angepasst,
                  - Neues Deckblatt.

- Aktualisierte und auf �ber 110 Seiten erweiterte Pr�sentation.

- Von der CT-Webseite wird auf die Websites der Nachfolger-Versionen JCT1
  und CT2 verwiesen, die schon die jeweils aktuelle, stabile Beta zum Download
  anbieten.

- Die folgenden zus�tzlichen, ebenfalls zur CrypTool-Familie geh�renden
  Webseiten gingen live:
  - www.cryptool-online.org  "CrypTool-Online" f�hrt verschiedene
                              Kryptoverfahren direkt im Browser aus.
  - www.m.cryptool.org       "CrypTool-Mobil" f�hrt verschiedene
                              Kryptoverfahren in Smartphones aus.
                              Das kann f�rs Geocachen n�tzlich sein.
  - www.cryptoportal.org     "Lehrerportal" mit Unterrichtsmaterial und
                              Links
  - http://www.mysterytwisterc3.org  Ein internationaler Krypto-Wettbewerb
                                     mit Aufgaben verschiedener
                                     Schwierigkeitsgrade.

- Ein kurzes CrypTool-Video auf YouTube:
   - Deutsch:  http://www.youtube.com/watch?v=of0C9Lx0vGs
   - Englisch: http://www.youtube.com/watch?v=bLJKuW4UOuE
   - Spanisch: http://www.youtube.com/watch?v=pTFdklPQiL4

- Auf der CrypTool-Webseite gibt es unter Pr�sentationen nun eine interaktive
  Einf�hrung in die Grundlagen von RSA (als PPT und als Flash):
  http://cryptool.com/index.php/de/documentation-topmenu-75.html


c) Neue Funktionalit�t / Bedienung:

- Bugfixes  --> Danke an die vielen aufmerksamen Benutzer!
   - Fehler in AKS behoben, der mit den Eingaben 2^8+1 und 2^16+1 auftrat.
     Die korrekte Fassung von AKS braucht l�nger.
   - Fehler in AKS behoben, der CT abst�rzen lie�, wenn man die Zeitdauer f�r
     sehr gro�e Zahlen absch�tzen lie� (Dauer �ber 1 Jahr, Stack-�berlauf
     in GMP). Dazu wurde MPIR anstatt einer �lteren Windows-Version der
     GMP-Bibliothek eingesetzt.
   - Fehler behoben bei weiteren Primzahltests, wenn Primfaktoren < 39
     vorkamen.
   - In der Maske "Schl�ssel aus Passwort generieren (nach PKSC #5)" werden
     nun auch die Hashwerte mit f�hrenden Nullen korrekt angezeigt.
   - Die ECC-AES-Hybrid-Ver-/Entschl�sselung l�uft nun dank einer neuen
     cv act lib von cryptovision auch unter Windows Vista.
     Au�erdem kommt hier nun beim Versuch, einen nicht verschl�sselten Text
     zu entschl�sseln, eine korrekte Fehlermeldung.
   - DH-Demo: Wenn man automatisch erzeugte Generatoren danach �nderte (z.B.
     die Ziffer 2 anf�gen) kam es in fr�heren Versionen zum Absturz.
     Ist behoben.
   - Seitenkanalangriff auf das Hybridverschl�sselungsprotokoll (Textbook-RSA):
     Wenn man mit RSA-Modulen arbeitete, die l�nger als 1024 Bit waren, kam es
     zum Absturz, wenn man den Angriffszyklus startete.
     Ist behoben.
   - Die auf dem CRT beruhende Secret-Sharing-Anwendung verbietet nun, dass
     n=k (denn so w�ren alle Shareholder notwendig). Ohne diese Einschr�nkung
     macht der Algorithmus das ganze Geheimnis dem ersten Teilnehmer bekannt.
   - RSA-Demo: Ein eingegebener Wert f�r e wird auch nach Aufruf des
     Optionen-Dialogs beibehalten.
   - Korrektur der ECC-Demo:
     - Die Vorg�ngerversion lieferte �ber der Gruppe F(p) bei der Punktaddition
       unter bestimmten Umst�nden einen Punkt au�erhalb der Kurve.
     - Die Koordinaten der Punkte, die dynamisch in der N�he des Mauszeigers
       erscheinen, sind nun auch am rechten Rand ganz sichtbar.
     - Der Punkt im Unendlichen wird zur Gesamtzahl der Punkte hinzugez�hlt.
     - Das Log-Fenster ist nun amodal, gr��enver�nderlich und der Inhalt
       ist �bersichtlicher gestaltet.
     - Die Slider sind nun breiter, so dass man die Parameter besser justieren
       kann.
     - Die Versionsnummer wurde auf 1.1.1 erh�ht und wird nun im Titel angezeigt.
   - Korrektur bei DESX/DESXL: Nun wird die effektive Bitl�nge in den
     Dialogen zur Verschl�sselung und zur Brute-Force-Analyse angezeigt.
   - Korrektur bei der DESX/DESXL-Brute-Force-Analyse, die Schl�ssel �berging,
     wenn die obersten 128 Bit des Schl�ssels durchsucht wurden (das Parity-
     Bit wird bei der Brute-Force-Analyse aus Performancegr�nden ignoriert;
     dies geht aber nur beim DES-Key-Teil des Gesamtschl�ssels).
   - Beim Angriff auf den Hashwert einer elektronischen Signatur wurde bisher
     die ben�tigte Schrittzahl falsch ausgegeben (immer ca. 4,x*10^18).
   - Absturz gefixt, der auftrat, wenn man in den Textoptionen als Alphabet
     die Gro�buchstaben plus die kleinen Umlaute definierte und dann die
     Caesar-Verschl�sselung aufrief.
   - Nun kann man in Feldern f�r Hexeingaben auch Hexfolgen aus dem Clipboard
     korrekt eingeben (wenn markiert, wird nur da eingef�gt).
   - Der in der Textanzeige eingestellte Font wird beibehalten, auch wenn man
     zwischendurch in die Hex-Ansicht wechselt.
   - Konflikte mit den Zertifikats-Seriennummern: Bisher wurden die
     Seriennummern fortlaufend vergeben und beim Importieren eines Zertifikats
     in den Schl�sselspeicher wurde nicht gepr�ft, ob diese Nummer schon
     vergeben ist. Dies konnte dazu f�hren, dass beim Validieren das falsche
     Zertifikat benutzt wurde.
     Beides ist behoben: Die Nummern werden zuf�llig erzeugt und beim Import
     weiterer Zertifikate werden diejenigen mit Nummern, die schon erzeugt
     wurden, abgelehnt.
   - Die Ciphertext-Only-Analyse von XOR-Chiffraten ermittelte eine falsche
     Schl�ssell�nge, obwohl die angezeigte Autokorrelation korrekt war.
     Nun wird die richtige Schl�ssell�nge angezeigt und benutzt.
   - Korrektur etlicher Rechtschreibfehler in der CrypTool-Onlinehilfe, den
     Ressourcen von CrypTool, AES-Tool und Zahlenhai, und den Animal AML-Dateien.


- CrypTool merkt sich nun die Position und Gr��e des Hauptfensters und nutzt
  dies beim Neustart.

- Benutzerfreundlichkeit: Insbesondere f�r neue Benutzer, die die Onlinehilfe
  nicht aufriefen, aber nach der Bedeutung der Ikone fragten, hat die Ikone
  zum Einf�gen von Schl�sseln aus dem internen Schl�sselspeicher in mehreren
  modalen Dialogboxen nun einen Tool-Tipp ("Schl�ssel einf�gen").

- Viele kleine Verbesserungen in den Masken, z.B. Elapsed-Time-Anzeige beim
  AKS-Test; der Text in der About-Box kann markiert und kopiert werden;
  sofortige Anzeige der Zeit und der Anzahl der bisherigen Faktoren bei
  der Faktorisierung; im Menu zur Analyse von Ciphertext-Only-Verfahren
  steht nun "XOR / Vernam" statt nur "XOR".

- Die Mitwirkenden und die �bersetzenden Organisationen werden nun in
  eigenen Dialogen aufgef�hrt (aufrufbar aus dem neuen About-Dialog).

- Umfangreiche Erweiterungen der Onlinehilfe.

- Auch externe PDFs k�nnen nun direkt aus der Onlinehilfe aufgerufen werden.

- Im Tutorial zu XOR und Psion in der Pr�sentation gab es bisher nur eine
  verschl�sselte Datei (erstellt aus einem deutschen Klartext). Nun gibt es
  auch eine Datei mit einem verschl�sselten englischen Klartext: psion-en-enc.hex


- Bei allen DES-basierten Verfahren wird nun sowohl die effektiv genutzte als
  auch die einzugebende Schl�ssell�nge angezeigt.

- Alle acht verf�gbaren Hashverfahren werden nun angeboten in den Masken f�r:
  - Schl�ssel aus Passwort generieren (nach PKSC #5),
  - Generieren eines Hashed Message Authentication Code (HMAC),
  - Generieren des Hashwertes einer Datei, und in der
  - Hash-Demo.

- Der HMAC-Dialog wurde neu entworfen.

- Im HMAC-Dialog sind die Bezeichnungen der Literatur angepasst und in der
  Onlinehilfe sind nun die entsprechenden Quellen angegeben.
  Variante 5 der HMAC-Beispiel-Konstruktionen entspricht nun genau dem RFC 2104.
  Details:
  In CrypTool sind f�nf HMAC-Varianten implementiert (H = Hash-Funktion,
  k = Schl�ssel, m = Nachricht):
  1.  H ( k, m )
  2.  H ( m, k )
  3.  H ( k, m, k )
  4.  H ( k, m, k' )
  5.  H ( k , H (k, m) )
  Nur Variante 5 ist in einem Standard (RFC 2104, FIPS PUB 198) spezifiziert.
  Dieser HMAC berechnet sich wie folgt: H ( k XOR opad, H(k XOR ipad, m) )
  mit ipad = 64 Bytes je 0x36, opad = 64 Bytes je 0x5C.
  Falls der Schl�ssel k l�nger als die Blockl�nge der Hash-Funktion ist,
  wird k durch H(k) ersetzt.
  Alle diese Funktionen sind mit Hilfe von OpenSSL implementiert.

- Beim PKCS #5-Dialog k�nnen nun bis zu 100.000 Iterationen eingestellt werden.
  Au�erdem werden mehr Hashverfahren unterst�tzt, als der urspr�ngliche
  Standard vorsieht.

- Erweiterung der Brute-Force-Analyse symmetrischer Verfahren:
  Eine weitere Spalte wurde erg�nzt, die den Schl�ssel zeigt, der zu
  den Werten der bisherigen Spalten Entropie des Klartextes, Klartext
  und Geheimtext passt.


- Wenn sich im Dialog Primzahltest ergibt, dass die zu testende Zahl
  NICHT prim ist, kann per Button direkt zum Faktorisierungsdialog
  gesprungen werden.

- Bis 1.4.21 wurden mit der Maske "Primzahlen generieren" zwei zuf�llig
  gew�hlte Primzahl innerhalb eines vordefinierten Bereichs erzeugt.
  Nun kann man damit auch alle Primzahlen innerhalb eines vorgegebenen
  Bereiches ausgeben (Primzahlmenge generieren).

- Bei Diffie-Hellman werden die Primzahlen und der Generator nun
  gem�� Standards f�r sichere Generatoren erzeugt.

- Neu hinzugekommen ist die schnelle Berechnung von Ganzzahl-Potenzen.
  F�r diese Berechnung wird die Bibliothek APFLOAT benutzt. Damit kann man
  alle Stellen der aktuellen Primzahlrekorde (Mersenne-Zahlen) ausgeben.
  In diesem Dialog werden bei der Eingabe von Ganzzahlen die Tausendertrenner
  (Punkte) automatisch gesetzt. Das ist bei evtl. sehr langen Exponenten
  Benutzer-freundlicher.


- Die klassischen Transpositions-Chiffren Skytale und Gartenzaun hinzugef�gt
  (angeboten innerhalb eines Dialogs) incl. Schl�ssel anzeigen und
  Schl�ssel einf�gen per Ikone.

- Solitaire-Verschl�sselung: Maske verbessert, Anzeige von "A" und "B" f�r die
  Jocker statt "53" und "54" (wie im Original), Message nicht mehr auf 64 kB
  beschr�nkt, erzeugte Schl�sselstr�me k�nnen gespeichert werden.
  Die manuelle Solitaire-Analyse (Rekonstruktion des Initialdecks) wurde
  verbessert.

- Die Permutationsverschl�sselung kann nun auch auf Hexdateien angewandt
  werden.

- Die Art, wie aus einem Schl�sselwort eine Permutation erzeugt wird, ist
  nun bei allen Verfahren (Doppelw�rfel, ADFGVX) gleich.

- Die Hill-Verschl�sselung bietet nun weitere Optionen, und alle Schl�ssel-
  parameter (Hill-Optionen) werden mit im Schl�sselspeicher (Registry)
  abgelegt.

- Die Playfair-Verschl�sselung bietet nun weitere Optionen (Vorformatierung;
  Unterscheidung, ob Trenner nur innerhalb von Paaren gleicher Buchstaben
  oder immer beim Aufeinandertreffen gleicher Buchstaben eingef�gt werden).
  Dies wirkt sich z.B. bei Worten wie "BALLOON" aus.

- Alle spezifischen Optionen befinden sich nun in den Dialogen der zugeh�rigen
  Methoden. Somit konnten wir den Men�eintrag "Weitere Optionen" entfernen.

- Die Checkbox "Sonderzeichen" in der Dialogbox "Textoptionen" bietet nun
  standardm��ig mehr Sonderzeichen an. Maximal kann das Alphabet f�r die
  klassischen Verfahren nun 98 Zeichen umfassen.

- Das in den Textoptionen eingestellte Alphabet wirkt sich nun auf fast alle
  klassischen Chiffren aus: Deshalb haben alle angepassten Verfahren nun einen
  Button, um aus der Schl�sseleingabe-Maske direkt zu den Textoptionen zu
  springen.

  Der Textoptionen-Button ist vorhanden bei
  - den klassischen Substitutions-Verfahren
        (Caesar, Vigen�re, monoalphabetische Substitution, Hill) und bei
  - den klassischen Transpositions-Verfahren
        (Skytale, Transpositions-Teil von ADFGVX).

  Der Textoptionen-Button ist absichtlich nicht verf�gbar in den Schl�ssel-
  eingabe-Dialogen der folgenden Verschl�sselungsverfahren:
  - Substitutions-Teil von ADFGVX (der Algorithmus erfordert ein festes Alphabet)
  - Playfair (der Algorithmus legt �ber die Matrix auch das Alphabet fest)
  - Permutation (alle Daten werden permutiert; wenn gew�nscht, kann das Dokument
                 von Ihnen selbst vorab vorformatiert werden -- mit dem Men�
                 "Ansicht \ Textdokument formatieren")
  - Solitaire (der Algorithmus erfordert ein festes Alphabet; alle Buchstaben
               werden in die 26 Gro�buchstaben verwandelt und alle anderen
               Zeichen gel�scht).

  Diese Neuerung kam zustande aufgrund vieler Anfragen, die insbesondere
  um Erweiterung des Alphabets f�r die monoalphabetische Substitution baten.


- Eine Visualisierung der Abl�ufe bei sicherer E-Mail kam hinzu: Der Benutzer
  kann Daten eingeben, die signiert oder verschl�sselt werden mit Hilfe des
  S/MIME-Protokolls.

- Eine weitere Visualisierung des AES-Algorithmus kam hinzu:
  Die Flussvisualisierung veranschaulicht die Ver�nderung der Bits
  in jeder Runde (compiliert mit Java 1.5).


- Das Lernprogramm/Lernspiel "Zahlenhai" (in der Version 1.2.1) wurde
  korrigiert und die Onlinehilfe aktualisiert und erweitert.
  Ausgabe/Anzeige der optionalen Werte:
  - Bisher konnte man die optionalen Werte auf zwei Arten anzeigen:
    - Bis n=158 waren sie abgespeichert.
    - F�r beliebige Werte konnten sie mit einem sehr langsamen
      Brute-Force-Verfahren berechnet werden.
  - Nun k�nnen diese mit einem Backtracking-Verfahren deutlich schneller
    berechnet werden (39 Zahlen in ca. 1 Minute; 40 Zahlen in ca. 5 Minuten).
  - Noch viel schneller sind heuristische Methoden, wie sie in JCT
    implementiert sind. Diese finden meist nicht den optimalen Wert,
    aber einen sehr guten Wert.
    Die besten bekannten Werte bis n=404 werden nun auch im Spiel
    mitgeliefert.
    Alle bekannten Werte k�nnen in einer Tabelle angezeigt werden.
  - Wenn man die optimalen Werte berechnet, was sehr lange dauern kann,
    kann der Zahlenhai nun auf bisher schon berechnete Zwischenergebnisse
    aufsetzen.
  - Weitere Hintergrundbilder wurden hinzugef�gt.

- Das Lernprogramm "Zahlentheorie" wurde etwas korrigiert und liegt nun
  in der Version vom 2009-11-08 bei.


- F�r die einfache Spaltentransposition ist eine Known-Plaintext-Analyse
  zum Finden des Transpositions-Schl�ssels neu hinzugekommen.
  Diese Known-Plaintext-Analyse wurde -- zusammen mit der bisherigen
  Known-Plaintext-Analyse f�r Hill -- besser integriert.
  Alle gefundenen Schl�ssel der Transpositions-Analyse werden in einer
  Tabelle angezeigt.

- Weitere Ciphertext-Only-Analyse f�r Vigen�re (nach Schr�del): Diese
  ist effizient f�r sehr kurze Chiffrate, sofern das Passwort aus einem
  W�rterbuch stammt.



2.6. Neuerungen in Version 1.4.31
     ----------------------------
Dieses Kapitel listet die Erweiterungen und Bugfixes auf, die in
CrypTool 1.4.31 seit CrypTool 1.4.30 hinzugef�gt wurden.

Die Version 1.4.31 wurde zeitgleich in Deutsch und Englisch released.

a) Entwickler-relevante �nderungen (eher Programm-technisch):

- Update der Bibliotheken und der genutzten Fremdsoftware auf ff. Versionen:
  - Scintilla 1.7.7  -->  3.0.2   ????????
  - compilerabh�ngig: cv act library 1.4.6 mit VS2008, 1.4.18 mit VS2010
  - OpenSSL 1.0.1
  - MPIR 1.3.1 (hergeleitet aus GMP-Version 4.2.1) statt GMP 4.1   ??????
      ???????   2.5.1 
  - Miracl 4.4.3  -->  5.5.4
  - NTL 5.5.2

- Das Release von CT 1.4.31 wird nun mit VS2010 kompiliert. Man kann die
  Sourcen weiterhin aber auch mit VS2008 �bersetzen.


b) �nderungen in der Benutzer-Dokumentation / auf den Web-Seiten:

- Online-Hilfe: aktualisiert an einigen Stellen

- CrypTool-Skript: - Einige Korrekturen und Erg�nzungen,
                   - Aufnahme einiger weiterer Sage-Programmbeispiele, xxx
                   - In den Fu�noten nun auch die Men�pfade in CT2 erg�nzt.

- Aktualisierte und auf �ber 110 xxxxxxxxxx Seiten erweiterte Pr�sentation.
  Splitted xxxxxxxxxxxxxx

- Am 18. Januar 2012 wurde die neue CrypTool-Webseite freigegeben, die auf
  Joomla 1.7 beruht und die die 5 Unterprojekte des CT-Projektes gleichwertig
  darstellt.


c) Neue Funktionalit�t / Bedienung / Fehlerkorrekturen:

- Installation und Benutzung ohne Administratorrechte: Nun braucht nicht nur
  das Programm keine Administrator-Rechte mehr, sondern auch das
  Installationsprogramm kann von einem normalen Nutzer ausgef�hrt werden.

- Wenn in der Registry Positions- und Gr��enangaben liegen, die das CT-Fenster
  au�erhalb des Bildschirms positionieren, f�ngt CT das beim Start selbst ab.
  Das Verschwinden der Fenster kam vermehrt unter Win 7 mit CT 1.4.30 vor.
- DES-Animal-Animation: Einige Fehler in den Schritten 357-424 und insbesondere
  in der Pre-Output-Matrix (64 bit) wurden beseitigt.
  Danke an Vasilis. Zus�tzlich wurde die entsprechende Online-Hilfe erweitert.
- Dialog zur Eingabe von Hex-Schl�sseln: Bisher funktionierte das Einf�gen per
  Strg-V korrekt; per Kontextmenu -> Paste aber nicht. Nun tut beides korrekt. 
- Bei SHA256 / SHA512 wurde bisher die falsche Funktion aufgerufen.
  Dies betraf auch den Dialog "Generieren von HMACs".
- Der Aufruf von bc von innerhalb der Zahlentheorie-Tutorials funktioniert
  nun auch unter Win7.

- Textfenster haben nun einen Kontextmenu-Eintrag, um zur Hexanzeige
  umzuschalten, und umgekehrt.
- Transpositions-Verschl�sselung: Der Schl�sseleingabe-Dialog hat nun auch den
  Button "Textoptionen".
- Monoalphabetische Verschl�sselung: Hier gibt es nun im Schl�sseleingabe-
  Dialog einen weiteren Parameter, mit dem man die Startposition (Offset)
  f�r das Passwort festlegen kann. Bisher wurde das Passwort immer an den
  Anfang des Geheimtext-Alphabets gestellt. xxxxxxxxxx
- Die Analyse f�r die Substitutions-Chiffre wird in 2 Varianten angeboten.
  Variante 2 verwendet eine Liste h�ufiger W�rter, die der User bisher nicht
  sehen oder �ndern konnte. Beides ist nun m�glich.
- Die ADFGVX-Analyse nutzt nun zur Bestimmung der Substitutionsmatrix auch
  die H�ufigkeitsverteilung des im Textoptionen-Dialog eingestellten
  Referenztextes.
  Au�erdem kann man entscheiden, ob auch die Ziffern in die H�ufigkeits-
  aufstellung mit aufgenommen werden (Gro�-Kleinschreibung und Sonderzeichen
  sind beim ADFGVX-Verfahren ausgeschlossen). Der Einleitungstext der Analyse
  wurde an das aktuelle Verhalten angepasst.
- AES-Tool 2.6:
  - Fehler behoben, der beim Eingeben von zu langen hexadezimalen Schl�sseln
    auftrat.
  - Erlaubt nun die Schl�sseleingabe als normalen ASCII-String und
    das sichere L�schen der Originaldatei nach dem Verschl�sseln.

- xxxxBugfixes  --> Danke an die vielen aufmerksamen Benutzer!





3. Beschr�nkungen und Voraussetzungen
   ----------------------------------

3.1. Anwendungsbereich dieser Lern-, Trainings- und Awareness-Software
     -----------------------------------------------------------------
CrypTool dient vor allem Ausbildungs- und Awareness-Zwecken. Man soll
es ohne vorherige Konfiguration sofort benutzen k�nnen.

Das Entwicklungsziel von CrypTool war also nicht, dass damit produktiv
verschl�sselt wird oder dass damit eine CA (Certification Authority)
betrieben wird -- auch wenn die Funktionen korrekt in CrypTool
implementiert sind.

Beispielsweise steht -- im Unterschied zu produktiven CA-Applikationen --
das CA-Schl�sselpaar fest in der Software (Source und Binary) und es
ist gesch�tzt mit einer ebenfalls bewusst sehr einfachen PIN f�r die
CA-PSE (Personal Security Environment).

Der Rootschl�ssel der in CrypTool 1.4.31 eingebauten CA hat eine L�nge
von 2048 Bit und ist 20 Jahre g�ltig (06.07.2006 - 06.07.2026).
Zertifikate, die mit dem alten Rootkey aus fr�heren CrypTool-Versionen
(1.3.05 und �lter) ausgestellt wurden, k�nnen nicht in Version 1.4.31
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

Nichtsdestotrotz sind die in CrypTool vorhandenen modernen Krypto-Verfahren
entsprechend den internationalen Standards implementiert und genauso "gut"
wie in kommerziellen Anwendungen.


3.2. Win32-Umgebung, Rechte bei Installation und Betrieb, Java-Runtime
     -----------------------------------------------------------------
CrypTool 1.4.31 ist geschrieben f�r das Betriebssystem Windows 7.
CrypTool erfordert eine Win32-Umgebung. Diese ist auch unter 64-Bit Win-7
vorhanden.

Einige Funktionen wie ANIMAL, ECC-Demo, ... [siehe Kapitel 1.2, Teil (3)]
erfordern zus�tzlich eine Java Runtime-Umgebung JRE (Version >= 1.5).

Die minimale Rechnerausstattung liegt bei 300 MHz CPU, 256 MByte RAM,
100 MByte Festplattenplatz (das sind relativ geringe Anforderungen).

Verschiedene Sprachversionen von CrypTool 1 kann man parallel auf einem
Rechner benutzen, wenn man sie in unterschiedlichen Verzeichnissen installiert.

Verschiedene Benutzer k�nnen am gleichen PC jeweils unterschiedliche
Einstellungen haben (da persistente Einstellungen im Nutzer-spezifischen
Teil der Registry abgelegt werden).

Ausf�hren von CrypTool:
 - CrypTool kann man ohne Administratorrechte ausf�hren.
 - Erl�uterung:
   Bei der Benutzung braucht man Schreibrechte f�r:
    - Dateien im CrypTool-Verzeichnis PSE (f�r das PKI-Schl�sselmanagement),
    - Dateien im Nutzer-spezifischen TEMP-Verzeichnis (zur Ablage tempor�rer
      Dateien),
    - Einstellungen im Benutzer-spezifischen Teil der Registry.

Installation von CrypTool:
 - Auch f�r die Installation braucht man dazu keine Administratorrechte.
 - Erl�uterung:
   Bei der Installation werden persistente Daten an ff. Stellen abgelegt,
   f�r die der Installierende Schreibrechte haben muss:
    - f�r das CrypTool-Verzeichnis,
    - f�r den Benutzer-spezifischen Bereich der Windows-Registry.


Anmerkung 1 -- Details zu den Zugriffsrechten:
a) Programm-Verzeichnis:
   F�r einen erfolgreichen Installationsvorgang muss das vom Benutzer
   gew�hlte Installationsverzeichnis w�hrend der Installation beschreibbar
   sein.
   F�r die zwei Unterverzeichnisse des Installationsverzeichnisses ("pse"
   und "examples") erhalten alle Benutzter der Gruppe "Users" Schreibrechte.

b) Windows-Registry:
   Um die Datei-Endung .aes f�r das Programm AES-Tool zu reservieren, muss
   der folgende Teil der Registry w�hrend der Installation beschreibbar sein:
   HKEY_CLASSES_ROOT
   HKEY_CLASSES_ROOT\Applications

   CrypTool wird in der Liste der installierten Anwendungen (System ->
   Software) nur aufgef�hrt, wenn der folgende Registry-Eintrag beschreibbar
   ist:
   HKEY_LOCAL_MACHINE\Software\Microsoft\Windows\CurrentVersion\Uninstall

c) Startmen�:
   CrypTool wird im Startmen� f�r alle Benutzer eingetragen, wenn das
   folgende Verzeichnis w�hrend der Installation beschreibbar ist:
   %allusersprofile%\Startmen�\Programme
   Wenn dieses Verzeichnis nicht beschreibbar ist, wird CrypTool eingetragen
   unter:
   %userprofile%\Startmen�\Programs.


Anmerkung 2:
Event: Die CrypTool-Anwendung stoppt mit der Meldung "Could not create
       temporary file".

When CrypTool creates a new temporary file the program tries to write the file
at the following locations: 
1. as of the local variable TEMP 
2. if TEMP is not set as of the local variable TMP 
3. if both variables, TEMP and TMP, are not set CrypTool tries to write the file
   on the folder which is actually set.

Bitte pr�fen Sie die Zugriffsrechte f�r die Pfade, auf die die tempor�ren
Variablen zeigen. Falls sowohl %TEMP% und %TMP% nicht gesetzt sind, setzen Sie
diese Umgebungsvariablen auf einen passenden Pfad. Falls sie gesetzt sind,
pr�fen Sie bitte, dass Sie die Rechte haben, dort Dateien und Verzeichnisse
zu schreiben. 


Anmerkung 3:
Wo das TEMP-Verzeichnis von Windows liegt, kann man sehen, wenn man im
Windows-Explorer %TEMP% eingibt. Den Wert kann man unter Windows 7 auch
ansehen und anpassen per "System Information" --> "Software Environment"
--> "Environment Variables". Oder auf der Kommandozeile.



3.3. Interaktive Online-Hilfe unter Windows XP
     -----------------------------------------
Bei CrypTool v1 kann zu jedem selektierten Men�eintrag per F1 Hilfe anfordern.

- F�r Endmen�-Eintr�ge klappte das immer direkt.

- F�r Men�-Eintr�ge, die selbst weitere Untermen�s haben, funktioniert es nur,
  wenn das Untermen� nicht aufgeklappt ist (vor Windows XP war dies
  unabh�ngig davon, ob das Untermen� aufgeklappt war oder nicht).

  Workaround um ein aufgeklapptes Untermen� zu unterdr�cken
  (anhand eines Beispiels):
  Markieren Sie den Men�eintrag "Einzelverfahren \ RSA-Kryptosystem":
  Wenn das Untermen� zu "RSA-Kryptosystem" aufgeklappt ist und Sie die
  Hilfe zum Men�eintrag "RSA-Kryptosystem" selbst haben wollen,
  m�ssen Sie erst das Untermen� von "RSA-Kryptosystem" mit Escape (Esc)
  oder der Links-Pfeiltaste wieder einklappen.


3.4. Unterst�tzung verschiedener Sprachen
     ------------------------------------
Programm, Hilfesystem und Dokumentation sind mehrsprachig aus-
gelegt (zur Zeit komplett englisch und deutsch).

F�r jede unterst�tzte Sprache gibt es bei CrypTool 1.4.31 ein eigenes
Installationsprogramm (Setup).


3.5. Einschr�nkungen / Features / Tipps
     ----------------------------------
- Zur Demonstration des RSA-Kryptosystem und zur Faktorisierung von
  Zahlen greift CrypTool auf die Langzahlarithmetik der Bibliothek
  Miracl zu. Die Bitl�nge der Zahlen wurde in der CrypTool-Anwendung
  auf 8192 beschr�nkt.

- Von Bin�rdateien werden "nur" knapp die ersten 2 GB in den
  Hex-Editor geladen (< 0x7ffff000 = 2.147.479.552 Bytes).

  Textdateien k�nnen dagegen in unbeschr�nkter Gr��e vom Editor geladen
  werden (sofern die Rechnerressourcen reichen).

- Beim Lesen und Speichern von Textdateien wird der Zeilenumbruch immer
  als CR/NL (wie unter Windows �blich) dargestellt. Das bedeutet,
  dass Dokumente, die aus Unix kommen und deshalb den Zeilenumbruch nur
  mit dem Zeichen LF kennzeichnen, l�nger werden [LF wird in CR/NL
  umgewandelt]. Eine Signaturpr�fung kann dadurch schief gehen.

- Textfenster in Dialogen werden mit einem von zwei unterschiedlichen
  Editor-Controls erstellt. Diese haben ein unterschiedliches Verhalten
  beim Dr�cken der Enter-Taste:
  a) Scintilla-Editor: Enter bewirkt das Hinzuf�gen von CR/NL und der
                       Cursor steht in der n�chsten Zeile.
  b) Standard MFC-Editor: Mit Enter wird der Texteditor verlassen und
                          es wird versucht, den OK-Button auszul�sen.

- Darstellung von mathematischen Zeichen in der HTML-Hilfe:
  Die Microsoft HTML-Hilfe ruft den eingestellten Microsoft Internet
  Explorer (IE) auf. Version IE 6 hat manchmal Probleme, mathematische
  Zeichen wie die Gau�-Klammer darzustellen.
  Wenn bei Ihnen der IE7 voreingestellt ist, funktioniert es korrekt.
  Die zugrunde liegenden, in das CHM-File eingebundenen HTML-Dateien
  werden von IE7 und Firefox 1.5 oder h�her korrekt dargestellt.
  Die Gau�-Klammer wird in der Onlinehilfe zum Modulo-Operator als
  Symbol f�r die n�chstniedrigere ganze Zahl verwendet.

- Aus Performancegr�nden wurde festgelegt, dass CrypTool bei der
  N-Gramm-Analyse die L�nge der Dokumente beschr�nkt:
   - f�r Bin�rdateien auf 64 kBytes und
   - f�r Textdateien auf 256 kBytes.
  Werden l�ngere Dateien ge�ffnet, werden sie -- nur bei dieser Art
  der Analyse -- auf die Maximal-L�nge gek�rzt.

- Hashwerte k�nnen von Dateien beliebiger Gr��e berechnet werden,
  sofern die Dateien nicht geladen werden.

- SMIME FlashVideo-Bug
  > Fehlerbeschreibung:
    Flashvideos mit der Endung ".flv" werden nach dem �ffnen einer
    CrypTool-Flash-Animation (z.B. S/MIME oder Rijndael) nicht mehr
    mit dem Standardplayer, sondern mit dem CrypTool-Player f�r
    Flashanimationen ge�ffnet.
  > L�sung:
    Explizites Setzen des zust�ndigen Players. Dazu Rechtsklicken
    auf die Datei und "�ffnen mit ..." ausw�hlen. Jetzt den
    gew�nschten Player markieren und das H�kchen unter der
    Programmliste setzen ("Dateityp immer mit dem ausgew�hlten
    Programm �ffnen"). Danach mit "OK" best�tigen und die Datei
    wird ab jetzt immer mit dem eingestellten Player ge�ffnet.

- AES-Tool:
  - Um Dateien verschl�sselt als selbstextrahierende Archive abzuspeichern,
    d�rfen diese Dateien nicht gr��er als 4 GB sein.
  - Wenn man dagegen nur die reine verschl�sselte AES-Datei ohne Selbstent-
    packungscode erzeugt, kann man auch "beliebig" gro�e Dateien verschl�sseln.

  Bitte beachten Sie, dass die Ausgabe des Standalone AES-Tools nicht
  ganz identisch ist mit der Ausgabe, die Sie in CrypTool mit der
  Men�folge "Ver/Entschl�sseln \ Symmetrisch (modern) \ Rijndael (AES)"
  erhalten (auch nicht, wenn das AES-Tool eine Datei mit der Endung "aes"
  erzeugt). CrypTool selbst verwendet z.Zt. einen festen IV (0), der nicht
  gespeichert wird. AES-Tool nutzt einen zuf�lligen IV und f�gt diesen
  zusammen mit dem Dateinamen hinter den verschl�sselten Daten an.


3.6. Mit �lteren CrypTool-Versionen erzeugte Zertifikate und Schl�ssel
     -----------------------------------------------------------------
Vergleichen Sie Kapitel 4.3, wo das entsprechende Verhalten bei der
Installation beschrieben wird.



4. Installation / Deinstallation / Schl�sselnutzung / Betrieb
   ----------------------------------------------------------

4.1. Installation
     ------------
Sie installieren CrypTool, indem Sie das CrypTool-Setup-Programm auf Ihrem PC
aufrufen. Standardm��ig wird CrypTool dann in das Verzeichnis
            "C:\Programme\CrypTool"
installiert. Das Zielverzeichnis kann in der Installationsroutine
ge�ndert werden. Sie m�ssen Zugriffsrechte f�r das Zielverzeichnis haben.

Wenn Sie es als Administrator in "C:\Programme\CrypTool" installieren,
k�nnen Sie CrypTool danach trotzdem als normaler Benutzer ausf�hren.

Wenn Sie den Zielverzeichnis-Namen "CrypTool" �ndern, z.B. in
"CrypTool-1.4.31-Final-D", so wird auch der Eintrag im Startmen�
der Windows-Taskleiste entsprechend ge�ndert.


4.2. Deinstallation von CrypTool
     ---------------------------
Um CrypTool zu de-installieren, benutzen Sie bitte das "Start"-Menu in
der Windows-Taskleiste.
Dort gehen Sie zu "Alle Programme" \ "CrypTool".
Dann klicken Sie auf "CrypTool deinstallieren".

Manchmal kann es sein, dass die JAR-Dateien nicht gel�scht werden k�nnen,
da Windows und die JRE melden, dass die Datei noch benutzt wird, obwohl
CrypTool samt aller Stand-alone-Programme beendet wurde.
Nach einem Neustart des Rechners kann man dann die JAR-Datei und das ganze
Verzeichnis l�schen.


4.3. Wiederholte Nutzung von Schl�sseln
     ----------------------------------

4.3.1. Schl�ssel aus vorherigen Versionen
       ----------------------------------
Besitzen Sie bereits eine fr�here Version von CrypTool, so versucht das
Installationsprogramm, vor der erneuten Installation das alte CrypTool
zu deinstallieren.
Bitte beachten Sie:
- Wenn bei der Deinstallation nicht alle Verzeichnisse/Dateien im
  Programmverzeichnis (meist "C:\Programme\CrypTool") gel�scht
  werden, l�schen Sie diese manuell.
- Bei der Deinstallation von CrypTool werden alle bisher erzeugten
  asymmetrischen Schl�ssel und Zertifikate gel�scht.

Wenn Sie diese Schl�ssel und Zertifikate auch in der neuen Version von
CrypTool nutzen wollen, gibt es zwei M�glichkeiten:
a) Import aus einer alten CrypTool-Version (VOR 1.4.00):
   - F�r RSA- und DSA-Schl�ssel:
     Exportieren Sie diese PSEs mit Hilfe des alten CrypTools in ein
     PKCS#12-Format und importieren Sie diese Dateien im neuen CrypTool.
   - F�r ECC-Schl�ssel:
     Hier reicht es, die entsprechenden Dateien
     (z.B. [da][db][EC-prime239v1][1131039030][d] )
     vom alten CrypTool\pse-Verzeichnis in das neue Verzeichnis zu
     kopieren.
b) Import aus einer alten CrypTool-Versionen (ab 1.4.00):
   Sichern Sie VOR der Deinstallation das unter dem Programmverzeichnis
   liegende Verzeichnis pse\ mit allen darin gespeicherten Dateien
   in ein anderes Verzeichnis. Alle Dateien darin k�nnen Sie dann nach
   Installation der neuen Version von CrypTool in das neue pse\-Programm-
   verzeichnis kopieren.

F�r den Fall, dass mehrere Benutzer dieselbe CrypTool-Installation
verwenden wollen, m�ssen die Zugriffsrechte auf den Verzeichnissen
pse\ und pse\pseca\ und den darin enthaltenen
Dateien f�r alle Benutzer auf Vollzugriff gesetzt werden.

Der Teilbaum "pse\" sollte nicht manuell bearbeitet werden, da
bei einer inkonsistenten Struktur nur eine Neuinstallation von
CrypTool bleibt, um die Zertifikats-basierten Verfahren zu nutzen.


4.3.2. Schl�ssel gespeichert in den Dateien des PSE-Verzeichnisses
       -----------------------------------------------------------
Die im Men� "PKI" erzeugten Schl�ssel f�r die Verfahren RSA und ECC liegen
im PSE-Verzeichnis (die Schl�ssel der klassischen Verschl�sselungsverfahren
werden nicht dauerhaft abgelegt).
Ab Version 1.4.20 wird als PSE-Verzeichnis ein Nutzer-spezifisches Verzeichnis
verwendet (nicht das eigentliche Installationsverzeichnis), um Rechteprobleme
in Mehrbenutzerumgebungen zu vermeiden.
CrypTool greift so standardm��ig auf asymmetrische Schl�ssel und Zertifikate
im Daten-Anwendungs-Verzeichnis des Nutzers zu. Das hei�t, wenn ein Benutzer
CrypTool das erste Mal aufruft, wird dieses Verzeichnis anhand der Umgebungs-
variablen APPDATA bestimmt, und das CrypTool-Programm-Verzeichnis pse\ wird
mit allen enthaltenen Schl�sseln und Zertifikaten in das Benutzer-Anwendungs-
Verzeichnis kopiert. Die Nutzer-individuellen Schl�ssel und Zertifikate
bieten die Vorteile, dass
- auf das Programmverzeichnis nicht mehr schreibend zugegriffen werden muss,
- die meisten Lese- und Schreibrechtprobleme beim Betrieb in Mehrbenutzer-
  systemen gel�st sind [siehe Abschnitt 4.5.b)], und
- bei einer Neu-Installation die Nutzer-individuellen Schl�ssel nicht mehr
  automatisch �berschrieben werden.

Sie k�nnen das fr�here Verhalten erzwingen, wenn Sie den Registry-Eintrag
HKEY_CURRENT_USER\Software\CrypTool\Settings\UserKeyStore\UseUserKeyStore
auf den Wert �0� setzen (diese Registry-Variable ist nach dem ersten Auf-
ruf von CrypTool sichtbar).



4.4. Installation in Mehrbenutzersystemen
     ------------------------------------
In Mehrbenutzersystemen wie Windows 7 hat der Administrator vollen
Zugriff auf das ganze Dateisystem, die restlichen Benutzer k�nnen/sollten
eingeschr�nkt sein.

Zur Installation braucht der Benutzer Schreibrechte f�r das
Verzeichnis, in das CrypTool installiert werden soll:
- z.B. f�r das Verzeichnis %ProgramFiles% (C:\Programme),
  falls das Unterverzeichnis "CrypTool" noch nicht angelegt ist,
- oder f�r das Verzeichnis %ProgramFiles%\CrypTool (C:\Programme\CrypTool),
  falls dieses schon angelegt ist).
Hat er diese Zugriffs-Rechte nicht, bricht die Installation ab.

Deshalb sollten Sie als normaler Benutzer ohne Administratorrechte als
Zielverzeichnis ein so genanntes "lokales Verzeichnis" angeben (statt
"C:\Programme"). Lokal und f�r den Benutzer zug�nglich k�nnten z.B. sein:
%ALLUSERSPROFILE% (Die Standardeinstellung im deutschen Windows XP ist:
"C:\Dokumente und Einstellungen\All Users").

Wenn Sie CrypTool ohne Administratorrechte installieren und keine
Schreibrechte auf %ALLUSERSPROFILE%\Start Menu haben, werden unter WinXP
im Startmen� ("Start \ Alle Programme") die Eintr�ge zu CrypTool fehlen.
Jeder Nutzer kann diese Eintr�ge aber manuell in sein eigenes Startmen�
aufnehmen.

Anmerkung: Wie bei %TEMP% auch, k�nnen Sie sehen, wo diese Verzeichnisse
liegen, indem Sie im Windows-Explorer %ALLUSERSPROFILE% oder %userprofile%
eingeben.


4.5. Betrieb in Mehrbenutzersystemen
     -------------------------------
a) Alle Benutzer-spezifischen Einstellungen (z.B. Optionen f�r Algorithmen,
   die Sie w�hrend der Benutzung �nderten) werden in der lokalen, Nutzer-
   spezifischen Registry gespeichert (auch die zuletzt ge�ffneten Dateien).

b) Will der Benutzer in Mehrbenutzersystemen wie Windows 7 aus CrypTool
   heraus Dateien anlegen (bzw. �ndern), braucht er Schreibrechte auf das
   entsprechende Zielverzeichnis (bzw. auf die entsprechenden Dateien).
   Geht das nicht, kommt eine Warnung.
   Explizit n�tig sind Schreibrechte nur auf 2 Verzeichnisse:
   - das Standard-Windows-Verzeichnis f�r tempor�re Dateien (TEMP)
     f�r die cry*.*-Dateien,
   - das Unterverzeichnis "CrypTool\pse", da darin die erzeugten
     asymmetrischen Zertifikate und Schl�ssel abgelegt werden.

4.6. Installation auf einem Netzwerk-Laufwerk --> Onlinehilfe-Problem
     ----------------------------------------------------------------
   Besonders in Schulen wird Lern-Software oft nur auf dem zentralen
   Rechner, z.B. auf einem Windows-Netzwerkrechner installiert; die
   Client-PCs rufen dann das Programm von dort auf.

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
   eigentlichen Seiteninhalte nicht mehr anzeigt (dagegen werden die
   Metainformationen wie Inhalt, Index und Suchbegriffe korrekt angezeigt),
   wenn man von einem Client aus auf Hilfedateien auf einem Server zugreift.

   ABHILFE:
   Da das Deinstallieren von Sicherheits-Patches keine gute Idee ist, und
   da es in diesem Szenario auch nicht gew�nscht ist, die CHM-Dateien lokal
   zu installieren, kann man einen bestimmten Eintrag in der Registry
   hinzuf�gen bzw. �ndern:

   Wir nehmen an, dass die CHM-Dateien in "X:\program\CrypTool" liegen,
   wobei "X" ein Netzlaufwerk mit dem UNC-Pfad "\\server\user" ist.
   Somit w�re der vollst�ndige UNC-Pfad zu den CHM-Dateien:
   "\\server\user\program\CrypTool".

   Rufen Sie den Registrierungs-Editor auf (Start > Run... > "regedit") und
   navigieren Sie zu "HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\HTMLHelp\1.x".
   Dort erstellen Sie einen neuen Schl�ssel namens "ItssRestrictions",
   in welchem Sie danach eine neue Zeichenfolge "UrlAllowList" mit dem Wert
   "\\server\user\program\CrypTool;file://\\server\user\program\CrypTool;
   X:\program\CrypTool;file://X:\program\CrypTool" erstellen.

   Indem man in der Registry aller Client-PCs diesen Eintrag aufnimmt,
   haben alle Client-PCs Zugriff auf das Server-Laufwerk.

   ACHTUNG:
   Generell kann das Bearbeiten der Registry dazu f�hren, dass Windows
   nicht mehr funktioniert. Die Verantwortung f�r diese �nderung liegt
   allein bei Ihnen!
   Um auf einem Client-PC die Registry zu �ndern, braucht man
   m�glicherweise Administratorrechte.

   Weitere Infos:
   - http://support.microsoft.com/kb/896054
   - http://www.robo-forum.de/cgi-bin/ultimatebb.cgi?ubb=get_topic;f=20;t=000065



5. Liste der Dateien in der Auslieferung
   -------------------------------------
CrypTool wird als komprimiertes, selbstextrahierendes Archiv in
f�nf (xxxx) verschiedenen Sprachversionen verteilt: Deutsch, Englisch,
Polnisch, Serbisch und Spanisch.

Das selbstextrahierende Archiv in deutscher Sprache
           SetupCrypTool_1_4_31_de.exe
enth�lt folgende Dateien:

ReadMe-de.txt .... Diese Kurzanleitung (deutsch).

md5sum.txt ....... MD5-Hashwerte aller Dateien innerhalb des CrypTool-Paketes.
sha1sum.txt ...... SHA-1-Hashwerte aller dieser Dateien.
authors.txt ...... Informationen zu den Autoren von CrypTool-1.

CrypTool.exe ..... Das E-Learning-Programm.
aestool.exe ...... Das Programm AES-Tool, das Dateien in sich selbst-entpackende
                   Programme verschl�sselt. Zur Entschl�sselung m�ssen
                   Sie das korrekte Passwort eingeben.

CrypTool-de.chm .. HTML-Hilfe-Archiv f�r die CrypTool-Onlinehilfe
                   (in deutsch).
rijndael-poster-a4.pdf ... Darstellung der Abl�ufe beim AES-Algorithmus.

msvcr90.dll ...... N�tig f�r CrypTool.exe.
EC-Param.ini ..... Initialisierungsdatei f�r auf Elliptischen
                   Kurven basierende Public-Key-Verfahren.
TEST-Param.ini ... Initialisierungsdatei f�r die Zufallstests.
secude.dll ....... Bibliothek kryptographischer Funktionen von der
                   Secude IT Security GmbH.
ticket ........... Lizenz f�r die Secude-Bibliothek.
libxml2.dll ...... Wird ben�tigt von der secude.dll.
secidea.dll ...... Wird ben�tigt von der secude.dll f�r die
                   IDEA-Verschl�sselung.
srndmskb.dll ..... Wird von der secude.dll f�r den Entropie-Sammler zur
                   Initialisierung des Secude-Zufallsgenerators ben�tigt.
db.dll ........... Wird ben�tigt von der secude.dll.
secude.xml ....... Wird ben�tigt von der secude.dll.
libeay32.dll...... Bibliothek aus OpenSSL.
SciLexer.dll ..... Bibliothek des Scintilla-Texteditor.
cracklib_Win32.dll .. Unterst�tzt die PQM-Tests.

Rijndael-Animation.exe .. Animation (Flash) des AES-Algorithmus.
Rijndael-Inspector.exe .. Animation (Flash) zu den �nderungen des
                          Datenblocks innerhalb des AES-Algorithmus.
AES_Flussvisualisierung.jar .. Visualisierung der Daten�nderung bei AES.

Enigma_de.exe .... Animation (Flash) der 3-Rotor Enigma-Maschine.
Enigma-Help_de.html .. HTML-Onlinehilfe f�r  "Enigma_de.exe" (deutsch).
enigma_screenshot1.png .. Screenshot f�r die Enigma-Hilfedatei.

eccdemo.jar ...... Demo (Java) zur Punktaddition auf Elliptischen Kurven.

ZT.exe ........... Lernprogramm (Authorware) zur Zahlentheorie.
TextZahlWandler.exe ...... Hilfsprogramm zu "ZT.exe".
ToolBarWrapper.dll .. Notwendig f�r das Authorware-Programm ZT.exe

Zahlenhai.exe .... Das Programm zum Lernspiel "Der Zahlenhai".
NumberShark_de.chm HTML-Hilfe-Archiv f�r die Zahlenhai-Onlinehilfe.
GameData.txt ..... Die ersten High-Scores f�r das Zahlenhai-Spiel.

script-de.pdf .... Ein Skript (deutsch) �ber Kryptographie, Primzahlen,
                   elementare Zahlentheorie und die Mathematik hinter
                   einigen Algorithmen.

CrypToolPresentation-de.pdf .. Folien-Pr�sentation (deutsch)

DialogSchwestern.pdf .. Fantasy-Geschichte von Dr. Elsner, in der
                        eine Variante des RSA-Kryptosystems
                        beschrieben wird.
ChinLab-de.pdf ... Geschichte von Dr. Elsner �ber zahlentheoretische
                   Probleme, die Marco Polo vom Gro�en Khan gestellt
                   werden.

Uninstall.exe .... Teil des NSIS-Installers.
license-de.rtf ... Benutzt vom Installationsprogramm.


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
        \Startbeispiel-de.txt
        \Startingexample-en.txt
        \Startingexample-pl.txt

        \Playfair-enc-de.txt
        \probetext-de.txt
        \psion-de-enc.hex ... Verschl�sselte Datei vom Tutorial in Deutsch
        \psion-en-enc.hex ... Verschl�sselte Datei vom Tutorial in Englisch
        \vernam.txt

        \Original.txt ..... "Harmlose" Beispieldatei f�r die
                            Hashkollision-Demo
        \Faelschung.txt ... "Gef�hrliche" Beispieldatei f�r die
                            Hashkollision-Demo

        \letterFromAliceToBob-DECRYPTED-de.txt .. Beispieldateien f�r die
        \letterFromAliceToBob-ENCRYPTED-de.hex .. Demo des Seitenkanal-
                                  angriffs auf die Hybridverschl�sselung.

        \state2.hex ....... Unverschl�sselte Beispieldaten von ...
        \state2-enc.hex ... Verschl�sselte Beispieldaten von ...
                            "Rijndael-Animation.exe" (per "CrypTool.exe").


cryptochallenges\ ... Dieses Verzeichnis enth�lt Dateien mit Chiffraten.
                      Die meisten sind historischer Natur, einige davon
                      sind ungel�st.
                      Zwei spezielle Herausforderungen sind auch dabei: die
                      Doppelw�rfel-Chiffre (vergleiche www.mysterytwisterc3.org)
                      und die HarryPotter-Chiffre.

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
                   Spanisch, Polnisch und Latein. Diese Dateien werden
                   standardm��ig als Referenz f�r die Analyse von
                   Chiffretexten herangezogen.
                   Diese Dateien sind schreibgesch�tzt.

reference\deutsch.txt  // Auszug aus dem dt. Umsatzsteuergesetz
         \english.txt  // Auszug aus der Agenda 21 [UN-Dokument]
         \genesis-de.txt  // Buch Genesis in den Sprachen
         \genesis-en.txt  // deutsch, englisch, franz�sisch,
         \genesis-es.txt  // spanisch, polnisch und lateinisch.
         \genesis-fr.txt  // Die 2-Buchstabencodes (de, ...) entsprechen
         \genesis-pl.txt  // den ISO 639 Language Codes.
         \genesis-la.txt  // xxx


words\ ........... In diesem Verzeichnis liegen die Dateien, mit denen
                   Tests und Analysen durchgef�hrt werden.

words\cracklib-words        // F�r Tests auf Passwortmuster
      cracklib_dict.hwm     // 
      cracklib_dict.pwd     // 
      cracklib_dict.pwi     // 
      VigenereAnalysisSchroedelDictionary.txt   // F�r die Vigen�re-Analyse
      VigenereAnalysisSchroedelDigrams.txt      // (nach Schr�del)
      VigenereAnalysisSchroedelTrigrams.txt     // Sprachabh�ngig
      substitution-de.txt   // F�r Variante 2 der mono-alphabetischen
      substitution-de.txt   // Substitutionsanalyse


sage\ ........... Dieses Verzeichnis enth�lt die Beispiel-Berechnungen
                  aus dem CT-Skript script-de.pdf, die mit dem Computer-
                  Algebra-System SAGE ausgef�hrt wurden.

sage\SAGE-Samples-in-Chap01.sage
     SAGE-Samples-in-Chap02.sage
     SAGE-Samples-in-Chap03.sage
     SAGE-Samples-in-Chap04.sage


pse\ ............. In diesem Verzeichnis und in seinem
                   Unterverzeichnis pseca\ werden erzeugte
                   (asymmetrische) Schl�ssel und Zertifikate abgelegt.

pse\[SideChannelAttack][Bob][RSA-512][1152179494][PIN=1234].pse
    [HybridEncryption][Bob][EC-prime239v1][1178702474][PIN=1234]
    [HybridEncryption][Bob][EC-prime239v1][1178702474][PIN=1234].pse

pse\pseca\calog        Diese Dateien sind f�r die Verwaltung der
         \capse.cse    Schl�sseldatenbank notwendig.
         \CA_exts
         \cert.dir
         \cert.pag
         \crls.dir
         \crls.pag
         \CRL_exts
         \user.dir
         \user.pag


animal\ .......... Dieses Verzeichnis enth�lt die Dateien, die f�r
                   das Animationsprogramm ANIMAL n�tig sind.

animal\Animal-2.3.21.jar
      \animal.bat
      \animal.properties
      \AnimalResources
      \AnimalResources.de
      \AnimalResources.de_DE
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
            \des_de.aml
            \nihilist_de.aml
            \vigenere_de.aml


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

Bc\manifest\bc-1.06-bin.mft
           \bc-1.06-bin.ver


xtras\ ............ Geh�rt zu Authorware, mit dem "ZT.exe" erstellt wurde.

xtras\BMPVIEW.X32
     \MIX32.X32
     \VIEWSVC.X32



smimedemo\ ............ Geh�rt zur Flash/Java-Animation einer
                        S/MIME-E-Mail.

smimedemo\anim.swf
         \lock2.gif
         \smime.ini
         \SMIME_Animation.exe   [erzeugt tempor�r params.xml]
         \start-de.bat
         \swt-awt-win32-3235.dll
         \swt-gdip-win32-3235.dll
         \swt-wgl-win32-3235.dll
         \swt-win32-3235.dll

smimedemo\font\Mathematica7.ttf
              \Mathematica7b.ttf
              \Mathematica7m.ttf
              \Mathematica7mb.ttf

smimedemo\images\encrypt.png
                \sign.png

smimedemo\krypto\CertInfoDialog.class
                \KeyStoreUtils.class
                \KryptoService.class

smimedemo\lib\bcmail-jdk16-141.jar
             \bcprov-jdk16-141.jar
             \commons-codec-1.3.jar
             \mail.jar
             \swt.jar

smimedemo\mail\Mail.class
              \MailService.class
              \SignedDataProcessor.class
              \SignedMultiPart.class

smimedemo\main\Config.class
              \Programm.class
              \Resetable.class

smimedemo\texte\ITexte.class
               \TranslationText.class

smimedemo\userinterface\AliasDialog$1.class
                       \AliasDialog.class
                       \GUI$1.class
                       \GUI$10.class
                       \GUI$11.class
                       \GUI$12.class
                       \GUI$13.class
                       \GUI$14.class
                       \GUI$15.class
                       \GUI$2.class
                       \GUI$3.class
                       \GUI$4.class
                       \GUI$5.class
                       \GUI$6.class
                       \GUI$7.class
                       \GUI$8.class
                       \GUI$9.class
                       \GUI.class
                       \MyInputDialogData.class
                       \PasswordDialog$1.class
                       \PasswordDialog.class

smimedemo\utils\Tools.class
               \Utils$FixedRand.class
               \Utils.class
               \Version.class



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




5.1. �berpr�fen der Integrit�t der heruntergeladenen Dateien
     -------------------------------------------------------
Die Integrit�t von Dateien kann mit Hashwerten �berpr�ft werden.
Hashwerte sind wie Fingerabdr�cke -- mit einer sehr geringen
Informationsmenge kann man ein viel gr��eres Objekt identifizieren.

Die Dateien vom CrypTool-Projekt kommen normalerweise dadurch auf
Ihren Computer, dass das Archiv (Setup-Datei) heruntergeladen und
die darin enthaltenen Dateien entpackt werden:
a) Herunterladbare Dateien:
   Auf der Homepage von CrypTool www.cryptool.org finden Sie
   die Hashwerte aller von der deutschen Webseite direkt
   herunterladbaren Dateien in den dortigen Dateien md5sum.txt bzw.
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
   die als Teil des Paketes mit entpackt werden.

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



6. Kurze Historie der freigegebenen Hauptversionen von CT1
   -------------------------------------------------------

Release-  Datum         Gr��e des Windows-Setups  Plattenplatz  Freigabe
Version                  Deutsch    Englisch      Bedarf DE      durch
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
1.4.30    Aug. 2010      52,1 MB     51,5 MB         95 MB        DB
1.4.31    Sep. 2012      52.4 MB     51.8 MB        100 MB        DBxxxxxxxxxx

Bemerkungen zu den Versionen:
1.3.02   Viele neue Funktionen gegen�ber 1.3.00.
1.3.03   Viele kleine Bugfixes und Verbesserungen der Dokumentation.
1.3.04   Etliche neue Funktionalit�t, einige kleine Bugfixes, und Verbes-
         serung und Erweiterung der Dokumentation (Online-Hilfe, Skript).
1.3.05   Kleine Bugfixes.
1.4.00-Beta10  Dez. 2005  Erste �ffentliche Beta von Version 1.4.00.
1.4.00-Beta12  M�rz 2006  Zweite �ffentliche Beta von Version 1.4.00.
1.4.00-Beta14  Juli 2006  Dritte �ffentliche Beta von Version 1.4.00.
1.4.00   Viele neue Funktionen gegen�ber 1.3.05.
1.4.10-Beta04  Mai  2007  Erste �ffentliche Beta von Version 1.4.10.
1.4.10-Beta06  Juli 2007  Zweite �ffentliche Beta von Version 1.4.10.
1.4.10   Funktionsumfang und Onlinehilfe stark erweitert i.Vgl. zu 1.4.00.
1.4.20-Beta03  Mai  2008  Erste �ffentliche Beta von Version 1.4.20.
1.4.20   Funktionsumfang und Onlinehilfe erweitert i.Vgl. zu 1.4.10;
         Vor allem Feinschliff und Code stabilisiert (Qualit�tsrelease).
1.4.21   Patch, das auch die MSVCR71.dll enth�lt, da diese Datei von der
         neuen aktuellen OpenSSL-Bibliothek benutzt wird und nicht auf
         frischen Windows-Umgebungen (ohne Office) enthalten ist.
1.4.30-Beta03  M�rz 2009  Erste �ffentliche Beta von Version 1.4.30.
1.4.30-Beta04  Sep. 2009  Zweite �ffentliche Beta von Version 1.4.30.
1.4.30-Beta05  Jan. 2010  Dritte �ffentliche Beta von Version 1.4.30 (22.01.2010).
1.4.30-Beta06  Feb. 2010  Vierte �ffentliche Beta von Version 1.4.30 (28.02.2010).
1.4.30-Beta07  Juni 2010  F�nfte �ffentliche Beta von Version 1.4.30 (09.06.2010).
1.4.30-Beta08  Juli 2010  Sechste �ffentliche Beta von Version 1.4.30 (09.07.2010).
1.4.30   Viele Bugfixes und erweiterter Funktionsumfang i.Vgl. zu v1.4.21.
         Plattenplatz-Bedarf der verschiedenen Sprachversionen von 1.4.30:
         EN:  93.7 MB
         DE:  94.7 MB
         PL: 100.0 MB
         RS:  93.7 MB  xxxxxxxxx
         SP:  94.4 MB
1.4.31-Beta04  Juli 2012  Erste �ffentliche Beta von Version 1.4.31.
1.4.31   Viele Bugfixes und ein wenig erweiterter Funktionsumfang i.Vgl. zu v1.4.30.



7. Feedback und Kontaktadressen
   ----------------------------
Sollten Sie Probleme haben oder Fehler finden, wenden Sie sich
bitte mit einer ausf�hrlichen Beschreibung des Problems (und einigen
Bildschirmbildern dazu) per E-Mail an eine der hier genannten Personen.

F�r Anregungen jeglicher Art bez�glich CrypTool sind wir immer
dankbar und helfen Ihnen gern, wenn es unsere Zeit erlaubt.

Auch w�rden wir uns freuen, wenn Sie uns mitteilen, wie und wo Sie
CrypTool einsetzen.

Kontaktadressen:
- esslinger@fb5.uni-siegen.de
- esslinger@cryptool.org
- joerg-cornelius.schneider@db.com
- henrik.koy@db.com



8. Verweise / Auszeichnungen
   -------------------------

Vergleiche: http://www.cryptool.org/de/ctp-links-de


8.1. Artikel �ber CrypTool
     ---------------------
8.1.1. c't 14/2001
       -----------
In diesem renommierten und auflagenstarken deutsch-sprachigen
Computermagazin wurde im Juli 2001 ein 5-seitiger Artikel zu
CrypTool ver�ffentlicht (S. 204-208).

8.1.2. DuD Oktober 2002
       ----------------
In der deutsch-sprachigen Fachzeitschrift "DuD Datenschutz und
Datensicherheit", Ausgabe 10/2002 erschien unter dem Titel
"CrypTool - spielerischer Einstieg in klassische und moderne
Kryptographie. Neue Version - fundierte Awareness in Deutsch
und Englisch" ein 4-seitiger Artikel �ber CrypTool.

8.1.3. KES 2/2003 (Mai 2003)
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

8.1.4. Tagungsband 8. Deutscher IT-Sicherheitskongress des BSI (Mai 2003)
       ------------------------------------------------------------------
Auf dem BSI-Kongress 2003 in Bonn wurde von Hr. Koy der Vortrag
"Awareness in der Informationsgesellschaft: CrypTool - Kryptographie
spielerisch verstehen" gehalten. Die Textfassung dazu steht im
Tagungsband, "IT-Sicherheit im verteilten Chaos", auf S. 485 - 500.

8.1.5. Datenschutz PRAXIS (Juni 2005)
       ------------------------------
In der deutsch-sprachigen Fachzeitschrift "Datenschutz PRAXIS",
Ausgabe Juni 2005 erschien unter dem Titel "Spielend verschl�sseln lernen
mit dem kostenlosen CrypTool" ein 2-seitiger Artikel �ber CrypTool von
Dr. Rainer W. Gerling.
Diesen Artikel finden Sie im Internet unter
http://www.lrz-muenchen.de/~rgerling/pdf/DatenschutzPRAXIS_2005_06_9.pdf.

8.1.6. Report Touch Briefing Information Security (Oktober 2006)
       ---------------------------------------------------------
Der "Touch Briefing Information Security"-Report 2006 enth�lt den Artikel
"The CrypTool Project -- Improving Awareness and Education for Cryptology".
Abrufbar im Internet unter:
  http://www.touchbriefings.com/pdf/2259/esslinger.pdf
Mit den Suchbegriffen "awareness cryptology" listeten danach sowohl
google.de wie google.com diesen Artikel auf Platz 1.

8.1.7. DFN-Mitteilungen, Heft 73 (Dezember 2007)
       ---------------------------------------------------------
Diese Mitteilungen des Deutschen Forschungsnetzes (DFN) enthalten den
4-seitigen Artikel "CrypTool -- Ein E-Learning-Programm f�r Kryptologie".

8.1.8. KES 3/2008 (Juli 2008)
       ----------------------
In der deutsch-sprachigen Fachzeitschrift "KES - Zeitschrift f�r
Informations-Sicherheit", Ausgabe 3/2008 erschien unter dem Titel
"(Ver)Schl�sselerlebnisse NG" ein 3 1/3-seitiger Artikel zum
10-j�hrigen Jubil�um von CrypTool und zu den neuen Versionen.

8.1.9. Telepolis 8/2008 (August 2008)
       ------------------------------
Ein Artikel von Klaus Schmeh �ber CrypTool erschien unter dem Titel
"Werkzeugkasten f�r Codeknacker" in dem Online-Magazin Telepolis.
http://www.heise.de/tp/r4/artikel/28/28389/1.html

8.1.10. Eclipse Magazin 4/2008 (Oktober 2008)
        --------------------------------------
Ein Artikel von Dominik Schadow �ber JCrypTool erschien unter dem Titel
"JCrypTool: Kryptisch gesagt..." im "Eclipse Magazin".
Dieser Artikel kann als Reprint herunter geladen werden von:
http://www.trivadis.com/fileadmin/user_upload/PDFs/Trivadis_in_der_Presse/EclipseMagazin_Kryptisch_gesagt_Schadow.pdf

8.1.11. ep-Elektropraktiker Januar 2009
        -------------------------------
In der deutsch-sprachigen Fachzeitschrift "ep-Elektropraktiker", Ausgabe 01/2009 erschien unter dem Titel "CrypTool - sichere Kommunikation" ein 2-seitiger
Artikel �ber CrypTool von H. M�bus.
http://www.elektropraktiker.de/download/luk-2009-1-06-46867.html

8.1.12. DuD M�rz 2009
        -------------
In der deutsch-sprachigen Fachzeitschrift "DuD Datenschutz und
Datensicherheit", Ausgabe 03/2009 erschien unter dem Titel
"CrypTool - Ein Open-Source-Projekt in der Praxis. Erfahrungsbericht
eines erfolgreichen Open-Source-Projektes" ein 6-seitiger Artikel �ber
CrypTool.


Weitere Artikel sind auf der oben genannten Webseite aufgelistet.



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
mit CrypTool die Aufgabe mit wenigen Mausklicks l�sen.
Im April 2012 waren Artikel vor 2002 nicht mehr abrufbar.
Unter http://www.wiwo.de/unternehmen/kryptographie-spezial/4754982.html
findet sich eine kurze Zusammenfassung des Artikels.

8.2.2. BSI B�rger-CD "Ins Internet - mit Sicherheit"
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

8.2.3. BSI-Software-Suite BOSS 2.0 (Jan. 2007)
       ---------------------------------------------
Das Bundesamt f�r Sicherheit in der Informationstechnik (BSI) hat
CrypTool 1.4.00 als Teil der BSI-Software-Suite "BSI OSS Security
Suite 2.0 (BOSS)" mit ausgeliefert.
Die BOSS-Live-CD wurde inzwischen durch OpenVAS ersetzt. OpenVAS ist ein
Server-basiertes Sicherheitswerkzeug. Gesteuert wird �ber eine
Client-Komponenten (Greenbone Security Desktop (GSD)), die f�r Linux und
Windows verf�gbar ist. Diese ist genauso wie alle anderen Komponenten von
OpenVAS als Freie Software verf�gbar.


8.2.4. In Fortbildungen / Kursen (Beispiele)
       -------------------------------------
- CISSP, TISP (TeleTrusT Information Security Professional), ...

- https://www.tisp.de/
  http://www.logicalsecurity.com/education
  http://www.careeracademy.com
  https://www.cccure.com

- http://www.cdachyd.in/cnss/cnss_ebrochure.htm   (Dez. 2008)
  Ein 20-w�chiger Kurs �ber Netzwerk- und Systemsicherheit (CNSS), angeboten
  von C-DAC Hyderabad, Indien, wo auch CrypTool zum Einsatz kommt.
  Das Centre for Development of Advanced Computing (C-DAC) ist eine
  regierungsnahe Forschungs- und Entwicklungseinrichtung im EDV-Bereich.



8.2.5. Nennungen auf verschiedenen Webseiten
       -------------------------------------

a) Simon Singh hat auf seiner Webseite http://www.simonsingh.net/
   beim Schreiben seines Buches "Geheime Botschaften" (engl. "The
   Code Book") viel Material zur Kryptographie, ihrer Geschichte und
   ihrer Vermittlung zusammengetragen.

   In seinem Newsletter #13 vom 11.2.2004 nennt er CrypTool als eines von vier
   weltweit empfohlenen Seiten ("4. Crypto tutorials"):
   - www.simonsingh.net/The_Black_Chamber/home.html
   - www.cryptoclub.math.uic.edu/indexmain.html
   - www.antilles.k12.vi.us/math/cryptotut/home.htm
   - www.cryptool.com
   Vgl.: http://simonsingh.net/2004/02/royal-institution-and-more-mind-games/


b) Auf der Professional Security Testers Warehouse (PST) postete
   Jaganmohan Kataru, CISSP, MCSE in das Security News Dashboard am
   21.09.2005 unter der �berschrift "eLearning Program for Cryptology":
   http://www.professionalsecuritytesters.org/modules.php?name=Forums&
   file=viewtopic&t=34

   Ein �hnliches Post gab es am 22.09.2005 auf der "CISSP, SSCP, CISM,
   CISA, ISSPCS, and SANS GIAC GCFW Open Study Guides Web site" for
   Cryptography: http://www.cccure.org/modules.php?name=News&new_topic=51
   mit dem Titel "CrypTool A great tool to learn more about cryptography".


c) Wikipedia:
   - Deutsch:
     - http://de.wikipedia.org/wiki/CrypTool
     - http://de.wikipedia.org/wiki/Kryptographie
     - http://de.wikipedia.org/wiki/Wikipedia:WikiProjekt_Kryptologie
   - Englisch:
     - http://en.wikipedia.org/wiki/CrypTool
     - http://en.wikipedia.org/wiki/Cryptography
     - http://en.wikipedia.org/wiki/Topics_in_Cryptography
   - Polnisch:
     - http://pl.wikipedia.org/wiki/CrypTool
     - http://pl.wikipedia.org/wiki/Kryptografia
   - Spanisch:
     - http://es.wikipedia.org/wiki/CrypTool
   - Serbisch:
     - http://sr.wikipedia.org/sr/CrypTool
   - Franz�sisch:
     - http://fr.wikipedia.org/wiki/CrypTool
   - Thail�ndisch:
     - http://th.wikipedia.org/wiki/CrypTool
   - Italienisch:
     - http://it.wikipedia.org/wiki/CrypTool
   - Griechisch:
     - http://el.wikipedia.org/wiki/CrypTool
   - Russisch: xxxxxxxxxxxxxx


d) Eine kleine Auswahl weiterer Seiten:
   https://www.a-i3.org/content/view/415/28/
   http://www.fh-lueneburg.de/mathe-lehramt/krypto/krypto.htm
   http://www.kryptographiespielplatz.de/
   http://www.tinohempel.de/info/info/kryptografie/index.htm
   http://www.edoeb.admin.ch/themen/00794/00928/00930/00953/index.html?lang=de
       (siehe Link unter "Freeware-Programm, mit dem Sie kryptographische
                          Verfahren anwenden k�nnen")
   http://www.roehri.ch/~sr/links/crypto.html
   http://williamstallings.com/Crypto/Crypto4e.html
        (Ressource-Seite zu dem Buch "Cryptography and Network Security",
         4. Auflage von William Stallings)
   http://williamstallings.com/Cryptography/Crypto5e-Student/
   ...



8.3. Weitere Freeware-Projekte (Crank, CAP, CryptoStudio, SAGE, etc.)
     ----------------------------------------------------------------

a) Vollst�ndig mit Source-Code verf�gbar sind:

- http://freshmeat.net/projects/crank/
  http://freecode.com/projects/crank
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
  http://freecode.com/projects/griffon
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
  Kryptos ist Open-Source-Projekt, das an der George Mason University begann.
  Kryptos ist eine Kryptographie-Lernsoftware mit einer statischen
  Oberfl�che, aber vielen modernen Algorithmen, die dynamisch aus
  verschiedenen Bibliotheken kommen k�nnen.
  Kryptos hat keine Kryptoanalyse-Funktionen.
  Die aktuelle Version Kryptos 3.01 stammt vom Dezember 2006,
  sie erfordert .NET Framework 2.0.

- http://cryptostudio.sourceforge.net/
  CryptoStudio von Prof. Marco Russo
  Die aktuelle Version 1.0 stammt vom Juni 2005. Sie ist in Englisch
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
  und ohne Analysefunktionalit�t, geschrieben in Python.
  Die drei klassischen Verschl�sselungsverfahren k�nnen sowohl von der GUI,
  von der Kommandozeile wie als Netzwerk-Proxy ausgef�hrt werden.
  Die aktuelle Version 1.0 stammt vom Juni 2003 von Shannon -jj Behrens
  ver�ffentlicht.

- http://www.nku.edu/~cryptography/doku.php?id=downloads:downloads
  (von http://www.nku.edu/~christensen)
  Das darin enthaltene Java-Programm CryptoHelper.JAR vom "Math and Computer
  Science Club" an der NKU ist ziemlich komplett, was klassische Chiffren angeht.
  Letzter Update: Gary Watson, Aug 2005.

- http://www.cs.unc.edu/~stotts/145/homes/crypt/
  Cypher, geschrieben in C und FLTK (f�r Windows und Unix), ist ein
  Toolkit, um die Entschl�sselung klassischer Chiffren zu unterst�tzen
  mittels statistischer Daten und Verfahren.
  Es wurde in einem Universit�ts-Projekt von 6 (?) Studenten im Jahre
  2000 entwickelt. Die Webseite enth�lt die Sourcen, aber nicht die
  ausf�hrbaren Dateien.

- Im Open-Source Computer-Algebra-System "SAGE" sind ebenfalls einige
  Algorithmen aus dem Gebiet der Kryptographie implementiert.
  Version 4.8. enth�lt z.B.:
    Ciphers
    Classical Ciphers
    Simplified DES
    Mini-AES
    Blum-Goldwasser Probabilistic Encryption
    Stream Ciphers
    Linear feedback shift register (LFSR) sequence commands
    Boolean functions
    Small Scale Variants of the AES (SR) Polynomial System Generator
    Multivariate Polynomial Systems
    S-Boxes and Their Algebraic Representations
    Hard Lattice Generator
  http://www.sagemath.org/doc/reference/index.html
  SAGE wird auch f�r einige Beispiele im CrypTool-Skript verwendet.


b) Die einzigen weiteren uns bekannten brauchbaren Programme, die
   Kryptographie und Kryptoanalyse (unter einer graphischen Oberfl�che)
   verbinden, sind solche, f�r die der Source-Code nicht freigegeben wurde:

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
  verfahren; war verf�gbar ab Dezember 2002 unter
  http://phoenix.goucher.edu/~jtrafton/Crypto; Link ist tot).

- Die Java-Anwendung CipherClerk von Wilhelm M. Plotz
  (Ver- und Entschl�sselung mit vielen klassischen Verfahren;
  letzter Update 2003)
  http://members.aon.at/cipherclerk/

- CryptoBench - GUI um Teile von Wei Dai's Crypto++ Bibliothek
  Kompakte und �bersichtliche GUI zur Nutzung der Kryptofunktionen aus
  Wei Dai's Crypto++ Bibliothek (keine Kryptoanalyse).
  Die aktuelle Version 1.0.1 der CryptoBench gibt es seit 2004.
  Wei Dai's Crypto++ Bibliothek ist Open Source, die GUI der
  CryptoBench ist Freeware aber kein Open Source.
  http://www.addario.org/cryptobench/

- "Cryptanalysis Tools" von Steven Kohns
  Das Programm, das f�r den Kryptographie-Kurs an der NKU (Northern Kentucky
  University) in 2004 entstand, hilft beim Erzeugen und Brechen einfacher
  Chiffren.
  Zur Ausf�hrung unter Windows XP muss man den "Windows 2000 compatibility
  mode" aktivieren.
  Letzter Update: Mai 02, 2004 - Uploaded Cryptanalysis Project
                  Nov 27, 2004 - Version 0.17 (laut Splash Screen)
                               - Version 0.37 (laut help file)
  http://studenthome.nku.edu/~kohuss/content/crypt.html

- "Cryptography Tools" von Don Spickler
  Das Java-Programm entstand an der Henson School of Science & Technology,
  Salisbury University "to help users understand the workings of and the
  cryptanalysis of several classical ciphers".
  Es gibt ausf�hrbare Dateien (keine Sourcen) f�r Windows, Linux und Mac.
  Letzter Update: Sep 24, 2009 - Version 1.2.1
  http://facultyfp.salisbury.edu/despickler/personal/CryptTools.asp


Falls uns hier etwas entgangen ist, w�rden wir uns �ber eine Nachricht
freuen - wir vervollst�ndigen oder korrigieren diese Liste gerne.

Au�erdem wollen wir hier ausdr�cklich das Angebot machen, die
Anstrengungen f�r diese einzelnen Programme in ein einziges
Programm zu integrieren. Wir freuen uns �ber jede Kooperation!!



8.4. Auszeichnungen
     --------------
Generell ist es f�r uns die gr��te Auszeichnung, wenn CrypTool breit
eingesetzt wird, und dabei in Schule, Lehre und Training einen guten
Nutzen stiftet. �ber die vielen bisher erhaltenen positiven R�ckmeldungen
freuten wir uns sehr. Wir versuchen, auch in Zukunft auf alle Ihre W�nsche
schnell zu reagieren.

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
  Wissensvermittlung Kryptographie) ging an das CrypTool-Projekt.

- Ausgew�hlter Ort 2008 im Land-der-Ideen
  Das CrypTool-Projekt wurde bei dem bundesweiten Wettbewerb "365 Orte im
  Land der Ideen" in der Kategorie Wissenschaft und Technik ausgew�hlt.
  Dazu fand am 22.07.08 an der Universit�t Siegen ein Tag-der-offenen-T�r
  statt.

Vergleiche auch http://www.cryptool.org/de/ctp-lehre/ctp-auszeichnungen-de




A. Anhang
   ------

A.1. .... Roadmap nach CT 1.4.31
A.2. .... Nachfolger-Projekte mit Java/Eclipse und C#/.NET
A.2.1. .... Design der Nachfolger-Projekte CT2 und JCT1
A.2.2. .... Funktionen der Nachfolger-Projekte CT2 und JCT1
A.3. .... M�gliche Punkte f�r eine Weiterentwicklung -- Neue Funktionen, Ideen
A.3.1. .... Funktionalit�t: Algorithmen / Verfahren
A.3.2. .... Funktionalit�t: Analyse
A.3.3. .... Interne Schnittstellen / Editoren
A.3.4. .... User-Interface / Visualisierungen
A.4. .... CrypTool v1 unter Linux
A.4.1. .... Ausf�hren von CrypTool v1 unter Linux mit Wine
A.4.2. .... Portierungsversuch von CrypTool v1 nach Linux mit Qt



A.1. Roadmap nach CT 1.4.31
     ----------------------
Generell flie�en alle gr��eren Neu-Entwicklungen aus dem CT-Projekt nun in
die beiden Nachfolger-Projekte CT2 und JCT1 (siehe A.2).

In CrypTool 1.x werden weiterhin Fehler behoben. Funktionen k�nnen erweitert
oder hinzugef�gt werden von Mitwirkenden, die weiter in C/C++ implementieren
wollen.

Alle in CT1, CT2, JCT und CT-Online verf�gbaren Funktionen k�nnen in einer
interaktiven Liste abgerufen werden auf:
   http://www.cryptool.org/de/ctp-dokumentation-de/ctp-functions-de



A.2. Nachfolger-Projekte mit Java/Eclipse und C#/.NET
     ------------------------------------------------
Die Nachfolger von CrypTool 1.x nutzen State-of-the-Art-Entwicklungsumgebungen,
aktuelle Layout-Techniken und moderne Software-Architekturen.

A.2.1. Design der Nachfolger-Projekte CT2 und JCT1
       -------------------------------------------
a) Generelle Wunschliste anhand des Benutzerfeedbacks
   Dies gilt f�r beide Nachfolger-Versionen Java-CrypTool und CrypTool 2:
   - Moderne Pure-Plugin-Architektur
   - Moderneres Layout, weniger Dialogboxen-Wechsel
   - Standardkonformit�t in der Bedienung
   - Mehr Benutzerinteraktion, Action-Historie
   - Alle Sprachen in einem Programm, einem Setup
   - Dynamischer Wechsel zwischen den Sprachen
   - Dynamischer Wechsel zwischen Kryptoprovidern
   - Automatische Updates aus dem Internet (unter Beibehaltung der ge�ffneten
     Dateien nach dem Neustart)
   - Alle Funktionen als Thread implementieren (parallel, alle abbrechbar)
   - Funktionen nutzen mehrere Core, falls vorhanden
   - Einfacheres Erstellen von Kaskaden zusammengestellt aus den
     existierenden Elementen
   - Anbieten eines Recorders f�r Benutzereingaben
   - Alle Dateien als Stream nutzen, um auch sehr gro�e Dateien bearbeiten
     zu k�nnen
   - Steuerung der gesamten Funktionalit�t auch von der Kommandozeile.

b) Java-CrypTool (JCrypTool, JCT):
   - Komplett neu designtes CrypTool in Java mit Eclipse/RCP
   - Plattform-unabh�ngig
   - Nutzung von SWT f�r die GUI
   - Nutzt strikt die Standards von Eclipse 3.x
   - Bouncy-Castle und FlexiProvider werden als Krypto-Provider benutzt.
     Evtl. wird FP in BC aufgehen.
   - Enge Zusammenarbeit mit dem Lehrstuhl Prof. Buchmann, TU Darmstadt f�r
     die Integration des FlexiProviders
   - F�r Einsteiger, aber auch f�r Experten
   - Nutzung von Github mit Git zur Sourcecode-Verwaltung:
     https://github.com/jcryptool/
     https://github.com/jcryptool/core
     https://github.com/jcryptool/core/wiki
     https://github.com/jcryptool/crypto
     https://github.com/jcryptool/doc

c) CrypTool 2.0 (CT 2)
   - Komplett neu designtes CrypTool in C# mit dem .NET-Framework und WPF
   - Nutzt strikt die Standards von Microsoft .NET (Aussehen wie Office 2007)
   - Nutzung von Windows Presentation Foundation (WPF) zur Gestaltung
     von multimedialen Oberfl�chen (GUI) mit Vektorgraphiken
   - Das gesamte Projekt l�sst sich mit der kostenlosen VS2010-Express-
     Edition f�r C# erstellen.
   - Verf�gbar sind die .NET Krypto-Provider, Bibliotheken wie GMP/MPIR und
     Crypto++ per Wrapper, und BouncyCastle f�r C#
   - Hoher Lerneffekt bei Einsteigern durch visuelle Programmierung
   - Enge Zusammenarbeit mit den Lehrst�hlen Prof. Weis in Duisburg-Essen
     und Prof. Wacker in Kassel
   - Nutzung von Subversion zur Source-Code-Verwaltung, gehostet von der
     Universit�t Duisburg-Essen: http://www.cryptool2.vs.uni-due.de.



A.2.2. Funktionen der Nachfolger-Projekte CT2 und JCT1
       -----------------------------------------------
Die neuen Versionen (siehe Kapitel A.2.1) sind:
- CT2: CrypTool 2.0  und
- JCT: JCrypTool 1.0


Einige Funktionen der Release-Versionen der Nachfolger-Projekte:
- CT2  Visuelle Programmierung (Komposition von Protokollen und Workflows)
- CT2  Tutorial: Primzahlen-Visualisierungen
- CT2  Tutorial: Bleichenbacher Angriff, Erweiterungen von K�hn
- CT2  Tutorial: SOA-Security (SOAP-Nachrichten nach WS-Security)
- CT2  WEP-Verschl�sselung und WEP-Analyse (Angriff auf WEP-Protokoll)
- CT2  DH-Schl�sselaustausch
- CT2  Steganographie-Verfahren
- CT2  Smartcard-Plugin (sendet Kommandos an eine Chipkarte
                         mittels der PC/SC-Schnittstelle in Windows)
- CT2  Cube Attack gegen symmetrische Chiffren (I. Dinur und A. Shamir)
- CT2  Homomorphe Verschl�sselung (Paillier)
- CT2  Quadratisches Sieb (deutlich schneller als in CT1)
       Siehe:
       - https://www.cryptoportal.org/details_links.php?PHPSESSID=1a3ea85bebc01e983a852682cecc48b3&link_id=69
       - http://bscw.schule.de/pub/bscw.cgi/d864899/Schulz_Witten_Zeit-Experimente.pdf
- CT2  Solitaire-Verschl�sselung und -Analyse
- CT2  Dezimalisierungsverfahren (Visa, Modulo, Multiplikation, IBM)
- CT2  Vigen�re-Autokey-Verschl�sselung und verteilte Analyse dazu
- CT2  Suche nach Wort-Patterns m.H. von Normierungen (z.B. "einen" = 12313)
- CT2  LFSR, NLFSR
- CT2  Verschl�sselung mit Enigma, Purple, T310/50, M209
- CT2  Verschl�sselung mit DES, AES, PRESENT, ...

- JCT  Adaptive Navigationsleiste, wahlweise als Baum oder Palette, mit Filter
- JCT  Vigen�re-Autokey-Verschl�sselung
- JCT  Visualisierung klassischer (Analyse-)Verfahren
- JCT  Einstellbarkeit aller Detail-Parameter moderner Algorithmen
       in der FlexiProvider-Perspektive (insbesondere Post-Quantum-Algorithmen)
- JCT  Dragon-Verschl�sselung & LFSR
- JCT  Entropie-Analyse
- JCT  Visualisierung von Kleptographie-Algorithmen (vier verschiedene
       "b�swillige" Verfahren zur RSA-Schl�sselerzeugung incl. SETUP-Angriff)
- JCT  Multi-partite Schl�sselvereinbarung
- JCT  Homomorphe Verschl�sselung
- JCT  Analyse von Transpositions-Chiffren mit dem ACO-Algorithmus
- JCT  Visualisierung von Zero-Knowledge-Beweisen
- JCT  Running-Key-Verschl�sselung und Analyse (Viterbi)
- JCT  Verifiable Secret Sharing
- JCT  XML-Sicherheit (Demonstrator f�r XML-Signaturen)
- JCT  M�chtige Action-History und Kaskadierungs-Unterst�tzung



A.3. M�gliche Punkte f�r eine Weiterentwicklung -- Neue Funktionen, Ideen
     --------------------------------------------------------------------

Die Entwickler-Wikis von CT2 und JCT enthalten je eine Liste mit Programmier-
Aufgaben zu weiteren Funktionen, die nachgefragt wurden:
- CT2: https://www.cryptool.org/trac/CrypTool2/wiki/StudentTasksProposals
- JCT: https://github.com/jcryptool/core/wiki/project-Ideas

Hier sind m�gliche Themen f�r Erweiterungen, die noch bei CT1 hochkamen.
Was schon in CT2 oder JCT geplant ist, ist entsprechend gekennzeichnet.


A.3.1. Funktionalit�t: Algorithmen / Verfahren
       ---------------------------------------
- Weitere Algorithmen zu jedem Thema implementieren:
    * Codes:
       - T9 (http://de.wikipedia.org/wiki/Text_on_9_keys) etc.
    * Verschl�sselung:
       - Klassische Verfahren (incl. Analyse): z.B.
           - Sigaba
           - Weitere Rotorchiffren, Hagelin, Lorenz-Maschine
           - CT2  Alphabete auch f�r die klassischen Verfahren
                  auf 256 Zeichen ausdehnen
       - Symmetrische Verfahren:
           Camellia (RFC3713), RC5 und Gost (http://vipul.net/gost),
           Radio Gatun, SOSEMANUK, VSH, ...
       - Public-Key-Verfahren: McEliece, Rabin, NTRU
       - Demonstration der Visuellen Kryptographie
       - Neue Verfahren von Ecrypt (Network of Excellence in Cryptology)
         integrieren. Siehe http://www.ecrypt.eu.org
    * Hashverfahren:
       - Tiger (http://www.cs.technion.ac.il/~biham/Reports/Tiger)
       - Alle SHA-3-Kandidaten
         (http://csrc.nist.gov/groups/ST/hash/sha-3/index.html)
    * Protokolle / Protokollschw�chen:
       - Visualisierung von Man-in-the-Middle-Angriffen
       - Visualisierung von SSL
       - Blind Signatures
       - Elektronische Wahlen
       - CT2 Virtuelle Kreditkartennummern (VCC) und Pr�fziffern
       - JCT Visualisierung eines Quantum-Schl�sselaustausch-Protokolls (BB84)
       - JCT Visualisierung des KEGVER-Protokolls und weiterer Kleptographie-
             Verfahren (http://www.cryptovirology.com)

- Schnelle Auswahl der verschiedenen Verschl�sselungsverfahren
  �ber eine Dialogbox statt �ber die Men�s (Offenlegung aller
  Steuerparameter der Algorithmen) (analog CryptoBench)

- CT2  GNFS (General number field sieve) zur Faktorisierung (Ted)

- Erzeugung aller Hashwerte aus regul�rem PW-Ausdruck (Hartmann)

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
  - Weitere Zufallstests (aus der spanischen Version?)
  - CT2  NIST Zufalls-Testsuite

- Weitere Standards implementieren und direkt �ber die Men�s bzw.
  aus der Online-Hilfe heraus an alle Stellen verzweigen, wo diese
  Standardverfahren (z.B. PKCS#5) verwendet werden (Hauptarbeit
  dabei sind das User Interface und die Dokumentation).

- JCT  PGP-S/MIME Interoperabilit�t

- Verbindung zwischen CrypTool (PKCS#12) und PGP schaffen, indem
  man PGP-Keys in CrypTool verwenden kann. Idee: Per Passwort-Eingabe
  �ffnet man seinen privaten Keyring, analysiert die Struktur, holt den
  Key heraus (PGP-Sourcen sind gegeben) und nutzt diesen, um mit den in
  CrypTool implementierten Verfahren PGP-Files zu entschl�sseln oder zu
  signieren. Damit wird klar, dass auch PGP die Standard-Algorithmen nutzt.

- Testbett mit Beispielen und L�sungen erzeugen, damit man das
  Testen automatisieren kann und damit man sicherstellen kann,
  dass durch Programm�nderungen nicht alte funktionierende
  Funktionalit�t negativ beeinflusst wird:
  a) Interface, um Testaufgaben manuell in Dialogboxen zu laden
  b) Schnittstelle schaffen, mit der sich die Testaufgaben aus
     einer Datei selbst in die Dialogboxen laden.
     Vielleicht sogar Script-Steuerung f�r alle Dialoge oder
     automatische Testtools vom Markt einsetzen.
  c) Commandline-Interface schaffen, das ohne Dialogboxen alle
     Aufgaben aus einer Datei per Schnittstelle ausliest und die
     L�sungen wieder in eine Datei schreibt:
     -> Abgleich automatisierbar
     -> neue Version leichter testbar.



A.3.2. Funktionalit�t: Analyse
       -----------------------
- CT2  Framework zum Verteilen kryptoanalytischer Berechnungen
- CT2  Toolbox zum Erzeugen und Analysieren von Strom-Chiffren
- CT2  Framework zum Bau und zur Analyse von LFSR-Stromchiffren
- CT2  Framework zur Analyse von Seitenkanal-Angriffen

- W�nschenswert w�re, wenn insbesondere die Analyse in allen Formen und
  samt Visualisierung weiter ausgebaut werden k�nnte.

- Zu ALLEN implementierten Verschl�sselungsverfahren eine (gute) Analyse
  anbieten, die (zumindest f�r die klassischen Verfahren besser ist als
  Brute-Force), z.B. f�r
   - Nihilist
   - Turning Grille (Fleissner-Schablone)

- Angriff auf symmetrische Verschl�sselungsverfahren, bei denen die
  Parameter der Verschl�sselungsverfahren flexibel reduziert werden k�nnen.

- Differentielle Kryptoanalyse auf symmetrische Chiffren (DES, ...).

- Die Brute-Force-M�glichkeiten erweitern: Nutzen von Wissen
  - um Teile des Klartextes,
  - um Teile des Schl�ssels.

- Demo, wie lange eine vollst�ndige Schl�sselsuche dauert (in Abh�ngigkeit
  von der Schl�ssell�nge).

- Analyse neu implementieren f�r:
   * homophone Verschl�sselung
   * Permutationen/Transpositionen
      - Known-Plaintext-Analyse der doppelten Spaltentransposition,
      - Ciphertext-Only-Analyse des Doppelw�rfels
   * Playfair-Verschl�sselung
      - C-Sourcen (Gunnar-Andresson) liegen uns vor.

- Analyse verbessern f�r:
   * monoalphabetische Substitution
      - explizite Anzeige von vertauschten Digrammen wie "ie"/"ei"
        und von Doppelzeichen wie "mm".
      - CT1: Ersetzte Buchstaben in der Dialogbox nicht nur gro�, sondern
        auch in roter Schrift anzeigen.
   * Vigen�re-Analyse noch weiter veranschaulichen:
      - Bei den Keyl�ngen die Eingabe eines Bereiches statt eines Einzel-
        wertes erm�glichen (z.B. "2-9") und dann in der Folgemaske auch
        f�r jede L�nge den statistisch wahrscheinlichen Schl�ssel ausgeben.
        Evtl. die Top-10 wahrscheinlichsten Keys f�r eine bestimmte L�nge
        anzeigen.
      - Per Klick auf einen der angezeigten Keys erh�lt man die jeweilige
        Entschl�sselung. Per Klick auf einen weiteren Button werden f�r
        alle Keys die Entschl�sselungen angeboten.
      - Mit der Analyseoption "Basischiffre anzeigen" werden z.Zt. pro
        Spalten-Caesar (d.h. bei einer ermittelten Schl�ssell�nge von
        n wird das Caesar-Verfahren f�r jeden Wert von i jeweils auf die
        Zeichenmenge m[i+k*n] mit 1<=i<=n und k>=0 angewandt) die
        Grafiken Korrelation und ASCII-Histogramm erstellt.
        Zus�tzlich k�nnte man noch den Text des jeweiligen Spalten-
        Caesars ausgeben.

- W�rterb�cher f�r alle Angriffe benutzen, nicht nur f�r die Substitution.

- Nutzung von Algorithmen aus dem Bereich KI (K�nstliche Intelligenz) und
  GP/GA (Genetic Programming/Algorithms) zur automatischen Analyse
  (klassischer) Verschl�sselungsverfahren.

- CT2: Massenmustersuche: Erweiterte, hoch performante Mustersuche, die
  nach vorgegebenen normierten und regul�ren Mustern beliebiger L�nge
  sucht (z.B. um alle Patterns in einer Datei zu finden, die auch in
  einer anderen (vorzugebenden) Datei vorkommen), oder die nach
  unbekannten, aber mehrfach vorkommenden Mustern in Dokumenten sucht.
  K�nnte dann auch um Ersetzen erweitert werden.

- Korrekturm�glichkeit einzelner Zeichen bei der Analyse von XOR,
  ADD, Vigen�re. Ausschluss unverschl�sselter Bereiche.

- Anzeigen des zweit-, dritt-, ... -besten Treffers bei der
  XOR/ADD-Analyse (dies kann zu einer k�rzeren Schl�ssell�nge
  f�hren).

- Autokorrelation: vor der �berlagerung noch Operationen auf den
  Bl�cken ausf�hren (XOR, ADD, ...). Macht das Sinn?

- Editieren der Homophonen-Schl�ssel (ben�tigt bei der Analyse
  der Homophonen Verschl�sselung)

- Gleitende Entropie: Automatisierte Suche von Stellen in einem Dokument
  mit hoher Entropie

- Vorhandene Einschr�nkungen in der N-Gramm-Analyse bzgl. Dateigr��e
  ausdehnen (evtl. mit Benutzerfeedback und der M�glichkeit abzubrechen,
  wenn viel Zeit erforderlich).
- Timing Attack auf RSA / Vorteile Blinding

- Aktuelle Hashangriffe darstellen (z.B. Erstellen von PS-Dokumenten nach
  Lucks oder von PDF-Dokumenten nach BSI mit gleichem Hashwert) und
  Aufzeigen der Anwendungsszenarien.

- Nutzung von Rainbow-Tabellen

- Weitere Angriffe auf konkrete Protokolle implementieren und/oder
  visualisieren, um zuk�nftige Konzepte zu verbessern.



A.3.3. Interne Schnittstellen / Editoren
       ---------------------------------
- Alle benutzten Schl�ssel in einem Container speichern.
  Alle Schl�ssel der unterschiedlichen Verschl�sselungsverfahren in einem
  Dialog anzeigen.
  Abspeichern permanent als Datei in einem Format, das f�r alle CrypTool-
  Versionen gemeinsam ist.

- In den Nachfolger-Projekten von CT1: Ausgabe/Anzeige komplett von
  den Kryptomodulen trennen (dies erleichtert Portierungen und Fehlersuche).

- Parametrisierung, wo immer das m�glich ist:
  Anbieten einer Option, um z.B. den Initialisierungsvektor,
  die Anzahl von Runden, die Schl�ssel- oder Wortl�nge oder
  das Padding zu setzen (z.B. f�r den RC5-Algorithmus - siehe RFC 2040).
  Diese Parameter m�ssen dann auch in das Format f�r den internen
  Schl�sselspeicher aufgenommen werden.

- Langzahl- und Krypto-Bibliotheken:
   - Unterst�tzung weiterer Libraries
     (FLINT/C, Wei Dai's Crypto++, ...).

- JCT  Commandline-Funktionalit�t (f�r Benutzer und Test-Automatisierung)



A.3.4. User-Interface / Visualisierungen
       ---------------------------------
- In den Dialogen in CrypTool 1.x k�nnen Zahlen nicht immer in allen
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

- Weiterhin w�re eine interaktive Anbindung an das CAS-System Sage
  w�nschenswert (http://www.sagemath.org/).

- Generelle Visualisierung der entsprechenden mathematischen Grundlagen, z.B.:
  - anhand eines Lehrbuchs
  - wie mit den Sage-Notebooks zur Einf�hrung in ECC von Maike Massierer:
      - http://sagenb.org/home/pub/1126/  (Version 1.3, January 2011)
    Dieses Deckblatt enth�lt keine Berechnungen, sondern nur die Links
    zu den �brigen Teilen; zum Ausf�hren der folgenden Teile
    muss man sich selbst Kopien als Sage-User anlegen.
  - wie die PascGalois Software (Group Calculator)
      - http://www.pascgalois.org/software.html
  - http://www.martindalecenter.com/Calculators2_6_NZ.html
  - http://world.std.com/~reinhold/BigNumCalc.html
  - http://mathforum.org/library/resource_types/calculators/?keyid=28652723&start_at=301&num_to_see=50
  - http://www.hbmeyer.de/pythagen.htm (Pythagorean Triples)

- CT1: F�r den Benutzer konfigurierbar einstellbar machen, ob neue Fenster
  wie bisher innerhalb des Hauptfensters erscheinen oder als "freie"
  (modale oder a-modale) Fenster daneben stehen.
  Einzelne Dialogboxen (z.B. N-Gramm-Analyse, Manuelle Analyse,
  Hybriddemo) als a-modale Fenster erzeugen, so dass man beliebig
  zwischen Hauptfenster und Auswertungsfenster springen kann
  (aufw�ndigere Steuerung, Erlauben oder Abfangen von Mehrfachauf-
  rufen derselben Dialogbox, evtl. Update nach Fokus-Wechsel bzw.
  nach �nderung der Originaldaten im Hauptfenster, ...).

- AES-Tool als eigenst�ndiges Tool erweitern:
  - Einbinden des PKCS#5-Dialogs, um dem Benutzer seine gewohnte
    Eingabeweise zu bieten: Dabei zuf�llige Werte f�r Salz und
    Iterationszahl voreinstellen und den User auffordern, sich
    den Hexwert zu merken oder ihn sicher aufzubewahren.
  - Auch Verschl�sseln ganzer Verzeichnisse.
  Generell sind bei CrypTool die Schl�ssel ganz bewusst f�r die
  modernen Verschl�sselungsverfahren in Hex-Zeichen einzugeben.
  Es ist Absicht, dass man in CrypTool zun�chst sieht, welche Art
  Schl�ssel die verschiedenen Algorithmen erwarten: Bei den
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
  �bernommen. AES-256 braucht dazu SHA-256.

- F�r den Benutzer konfigurierbar einstellbar machen, wie gro� die
  Teile von Text- und Bin�rdateien sein k�nnen, die CrypTool laden kann.

- In der Anzeige f�r Grafiken eine Vergr��erungsfunktion einbauen
  und / oder die Koordinaten anzeigen, an denen sich die Maus befindet.

- CT1: Alle Dialoge thread-safe machen, damit man Langl�ufer abbrechen kann,
  ohne das ganze Programm per Task-Manager zu beenden.
  Implementiert ist dies schon z.B. im Faktorisierungs-Dialog.
  Dies ist insbesondere bei der Kryptoanalyse sinnvoll (z.B. w�re es n�tig
  bei der Known-Plaintext-Analyse der einstufigen Spaltentransposition):
  Bei unbeschr�nkter Obergrenze der Permutationsl�nge dauerte es ab 900
  "ewig". Hier wurde es dann aus Konsistenzgr�nden auf 100 beschr�nkt,
  weil auch die Permutations-Verschl�sselung keine l�ngeren Permutationen
  zulie�.

- Visualisierung:
   - Generell ist die Visualisierung der Abh�ngigkeiten und Abl�ufe bei
     Protokollen (nicht nur bei "einfachen" Algorithmen) eine sinnvolle
     Erweiterung.
   - Angriffe auf schwache RSA-Schl�ssel sind in der CT1-Onlinehilfe
     beschrieben: Siehe Men� Hilfe \ Szenarien (Tutorials) \
     RSA-Kryptosystem (Demonstration), unter dem Abschnitt
     "3. Angriff auf das RSA-Verfahren", wo erkl�rt wird, dass die
     Faktorisierung des Moduls das Verfahren knacken kann.
     Dies ist implementiert, aber nicht visualisiert.
   - Angriffe auf andere asymmetrische Verfahren sind in CrypTool
     bisher noch gar nicht behandelt. Um Diffie-Hellman, DSA oder
     EC-DSA anzugreifen, muss man "diskrete Logarithmen" berechnen.
     Auch dies k�nnte man nach dem Implementieren wieder visualisieren.
   - Avalanche-Effekt zeigen bei Hash- oder Verschl�sselungsverfahren.



A.4. CrypTool v1 unter Linux
     -----------------------

A.4.1. Ausf�hren von CrypTool v1 unter Linux mit Wine
       ----------------------------------------------
Bei einem kurzen Test mit Wine 1.3.28 unter Ubuntu 11.10 lief das Setup von
CrypTool 1.4.31 Beta 04 (compiliert mit VS2008) ok. CrypTool selbst lief ok mit
einigen Verschl�sselungsverfahren und mit der RSA-Schl�sselerzeugung. Aber in
der RSA-AES-Hybrid-Verschl�sselungs-Demo und beim Klicken auf Links in der
Onlinehilfe st�rzte Wine ab.

Wir unternehmen keine Anstrengungen, Wine zu unterst�tzen.
Stattdessen empfehlen wir, die plattformunabh�ngige Version JCT zu benutzen, die
auch unter Linux l�uft (siehe Kapitel 3.5).


A.4.2. Portierungsversuch von CrypTool v1 nach Linux mit Qt
       ----------------------------------------------------
Eine Portierung von CrypTool 1.4.x nach Linux mit Hilfe von GCC 4.x und
Qt 4.x war au�erhalb des eigentlichen CrypTool-Projektes von Einzelpersonen
begonnen worden, aber mangels Zeit nicht/wenig fortgesetzt worden.
- Die Bibliotheken von Secude, Miracl, NTL, OpenSSL und GMP/MPIR stehen
  zur Verf�gung.
- Gesamtaufgabe in sinnvolle Teile zerlegt:
       - Oberfl�che: Hier liegt die Hauptarbeit.
       - Funktionalit�t, implementiert in purem C/C++: ok
       - Online-Hilfe in HTML: ok.
- Die erste Beta wurde im November 2007 ver�ffentlicht.
  Die zweite Beta ("still no functional version", 11 % der geplanten
  Aufgaben) wurde am 15.12.08 ver�ffentlicht.
- Siehe http://www.cryptoolinux.net/

################################################################

Bitte schauen Sie auf die Webseite wwww.cyptool.org und probieren die neuen
Versionen von CT2 und JCT.

