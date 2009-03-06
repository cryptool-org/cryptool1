package eccdemo;
class Texte
{
	static String frameTitleFr;
	static String frameTitleFp;
	String titel, text1,text2,text3,text4,text5,text6,text7;
	String text8,text9,text10,text11,text12,text13,text14;
	String text15,text16,text17;
	String labelSpace,buttonFr, buttonFp, buttonLog, buttonDelete;
	String p1, p2, p3, p4, p5;
	String q1,q2,q3;
	String rp1, rp2,rp3,rp4,rp5,rp6;
	String rpq1,rpq2,rpq3,rpq4;
	String rAus2PNaN1,rAus2PNaN2,rAus2PNaN3;
	String rAusPQNaN1,rAusPQNaN2,rAusPQNaN3;
	//finite number space
	String frp1, frp2,frp3,frp4,frp5,frp6;
	String frpq1,frpq2,frpq3,frpq4;
	String frAus2PNaN1,frAus2PNaN2,frAus2PNaN3;
	String frAusPQNaN1,frAusPQNaN2,frAusPQNaN3;
	String graph1, graph2, graph3;
	//Log-File
	String logTitle, logCurve;
	String logFrNumberSpace;
	String logFpNumberSpace;
	//Help-Dialog
	String helpTitle;
	String helpButton;
	static String pointsText;
	
	Texte (int sprache)
	{
		if(sprache==0)//deutsch
		{
			Texte.frameTitleFr="ECC-Demo 1.1: Punktaddition auf Elliptischen Kurven über den reellen Zahlenraum R";
			Texte.frameTitleFp="ECC-Demo 1.1: Punktaddition auf Elliptischen Kurven über diskreten Gruppen Fp";
			//long title with authors
			//this.frameTitle="Punktaddition auf Elliptischen Kurven                                                                                           © D.Laupichler, M.Kraft 2005";
			this.helpButton="Hilfe";
			Texte.pointsText="Punkte:";
			this.labelSpace="Wählen Sie den Zahlenraum";
			this.buttonFr="Reeller Zahlenraum R";
			this.buttonFp="Diskrete Gruppe über Fp";
			this.buttonLog="Log-Datei";
			this.buttonDelete="Lösche Punkte";
			this.titel="_______________________________________";
			this.text1="Dieses Programm visualisiert verschiedene";
			this.text2="Elliptische Kurven und ermöglicht es,";
			this.text3="Punktadditionen auf diesen durchzuführen.";
			this.text4="Die Kurven können entweder über dem Zahlenraum";
			this.text5="der reellen Zahlen oder über der diskreten Gruppe";
			this.text6="über Primzahlen zwischen 3 und 97 erzeugt werden.";
			this.text7="Die Kurvenparameter a und b können Sie mit";
			this.text8="den Reglern verändern.";
			this.text9="";
			this.text10="Nachdem Sie eine Kurve ausgewählt haben,";
			this.text11="legen Sie durch Klick mit der linken Maustaste";
			this.text12="einen Punkt auf der Kurve fest! In der Grafik";
			this.text13="wird Ihnen jeweils der Punkt rot angezeigt, der";
			this.text14="Ihrem Mauszeiger am nächsten ist.";
			this.text15="";
			this.text16="";
			this.text17="";
			
			this.p1="Sie haben einen Punkt P auf der Kurve";
			this.p2="ausgewählt. Sie können nun den Punkt";
			this.p3="mit dem Button '2*P' zu sich selbst addieren,";
			this.p4="oder einen weiteren Punkt auswählen.";
			
			this.q1="Sie haben jetzt einen Punkt P und einen Punkt Q";
			this.q2="auf der Kurve gewählt. Mit dem Button 'P+Q'";
			this.q3="können Sie die beiden Punkte addieren.";
			
			this.rp1="Die Tangente an den Punkt P schneidet die";
			this.rp2="Kurve im Punkt -R. Die Spiegelung von -R an der";
			this.rp3="x-Achse ist der Punkt R.";
			this.rp4="R ist das Ergebnis der Punktaddition von P.";
			this.rp5="Durch erneutes Drücken des Buttons können Sie";
			this.rp6="die Punktaddition mit dem Punkt P fortsetzen.";
			
			this.rpq1="Die Gerade durch die Punkte P und Q schneidet";
			this.rpq2="die Kurve im Punkt -R. Die Spiegelung von -R";
			this.rpq3="an der x-Achse ist der Punkt R.";
			this.rpq4="R ist das Ergebnis der Addition von P und Q.";
			
			this.rAus2PNaN1="Die Tangente an den Punkt P hat keinen weiteren";
			this.rAus2PNaN2="Schnittpunkt mit der Kurve.";
			this.rAus2PNaN3="Der Punkt R ist der Punkt im Unendlichen O.";
			
			this.rAusPQNaN1="Die Gerade durch die Punkte P und Q hat keine";
			this.rAusPQNaN2="weiteren Schnittpunkte mit der Kurve.";
			this.rAusPQNaN3="Der Punkt R ist der Punkt im Unendlichen O.";
			
			//finite number space
			this.frp1="Die Verdopplung des Punktes P ergibt den";
			this.frp2="Punkt R.";
			this.frp3="Durch erneutes Drücken des Buttons können Sie";
			this.frp4="die Punktaddition mit dem Punkt P fortsetzen.";
			this.frp5="Eine Erläuterung des mathematischen Verfahrens";
			this.frp6="finden Sie in der Hilfe zu dieser Demo.";
			
			this.frpq1="Die Addition der Punkte P und Q ergibt den";
			this.frpq2="Punkt R.";
			this.frpq3="Eine Erläuterung des mathematischen Verfahrens";
			this.frpq4="finden Sie in der Hilfe zu dieser Demo.";
			
			this.frAus2PNaN1="Das Ergebnis der Verdopplung des Punktes P";
			this.frAus2PNaN2="ist der Punkt im Unendlichen O, welcher sich";
			this.frAus2PNaN3="nicht im Koordinatensystem darstellen lässt.";
			
			this.frAusPQNaN1="Das Ergebnis der Addition der Punkte P und Q";
			this.frAusPQNaN2="ist der Punkt im Unendlichen O, welcher sich";
			this.frAusPQNaN3="nicht im Koordinatensystem darstellen lässt.";
			
			this.graph1=" mit ";
			this.graph2=" über ";
			this.graph3=" Punkten.";
			
			//log file
			this.logTitle="Log-Datei: Punktaddition auf Elliptischen Kurven";
			this.logFrNumberSpace="----- Berechnung im reellen Zahlenraum R -----\n\n";
			this.logFpNumberSpace="----- Berechnung in der diskreten Gruppe Fp mit p = ";
			this.logCurve="Gewählte Kurve:\n";
			
			this.helpTitle="Hilfe";
			
		}
		
		if(sprache==1)//english
		{
			Texte.frameTitleFr="ECC Demonstration 1.1: Point addition on elliptic curves over the real number space R";
			Texte.frameTitleFp="ECC Demonstration 1.1: Point addition on elliptic curves over discrete groups of prime numbers";	
			//long title with authors
			//this.frameTitle="Point addition over elliptic curves                                                                                             © D.Laupichler, M.Kraft 2005";
			this.helpButton="Help";
			Texte.pointsText="Points:";
			this.labelSpace="Choose the number space";
			this.buttonFr="Real number space R";
			this.buttonFp="Discrete group over Fp";
			this.buttonLog="Logfile";
			this.buttonDelete="Delete points";
			this.titel="_______________________________________";
			this.text1="This program allows you to generate various";
			this.text2="elliptic curves and to carry out point additions";
			this.text3="on these curves.";
			this.text4="As number spaces you can use the real numbers";
			this.text5="or groups over the prime numbers ranging";
			this.text6="from 3 to 97.";
			this.text7="The curve parameters a and b can be changed";
			this.text8="through the scrollbars.";
			this.text9="";
			this.text10="After choosing an elliptic curve, you can";
			this.text11="select points on this curve by clicking on it";
			this.text12="with the left mouse button. A red dot on the";
			this.text13="curve indicates the valid point that is closest";
			this.text14="to the current mouse position.";
			this.text15="";
			this.text16="";
			this.text17="";
			
			this.p1="You have chosen a point P on the curve.";
			this.p2="You can now add the point to itself by";
			this.p3="clicking the button '2*P' or choose";
			this.p4="another point.";
			
			this.q1="You now have chosen two points P and Q";
			this.q2="on the curve. By clicking the button 'P+Q',";
			this.q3="you can add the two points.";
			
			this.rp1="The tangent of the point P intersects";
			this.rp2="the curve at the point -R. The mirroring";
			this.rp3="at the x-axis is the point R.";
			this.rp4="R is the result of the point addition of P.";
			this.rp5="By clicking the button again, you can continue";
			this.rp6="the point addition with the point P.";
			
			this.rpq1="The straight line through the points P and Q";
			this.rpq2="intersects the curve at the point -R. The";
			this.rpq3="mirroring at the x-axis is the point R.";
			this.rpq4="R is the result of the addition of P and Q.";
			
			this.rAus2PNaN1="The tangent of the point P has no other";
			this.rAus2PNaN2="intersection with the curve.";
			this.rAus2PNaN3="The point R is the point at infinity O.";
			
			this.rAusPQNaN1="The straight lint through the points P and";
			this.rAusPQNaN2="Q has no other intersection with the curve.";
			this.rAusPQNaN3="The point R is the point at infinity O.";	
			
			//finite number space
			this.frp1="Doubling the point P results in the point R";
			this.frp2="By clicking the button again, you can continue";
			this.frp3="the point addition with the point P.";
			this.frp4="";
			this.frp5="An explanation of the mathematical procedure";
			this.frp6="can be found in the help texts of this program.";
			
			this.frpq1="The addition of the points P and Q results";
			this.frpq2="in the point R.";
			this.frpq3="An explanation of the mathematical procedure";
			this.frpq4="can be found in the help texts of this program.";
			
			this.frAus2PNaN1="The result of the doubling of the point P";
			this.frAus2PNaN2="is the point at infinity O which is not";
			this.frAus2PNaN3="drawable on the grid.";
			
			this.frAusPQNaN1="The result of the addition of P and Q";
			this.frAusPQNaN2="is the point at infinity O which is not";
			this.frAusPQNaN3="drawable on the grid.";

			this.graph1=" with ";
			this.graph2=" over ";
			this.graph3=" points.";
			
			//log file
			this.logTitle="Point addition over Elliptic Curves";
			this.logFrNumberSpace="----- Calculation in the real number space R -----\n\n";	
			this.logFpNumberSpace="----- Calculation in the discrete group Fp with p = ";
			this.logCurve="Selected curve:\n";
			
			this.helpTitle="Help";
			
		}
	}
}

