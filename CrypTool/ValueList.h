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

//////////////////////////////////////////////////////////////////
// Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
// ValueList.h : header file
//

#ifndef VALUELIST_H
#define VALUELIST_H
/////////////////////////////////////////////////////////////////////////////
// CValueList 
typedef struct tagValue{
	double x, y;
	CPoint aPoint;
	char *aString;
	tagValue *NextItem;
} ValueType;

class CValueList : public CObject
{
// Construction
public:
	CValueList();
	~CValueList();

// Attributes
public:
	ValueType* ThePivot;
	ValueType* TheActual;
// Operations
public:
	void AddItem(ValueType *AnItem);
	void SetFirstItem();
	BOOL GetNextItem(ValueType **AnItem);
	void DelAll();
};
#endif
/////////////////////////////////////////////////////////////////////////////



