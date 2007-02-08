// ---------------------------------------------------------------------------
// Name:      actISCardAccess.h
// Product:   cv act library
// Purpose:   The class ISCardAccess manages the operations with the smartcards and readers
//            
// Copyright: (c) 2002 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//
// Autor:	  Dr. Xiangdong Wang (XWG)
// Date:	  03/21/2002
// ---------------------------------------------------------------------------

#ifndef ISCARDACCESS_H
#define ISCARDACCESS_H

#include "actBasics.h"
#include "actBlob.h"

namespace act
{
	// ---------------------------------------------------------------------------
	#define APDUSUCCESS(sw1sw2)	((sw1sw2 == act::APDU_OK) | (sw1sw2 == act::APDU_OK1))

	const int RESPONSE_MAXLEN = 300;

	enum  ReturnCode {
		APDU_OK					= 0x9000,
		APDU_OK1				= 0x9001,


		// error codes defined in ISO7816-4
		APDU_STATE_UNCHANGED		= 0x6200,
		APDU_RETURN_CORRUPTED		= 0x6281,
		APDU_END_REACHED			= 0x6282,
		APDU_SELECTFILE_INVALID		= 0x6283,
		APDU_FCI_FORMAT				= 0x6284,

		APDU_AUTHEN_FAILED			= 0x6300,
		APDU_FILE_FILLED_UP			= 0x6381,

		APDU_STATE_UNCHANGED2		= 0x6400,

		APDU_STATE_CHANGED			= 0x6500,
		APDU_MEMORY_FAILURE			= 0x6581,

		APDU_SECURITY_ERROR			= 0x6600,	// not defined in ISO7816

		APDU_WRONG_LEN				= 0x6700,

		APDU_NO_CLA_FUNCTION		= 0x6800,
		APDU_NO_LOGICAL_CHANNEL		= 0x6881,
		APDU_NO_SM					= 0x6882,

		APDU_CMD_NOT_ALLOWED		= 0x6900,
		APDU_CMD_INCOMPATIBLE		= 0x6981,
		APDU_SECURITY_STATE			= 0x6982,
		APDU_AUTHEN_BLOCKED			= 0x6983,
		APDU_REF_DATA_INVALID		= 0x6984,
		APDU_NO_CONDITION_			= 0x6985,
		APDU_CMD_EF_NOT_ALLOWED		= 0x6986,
		APDU_SM_DATA_MISSING		= 0x6987,
		APDU_SM_DATA_INCORRECT		= 0x6988,

		APDU_WRONG_PARAMETER		= 0x6A00,
		APDU_WRONG_DATA				= 0x6A80,
		APDU_FUNCTION_NOT_SUPPORTED	= 0x6A81,
		APDU_FILE_NOT_FOUND			= 0x6A82,
		APDU_RECORD_NOT_FOUND		= 0x6A83,
		APDU_NOT_ENOUGH_MEMORY		= 0x6A84,
		APDU_LC_TLV_INCONSISTENT	= 0x6A85,
		APDU_INVALID_P1P2			= 0x6A86,
		APDU_LC_P1P2_INCONSISTENT	= 0x6A87,
		APDU_REF_DATA_NOT_FOUND		= 0x6A88,

		APDU_WRONG_PARAMETER2		= 0x6B00,

		APDU_WRONG_LE				= 0x6C00,

		APDU_INS_INVALID			= 0x6D00,

		APDU_CLA_INVALID			= 0x6E00,

		APDU_TECHNICAL_ERROR		= 0x6F00,


		// other error codes depend on card OS
		APDU_NO_ICC				= 0x64a1,
		APDU_PROTOCOL_ERROR		= 0x64a8,
		
		APDU_NO_AC_RIGHT		= 0x6982,
		APDU_PIN_LOCKED			= 0x6983,
		APDU_PIN_FORMAT_ERROR	= 0x6984,

		APDU_BAD_PIN_NO			= 0x6a88
		
	};

	enum ProtocolType {
		PROTOCOL_UNDEFINED  =  0x0000,  // There is no active protocol.
		PROTOCOL_T0         =  0x0001,  // T=0 is the active protocol.
		PROTOCOL_T1         =  0x0002,  // T=1 is the active protocol.
		PROTOCOL_RAW        =  0x10000  // Raw is the active protocol.
	};

	enum DispositionType {
		LEAVE_CARD = 0,			// Don't do anything special. 
		RESET_CARD = 1,			// Reset the card. 
		UNPOWER_CARD = 2,		// Power down the card. 
		EJECT_CARD = 3			// Eject the card. */
	};


	class ISlot;

	// ---------------------------------------------------------------------------
	class ISCardAccess
	{
	public:

		virtual ~ISCardAccess() {}

		virtual long GetProtocol() const = 0;
		virtual void SetProtocol(long protocol) = 0;

		virtual void Open() = 0;
		virtual void Close() = 0;
		virtual void ResetCard() = 0;

		virtual void BeginTransaction() = 0;
		virtual void EndTransaction(word disposition = LEAVE_CARD) = 0;

		virtual word SendCard(const Blob& cmd, Blob& response) = 0;

		virtual const ISlot* GetSlot() const = 0;
		virtual Blob GetResponse() const = 0;
		
		virtual word Send(const Blob& cmd) = 0;
		virtual word Send(const Blob& header, const Blob& data) = 0;
		virtual word Send(const Blob& header, const Blob& data, byte le) = 0;

		virtual word Send(const std::string& cmd) = 0;
		virtual word Send(const std::string& header, const std::string& data) = 0;
		virtual word Send(const std::string& header, const std::string& data, byte le) = 0;

		// Extended APDU
		virtual word SendX(const Blob& header, const Blob& data) = 0;
		virtual word SendX(const Blob& header, const Blob& data, unsigned short le) = 0;
		virtual word SendX(const std::string& header, const std::string& data) = 0;
		virtual word SendX(const std::string& header, const std::string& data, unsigned short le) = 0;


	};

} // namespace act
#endif

