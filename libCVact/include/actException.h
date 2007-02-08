//////////////////////////////////////////////////////////////////////////////////
// Name:      actException.h
// Product:   cv act library
// Purpose:   exception hierarchy
//
// Copyright: (c) 2000 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//////////////////////////////////////////////////////////////////////////////////


#ifndef ACT_EXCEPTION_H
#define ACT_EXCEPTION_H

namespace act
{
#ifndef UNDER_CE

	// base class for all exceptions thrown by cv act

	class Exception
	{
	public:
		explicit Exception(const char *msg = 0, const char *where = 0) :  m_what(msg), m_where(where) {}
		virtual ~Exception() throw() {}
		virtual const char *what() const throw() { if (m_what != 0) return m_what; else return "";}
		virtual const char *where() const throw() {if (m_where != 0) return m_where; else return "";}
	private:
		const char *m_what;
		const char *m_where;
	};


	class BadException : public Exception
	{
		public:
			BadException(const char *msg = 0, const char *where = 0) : Exception(msg,where) {}
	};

	class NullPointerException : public BadException 
	{
		public:
			NullPointerException(const char *msg = 0, const char *where = 0) : BadException(msg,where) {}
	};

	class OutOfRangeException : public BadException 
	{
		public:
			OutOfRangeException(const char *msg = 0, const char *where = 0) : BadException(msg,where) {}
	};


	// ---------------------------------------------------------------------------
	class LogicalException : public Exception
	{
		public:
			LogicalException(const char *msg = 0, const char *where = 0) : Exception(msg,where) {}
	};


	class ASN1Exception : public LogicalException
	{
		public:
			ASN1Exception(const char *msg = 0, const char *where = 0) : LogicalException(msg,where) {}
	};

	class NoSuchDLLException : public LogicalException
	{
		public:
			NoSuchDLLException(const char *msg = 0, const char *where = 0) : LogicalException(msg,where) {}
	};

	class PasswordException : public LogicalException
	{
		public:
			PasswordException(const char *msg = 0, const char *where = 0) : LogicalException(msg,where) {}
	};

	// ---------------------------------------------------------------------------
	class AlgorithmException : public LogicalException
	{
		public:
			AlgorithmException(const char *msg = 0, const char *where = 0) : LogicalException(msg,where) {}
	};

	class InvalidAlgorithmParameterException : public AlgorithmException
	{
		public:
			InvalidAlgorithmParameterException(const char *msg = 0, const char *where = 0) : AlgorithmException(msg,where) {}
	};


	class NoSuchAlgorithmException : public AlgorithmException
	{
		public:
			NoSuchAlgorithmException(const char *msg = 0, const char *where = 0) : AlgorithmException(msg,where) {}
	};

	class ArithmeticException : public LogicalException
	{
		public:
			ArithmeticException(const char *msg = 0, const char *where = 0) : LogicalException(msg,where) {}
	};

	// ---------------------------------------------------------------------------
	class CertificateException : public LogicalException
	{
		public:
			CertificateException(const char *msg = 0, const char *where = 0) : LogicalException(msg,where) {}
	};

	class CertificateEncodingException : public CertificateException
	{
		public:
			CertificateEncodingException(const char *msg = 0, const char *where = 0) : CertificateException(msg,where) {}
	};

	class CertificateExpiredException : public CertificateException
	{
		public:
			CertificateExpiredException(const char *msg = 0, const char *where = 0) : CertificateException(msg,where) {}
	};

	class CertificateNotYetValidException : public CertificateException
	{
		public:
			CertificateNotYetValidException(const char *msg = 0, const char *where = 0) : CertificateException(msg,where) {}
	};

	class CertificateParsingException : public CertificateException
	{
		public:
			CertificateParsingException(const char *msg = 0, const char *where = 0) : CertificateException(msg,where) {}
	};

	// ---------------------------------------------------------------------------
	class KeyException : public LogicalException
	{
		public:
			KeyException(const char *msg = 0, const char *where = 0) : LogicalException(msg,where) {}
	};

	class InvalidKeyException : public KeyException
	{
		public:
			InvalidKeyException(const char *msg = 0, const char *where = 0) : KeyException(msg,where) {}
	};

	class KeyManagementException : public KeyException
	{
		public:
			KeyManagementException(const char *msg = 0, const char *where = 0) : KeyException(msg,where) {}
	};

	class MessageDigestException : public LogicalException
	{
		public:
			MessageDigestException(const char *msg = 0, const char *where = 0) : LogicalException(msg,where) {}
	};

	class PaddingException : public LogicalException
	{
		public:
			PaddingException(const char *msg = 0, const char *where = 0) : LogicalException(msg,where) {}
	};

	class SignatureException : public LogicalException
	{
		public:
			SignatureException(const char *msg = 0, const char *where = 0) : LogicalException(msg,where) {}
	};

	// ---------------------------------------------------------------------------
	class SmartcardException : public LogicalException
	{
		public:
			SmartcardException(const char *msg = 0, const char *where = 0, long code = 0) 
				: LogicalException(msg,where)
				, m_code(code) 
			{}

			virtual long code() const throw() {return m_code;}
		private:
			long m_code;
	};

	class InvalidPinException : public SmartcardException
	{
		public:
			InvalidPinException(const char *msg = 0, const char *where = 0, long code = 0) : SmartcardException(msg,where,code) {}
	};

	class PinLockedException : public SmartcardException
	{
		public:
			PinLockedException(const char *msg = 0, const char *where = 0, long code = 0) : SmartcardException(msg,where,code) {}
	};

	class PinExpiredException : public SmartcardException
	{
		public:
			PinExpiredException(const char *msg = 0, const char *where = 0, long code = 0) : SmartcardException(msg,where,code) {}
	};

	class PinLenRangeException : public SmartcardException
	{
		public:
			PinLenRangeException(const char *msg = 0, const char *where = 0, long code = 0) : SmartcardException(msg,where,code) {}
	};

	class InvalidCardException : public SmartcardException
	{
		public:
			InvalidCardException(const char *msg = 0, const char *where = 0, long code = 0) : SmartcardException(msg,where,code) {}
	};

	class CardOutOfMemoryException : public SmartcardException
	{
		public:
			CardOutOfMemoryException(const char *msg = 0, const char *where = 0, long code = 0) : SmartcardException(msg,where,code) {}
	};

	// ---------------------------------------------------------------------------
	class RuntimeException : public Exception
	{
		public:
			RuntimeException(const char *msg = 0, const char *where = 0) : Exception(msg,where) {}
	};
	
	class BadAllocException : public RuntimeException
	{
		public:
			BadAllocException(const char *msg = 0, const char *where = 0) : RuntimeException(msg,where) {}
	};


#else

	#define throw(_x)	_exit(_x)

	enum
	{
		EXCEPTION = 1,
			BADEXCEPTION = 10,
				NULLPOINTEREXCEPTION = 100,
				OUTOFRANGEEXCEPTION = 101,
			LOGICALEXCEPTION = 11,
				ALGORITHMEXCEPTION = 110,
					INVALIDALGORITHMPARAMETEREXCEPTION = 1100,
					NOSUCHALGORITHMEXCEPTION = 1101,
				ARITHMETICEXCEPTION = 111,
				CERTIFICATEEXCEPTION = 112,
					CERTIFICATEENCODINGEXCEPTION = 1120,
					CERTIFICATEEXPIREDEXCEPTION = 1121,
					CERTIFICATENOTYETVALIDEXCEPTION = 1122,
					CERTIFICATEPARSINGEXCEPTION = 1123,
				KEYEXCEPTION = 113,
					INVALIDKEYEXCEPTION = 1130,
					KEYMANAGEMENTEXCEPTION = 1131,
				MESSAGEDIGESTEXCEPTION = 114,
				PADDINGEXCEPTION = 115,
				SIGNATUREEXCEPTION = 116,
				SMARTCARDEXCEPTION = 117,
					INVALIDPINEXCEPTION = 1170,
					INVALIDCARDEXCEPTION = 1171,
			RUNTIMEEXCEPTION = 12,
				BADALLOCEXCEPTION = 120
	};

	int Exception(const char *msg = 0, const char *where = 0);
		int BadException(const char *msg = 0, const char *where = 0);
			int	NullPointerException(const char *msg = 0, const char *where = 0);
			int	OutOfRangeException(const char *msg = 0, const char *where = 0);
		int	LogicalException(const char *msg = 0, const char *where = 0);
			int	AlgorithmException(const char *msg = 0, const char *where = 0);
				int	InvalidAlgorithmParameterException(const char *msg = 0, const char *where = 0);
				int	NoSuchAlgorithmException(const char *msg = 0, const char *where = 0);
			int ArithmeticException(const char *msg = 0, const char *where = 0);
			int	CertificateException(const char *msg = 0, const char *where = 0);
				int	CertificateEncodingException(const char *msg = 0, const char *where = 0);
				int	CertificateExpiredException(const char *msg = 0, const char *where = 0);
				int	CertificateNotYetValidException(const char *msg = 0, const char *where = 0);
				int	CertificateParsingException(const char *msg = 0, const char *where = 0);
			int	KeyException(const char *msg = 0, const char *where = 0);
				int	InvalidKeyException(const char *msg = 0, const char *where = 0);
				int	KeyManagementException(const char *msg = 0, const char *where = 0);
			int	MessageDigestException(const char *msg = 0, const char *where = 0);
			int	PaddingException(const char *msg = 0, const char *where = 0);
			int SignatureException(const char *msg = 0, const char *where = 0);
			int SmartcardException(const char *msg = 0, const char *where = 0,long code = 0);
				int InvalidPinException(const char *msg = 0, const char *where = 0, long code = 0);
				int InvalidCardException(const char *msg = 0, const char *where = 0, long code = 0);
		int	RuntimeException(const char *msg = 0, const char *where = 0);
			int BadAllocException(const char *msg = 0, const char *where = 0);


#endif // UNDER_CE

}// namespace act

#endif // ACT_EXCEPTION_H

