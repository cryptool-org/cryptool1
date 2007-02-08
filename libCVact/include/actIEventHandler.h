// ---------------------------------------------------------------------------
// Name:      actIEventHandler.h
// Product:   cv act library
// Purpose:   The class IEventHandler defines the callback functions
//            
// Copyright: (c) 2002 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//
// Autor:	  Dr. Xiangdong Wang (XWG)
// Date:	  03/26/2002
// ---------------------------------------------------------------------------

#ifndef IEVENTHANDLER_H
#define IEVENTHANDLER_H


namespace act
{

	enum  EventCode {
		TOKEN_REMOVED	=	0x00000010,		// token removed
		TOKEN_INSERTED	=	0x00000020,		// token inserted
		SLOT_REMOVED	=	0x00000040		// slot removed
	};

	class IEventHandler
	{
	public:
		virtual ~IEventHandler() {}

		virtual void OnEvent(int event) = 0;		// token inserted, changed, removed,...
	};

} // namespace act

#endif



