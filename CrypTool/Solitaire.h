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


#pragma once
#include "stdafx.h"
#include "limits.h"

enum solitaire_action { SOL_NOTHING, SOL_ENCRYPT, SOL_DECRYPT };

struct card {
	unsigned char ord;
	card *dn, *up;
	card( unsigned char _ord ) : ord(_ord), dn(0), up(0) {}
};

class c_solitaire {
	card *top;
	card *joker_A, *joker_B;
	long inner_state;
	long no_of_cards;
	void clear();

	unsigned char crypt_c( solitaire_action encrypt, unsigned char c );
	long		  crypt( solitaire_action encrypt, const char *f_in, const char *f_out );

	friend long crypt_solitaire( solitaire_action encrypt, const char *f_in, const char *f_out, long cards, long ID, unsigned char *cardset, char *password = 0 );
	friend long crypt_solitaire( solitaire_action encrypt, const char *f_in, const char *f_out, CString &cardset );

public:
	c_solitaire ();
	~c_solitaire();
	bool			initialize( long cards, long ID, const unsigned char *cardset );
	bool			initialize( long cards, char *pass, const unsigned char *cardset = 0 );
	bool			add_passphrase( char *pass );
	bool			s1_swap_JA();
	bool			s2_swap_JB();
	bool			s3_triple_cut();
	bool			s4_count_cut(unsigned char c = '\0');
	unsigned char	s5_stream_char();
	bool            get_deck( CString &str );
	bool			set_deck( CString &str );
	long            get_no_of_cards() { return no_of_cards; }
	unsigned char   get_char( char ch );
	long	        get_inner_state() { return inner_state; }
	void            set_inner_state(long state) { inner_state = state; }
};


#if 1
class Deck
{
public:
	char deck [54];
	int anzahl;
	int posB;
	int posA;
	int min;
	int max;
	int k;
	int temp;
	char rueckgabe;
	char key[USHRT_MAX];
	int anzahlnullrunden;
	char joker;		
	int laden;
	int pass[1024];
	char tempini[54];
	//int passlaenge;
	CString plaintext;
	CString ciphertext;
	
public:
	void setkartenanzahl(int anzahlkarten);
	Deck(int anzahlkarten);
	CString getDeck();
	CString getKey();
	CString getDeckChar(int zaehler);
	CString getKeyChar(int zaehler);
	void keyUmrechnen();
	void deck2tempini();
	void print();
	void aufsteigend();
	void absteigend();
	void mischen();
	void schritt1();
	void schritt2();
	void schritt3();
	void schritt4();
	char schritt5();
	char schritt5ohneJokerAusgabe();
	int  nullrunde();
	bool pruefenullrunde();
	void schritt1revers();
	bool schritt1reversabfrage();
	void vorneeinordnena();
	void hinteneinordnena();
	void schritt1reversvorne();
	void schritt1revershinten();  
	void schritt2revers();
	bool schritt2reversabfrage();
	void vorneeinordnenb();
	void hinteneinordnenb();
	void schritt2reversvorne();
	void schritt2revershinten();  
	void schritt3revers();
	void schritt4revers();
	void analysevorne();
	void analysehinten();
	void passwortinzahlen(CString pw);
	void pass2deck(int laenge);
	void schritt5fuerpasswort(int count);
	char umwandelninbuch(int k);
	int  umwandelninzahl(char k);
	void verschluesseln(CString plaintext);
	void readPlaintext(const char* ifile);
	void writeCiphertext(const char* ofile);
	void writeplaintext(const char* ofile);
	void entschluesseln(CString ciphertext);

   int writedeck( const char *deck_label );
   int readdeck ( const char *deck_label );
   int loaddeck( const char *default_filename );
};

#endif 