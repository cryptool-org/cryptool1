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



