// ---------------------------------------------------------------------------
// Name:      actISCardOS.h
// Product:   cv act library
// Purpose:   The class ISCardOS accesses the card operating system
//            
// Copyright: (c) 2002 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//
// Autor:	  Dr. Xiangdong Wang (XWG)
// Date:	  03/21/2002
// ---------------------------------------------------------------------------

#ifndef ISCARDOS_H
#define ISCARDOS_H

#include "actBasics.h"
#include "actBlob.h"

namespace act
{
	class ISCardAccess;
	class IEMSAAlg;
	class IKey;

	enum SCARD_FILETYPE	{
		MFType		= 0, 
		DFType		= 1, 
		EFType		= 2, 
		AIDType		= 4,
		PathType	= 8
	};

	class ISCardOS
	{
	public:
		virtual ~ISCardOS() {}

		virtual Blob GetSerialNumber() const = 0;								// hardware serial number
		virtual const char* GetName() const = 0;
		virtual ISCardAccess* GetAccess() const = 0;

		// COS specific functions
		virtual Blob ComputeDigitalSignature(const Blob& data) = 0;
		virtual Blob ComputeDigitalSignature(IEMSAAlg* emsa) = 0;
		virtual Blob Decipher(const Blob& encrypted_data) = 0;
		virtual Blob AgreeKey(const Blob& pubkey) = 0;

		virtual Blob SelectFile(const int filetype, const char* filepath) = 0;	// return file control information
		virtual Blob SelectFile(const int filetype, const Blob& filepath) = 0;	// return file control information
		virtual Blob SelectFile(const int filetype, unsigned short fid) = 0;	// return file control information
		virtual void SelectApp(const Blob &aid) = 0;
		virtual void SelectAID(int nr = 1) = 0;

		virtual Blob GetAID(int nr = 1) = 0;
		virtual Blob ReadBinary(const char* filepath) = 0;
		virtual Blob ReadBinary(const Blob& filepath) = 0;
		virtual Blob ReadBinary(unsigned short fid) = 0;
		virtual Blob ReadRecord(byte recnr) = 0;
		virtual void UpdateBinary(const Blob& filepath, const Blob& data, unsigned short offset = 0) = 0;
		virtual void UpdateBinary(unsigned short fid, const Blob& data, unsigned short offset = 0) = 0;

		virtual void DeleteEF(const Blob& fid) = 0;
		virtual void DeleteEF(unsigned short fid) = 0;

		virtual void CreateEF(const Blob& fci) = 0;
		virtual void CreateEF(const Blob& fid, unsigned short len, bool secure = false) = 0;
		virtual void CreateEF(unsigned short fid, unsigned short len, bool secure = false) = 0;

		virtual Blob GetRandom(const unsigned long count) const = 0;
	};

} // namespace act

#endif


