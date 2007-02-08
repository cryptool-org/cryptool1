//////////////////////////////////////////////////////////////////////////////////
// Name:      actCertificateReg.h
// Product:   cv act library
// Purpose:   
//
// Copyright: (c) 2000 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//////////////////////////////////////////////////////////////////////////////////

#ifndef ACT_CERTIFICATEREG_H
#define ACT_CERTIFICATEREG_H

namespace act
{
	class ICertificate;
	class ICRL;

	typedef ICertificate* (*CreateCertificatePtr)();
	typedef ICRL* (*CreateCRLPtr)();

	struct CertificateMapEntry {
		const char* Name;
		CreateCertificatePtr CreatePtr;
	};

	struct CRLMapEntry {
		const char* Name;
		CreateCRLPtr CreatePtr;
	};

	class CertificateReg
	{
	public:
		static ICertificate* CreateCertificate(const char* name);
		static CreateCertificatePtr GetCreatePointer(const char* name);
		static const char* GetName(void* createptr);
		static const char* GetNextName(const char* name);
		static void Insert(const char* name, CreateCertificatePtr createptr);
		static void Insert(const CertificateMapEntry* certmap);
	};

	class CRLReg
	{
	public:
		static ICRL* CreateCRL(const char* name);
		static CreateCRLPtr GetCreatePointer(const char* name);
		static const char* GetName(void* createptr);
		static const char* GetNextName(const char* name);
		static void Insert(const char* name, CreateCRLPtr createptr);
		static void Insert(const CRLMapEntry* certmap);
	};
}
#endif

