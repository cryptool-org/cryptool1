#pragma once
#include "stdafx.h"
#include "limits.h"




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
		void inideckspeichern();
		void abschlussdeckspeichern();
		void inideckladen();
		void abschlussdeckladen();
		void passwortinzahlen(CString pw);
		void pass2deck(int laenge);
		void schritt5fuerpasswort(int count);
		char umwandelninbuch(int k);
		int umwandelninzahl(char k);
		void verschluesseln(CString plaintext);
		void readPlaintext(const char* ifile);
		void writeCiphertext(const char* ofile);
		void writeplaintext(const char* ofile);
		void entschluesseln(CString ciphertext);
		void keyspeichern();
		void keyladen();
	};