// ---------------------------------------------------------------------------
// Name:      actSlotManager.h
// Product:   cv act library
// Purpose:   The class SlotManager detects and manages the subsystems and the slots
//            
// Copyright: (c) 2002 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//
// Autor:	  Dr. Xiangdong Wang (XWG)
// Date:	  03/26/2002
// ---------------------------------------------------------------------------

#ifndef SLOTMANAGER_H
#define SLOTMANAGER_H

namespace act
{
	class ISubsystem;
	class ISlot;

	class SlotManager
	{
	public:
		SlotManager();
		~SlotManager();

		bool Install(ISubsystem* );
		void Refresh();

		// SlotList
		const ISlot* GetSlot(int pos) const;
		int GetSlotNumber() const;
		ISlot* CreateSlot(const char* name) const;

	private:
		int m_total;

		struct SubsystemList {
			ISubsystem* subsys;
			SubsystemList* next;
		};
		SubsystemList*	m_current;
		SubsystemList*	m_begin;
	};

} // namespace act

#endif



