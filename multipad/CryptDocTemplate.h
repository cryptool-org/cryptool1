//////////////////////////////////////////////////////////////////
// Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
#include <AFXWIN.H>

class CCryptDocTemplate : public CMultiDocTemplate
{
	DECLARE_DYNAMIC(CCryptDocTemplate)

// Constructors
public:
	CCryptDocTemplate(UINT nIDResource, CRuntimeClass* pDocClass,
		CRuntimeClass* pFrameClass, CRuntimeClass* pViewClass);

// Implementation
public:

	virtual Confidence MatchDocType(LPCTSTR lpszPathName, CDocument*& rpDocMatch);

	virtual ~CCryptDocTemplate();
};
