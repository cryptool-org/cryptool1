// ComputerList.h: interface for the CComputerList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMPUTERLIST_H__5A9ABDA2_6CD6_11D6_9FD1_F82875035D7B__INCLUDED_)
#define AFX_COMPUTERLIST_H__5A9ABDA2_6CD6_11D6_9FD1_F82875035D7B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Computer.h"

class CComputerList  
{
public:
	CComputer& getComputer(int i);
	void addComputer(CComputer& computer);
	void clearList();
	CComputerList();
	virtual ~CComputerList();

private:
	CObList list;
};

#endif // !defined(AFX_COMPUTERLIST_H__5A9ABDA2_6CD6_11D6_9FD1_F82875035D7B__INCLUDED_)
