//////////////////////////////////////////////////////////////////////////////////
// Name:      actLogger.h
// Product:   cv act library
// Purpose:   Logger
//
// Copyright: (c) 2000-2001 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//////////////////////////////////////////////////////////////////////////////////

#ifndef ACT_LOGGER_h
#define ACT_LOGGER_h

#include "actDebug.h"

#include "actBlob.h"
#include "SyncObject.h"


// for convenience:
#ifdef WIN32
	#define ACT_SNPRINTF _snprintf
#else
	#define ACT_SNPRINTF snprintf
#endif

//
// MTE [11/1/2006]: Added addtional accessing macros.
// NOTE: Redefine to use another Logger.
#define	ACT_LOGGER(x)		act::Logger::x

// 
// MTE [11/1/2006]: Added to replace direct usage of ACT_LOGGER(LogInit)().
#define ACT_LOGISENABLED()	(ACT_DEBUG != 0 || ACT_LOGGER(LogInit)())

//
// MTE [11/1/2006]: Changed to use ACT_LOGISENABLED().
#define ACT_LOGINFO(info)	{ if(ACT_LOGISENABLED()) ACT_LOGGER(Log)(ACT_LOGGER(LEVEL_INFO), info); }
#define ACT_LOGWARN(warn)	{ if(ACT_LOGISENABLED()) ACT_LOGGER(Log)(ACT_LOGGER(LEVEL_WARN), warn); }
#define ACT_LOGERROR(error)	{ if(ACT_LOGISENABLED()) ACT_LOGGER(Log)(ACT_LOGGER(LEVEL_ERROR), error); }
#define ACT_LOGEXCEPTION(e)	{ if(ACT_LOGISENABLED()) { char buf[1024]; ACT_SNPRINTF(buf, 1024, "Exception:\t '%s' in '%s'", e.what(), e.where()); ACT_LOGERROR(buf) }}

#define ACT_LOGINFODATA(info, data)	  { if(ACT_LOGISENABLED()) ACT_LOGGER(Log)(ACT_LOGGER(LEVEL_INFO), info, data); }
#define ACT_LOGWARNDATA(warn, data)   { if(ACT_LOGISENABLED()) ACT_LOGGER(Log)(ACT_LOGGER(LEVEL_WARN), warn, data); }
#define ACT_LOGERRORDATA(error, data) { if(ACT_LOGISENABLED()) ACT_LOGGER(Log)(ACT_LOGGER(LEVEL_ERROR), error, data); }

#define ACT_LOGBLOB(blob)			  { if(ACT_LOGISENABLED()) ACT_LOGGER(Log)(ACT_LOGGER(LEVEL_INFO), #blob, blob); }
#define ACT_LOGVALUE(value, format)	  { if(ACT_LOGISENABLED()) { char buf[256]; ACT_SNPRINTF(buf, 256, #value " :\t " format, value); ACT_LOGINFO(buf) }}

#define ACT_LOGINT(value)	 ACT_LOGVALUE(value, "%i")
#define ACT_LOGHEX(value)	 ACT_LOGVALUE(value, "0x%08x")
#define ACT_LOGSTRING(value) ACT_LOGVALUE(value, "%s")

// TODO: MTE: What about this "nice" construct ?
#define ACT_LOGPOINTER(p) { if(ACT_LOGISENABLED()) { if(p != 0) ACT_LOGINT(*p) else ACT_LOGHEX(p) }}
#define ACT_LOGISNULL(p)  { if(ACT_LOGISENABLED()) { char buf[256]; if(p != 0) ACT_SNPRINTF(buf, 256, #p " :\t *"); else ACT_SNPRINTF(buf, 256, #p " :\t 0"); ACT_LOGINFO(buf) }}


namespace act
{
	class Logger
	{
	public:
		enum Levels
		{
			LEVEL_OFF		=  0,
			LEVEL_ERROR		= 30,
			LEVEL_WARNING	= 50,
			LEVEL_WARN		= LEVEL_WARNING,
			LEVEL_INFO		= 80,
			LEVEL_MAX		= 99
		};

		static void SetLogger(Logger* pLogger);
		static void FreeLogger();
		static void Log(short level, const char* msg);
		static void Log(short level, const Blob& blobmsg);
		static void Log(short level, const char* msg, const Blob& blobmsg);
		static void SetLoglevel(short level);
		static bool LogInit()
		{
			return(s_pLogger != 0 ? true : false);
		}

	protected:
		Logger(){}
		virtual ~Logger(){}
		virtual void doLog(short level, const char* msg) = 0;
		virtual void doSetLoglevel(short level) = 0;

	private:
		static Logger* s_pLogger;
		static SyncObject m_sync;
	};
}

#endif // ACT_LOGGER_h

