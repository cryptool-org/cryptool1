/*
 * $Id$
 * 
 * $Log$
 * Revision 1.1  2001/01/29 13:58:26  koy
 * Initial revision
 *
 * Revision 1.1.1.1  2000/10/31 09:37:15  koy
 * Neuer CVS Baum ab CrypTool Version 1.2.02
 *
 *
 * Revision 1.1.1.1  2000/07/18 07:17:35  gruber
 * no message
 *
 * Revision 1.1.1.1  2000/07/17 14:22:27  gruber
 * erster import
 *
 * Revision 1.3  1996/09/24 12:32:34  schupp
 * inserted RCS header
 *
 * 
 */
/****************************************************************************
 *
 *	V.24 Tools Plus
 *
 ****************************************************************************
 *
 *	Modul:			v24tools.h
 *
 *	Version:		2.0
 *
 *	Betriebssystem:		Unix System V
 *
 *	Funktionen:		Zentraler Header-File
 *
 ****************************************************************************
 *
 *	Quellcode-Copyright (C) 1991-1992 by Langner GmbH
 *	Alle Rechte vorbehalten.
 *
 ****************************************************************************/


#ifndef _V24TOOLS_H_
#define _V24TOOLS_H_

#include <termio.h>


#define V24QSIZE	256	/* default 256 Byte buffer                */
#define V24NPORTS	4	/* Maximale Anzahl von Ports              */

#ifdef AIX
#define LOCKDIR		"/etc/locks"		/* uucp Lock-Verzeichnis  */
#else
#define LOCKDIR		"/usr/spool/uucp"	/* uucp Lock-Verzeichnis  */
#endif


/*-- diverse Flags und Konstanten --*/

#define SECOND		10	/* Zeiteinheit: 10tel Sekunden            */

#define N 		0x4e	/* 'N' = no parity                        */
#define E 		0x45	/* 'E' = even parity                      */
#define O 		0x4f	/* 'O' = odd parity                       */

#define V24SHARE	0	/* Port mit anderen Prozessen teilen      */
#define V24XCLUDE	1	/* Port exklusiv oeffnen                  */
#define V24LOCK		2	/* Lock-File fuer uucp anlegen            */

#define V24NOFLOW	0	/* Kein Handshake                         */
#define V24XONXOFF	1	/* strikter XON/XOFF-Handshake            */
#define V24XANYXOFF	2	/* gelockerter XON/XOFF-Handshake         */
#define V24RTSCTS	3	/* RTS/CTS-Handshake                      */
#define V24CTS		4	/* CTS-Handshake                          */
#define V24RTS		5	/* RTS-Handshake                          */

#define NUL		'\0'
#define SOH		0x01
#define STX		0x02
#define ETX		0x03
#define EOT		0x04
#define ACK		0x06
#define BEL		0x07
#define BS		0x08
#define TAB		0x09
#define LF		0x0a
#define VT		0x0b
#define FF		0x0c
#define CR		0x0d
#define SO		0x0e
#define SI		0x0f
#define NAK		0x15
#define SYN		0x16
#define CAN		0x18
#define SUB		0x1a
#define ESC		0x1b
#define SP		' '
#define XON		0x11
#define XOFF		0x13

#define PULSEDIAL	0
#define TONEDIAL	1

#define EIN		1
#define AUS		0
#define TEST		2
#define START		1
#define STOP		0
#define SECOND		10

#define RCV		0		/* Empfangspuffer */
#define SND		1		/* Sendepuffer */

#define MDM_OK		0
#define MDM_NOCARR	1
#define MDM_ERROR	2
#define MDM_BUSY	3
#define MDM_DIALTONE	4
#define MDM_CONNECT	5
#define MDM_TIMEOUT	-1
#define MDM_UNDEF	-2


/****************************************************************************/
/****************************** Datenstrukturen *****************************/
/****************************************************************************/

typedef struct _port {
	/*-- Systemwerte --*/
	char name[256];			/* Name des Ports                   */
	int handle;			/* System handle                    */
	/*-- Empfangspuffer --*/
	char *bp;			/* Pointer auf Empfangspuffer       */
	unsigned int qsize;		/* Groesse des Empfangspuffers      */
	unsigned int front;		/* Front-Offset im Empfangspuffer   */
	unsigned int rear;		/* Rear-Offset im Empfangspuffer    */
	/*-- Flags --*/
	unsigned char in_use;		/* In Use-Flag                      */
	unsigned char local;		/* Port lokal geoeffnet             */
	unsigned char handshake;	/* Art des Handshakes               */
	unsigned char lock;		/* Art des Device-Lockings          */
	int time_out;			/* Timeout bei Lesezugriffen        */
	/*-- termio-Parameter --*/
	struct termio prev_par;		/* Parameter beim Oeffnen des Ports */
	struct termio curr_par;		/* gegenwaertige Parameter          */
	} v24port;


/****************************************************************************/
/****************************** Fehlercodes *********************************/
/****************************************************************************/

#define EV24INUSE	-1	/* Schnittstelle bereits geoeffnet          */
#define EV24DEVICE	-2	/* Schnittstelle nicht installiert          */
#define EV24NOMEM	-3	/* Puffer kann nicht allokiert werden       */
#define EV24CLOSED	-4	/* Port ist nicht geoeffnet                 */
#define EV24OUTRNG	-5	/* Wert ausserhalb des zulaessigen Bereichs */
#define EV24TIMEOUT	-6	/* Timeout beim Schreiben oder Lesen        */
#define EV24NOSLOT	-7	/* Port-Tabelle voll                        */
#define EV24IOCTL	-8	/* ioctl() error                            */
#define EV24ACCESS	-9	/* kein Zugriffsrecht                       */
#define EV24BUSY	-10	/* Port von anderem Prozess belegt          */
#define EV24LOCAL	-11	/* Port lokal geoeffnet, kein RTS/CTS/DCD   */
#define EV24IO		-12	/* I/O Error (read oder write)              */
#define EV24LOCKED	-13	/* Schnittstelle ist gesperrt               */
#define EV24HARDW	-14	/* Hardware unterstuetzt Funktion nicht     */

#define EV24NOENT	1	/* File not found                           */
#define EV24ABORT	2	/* Xmodem/Ymodem/Zmodem Transfer Aborted    */
#define EV24XMDNOEOF	3	/* Xmodem: End of File not recognized       */
#define EV24DISKFULL	4	/* Disk Full                                */


/****************************************************************************/
/******************************** Prototypen ********************************/
/****************************************************************************/

#ifdef __ANSIC__
#define VOID void

/*-- Oeffnen/Schliessen --*/
int v24open(char *portname, int flags);
int v24close(int port);

/*-- Senden --*/
int v24putc(int port,char c);
int v24puts(int port,char *s);
int v24write(int port,void *s,unsigned len);
int v24sendbreak(int port);

/*-- Empfangen --*/
int v24getc(int port,char *c,int time_out);
int v24nextc(int port);
int v24getch(int port);
int v24gets(int port,char *s,int len,char termchar);
int v24read(int port,char *s,unsigned len);

/*-- Uebertragungsparameter --*/
int v24sethandshake(int port, int handshake);
int v24gethandshake(int port);
int v24settimeout(int port, int time_out);
int v24gettimeout(int port);
int v24setparams(int port,int speed,int dbits,int parity,int stopbits);
int v24getparams(int port,int *speed,int *dbits,int *parity,int *stopbits);
int v24reset(int port);
int v24restore(int port);

/*-- Steuer- und Meldeleitungen --*/
int DCD(int port);
int DSR(int port);
int CTS(int port);
int RI(int port);
int DTR(int port, int sw);
int RTS(int port, int sw);

/*-- Pufferverwaltung --*/
int v24setbuffer(int port,int which,unsigned size);
int v24qsize(int port, int which);
unsigned v24pending(int port,int which);
int v24qempty(int port,int which);
int v24flush(int port,int which);

/*-- Dateitransfer --*/
int v24sendxmodem(int port, char *fname,int ymodem,int (*xmdstat)());
int v24rcvxmodem(int port, char *fname,int crcopt,int (*xmdstat)());
int v24rcvzmodem(int port, int (*zmdstat)());
int v24sendzmodem(int port, char *fname,int lastfile,int (*zmdstat)());

/*-- CRC berechnen --*/
unsigned updcrc(unsigned crc, unsigned char c);
unsigned updcrc16(unsigned crc, unsigned char c);
long updcrc32(long crc, unsigned char c);

/*-- Modemfunktionen --*/
int v24dial(int port, int dialmode, char *number);
void v24hangup(int port);
void v24answer(int port);
void v24mdm_init(int port);
void v24mdm_setpar(int port, int echo, int quiet, int verbose);
void v24mdm_reset(int port);

#else
#define VOID
#endif

#endif

