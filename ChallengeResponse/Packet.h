// Packet.h: interface for the CPacket class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PACKET_H__D1B4CB61_6D7B_11D6_9FD1_DD9275F6D937__INCLUDED_)
#define AFX_PACKET_H__D1B4CB61_6D7B_11D6_9FD1_DD9275F6D937__INCLUDED_

#include "ScenarioObject.h"
#include "Data.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CPacket : CScenarioObject
{
public:
	void addMoreData(CString contentCaption, CString contentValue);
	bool visible;
	int actualWireStep;
	void erase(CClientDC &dc);
	void setParameters(int x1, int y1, int x2, int y2, int borderWidth);
	bool attackerCopy;
	int actualWire;
	bool onWire;
	
	
	
	//geerbte Variablen und Methoden
	void draw(CClientDC& dc);
	
	//eigene Variablen und Methoden
	int targetComputer;
	int lastComputer;
	int startComputer;
	CData data;
	bool active;
	void activate(CString contentCaption, CString contentValue, int startComputer, int lastComputer, int targetComputer, bool attackerCopy);

	//Konstruktor & Dekonstruktor
	CPacket();
	virtual ~CPacket();
};

#endif // !defined(AFX_PACKET_H__D1B4CB61_6D7B_11D6_9FD1_DD9275F6D937__INCLUDED_)
