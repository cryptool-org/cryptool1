// ---------------------------------------------------------------------------
// Name:      actISlot.h
// Product:   cv act library
// Purpose:   The class ISlot manages the Tokens
//            
// Copyright: (c) 2002 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//
// Autor:	  Dr. Xiangdong Wang (XWG)
// Date:	  03/26/2002
// ---------------------------------------------------------------------------

#ifndef ISLOT_H
#define ISLOT_H

#include "actBasics.h"
#include "actBlob.h"

namespace act
{
	class IToken;
	class IEventHandler;
	class ISubsystem;

	class ISlot
	{
	public:

		virtual ISlot* Clone() const = 0;

		virtual void IncReferenceCounter() = 0;
		virtual void Destroy() = 0;

		virtual bool IsTokenPresent() const = 0;
		virtual const char* GetName() const = 0;
		virtual Blob GetATR() const = 0;
		virtual const ISubsystem* GetSystem() const = 0;

		virtual IToken* CreateToken() = 0;
		virtual void NotifyEvent(IEventHandler* cmd) = 0;

		virtual Blob GetHistoricalBytes() const = 0;

		virtual void SetParam(paramid_t id,int val) = 0;
		virtual int  GetParam(paramid_t id) const = 0;

	protected:
		virtual ~ISlot() {}

	};

	const char* GetOSName(const Blob& atr);


} // namespace act

#endif



