// ---------------------------------------------------------------------------
// Name:      actISlotMonitor.cpp
// Product:   cv act library
// Purpose:   The class SlotMonitor notifies the slot events
//            
// Copyright: (c) 2002 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//
// Autor:	  Dr. Xiangdong Wang (XWG)
// Date:	  05/27/2002
// ---------------------------------------------------------------------------
#ifndef ISLOTMONITOR_H
#define ISLOTMONITOR_H

namespace act
{
	class IEventHandler;

	class ISlotMonitor
	{
	public:
		virtual ~ISlotMonitor() {}

		virtual void Start(IEventHandler* cmd) = 0;
		virtual void Stop() = 0;
		virtual bool Interrupted() const = 0;

	protected:
		virtual void Run() = 0;
	};
}
#endif	// act



