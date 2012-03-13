/**************************************************************************

  Copyright [2009] [CrypTool Team]

  This file is part of CrypTool.

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

**************************************************************************/

#include "Solitaire.h"
#include "assert.h"
#include <fstream>
#include "CrypToolTools.h"


using namespace std;

c_solitaire::c_solitaire () : 
	inner_state(-1), top(0), joker_A(0), joker_B(0), no_of_cards(0)
{
}

void c_solitaire::clear()
{
	while ( top )
	{
		card *rem = top->dn;
		if ( top == rem )
		{
			delete top;
			top = 0;
		}
		else
		{
			top->dn = rem->dn;
			delete rem;
		}
	}
	joker_A = joker_B = 0;
	inner_state = 0;
}

c_solitaire::~c_solitaire()
{
	clear();
}

unsigned char c_solitaire::get_char( char ch )
{
	if ( ch >= 'A' && ch <= 'Z' )
		return (unsigned char)(ch-'A'+1); 
	if ( ch >= 'a' && ch <= 'z' )
		return (unsigned char)(ch-'a'+1); 
	return 0;
}


//////////////////////////////////////////////////////////
// Solitaire Initialization
bool c_solitaire::initialize( long cards, long ID, const unsigned char *cardset )
{
	clear();
	if ( cards < 3 || cards > 54 )
		return false;

// set cards
	no_of_cards = cards;
	card *new_card;
	for ( long i=1; i<=cards; i++ )
	{
		switch ( ID ) {
			case 0: // aufsteigend sortiert
			case 2: // gemischt
				new_card = new card((unsigned char)i);
				break;
			case 1: // absteigend sortiert
				new_card = new card((unsigned char)(cards-i+1));
				break;
			case 3: // nach Vorgabe
				new_card = new card( cardset[i] );
				break;
			default:
				assert(false);
				break;
		}
		if ( !top )
		{
			top		= new_card;
			top->up	= top;
			top->dn	= top;
		}
		else
		{
			new_card->dn	= top;
			new_card->up	= top->up;
			top->up->dn		= new_card;
			top->up	        = new_card;
		}
	}

	if ( ID == 2 )
	{ // Mischen
		int state = 0, r;
		card *c = top;
		for ( long i=0; i<1000; i++ )
		{
			r = rand() % 2;
			if ( r ) {
				if ( !state )
				{
					joker_A = c; state++;
				}
				else
				{ // mix
					joker_B = c; state = 0;
					unsigned char t = joker_A->ord;
					joker_A->ord = joker_B->ord;
					joker_B->ord = t;
				}
			}
			c = c->dn;
		}
	}

// find the joker
	card *c = top;
	while ( 1 ) {
		if ( c->ord == cards -1 )
			joker_A = c;
		if ( c->ord == cards )
		{
			c->ord = (unsigned char)(cards-1);
			joker_B = c;
		}
		c = c->dn;
		if ( c == top )
			break;
	}

	return true;
}

bool c_solitaire::initialize( long cards, char *pass, const unsigned char *cardset )
{
	if ( cards < 26 ) 
		return false;
	bool no_error;
	if ( cardset )
		no_error = initialize( cards, 3, cardset );
	else
		no_error = initialize( cards, 0 );
	if ( !no_error )
		return false;
	
	return add_passphrase( pass );
}

bool c_solitaire::set_deck( CString &str )
{
	unsigned char check[55], deck[55];
	long cards = 0, ndx = 0, max = 0;
	for (long i=1;i<=54;i++) check[i] = 0;
	while ( str.GetLength() )
	{
		long p = str.Find(',');
		CString s;
		if ( p > 0 )
		{
			s = str.Mid(0, p);
			str.Delete(0, p+1);
		}
		else if ( p == 0 || !str.GetLength())
			return false;
		else {
			s = str;
			str = _T("");
		}
		long d;
		if ( !s.Find('A') ) d = 53;
		else if ( !s.Find('B') ) d = 54;
		else { 
			d = atoi(s.GetBuffer());
			if (d > max) max = d;
		}
		if ( d < 1 || d > 54 || check[d] || ++ndx > 54 )
			return false;
		check[d]  = (unsigned char)ndx;
		deck[ndx] = (unsigned char)d;
	}
	if ( ndx == max +2 && check[53] && check[54] )
	{
		deck[check[53]] = (unsigned char)++max;
		deck[check[54]] = (unsigned char)++max;
	}
	if ( ndx == max )
	{
		initialize( ndx, 3, deck );
		return true;
	}
	return false;
}

bool c_solitaire::get_deck( CString &str )
{
	if ( 0 > inner_state ) 
		return false;
	str = _T("");
	card *t = top;
	char numStr[12];
	for ( long i=1; i<=no_of_cards; i++ )
	{
		if ( t == joker_A ) 
			str += 'A';
		else if ( t == joker_B )
			str += 'B';
		else
		{
			_itoa( t->ord, numStr, 10 );
			str += CString(numStr);
		}
		if ( i < no_of_cards )
			str += ',';
		t = t->dn;
	}

	return true;
}

bool c_solitaire::add_passphrase( char *pass )
{
	if ( no_of_cards < 26 )
		return false;

	long i;
	for ( i=0; i<(long)strlen(pass); i++ )
	{
		if ( pass[i] >= 'a' && pass[i] <= 'z' ) pass[i] -= ('a' - 'A');
		if ( pass[i] <  'A' || pass[i] > 'Z' ) 
			return false;
	}

	for ( i=0; i<(long)strlen(pass); i++)
	{
		set_inner_state(0);
		s1_swap_JA();
		s2_swap_JB();
		s3_triple_cut();
		s4_count_cut();
		set_inner_state(3);
		s4_count_cut( (unsigned char)(pass[i] - 'A' +1) );
	}
	return true;
}


/////////////////////////////////////////////////////
// Solitaire Enrcyption
bool c_solitaire::s1_swap_JA()
{ // 1. Find the A joker. Move it one card down.
	if ( inner_state ) 
		return false;

	unsigned char t = joker_A->ord;
	joker_A->ord = joker_A->dn->ord;
	joker_A = joker_A->dn;
	joker_A->ord = t;

	if ( top == joker_A )
		top = top->up;
	if ( joker_B == joker_A )
		joker_B = joker_A->up;
	inner_state++;
	return true;
}


bool c_solitaire::s2_swap_JB()
{ // 2. Find the B joker. Move it two cards down.
	if ( 1 != inner_state ) 
		return false;

	unsigned char t = joker_B->ord;
	for ( long i=1; i<=2; i++ )
	{
		joker_B->ord = joker_B->dn->ord;
		joker_B = joker_B->dn;
		if ( top == joker_B )
			top = top->up;
		if ( joker_B == joker_A )
			joker_A = joker_A->up;
	}
	joker_B->ord = t;

	inner_state++;
	return true;
}

bool c_solitaire::s3_triple_cut()
{ // 3. Perform a triple cut. That is, swap the cards above the first joker with the cards below the second joker.
	if ( 2 != inner_state ) 
		return false;

	card *i_dn, *i_up;
	i_dn = top;		while ( i_dn != joker_A && i_dn != joker_B ) i_dn = i_dn->dn;
	i_up = top->up; while ( i_up != joker_A && i_up != joker_B ) i_up = i_up->up;

	if ( i_up->dn == top )
		top = i_dn;
	else if ( i_dn == top )
		top = i_up->dn;
	else 
	{
		card *tb = i_up->dn, *te = top->up;
		// 1. remove tb ** te from list
		i_up->dn		= top;
		top->up			= i_up;
		// 2. insert tb ** te between i_dn->up and i_dn
		tb->up			= i_dn->up;
		te->dn			= i_dn;
		i_dn->up->dn	= tb;
		i_dn->up		= te;
		top = tb;
	}

	inner_state++;
	return true;
}

/*
 NOTE: Password based initial deck setting (step 4 with parameter c)
 Perform the Solitaire operation, but instead of Step 5, do another count cut based on the first character of the passphrase (19, in this example). 
 In other words, do step 4 a second time, using 19 as the cut number instead of the last card. Remember to put the top cards just above the bottom 
 card in the deck, as before.
 Repeat the five steps of the Solitaire algorithm once for each character of the key. That is, the second time through the Solitaire steps use the 
 second character of the key, the third time through use the third character, etc. 
*/
bool c_solitaire::s4_count_cut(unsigned char c)
{  // Count down from the top card that number. 
   // Cut after the card that you counted down to, leaving the bottom card on the bottom.
	if ( 3 != inner_state ) 
		return false;

	if ( !c )
		c = top->up->ord;

	card *t = top, *tb = top->up;
	while ( c-- > 1 ) t = t->dn;
	// 1. remove top ** t from list;
	tb->dn		= t->dn;
	t->dn->up	= tb;
	// 2. insert top ** t between tb->up and tb
	top->up		= tb->up;
	t->dn		= tb;
	tb->up->dn	= top;
	tb->up		= t;
	top	= tb->dn; // ... leaving the bottom card on the bottom.

	inner_state++;
	return true;
}

unsigned char c_solitaire::s5_stream_char()
{
	if ( 4 != inner_state ) 
		return 0;

	unsigned char c = top->ord;
	card *t = top;
	while ( c-- >= 1 ) t = t->dn;
	inner_state = 0;

	if ( t == joker_A || t == joker_B )
		return 0;

	c = t->ord; 
	return c;
}

unsigned char c_solitaire::crypt_c( solitaire_action encrypt, unsigned char c )
{
	long out = 0;
	while ( !out )
	{
		s1_swap_JA();
		s2_swap_JB();
		s3_triple_cut();
		s4_count_cut();
		out = s5_stream_char();
	}
	if ( out > 26 ) out -= 26;
	if ( encrypt == SOL_ENCRYPT)
	{
		out = c + out;
		if ( out > 26 ) out -= 26;
	}
	else if ( encrypt == SOL_DECRYPT )
	{
		out = c - out;
		if ( out < 1 ) out += 26;
	}
	else return 0; // FIXME 
	assert( 0 < out && 26 >= out );
	return (unsigned char)(out + ('A' -1));
}

long c_solitaire::crypt( solitaire_action encrypt, const char *f_in, const char *f_out )
{
	long error = 0;
	fstream fin, fout;
	fin.open( f_in, ios::in || ios::binary );
	if ( fin.is_open() )
	{
		fout.open( f_out, ios::out );
		if ( fout.is_open() )
		{
			long x = 0;

			unsigned char c, c2;
			while ( !fin.eof() )
			{
				c = fin.get();

				switch ( c ) {
					case 'Ä':
					case 'ä':
						c  = get_char('A');
						c2 = get_char('E');
						break;
					case 'Ö':
					case 'ö':
						c  = get_char('O');
						c2 = get_char('E');
						break;
					case 'Ü':
					case 'ü':
						c  = get_char('U');
						c2 = get_char('E');
						break;
					case 'ß':
						c  = get_char('S');
						c2 = get_char('S');
						break;
					default:
						c = get_char( c );
						c2 = 0;
						break;
				}
				// FIXME 
				if ( c ) {
					fout.put( crypt_c( encrypt, c ) );
					if ( !(++x % 5) ) { if ( x == 70 ) { fout.put('\n');  x = 0; } else fout.put(' '); }   
				}
				if ( c2 ) {
					fout.put( crypt_c( encrypt, c2 ) );
					if ( !(++x % 5) ) { if ( x == 70 ) { fout.put('\n');  x = 0; } else fout.put(' '); }   
				}
			}

			fout.close();
		}
		else error = 2; // FIXME 
		fin.close();
	}
	else error = 1; // FIXME 
	return error;
}

long crypt_solitaire( solitaire_action encrypt, const char *f_in, const char *f_out, long cards, long ID, unsigned char *cardset, char *password )
{
	long no_error = true;
	assert ( encrypt != SOL_NOTHING );

	c_solitaire s;
	if ( password )
		no_error = s.initialize( cards, password, cardset );
	else
		no_error = s.initialize( cards, ID, cardset);

	if ( no_error )
		return s.crypt( encrypt, f_in, f_out );
	else no_error = 4; // FIXME
	return no_error;
}

long crypt_solitaire( solitaire_action encrypt, const char *f_in, const char *f_out, CString &cardset )
{
	c_solitaire s;
	if ( s.set_deck(cardset) )
		return s.crypt( encrypt, f_in, f_out );
	return 4; // FIXME 
}




#if 1
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

//////////////////////////////////////////////////////////
// ANALYSE
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

////////////////////////////////////////////////////////////////////////////
// STORE DECK TO REGISTRY
int Deck::writedeck( const char *deck_label )
{
	if ( ERROR_SUCCESS == CT_OPEN_REGISTRY_SETTINGS(KEY_WRITE, IDS_REGISTRY_SETTINGS, "Solitaire") )
	{
      CString Deck;
      Deck.Format("%d ", anzahl);
      for ( size_t i=0; i<(size_t)anzahl; i++ )
      {
         char strnum[4];
         sprintf( strnum, "%2d ", deck[i] );
         Deck = Deck + CString( strnum );
      }
      CT_WRITE_REGISTRY( Deck, deck_label );
      CT_CLOSE_REGISTRY();
      return 1;
   }
   return 0;
}

int Deck::readdeck( const char *deck_label )
{
   const char default_deck[] = "54 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50 51 52 53 54";

   char           str_deck[166];
   unsigned long  str_len = 165, i, j, error = 0;

   if ( ERROR_SUCCESS == CT_OPEN_REGISTRY_SETTINGS(KEY_ALL_ACCESS, IDS_REGISTRY_SETTINGS, "Solitaire") )
	{
      error = !CT_READ_REGISTRY_DEFAULT( (char*)str_deck, deck_label, default_deck, str_len );
      CT_CLOSE_REGISTRY();
   }
   else
      error = 1;

   if ( error ) 
      strcpy( str_deck, default_deck );

   anzahl = atoi( str_deck );
   for ( i=j=0; j<(unsigned long)anzahl; j++ )
   {
      while( str_deck[i] >= '0' && str_deck[i] <= '9' ) i++;
      while( str_deck[i] == ' ' ) i++;
      deck[j] = atoi(&str_deck[i]);
   }

   return !error;
}

int Deck::loaddeck( const char *default_filename )
{
	DWORD   dwFlags(OFN_HIDEREADONLY | OFN_PATHMUSTEXIST);
	CFileDialog dlg(TRUE, 0, CString(default_filename), dwFlags, _T("*.txt"));
	if ( IDOK == dlg.DoModal() )
	{
		CString pathStr = dlg.GetPathName();
		ifstream fin;
		fin.open( pathStr, ios::in );
      

		if ( fin.is_open() )
		{
         int i = 0, max = 0, A = 0, B = 0;
         char tmp_deck[54];
         for ( i=0; !fin.eof(); i++ )
         {
            char id_str[4];
            int  id_card;

            if ( i >= 54 ) // max 54 cards
               return -2;

            fin.getline( id_str, 4, ',' );
            if ( !fin.gcount() )
               return -2;

            if ( id_str[0] == 'A' )       { A = i; id_card = 53; }
            else if ( id_str[0] == 'B' )  { B = i; id_card = 54; }
            else {
               id_card = atoi(id_str);
               if ( id_card > 52 || 1 > id_card )
                  return -2;
               for (int j=0; j<i; j++)
                  if ( id_card == tmp_deck[j] )
                     return -2;
               if ( id_card > max ) max = id_card;
            }

            tmp_deck[i] = id_card;
         }
			fin.close();
         if ( max != i-2 || !A || !B )
            return -2;
         anzahl = max +2;
         for ( i=0; i<anzahl; i++ )
         {
            if ( A == i )      deck[i] = anzahl-1;
            else if ( B == i ) deck[i] = anzahl;
            else               deck[i] = tmp_deck[i];
         }
         return 1;
		}
      else
         return -1;
	}
   return 0;
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
			case 'Ä': { ststr += "ae"; break;}
			case 'ä': { ststr += "AE"; break;}
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
				
#endif
