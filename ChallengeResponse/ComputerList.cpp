// ComputerList.cpp: implementation of the CComputerList class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ComputerList.h"
#include "ScenarioObject.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CComputerList::CComputerList()
{
	clearList();
}

CComputerList::~CComputerList()
{

}

void CComputerList::clearList()
{
	list.RemoveAll();
}

void CComputerList::addComputer(CComputer& computer)
{
	//list.AddTail(&computer); //??? Compilerfehler
}

CComputer& CComputerList::getComputer(int i)
{
	return (CComputer&)(list.GetAt(list.FindIndex(i)));
}
