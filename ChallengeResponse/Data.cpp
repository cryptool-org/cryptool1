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
