// ---------------------------------------------------------------------------
// Name:      actISubsystem.h
// Product:   cv act library
// Purpose:   The class ISubsystem detects and manages the slots
//            
// Copyright: (c) 2002 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//
// Autor:	  Dr. Xiangdong Wang (XWG)
// Date:	  03/26/2002
// ---------------------------------------------------------------------------

#ifndef ISUBSYSTEM_H
#define ISUBSYSTEM_H

namespace act
{
	class ISlot;

	class ISubsystem
	{
	public:
		virtual void IncReferenceCounter() = 0;
		virtual void Destroy() = 0;

		virtual void Refresh() = 0;
		virtual const char* GetName() const = 0;
		virtual void Install(int port) {;}

		// SlotList
		virtual const ISlot* GetSlot(int pos) const = 0;
		virtual int GetSlotNumber() const = 0;
		virtual ISlot* CreateSlot(const char* name) = 0;
	
	protected:
		virtual ~ISubsystem() {}

	};

} // namespace act

#endif



