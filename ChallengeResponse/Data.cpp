// Data.cpp: implementation of the CData class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Data.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CData::CData()
{
}

CData::~CData()
{
	clearLists();
}

void CData::clearLists()
{
	labels.RemoveAll();
	values.RemoveAll();
}

void CData::addLabel(CString label)
{
	labels.AddTail(label);
	values.AddTail((CString)"");
}

void CData::changeValue(CString label, CString value)
{
	
	for (int i=0; i<labels.GetCount(); i++){
		
		
		if ((labels.GetAt(labels.FindIndex(i)))==label) values.SetAt(values.FindIndex(i),value);
	}
}

int CData::getNumberOfLines()
{
	return labels.GetCount();
}

CString CData::getLine(int i, bool isAttacker)
{
	
	if (!isAttacker){	
		return getLabel(i)+getValueHidden(i);
	}else{
		return getLabel(i)+getValue(i);
	}
}

CString CData::getLabel(int i)
{
	return labels.GetAt(labels.FindIndex(i));
}

CString CData::getValue(int i)
{
	return values.GetAt(values.FindIndex(i));
}


void CData::copy(CData& orgData, bool copyValues)
{
	clearLists();
	for(int i=0; i<=orgData.getNumberOfLines()-1;i++){
		addLabel(orgData.getLabel(i));
		if (copyValues) changeValue(orgData.getLabel(i),orgData.getValue(i));
	}
}



CString CData::getValueHidden(int i)
{
	CString returnValue;
	for(int j=0; j<=getValue(i).GetLength()-1;j++){
		returnValue.Insert(j,"*");
	}
	return returnValue;
}

CString CData::getValueByLabel(CString label)
{
	for (int i=0; i<labels.GetCount(); i++){
		if ((labels.GetAt(labels.FindIndex(i)))==label) return getValue(i);
	}
	return (CString)"";
}
