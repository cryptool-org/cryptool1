//////////////////////////////////////////////////////////////////
// Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
// ValueList.cpp : implementation file
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "ValueList.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CValueList

CValueList::CValueList() {ThePivot = NULL; TheActual = NULL;}


CValueList::~CValueList()
{
	ValueType * AnItem;
		if (ThePivot){
		while (ThePivot != ThePivot->NextItem){
			AnItem = ThePivot->NextItem;
			ThePivot->NextItem = AnItem->NextItem;
			if(AnItem->aString)
				delete AnItem->aString;
			delete AnItem;
		}
		if(ThePivot->aString)
			delete ThePivot->aString;
		delete ThePivot;
	}
}

void CValueList::DelAll()
{
	ValueType * AnItem;
		if (ThePivot){
		while (ThePivot != ThePivot->NextItem){
			AnItem = ThePivot->NextItem;
			ThePivot->NextItem = AnItem->NextItem;
			if(AnItem->aString)
				delete AnItem->aString;
			delete AnItem;
		}
		if(ThePivot->aString)
			delete ThePivot->aString;
		delete ThePivot;
	}
	ThePivot=TheActual=NULL;
}

void CValueList::AddItem(ValueType *AnItem){
	if(ThePivot != NULL){
		AnItem->NextItem = ThePivot->NextItem;
		ThePivot->NextItem = AnItem;

	} else AnItem->NextItem = AnItem;
	
	ThePivot = AnItem;
}	


BOOL  CValueList::GetNextItem(ValueType **AnItem){
	
	if( TheActual == NULL ) return FALSE;
	*AnItem = TheActual;
	
	if( TheActual != ThePivot) TheActual=TheActual->NextItem; // work on the next Item
	else TheActual=NULL;  // say next time no;
	return TRUE;
}

void CValueList::SetFirstItem()
{
	if(ThePivot != NULL) TheActual = ThePivot->NextItem;
	//else TheActual = NULL;
}

/////////////////////////////////////////////////////////////////////////////
// CValueList message handlers 