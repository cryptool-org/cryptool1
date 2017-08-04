==================================================================
    CrypTool, Version 1.4.31 für Win32, August 2017

CrypTool v1 (CT1) ist ein freies, internationales
E-Learning-Programm für Kryptographie und Kryptoanalyse.

    (c) Contributors
        Dazu gehören u.a. Deutsche Bank AG, Frankfurt am Main, und die
        Universitäten Siegen, Darmstadt, Bochum, Duisburg-Essen und Kassel.
        1998-2017
    Freie Software und Open Source gemäß der Apache Lizenz 2.0
    www.cryptool.org
    Prof. Bernhard Esslinger
    $Id$
==================================================================

 1. ... Kurzbeschreibung des CT1-Paketes (und bekannte Fehler)
 1.1. ... Wie Sie als Benutzer am besten starten -- Der Einstieg in CT1
 1.2. ... Was beinhaltet die CT1-Distribution
 1.3. ... Danke
 1.4. ... Maintainer, Hosting, Webseite und Welcome
 2. ... Was bietet CT1 im Detail
 2.1. ... Was können Sie mit CT1 machen
 2.2. ... Informationen für Entwickler / Wo finden Sie die Sourcen
 2.3. ... Wo finden Sie weitere Überblicke zu CT1
 2.4. ... Neuerungen in Version 1.4.20 / 1.4.21
 2.5. ... Neuerungen in Version 1.4.30
 2.6. ... Neuerungen in Version 1.4.31
 3. ... Beschränkungen und Voraussetzungen
 3.1. ... Anwendungsbereich dieser Lern-, Trainings- und Awareness-Software
 3.2. ... Win32-Umgebung, Rechte bei Installation und Betrieb, Java-Runtime
 3.3. ... Interaktive Online-Hilfe unter Windows XP
 3.4. ... Unterstützung verschiedener Sprachen
 3.5. ... Einschränkungen / Features / Tipps
 3.6. ... Mit älteren CT1-Versionen erzeugte Zertifikate und Schlüssel
 4. ... Installation / Deinstallation / Schlüsselnutzung / Betrieb
 4.1. ... Installation
 4.2. ... Deinstallation von CT1
 4.3. ... Wiederholte Nutzung von Schlüsseln
 4.3.1. ... Schlüssel aus vorherigen Versionen
 4.3.2. ... Schlüssel gespeichert in den Dateien des PSE-Verzeichnisses
 4.4. ... Installation in Mehrbenutzersystemen
 4.5. ... Betrieb in Mehrbenutzersystemen
 4.6. ... Installation auf einem Netzwerk-Laufwerk --> Onlinehilfe-Problem
 5. ... Liste der Dateien in der Auslieferung
 5.1. ... Überprüfen der Integrität der heruntergeladenen Dateien
 6. ... Kurze Historie der freigegebenen Hauptversionen von CT1
 7. ... Feedback und Kontaktadressen
 8. ... Verweise / Auszeichnungen
 8.1. ... Artikel / Wissenschaftliche Veröffentlichungen über CrypTool
 8.2. ... Sonstige Referenzen auf CrypTool
 8.3. ... Weitere Freeware-Projekte (Crank, CAP, CryptoStudio, SageMath, etc.)
 8.4. ... Auszeichnungen
A. ... Anhang
A.1. .... Roadmap nach CT 1.4.31
A.2. .... Nachfolger-Projekte mit Java/Eclipse und C#/.NET
A.3. .... Mögliche Punkte für eine Weiterentwicklung -- Neue Funktionen, Ideen
A.4. .... CT1 unter Linux


Benutzte Abkürzungen:
CT   CrypTool (z.B. um das ganze CT-Projekt zu bezeichnen)
CT1  CrypTool 1 = CrypTool-Version 1 (diese Version enthält diese Readme-Datei)
CT2  CrypTool 2 = CrypTool-Version 2 (nutzt .NET; läuft unter Win32)
JCT  JCrypTool  = Java-CrypTool (läuft unter Win32, Linux und MacOS)
QCT  QtCrypTool = Zukünftige Portierung von CT1 mit Qt (auch Plattform-unabhängig)


1. Kurzbeschreibung des CT1-Paketes (und bekannte Fehler)
   ------------------------------------------------------
Diese Readme-Datei gehört zur Distribution des Programms CrypTool 1 (CT1).
CrypTool ist Open-Source und kostenlos. Mit CrypTool kann man kryptographische
Verfahren erlernen, ausprobieren und sowohl bekannte wie unbekannte Verfahren
analysieren.

Schon in der Antike wurden solche Verfahren zur Geheimhaltung von Nachrichten
entwickelt. Heutige Verfahren basieren auf moderner Mathematik und erlauben
neben der Verschlüsselung auch die Prüfung der Integrität, die Erstellung von
Signaturen, sichere Authentisierung und Vieles mehr. CrypTool unterstützt
sowohl die Ausführung als auch die Analyse solcher Verfahren.

CT1 wird seit 1998 im CrypTool-Projekt entwickelt. Im CrypTool-Projekt
arbeiten über 70 Personen weltweit und ehrenamtlich mit.

Zu jedem Programmteil von CT1 gibt es reichhaltige Online-Hilfe, die auch
ohne tiefes Kryptowissen verstanden werden kann.

CT1 existiert in den 7 Sprachen (Sprachkürzel nach ISO 639-1):
- Deutsch (DE),
- Englisch (EN),
- Französisch (FR),
- Griechisch (EL),
- Polnisch (PL),
- Serbisch (SR) und
- Spanisch (ES).

In allen Sprach-Versionen hat das Programm die gleiche und volle
Funktionalität -- übersetzt und lokalisiert sind also jeweils die
Oberfläche (Menüs, Dialoge, etc.) der Programme CrypTool, AES-Tool
und Zahlenhai, und das Installationsprogramm (Setup).

Hier eine Auflistung der restlichen Komponenten des CT1-Paketes,
die bisher nicht in allen Sprachversionen lokalisiert werden konnten:
                        DE    EN    EL     ES     FR     PL     SR
Onlinehilfe (html)      ja    ja    nein   nein   nein   nein   nein
Readme-Datei (txt)      ja    ja    nein   nein   nein   nein   nein
CT-Buch (pdf)           ja    ja    nein   nein   nein   nein   nein
CT-Präsentation (pdf)   ja    ja    nein   ja     nein   nein   nein
Elsner-Stories (pdf)    ja    ja    nein   nein   nein   nein   nein

Im Deutschen und Englischen liegen alle Komponenten von CT1 übersetzt
vor. Wenn etwas in einer der anderen Sprachversion nicht vorliegt, wird
die englische Komponente beigelegt.

Weitere Sprachversionen (türkisch, russisch, ukrainisch,...)
sind teilweise in Arbeit.

Momentan ist die griechische Version nicht verfügbar, da der Compiler VS2008
die griechischen Fonts (als UTF16) nicht korrekt unterstützt.
Aus anderen Gründen müssen wir für CT 1.4.31 jedoch VS2008 benutzen.
Nichtsdestotrotz werden wir ab CT 1.5 wieder den neuesten MS-Compiler
(VS 2017) einsetzen. (xxx)

Die aktuelle Release-Version von CrypTool und den Quellcode dazu finden Sie
unter der folgenden Internet-Adresse (dazu ist keine Registrierung nötig):
                https://www.cryptool.org/de/

Seit Anfang 2010 werden ca. 6000 CT1-Pakete pro Monat herunter geladen
(davon entfallen etwas über die Hälfte auf die englische Version).

Zu CT1 gibt es zwei Nachfolger-Versionen, genannt CT2 und JCT.
Deren Download-Zahlen betragen: (xxx)
               JCT: ca. 1000 / Monat.
               CT2: ca. 4000 / Monat
Die Nachfolger-Versionen von CT1 bieten einen deutlich größeren
Funktionsumfang als CT1.

Ziel aller CrypTool-Versionen ist es, kryptographische Mechanismen anschaulich
zu machen und die Verwendung und die Grenzen einzelner Verfahren aufzuzeigen.
In CT1 sind fast alle State-of-the-art-Kryptofunktionen implementiert.
Dies ermöglicht einen "spielerischen" Einstieg in die moderne und klassische
Kryptographie -- unter einer einheitlichen Oberfläche.

CrypTool wird weltweit eingesetzt
- in Unternehmen sowohl zur Mitarbeiter-Sensibilisierung bezüglich
  IT-Sicherheit (Awareness) als auch zur Ausbildung,
- im Schulunterricht und
- in der Lehre an vielen Hochschulen.

Bitte beachten Sie die Lizenz- und Nutzungsbestimmungen für CT1.
Diese werden z.B. auf der Webseite, bei der Installation und auf der
Einstiegsseite der Online-Hilfe erläutert.

Für bisherige Benutzer von CT1 dürften in diesem Readme vor
allem die Kapitel 2.6 (Neuerungen in CT 1.4.31) und in Kapitel A.1
(Roadmap nach CT 1.4.31) interessant sein.

Wir laden jeden herzlich ein, an CrypTool mit zu entwickeln oder
Feedback zu geben. Auch für Hinweise zu Arbeiten (Diplom-, Bachelor-,
Master-, Doktor-, Seminar- oder Projektarbeiten), die man in CrypTool
integrieren könnte, sind wir sehr dankbar.
Insbesondere junge Entwickler sind eingeladen, sich zu trauen -- sie können
bei erfahrenen Entwicklern sehr viel über professionelle Software-Entwicklung
lernen.
Kontakte: Siehe Kapitel 7 unten.


Bekannte Fehler:
1) Unter Windows 10 kam es häufiger zu folgendem Phänomen:
   Beim ersten Aufruf von PDFs (wie der CT1-Präsentation oder des CT-Buches)
   aus der CT1-Onlinehilfe, aus dem CT1-Menü "Hilfe" oder aus dem
   Windows-Startmenu heraus, startet Acrobat nicht. Evtl. zeigt die
   Onlinehilfe eine leere Seite, dann stürzt die Onlinehilfe ab.
   Beim nächsten Start der Onlinehilfe klappen diese Aufrufe.
   Das lag daran, dass ein Acrobat-Prozess hängen blieb. Wenn man diesen
   Acrobat-Prozess im Windows-TaskManager beendet, starten meist auch die
   PDFs aus CT1 heraus wie gewünscht.
   Leider kann es geschehen, dass sich auch beim folgenden Aufruf des PDFs
   wieder ein Acrobat-Prozess aufhängt (bis es einmal klappt) oder dass der
   Fehler beim Neustart von CT1 erneut auftritt.
2) Ein weiterer Fehler, der außerhalb unseres CrypTool-Codes zu liegen
   scheint:
   Ruft man den Calculator BC aus den beigelegten ZT-Tools auf (per F3 oder
   aus dem ZT-Menü "Rechner"), stürzt BC beim ersten Aufruf ab.
   Ohne ZT zu schließen, kann man F3 erneut drücken, und BC stürzt nicht
   mehr ab. Leider werden weder ZT noch BC weiter entwickelt, so dass sich
   an diesem Verhalten nichts ändern wird.



1.1. Wie Sie als Benutzer am besten starten -- Der Einstieg in CT1
     -------------------------------------------------------------
Vorausgesetzt wird, dass der Benutzer mit Anwendungen in einer
Windows-Umgebung umgehen kann.

Beim Start von CT1 öffnet sich zuerst im Vordergrund ein kleines
Begrüßungsfenster und dann die Arbeitsfläche von CrypTool.
Wenn Sie im Begrüßungsfenster gleich die F1-Taste drücken, erscheint
zusätzlich die Startseite der Online-Hilfe.

Diese Startseite der Online-Hilfe ist ein guter Ausgangspunkt, um alle
wesentlichen Inhalte von CrypTool kennen zu lernen (z.B. indem man den
Links auf dieser Startseite folgt).
Bitte lesen Sie die Hinweise und Tipps der Hilfe-Startseite.

Einen schnellen Einstieg in die Kryptographie mittels CrypTool
erhalten Sie, wenn Sie einige Szenarien (Tutorials) der Online-Hilfe
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

Eine 1-seitige Übersicht über alle Menüs in CrypTool (Menübaum) finden Sie
in dem als PDF beigelegten CrypTool-Buch (siehe Anhang A1 dieser PDF-Datei).

Eine Übersicht über alle Funktionen in den verschiedenen CrypTool-Programmen
finden Sie auf der Webseite des CT-Portals (www.cryptool.org) unter dem Menü
"Dokumentation --> CT-Funktionen" oder direkt via:
   https://www.cryptool.org/de/ctp-dokumentation/funktionsumfang

Wir wünschen viel Spaß beim Lernen und beim Ausprobieren der Funktionen
von CrypTool.


1.2. Was beinhaltet die CT1-Distribution
     -----------------------------------
Das CT1-Paket enthält die folgenden vier Hauptbestandteile:

(1) Das Programm CT1
--------------------
Hauptteil des CT1-Paketes ist das Programm CT1 selbst:

- In CrypTool ist eine umfangreiche Sammlung kryptographischer
  Algorithmen und Protokolle implementiert, die hervorragend
  dokumentiert und teilweise visualisiert sind.
  Somit ist CrypTool sehr gut geeignet zur Ausbildung und zur
  Mitarbeiter-Sensibilisierung für IT-Sicherheit.

- Die meisten der kryptographischen Basisalgorithmen stammen aus:
  - der Secude-Bibliothek (http://secude.com/),  (xxx)
  - der Miracl-Bibliothek von Miracl (vormals DCU/CertiVox, Shamus Software)
        (https://www.miracl.com),
  - der OpenSSL-Bibliothek (http://www.openssl.org/),
  - der NTL-Zahlentheorie-Bibliothek von Victor Shoup
        (http://www.shoup.net/ntl/),
  - der APFLOAT-Bibliothek von Mikko Tommila (http://www.apfloat.org/apfloat),
  - der MPIR-Bibliothek für beliebig genaue Arithmetik (entstanden aus GMP)
        (www.mpir.org) und
  - der cv act library der cv cryptovision GmbH (www.cryptovision.com). (xxx)

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
    - Demos und Beispiel-Szenarien (hier werden Einzelverfahren
      Schritt für Schritt erläutert)
c) Buch zum Thema Kryptographie (beigelegt als PDF-Datei),
d) Präsentation, die auf Folien die Möglichkeiten von CrypTool
   aufzeigt (beigelegt als PDF-Datei).


(3) Eigenständige Programme
---------------------------
Die folgenden Programme und können aus CrypTool heraus, aber auch stand-alone
aufgerufen werden:

a) Das Programm AES-Tool v 2.7 (entstanden im CrypTool-Projekt):
   Mit dem AES-Tool kann man selbst-entpackende Executables erstellen.
   AES-Tool verschlüsselt mit einem Session-Key den Inhalt einer beliebigen
   Datei mit dem AES-128 Bit-Verfahren.
   Dieses Verschlüsselungstool kann sowohl als Fensteranwendung als auch
   von der Kommandozeile (z.B. aus einer Batchdatei) aufgerufen werden.
   Bei der CrypTool-Installation wird diesem Programm die Dateiendung "AES"
   zugeordnet.

b) Das Lernspiel "Der Zahlenhai" v 1.2.4 (entstanden im CrypTool-Projekt):
   Dieses Lernspiel bringt Schülern den Umgang mit Teilern und Primfaktoren
   näher.

c) Das Animationsprogramm Animal (siehe http://www.algoanim.net)
   (Version 2.4.9, 5. September 2016):
   Animal is a general-purpose animation tool with a current focus on
   algorithm animation. It contains a lot of animation generators
   (currently, there are more than 500.)
   Mit diesem an der TU Darmstadt von Dr. Rößling gepflegten Programm
   kann man die Einzelschritte von Algorithmen oder die Komponenten von
   Datenstrukturen beliebig genau modellieren, die Einzelschritte manuell
   vor und zurück abspielen oder automatisch ablaufen lassen.
   Auch Source-Code-Zeilen lassen sich damit dynamisch visualisieren.
   Das Animal-System erlaubt die Erstellung von Animationen mithilfe
   einer GUI, einer Skriptsprache sowie einer Java-API.
   Weitere Beispiele für Animationen finden sich im Animal-Repository
   auf der Webseite (www.algoanim.net/available-animations) und inkludiert
   im mitgelieferten Animal-ControlCenter.
   Animal benötigt JRE 1.7 (siehe Kapitel 3.2).

d) Ebenso wie Animal sind die ff. Programme eigenständige Java-Anwendungen
   (JAR-Dateien). Diese benötigen jeweils mindestens JRE 1.5 (s. Kapitel 3.2).
   - ECC-Demo v 1.1.1
   - AES-Flussvisualisierung
   - Das Control-Center zur Steuerung der S/MIME-Demo (diese erstellt anhand
     der Parameter eine XML-Datei, die zur Steuerung der aufgerufenen
     Flash-Animation dient).

e) Die Flash-Anwendungen:
   - Rijndael-Animation (visualisiert das Verschlüsselungsverfahren AES),
   - Rijndael-Inspektor (visualisiert die Änderungen der State-Matrix
                         nach jedem Schritt in jeder Runde bei AES),
   - S/MIME-Demo und
   - Enigma (visualisiert das 2. Weltkriegs-Krypto-Gerät Enigma).

f) Die Authorware-Anwendung "ZT" (Zahlentheorie) führt in die elementare
   Zahlentheorie ein und visualisiert viele der Verfahren und Konzepte,
   die Grundlage der modernen Public-Key-Kryptographie sind.
   Wo nötig zeigt sie auch die entsprechenden mathematischen Formeln.
   Dabei können die mathematischen Verfahren dynamisch mit eigenen
   kleinen Zahlenbeispielen ausprobiert werden.
   Beigelegt ist auch das Programm bc v1.06 der Free Software Foundation
   (FSF), mit dem man auf der Kommandozeile beliebig genau rechnen kann.



(4) Geschichten (mit Bezug zu Zahlentheorie und Kryptographie) und Rätsel
-------------------------------------------------------------------------
a) Als PDF-Datei sind zwei Geschichten beigelegt:
   - In "Der Dialog der Schwestern" wird von den beiden Titelheldinnen eine
     Variante des RSA-Verfahrens benutzt, um verschlüsselt zu kommunizieren.
   - In "Das Chinesische Labyrinth" muss Marco Polo zahlentheoretische
     Aufgaben lösen, um Berater des Großen Khan zu werden.

b) Krypto-Wettbewerbe / Krypto-Rätsel:
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
   5) Doppelwürfel (erstellt von Klaus Schmeh, Quelltext englisch, gelöst)
   6) "Die tanzenden Männchen" von Arthur Conan Doyle (Sherlock Holmes)
                   (transkribiert, gelöst)
   7) Harry-Potter-Chiffre (von Klaus Schmeh, Quelltext deutsch, ungelöst)
   8) "Mathias Sandorf" von Jules Verne (gelöst)

   Mehr Informationen dazu gibt es in der Onlinehilfe zu CT1 (unter dem
   Indexeintrag "Krypto-Wettbewerbe") und in dem Buch von Klaus Schmeh.

   Viele weitere Rätsel und Herausforderungen (Challenges) finden sich auch
   - auf den Seiten von CrypTool-Online und
   - auf den Seiten des Krypto-Wettbewerbs "MysteryTwister C3" (MTC3):
     https://www.mysterytwisterc3.org


Alle Einzeldateien, die bei der Installation des CrypTool-Paketes
auf Ihre Platte kopiert werden, sind in Kapitel 5 (unten in diesem
Readme) aufgeführt.



1.3. Danke
     -----
Zu CT1 haben sehr viele verschiedene Personen (über 300)
beigetragen -- insbesondere auch ehrenamtlich in ihrer Freizeit.
Einige sind namentlich in der Dialogbox aufgeführt, die man erhält,
wenn man in der Dialogbox "Über CrypTool" einen Doppelklick ausführt.
Herzlichen Dank an alle Mitwirkenden.

Besonders herausheben möchte ich einige Kernentwickler/Architekten
im CT1-Projekt, deren hohes und langjähriges Engagement und
deren hervorragende Kompetenz und Hartnäckigkeit solche dauerhaften,
lebendigen und erfolgreichen Open-Source-Projekte erst ermöglichen:
Jörg, Henrik, Florian, Peer.

Ebenfalls danken möchte ich einigen Kernentwicklern/Architekten in
den Nachfolger-Projekten CT2 und JCT, die mit großer Ausdauer und
Kompetenz die Schwierigkeiten mit den allerneuesten Entwicklungsumgebungen
und Software-Architekturen bewältigten:
- Arno, Nils, Philipp, Thomas, Sebastian, Martin, Timo, Soeren, ...
- Dominik, Simon, Matthias, Tobias, Amro, David, Michael, ...

Und natürlich den vielen Ungenannten, insbesondere Studenten und
Praktikanten, die viel dazu beitrugen -- und dabei noch viel mehr lernten
von den Experten im Projekt.

Ebenfalls beigetragen haben z.B. die Deutsche Bank AG, die Technische
Universität Darmstadt und die Universität Duisburg-Essen.

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

- Dr. Guido Rößling erlaubte uns, seine Freeware Animal, eine Java-basierte
  Animationssoftware, mit auszuliefern.

- Ebenfalls integrieren durften wir erweiterte Versionen von:
  - den beiden Flash-Animationen zu AES von Enrique Zabala,
  - der Flash-Animation zur Enigma von Dr. Frank Spieß,
  - dem Zahlentheorie-Lernprogramm von Martin Ramberger.
  Die über eine Verwendung außerhalb des freien CrypTool-Contextes
  hinaus gehenden Rechte verbleiben beim jeweiligen Autor.

- Die Firmen (siehe Kapitel 1.2)
  - Secude IT Security GmbH, (xxx)
  - Shamus Software Ltd und
  - cv cryptovision GmbH (xxx)
  gestatteten uns großzügigerweise, ihre Krypto-Bibliotheken zu nutzen.
  Diese mit CT1 verteilten Bibliotheken dürfen nicht in einem
  Kontext außerhalb von CrypTool benutzt werden, ohne vorher die erwähnten
  Firmen zu kontaktieren und nach ihren aktuellen Lizenzbedingungen zu
  fragen.

Ebenso möchten wir den Open-Source-Entwicklern herzlich danken, die uns
mit ihrem Code Anregungen gaben oder deren Code wir nutzen dürfen, z.B.
- die Bibliotheken OpenSSL, GMP/MPIR, APFLOAT und NTL,
- die Installations-Software NSIS (http://nsis.sourceforge.net/Main_Page),
- die Texteditor-Software Scintilla (http://scintilla.sourceforge.net),
- das Hex-Control (www.codeguru.com/Cpp/controls/controls/article.php/c5287),
- die Rendering-Engine aus OpenQVis (http://openqvis.sourceforge.net/).

Bedanken möchte ich mich auch bei
- Herrn Dr. Bartosz Sawicki von der Universität Warschau, der mit seinem
  Team die erste polnische Version erstellte.
- Herrn Dr. Gonzalo Alvarez von der Universität Madrid, der mit seinen
  Kollegen die erste spanische Version erstellte.
- Bojan Dimitrovski von der Universität Belgrad, der mit seinen
  Kollegen die erste serbische Version erstellte.
- Prof. Ioannis Mavridis und Dr. Theodoros Mastoras für die erste
  griechische Version von CT1.
- Alain Stephan für die erste französische Version von CT1.
Und einigen weiteren Personen (wie Pawel, Vasilios und Vesna), die dafür
sorgten, dass die Änderungen in neuen CT1-Versionen ebenfalls übersetzt wurden.

Evtl. weitere Übersetzungen:
- Türkisch (xxx): Interesse, aber bisher nicht begonnen.
- Russisch (xxx): Anfragen, aber bisher nicht begonnen.



1.4. Maintainer, Hosting, Webseite und Welcome
     -----------------------------------------
CrypTool war nie gebunden an eine einzige Person oder einen einzigen
Lehrstuhl. Auch das Hosting wechselte. Nach Siegen und Darmstadt kamen:
Der Lehrstuhl für Verteilte Systeme, Fakultät für Ingenieurwissenschaften
unter Prof. Dr. Torben Weis an der Universität Duisburg-Essen hostete CT
ab April 2008.
Seit April 2014 hostet der Lehrstuhl für Angewandte Informationssicherheit
von Prof. Dr. Arno Wacker an der Universität Kassel:
- die Webseiten des gesamten CrypTool-Projekts,
- das Subversion-Repository für die Programm-Sourcen von CT1, und
- das Subversion-Repository für die Programm-Sourcen des Nachfolgers
  CrypTool 2.
Webserver und Buildserver laufen momentan virtuell in einer Proxmox-Umgebung
mit 24 Intel Xeon E5-2640 a 2.5GHz und 128 Gigabyte Speicher.

Die CrypTool-Entwicklergruppe um Prof. Bernhard Esslinger fungiert
als Maintainer von CT1, d.h. sie kümmert sich um die Pflege des Codes,
die Veröffentlichung als Open Source und Freeware, und um die
Koordination der Weiterentwicklung. Die nächsten Schritte der
Roadmap sind in Kapitel A.1 und auch auf der Webseite veröffentlicht.

Homepage von CrypTool: www.cryptool.org

Wir freuen uns über jeden weiteren Entwickler, der sich an der
Weiterentwicklung von CrypTool beteiligt.
Ideen zur Weiterentwicklung finden Sie z.B. in Kapitel A.3.

Ebenfalls sehr willkommen sind uns Ideen und Infos, wie CrypTool in
Lehre, Schule und Ausbildung eingesetzt wird, damit wir dazu
beitragen können, diese Informationen auszutauschen. Ein Mittel
dazu ist z.B. das Kryptologie-Portal für Lehrer (www.cryptoportal.org).



2. Was bietet CT1 im Detail
   ------------------------

2.1. Was können Sie mit CT1 machen
     -----------------------------
Die generellen Eigenschaften und Funktionen von CT1 sind:

- E-Learning-Programm rund um das Thema Kryptographie und Kryptoanalyse.

- Alles in einem Programmpaket und steuerbar unter einer Oberfläche.

- Viele klassische Verschlüsselungsverfahren; und dazu teilweise manuell
  unterstützte, teilweise automatische Analysen (Known-Plaintext- und
  Ciphertext-Only-Angriff).

- Codierungen wie Base64 und UU-Encode.

- Nahezu alle modernen symmetrischen Verschlüsselungsverfahren: Und dazu
  jeweils die Brute-Force-Analyse
  (Beim Brute-Force-Angriff auf symmetrische Algorithmen werden Jokerzeichen
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

- Drei auf Gitterreduktion basierende Angriffe gegen das RSA-Verfahren,
  die dann greifen, wenn bestimmte Vorbedingungen erfüllt sind:
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
     - mit Animal: für die Verschlüsselungsverfahren Caesar, Vigenère,
                   Nihilist und DES,
     - mit Flash:  für AES, Enigma und S/MIME,
     - mit Java/SWT: - Punktaddition auf Elliptischen Kurven
                       (sowohl auf diskreten wie auf reellen Kurven),
                     - Flussvisualisierung von AES,
                     - Control-Center von S/MIME.

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
  wie sie in der Realität vorkam, kann der Angreifer den Sessionkey
  durch Protokoll-gerechte Anfragen an den Server hoch effizient
  berechnen.

- Hashwerte berechnen und ihre Sensitivität demonstrieren.

- Implementierung von HMAC-Verfahren (Kombination von Hashes und
  symmetrischen Verfahren zur Authentisierung von Nachrichten).
  Hashverfahren werden auch in den in CrypTool implementierten Konzepten
  PKCS#5 und digitale Signaturen verwendet.

- Das Shared-Secret-Verfahren nach Shamir wurde mit vielen Optionen
  implementiert.

- Zufallszahlen:
  - Pseudozufallszahlengeneratoren und statistische Analysen für
    Zufallsdaten (z.B. FIPS-140-1).
  - Der Secude-Zufallszahlengenerator bietet die Möglichkeit, Entropie
    über Mausbewegung und Tastatureingaben zu sammeln.
    Dies ist die Standardeinstellung für den ersten Aufruf des
    kryptographischen Zufallsgenerators, damit deutlich wird, dass man
    für gute Zufallszahlen einen zufälligen Input braucht. (xxx)
  - Eine 3-D-Visualisierung von großen Mengen an Zufallszahlen mit Hilfe
    der Volume-Rendering-Engine von OpenQVis.

- PKCS#12-Export und -Import von RSA- und DSA-PSEs und damit von den
  darin gespeicherten Schlüsseln.

- Die modernen Verfahren wurden gemäß den internationalen Standards
  implementiert (Referenzimplementierung).

- Die letzte Einstellung zu einem Verfahren (Parameter, Schlüssel oder
  Alphabet) wird Programm-intern aufbewahrt. Der Schlüssel kann pro
  Verfahren über das Schlüssel-einfügen-Symbol auch wieder abgerufen
  werden, was die Bedienung beim Testen und Probieren stark erleichtert.

- Zu jedem Fenster kann ein Dialog angezeigt werden, der alle
  wesentlichen Eigenschaften dieses Dokuments anzeigt.

- In allen klassischen Algorithmen, wo die Alphabete der zu bearbeitenden
  Texte eine Rolle spielen, wird das im zentralen Dialog "Textoptionen"
  eingestellte Alphabet benutzt.
  Damit wird die Transparenz und Bedienbarkeit deutlich verbessert:
  Um sofort bei der Schlüsseleingabe sichtbar zu machen, welche Verfahren
  darauf reagieren, enthält jede passende Schlüsseleingabe-Maske einen
  zusätzlichen Button "Textoptionen", der direkt zum Dialog "Textoptionen"
  führt (man muss also nicht mehr erst an der Stelle, wo man die Textoptionen
  am ehesten braucht, den Schlüsseleingabe-Dialog wieder schließen und
  über das Hauptmenü zu den Textoptionen gehen).
  Dieser Aufruf mit einem Klick auf den Button "Textoptionen" ist bspw.
  implementiert in den Schlüsseleingabe-Masken für Caesar, monoalphabetische
  Substitution, Vigenère, Skytale, Permutation und Homophone.

- CrypTool kann man ohne Administratorrechte ausführen.
  Verschiedene Benutzer können am gleichen PC jeweils verschiedene
  Einstellungen haben. Details siehe Kapitel 3.2 und 4.4.

- Die gleiche Menüstruktur ist konstant sichtbar: Einträge, die für
  bestimmte Dokumenttypen nicht ausführbar sind, werden ausgegraut.

- Das eigenständige Programm AES-Tool kann selbst-entpackende
  Programme erzeugen. Damit kann man eine beliebige Datei Passwort-geschützt
  mit AES verschlüsseln (das Passwort kann in ASCII oder direkt als
  Hexadezimal-Schlüssel eingegeben werden).
  Voller Funktionsumfang auch bei einem Aufruf von der Kommandozeile.
  Erzeugt man selbst-entpackende Archive, darf das Ergebnis nicht größer
  als 4 GB werden. Erzeugt man nur die verschlüsselten AES-Dateien
  kann das Original auch deutlich größer als 4 GB sein.

- Das eigenständige Lernprogramm "ZT" für die Mathematik hinter der
  asymmetrischen Kryptographie beschreibt ausführlich und interaktiv
  die elementare Zahlentheorie.

- Drei auf dem Chinesischen Restesatz beruhende Anwendungen:
  * Lösung von Systemen linearer modularer Kongruenzen am Beispiel
    einer Planetenkonstellation im Sonnensystem.
  * Veranschaulichung des Rechnens (Addieren, Subtrahieren, Multiplizieren)
    mit modularen Resten statt mit den (größeren) eigentlichen Zahlen.
  * Veranschaulichen des Shared-Secret-Verfahrens (entspricht der
    Analogie, dass man zum Öffnen eines Tresors z.B. drei beliebige
    von 5 Schlüsselinhabern braucht).

- Mit dem Dialog "Mersenne-Zahlen berechnen" können Sie sich in weniger
  als 1 Minute die mehrere Millionen langen größten Primzahlen erzeugen,
  die bisher im GIMPS-Projekt gefunden wurden.

- Mit dem Passwort-Qualitätsmesser (PQM) kann man die Widerstandsfähigkeit
  eines Passworts mit verschiedenen Verfahren und unter Vorgabe von
  Mindestanforderungen abschätzen.

- Mit dem Passwort-Entropie-Dialog können Sie Passworte erzeugen, die eine
  ähnlich hohe Sicherheit bieten wie zufällig erzeugte Binärschlüssel für
  symmetrische Verfahren einer vorgegebenen Bitlänge. Sie können dabei
  ebenfalls das für das Passwort verwendete Alphabet festlegen.

- Das Lern-Spiels "Der Zahlenhai" bringt Schülern den Umgang mit
  Teilern und Primfaktoren näher.

- Download-Seite https://www.cryptool.org/de/ct1-downloads
  Diese Webseite enthält die Hashwerte aller herunterladbaren CrypTool-
  Dateien: Damit kann man die Integrität der Dateien aus dem CrypTool-Paket,
  die sich auf dem Computer befinden, überprüfen.

- Umfangreiche Dokumentation (Onlinehilfe, Buch).
  Die Online-Hilfe ist im HTML-Format.
  Sie enthält Erläuterungen zur Bedienung und zu allen Verfahren, einen
  Überblick über die Historie der Kryptographie und die Einordnung in
  weitere Sachgebiete sowie Informationen für eine sinnvolle Verwendung
  von Kryptographie.

- Weltweite Nutzung in Schulen, Universitäten, Behörden und Firmen.



2.2. Informationen für Entwickler / Wo finden Sie die Sourcen
     --------------------------------------------------------

- Die Release-Sourcen (Tag "CrypTool_1_4_31") und die aktuellen Entwickler-
  Sourcen stehen direkt im Subversion-Repository zur Verfügung.
  Darauf kann jedermann lesend (ohne Angabe eines Passworts) zugreifen per
  svn checkout https://www.cryptool.org/svn/CrypTool/trunk/ --username anonymous


- Snapshot zur Anzahl von Dateien und zur Anzahl der Source-Code-Zeilen

  Einen Eindruck von der Größe des CT1-Projekts liefert die folgende, im
  Juli 2017 erstellte Statistik (anhand der Dateien für die Version
  1.4.31 Prefinal):

    FILE SUMMARY (Anzahl der Dateien anhand ihrer Dateinamenserweiterung)
    ------------
              4 .rc files
             36 .c files
            324 .cpp files
            378 .h files
             36 .java files
             14 .pl files
           1152 .html files
             47 .txt files
             47 .tex files
              4 .sage files
          2.042 TOTAL


    LINES OF CODE (LoC) SUMMARY
    ---------------------------
         85.625 MFC resource code (rc)
        286.487 C/C++ source code (c cpp h)
          9.795 Java source code (java)
          2.266 Perl code (pl)
         66.610 HTML code (html hpp)
          8.532 Text files (txt)
         61.545 LaTeX code (tex)
            825 Sage code (sage)
        521.685 TOTAL

    TOTAL: 521.685 Code-Zeilen (plus von 19 % gegenüber 437.772 bei CT 1.4.30)
    - In den TOTAL-Wert gehen nur Sourcen ein, die innerhalb des
      CrypTool-Projektes entwickelt wurden oder dem CT-Projekt gewidmet
      wurden.
      Die Sourcen anderer Open-Source-Projekte, die innerhalb von CrypTool
      benutzt werden (wie OpenSSL, NTL, Scintilla, Animal) werden nicht
      gezählt. Ebenso wenig werden automatisch erzeugte Dateien oder
      Wortlisten (Referenzdateien) gezählt.


- Details zum Compilieren, Linken und zur einheitlichen Entwicklung
  finden sich in den Sourcen in der Datei "readme-source.txt".

- Die Sourcen wurden mit der Microsoft Entwicklungsumgebung Visual Studio 2008
  Standard Edition compiliert.
  Anmerkungen zu den MS Entwicklungsumgebungs-Versionen:
  - Die Express-Edition von VS2008 reicht nicht aus, weil CT 1.4 noch die
    alte MFC-Klassenbibliothek für die GUI nutzt, die die Express-Edition
    im Gegensatz zur Standard-Edition nicht unterstützt.
  - Die Compilierung mit einer aktuelleren Microsoft-Entwicklungsumgebung
    wie Visual Studio 2010 Standard Edition (VC++ v9.0), VS2013 oder VS2015
    funktionierte an sich, aber leider waren dann etliche Grafiken auf
    UHD-Monitoren verzerrt (was beim VS2008 nicht so war).
    --> Wir fanden keinen Hinweis, wie man diese Anpassung in den neueren
        Entwicklungsumgebungen abstellt, ohne alle Grafiken neu zu machen ;-)
        Diese Anpassung wird wahrscheinlich durch die GUI-Einstellungen
        verursacht, die es Benutzern erlaubt, "Größe von Text, Apps und
        anderen Elementen" auf Werte ungleich 100 % zu setzen.

- Eine Komplett-Compilierung aller Versionen (7 Sprachen, jeweils Debug und
  Release) dauert auf einem modernen PC rund 2 h. (xxx)



2.3. Wo finden Sie weitere Überblicke zu CrypTool
     --------------------------------------------
Eine gute Übersicht, was CrypTool bietet, finden Sie auch
- in der Onlinehilfe (siehe "Startseite"),
- in der beigelegten PDF-Präsentation (Titel: "Kryptologie mit CrypTool"),
- mithilfe des Menübaums im Anhang A.1 des beigelegten CrypTool-Buchs,
- auf der Webseite des CrypTool-Portals
  (https://www.cryptool.org/de/ctp-dokumentation/funktionsumfang) unter
          - "Dokumentation" -> "CT-Funktionsumfang",
- auf der Webseite von CT1 (https://www.cryptool.org/de/cryptool1) unter
          - "Dokumentation" -> "Funktionen von CrypTool 1.4.3x", und
          - "Screenshots" -> "Screenshots".



2.4. Neuerungen in Version 1.4.20 / 1.4.21
     -------------------------------------
Dieses Kapitel listet die Erweiterungen und Bugfixes auf, die in
CrypTool 1.4.20 und 1.4.21 seit CrypTool 1.4.10 hinzugefügt wurden.

a) Entwickler-relevante Änderungen (eher Programm-technisch):

- Aufräumen des Source-Code, höhere Wiederverwendung.

- Update auf OpenSSL 0.9.8g, Animal 2.3.14 und NSIS 2.37.

- Automatisierter Konsistenzcheck in der Onlinehilfe (Verweis auf Menüs,
  Dialoge, Bilder, Querverlinkung).

- Eingabefelder gegen Fuzzy-Eingaben per Clipboard stabilisiert, um
  provozierte Abstürze zu vermeiden.


b) Änderungen in der Benutzer-Dokumentation / Web-Darstellung:

- Online-Hilfe: erweitert.

- Buch: Behebung kleinerer Fehler, Menübaum in Anhang A.1 der neuen
        CrypTool-Version angepasst.

- Aktualisierte und auf über 100 Seiten erweiterte Präsentation.

- Neue CrypTool-Webseite mit Joomla seit April 2008.


c) Funktionale Änderungen / Erweiterungen:

- Bugfixes:
  - Viele kleine Verbesserungen in den Masken:
    Benutzerführung; Refresh; Cursor korrekt auch nach Dialogwechsel;
    bei DH, Hill und Seitenkanalangriff einheitlich Häkchen für die Anzeige
    von Detaildialogen und die Erstellung von Logfiles.
  - AML-Datei für die DES-Animation mit Animal korrigiert (in der Matrix
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
  variable Alphabet für das Transpositions-Passwort nutzen (nicht mehr
  nur die 26 Großbuchstaben).

- Erweiterung der Brute-Force-Analyse symmetrischer Verfahren (Henk -- danke
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

Die Version 1.4.30 wurde zeitgleich in 5 Sprachen (Deutsch, Englisch,
Polnisch, Serbisch und Spanisch released).

a) Entwickler-relevante Änderungen (eher Programm-technisch):

- Aufräumen des Source-Code, höhere Wiederverwendung,
  Beseitigen vieler Warnungen.
  Z.B. wurde die Hill-Verschlüsselung samt GUI neu geschrieben. Dabei wurden
  rund 6000 Zeilen C++-Code eingespart und dennoch Funktionalität und
  Performance verbessert!

- Das Begrüßungsfenster wurde neu erstellt, so dass leichter die Texte
  verschiedener Sprachen darüber gelegt werden können.

- Nun mit VS2008 compiliert.

- Update der Bibliotheken und genutzten Fremdsoftware auf ff. Versionen:
  - Scintilla 1.7.7
  - cv act library v. 1.4.6 (unterstützt auch Windows Vista)
  - OpenSSL 0.9.8k
  - MPIR 1.3.1 (hergeleitet aus GMP-Version 4.2.1) statt GMP 4.1
  - APFLOAT 2.41
  - Animal 2.3.21.

- Quellcode und die Applikation CT1 stehen nun unter der Lizenz
  Apache 2.0 (siehe http://www.apache.org/licenses/LICENSE-2.0).


b) Änderungen in der Benutzer-Dokumentation / auf den Web-Seiten:

- Online-Hilfe: deutlich erweitert (z.B. sind nun bei allen Blockchiffren
                explizit die benutzten Modi und Padding-Varianten erläutert).

- CrypTool-Buch: Umfangreiche Überarbeitung:
                - Erweiterungen und Update auf aktuellen Stand,
                - Aufnahme von vielen SageMath-Programmbeispielen,
                  Auslieferung des SageMath-Codes als Datei,
                - Behebung kleinerer Fehler,
                - Menübaum in Anhang A.1 an neue CrypTool-Version angepasst,
                - Neues Deckblatt.

- Aktualisierte und auf über 110 Seiten erweiterte Präsentation.

- Von der CT-Webseite wird auf die Websites der Nachfolger-Versionen JCT
  und CT2 verwiesen, die schon die jeweils aktuelle, stabile Beta zum Download
  anbieten.

- Die folgenden zusätzlichen, ebenfalls zur CrypTool-Familie gehörenden
  Webseiten gingen live:
  - www.cryptool-online.org  "CrypTool-Online" führt verschiedene
                              Kryptoverfahren direkt im Browser aus.
  - www.m.cryptool.org       "CrypTool-Mobil" führt verschiedene
                              Kryptoverfahren in Smartphones aus.
                              Das kann fürs Geocachen nützlich sein.
  - www.cryptoportal.org     "Lehrerportal" mit Unterrichtsmaterial und
                              Links
  - https://www.mysterytwisterc3.org  Ein internationaler Krypto-Wettbewerb
                                      mit Aufgaben verschiedener
                                      Schwierigkeitsgrade.

- Ein kurzes CrypTool-Video auf YouTube:
   - Deutsch:  http://www.youtube.com/watch?v=of0C9Lx0vGs
   - Englisch: http://www.youtube.com/watch?v=bLJKuW4UOuE
   - Spanisch: http://www.youtube.com/watch?v=pTFdklPQiL4

- Auf der CrypTool-Webseite gibt es unter Präsentationen nun eine interaktive
  Einführung in die Grundlagen von RSA (als PPT und als Flash):
  https://www.cryptool.org/de/ctp-dokumentation/presentations


c) Neue Funktionalität / Bedienung:

- Bugfixes  --> Danke an die vielen aufmerksamen Benutzer!
   - Fehler in AKS behoben, der mit den Eingaben 2^8+1 und 2^16+1 auftrat.
     Die korrekte Fassung von AKS braucht länger.
   - Fehler in AKS behoben, der CT abstürzen ließ, wenn man die Zeitdauer für
     sehr große Zahlen abschätzen ließ (Dauer über 1 Jahr, Stack-Überlauf
     in GMP). Dazu wurde MPIR anstatt einer älteren Windows-Version der
     GMP-Bibliothek eingesetzt.
   - Fehler behoben bei weiteren Primzahltests, wenn Primfaktoren < 39
     vorkamen.
   - In der Maske "Schlüssel aus Passwort generieren (nach PKSC #5)" werden
     nun auch die Hashwerte mit führenden Nullen korrekt angezeigt.
   - Die ECC-AES-Hybrid-Ver-/Entschlüsselung läuft nun dank einer neuen
     cv act lib von cryptovision auch unter Windows Vista.
     Außerdem kommt hier nun beim Versuch, einen nicht verschlüsselten Text
     zu entschlüsseln, eine korrekte Fehlermeldung.
   - DH-Demo: Wenn man automatisch erzeugte Generatoren danach änderte (z.B.
     die Ziffer 2 anfügen) kam es in früheren Versionen zum Absturz.
     Ist behoben.
   - Seitenkanalangriff auf das Hybridverschlüsselungsprotokoll
     (Textbook-RSA):
     Wenn man mit RSA-Modulen arbeitete, die länger als 1024 Bit waren, kam es
     zum Absturz, wenn man den Angriffszyklus startete.
     Ist behoben.
   - Die auf dem CRT beruhende Secret-Sharing-Anwendung verbietet nun, dass
     n=k (denn so wären alle Shareholder notwendig). Ohne diese Einschränkung
     macht der Algorithmus das ganze Geheimnis dem ersten Teilnehmer bekannt.
   - RSA-Demo: Ein eingegebener Wert für e wird auch nach Aufruf des
     Optionen-Dialogs beibehalten.
   - Korrektur der ECC-Demo:
     - Die Vorgängerversion lieferte über der Gruppe F(p) bei der
       Punktaddition unter bestimmten Umständen einen Punkt außerhalb der
       Kurve.
     - Die Koordinaten der Punkte, die dynamisch in der Nähe des Mauszeigers
       erscheinen, sind nun auch am rechten Rand ganz sichtbar.
     - Der Punkt im Unendlichen wird zur Gesamtzahl der Punkte hinzugezählt.
     - Das Log-Fenster ist nun amodal, größenveränderlich und der Inhalt
       ist übersichtlicher gestaltet.
     - Die Slider sind nun breiter, so dass man die Parameter besser justieren
       kann.
     - Die Versionsnummer wurde auf 1.1.1 erhöht und wird nun im Titel
       angezeigt.
   - Korrektur bei DESX/DESXL: Nun wird die effektive Bitlänge in den
     Dialogen zur Verschlüsselung und zur Brute-Force-Analyse angezeigt.
   - Korrektur bei der DESX/DESXL-Brute-Force-Analyse, die Schlüssel überging,
     wenn die obersten 128 Bit des Schlüssels durchsucht wurden (das Parity-
     Bit wird bei der Brute-Force-Analyse aus Performancegründen ignoriert;
     dies geht aber nur beim DES-Key-Teil des Gesamtschlüssels).
   - Beim Angriff auf den Hashwert einer elektronischen Signatur wurde bisher
     die benötigte Schrittzahl falsch ausgegeben (immer ca. 4,x*10^18).
   - Absturz gefixt, der auftrat, wenn man in den Textoptionen als Alphabet
     die Großbuchstaben plus die kleinen Umlaute definierte und dann die
     Caesar-Verschlüsselung aufrief.
   - Nun kann man in Feldern für Hexeingaben auch Hexfolgen aus dem Clipboard
     korrekt eingeben (wenn markiert, wird nur da eingefügt).
   - Der in der Textanzeige eingestellte Font wird beibehalten, auch wenn man
     zwischendurch in die Hex-Ansicht wechselt.
   - Konflikte mit den Zertifikats-Seriennummern: Bisher wurden die
     Seriennummern fortlaufend vergeben und beim Importieren eines Zertifikats
     in den Schlüsselspeicher wurde nicht geprüft, ob diese Nummer schon
     vergeben ist. Dies konnte dazu führen, dass beim Validieren das falsche
     Zertifikat benutzt wurde.
     Beides ist behoben: Die Nummern werden zufällig erzeugt und beim Import
     weiterer Zertifikate werden diejenigen mit Nummern, die schon erzeugt
     wurden, abgelehnt.
   - Die Ciphertext-Only-Analyse von XOR-Chiffraten ermittelte eine falsche
     Schlüssellänge, obwohl die angezeigte Autokorrelation korrekt war.
     Nun wird die richtige Schlüssellänge angezeigt und benutzt.
   - Korrektur etlicher Rechtschreibfehler in der CrypTool-Onlinehilfe, den
     Ressourcen von CrypTool, AES-Tool und Zahlenhai, und den Animal
     AML-Dateien.


- CrypTool merkt sich nun die Position und Größe des Hauptfensters und nutzt
  dies beim Neustart.

- Benutzerfreundlichkeit: Insbesondere für neue Benutzer, die die Onlinehilfe
  nicht aufriefen, aber nach der Bedeutung der Ikone fragten, hat die Ikone
  zum Einfügen von Schlüsseln aus dem internen Schlüsselspeicher in mehreren
  modalen Dialogboxen nun einen Tool-Tipp ("Schlüssel einfügen").

- Viele kleine Verbesserungen in den Masken, z.B. Elapsed-Time-Anzeige beim
  AKS-Test; der Text in der About-Box kann markiert und kopiert werden;
  sofortige Anzeige der Zeit und der Anzahl der bisherigen Faktoren bei
  der Faktorisierung; im Menü zur Analyse von Ciphertext-Only-Verfahren
  steht nun "XOR / Vernam" statt nur "XOR".

- Die Mitwirkenden und die übersetzenden Organisationen werden nun in
  eigenen Dialogen aufgeführt (aufrufbar aus dem neuen About-Dialog).

- Umfangreiche Erweiterungen der Onlinehilfe.

- Auch externe PDFs können nun direkt aus der Onlinehilfe aufgerufen werden.

- Im Tutorial zu XOR und Psion in der Präsentation gab es bisher nur eine
  verschlüsselte Datei (erstellt aus einem deutschen Klartext). Nun gibt es
  auch eine Datei mit einem verschlüsselten englischen Klartext:
  psion-en-enc.hex


- Bei allen DES-basierten Verfahren wird nun sowohl die effektiv genutzte als
  auch die einzugebende Schlüssellänge angezeigt.

- Alle acht verfügbaren Hashverfahren werden nun angeboten in den Masken für:
  - Schlüssel aus Passwort generieren (nach PKSC #5),
  - Generieren eines Hashed Message Authentication Code (HMAC),
  - Generieren des Hashwertes einer Datei, und in der
  - Hash-Demo.

- Der HMAC-Dialog wurde neu entworfen.

- Im HMAC-Dialog sind die Bezeichnungen der Literatur angepasst und in der
  Onlinehilfe sind nun die entsprechenden Quellen angegeben.
  Variante 5 der HMAC-Beispiel-Konstruktionen entspricht nun genau dem
  RFC 2104.
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

- Beim PKCS #5-Dialog können nun bis zu 100.000 Iterationen eingestellt
  werden.
  Außerdem werden mehr Hashverfahren unterstützt, als der ursprüngliche
  Standard vorsieht.

- Erweiterung der Brute-Force-Analyse symmetrischer Verfahren:
  Eine weitere Spalte wurde ergänzt, die den Schlüssel zeigt, der zu
  den Werten der bisherigen Spalten Entropie des Klartextes, Klartext
  und Geheimtext passt.


- Wenn sich im Dialog Primzahltest ergibt, dass die zu testende Zahl
  NICHT prim ist, kann per Button direkt zum Faktorisierungsdialog
  gesprungen werden.

- Bis 1.4.21 wurden mit der Maske "Primzahlen generieren" zwei zufällig
  gewählte Primzahl innerhalb eines vordefinierten Bereichs erzeugt.
  Nun kann man damit auch alle Primzahlen innerhalb eines vorgegebenen
  Bereiches ausgeben (Primzahlmenge generieren).

- Bei Diffie-Hellman werden die Primzahlen und der Generator nun
  gemäß Standards für sichere Generatoren erzeugt.

- Neu hinzugekommen ist die schnelle Berechnung von Ganzzahl-Potenzen.
  Für diese Berechnung wird die Bibliothek APFLOAT benutzt. Damit kann man
  alle Stellen der aktuellen Primzahlrekorde (Mersenne-Zahlen) ausgeben.
  In diesem Dialog werden bei der Eingabe von Ganzzahlen die Tausendertrenner
  (Punkte) automatisch gesetzt. Das ist bei evtl. sehr langen Exponenten
  Benutzer-freundlicher.


- Die klassischen Transpositions-Chiffren Skytale und Gartenzaun hinzugefügt
  (angeboten innerhalb eines Dialogs) incl. Schlüssel anzeigen und
  Schlüssel einfügen per Ikone.

- Solitaire-Verschlüsselung: Maske verbessert, Anzeige von "A" und "B" für die
  Jocker statt "53" und "54" (wie im Original), Message nicht mehr auf 64 kB
  beschränkt, erzeugte Schlüsselströme können gespeichert werden.
  Die manuelle Solitaire-Analyse (Rekonstruktion des Initialdecks) wurde
  verbessert.

- Die Permutationsverschlüsselung kann nun auch auf Hexdateien angewandt
  werden.

- Die Art, wie aus einem Schlüsselwort eine Permutation erzeugt wird, ist
  nun bei allen Verfahren (Doppelwürfel, ADFGVX) gleich.

- Die Hill-Verschlüsselung bietet nun weitere Optionen, und alle Schlüssel-
  parameter (Hill-Optionen) werden mit im Schlüsselspeicher (Registry)
  abgelegt.

- Die Playfair-Verschlüsselung bietet nun weitere Optionen (Vorformatierung;
  Unterscheidung, ob Trenner nur innerhalb von Paaren gleicher Buchstaben
  oder immer beim Aufeinandertreffen gleicher Buchstaben eingefügt werden).
  Dies wirkt sich z.B. bei Worten wie "BALLOON" aus.

- Alle spezifischen Optionen befinden sich nun in den Dialogen der zugehörigen
  Methoden. Somit konnten wir den Menüeintrag "Weitere Optionen" entfernen.

- Die Checkbox "Sonderzeichen" in der Dialogbox "Textoptionen" bietet nun
  standardmäßig mehr Sonderzeichen an. Maximal kann das Alphabet für die
  klassischen Verfahren nun 98 Zeichen umfassen.

- Das in den Textoptionen eingestellte Alphabet wirkt sich nun auf fast alle
  klassischen Chiffren aus: Deshalb haben alle angepassten Verfahren nun einen
  Button, um aus der Schlüsseleingabe-Maske direkt zu den Textoptionen zu
  springen.

  Der Textoptionen-Button ist vorhanden bei
  - den klassischen Substitutions-Verfahren
        (Caesar, Vigenère, monoalphabetische Substitution, Hill) und bei
  - den klassischen Transpositions-Verfahren
        (Skytale, Transpositions-Teil von ADFGVX).

  Der Textoptionen-Button ist absichtlich nicht verfügbar in den Schlüssel-
  eingabe-Dialogen der folgenden Verschlüsselungsverfahren:
  - Substitutions-Teil von ADFGVX (Algorithmus erfordert ein festes Alphabet)
  - Playfair (der Algorithmus legt über die Matrix auch das Alphabet fest)
  - Permutation (alle Daten werden permutiert; wenn gewünscht, kann das
                 Dokument von Ihnen selbst vorab vorformatiert werden -- mit
                 dem Menü "Ansicht \ Textdokument formatieren")
  - Solitaire (der Algorithmus erfordert ein festes Alphabet; alle Buchstaben
               werden in die 26 Großbuchstaben verwandelt und alle anderen
               Zeichen gelöscht).

  Diese Neuerung kam zustande aufgrund vieler Anfragen, die insbesondere
  um Erweiterung des Alphabets für die monoalphabetische Substitution baten.


- Eine Visualisierung der Abläufe bei sicherer E-Mail kam hinzu: Der Benutzer
  kann Daten eingeben, die signiert oder verschlüsselt werden mit Hilfe des
  S/MIME-Protokolls.

- Eine weitere Visualisierung des AES-Algorithmus kam hinzu:
  Die Flussvisualisierung veranschaulicht die Veränderung der Bits
  in jeder Runde (compiliert mit Java 1.5).


- Das Lernprogramm/Lernspiel "Zahlenhai" (in der Version 1.2.1) wurde
  korrigiert und die Onlinehilfe aktualisiert und erweitert.
  Ausgabe/Anzeige der optionalen Werte:
  - Bisher konnte man die optionalen Werte auf zwei Arten anzeigen:
    - Bis n=158 waren sie abgespeichert.
    - Für beliebige Werte konnten sie mit einem sehr langsamen
      Brute-Force-Verfahren berechnet werden.
  - Nun können diese mit einem Backtracking-Verfahren deutlich schneller
    berechnet werden (39 Zahlen in ca. 1 Minute; 40 Zahlen in ca. 5 Minuten).
  - Noch viel schneller sind heuristische Methoden, wie sie in JCT
    implementiert sind. Diese finden meist nicht den optimalen Wert,
    aber einen sehr guten Wert.
    Die besten bekannten Werte bis n=404 werden nun auch im Spiel
    mitgeliefert.
    Alle bekannten Werte können in einer Tabelle angezeigt werden.
  - Wenn man die optimalen Werte berechnet, was sehr lange dauern kann,
    kann der Zahlenhai nun auf bisher schon berechnete Zwischenergebnisse
    aufsetzen.
  - Weitere Hintergrundbilder wurden hinzugefügt.

- Das Lernprogramm "Zahlentheorie" wurde etwas korrigiert und liegt nun
  in der Version vom 2009-11-08 bei.


- Für die einfache Spaltentransposition ist eine Known-Plaintext-Analyse
  zum Finden des Transpositions-Schlüssels neu hinzugekommen.
  Diese Known-Plaintext-Analyse wurde -- zusammen mit der bisherigen
  Known-Plaintext-Analyse für Hill -- besser integriert.
  Alle gefundenen Schlüssel der Transpositions-Analyse werden in einer
  Tabelle angezeigt.

- Weitere Ciphertext-Only-Analyse für Vigenère (nach Schrödel): Diese
  ist effizient für sehr kurze Chiffrate, sofern das Passwort aus einem
  Wörterbuch stammt.



2.6. Neuerungen in Version 1.4.31
     ----------------------------
Dieses Kapitel listet die Erweiterungen und die Bugfixes auf, die in
CrypTool 1.4.31 seit CrypTool 1.4.30 hinzugefügt wurden.

Die Version 1.4.31 wird zeitgleich in 6 von 7 Sprachen released.
Griechisch folgt.

a) Entwickler-relevante Änderungen (eher Programm-technisch):

- Update der Bibliotheken und der genutzten Fremdsoftware auf ff. Versionen:
  - Scintilla (3.7.0 postponed to CT 1.5; weiterhin modifizierte 1.7.7
    benutzt)
  - compilerabhängig: cv act library 1.4.6 mit VS2008, 1.4.18 mit VS2010
  - OpenSSL 1.0.1 (xxx)
  - MPIR 1.3.1 (hergeleitet aus GMP-Version 4.2.1) statt GMP 4.1
      ??????  2.5.1    (postponed to CT 1.5) (xxx)
  - Miracl 4.4.3  -->  5.5.4 (postponed to CT 1.5) (xxx)
  - NTL 5.5.2  --> 10.3 (thread-safe und mit Exception-Handling, braucht
                        einen C++11-Compiler)   (postponed to CT 1.5) (xxx)
  - Animal 2.4.9
  - Ersatz der Secude-Bibliothek (dies auf CT 1.5 verschoben, da sie Probleme
    nach der Compilation mit VS2010 (nicht mit VS2008) hatte) (xxx)

- Das CT1-Installationsprogramm ist nun signiert mit einem Zertifikat, das von
  einer CA herausgegeben wird, die im Windows-Schlüsselspeicher enthalten ist.
  Dies vermeidet, dass Windows dem Benutzer unnötige Warnungen über
  nicht-signierte Software angezeigt.

- Das Installationsprogramm füllt nun das Herausgeber-Feld, so dass in der
  Windows-Übersicht der installierten Software nun "CrypTool-Team" angezeigt
  wird.
  
- Das Release von CT 1.4.31 wird weiterhin mit VS2008 kompiliert (siehe oben).
  Ab CT 1.5 wird mit VS 2017 übersetzt, oder CT1 gleich durch QCT ersetzt.


b) Änderungen in der Benutzer-Dokumentation / auf den Web-Seiten:

- Online-Hilfe: aktualisiert an etlichen Stellen (bspw. bc) und Korrektur
                von über 70 internen und externen Links.

- CrypTool-Buch: - Edition 12 ist ein großes Update, viele Korrekturen und
                   Ergänzungen
                 - Zwei weitere Kapitel: zu Bitblock- und Bitstrom-
                   Verschlüsselung und mit einer Studie über aktuelle
                   akademische Resultate für das Lösen diskreter Logarithmen
                   und zur Faktorisierung
                 - Aufnahme weiterer SageMath-Programmbeispiele
                   (zu Primitivwurzeln und RSA-Fixpunkten)
                 - Anhänge zu den Funktionsübersichten auch für CT2 und
                   JCT  (xxx)
                 - In den Fußnoten nun auch die Menüpfade zu CT2 und JCT.

- Präsentation zu CT1 aktualisiert (März 2017)
  Die Informationen zum Gesamtprojekt und zu den beiden anderen CT-Projekten
  (CT2, JCT) liegen nun in eigenständigen Präsentationen.

- Am 18. Januar 2012 wurde die neue CrypTool-Webseite (CTP) freigegeben, die
  die 5 Unterprojekte des CT-Projektes gleichwertig darstellt.
  Dazu gehört auch CT1. Seitdem wurde die Seite regelmäßig geupdated.


c) Neue Funktionalität / einheitlichere Bedienung / Fehlerkorrekturen:

- Zwei weitere Sprachen hinzugefügt: Griechisch und Französisch.
  Das Griechische Release wird aufgrund von Fontproblemen erst später
  ausgeliefert.
- Installation und Benutzung ohne Administratorrechte: Nun braucht nicht nur
  das Programm keine Administrator-Rechte mehr, sondern auch das
  Installationsprogramm kann von einem normalen Nutzer ausgeführt werden.
- Unter den zahlentheoretischen Funktionen wurde der Spezialfall der
  Generic t-adic NAF Schlüsselerzeuger hinzugefügt. Dialogfenster breiter.
  Umschreiben des Generators, da sein Pattern bei einigen Virenscannern
  zu False-Positive Falsch-Meldungen führte, die diese dann bei der
  Setup-Installationsdatei der Beta meldeten.
- Textfenster haben nun einen Kontextmenü-Eintrag, um zur Hexanzeige
  umzuschalten, und umgekehrt.
- Viele kleine Verbesserungen in Dialogfenstern (z.B. "Angriff auf stereotype
  Nachrichten").
- RSA-Demo-Dialog erhielt einige optische Änderungen aufgrund des didaktischen
  Feedbacks, das wir erhielten. (xxx)
- Transpositions-Verschlüsselung: Der Schlüsseleingabe-Dialog hat nun auch den
  Button "Textoptionen".
  Ebenso hinzugefügt wurde dieser Button in der Analyse der maS.
- Monoalphabetische Substitution (maS): Hier gibt es nun im Schlüsseleingabe-
  Dialog einen weiteren Parameter, mit dem man die Startposition (Offset) für
  das Passwort festlegen kann. Bisher wurde das Passwort immer an den Anfang
  des Geheimtext-Alphabets gestellt.
- Die Analyse für die Substitutions-Chiffre wird in 2 Varianten angeboten.
  Variante 2 verwendet eine Liste häufiger Wörter, die der User bisher nicht
  sehen oder ändern konnte. Beides ist nun möglich. (xxx)
- Die ADFGVX-Analyse nutzt nun zur Bestimmung der Substitutionsmatrix auch
  die Häufigkeitsverteilung des im Textoptionen-Dialog eingestellten
  Referenztextes.
  Außerdem kann man entscheiden, ob auch die Ziffern in die Häufigkeits-
  aufstellung mit aufgenommen werden (Groß-Kleinschreibung und Sonderzeichen
  sind beim ADFGVX-Verfahren ausgeschlossen). Der Einleitungstext der Analyse
  wurde an das aktuelle Verhalten angepasst.
- Die Felder zur Anzeige des Hashwertes einer Datei können nur auch 256 Bit
  lange Hashwerte ohne Scrollen anzeigen.
- Zahlenhai 1.2.4:
  - Einige Funktionen nun nicht nur über Tastenkombinationen sondern
    auch über Buttons erreichbar.
  - Onlinehilfe korrigiert, insbesondere einige veraltete Links.
- AES-Tool 2.7:
  - Fehler behoben, der beim Eingeben von zu langen hexadezimalen Schlüsseln
    auftrat.
  - Erlaubt nun die Schlüsseleingabe als normalen ASCII-String und
    das sichere Löschen der Originaldatei nach dem Verschlüsseln.

- Wenn in der Registry Positions- und Größenangaben liegen, die das CT-Fenster
  außerhalb des Bildschirms positionieren, fängt CT das beim Start selbst ab.
  Das "Verschwinden" der Fenster kam vermehrt unter Win 7 mit CT 1.4.30 vor,
  wenn Betriebssystem-Updates eingespielt oder Monitorauflösungen geändert
  wurden.
- Im Textoptionen-Dialog wird nun die Referenzdatei für Analysen initial
  so gesetzt, dass sie zur jeweiligen Sprache passt und verschiedene
  Sprachversionen von CT1 auch nebeneinander installiert sein können.

- DES-Animal-Animation: Einige Fehler in den Schritten 357-424 und
  insbesondere in der Pre-Output-Matrix (64 bit) wurden beseitigt.
  Danke an Vasilis. Zusätzlich wurde die entsprechende Online-Hilfe erweitert.
- Dialog zur Eingabe von Hex-Schlüsseln: Bisher funktionierte das Einfügen per
  Strg-V korrekt; per Kontextmenü -> Paste aber nicht. Nun tut beides korrekt. 
- Bei SHA256 / SHA512 wurde bisher die falsche Funktion aufgerufen.
  Dies betraf auch den Dialog "Generieren von HMACs".
- Der Aufruf von bc innerhalb der Zahlentheorie-Tutorials funktioniert nun
  auch unter Windows. Sie können bc auch direkt im BC-Unterverzeichnis
  aufrufen.
  Beispieleingaben: 3*5 // 5+3^2 // a=10; a+2; b=a; b+7 // sqrt(4.5) //
    define d (n) { return (2*n); }; d(5) // l(100)/l(10) # Natural log //
    quit // Beispiel einer Summenfunktion per For-Schleife:
    sum=0; for(i=16;i>=0;i--)sum+=32*(256^i); sum
  Eine ausführliche Erläuterung zu bc findet sich auch in der CT1-Onlinehilfe.

- Playfair mit einer 6*6-Matrix konvertiert nun nicht mehr fälschlicherweise
  "J" zu "I".
- Scilexer.dll graut Nicht-Alphabet-Zeichen wieder korrekt aus.
  Siehe z.B. Menü Ansicht --> Alphabet oder den Hill-Analysedialog.
- Einen kleinen Fehler im Homophonen-Dialog korrigiert, wo initial ein
  falscher Index angezeigt wurde.
- Den Dialog zu Solitaire-Verschlüsselung und Solitaire-Analyse verbessert,
  und die entsprechende Onlinehilfe korrigiert.
- Den Dialog "Angriff auf stereotype Nachrichten" stabiler gemacht, und ein
  paar Layout-Fehler behoben.
- Die Berechnung im Dialog "Mersenne-Zahlen berechnen" robuster gemacht,
  indem eine ini-Datei für die apfloat-Bibliothek benutzt wird.
  Tausendertrenner (Punkte) werden nun auch für das Feld "Ergebnislänge"
  gesetzt. Für das Feld Ergebnis werden weiterhin keine Tausendertrenner
  angezeigt, denn deren Berechnung und Anzeige in einem MFC-Control dauert
  zu lange.

- Danke an die vielen aufmerksamen Benutzer, die uns auf Bugs und 
  Inkonsistenzen aufmerksam machten.





3. Beschränkungen und Voraussetzungen
   ----------------------------------

3.1. Anwendungsbereich dieser Lern-, Trainings- und Awareness-Software
     -----------------------------------------------------------------
CrypTool dient vor allem Ausbildungs- und Awareness-Zwecken. Man soll
es ohne vorherige Konfiguration sofort benutzen können.

Das Entwicklungsziel von CrypTool 1 war also nicht, dass damit produktiv
verschlüsselt wird oder dass damit eine CA (Certification Authority)
betrieben wird -- auch wenn die Funktionen korrekt in CrypTool
implementiert sind.

Beispielsweise steht -- im Unterschied zu produktiven CA-Applikationen --
das CA-Schlüsselpaar fest in der Software (Source und Binary) und es
ist geschützt mit einer ebenfalls bewusst nur sehr einfachen PIN für die
CA-PSE (Personal Security Environment).

Der Rootschlüssel der in CrypTool 1.4.31 eingebauten CA hat eine Länge
von 2048 Bit und ist 20 Jahre gültig (06.07.2006 - 06.07.2026).
Zertifikate, die mit dem alten Rootkey aus früheren CrypTool-Versionen
(1.3.05 und älter) ausgestellt wurden, können nicht in Version 1.4.31
importiert werden.

Beachten Sie also beim Umgang mit Zertifikaten, dass jedes CrypTool-
Programm eine Root-CA mit demselben Schlüsselpaar beinhaltet, mit
der die im Programm erzeugten User-Zertifikate signiert werden.
D.h. jeder (!), der CrypTool einsetzt, kann User-Zertifikate mit
dieser eingebauten CA signieren.

Professionelle PKI-Software wie z.B. die OpenXPKI, die Entrust-CA oder die
Microsoft-CA managen zusätzlich den ganzen Lebenszyklus von Zertifikaten,
bieten CRL-Handling, sorgen für eindeutige Seriennummern und nutzen
definierte Registrierungsprozesse.

In JCT sind die Prozesse einer PKI visualisiert.

Nichtsdestotrotz sind die in CrypTool 1 vorhandenen modernen Krypto-Verfahren
entsprechend den internationalen Standards implementiert und genauso "gut"
wie in kommerziellen Anwendungen.


3.2. Win32-Umgebung, Rechte bei Installation und Betrieb, Java-Runtime
     -----------------------------------------------------------------
CT1 v1.4.31 ist geschrieben für das Betriebssystem Windows 8 und 10.
CT1 erfordert eine Win32-Umgebung. Diese ist auch unter 64-Bit Windows
vorhanden.

Einige Funktionen wie Animal, ECC-Demo, ... [siehe Kapitel 1.2, Teil (3)]
erfordern zusätzlich eine Java Runtime-Umgebung JRE (Version >= 1.7).

Die minimale Rechnerausstattung liegt bei 300 MHz CPU, 256 MByte RAM,
200 MByte Festplattenplatz (das sind relativ geringe Anforderungen).

Verschiedene Sprachversionen von CT1 kann man parallel auf einem Rechner
benutzen, wenn man sie in unterschiedlichen Verzeichnissen installiert.

Verschiedene Benutzer können am gleichen PC jeweils unterschiedliche
Einstellungen haben (da persistente Einstellungen im Nutzer-spezifischen
Teil der Registry abgelegt werden).

Ausführen von CT1:
 - CT1 kann man ohne Administratorrechte ausführen.
 - Erläuterung:
   Bei der Benutzung braucht man Schreibrechte für:
    - Dateien im CrypTool-Verzeichnis PSE (für das PKI-Schlüsselmanagement),
    - Dateien im Nutzer-spezifischen TEMP-Verzeichnis (zur Ablage temporärer
      Dateien),
    - Einstellungen im Benutzer-spezifischen Teil der Registry.

Installation von CT1:
 - Auch für die Installation braucht man dazu keine Administratorrechte.
 - Erläuterung:
   Bei der Installation werden persistente Daten an ff. Stellen abgelegt,
   für die der Installierende Schreibrechte haben muss:
    - für das CrypTool-Verzeichnis,
    - für den Benutzer-spezifischen Bereich der Windows-Registry.


Anmerkung 1 -- Details zu den Zugriffsrechten:
a) Programm-Verzeichnis:
   Für einen erfolgreichen Installationsvorgang muss das vom Benutzer
   gewählte Installationsverzeichnis während der Installation beschreibbar
   sein.
   Für die zwei Unterverzeichnisse des Installationsverzeichnisses ("pse"
   und "examples") erhalten alle Benutzter der Gruppe "Users" Schreibrechte.

b) Windows-Registry:
   Um die Datei-Endung .aes für das Programm AES-Tool zu reservieren, muss
   der folgende Teil der Registry während der Installation beschreibbar sein:
   HKEY_CLASSES_ROOT
   HKEY_CLASSES_ROOT\Applications

   CT1 wird in der Liste der installierten Anwendungen (System -> Software)
   nur aufgeführt, wenn der folgende Registry-Eintrag beschreibbar ist:
   HKEY_LOCAL_MACHINE\Software\Microsoft\Windows\CurrentVersion\Uninstall

c) Startmenü:
   CT1 wird im Startmenü für alle Benutzer eingetragen, wenn das
   folgende Verzeichnis während der Installation beschreibbar ist:
   %allusersprofile%\Startmenü\Programme
   Wenn dieses Verzeichnis nicht beschreibbar ist, wird CT1 eingetragen unter:
   %userprofile%\Startmenü\Programs.


Anmerkung 2:
Event: Die CT1-Anwendung stoppt mit der Meldung "Could not create
       temporary file".

CT1 versucht tempräre Dateien in eines der folgenden Verzeichnisse zu
schreiben:
 1. das in der lokalen Variable TEMP 
 2. wenn TEMP nicht gesetzt ist: das der lokalen Variable TMP 
 3. wenn beide Variables, TEMP und TMP, nicht gesetzt sind: CT1 versucht es
    in das aktuelle Verzeichnis zu schreiben.

Bitte prüfen Sie die Zugriffsrechte für die Pfade, auf die die lokalen
Variablen zeigen. Falls sowohl %TEMP% und %TMP% nicht gesetzt sind, setzen
Sie diese Umgebungsvariablen auf einen passenden Pfad. Falls diese gesetzt
sind, prüfen Sie bitte, dass Sie die Rechte haben, dort Dateien und
Verzeichnisse zu schreiben. 


Anmerkung 3:
Wo das TEMP-Verzeichnis von Windows liegt, kann man sehen, wenn man im
Windows-Explorer %TEMP% eingibt. Den Wert kann man auch ansehen und anpassen
per "System Information" --> "Software Environment"
--> "Environment Variables". Oder auf der Kommandozeile.



3.3. Interaktive Online-Hilfe unter Windows XP
     -----------------------------------------
Bei CT1 kann man zu jedem selektierten Menüeintrag mit der F1-Taste
Hilfe anfordern.

- Für Endmenü-Einträge klappte das immer direkt.

- Für Menü-Einträge, die selbst weitere Untermenüs haben, funktioniert es nur,
  wenn das Untermenü nicht aufgeklappt ist (vor Windows XP war dies
  unabhängig davon, ob das Untermenü aufgeklappt war oder nicht).

  Workaround, um ein aufgeklapptes Untermenü zu unterdrücken
  (anhand eines Beispiels):
  Markieren Sie den Menüeintrag "Einzelverfahren \ RSA-Kryptosystem":
  Wenn das Untermenü zu "RSA-Kryptosystem" aufgeklappt ist und Sie die
  Hilfe zum Menüeintrag "RSA-Kryptosystem" selbst haben wollen,
  müssen Sie erst das Untermenü von "RSA-Kryptosystem" mit Escape (Esc)
  oder der Links-Pfeiltaste wieder einklappen.


3.4. Unterstützung verschiedener Sprachen
     ------------------------------------
Programm, Hilfesystem und Dokumentation sind mehrsprachig ausgelegt.

Für jede unterstützte Sprache gibt es bei CrypTool 1.4.31 ein eigenes
Installationsprogramm (Setup).


3.5. Einschränkungen / Features / Tipps
     ----------------------------------
- Zur Demonstration des RSA-Kryptosystem und zur Faktorisierung von
  Zahlen greift CrypTool auf die Langzahlarithmetik der Bibliothek
  Miracl zu. Die Bitlänge der Zahlen wurde in der CrypTool-Anwendung
  bei RSA auf 8192 beschränkt.

- Von Binärdateien werden "nur" knapp die ersten 2 GB in den
  Hex-Editor geladen (< 0x7ffff000 = 2.147.479.552 Bytes).

  Textdateien können dagegen in unbeschränkter Größe vom Editor geladen
  werden (sofern die Rechnerressourcen reichen).

- Beim Lesen und Speichern von Textdateien wird der Zeilenumbruch immer
  als CR/NL (wie unter Windows üblich) dargestellt. Das bedeutet,
  dass Dokumente, die aus Unix kommen und deshalb den Zeilenumbruch nur
  mit dem Zeichen LF kennzeichnen, länger werden [LF wird in CR/NL
  umgewandelt]. Eine Signaturprüfung kann dadurch schief gehen.

- Textfenster in Dialogen werden mit einem von zwei unterschiedlichen
  Editor-Controls erstellt. Diese haben ein unterschiedliches Verhalten
  beim Drücken der Enter-Taste:
  a) Scintilla-Editor: Enter bewirkt das Hinzufügen von CR/NL und der
                       Cursor steht in der nächsten Zeile.
  b) Standard MFC-Editor: Mit Enter wird der Texteditor verlassen und
                          es wird versucht, den OK-Button auszulösen.

- Darstellung von mathematischen Zeichen in der HTML-Hilfe:
  Die Microsoft HTML-Hilfe ruft den eingestellten Microsoft Internet
  Explorer (IE) auf. Version IE 6 hat manchmal Probleme, mathematische
  Zeichen wie die Gauß-Klammer darzustellen.
  Wenn bei Ihnen der IE7 voreingestellt ist, funktioniert es korrekt.
  Die zugrunde liegenden, in das CHM-File eingebundenen HTML-Dateien
  werden von IE7 und Firefox 1.5 oder höher korrekt dargestellt.
  Die Gauß-Klammer wird in dem Onlinehilfe-Kapitel zum Modulo-Operator
  als Symbol für die nächstniedrigere ganze Zahl verwendet.

- Aus Performancegründen wurde festgelegt, dass CrypTool bei der
  N-Gramm-Analyse die Länge der Dokumente beschränkt:
   - für Binärdateien auf 64 kByte und
   - für Textdateien auf 256 kByte.
  Werden längere Dateien geöffnet, werden sie -- nur bei dieser Art
  der Analyse -- auf diese Maximal-Länge gekürzt.

- Hashwerte können von Dateien beliebiger Größe berechnet werden.
  Bemerkung: Wird eine Datei geladen, deren Dateilänge größer ist als die
  Maximalgröße des internen Editors, stimmen die Hashwerte nicht überein,
  da das im Editor angezeigte Dokument ja abgeschnitten ist.

- SMIME FlashVideo-Bug
  > Fehlerbeschreibung:
    Flashvideos mit der Endung ".flv" werden nach dem Öffnen einer
    CrypTool-Flash-Animation (z.B. S/MIME oder Rijndael) nicht mehr
    mit dem Standardplayer, sondern mit dem CrypTool-Player für
    Flashanimationen geöffnet.
  > Lösung:
    Explizites Setzen des zuständigen Players. Dazu Rechtsklicken
    auf die Datei und "Öffnen mit ..." auswählen. Jetzt den
    gewünschten Player markieren und das Häkchen unter der
    Programmliste setzen ("Dateityp immer mit dem ausgewählten
    Programm öffnen"). Danach mit "OK" bestätigen und die Datei
    wird ab jetzt immer mit dem eingestellten Player geöffnet.

- AES-Tool:
  - Um Dateien verschlüsselt als selbstextrahierende Archive abzuspeichern,
    dürfen diese Dateien nicht größer als 4 GB sein.
  - Wenn man dagegen nur die reine verschlüsselte AES-Datei ohne
    Selbstentpackungscode erzeugt, kann man auch "beliebig" große
    Dateien verschlüsseln.

  Bitte beachten Sie, dass die Ausgabe des Standalone AES-Tools nicht
  ganz identisch ist mit der Ausgabe, die Sie in CrypTool mit der
  Menüfolge "Ver/Entschlüsseln \ Symmetrisch (modern) \ Rijndael (AES)"
  erhalten (auch nicht, wenn das AES-Tool eine Datei mit der Endung "aes"
  erzeugt). CrypTool selbst verwendet z.Zt. einen festen IV (0), der nicht
  gespeichert wird. AES-Tool nutzt einen zufälligen IV und fügt diesen
  zusammen mit dem Dateinamen hinter den verschlüsselten Daten an.


3.6. Mit älteren CrypTool-Versionen erzeugte Zertifikate und Schlüssel
     -----------------------------------------------------------------
Vergleichen Sie Kapitel 4.3, wo das entsprechende Verhalten bei der
Installation beschrieben wird.



4. Installation / Deinstallation / Schlüsselnutzung / Betrieb
   ----------------------------------------------------------

4.1. Installation
     ------------
Sie installieren CrypTool, indem Sie das CrypTool-Setup-Programm auf Ihrem PC
aufrufen. Standardmäßig wird CrypTool dann in das Verzeichnis
            "C:\Programme\CrypTool"
installiert. Das Zielverzeichnis kann in der Installationsroutine
geändert werden. Sie müssen Zugriffsrechte für das Zielverzeichnis haben.

Wenn Sie es als Administrator in "C:\Programme\CrypTool" installieren,
können Sie CrypTool danach trotzdem als normaler Benutzer ausführen.

Wenn Sie den Zielverzeichnis-Namen "CrypTool" ändern, z.B. in
"CrypTool-1.4.31-Final-de", so wird auch der Eintrag im Startmenü
der Windows-Taskleiste entsprechend geändert.

Nach der Erzeugung wurde das Setup lokal mit den Antiviren-Produkten von
Symantec und Avira gescannt, und remote bei virustotal.com: Dort fanden
nur 2/50 Scannern etwas. Das waren die zwei exotischen Produkte Bkav
(HW32.Packed.B5F3) und Qihoo-360 (HEUR/QVM20.1.0000.Malware.Gen), deren
Meldung wir für False-Positives halten.


4.2. Deinstallation von CrypTool
     ---------------------------
Um CrypTool v1 zu de-installieren, gibt es mehrere Wege -- dies sind die
beiden einfachsten Wege:
1) Sie benutzen das "Start"-Menü in der Windows-Taskleiste.
   Dort gehen Sie zu "Alle Programme" \ "CrypTool".
   Dann klicken Sie im CT-Menü auf "CrypTool deinstallieren".
2) Sie nutzen das Windows-Fenster "Einstellungen" und suchen darin nach
   "Programme installieren und entfernen". Dort klicken Sie in der Liste
   der installierten Programme auf CrypTool.

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
CrypTool nutzen wollen, gibt es zwei Möglichkeiten:
a) Import aus einer alten CrypTool-Version (VOR 1.4.00):
   - Für RSA- und DSA-Schlüssel:
     Exportieren Sie diese PSEs mit Hilfe des alten CrypTools in ein
     PKCS#12-Format und importieren Sie diese Dateien im neuen CrypTool.
   - Für ECC-Schlüssel:
     Hier reicht es, die entsprechenden Dateien
     (z.B. [da][db][EC-prime239v1][1131039030][d] )
     vom alten CrypTool\pse-Verzeichnis in das neue Verzeichnis zu
     kopieren.
b) Import aus einer alten CrypTool-Versionen (ab 1.4.00):
   Sichern Sie VOR der Deinstallation das unter dem Programmverzeichnis
   liegende Verzeichnis pse\ mit allen darin gespeicherten Dateien
   in ein anderes Verzeichnis. Alle Dateien darin können Sie dann nach
   Installation der neuen Version von CrypTool in das neue pse\-Programm-
   verzeichnis kopieren.

Für den Fall, dass mehrere Benutzer dieselbe CrypTool-Installation
verwenden wollen, müssen die Zugriffsrechte auf den Verzeichnissen
pse\ und pse\pseca\ und den darin enthaltenen Dateien für alle
Benutzer auf Vollzugriff gesetzt werden.

Der Teilbaum "pse\" sollte nicht manuell bearbeitet werden, da
bei einer inkonsistenten Struktur nur eine Neuinstallation von
CrypTool bleibt, um die Zertifikats-basierten Verfahren zu nutzen.


4.3.2. Schlüssel gespeichert in den Dateien des PSE-Verzeichnisses
       -----------------------------------------------------------
Die im Menü "PKI" erzeugten Schlüssel für die Verfahren RSA und ECC liegen
im PSE-Verzeichnis (die Schlüssel der klassischen Verschlüsselungsverfahren
werden nicht dauerhaft abgelegt).
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
In Mehrbenutzersystemen hat der Administrator vollen Zugriff auf das ganze
Dateisystem, die restlichen Benutzer können/sollten eingeschränkt sein.

Zur Installation braucht der Benutzer Schreibrechte für das
Verzeichnis, in das CrypTool installiert werden soll:
- z.B. für das Verzeichnis %ProgramFiles% (C:\Programme),
  falls das Unterverzeichnis "CrypTool" noch nicht angelegt ist,
- oder für das Verzeichnis %ProgramFiles%\CrypTool (C:\Programme\CrypTool),
  falls dieses schon angelegt ist).
Hat er diese Zugriffs-Rechte nicht, bricht die Installation ab.

Deshalb sollten Sie als normaler Benutzer ohne Administratorrechte als
Zielverzeichnis ein so genanntes "lokales Verzeichnis" angeben (statt
"C:\Programme"). Lokal und für den Benutzer zugänglich könnten z.B. sein:
%ALLUSERSPROFILE% (Die Standardeinstellung ist: "C:\ProgramData").

Wenn Sie CrypTool ohne Administratorrechte installieren und keine
Schreibrechte auf %ALLUSERSPROFILE%\Start Menu haben, werden unter WinXP
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

b) Will der Benutzer in Mehrbenutzersystemen aus CrypTool heraus Dateien
   anlegen (bzw. ändern), braucht er Schreibrechte auf das entsprechende
   Zielverzeichnis (bzw. auf die entsprechenden Dateien).
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
   des Windows-Betriebssystems nicht angezeigt. Das ist kein CrypTool-
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
   eigentlichen Seiteninhalte nicht mehr anzeigt (dagegen werden die
   Metainformationen wie Inhalt, Index und Suchbegriffe korrekt angezeigt),
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
   Dort erstellen Sie einen neuen Schlüssel namens "ItssRestrictions",
   in welchem Sie danach eine neue Zeichenfolge "UrlAllowList" mit dem Wert
   "\\server\user\program\CrypTool;file://\\server\user\program\CrypTool;
   X:\program\CrypTool;file://X:\program\CrypTool" erstellen.

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
CrypTool wird als komprimiertes, selbstextrahierendes Archiv in derzeit
sieben verschiedenen Sprachversionen verteilt.

Das selbstextrahierende Archiv in deutscher Sprache
           SetupCrypTool_1_4_31_de.exe
enthält folgende Dateien:

ReadMe-de.txt .... Diese Kurzanleitung (deutsch).

md5sum.txt ....... MD5-Hashwerte aller Dateien innerhalb des CrypTool-Paketes.
sha1sum.txt ...... SHA-1-Hashwerte aller dieser Dateien.
authors.txt ...... Informationen zu den Autoren von CT1.

CrypTool.exe ..... Das E-Learning-Programm.
aestool.exe ...... Das Programm AES-Tool, das Dateien in sich selbst-entpackende
                   Programme verschlüsselt. Zur Entschlüsselung müssen
                   Sie das korrekte Passwort eingeben.

CrypTool-de.chm .. HTML-Hilfe-Archiv für die CrypTool-Onlinehilfe
                   (in deutsch).
rijndael-poster-a4.pdf ... Darstellung der Abläufe beim AES-Algorithmus.

msvcr90.dll ...... Nötig für CrypTool.exe.
EC-Param.ini ..... Initialisierungsdatei für auf Elliptischen
                   Kurven basierende Public-Key-Verfahren.
TEST-Param.ini ... Initialisierungsdatei für die Zufallstests.
secude.dll ....... Bibliothek kryptographischer Funktionen von der
                   Secude IT Security GmbH. (xxx)
ticket ........... Lizenz für die Secude-Bibliothek. (xxx)
libxml2.dll ...... Wird benötigt von der secude.dll. (xxx)
secidea.dll ...... Wird benötigt von der secude.dll für die
                   IDEA-Verschlüsselung. (xxx)
srndmskb.dll ..... Wird von der secude.dll für den Entropie-Sammler zur
                   Initialisierung des Secude-Zufallsgenerators benötigt.(xxx)
db.dll ........... Wird benötigt von der secude.dll. (xxx)
secude.xml ....... Wird benötigt von der secude.dll. (xxx)
libeay32.dll...... Bibliothek aus OpenSSL.
SciLexer.dll ..... Bibliothek des Scintilla-Texteditor.
cracklib_Win32.dll .. Unterstützt die PQM-Tests.

Rijndael-Animation.exe .. Animation (Flash) des AES-Algorithmus.
Rijndael-Inspector.exe .. Animation (Flash) zu den Änderungen des
                          Datenblocks innerhalb des AES-Algorithmus.
AES_Flussvisualisierung.jar .. Visualisierung der Datenänderung bei AES.

Enigma_de.exe .... Animation (Flash) der 3-Rotor Enigma-Maschine.
Enigma-Help_de.html .. HTML-Onlinehilfe für  "Enigma_de.exe" (deutsch).
enigma_screenshot1.png .. Screenshot für die Enigma-Hilfedatei.

eccdemo.jar ...... Demo (Java) zur Punktaddition auf Elliptischen Kurven.

ZT.exe ........... Lernprogramm (Authorware) zur Zahlentheorie.
TextZahlWandler.exe .. Hilfsprogramm zu "ZT.exe".
ToolBarWrapper.dll .. Notwendig für das Authorware-Programm ZT.exe

Zahlenhai.exe .... Das Programm zum Lernspiel "Der Zahlenhai".
NumberShark_de.chm HTML-Hilfe-Archiv für die Zahlenhai-Onlinehilfe.
GameData.txt ..... Die ersten High-Scores für das Zahlenhai-Spiel.

CT-Book-de.pdf ... Ein Buch (deutsch) über Kryptographie, Primzahlen,
                   elementare Zahlentheorie und die Mathematik hinter
                   einigen Algorithmen.

CrypTool1-Presentation-de.pdf .. Folien-Präsentation (deutsch)

DialogSchwestern.pdf .. Fantasy-Geschichte von Dr. Elsner, in der
                        eine Variante des RSA-Kryptosystems
                        beschrieben wird.
ChinLab-de.pdf ... Geschichte von Dr. Elsner über zahlentheoretische
                   Probleme, die Marco Polo vom Großen Khan gestellt
                   werden.

Uninstall.exe .... Teil des NSIS-Installers.
license-de.rtf ... Benutzt vom Installationsprogramm.


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
        \Startbeispiel-de.txt
        \Startingexample-en.txt
        \Startingexample-pl.txt

        \Playfair-enc-de.txt
        \probetext-de.txt
        \psion-de-enc.hex ... Verschlüsselte Datei vom Tutorial in Deutsch
        \psion-en-enc.hex ... Verschlüsselte Datei vom Tutorial in Englisch
        \vernam.txt

        \Original.txt ..... "Harmlose" Beispieldatei für die
                            Hashkollision-Demo
        \Faelschung.txt ... "Gefährliche" Beispieldatei für die
                            Hashkollision-Demo

        \letterFromAliceToBob-DECRYPTED-de.txt .. Beispieldateien für die
        \letterFromAliceToBob-ENCRYPTED-de.hex .. Demo des Seitenkanal-
                                  angriffs auf die Hybridverschlüsselung.

        \state2.hex ....... Unverschlüsselte Beispieldaten von ...
        \state2-enc.hex ... Verschlüsselte Beispieldaten von ...
                            "Rijndael-Animation.exe" (per "CrypTool.exe").


cryptochallenges\ ... Dieses Verzeichnis enthält Dateien mit Chiffraten.
                      Die meisten sind historischer Natur, einige davon
                      sind ungelöst.
                      Zwei spezielle Herausforderungen sind auch dabei: die
                      Doppelwürfel-Chiffre (vergleiche www.mysterytwisterc3.org)
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


reference\ ....... Dieses Verzeichnis enthält Textdateien in den Sprachen
                   Deutsch, Englisch, Französisch, Griechisch, Polnisch,
                   Serbisch, Spanisch und Latein. Diese Dateien werden
                   standardmäßig als Referenz für die Analyse von
                   Chiffretexten herangezogen.
                   Diese Dateien sind schreibgeschützt.

reference\deutsch.txt   // Auszug aus dem dt. Umsatzsteuergesetz
         \english.txt   // Auszug aus der Agenda 21 [UN-Dokument]
         \homer-el.txt  // Auszug aus Homers Ilias
         \genesis-de.txt  // Buch Genesis in den Sprachen
         \genesis-en.txt  // Deutsch, Englisch, Französisch, Polnisch,
         \genesis-es.txt  // Serbisch, Spanisch und Lateinisch.
         \genesis-fr.txt  // Die 2-Buchstabencodes (de, en, ...)
         \genesis-pl.txt  // entsprechen den ISO 639 Language Codes.
         \genesis-sr.txt  // 
         \genesis-la.txt  // 


words\ ........... In diesem Verzeichnis liegen die Dateien, mit denen
                   Tests und Analysen durchgeführt werden.

words\cracklib-words        // Für Tests auf Passwortmuster
      cracklib_dict.hwm     // 
      cracklib_dict.pwd     // 
      cracklib_dict.pwi     // 
      VigenereAnalysisSchroedelDictionary.txt   // Für die Vigenère-Analyse
      VigenereAnalysisSchroedelDigrams.txt      // (nach Schrödel)
      VigenereAnalysisSchroedelTrigrams.txt     // Sprachabhängig
      SubstitutionAnalysisMethod2-de.txt   // Für Variante 2 der mono-alphabe-
      SubstitutionAnalysisMethod2-en.txt   // tischen Substitutionsanalyse


sage\ ........... Dieses Verzeichnis enthält die Beispiel-Berechnungen
                  aus dem CT-Buch CT-Book-de.pdf, die mit dem Computer-
                  Algebra-System SageMath ausgeführt wurden. (xxx)

sage\SAGE-Samples-in-Chap01.sage
     SAGE-Samples-in-Chap02.sage
     SAGE-Samples-in-Chap03.sage
     SAGE-Samples-in-Chap04.sage


pse\ ............. In diesem Verzeichnis und in seinem
                   Unterverzeichnis pseca\ werden erzeugte
                   (asymmetrische) Schlüssel und Zertifikate abgelegt.

pse\[SideChannelAttack][Bob][RSA-512][1152179494][PIN=1234].pse
    [HybridEncryption][Bob][EC-prime239v1][1178702474][PIN=1234]
    [HybridEncryption][Bob][EC-prime239v1][1178702474][PIN=1234].pse

pse\pseca\calog        Diese Dateien sind für die Verwaltung der
         \capse.cse    Schlüsseldatenbank notwendig.
         \CA_exts
         \cert.dir
         \cert.pag
         \crls.dir
         \crls.pag
         \CRL_exts
         \user.dir
         \user.pag


animal\ .......... Dieses Verzeichnis enthält die Dateien, die für
                   das Animationsprogramm Animal nötig sind.

animal\animal-2_4_9.jar
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

animal\anims ..... Dieses Verzeichnis enthält AML-Dateien.
                   In jeder AML-Datei ist die Beschreibung zu einer
                   Animation für ein Verschlüsselungsverfahren
                   abgelegt.

animal\anims\caesar_de.aml
            \des_de.aml
            \nihilist_de.aml
            \vigenere_de.aml


Bc\ .............. In diesem Verzeichnis und darunter liegt das Utility
                   bc zum Rechnen mit beliebig langen Zahlen. Es gehört
                   zu "ZT.exe" und kann direkt daraus gestartet werden.
                   Nur bc.exe und bc.1.txt sind im Original dabei; die
                   restlichen BC-Dateien stammen vom "ZT.exe"-Autor
                   und beinhalten Skripte mit zahlentheoret. Funktionen.

Bc\bc.1.txt
  \bc.deutsch.txt ... Übersetzung von bc.1.txt
  \Bc.exe
  \BCmax.bat ........ Wird per F3 aus ZT.exe aufgerufen
                      (bat-Datei startet bc.exe mit ein paar Bibliotheken)
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


xtras\ ............ Gehört zu Authorware, mit dem "ZT.exe" erstellt wurde.

xtras\BMPVIEW.X32
     \MIX32.X32
     \VIEWSVC.X32


smimedemo\ ............ Gehört zur Flash/Java-Animation einer S/MIME-E-Mail.

smimedemo\anim.swf
         \lock2.gif
         \smime.ini
         \SMIME_Animation.exe   [erzeugt temporär params.xml]
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


tadicnafkeys\ ..... Diese Dateien gehören zum Generic t-adic NAF Key Generator.

tadicnafkeys\k1.txt
            \t-adicNAF.exe
            \t-adicNAF.hta
            \t-adicNAF.pdf

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




5.1. Überprüfen der Integrität der heruntergeladenen Dateien
     -------------------------------------------------------
Die Integrität von Dateien kann mit Hashwerten überprüft werden.
Hashwerte sind wie Fingerabdrücke -- mit einer sehr geringen
Informationsmenge kann man ein viel größeres Objekt identifizieren.

Die Dateien vom CrypTool-Projekt kommen normalerweise dadurch auf
Ihren Computer, dass das Archiv (Setup-Datei) heruntergeladen und
die darin enthaltenen Dateien entpackt werden:
a) Herunterladbare Dateien:
   Auf der Homepage von CrypTool (www.cryptool.org) finden Sie
   die Hashwerte aller von der deutschen Webseite direkt
   herunterladbaren Dateien in den dortigen Dateien md5sum.txt bzw.
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



6. Kurze Historie der freigegebenen Hauptversionen von CT1
   -------------------------------------------------------

Release-  Datum         Größe des Windows-Setups  Plattenplatz  Freigabe
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
1.4.31    Aug. 2017      70,7 MB     69,9 MB        113 MB        CT (xxxok)

Bemerkungen zu den (Zwischen-)Versionen:
1.3.02  Viele neue Funktionen gegenüber 1.3.00
1.3.03  Viele kleine Bugfixes und Verbesserungen der Dokumentation
1.3.04  Etliche neue Funktionalität, einige kleine Bugfixes, und Verbes-
        serung und Erweiterung der Dokumentation (Online-Hilfe, Buch)
1.3.05  Kleine Bugfixes
1.4.00-Beta10  Dez. 2005  Erste öffentliche Beta von Version 1.4.00
1.4.00-Beta12  März 2006  Zweite öffentliche Beta von Version 1.4.00
1.4.00-Beta14  Juli 2006  Dritte öffentliche Beta von Version 1.4.00
1.4.00  Viele neue Funktionen gegenüber 1.3.05
1.4.10-Beta04  Mai  2007  Erste öffentliche Beta von Version 1.4.10
1.4.10-Beta06  Juli 2007  Zweite öffentliche Beta von Version 1.4.10
1.4.10  Funktionsumfang und Onlinehilfe stark erweitert i.Vgl. zu 1.4.00
1.4.20-Beta03  Mai  2008  Erste öffentliche Beta von Version 1.4.20
1.4.20  Funktionsumfang und Onlinehilfe erweitert i.Vgl. zu 1.4.10;
        vor allem Feinschliff und Code stabilisiert (Qualitätsrelease).
1.4.21  Patch, das auch die MSVCR71.dll enthält, da diese Datei von der
        neuen aktuellen OpenSSL-Bibliothek benutzt wird und nicht auf
        frischen Windows-Umgebungen (ohne Office) enthalten ist.
1.4.30-Beta03  März 2009  Erste öffentliche Beta von Version 1.4.30
1.4.30-Beta04  Sep. 2009  Zweite öffentliche Beta von Version 1.4.30
1.4.30-Beta05  Jan. 2010  Dritte öffentliche Beta von Version 1.4.30 (22.01.2010)
1.4.30-Beta06  Feb. 2010  Vierte öffentliche Beta von Version 1.4.30 (28.02.2010)
1.4.30-Beta07  Juni 2010  Fünfte öffentliche Beta von Version 1.4.30 (09.06.2010)
1.4.30-Beta08  Juli 2010  Sechste öffentliche Beta von Version 1.4.30 (09.07.2010)
1.4.30  Viele Bugfixes und erweiterter Funktionsumfang i.Vgl. zu CT 1.4.21
        Plattenplatz-Bedarf der verschiedenen Sprachversionen von CT 1.4.30:
        EN:  93,7 MB
        DE:  94,7 MB
        PL: 100,0 MB
        SR:  93,7 MB
        ES:  94,4 MB
1.4.31-Beta05  Juli 2012  Erste öffentliche Beta von Version 1.4.31
1.4.31-Beta06  Feb. 2013  Zweite öffentliche Beta von Version 1.4.31
1.4.31-Beta06a Juni 2013  Dritte öffentliche Beta von Version 1.4.31
                          (erstmals mit einer griechischen Sprachversion)
1.4.31-Beta06a Juli 2013  Vierte öffentliche Beta von Version 1.4.31
1.4.31-Beta06b Okt. 2013  Fünfte öffentliche Beta von Version 1.4.31
1.4.31-Beta06c 2015       Weitere Beta von Version 1.4.31
1.4.31-Beta06d 2016       Weitere Beta von Version 1.4.31
1.4.31  Viele Bugfixes und erweiterter Funktionsumfang i.Vgl. zu 1.4.30.
                          (erstmals mit einer französischen Sprachversion)



7. Feedback und Kontaktadressen
   ----------------------------
Sollten Sie Probleme haben oder Fehler finden, wenden Sie sich
bitte mit einer ausführlichen Beschreibung des Problems (und einigen
Bildschirmbildern dazu) per E-Mail an eine der hier genannten Personen.

Für Anregungen jeglicher Art bezüglich CrypTool sind wir immer
dankbar und helfen Ihnen gern, wenn es unsere Zeit erlaubt.

Auch würden wir uns freuen, wenn Sie uns mitteilen, wie und wo Sie
CrypTool einsetzen.

Kontaktadressen:
- bernhard.esslinger@uni-siegen.de
- esslinger@cryptool.org
- joerg-cornelius.schneider@db.com
- henrik.koy@db.com




8. Verweise / Auszeichnungen
   -------------------------

Vergleiche auch:
- https://www.cryptool.org/de/ctp-links
- https://www.cryptool.org/de/ctp-lehre/wissenschaft
- https://www.cryptool.org/de/ctp-lehre/auszeichnungen


8.1. Artikel / Wissenschaftliche Veröffentlichungen über CrypTool
     ------------------------------------------------------------

8.1.1. Artikel -- eine ältere Auswahl
       ------------------------------

- c't 14/2001
In diesem renommierten und auflagenstarken deutsch-sprachigen
Computermagazin wurde im Juli 2001 ein 5-seitiger Artikel zu
CrypTool veröffentlicht (S. 204-208).

- DuD Oktober 2002
In der deutsch-sprachigen Fachzeitschrift "DuD Datenschutz und
Datensicherheit", Ausgabe 10/2002 erschien unter dem Titel
"CrypTool - spielerischer Einstieg in klassische und moderne
Kryptographie. Neue Version - fundierte Awareness in Deutsch
und Englisch" ein 4-seitiger Artikel über CrypTool.

- KES 2/2003 (Mai 2003)
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

- Tagungsband 8. Deutscher IT-Sicherheitskongress des BSI (Mai 2003)
Auf dem BSI-Kongress 2003 in Bonn wurde von Hr. Koy der Vortrag
"Awareness in der Informationsgesellschaft: CrypTool - Kryptographie
spielerisch verstehen" gehalten. Die Textfassung dazu steht im
Tagungsband, "IT-Sicherheit im verteilten Chaos", auf S. 485 - 500.

- Datenschutz PRAXIS (Juni 2005)
In der deutsch-sprachigen Fachzeitschrift "Datenschutz PRAXIS",
Ausgabe Juni 2005 erschien unter dem Titel "Spielend verschlüsseln lernen
mit dem kostenlosen CrypTool" ein 2-seitiger Artikel über CrypTool von
Dr. Rainer W. Gerling.
Diesen Artikel finden Sie im Internet unter
http://www.lrz-muenchen.de/~rgerling/pdf/DatenschutzPRAXIS_2005_06_9.pdf.

- Report Touch Briefing Information Security (Oktober 2006)
Der "Touch Briefing Information Security"-Report 2006 enthält den Artikel
"The CrypTool Project -- Improving Awareness and Education for Cryptology".
Abrufbar im Internet unter:
  http://www.touchbriefings.com/pdf/2259/esslinger.pdf
Mit den Suchbegriffen "awareness cryptology" listeten danach sowohl
google.de wie google.com diesen Artikel auf Platz 1.

- DFN-Mitteilungen, Heft 73 (Dezember 2007)
Diese Mitteilungen des Deutschen Forschungsnetzes (DFN) enthalten den
4-seitigen Artikel "CrypTool -- Ein E-Learning-Programm für Kryptologie".

- KES 3/2008 (Juli 2008)
In der deutsch-sprachigen Fachzeitschrift "KES - Zeitschrift für
Informations-Sicherheit", Ausgabe 3/2008 erschien unter dem Titel
"(Ver)Schlüsselerlebnisse NG" ein 3 1/3-seitiger Artikel zum
10-jährigen Jubiläum von CrypTool und zu den neuen Versionen.

- Telepolis 8/2008 (August 2008)
Ein Artikel von Klaus Schmeh über CrypTool erschien unter dem Titel
"Werkzeugkasten für Codeknacker" in dem Online-Magazin Telepolis.
http://www.heise.de/tp/r4/artikel/28/28389/1.html

- Eclipse Magazin 4/2008 (Oktober 2008)
Ein Artikel von Dominik Schadow über JCrypTool erschien unter dem Titel
"JCrypTool: Kryptisch gesagt..." im "Eclipse Magazin".
Dieser Artikel kann als Reprint herunter geladen werden von:
http://www.trivadis.com/fileadmin/user_upload/PDFs/Trivadis_in_der_Presse/EclipseMagazin_Kryptisch_gesagt_Schadow.pdf

- ep-Elektropraktiker Januar 2009
In der deutsch-sprachigen Fachzeitschrift "ep-Elektropraktiker", Ausgabe 01/2009 erschien unter dem Titel "CrypTool - sichere Kommunikation" ein 2-seitiger
Artikel über CrypTool von H. Möbus.
http://www.elektropraktiker.de/download/luk-2009-1-06-46867.html

- DuD März 2009
In der deutsch-sprachigen Fachzeitschrift "DuD Datenschutz und
Datensicherheit", Ausgabe 03/2009 erschien unter dem Titel
"CrypTool - Ein Open-Source-Projekt in der Praxis. Erfahrungsbericht
eines erfolgreichen Open-Source-Projektes" ein 6-seitiger Artikel über
CrypTool.

Weitere Artikel sind auf der folgenden Webseite aufgelistet:
https://www.cryptool.org/de/ctp-lehre/auszeichnungen/267-medien


8.1.2. Wissenschaftliche Veröffentlichungen
       ------------------------------------
Ein paar sind aufgeführt unter:
https://www.cryptool.org/de/ctp-lehre/wissenschaft



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
Im April 2012 waren Artikel vor 2002 nicht mehr abrufbar.
Unter http://www.wiwo.de/unternehmen/kryptographie-spezial/4754982.html
findet sich eine kurze Zusammenfassung des Artikels.

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
Die BOSS-Live-CD wurde inzwischen durch OpenVAS ersetzt. OpenVAS ist ein
Server-basiertes Sicherheitswerkzeug. Gesteuert wird über eine
Client-Komponenten (Greenbone Security Desktop (GSD)), die für Linux und
Windows verfügbar ist. Diese ist genauso wie alle anderen Komponenten von
OpenVAS als Freie Software verfügbar.


8.2.4. In Fortbildungen / Kursen (Beispiele)
       -------------------------------------
- CISSP, TISP (TeleTrusT Information Security Professional), ...

- https://www.tisp.de/
  http://www.logicalsecurity.com/education
  http://www.careeracademy.com
  https://www.cccure.com

- http://www.cdachyd.in/cnss/cnss_ebrochure.htm   (Dez. 2008)
  Ein 20-wöchiger Kurs über Netzwerk- und Systemsicherheit (CNSS), angeboten
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
   21.09.2005 unter der Überschrift "eLearning Program for Cryptology":
   http://www.professionalsecuritytesters.org/modules.php?name=Forums&
   file=viewtopic&t=34

   Ein ähnliches Post gab es am 22.09.2005 auf der "CISSP, SSCP, CISM,
   CISA, ISSPCS, and SANS GIAC GCFW Open Study Guides Web site" for
   Cryptography: http://www.cccure.org/modules.php?name=News&new_topic=51
   mit dem Titel "CrypTool A great tool to learn more about cryptography".


c) Wikipedia:
   - Deutsch:
     - https://de.wikipedia.org/wiki/CrypTool
     - http://de.wikipedia.org/wiki/Kryptographie
     - http://de.wikipedia.org/wiki/Wikipedia:WikiProjekt_Kryptologie
   - Englisch:
     - https://en.wikipedia.org/wiki/CrypTool
     - http://en.wikipedia.org/wiki/Cryptography
     - http://en.wikipedia.org/wiki/Topics_in_Cryptography
   - Polnisch:
     - http://pl.wikipedia.org/wiki/CrypTool
     - http://pl.wikipedia.org/wiki/Kryptografia
   - Spanisch:
     - http://es.wikipedia.org/wiki/CrypTool
   - Serbisch:
     - http://sr.wikipedia.org/sr/CrypTool
   - Französisch:
     - http://fr.wikipedia.org/wiki/CrypTool
   - Thailändisch:
     - http://th.wikipedia.org/wiki/CrypTool
   - Italienisch:
     - http://it.wikipedia.org/wiki/CrypTool
   - Griechisch:
     - http://el.wikipedia.org/wiki/CrypTool
   - Russisch: (xxx)
   - Türkisch: (xxx)
   - Chinesisch: (xxx)


d) Eine kleine Auswahl weiterer Seiten, die CrypTool 1 erwähnen:
   https://www.a-i3.org/content/view/415/28/
   http://www.fh-lueneburg.de/mathe-lehramt/krypto/krypto.htm
   http://www.kryptographiespielplatz.de/
   http://www.tinohempel.de/info/info/kryptografie/index.htm
   http://www.edoeb.admin.ch/themen/00794/00928/00930/00953/index.html?lang=de
       (siehe Link unter "Freeware-Programm, mit dem Sie kryptographische
                          Verfahren anwenden können")
   http://www.roehri.ch/~sr/links/crypto.html
   http://www.freebyte.com/security/, http://www.freebyte.com/education/
       (Last updated on April 03, 2015)
   http://nlp.stanford.edu/projects/nmt/data/wmt14.en-de/vocab.50K.de
       [text for Neural Machine Translation :-)]
   http://williamstallings.com/Cryptography/Crypto7e-Student/
        (Ressource-Seite zu dem Buch "Cryptography and Network Security",
         7. Auflage von William Stallings)
   http://www.garykessler.net/library/crypto.html
   http://blog.learningtree.com/an-introduction-to-using-cryptool-to-show-how-ciphers-work
   http://www.c-sharpcorner.com/article/encryption-decryption-using-cryptool/
   https://crypto.stackexchange.com/questions/18001/cryptool-des-ecb-and-cbc-double-encyption
   https://www.limited-entropy.com/crypto-series-introduction-to-cryptool/
   http://www.guru99.com/how-to-make-your-data-safe-using-cryptography.html  +++
   http://scienceblogs.de/klausis-krypto-kolumne/

   Ein freies Schulbuch zum Fach Informatik am Gymnasium:
   - http://blog.learningtree.com/an-introduction-to-using-cryptool-to-show-how-ciphers-work
   - http://www.inf-schule.de/kommunikation/kryptologie/historischechiffriersysteme/station_ersetzungsverfahren
   - http://www.inf-schule.de/kommunikation/kryptologie/historischechiffriersysteme/station_vigenereverfahren
   - http://www.inf-schule.de/kommunikation/kryptologie/historischechiffriersysteme/station_onetimepad
   - http://www.inf-schule.de/kommunikation/kryptologie/modernechiffriersysteme/beispiel_aes/exkurs_experimentecryptool
   - http://www.inf-schule.de/kommunikation/kryptologie/rsa/cryptool/station_rsademo
   - http://www.inf-schule.de/kommunikation/kryptologie/digitalesignatur/einstieg_hashfunktion/experimentecryptool



8.3. Weitere Freeware-Projekte (Crank, CAP, CryptoStudio, SageMath, etc.)
     --------------------------------------------------------------------

a) Vollständig mit Source-Code verfügbar sind:

- http://freshmeat.net/projects/crank/
  http://freecode.com/projects/crank
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
  http://freecode.com/projects/griffon
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
  Kryptos ist eine Kryptographie-Lernsoftware mit einer statischen
  Oberfläche, aber vielen modernen Algorithmen, die dynamisch aus
  verschiedenen Bibliotheken kommen können.
  Kryptos hat keine Kryptoanalyse-Funktionen.
  Die aktuelle Version Kryptos 3.01 stammt vom Dezember 2006,
  sie erfordert .NET Framework 2.0.

- http://cryptostudio.sourceforge.net/
  CryptoStudio von Prof. Marco Russo
  Die aktuelle Version 1.0 stammt vom Juni 2005. Sie ist in Englisch
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
  und ohne Analysefunktionalität, geschrieben in Python.
  Die drei klassischen Verschlüsselungsverfahren können sowohl von der GUI,
  von der Kommandozeile wie als Netzwerk-Proxy ausgeführt werden.
  Die aktuelle Version 1.0 wurde von Shannon -jj Behrens im Juni 2003
  veröffentlicht.

- http://www.nku.edu/~cryptography/doku.php?id=downloads:downloads
  (von http://www.nku.edu/~christensen)
  Das darin enthaltene Java-Programm CryptoHelper.JAR vom "Math and Computer
  Science Club" an der NKU ist ziemlich komplett, was klassische Chiffren
  angeht.
  Letzter Update: Gary Watson, Aug 2005.

- http://www.cs.unc.edu/~stotts/145/homes/crypt/
  Cypher, geschrieben in C und FLTK (für Windows und Unix), ist ein
  Toolkit, um die Entschlüsselung klassischer Chiffren zu unterstützen
  mittels statistischer Daten und Verfahren.
  Es wurde in einem Universitäts-Projekt von 6 (?) Studenten im Jahre
  2000 entwickelt. Die Webseite enthält die Sourcen, aber nicht die
  ausführbaren Dateien.

- http://silenteye.v1kings.io/
  https://github.com/achorein/silenteye/tree/0.4/vagrant
  SilentEye ist mittels Qt eine Cross-Plattform-Anwendung für Steganographie.
  Damit man man Nachrichten in Bildern und Tönen verstecken. Es hat eine
  ansprechende Oberfläche und bietet einfache Erweiterungsmöglichkeiten.
  Zusätzlich kann man es von der Kommandozeile aufrufen. Nutzt GNU GPL v3.
  Letzter Update: Version 0.4.3, Feb 2013.  

- Im Open-Source Computer-Algebra-System "SageMath" sind ebenfalls einige
  Algorithmen aus dem Gebiet der Kryptographie implementiert:
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
  SageMath wird auch für einige Beispiele im CrypTool-Buch verwendet.

- Die Webseite der American Cryptogram Association (ACA), einer Non-Profit-
  Organisation, die sich "dem Hobby und der Kunst der Kryptoanalye" widmet.
  Diese Seite enthält sehr viel Code und Informationen zu Papier&Bleistift-
  Verfahren und zu klassichen Chiffren und ihrer Kryptoanalyse.
  http://www.cryptogram.org/



b) Die einzigen weiteren uns bekannten brauchbaren Programme, die
   Kryptographie und Kryptoanalyse (unter einer graphischen Oberfläche)
   verbinden, sind solche, für die der Source-Code nicht freigegeben wurde:

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
  verfahren; war verfügbar ab Dezember 2002 unter
  http://phoenix.goucher.edu/~jtrafton/Crypto; Link ist tot).

- Die Java-Anwendung CipherClerk von Wilhelm M. Plotz
  (Ver- und Entschlüsselung mit vielen klassischen Verfahren;
  letztes Update 2003)
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
  Zur Ausführung unter Windows XP muss man den "Windows 2000 compatibility
  mode" aktivieren.
  Letztes Update:  2.05.2004 - Uploaded Cryptanalysis Project
                  27.11.2004 - Version 0.17 (laut Splash Screen)
                             - Version 0.37 (laut Hilfedatei)
  http://studenthome.nku.edu/~kohuss/content/crypt.html

- "Cryptography Tools" von Don Spickler
  Das Java-Programm entstand an der Henson School of Science & Technology,
  Salisbury University "to help users understand the workings of and the
  cryptanalysis of several classical ciphers".
  Es gibt ausführbare Dateien (keine Sourcen) für Windows, Linux und Mac.
  Letztes Update: 24.9.2009 -- Version 1.2.1
  http://facultyfp.salisbury.edu/despickler/personal/CryptTools.asp

- "CryptoCrack" von Phil Pilcrow
  Das Windows-Programm CryptoCrack wurde entworfen, um klassiche Chiffren zu
  lösen: "CryptoCrack can solve over 50 different classical cipher types and
  in many cases without knowing any plaintext or the key length"
  (Abruf 23.10.16).
  Deshalb enthält es keine Routinen, um Maschinen-basierte oder moderne,
  Computer-basierte Verfahren wie Enigma, AES, DES, Blowfish etc. zu knacken.
  Dieses Tool löst viele klassische Chiffren sehr schnell und in guter
  Qualität.
  Erstes Release: 29.5.2011; weiterhin aktive Weiterentwicklung.  
  Letztes Update: März 2017 -- Version 0.7 beta (Version 0.7.6279.17017))
  https://sites.google.com/site/cryptocrackprogram/home

- "CryptoMake" von Phil Pilcrow
  Sehr umfangreiches Programm zum Verschlüsseln mit klassischen Verfahren.
  Erstes Release: 5.3.2014; weiterhin aktive Weiterentwicklung.
  Letztes Update: Feb. 2016 -- Version 0.2 beta (version 0.2.5901.21555)
  https://sites.google.com/site/cryptomake/


Falls uns hier etwas entgangen ist, würden wir uns über eine Nachricht
freuen -- wir vervollständigen oder korrigieren diese Liste gerne.

Außerdem wollen wir hier ausdrücklich das Angebot machen, die
Anstrengungen für diese einzelnen Programme in ein einziges
Programm zu integrieren. Wir freuen uns über jede Kooperation!!



8.4. Auszeichnungen
     --------------
Generell ist es für uns die größte Auszeichnung, wenn CrypTool breit
eingesetzt wird, und dabei in Schule, Lehre und Training einen guten
Nutzen stiftet. Über die vielen bisher erhaltenen positiven Rückmeldungen
freuten wir uns sehr. Wir versuchen, auch in Zukunft auf alle Ihre Wünsche
schnell zu reagieren.

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
  Wissensvermittlung Kryptographie) ging an das CrypTool-Projekt.

- Ausgewählter Ort 2008 im Land-der-Ideen
  Das CrypTool-Projekt wurde bei dem bundesweiten Wettbewerb "365 Orte im
  Land der Ideen" in der Kategorie Wissenschaft und Technik ausgewählt.
  Dazu fand am 22.07.08 an der Universität Siegen ein Tag-der-offenen-Tür
  statt.

Vergleiche auch
https://www.cryptool.org/de/ctp-lehre/auszeichnungen/258-auszeichnungen


A. Anhang
   ------

A.1. .... Roadmap nach CT 1.4.31
A.2. .... Nachfolger-Projekte mit Java/Eclipse und C#/.NET
A.2.1. .... Design der Nachfolger-Projekte CT2 und JCT
A.2.2. .... Funktionen der Nachfolger-Projekte CT2 und JCT
A.3. .... Mögliche Punkte für eine Weiterentwicklung -- Neue Funktionen, Ideen
A.3.1. .... Funktionalität: Algorithmen / Verfahren
A.3.2. .... Funktionalität: Analyse
A.3.3. .... Interne Schnittstellen / Editoren
A.3.4. .... User-Interface / Visualisierungen
A.4. .... CT1 unter Linux
A.4.1. .... Ausführen von CT1 unter Linux mit Wine
A.4.2. .... Portierungsversuch von CT1 nach Linux mit Qt


Alle in CT1, CT2, JCT und CT-Online verfügbaren Funktionen können in einer
interaktiven Liste abgerufen werden auf:
   https://www.cryptool.org/de/ctp-dokumentation/funktionsumfang



A.1. Roadmap nach CT 1.4.31
     ----------------------
Generell fließen alle größeren Neu-Entwicklungen aus dem CT-Projekt nun in
die beiden schon existierenden Nachfolger-Projekte CT2 und JCT (siehe A.2).

In CT1 werden weiterhin Fehler behoben.

Für diejenigen, die weiterhin lieber in C/C++ implementieren wollen, gibt es
auch einen Nachfolger: Qt-CrypTool (QCT).
Hier wird CT1 mit Qt 5 weiter entwickelt:
- Die Oberfläche wird komplett neu geschrieben mit Qt (statt MFC) und
  damit Plattform-unabhängig sein. Sie soll dasselbe Look&Feel wie CT1
  haben.
- QCT wird ebenso wie JCT auf Linux, MacOS, und Windows laufen.
- Mittels Qt kann man mehrere Sprachen in ein Setup und in ein Executable
  packen, so dass man in QCT ohne Neustart die Sprache wechseln kann.
- Eine mögliche inhaltliche Weiterentwicklung ist die Integration eines
  Forks von OpenSSL, der die Chinesischen Krypto-Standards implementiert
  (diese sind vergleichbar zu den NIST-Standards und genießen noch mehr
  Aufmerksamkeit, seit durch Edward Snowden Gewissheit wurde, was vorher
  nur Gerüchte waren).
- Siehe https://github.com/flomar/QCrypTool


A.2. Nachfolger-Projekte mit Java/Eclipse und C#/.NET
     ------------------------------------------------
Die Nachfolger von CT1 nutzen State-of-the-Art-Entwicklungsumgebungen,
aktuelle Layout-Techniken und moderne Software-Architekturen.

A.2.1. Design der Nachfolger-Projekte CT2 und JCT
       ------------------------------------------
a) Generelle Wunschliste anhand des Benutzerfeedbacks zu CT1
   Dies gilt für beide Nachfolger-Versionen Java-CrypTool und CrypTool 2:
   - Moderne Pure-Plugin-Architektur
   - Alle Sprachen von einem Programm unterstützt, ein einzigs Setup
   - Moderneres Layout, weniger Dialogboxen-Wechsel
   - Standardkonformität in der Bedienung
   - Mehr Benutzerinteraktion
   - Dynamischer Wechsel zwischen den Sprachen
   - Dynamischer Wechsel zwischen Kryptoprovidern
   - Automatische Updates aus dem Internet (unter Beibehaltung der geöffneten
     Dateien nach dem Neustart)
   - Alle Funktionen als Thread implementieren (parallel, alle abbrechbar)
   - Funktionen nutzen alle CPU-Kerne, falls vorhanden
   - Einfacheres Erstellen von Kaskaden, zusammengestellt aus den
     existierenden Elementen
   - Mehr Einstellmöglichkeiten bei den Alphabeten der klassischen Verfahren
   - Anbieten eines Recorders für Benutzereingaben (Action-Historie)
   - Alle Dateien als Stream nutzen, um auch sehr große Dateien bearbeiten
     zu können
   - Steuerung der gesamten Funktionalität auch von der Kommandozeile

b) Java-CrypTool (JCrypTool, JCT):
   - Komplett neu designtes CrypTool in Java mit Eclipse/RCP
   - Plattform-unabhängig --> Support für Windows, MacOS und Linux
   - Nutzung von SWT für die GUI
   - Nutzt strikt die Standards von Eclipse
   - Bouncy-Castle (BC) und FlexiProvider (FP) werden als Krypto-Provider
     benutzt. Der FP wird in BC aufgehen.
     JCT als Angebot eines dynamischen, grafischen Frontends für BC.
   - XML-Sicherheit (Demonstrator für XML-Signaturen)
   - Zusammenarbeit mit dem Lehrstuhl Prof. Buchmann, TU Darmstadt für
     die Integration des FlexiProviders
   - Für Einsteiger, aber auch für Experten
   - Nutzung von Github mit Git zur Sourcecode-Verwaltung:
     https://github.com/jcryptool/
     https://github.com/jcryptool/core
     https://github.com/jcryptool/core/wiki
     https://github.com/jcryptool/crypto
     https://github.com/jcryptool/doc

c) CrypTool 2 (CT2)
   - Komplett neu designtes CrypTool in C# mit dem .NET-Framework und WPF
   - Nutzt strikt die Standards von Microsoft .NET (Aussehen wie Office 2007)
   - Nutzung von Windows Presentation Foundation (WPF) zur Gestaltung
     von multimedialen Oberflächen (GUI) mit Vektorgraphiken
   - Das gesamte Projekt lässt sich mit der jeweils neuesten kostenlosen
     Version von Visual Studio Express-Edition für C# erstellen.
   - Verfügbar als Krypto-Provider sind:
     - der .NET Krypto-Provider,
     - Bibliotheken wie GMP/MPIR und Crypto++ per Wrapper, und
     - BouncyCastle für C#.
   - Hoher Lerneffekt bei Einsteigern durch visuelle Programmierung
   - Enge Zusammenarbeit mit den Lehrstühlen Prof. Weis in Duisburg-Essen
     und Prof. Wacker in Kassel
   - Nutzung von Subversion zur Source-Code-Verwaltung.



A.2.2. Funktionen der Nachfolger-Projekte CT2 und JCT
       ----------------------------------------------
Die neuen Versionen (siehe Kapitel A.2.1) sind:
- CT2: CrypTool 2.x   und
- JCT: JCrypTool 1.x



Einige (nicht alle) Funktionen der Release-Versionen der Nachfolger-Projekte:

-------------------------------------------------------
- CT2  Visuelle Programmierung (Komposition von Protokollen und Workflows)
- CT2  Tutorial: Primzahlen-Visualisierungen
- CT2  Tutorial: Bleichenbacher Angriff, Erweiterungen von Kühn
- CT2  Tutorial: Gitter-basierte Kryptographie
- CT2  WEP-Verschlüsselung und WEP-Analyse (Angriff auf WEP-Protokoll)
- CT2  DH-Schlüsselaustausch
- CT2  Visualisierung eines Quantum-Schlüsselaustausch-Protokolls (BB84)
- CT2  Steganographie-Verfahren
- CT2  Smartcard-Plugin (sendet Kommandos an eine Chipkarte
                         mittels der PC/SC-Schnittstelle in Windows)
- CT2  Cube Attack gegen symmetrische Chiffren (I. Dinur und A. Shamir)
- CT2  SAT-Solver
- CT2  Homomorphe Verschlüsselung (Paillier)
- CT2  Quadratisches Sieb (deutlich schneller als in CT1)
       Zeitmessungen siehe:
       - https://www.cryptoportal.org/details_links.php?PHPSESSID=1a3ea85bebc01e983a852682cecc48b3&link_id=69
       - http://bscw.schule.de/pub/bscw.cgi/d864899/Schulz_Witten_Zeit-Experimente.pdf
- CT2  GNFS (aufbauend auf YAFU und msieve)
- CT2  Solitaire-Verschlüsselung und -Analyse
- CT2  Dezimalisierungsverfahren (Visa, Modulo, Multiplikation, IBM)
- CT2  Mathematische Werkzeuge wie Berlekamp-Massey
- CT2  Vigenère-Autokey-Verschlüsselung und verteilte Analyse dazu
- CT2  Mächtige Analyseverfahren gegen klassische Verfahren (incl. Enigma)
- CT2  Suche nach Wort-Patterns m.H. von Normierungen (z.B. "einen" = 12313)
- CT2  LFSR, NLFSR
- CT2  Symmetrische Verschlüsselungsverfahren von Ecrypt (SOSEMANUK, ...)
- CT2  Verschlüsselung mit Enigma, Purple, T310/50, M209, M-138
- CT2  Verschlüsselung mit DES, AES, PRESENT, Twofish, ...
- CT2  Verschlüsselung eines Klartextes mit AES unter Verwendung eines ASCII-
       Passworts (das per PKCS#5 in einen AES-Schlüssel konvertiert wird). Das
       Ergebnis wird Base64-encoded ausgegeben, um es leicht per Copy & Paste
       z.B. in eine Email einfügen zu können. Verbinden mit der Smartphone
       App CrypDroid.
- CT2  Bewertung der Passwort-Stärke

-------------------------------------------------------
- JCT  Adaptive Navigationsleiste, wahlweise als Baum oder Palette, mit Filter
- JCT  Vigenère-Autokey-Verschlüsselung
- JCT  Visualisierung klassischer (Analyse-)Verfahren
- JCT  Einstellbarkeit aller Detail-Parameter moderner Algorithmen
       in der Algorithmen-Perspektive (bspw. für Post-Quantum-Algorithmen)
- JCT  Dragon-Verschlüsselung & LFSR
- JCT  Analyse-Verfahren für Entropie, Friedman, Häufigkeit
- JCT  Detaillierte Visualisierung der inneren Eigenschaften von DES
       (Rundenschlüssel, Fix-Punkte, Avalanche-Effekt in der S-Box)
- JCT  Visualisierung von Berechnungen auf Elliptischen Kurven
       über R, F(p) und F(2^m)
- JCT  Visualisierung von Kleptographie-Algorithmen (vier verschiedene
       "böswillige" Verfahren zur RSA-Schlüsselerzeugung incl. SETUP-Angriff)
- JCT  Multi-partite Schlüsselvereinbarung
- JCT  Homomorphe Verschlüsselung (RSA, Paillier, Gentry&Halevi)
- JCT  Analyse von Transpositions-Chiffren mit dem ACO-Algorithmus
- JCT  Visualisierung von Zero-Knowledge-Beweisen
- JCT  Running-Key-Verschlüsselung und automatische Analyse (Viterbi)
- JCT  Verifiable Secret Sharing
- JCT  Spiele: Zahlenhai (incl. heuristische Solver) und Sudoku-Solver
- JCT  Mächtige Action-History und Kaskadierungs-Unterstützung
- JCT  Vielfältige Einstellmöglichkeiten für die bei den klassischen
       Verschlüsselungs-Verfahren benutzten Alphabete und ein integriertes
       Kommandozeilenprogramm dafür
- JCT  Visualisierung und Erläuterung der Mustersperre von Android (AUP)
- JCT  Visualisierung der Ergebnisse verschiedener Gültigkeitsmodelle für
       Zertifikate (nutzt Schiebregler, um die Parameter schnell anzupassen)
- JCT  PQC-Signaturschemata (WOTS, MSS, XMSS-MT) und damit
       Visualisierung und Erläuterung des Merkle tree und von Post-Quantum
       sicheren Signaturen




A.3. Mögliche Punkte für eine Weiterentwicklung -- Neue Funktionen, Ideen
     --------------------------------------------------------------------

Die Entwickler-Wikis von CT2 und JCT enthalten je eine Liste mit Programmier-
Aufgaben zu weiteren Funktionen, die nachgefragt wurden:
- CT2: https://www.cryptool.org/trac/CrypTool2/wiki/StudentTasksProposals
- JCT: https://github.com/jcryptool/core/wiki/project-Ideas

Hier sind weitere mögliche Themen für Erweiterungen, die noch bei CT1 hochkamen.
Was schon in CT2 oder JCT geplant ist, ist entsprechend gekennzeichnet.



A.3.1. Funktionalität: Algorithmen / Verfahren
       ---------------------------------------
- Erstellen eines Interfaces, so dass die Offline-Programme JCT und CT2 von
  Webbrowsern aus aufgerufen werden können

- Weitere Algorithmen zu jedem Thema implementieren:
    * Codes:
       - T9 (http://de.wikipedia.org/wiki/Text_on_9_keys) etc.
    * Verschlüsselung:
       - Klassische Verfahren (incl. Analyse): z.B.
           - Sigaba
           - Weitere Rotorchiffren, Hagelin, Lorenz-Maschine
           - JCT: Alphabete auch für die klassischen Verfahren
                  auf 256 Zeichen ausdehnen
       - Symmetrische Verfahren:
           Camellia (RFC3713), RC5 und Gost (http://vipul.net/gost),
           Radio Gatun, SOSEMANUK, VSH, ...
       - Public-Key-Verfahren: McEliece, Rabin, NTRU
       - Demonstration der Visuellen Kryptographie
       - Neue Verfahren von Ecrypt (Network of Excellence in Cryptology)
         integrieren. Siehe http://www.ecrypt.eu.org
    * Hashverfahren:
       - CT2: Tiger (http://www.cs.technion.ac.il/~biham/Reports/Tiger)
       - Alle SHA-3-Kandidaten
         (http://csrc.nist.gov/groups/ST/hash/sha-3/index.html)
    * Protokolle / Protokollschwächen:
       - Visualisierung von Man-in-the-Middle-Angriffen
       - Visualisierung von SSL
       - Blind Signatures
       - Elektronische Wahlen
       - CT2 Virtuelle Kreditkartennummern (VCC) und Prüfziffern
       - JCT Visualisierung des KEGVER-Protokolls und weiterer Kleptographie-
             Verfahren (http://www.cryptovirology.com)

- Schnelle Auswahl der verschiedenen Verschlüsselungsverfahren
  über eine Dialogbox statt über die Menüs (Offenlegung aller
  Steuerparameter der Algorithmen) (analog CryptoBench)

- Erzeugung aller Hashwerte aus regulärem PW-Ausdruck (Hartmann)

- Kryptographisch starke elliptische Kurven erzeugen und damit
  Implementierung eines auf Elliptischen Kurven basierenden
  Kryptosystems. Dazu könnte man das Kryptosystem von Menezes
  und Vanstone nehmen, das 1993 von diesen Autoren vorgeschlagen
  wurde: A. Menezes and S. Vanstone,
         "Elliptic curve cryptosystems and their implementation",
         Journal of Cryptology, 6 (1993), Seite 209-224,
  oder eines von Dan Bernstein.

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
  - Weitere Zufallstests (aus der spanischen Version?)
  - CT2  NIST Zufalls-Testsuite

- Weitere Standards implementieren und direkt über die Menüs bzw.
  aus der Online-Hilfe heraus an alle Stellen verzweigen, wo diese
  Standardverfahren (z.B. PKCS#5) verwendet werden (Hauptarbeit
  dabei sind das User Interface und die Dokumentation).

- JCT  PGP-S/MIME Interoperabilität

- Verbindung zwischen CrypTool (PKCS#12) und PGP schaffen, indem man
  PGP-Keys in CrypTool verwenden kann. Idee: Per Passwort-Eingabe
  öffnet man seinen privaten Keyring, analysiert die Struktur, holt den
  Key heraus (PGP-Sourcen sind gegeben) und nutzt diesen, um mit den in
  CrypTool implementierten Verfahren PGP-Files zu entschlüsseln oder zu
  signieren. Damit wird klar, dass auch PGP die Standard-Algorithmen nutzt,
  die bspw. S/MIME einsetzt.

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



A.3.2. Funktionalität: Analyse
       -----------------------
- Nutzen von Distributed Computing zur Kryptoanalyse
- Anbieten eines Werkzeugkastens zur Kryptoanalyse (crytanalysis framework)
  zum Erlernen von schnellem Code-Brechen
- CT2  Framework zum Verteilen kryptoanalytischer Berechnungen
- CT2  Toolbox zum Erzeugen und Analysieren von Strom-Chiffren
- CT2  Framework zum Bau und zur Analyse von LFSR-Stromchiffren
- CT2  Framework zur Analyse von Seitenkanal-Angriffen

- Wünschenswert wäre, wenn insbesondere die Analyse in allen Formen und
  samt Visualisierung weiter ausgebaut werden könnte.

- Zu ALLEN implementierten Verschlüsselungsverfahren eine (gute) Analyse
  anbieten, die (zumindest für die klassischen Verfahren besser ist als
  Brute-Force), z.B. für
   - Nihilist
   - Turning Grille (Fleissner-Schablone)

- Angriff auf symmetrische Verschlüsselungsverfahren, bei denen die
  Parameter der Verschlüsselungsverfahren flexibel reduziert werden können.

- Differentielle Kryptoanalyse auf symmetrische Chiffren (DES, ...).

- Die Brute-Force-Möglichkeiten erweitern: Nutzen von Wissen
  - um Teile des Klartextes,
  - um Teile des Schlüssels.

- Demo, wie lange eine vollständige Schlüsselsuche dauert (in Abhängigkeit
  von der Schlüssellänge).

- Analyse neu implementieren für:
   * homophone Verschlüsselung
   * Permutationen/Transpositionen
      - Known-Plaintext-Analyse der doppelten Spaltentransposition,
      - Ciphertext-Only-Analyse des Doppelwürfels
   * Playfair-Verschlüsselung
      - C-Sourcen (Gunnar-Andresson) liegen uns vor.

- Analyse verbessern für:
   * monoalphabetische Substitution
      - explizite Anzeige von vertauschten Digrammen wie "ie"/"ei"
        und von Doppelzeichen wie "mm".
      - CT1: Ersetzte Buchstaben in der Dialogbox nicht nur groß, sondern
        auch in roter Schrift anzeigen.
   * Vigenère-Analyse noch weiter veranschaulichen:
      - Bei den Keylängen die Eingabe eines Bereiches statt eines Einzel-
        wertes ermöglichen (z.B. "2-9") und dann in der Folgemaske auch
        für jede Länge den statistisch wahrscheinlichen Schlüssel ausgeben.
        Evtl. die Top-10 wahrscheinlichsten Keys für eine bestimmte Länge
        anzeigen.
      - Per Klick auf einen der angezeigten Keys erhält man die jeweilige
        Entschlüsselung. Per Klick auf einen weiteren Button werden für
        alle Keys die Entschlüsselungen angeboten.
      - Mit der Analyseoption "Basischiffre anzeigen" werden z.Zt. pro
        Spalten-Caesar (d.h. bei einer ermittelten Schlüssellänge von
        n wird das Caesar-Verfahren für jeden Wert von i jeweils auf die
        Zeichenmenge m[i+k*n] mit 1<=i<=n und k>=0 angewandt) die
        Grafiken Korrelation und ASCII-Histogramm erstellt.
        Zusätzlich könnte man noch den Text des jeweiligen Spalten-
        Caesars ausgeben.

- Wörterbücher für alle Angriffe benutzen, nicht nur für die Substitution.

- Nutzung von Algorithmen aus dem Bereich KI (Künstliche Intelligenz) und
  GP/GA (Genetic Programming/Algorithms) zur automatischen Analyse
  (klassischer) Verschlüsselungsverfahren.

- CT2: Massenmustersuche: Erweiterte, hoch performante Mustersuche, die
  nach vorgegebenen normierten und regulären Mustern beliebiger Länge
  sucht (z.B. um alle Patterns in einer Datei zu finden, die auch in
  einer anderen (vorzugebenden) Datei vorkommen), oder die nach
  unbekannten, aber mehrfach vorkommenden Mustern in Dokumenten sucht.
  Könnte dann auch um Ersetzen erweitert werden.

- Korrekturmöglichkeit einzelner Zeichen bei der Analyse von XOR,
  ADD, Vigenère. Ausschluss unverschlüsselter Bereiche.

- Anzeigen des zweit-, dritt-, ... besten Treffers bei der XOR/ADD-Analyse
  (dies kann zu einer kürzeren Schlüssellänge führen).

- Autokorrelation: vor der Überlagerung noch Operationen auf den
  Blöcken ausführen (XOR, ADD, ...). Macht das Sinn?

- Editieren der Homophonen-Schlüssel (benötigt bei der Analyse
  der Homophonen Verschlüsselung)

- Gleitende Entropie: Automatisierte Suche von Stellen in einem Dokument
  mit hoher Entropie

- Vorhandene Einschränkungen in der N-Gramm-Analyse bzgl. Dateigröße
  ausdehnen (evtl. mit Benutzerfeedback und der Möglichkeit abzubrechen,
  wenn viel Zeit erforderlich).
- Timing Attack auf RSA / Vorteile Blinding

- Aktuelle Hashangriffe darstellen (z.B. Erstellen von PS-Dokumenten nach
  Lucks oder von PDF-Dokumenten nach BSI mit gleichem Hashwert) und
  Aufzeigen der Anwendungsszenarien.

- Nutzung von Rainbow-Tabellen

- Weitere Angriffe auf konkrete Protokolle implementieren und/oder
  visualisieren, um zukünftige Konzepte zu verbessern.



A.3.3. Interne Schnittstellen / Editoren
       ---------------------------------
- Alle benutzten Schlüssel in einem Container speichern.
  Alle Schlüssel der unterschiedlichen Verschlüsselungsverfahren in einem
  Dialog anzeigen.
  Abspeichern permanent als Datei in einem Format, das für alle CrypTool-
  Versionen gemeinsam ist.

- In den Nachfolger-Projekten von CT1: Ausgabe/Anzeige komplett von
  den Kryptomodulen trennen (dies erleichtert Portierungen und Fehlersuche).

- Parametrisierung, wo immer das möglich ist:
  Anbieten einer Option, um z.B. den Initialisierungsvektor,
  die Anzahl von Runden, die Schlüssel- oder Wortlänge oder
  das Padding zu setzen (z.B. für den RC5-Algorithmus - siehe RFC 2040).
  Diese Parameter müssen dann auch in das Format für den internen
  Schlüsselspeicher aufgenommen werden.

- Langzahl- und Krypto-Bibliotheken:
   - Unterstützung weiterer Libraries (FLINT/C, Wei Dai's Crypto++, ...).

- JCT  Commandline-Funktionalität (für Benutzer und Test-Automatisierung)



A.3.4. User-Interface / Visualisierungen
       ---------------------------------
Die folgenden Vorschläge beziehen sich meist auf CT1. Ähnliche Anforderungen
betreffen aber all Krypto-Programme mit einer GUI.

- In den Dialogen in CT1 können Zahlen nicht immer in allen
  Darstellungsarten eingegeben werden (z.B. kann im Dialog
  RSA-Kryptosystem die zu verschlüsselnde Nachricht als Text mit frei
  einzustellendem Alphabet und als Zahl mit 4 verschiedenen Basen)
  eingegeben werden; die Primzahlen dagegen kann man "nur" als Zahl
  im Zehnersystem bzw. als Ausdrücke mit Zahlen im Zehnersystem
  eingeben). Alternative wäre ein amodales Umrechnungsdialog-Fenster.

- Nützlich wäre es, wenn man aus CrypTool heraus einen Taschenrechner
  als amodales Fenster aufmachen könnte, der Terme mit Zahlen
  beliebiger Basis als Eingabe nimmt und die Ausgabe in mehreren
  Feldern in verschiedenen Zahlensystemen parallel anzeigt. Von hier
  aus sollte man dann die Zahlen per Knopfdruck ins Clipboard bringen
  können oder per Maus in die Eingabefelder der CrypTool-Dialogboxen
  ziehen können.

- Weiterhin wäre eine interaktive Anbindung an das CAS-System SageMath
  interessant (http://www.sagemath.org/).

- Generelle Visualisierung der entsprechenden mathematischen Grundlagen, z.B.:
  - anhand eines Lehrbuchs
  - wie mit den Sage-Notebooks zur Einführung in ECC von Maike Massierer:
      - http://web.maths.unsw.edu.au/~maikemassierer/ecc-notebook
        (Version 1.3, Januar 2011) (xxx)
    Teil 0, das Deckblatt enthält keine Berechnungen, sondern nur die Links
    zu den übrigen Teilen; zum Ausführen der folgenden Teile muss man sich
    selbst Kopien als Sage-User anlegen.
  - wie die PascGalois Software (Group Calculator)
      - http://www.pascgalois.org/software.html
  - http://www.martindalecenter.com/Calculators2_6_NZ.html
  - http://world.std.com/~reinhold/BigNumCalc.html
  - http://mathforum.org/library/resource_types/calculators/?keyid=28652723&start_at=301&num_to_see=50
  - http://www.hbmeyer.de/pythagen.htm (Pythagorean Triples)

- CT1: Für den Benutzer konfigurierbar einstellbar machen, ob neue Fenster
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
  Schlüssel die verschiedenen Algorithmen erwarten: Bei den
  klassischen Verfahren besteht der Schlüssel oft aus Elementen des
  zugrunde liegenden Alphabets, bei den modernen symmetrischen Verfahren
  sind es Binärdaten von 56 Bit bis 256 Bit Länge.
  Andererseits sind es Benutzer gewohnt, ihre Eingaben per ASCII-Zeichen
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
  CT1: Ab AES-Tool 2.6 (ausgeliefert mit CT 1.4.31) kann man die Schlüssel
  auch in ASCII-Form eingeben. Die ASCII-Zeichen werden dann per PKCS#5
  transformiert. 

- Für den Benutzer konfigurierbar einstellbar machen, wie groß die
  Teile von Text- und Binärdateien sein können, die CrypTool laden kann.

- In der Anzeige für Grafiken eine Vergrößerungsfunktion einbauen
  und / oder die Koordinaten anzeigen, an denen sich die Maus befindet.

- CT1: Alle Dialoge thread-safe machen, damit man Langläufer abbrechen kann,
  ohne das ganze Programm per Task-Manager zu beenden.
  Implementiert ist dies schon z.B. im Faktorisierungs-Dialog.
  Dies ist insbesondere bei der Kryptoanalyse sinnvoll (z.B. wäre es nötig
  bei der Known-Plaintext-Analyse der einstufigen Spaltentransposition):
  Bei unbeschränkter Obergrenze der Permutationslänge dauerte es ab 900
  "ewig". Hier wurde es dann aus Konsistenzgründen auf 100 beschränkt,
  weil auch die Permutations-Verschlüsselung keine längeren Permutationen
  zuließ.

- Visualisierung:
   - Generell ist die Visualisierung der Abhängigkeiten und Abläufe bei
     Protokollen (nicht nur bei "einfachen" Algorithmen) eine sinnvolle
     Erweiterung.
   - Angriffe auf schwache RSA-Schlüssel sind in der CT1-Onlinehilfe
     beschrieben: Siehe Menü Hilfe \ Szenarien (Tutorials) \
     RSA-Kryptosystem (Demonstration), unter dem Abschnitt
     "3. Angriff auf das RSA-Verfahren", wo erklärt wird, dass die
     Faktorisierung des Moduls das Verfahren knacken kann.
     Dies ist implementiert, aber nicht visualisiert.
   - Angriffe auf andere asymmetrische Verfahren sind in CrypTool
     bisher noch gar nicht behandelt. Um Diffie-Hellman, DSA oder
     EC-DSA anzugreifen, muss man "diskrete Logarithmen" berechnen.
     Auch dies könnte man nach dem Implementieren wieder visualisieren.
   - Avalanche-Effekt zeigen bei Hash- oder Verschlüsselungsverfahren.



A.4. CT1 unter Linux
     ---------------

A.4.1. Ausführen von CT1 unter Linux mit Wine
       --------------------------------------
Bei einem kurzen Test mit Wine 1.8.0 unter MINT 17.3 im Oktober 2016 lief das
Setup von CrypTool 1.4.31 Prefinal (compiliert mit VS2008) ok durch.

Die meisten Funktionen in CT1 selbst (wie Verschlüsselungsmethoden oder
RSA-Schlüsselgenerierung) sind ausführbar unter Wine. Wine ist viel stabiler
als vor 6 Jahren.
- ok:  Aufruf der meisten Masken (incl. RSA-AES-Hybrid-Verschlüsselungs-Demo),
       Durchführen der Berechnungen und Klick auf F1 (Kontext-sensitive Hilfe)
- ok:  Melden, wenn Java nicht in Wine installiert ist
- ok:  Aus CT1, per Menü Hilfe das Readme in IE anzeigen
- nok: Aus CT1, per Menü Hilfe ein PDF (Buch, Präsentation) starten:
       Wine sucht vergeblich nach dem Acrobat Reader, auch wenn Okular
       und Acrobat vorhanden sind.
- ok:  In der Onlinehilfe: Aufruf innerer Links in der Hilfe
- nok: In der Onlinehilfe:
       - Aufruf von externen Programmen aus der Hilfe (Readme.txt im Notepad,
         PDFs)
       - Vor- und Zurück-Button
- nok: Fehlfunktionen innerhalb der Macromedia-Anwendung ZT

Wir unternehmen keine extra Anstrengungen, Wine zu unterstützen.
Stattdessen empfehlen wir, die plattformunabhängige Version JCT zu benutzen,
die auch unter Linux läuft (siehe Kapitel 3.5).


A.4.2. Portierung von CT1 nach Linux mit Qt
       ------------------------------------
Eine erste Portierung von CrypTool 1.x nach Linux mit Hilfe von GCC 4.x und
Qt 4.x war außerhalb des eigentlichen CrypTool-Projektes von Einzelpersonen
begonnen worden, aber mangels Zeit nicht/wenig fortgesetzt worden (früher
unter http://www.cryptoolinux.net/).
- Die Bibliotheken von Miracl, NTL, OpenSSL und GMP/MPIR stehen
  zur Verfügung.
- Die Gesamtaufgabe sollte man in sinnvolle Teile zerlegen:
       - Oberfläche: Hier liegt die Hauptarbeit.
       - Funktionalität, implementiert in purem C/C++: ok
       - Online-Hilfe in HTML: ok.
- Die erste Beta wurde im November 2007 veröffentlicht.
  Die zweite Beta ("still no functional version", 11 % der geplanten
  Aufgaben) wurde am 15.12.2008 veröffentlicht.
- Dieses Projekt ist beendet.

Nichtsdestotrotz wird das CT1-Kernteam einen Nachfolger von CT1 mit Qt 5
bauen, der dasselbe Look&Feel wie CT1 hat und QCT genannt wird
(siehe A.1 Roadmap nach CT 1.4.31).


################################################################

Bitte probieren Sie auch die neuen Versionen CT2 und JCT.
Sie finden diese ebenfalls auf der Webseite  www.cryptool.org  

Eintrag in der Wikipedia: https://de.wikipedia.org/wiki/CrypTool

