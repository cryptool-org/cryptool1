/*****************************************
 *
 * SECUDE Sicherheitstechnologie
 * Informationssystem GmbH, Darmstadt
 *
 * (C) Copyright SECUDE GmbH,  1997 - 2000
 *
 ******************************************/

#include <ocsp.h>

#if !defined(OCSPHL_H_) && defined(__cplusplus)
#define OCSPHL_H_

class COCSPQueryCertRef : private SingleOCSPQuery {
	friend class COCSPQuery;
private:
	COCSPQueryCertRef();
	~COCSPQueryCertRef();
	COCSPQueryCertRef operator=(COCSPQueryCertRef);
public:
	operator bool() const
		{ return this != NULL; }
	OCSPQueryCertStatusInfo getStatus() const
		{ return this
			? status : OCSPQCillegal; }
	OCSPCertStatusInfo getStatusInfo() const
		{ return this
			&& response
			&& response->certStatus
			? response->certStatus->type : OCSPCunknown; }
	Certificate *getResponderCert() const
		{ return this
			? responderCert : NULL; }
	GeneralTime *getThisUpdate() const
		{ return this
			&& response
			? response->thisUpdate : NULL; }
	GeneralTime *getNextUpdate() const
		{ return this
			&& response
			? response->nextUpdate : NULL; }
	GeneralTime *getRevocationTime() const
		{ return this
			&& response
			&& response->certStatus
			&& response->certStatus->type == OCSPCrevoked
			&& response->certStatus->value.revoked
			? response->certStatus->value.revoked->revocationTime : NULL; }
	CRLReason *getRevocationReason() const
		{ return this
			&& response
			&& response->certStatus
			&& response->certStatus->type == OCSPCrevoked
			&& response->certStatus->value.revoked
			? response->certStatus->value.revoked->revocationReason : NULL; }
	SEQUENCE_OF_Extension *getExtensions() const
		{ return this
			&& response
			? response->singleResponseExtensions : NULL; }
};

class COCSPResponseCache : private OCSPResponseCache {
private:
	bool inited;
public:
	COCSPResponseCache(unsigned long cacheTime = 0UL, unsigned long maxAge = 0UL, OCSPLockFunc *lockfunc = NULL, void *lockfunccontext = NULL)
		{ 
			ocsp_init_OCSPResponseCache(this, cacheTime, maxAge, lockfunc, lockfunccontext);
			inited = true;
		}
	COCSPResponseCache(bool init)
		{
			if (init)
				ocsp_init_OCSPResponseCache(this, 0UL, 0UL, NULL, NULL);
			inited = init;
		}
	~COCSPResponseCache()
		{ aux_free2_OCSPResponseCache(this); }
	void init(unsigned long cacheTime = 0UL, unsigned long maxAge = 0UL, OCSPLockFunc *lockfunc = NULL, void *lockfunccontext = NULL)
		{
			if (!inited)
				ocsp_init_OCSPResponseCache(this, cacheTime, maxAge, lockfunc, lockfunccontext);
			inited = true;
		}
	void clean(GeneralTime *when = NULL)
		{ ocsp_clean_OCSPResponseCache(this, when); }
	void setCacheTime(unsigned long age = 0UL)
		{ cacheTime = age; }
	void setMaxAge(unsigned long age = 0UL)
		{ maxAge = age; }
	void setLockFunc(OCSPLockFunc *func = NULL, void *context = NULL)
		{ lockfunc = func; lockfunccontext = context; }
	friend class COCSPQuery;
};

class COCSPQuery : private OCSPQuery {
public:
	COCSPQuery()
		{ ocsp_init_OCSPQuery(this); }
	~COCSPQuery()
		{ aux_free2_OCSPQuery(this); }
	int getTransportStatus() const
		{ return this->transportStatus; }
	const char *getTransportMessage() const
		{ return this->transportMessage; }
	OCSPQueryStatus getQueryStatus() const
		{ return this->queryStatus; }
	Certificate *getResponderCert() const
		{ return this->responderCert; }
	GeneralTime *getReceivedAt() const
		{ return this->receivedAt; }
	GeneralTime *getProducedAt()
		{ return this->tbsResponse ? this->tbsResponse->producedAt : NULL; }
	const COCSPQueryCertRef * addCertificate(KeyInfo* cakey, Certificate* cert)
		{ return (COCSPQueryCertRef*)ocsp_add_SingleOCSPQuery(this, cakey, cert); }
	const COCSPQueryCertRef * findCertificate(Certificate* cert)
		{ return NULL; }
	RC doQuery(PSE pse,
			SEQUENCE_OF_Certificate *requestCerts,
			OCSPQueryFunc *queryfunc,
			const char *responderuri = NULL,
			void *queryfunccontext = NULL,
			OCSPLockFunc *lockfunc = NULL,
			void *lockfunccontext = NULL
			)
		{ return ocsp_do_OCSPQuery(this, pse, requestCerts, queryfunc, responderuri, queryfunccontext, lockfunc, lockfunccontext); }
	OctetString *saveResponse(void) const
		{ return ocsp_save_OCSPResponse(this); }
	RC restoreResponse(OctetString *response, GeneralTime *receivedAt = NULL)
		{ return ocsp_restore_OCSPResponse(this, response, receivedAt); }
	RC cacheResponse(COCSPResponseCache *cache)
		{ return ocsp_cache_OCSPResponse(this, cache); }
	RC retrieveResponse(COCSPResponseCache *cache, GeneralTime *when = NULL)
		{ return ocsp_retrieve_OCSPResponse(this, cache, when); }
	RC matchQuery(KeyInfo *trustedOCSPCAKey = NULL, DName *trustedOCSPCAName = NULL, KeyInfo *trustedOCSPKey = NULL)
		{ return ocsp_match_OCSPQuery(this, trustedOCSPCAKey, trustedOCSPCAName, trustedOCSPKey); }
	void setHashAlgorithm(AlgId *alg = NULL)
		{ aux_free_AlgId(&hashAlgorithm); hashAlgorithm = alg ? aux_cpy_AlgId(alg) : NULL; }
	void setRequireNonce(Boolean flag = TRUE)
		{ requireNonce = flag; }
	void setRequireCertHashe(Boolean flag = TRUE)
		{ requireCertHash = flag; }
	void setSign(Boolean flag = TRUE)
		{ signRequest = flag; }
	void setCheckExtensions(Boolean flag = TRUE)
		{ checkExtensions = flag; }
	void setIncludeServiceLocator(Boolean flag = TRUE)
		{ includeServiceLocator = flag; }
	void setExGeneralNameBug(Boolean flag = TRUE)
		{ exGeneralNameBug = flag; }
	void setTraceFunc(OCSPTraceFunc *traceFunc, void *traceFuncContext = NULL, OCSPTraceLevel traceLevel = OCSP_TRACEWARNING)
		{
			this->traceFunc = traceFunc;
			this->traceFuncContext = traceFuncContext;
			this->traceLevel = traceLevel;
		}
};

#endif /* OCSPHL_H_ */

