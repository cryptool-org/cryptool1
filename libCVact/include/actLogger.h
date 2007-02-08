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

#include "actBlob.h"
#include "SyncObject.h"

// for convenience:
#ifdef WIN32
	#define ACT_SNPRINTF _snprintf
#else
	#define ACT_SNPRINTF snprintf
#endif

#define ACT_LOGERROR(error)	{ if (act::Logger::LogInit()) act::Logger::Log(act::Logger::LEVEL_ERROR, error);}
#define ACT_LOGEXCEPTION(e) { if (act::Logger::LogInit()) { char buf[256]; ACT_SNPRINTF(buf, 256, "Exception:\t '%s' in '%s'", e##.what(), e##.where()); ACT_LOGERROR(buf)}}
#define ACT_LOGWARN(warn) { if (act::Logger::LogInit()) act::Logger::Log(act::Logger::LEVEL_WARNING, warn);}
#define ACT_LOGINFO(info) { if (act::Logger::LogInit()) act::Logger::Log(act::Logger::LEVEL_INFO, info);}

#define ACT_LOGERRORDATA(error, data)	{ if (act::Logger::LogInit()) act::Logger::Log(act::Logger::LEVEL_ERROR, error, data);}
#define ACT_LOGWARNDATA(warn, data)		{ if (act::Logger::LogInit()) act::Logger::Log(act::Logger::LEVEL_WARNING, warn, data);}
#define ACT_LOGINFODATA(info, data)		{ if (act::Logger::LogInit()) act::Logger::Log(act::Logger::LEVEL_INFO, info, data);}

#define ACT_LOGBLOB(blob) { if (act::Logger::LogInit()) act::Logger::Log(act::Logger::LEVEL_INFO, #blob, blob);}
#define ACT_LOGINT(intvalue) { if (act::Logger::LogInit()) { char buf[256]; ACT_SNPRINTF(buf, 256, #intvalue " :\t %i", intvalue); ACT_LOGINFO(buf)}}
#define ACT_LOGHEX(hexvalue) { if (act::Logger::LogInit()) { char buf[256]; ACT_SNPRINTF(buf, 256, #hexvalue " :\t 0x%08x", hexvalue); ACT_LOGINFO(buf)}}
#define ACT_LOGSTRING(stringvalue) { if (act::Logger::LogInit()) { char buf[256]; ACT_SNPRINTF(buf, 256, #stringvalue ":\t %s", stringvalue); ACT_LOGINFO(buf)}}

#define ACT_LOGPOINTER(p) { if (act::Logger::LogInit()) {	if (p != 0)	{ACT_LOGINT(*p);} else {ACT_LOGHEX(p);}}}
#define ACT_LOGISNULL(p)  { if (act::Logger::LogInit()) { char buf[256]; if (p !=0) ACT_SNPRINTF(buf, 256, #p " :\t *"); else ACT_SNPRINTF(buf, 256, #p " :\t 0"); ACT_LOGINFO(buf)}}


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
			LEVEL_INFO		= 80,
			LEVEL_MAX		= 99
		};

		static void SetLogger(Logger* pLogger);
		static void FreeLogger();
		static void Log(short level, const char* msg);
		static void Log(short level, const Blob& blobmsg);
		static void Log(short level, const char* msg, const Blob& blobmsg);
		static void SetLoglevel(short level);
		static bool LogInit() { if (s_pLogger) return true; else return false;}

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

