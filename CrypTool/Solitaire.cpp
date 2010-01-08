#include "Solitaire.h"
#include "assert.h"


void Deck::setkartenanzahl(int anzahlkarten)
{
	this->anzahl = anzahlkarten;
}


	// Aufsteigend sortiertes Kartendeck
Deck::Deck(int anzahlkarten) :
	posA(0), 
	posB(0)
{
	anzahl=anzahlkarten;		
	for (char i=0;i<anzahl;i++)
		deck[i]=i+1;
}

void Deck::aufsteigend()
{
	for (char i=0;i<anzahl;i++)
		deck[i]=i+1;
}

CString Deck::getDeck()
{
	CString uebergabe;
	CString c;
	for (int i=0;i<anzahl;i++)
	{						
		c.Format("%i",deck[i]);
		uebergabe +=c;
		uebergabe += ",";
	}
	uebergabe.Delete(uebergabe.GetLength()-1);
	return uebergabe;
}

CString Deck::getKey()
{
	CString uebergabe;
	CString c;
	for (int i=0;i<plaintext.GetLength();i++)
	{					
		c.Format("%i",key[i]);
		uebergabe +=c;
		uebergabe += ",";
	}
	uebergabe.Delete(uebergabe.GetLength()-1);
	return uebergabe;
}

CString Deck::getDeckChar(int zaehler)
{
	CString uebergabe;
    CString c;
	for (int i=0;i<zaehler;i++)
	{
		c.Format("%i",deck[i]);
		uebergabe +=c;
		uebergabe += ",";
	}
	uebergabe.Delete(uebergabe.GetLength()-1);
	return uebergabe;
}

CString Deck::getKeyChar(int zaehler)
{
	CString uebergabe;
    CString c;
	for (int i=0;i<zaehler;i++)
	{
		c.Format("%i",key[i]);
		uebergabe +=c;
		uebergabe += ",";
	}
	uebergabe.Delete(uebergabe.GetLength()-1);
	return uebergabe;
}

// gibt Deck-Array aus
void Deck::print()
{
	printf("\n");
	for (char i=0;i<anzahl;i++)
	{
		//d is for out-type
		printf("%d",deck[i]);
		printf(",");
	}
	printf("%s","\n\n");
}

void Deck::absteigend()
{
	temp=anzahl;
	for (char i=0;i<anzahl;i++)
	{
		deck [i]=temp;
		temp--;
	}
}


//mischt Array durcheinander
void Deck::mischen()
{		
    for (int i=0; i<anzahl; i++) 
	{
		// eine zufällige Position generieren
        int r = rand() % anzahl;  
		// deck[i] wird vertauscht mit zufälliger Zahl
		int temp = deck[i]; deck[i] = deck[r]; deck[r] = temp;
    }
}


void Deck::schritt1()  
{	
	int temp;

	if (deck[anzahl-1]==anzahl-1)
	{
		temp = deck[anzahl-1];
		for(char j=anzahl-2; j>0; j--)
		{
			deck[j+1]=deck[j];	
		}
		deck[1] = temp;
	}
	else
	{	
		for (char i=0;i<=anzahl-2;i++)
			//wenn Joker nicht letzter
			if(deck[i]==anzahl-1)
			{				
				temp = deck[i]; 
				deck[i] = deck[i+1];
				deck[i+1] =temp;
				break;
			}
	}
}

void Deck::schritt2()  
{
	int temp;
	
	if(deck[anzahl-2]==anzahl)
	{
		temp = deck[anzahl-2];
		for(char j=anzahl-3; j>0; j--)
		{
			deck[j+1]=deck[j];	
		}
		deck[1] = temp;				
	}
	else if (deck[anzahl-1]==anzahl)
	{
		temp = deck[anzahl-1];
		for(char k=anzahl-2; k>1; k--)
		{
			deck[k+1]=deck[k];	
		}
		deck[2] = temp;
	}
	else
	{
		for (char i=0;i<=anzahl-3;i++)
			if(deck[i]==anzahl)
			{				//wenn Joker nicht letzter und nicht vorletzter ist
				temp = deck[i];
				deck[i] = deck[i+1];
				deck[i+1]=deck[i+2];
				deck[i+2]=temp;
				break;
			}
	}
}


/*
3. Führe ein dreigeteiltes Abheben durch. Das heißt, vertausche die Karten vor dem 
ersten Joker mit denen nach dem zweiten Joker. Sah das Spiel vorher so aus:

2 4 6 B 5 8 7 1 A 3 9

so wird es nach dem dreigeteilten Abheben so aussehen:

3 9 B 5 8 7 1 A 2 4 6

"Erster" und "zweiter" Joker bezeichnet hier den Joker der näher zur, bzw. 
entfernter von der obersten Karte liegt. Die Namen "A" und "B" werden in diesem 
Schritt ignoriert. Beachte, daß die Joker, und die Karten dazwischen sich nicht 
bewegen; die anderen Karten bewegen sich darum herum. Das kann man einfach in den 
Händen machen. Sollte in einer der drei Abschnitte keine Karte sein (entweder 
liegen die Joker direkt nebeneinander, oder einer ist selbst die oberste oder 
unterste Karte), nimmt man einfach an, dieser Abschnitt sei leer, und bewegt ihn 
trotzdem.
*/

void Deck::schritt3()
{
	char temp[54];
	int i;

	for ( i=0;i<anzahl;i++)
	{			
		if (deck[i]==anzahl)
			{posB=(char)i;}
		if (deck[i]==anzahl-1)
			{posA=(char)i;}
	}

	if (posA>posB)
	{
		min = posB;
		max = posA;
	}
	else 
	{
		min = posA;
		max = posB;
	}
	
	memcpy(temp,deck,anzahl);
	char k=0;
	for(i=max+1;i<anzahl;i++)
	{
		deck[k]=temp[i];
		k++;
	}

	k=anzahl-max;
	for(i=min+1;i<=max+1;i++)
	{
		deck[k-1]=temp[i-1];
		k++;
	}

	//k=54-max+(54-(54-max)-min);
	k=anzahl-min;
	for(i=0;i<min;i++)
	{
		deck[k]=temp[i];
		k++;
	}
}

void Deck::schritt4()
{
	// temporaeres Hilfsdeck
	char tempdeck[54];

	// Hilfvariable a bekommt den Wert der letzten Karte im deck
	char a = deck[anzahl-1];

	// falls JokerB die letzte Karte ist, a um eins verringern
	if(a==anzahl) a=a-1;

	// tempdeck wird mit den Werten von deck belegt
	for(char i=0; i<anzahl; i++)
		tempdeck[i]=deck[i];
	
	/* 1. Teil des Zaehlabhebens, abgezaehlter Block
	 wird an die entsprechende Stelle in deck geschrieben
	 k ist Hilfvariable für die Schleife,
	 anzahl-1-a entspricht 53-a-(54-anzahl)*/
	char k = 0;
	for(char j=anzahl-1-a; j<anzahl-1; j++)
	{
		deck[j]=tempdeck[k];
		k++;
	}

	/* 2. Teil des Zaehlabhebens, Mittelblock wird an den 
	 Anfang von deck geschrieben,
	 k ist Hilfvariable für die Schleife,
	 anzahl-1-a entspricht 53-a-(54-anzahl)*/
	k=a;
	for(char l=0; l<anzahl-1-a; l++)
	{
		deck[l]=tempdeck[k];
		k++;
	}
}

char Deck::schritt5()
{
	// der Wert der obersten Karte
	char a = deck[0];

	if (a == anzahl)
		a-=1;

	if (deck[a] == anzahl || deck[a] == (anzahl-1))
		return -1;
	else
		return deck[a];
}

char Deck::schritt5ohneJokerAusgabe()
{
	// der Wert der obersten Karte
	char a = deck[0];

	if (a == anzahl)
		a-=1;

	//Joker gefunden
	if (deck[a] == anzahl || deck[a] == (anzahl-1))
	{
		while(pruefenullrunde()==true)
		{
			schritt1();
			schritt2();
			schritt3();
			schritt4();
		};
	}
    
	a = deck[0];
	if (a == anzahl)
		a-=1;

	return deck[a];
}

bool Deck::pruefenullrunde()
{
	//anzahlnullrunden=0;
	char a = deck[0];
	if (a == anzahl)
		a-=1;

	if (deck[a] == anzahl || deck[a] == (anzahl-1))
		return true;
	else
		return false;

}

int Deck::nullrunde()
{
	char d = deck[0];
	anzahlnullrunden++;
	schritt1(); 
	schritt2();
	schritt3();
	schritt4();
	if (deck[d] == anzahl || deck[d] == (anzahl-1))
		nullrunde();
	return anzahlnullrunden;
}


void Deck::schritt1revers()  
{	
	int temp;
	
	//wenn Joker an erster Stelle
	if (deck[0]==anzahl-1)
	{	
		temp = deck[0];
		for(char j=0; j<anzahl-2; j++)
		{
			deck[j]=deck[j+1];
		}
		deck[anzahl-2] = temp;
	}
	else /* Hier muss eine Abfrage kommen wenn Joker A an zweiter Stelle steht. 
		 An welcher Stelle soll der Joker positioniert werden, vorn oder hinten */ 
	{
		for (char i=1;i<=anzahl-1;i++)
		{	
			//wenn Joker A nicht erster
			if(deck[i]==anzahl-1)
			{				
				temp = deck[i]; 
				deck[i] = deck[i-1];
				deck[i-1] =temp;
				break;
			}
		}
	}
}

bool Deck::schritt1reversabfrage()  
{	
	int temp;
	
	//wenn Joker an erster Stelle
	if (deck[0]==anzahl-1)
		{	
			temp = deck[0];
			for(char j=0; j<anzahl-2; j++)
			{
				deck[j]=deck[j+1];
			}
			deck[anzahl-2] = temp;
			return false;
		}
	else if(deck[1]==anzahl-1)/* mit Abfrage der Jokerposition*/
	{
		return true;
	}
	else 
	{
		for (char i=2;i<=anzahl-1;i++)
		{	
			//wenn Joker A nicht erster
			if(deck[i]==anzahl-1)
			{				
				temp = deck[i]; 
				deck[i] = deck[i-1];
				deck[i-1] =temp;
				return false;
			}		
		}
	}
	return true; // CHECKME
}

void Deck::vorneeinordnena()
{
	char temp = deck[1]; 
	deck[1] = deck[0];
	deck[0] =temp;
}

void Deck::hinteneinordnena()
{
	char temp = deck[1];
	for(char k=1; k<=anzahl-2; k++)
		deck[k]=deck[k+1];
	deck[anzahl-1] = temp;
}

void Deck::schritt1reversvorne()  
{	
	int temp;
	
	//wenn Joker A an erster Stelle
	if (deck[0]==anzahl-1)
	{	
		temp = deck[0];
		for(char j=0; j<anzahl-2; j++)
		{
			deck[j]=deck[j+1];
		}
		deck[anzahl-2] = temp;
	}
	else /* Joker A wird immer vorne einsortiert */ 
	{
		for (char i=1;i<=anzahl-1;i++)
		{	
			//wenn Joker A nicht erster
			if(deck[i]==anzahl-1)
			{				
				temp = deck[i]; 
				deck[i] = deck[i-1];
				deck[i-1] =temp;
				break;
			}
		}
	}
}

void Deck::schritt1revershinten()  
{	
	int temp;
	
	//wenn Joker A an erster Stelle
	if (deck[0]==anzahl-1)
	{	
		temp = deck[0];
		for(char j=0; j<anzahl-2; j++)
		{
			deck[j]=deck[j+1];
		}
		deck[anzahl-2] = temp;
	}
	// Joker A an zweiter Stelle, hinten positionieren
	else if (deck[1]==anzahl-1)
	{
		temp = deck[1];
		for(char k=1; k<=anzahl-2; k++)
		{
			deck[k]=deck[k+1];
		}
		deck[anzahl-1] = temp;
	}
	else 
	{
		for (char i=2;i<=anzahl-1;i++)
		{	
			//wenn Joker A nicht erster und nicht zweiter
			if(deck[i]==anzahl-1)
			{				
				temp = deck[i]; 
				deck[i] = deck[i-1];
				deck[i-1] =temp;
				break;
			}
		}
	}
}

void Deck::schritt2revers()  
{
	int temp;
	
	//wenn Joker B zweite Karte
	if(deck[1]==anzahl)
	{
		temp = deck[1];
		for(char j=1; j<anzahl-2; j++)
			deck[j]=deck[j+1];	
		deck[anzahl-2] = temp;				
	}
	//wenn Joker B erste Karte ist
	else if (deck[0]==anzahl)
	{
		temp = deck[0];
		for(char k=0; k<anzahl-3; k++)
			deck[k]=deck[k+1];	
		deck[anzahl-3] = temp;
	}
	else /* Hier muss eine Abfrage kommen wenn Joker B an dritter Stelle steht. 
		 An welcher Stelle soll der Joker positioniert werden, vorn oder hinten */ 
	{
		for (char i=2;i<=anzahl-1;i++)
		{	
			//wenn Joker nicht erster und nicht zweiter ist
			if(deck[i]==anzahl)
			{				
				temp = deck[i];
				deck[i] = deck[i-1];
				deck[i-1]=deck[i-2];
				deck[i-2]=temp;
				break;
			}
		}
	}
}

bool Deck::schritt2reversabfrage()  
{
	int temp;
	
	//wenn Joker B zweite Karte
	if(deck[1]==anzahl)
	{
		temp = deck[1];
		for(char j=1; j<anzahl-2; j++)
			deck[j]=deck[j+1];	
		deck[anzahl-2] = temp;				
		return false;
	}
	//wenn Joker B erste Karte ist
	else if (deck[0]==anzahl)
	{
		temp = deck[0];
		for(char k=0; k<anzahl-3; k++)
			deck[k]=deck[k+1];	
		deck[anzahl-3] = temp;
		return false;
	}
	else if(deck[2]==anzahl)/* mit Abfrage der Jokerposition*/
		return true;
	else for (char i=3;i<=anzahl-1;i++)
	{	
		//wenn Joker nicht erster und nicht zweiter ist
		if(deck[i]==anzahl)
		{				
			temp = deck[i];
		    deck[i] = deck[i-1];
			deck[i-1]=deck[i-2];
			deck[i-2]=temp;
			return false;
		}
	}

	return true; // CHECKME
}


void Deck::vorneeinordnenb()
{	
	char temp = deck[2];
	deck[2] = deck[1];
	deck[1]=deck[0];
	deck[0]=temp;
				
}

void Deck::hinteneinordnenb()
{
	char temp =deck[2];
	for(char l=2; l<anzahl-1;l++)
		deck[l]=deck[l+1];
	deck[anzahl-1]=temp;
}


void Deck::schritt2reversvorne()  
{
	int temp;
	
	//wenn Joker B zweite Karte
	if(deck[1]==anzahl)
	{
		temp = deck[1];
		for(char j=1; j<anzahl-2; j++)
			deck[j]=deck[j+1];	
		deck[anzahl-2] = temp;				
	}
	//wenn Joker B erste Karte ist
	else if (deck[0]==anzahl)
	{
		temp = deck[0];
		for(char k=0; k<anzahl-3; k++)
			deck[k]=deck[k+1];	
		deck[anzahl-3] = temp;
	}
	else /* wenn Joker B dritte Karte ist, vorne einsortieren */ 
	{
		for (char i=2;i<=anzahl-1;i++)
		{	
			//wenn Joker B nicht erster und nicht zweiter ist
			if(deck[i]==anzahl)
			{				
				temp = deck[i];
				deck[i] = deck[i-1];
				deck[i-1]=deck[i-2];
				deck[i-2]=temp;
				break;
			}
		}
	}
}

void Deck::schritt2revershinten()  
{
	int temp;
	
	//wenn Joker B zweite Karte
	if(deck[1]==anzahl)
	{
		temp = deck[1];
		for(char j=1; j<anzahl-2; j++)
			deck[j]=deck[j+1];	
		deck[anzahl-2] = temp;				
	}
	//wenn Joker B erste Karte ist
	else if (deck[0]==anzahl)
	{
		temp = deck[0];
		for(char k=0; k<anzahl-3; k++)
			deck[k]=deck[k+1];	
		deck[anzahl-3] = temp;
	}
	else if (deck[2]==anzahl)/* wenn Joker B dritte Karte, hinten einsortieren*/
	{
		temp =deck[2];
		for(char l=2; l<anzahl-1;l++)
			deck[l]=deck[l+1];
		deck[anzahl-1]=temp;
	}
	else
	{
		for (char i=3;i<=anzahl-1;i++)
		{	
			//wenn Joker nicht erster und nicht zweiter und nicht dritter ist
			if(deck[i]==anzahl)
			{				
				temp = deck[i];
				deck[i] = deck[i-1];
				deck[i-1]=deck[i-2];
				deck[i-2]=temp;
				break;
			}
		}
	}

}


void Deck::schritt3revers()
{
	char temp[54];
	int i;

	for ( i=0;i<anzahl;i++)
	{			
		if (deck[i]==anzahl)
			posB=(char)i;
		if (deck[i]==anzahl-1)
			posA=(char)i;
	}

	if (posA>posB)
	{
		min = posB;
		max = posA;
	}
	else 
	{
		min = posA;
		max = posB;
	}
	
	memcpy(temp,deck,anzahl);
	char k=0;
	for(i=max+1;i<anzahl;i++)
	{
		deck[k]=temp[i];
		k++;
	}

	k=anzahl-max;
	for( i=min+1;i<=max+1;i++)
	{
		deck[k-1]=temp[i-1];
		k++;
	}

	//k=54-max+(54-(54-max)-min);
	k=anzahl-min;
	for( i=0;i<min;i++)
	{
		deck[k]=temp[i];
		k++;
	}
}


void Deck::schritt4revers()
{
	// temporaeres Hilfsdeck
	char tempdeck[54];

	// Hilfvariable a bekommt den Wert der letzten Karte im deck
	char a = deck[anzahl-1];

	// falls JokerB die letzte Karte ist, a um eins verringern
	if(a==anzahl) a=a-1;

	// tempdeck wird mit den Werten von deck belegt
	for(char i=0; i<anzahl; i++)
		tempdeck[i]=deck[i];
	
	/* 2. Block wird an den Anfang von deck geschrieben*/
	char k = 0;
	for(char j=anzahl-1-a; j<anzahl-1; j++)
	{
		deck[k]=tempdeck[j];
		k++;
	}

	/*1. Block wird in die Mitte von Deck geschrieben*/ 
	k=0;
	for(char l=a; l<anzahl-1; l++)
	{
		deck[l]=tempdeck[k];
		k++;
	}

}

void Deck::inideckspeichern()
{
	FILE * pFile;
	pFile=fopen("StoredLastInitialdeck.txt","w+");
	// erste Zeile in Textdatei gibt die Kartenanzahl wieder
	fprintf( pFile, "%d", anzahl);	
	fprintf( pFile, "%s", "\n");
		
	for (char c=0;c<anzahl;c++)
	{	
		fprintf( pFile, "%d", tempini[c]);
		fprintf( pFile, "%s", "\n");
	}
	fclose (pFile);
}

void Deck::deck2tempini()
{
	memcpy(tempini,deck,54);
}

void Deck::analysevorne()
{
	schritt4revers();
	schritt3revers();
	schritt2reversvorne();
	schritt1reversvorne();
}

void Deck::analysehinten()
{
	schritt4revers();
	schritt3revers();
	schritt2revershinten();
	schritt1revershinten();
}

void Deck::keyUmrechnen()
{
	for (int i=0;i<plaintext.GetLength();i++)
	{
		key[i]=key[i]%26;
		if(key[i]==0) {key[i]=26;}
	}
}

void Deck::abschlussdeckspeichern()
{
	FILE * pFile;
	pFile=fopen("StoredLastFinaldeck.txt","w+");
	// erste Zeile in Textdatei gibt die Kartenanzahl wieder
	fprintf( pFile, "%d", anzahl);	
	fprintf( pFile, "%s", "\n");
	for (char c=0;c<anzahl;c++)
	{	
		fprintf( pFile, "%d", deck[c]);
		fprintf( pFile, "%s", "\n");
	}
	fclose (pFile);
}

void Deck::inideckladen()
{
	int load[54];
	int i;
	
	FILE * loadFile;
	loadFile = fopen( "StoredLastInitialdeck.txt", "r+" );
	
	rewind (loadFile);
	
	fscanf(loadFile, "%d\n", &anzahl);

	for ( i=0;i<anzahl;i++)
	{
		fscanf(loadFile, "%d\n", &load[i]);
	}
	//memcpy(deck,(char)load,54);
	for( i=0;i<54; i++)
		deck[i]=(char)load[i];
}

void Deck::abschlussdeckladen()
{
	int load[54];
	int i;
	
	FILE * loadFile;
	loadFile = fopen( "StoredLastFinaldeck.txt", "r+" );
	
	rewind (loadFile);
	
	fscanf(loadFile, "%d\n", &anzahl);

	for ( i=0;i<anzahl;i++)
		fscanf(loadFile, "%d\n", &load[i]);
	//memcpy(deck,(char)load,54);
	for( i=0;i<54; i++)
		deck[i]=(char)load[i];
}


void Deck::passwortinzahlen(CString pw)
{	
	for (int c=0 ;c<pw.GetLength(); c++)
		pass[c] = umwandelninzahl(pw[c]);
}

//funktioniert nur bei Kartenanzahl > 25
void Deck::pass2deck(int laenge)
{
	for (int i=0;i<laenge;i++)
	{
		schritt1();
		schritt2();
		schritt3();
		schritt4();
		schritt5fuerpasswort(i);
	}
}

//Analog zu Schritt4 nur nicht die letzte Karte sondern das Passwort
void Deck::schritt5fuerpasswort(int count)
{
	// temporaeres Hilfsdeck
	char tempdeck[54];

	// Hilfvariable a bekommt den Wert der letzten Karte im deck
	char a = pass[count];

	// tempdeck wird mit den Werten von deck belegt
	for(char i=0; i<anzahl; i++)
		tempdeck[i]=deck[i];
	
	/* 1. Teil des Zaehlabhebens, abgezaehlter Block
	 wird an die entsprechende Stelle in deck geschrieben
	 k ist Hilfvariable für die Schleife,
	 anzahl-1-a entspricht 53-a-(54-anzahl)*/
	char k = 0;
	for(char j=anzahl-1-a; j<anzahl-1; j++)
	{
		deck[j]=tempdeck[k];
		k++;
	}

	/* 2. Teil des Zaehlabhebens, Mittelblock wird an den 
	 Anfang von deck geschrieben,
	 k ist Hilfvariable für die Schleife,
	 anzahl-1-a entspricht 53-a-(54-anzahl)*/
	k=a;
	for(char l=0; l<anzahl-1-a; l++)
	{
		deck[l]=tempdeck[k];
		k++;
	}
}
	
void Deck::verschluesseln(CString plaintext)
{
	int st[USHRT_MAX];
	int temp[USHRT_MAX];
	
	CString Wert;
	CString tempstring;
	
	this->plaintext=plaintext;
	char ueber;
    ciphertext="";

	for (int c=0;c<plaintext.GetLength();c++)
	{			
		if (((plaintext[c]>='A')&&(plaintext[c]<='Z')) || ((plaintext[c]>='a')&&(plaintext[c]<='z')) )
		{
			tempstring+=plaintext[c];
			st[c]=umwandelninzahl(plaintext[c]);
		}
	}

	plaintext=tempstring;
	
	for (int d=0;d<plaintext.GetLength();d++)
	{
		temp[d] = (st[d]+key[d]) % 26;
		if( !temp[d] ) 
			temp[d]=26;
		
		ueber=umwandelninbuch(temp[d]);
		Wert.Format("%c",ueber);
		this->ciphertext+=Wert;
	}
}
	
	
int Deck::umwandelninzahl(char k)
{
	if ( k >= 'a' && k <= 'z' )
		return (int)(k - 'a') +1;
	if ( k >= 'A' && k <= 'Z' )
		return (int)(k - 'A') +1;
	return -1;
}

char Deck::umwandelninbuch(int k)
{
	assert( k >= 1 && k <= 26 );
	return 'A' + (char)(k -1);
}

//function to read inputfile into string plaintext
void Deck::readPlaintext(const char* ifile) 
{
	ifstream input(ifile);

	CString ststr;
	this->plaintext = "";
	char ch;
	while (input.get(ch))
	{
		switch (ch)
		{
			case 'Ä': {ststr += "ae"; break;}
			case 'ä': {ststr += "AE"; break;}
			case 'Ö': { ststr += "oe"; break; }
			case 'ö': { ststr += "OE"; break; }
			case 'Ü': { ststr += "ue"; break; }
			case 'ü': { ststr += "UE"; break; }
			case 'ß': { ststr += "ss"; break; }
			case ' ': { ststr += ""; break; }
			default: 
				{
					if (((ch>='A')&&(ch<='Z')) || ((ch>='a')&&(ch<='z')) )
						ststr += ch;
					else
						ststr +="";
				}
		}
	}

	this->plaintext =ststr;
	input.close();
}

//function to write string ciphertext to inputfile
void Deck::writeCiphertext(const char* ofile)
{
	ofstream output(ofile);
	
	for (int i = 0; i < ciphertext.GetLength(); i++)
	{
		if (i%5 ==0 &&i !=0){output.put(' ');}
		output.put(ciphertext[i]);
	}
	output.close();
}

void Deck::writeplaintext(const char* ofile)
{
	ofstream output(ofile);
	
	for (int i = 0; i < plaintext.GetLength(); i++)
	{
		if (i%5 ==0 &&i !=0){output.put(' ');}
		output.put(plaintext[i]);
	}
	output.close();
}

void Deck::entschluesseln(CString ciphertext)
{
	int integ[USHRT_MAX];
	int temp[USHRT_MAX];
	CString tempstring;
	char ueber;
	CString Wert;

	this->ciphertext=ciphertext;
	
	plaintext="";
	for (int i=0;i<ciphertext.GetLength();i++)
	{
		if (((ciphertext[i]>='A')&&(ciphertext[i]<='Z')) || ((ciphertext[i]>='a')&&(ciphertext[i]<='z')) )
		{
			tempstring+=ciphertext[i];
			integ[i]=umwandelninzahl(ciphertext[i]);
	 		
		}
	}
	ciphertext=tempstring;
	/////////////////////////
	//Wenn die erste Zahl kleiner oder gleich der zweiten Zahl ist, 
	//addiere vor der Subtraktion 26 zu der ersten Zahl. Also 1-22=? wird zu 27-22=5.
	/////////////////////////
	for (int d=0;d<ciphertext.GetLength();d++)
	{
		if (integ[d]<=key[d])
		{integ[d]=integ[d]+26;}
		temp[d] = (integ[d]-key[d])%26;
		if(temp[d]==0) {temp[d]=26;}
		
		ueber=umwandelninbuch(temp[d]);
		//Wert.Format("%i",temp[d]);
		Wert.Format("%c",ueber);
		this->plaintext+=Wert;
	}
}

/*Dies ist die Speichern Funktion, welche vom Speichern-Button
  aufgerufen wird. Sie speichert den erzeugten Schlüsselstrom in
  der Textdatei "StoredLastKeystream.txt".*/
void Deck::keyspeichern()
{
	FILE * pFile;
	char buffer[BUFSIZ];
	pFile=fopen("StoredLastKeystream.txt","w+");
	CString keysave = getKey();
	setbuf (pFile , buffer);
	
	fputs (keysave,pFile);
	fflush (pFile);
	fclose (pFile);
}

/*Dies ist die Laden Funktion.Sie kann aufgerufen 
werden um den zuletzt gespeicherten Schlüssel 
aus der Textdatei "StoredLastKeystream.txt" zu laden.*/
void Deck::keyladen()
{
	int load[USHRT_MAX];
	int i;
	
	FILE * loadFile;
	loadFile = fopen( "StoredLastKeystream.txt", "r+" );
	
	rewind (loadFile);
	
	for ( i=0;i<plaintext.GetLength();i++)
		fscanf(loadFile, "%d\n", &load[i]);
	
	for( i=0;i<plaintext.GetLength(); i++)
		key[i]=(char)load[i];
}
				

