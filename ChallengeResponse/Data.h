// Data.h: interface for the CData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DATA_H__064E9A01_6BDC_11D6_9FD1_E9F62E3D370B__INCLUDED_)
#define AFX_DATA_H__064E9A01_6BDC_11D6_9FD1_E9F62E3D370B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CData  
{
public:
	CString getValueByLabel(CString label);
	CString getValueHidden(int i);
	CString getValue(int i);
	CString getLabel(int i);
	void copy(CData& orgData, bool copyValues);
	CString getLine(int i, bool isAttacker);
	int getNumberOfLines();
	void changeValue(CString label, CString value);
	void addLabel(CString label);
	void clearLists();
	CData();
	virtual ~CData();
	CStringList labels;
	CStringList values;
};

#endif // !defined(AFX_DATA_H__064E9A01_6BDC_11D6_9FD1_E9F62E3D370B__INCLUDED_)
