// ScenarioObject.h: interface for the CScenarioObject class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SCENARIOOBJECT_H__7EE1C7C2_EB61_11D7_9FD1_ED1DDA3A9E7B__INCLUDED_)
#define AFX_SCENARIOOBJECT_H__7EE1C7C2_EB61_11D7_9FD1_ED1DDA3A9E7B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CScenarioObject : public CObject 
{
public:
	void setPens();
	//eigene Variablen und Methoden
	bool visible;
	void draw(CClientDC &dc);
	void setParametersSO(int x1, int y1, int x2, int y2, int borderWidth);
	bool isMouseOverScenarioObject(CPoint& point);
	bool isMouseOverObject(CPoint& point);
	CString name;

	//Konstruktor & Dekonstruktor
	CScenarioObject();
	virtual ~CScenarioObject();

protected:
	//eigene Variablen
	int  x1,y1,x2,y2;
	int  borderWidth;

	CPen blackPen, redPen, whitePen, yellowPen, bluePen;
	CPen* originalPen;
	CFont captionFont, dataFont;
	COLORREF black, red, white, yellow, blue;
	CFont* originalFont;

};

#endif // !defined(AFX_SCENARIOOBJECT_H__7EE1C7C2_EB61_11D7_9FD1_ED1DDA3A9E7B__INCLUDED_)
