/*###*****************************************
 *###
 *### SECUDE IT Security GmbH
 *###
 *### Copyright (c) 2004-2006
 *###
 *### File ./include/secude/f_macros.h
 *###
 *### global functions:
 *###
 *###*****************************************/

#ifndef FUNCTION_MACROS_H_
#define FUNCTION_MACROS_H_


/*
 *	Macros for extended global variable and function declaration
 *
 *	SEC_PROTOTYPE_*		function prototype declaration 
 *				(depending on __STDC__)
 *
 *	SEC_DECLARATION_*	function header declaration
 *				(depending on __STDC__)
 *
 *	SEC_GLOBAL_FUNC_PREFIX	prefix for global variables and functions
 *				(e.g. for Windows)
 *
 *	SEC_STATIC_FUNC_PREFIX	prefix for static symbols
 *
 */




#ifdef _WIN32
#ifndef SECUDE_STATIC_LIB
#ifdef SECUDE_DLL_EXPORT
#ifdef SEC_MSC
#define SEC_GLOBAL_FUNC_PREFIX		__declspec( dllexport )
#else
#define SEC_GLOBAL_FUNC_PREFIX		/* is done in CALLING_CONV! */
#define SEC_API_CALLING_CONV		_export
#define SEC_GLOBAL_VAR_PREFIX		_export
#endif
#else
#ifdef SEC_MSC
#define SEC_GLOBAL_FUNC_PREFIX		__declspec( dllimport )
#else
#define SEC_GLOBAL_FUNC_PREFIX		/* is done in CALLING_CONV! */
#define SEC_API_CALLING_CONV		__import
#define SEC_GLOBAL_VAR_PREFIX		__import
#endif
#endif
#endif
#ifdef SEC_MSC
#define SEC_API_CALLING_CONV		__stdcall
#endif
#endif

#ifndef SEC_STATIC_FUNC_PREFIX
#define SEC_STATIC_FUNC_PREFIX		/* nope */
#endif /* SEC_GLOBAL_FUNC_PREFIX */

#ifndef SEC_GLOBAL_FUNC_PREFIX
#define SEC_GLOBAL_FUNC_PREFIX
#endif

#ifndef SEC_API_CALLING_CONV
#define SEC_API_CALLING_CONV
#endif

#ifndef SEC_GLOBAL_VAR_PREFIX
#define SEC_GLOBAL_VAR_PREFIX
#endif

#ifdef OS2
#undef SEC_API_CALLING_CONV
#define SEC_API_CALLING_CONV _Optlink
#endif

#define SEC_CALLBACK(t, f) t (SEC_API_CALLING_CONV f)

#if defined(USE_ANSI_PROTOTYPES)
#define SEC_PROTOTYPE_0() \
	(void)
#define SEC_PROTOTYPE_1(ta,a) \
	(ta a)
#define SEC_PROTOTYPE_2(ta,a,tb,b) \
	(ta a,tb b)
#define SEC_PROTOTYPE_3(ta,a,tb,b,tc,c) \
	(ta a,tb b,tc c)
#define SEC_PROTOTYPE_4(ta,a,tb,b,tc,c,td,d) \
	(ta a,tb b,tc c,td d)
#define SEC_PROTOTYPE_5(ta,a,tb,b,tc,c,td,d,te,e) \
	(ta a,tb b,tc c,td d,te e)
#define SEC_PROTOTYPE_6(ta,a,tb,b,tc,c,td,d,te,e,tf,f) \
	(ta a,tb b,tc c,td d,te e,tf f)
#define SEC_PROTOTYPE_7(ta,a,tb,b,tc,c,td,d,te,e,tf,f,tg,g) \
	(ta a,tb b,tc c,td d,te e,tf f,tg g)
#define SEC_PROTOTYPE_8(ta,a,tb,b,tc,c,td,d,te,e,tf,f,tg,g,th,h) \
	(ta a,tb b,tc c,td d,te e,tf f,tg g,th h)
#define SEC_PROTOTYPE_9(ta,a,tb,b,tc,c,td,d,te,e,tf,f,tg,g,th,h,ti,i) \
	(ta a,tb b,tc c,td d,te e,tf f,tg g,th h,ti i)
#define SEC_PROTOTYPE_10(ta,a,tb,b,tc,c,td,d,te,e,tf,f,tg,g,th,h,ti,i,tj,j) \
	(ta a,tb b,tc c,td d,te e,tf f,tg g,th h,ti i,tj j)
#define SEC_PROTOTYPE_11(ta,a,tb,b,tc,c,td,d,te,e,tf,f,tg,g,th,h,ti,i,tj,j,tk,k) \
	(ta a,tb b,tc c,td d,te e,tf f,tg g,th h,ti i,tj j,tk k)
#define SEC_PROTOTYPE_12(ta,a,tb,b,tc,c,td,d,te,e,tf,f,tg,g,th,h,ti,i,tj,j,tk,k,tl,l) \
	(ta a,tb b,tc c,td d,te e,tf f,tg g,th h,ti i,tj j,tk k,tl l)
#define SEC_PROTOTYPE_13(ta,a,tb,b,tc,c,td,d,te,e,tf,f,tg,g,th,h,ti,i,tj,j,tk,k,tl,l,tm,m) \
	(ta a,tb b,tc c,td d,te e,tf f,tg g,th h,ti i,tj j,tk k,tl l,tm m)
#define SEC_PROTOTYPE_14(ta,a,tb,b,tc,c,td,d,te,e,tf,f,tg,g,th,h,ti,i,tj,j,tk,k,tl,l,tm,m,tn,n) \
	(ta a,tb b,tc c,td d,te e,tf f,tg g,th h,ti i,tj j,tk k,tl l,tm m,tn n)
#define SEC_PROTOTYPE_15(ta,a,tb,b,tc,c,td,d,te,e,tf,f,tg,g,th,h,ti,i,tj,j,tk,k,tl,l,tm,m,tn,n,to,o) \
	(ta a,tb b,tc c,td d,te e,tf f,tg g,th h,ti i,tj j,tk k,tl l,tm m,tn n,to o)
#define SEC_PROTOTYPE_16(ta,a,tb,b,tc,c,td,d,te,e,tf,f,tg,g,th,h,ti,i,tj,j,tk,k,tl,l,tm,m,tn,n,to,o,tp,p) \
	(ta a,tb b,tc c,td d,te e,tf f,tg g,th h,ti i,tj j,tk k,tl l,tm m,tn n,to o,tp p)
#define SEC_PROTOTYPE_17(ta,a,tb,b,tc,c,td,d,te,e,tf,f,tg,g,th,h,ti,i,tj,j,tk,k,tl,l,tm,m,tn,n,to,o,tp,p,tq,q) \
	(ta a,tb b,tc c,td d,te e,tf f,tg g,th h,ti i,tj j,tk k,tl l,tm m,tn n,to o,tp p,tq q)
#define SEC_PROTOTYPE_18(ta,a,tb,b,tc,c,td,d,te,e,tf,f,tg,g,th,h,ti,i,tj,j,tk,k,tl,l,tm,m,tn,n,to,o,tp,p,tq,q,tr,r) \
	(ta a,tb b,tc c,td d,te e,tf f,tg g,th h,ti i,tj j,tk k,tl l,tm m,tn n,to o,tp p,tq q, tr r)
#define SEC_DECLARATION_0() \
	(void)
#define SEC_DECLARATION_1(ta,a) \
	(ta a)
#define SEC_DECLARATION_2(ta,a,tb,b) \
	(ta a,tb b)
#define SEC_DECLARATION_3(ta,a,tb,b,tc,c) \
	(ta a,tb b,tc c)
#define SEC_DECLARATION_4(ta,a,tb,b,tc,c,td,d) \
	(ta a,tb b,tc c,td d)
#define SEC_DECLARATION_5(ta,a,tb,b,tc,c,td,d,te,e) \
	(ta a,tb b,tc c,td d,te e)
#define SEC_DECLARATION_6(ta,a,tb,b,tc,c,td,d,te,e,tf,f) \
	(ta a,tb b,tc c,td d,te e,tf f)
#define SEC_DECLARATION_7(ta,a,tb,b,tc,c,td,d,te,e,tf,f,tg,g) \
	(ta a,tb b,tc c,td d,te e,tf f,tg g)
#define SEC_DECLARATION_8(ta,a,tb,b,tc,c,td,d,te,e,tf,f,tg,g,th,h) \
	(ta a,tb b,tc c,td d,te e,tf f,tg g,th h)
#define SEC_DECLARATION_9(ta,a,tb,b,tc,c,td,d,te,e,tf,f,tg,g,th,h,ti,i) \
	(ta a,tb b,tc c,td d,te e,tf f,tg g,th h,ti i)
#define SEC_DECLARATION_10(ta,a,tb,b,tc,c,td,d,te,e,tf,f,tg,g,th,h,ti,i,tj,j) \
	(ta a,tb b,tc c,td d,te e,tf f,tg g,th h,ti i,tj j)
#define SEC_DECLARATION_11(ta,a,tb,b,tc,c,td,d,te,e,tf,f,tg,g,th,h,ti,i,tj,j,tk,k) \
	(ta a,tb b,tc c,td d,te e,tf f,tg g,th h,ti i,tj j,tk k)
#define SEC_DECLARATION_12(ta,a,tb,b,tc,c,td,d,te,e,tf,f,tg,g,th,h,ti,i,tj,j,tk,k,tl,l) \
	(ta a,tb b,tc c,td d,te e,tf f,tg g,th h,ti i,tj j,tk k,tl l)
#define SEC_DECLARATION_13(ta,a,tb,b,tc,c,td,d,te,e,tf,f,tg,g,th,h,ti,i,tj,j,tk,k,tl,l,tm,m) \
	(ta a,tb b,tc c,td d,te e,tf f,tg g,th h,ti i,tj j,tk k,tl l,tm m)
#define SEC_DECLARATION_14(ta,a,tb,b,tc,c,td,d,te,e,tf,f,tg,g,th,h,ti,i,tj,j,tk,k,tl,l,tm,m,tn,n) \
	(ta a,tb b,tc c,td d,te e,tf f,tg g,th h,ti i,tj j,tk k,tl l,tm m,tn n)
#define SEC_DECLARATION_15(ta,a,tb,b,tc,c,td,d,te,e,tf,f,tg,g,th,h,ti,i,tj,j,tk,k,tl,l,tm,m,tn,n,to,o) \
	(ta a,tb b,tc c,td d,te e,tf f,tg g,th h,ti i,tj j,tk k,tl l,tm m,tn n,to o)
#define SEC_DECLARATION_16(ta,a,tb,b,tc,c,td,d,te,e,tf,f,tg,g,th,h,ti,i,tj,j,tk,k,tl,l,tm,m,tn,n,to,o,tp,p) \
	(ta a,tb b,tc c,td d,te e,tf f,tg g,th h,ti i,tj j,tk k,tl l,tm m,tn n,to o,tp p)
#define SEC_DECLARATION_17(ta,a,tb,b,tc,c,td,d,te,e,tf,f,tg,g,th,h,ti,i,tj,j,tk,k,tl,l,tm,m,tn,n,to,o,tp,p,tq,q) \
	(ta a,tb b,tc c,td d,te e,tf f,tg g,th h,ti i,tj j,tk k,tl l,tm m,tn n,to o,tp p, tq q)
#define SEC_DECLARATION_18(ta,a,tb,b,tc,c,td,d,te,e,tf,f,tg,g,th,h,ti,i,tj,j,tk,k,tl,l,tm,m,tn,n,to,o,tp,p,tq,q, tr, r) \
	(ta a,tb b,tc c,td d,te e,tf f,tg g,th h,ti i,tj j,tk k,tl l,tm m,tn n,to o,tp p, tq q, tr r)
#define SEC_DECLARATION_20(ta,a,tb,b,tc,c,td,d,te,e,tf,f,tg,g,th,h,ti,i,tj,j,tk,k,tl,l,tm,m,tn,n,to,o,tp,p,tq,q,\
    tr, r, ts, s, tt, t) \
	(ta a,tb b,tc c,td d,te e,tf f,tg g,th h,ti i,tj j,tk k,tl l,tm m,tn n,to o,tp p, tq q, tr r, ts s, tt t)
	
	
#else


#define SEC_PROTOTYPE_0() ()
#define SEC_PROTOTYPE_1(ta,a) ()
#define SEC_PROTOTYPE_2(ta,a,tb,b) ()
#define SEC_PROTOTYPE_3(ta,a,tb,b,tc,c) ()
#define SEC_PROTOTYPE_4(ta,a,tb,b,tc,c,td,d) ()
#define SEC_PROTOTYPE_5(ta,a,tb,b,tc,c,td,d,te,e) ()
#define SEC_PROTOTYPE_6(ta,a,tb,b,tc,c,td,d,te,e,tf,f) ()
#define SEC_PROTOTYPE_7(ta,a,tb,b,tc,c,td,d,te,e,tf,f,tg,g) ()
#define SEC_PROTOTYPE_8(ta,a,tb,b,tc,c,td,d,te,e,tf,f,tg,g,th,h) ()
#define SEC_PROTOTYPE_9(ta,a,tb,b,tc,c,td,d,te,e,tf,f,tg,g,th,h,ti,i) ()
#define SEC_PROTOTYPE_10(ta,a,tb,b,tc,c,td,d,te,e,tf,f,tg,g,th,h,ti,i,tj,j) ()
#define SEC_PROTOTYPE_11(ta,a,tb,b,tc,c,td,d,te,e,tf,f,tg,g,th,h,ti,i,tj,j,tk,k) ()
#define SEC_PROTOTYPE_12(ta,a,tb,b,tc,c,td,d,te,e,tf,f,tg,g,th,h,ti,i,tj,j,tk,k,tl,l) ()
#define SEC_PROTOTYPE_13(ta,a,tb,b,tc,c,td,d,te,e,tf,f,tg,g,th,h,ti,i,tj,j,tk,k,tl,l,tm,m) ()
#define SEC_PROTOTYPE_14(ta,a,tb,b,tc,c,td,d,te,e,tf,f,tg,g,th,h,ti,i,tj,j,tk,k,tl,l,tm,m,tn,n) ()
#define SEC_PROTOTYPE_15(ta,a,tb,b,tc,c,td,d,te,e,tf,f,tg,g,th,h,ti,i,tj,j,tk,k,tl,l,tm,m,tn,n,to,o) ()
#define SEC_PROTOTYPE_16(ta,a,tb,b,tc,c,td,d,te,e,tf,f,tg,g,th,h,ti,i,tj,j,tk,k,tl,l,tm,m,tn,n,to,o,tp,p) ()
#define SEC_PROTOTYPE_17(ta,a,tb,b,tc,c,td,d,te,e,tf,f,tg,g,th,h,ti,i,tj,j,tk,k,tl,l,tm,m,tn,n,to,o,tp,p,tq,q) ()
#define SEC_PROTOTYPE_18(ta,a,tb,b,tc,c,td,d,te,e,tf,f,tg,g,th,h,ti,i,tj,j,tk,k,tl,l,tm,m,tn,n,to,o,tp,p,tq,q,tr,r) ()
#define SEC_DECLARATION_0() \
	()
#define SEC_DECLARATION_1(ta,a) \
	(a) \
	ta a;
#define SEC_DECLARATION_2(ta,a,tb,b) \
	(a,b) \
	ta a; \
	tb b;
#define SEC_DECLARATION_3(ta,a,tb,b,tc,c) \
	(a,b,c) \
	ta a; \
	tb b; \
	tc c;
#define SEC_DECLARATION_4(ta,a,tb,b,tc,c,td,d) \
	(a,b,c,d) \
	ta a; \
	tb b; \
	tc c; \
	td d;
#define SEC_DECLARATION_5(ta,a,tb,b,tc,c,td,d,te,e) \
	(a,b,c,d,e) \
	ta a; \
	tb b; \
	tc c; \
	td d; \
	te e;
#define SEC_DECLARATION_6(ta,a,tb,b,tc,c,td,d,te,e,tf,f) \
	(a,b,c,d,e,f) \
	ta a; \
	tb b; \
	tc c; \
	td d; \
	te e; \
	tf f;
#define SEC_DECLARATION_7(ta,a,tb,b,tc,c,td,d,te,e,tf,f,tg,g) \
	(a,b,c,d,e,f,g) \
	ta a; \
	tb b; \
	tc c; \
	td d; \
	te e; \
	tf f; \
	tg g;
#define SEC_DECLARATION_8(ta,a,tb,b,tc,c,td,d,te,e,tf,f,tg,g,th,h) \
	(a,b,c,d,e,f,g,h) \
	ta a; \
	tb b; \
	tc c; \
	td d; \
	te e; \
	tf f; \
	tg g; \
	th h;
#define SEC_DECLARATION_9(ta,a,tb,b,tc,c,td,d,te,e,tf,f,tg,g,th,h,ti,i) \
	(a,b,c,d,e,f,g,h,i) \
	ta a; \
	tb b; \
	tc c; \
	td d; \
	te e; \
	tf f; \
	tg g; \
	th h; \
	ti i;
#define SEC_DECLARATION_10(ta,a,tb,b,tc,c,td,d,te,e,tf,f,tg,g,th,h,ti,i,tj,j) \
	(a,b,c,d,e,f,g,h,i,j) \
	ta a; \
	tb b; \
	tc c; \
	td d; \
	te e; \
	tf f; \
	tg g; \
	th h; \
	ti i; \
	tj j;
#define SEC_DECLARATION_11(ta,a,tb,b,tc,c,td,d,te,e,tf,f,tg,g,th,h,ti,i,tj,j,tk,k) \
	(a,b,c,d,e,f,g,h,i,j,k) \
	ta a; \
	tb b; \
	tc c; \
	td d; \
	te e; \
	tf f; \
	tg g; \
	th h; \
	ti i; \
	tj j; \
	tk k;
#define SEC_DECLARATION_12(ta,a,tb,b,tc,c,td,d,te,e,tf,f,tg,g,th,h,ti,i,tj,j,tk,k,tl,l) \
	(a,b,c,d,e,f,g,h,i,j,k,l) \
	ta a; \
	tb b; \
	tc c; \
	td d; \
	te e; \
	tf f; \
	tg g; \
	th h; \
	ti i; \
	tj j; \
	tk k; \
	tl l;
#define SEC_DECLARATION_13(ta,a,tb,b,tc,c,td,d,te,e,tf,f,tg,g,th,h,ti,i,tj,j,tk,k,tl,l,tm,m) \
	(a,b,c,d,e,f,g,h,i,j,k,l,m) \
	ta a; \
	tb b; \
	tc c; \
	td d; \
	te e; \
	tf f; \
	tg g; \
	th h; \
	ti i; \
	tj j; \
	tk k; \
	tl l; \
	tm m;
#define SEC_DECLARATION_14(ta,a,tb,b,tc,c,td,d,te,e,tf,f,tg,g,th,h,ti,i,tj,j,tk,k,tl,l,tm,m,tn,n) \
	(a,b,c,d,e,f,g,h,i,j,k,l,m,n) \
	ta a; \
	tb b; \
	tc c; \
	td d; \
	te e; \
	tf f; \
	tg g; \
	th h; \
	ti i; \
	tj j; \
	tk k; \
	tl l; \
	tm m; \
	tn n;
#define SEC_DECLARATION_15(ta,a,tb,b,tc,c,td,d,te,e,tf,f,tg,g,th,h,ti,i,tj,j,tk,k,tl,l,tm,m,tn,n,to,o) \
	(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o) \
	ta a; \
	tb b; \
	tc c; \
	td d; \
	te e; \
	tf f; \
	tg g; \
	th h; \
	ti i; \
	tj j; \
	tk k; \
	tl l; \
	tm m; \
	tn n; \
	to o;
#define SEC_DECLARATION_16(ta,a,tb,b,tc,c,td,d,te,e,tf,f,tg,g,th,h,ti,i,tj,j,tk,k,tl,l,tm,m,tn,n,to,o,tp,p) \
	(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p) \
	ta a; \
	tb b; \
	tc c; \
	td d; \
	te e; \
	tf f; \
	tg g; \
	th h; \
	ti i; \
	tj j; \
	tk k; \
	tl l; \
	tm m; \
	tn n; \
	to o; \
	tp p;
#define SEC_DECLARATION_17(ta,a,tb,b,tc,c,td,d,te,e,tf,f,tg,g,th,h,ti,i,tj,j,tk,k,tl,l,tm,m,tn,n,to,o,tp,p,tq,q) \
	(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q) \
	ta a; \
	tb b; \
	tc c; \
	td d; \
	te e; \
	tf f; \
	tg g; \
	th h; \
	ti i; \
	tj j; \
	tk k; \
	tl l; \
	tm m; \
	tn n; \
	to o; \
	tp p; \
	tq q;
#define SEC_DECLARATION_18(ta,a,tb,b,tc,c,td,d,te,e,tf,f,tg,g,th,h,ti,i,tj,j,tk,k,tl,l,tm,m,tn,n,to,o,tp,p,tq,q,tr,r) \
	(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r) \
	ta a; \
	tb b; \
	tc c; \
	td d; \
	te e; \
	tf f; \
	tg g; \
	th h; \
	ti i; \
	tj j; \
	tk k; \
	tl l; \
	tm m; \
	tn n; \
	to o; \
	tp p; \
	tq q; \
	tr r;

	
#endif /* __STDC__ */

#ifdef MACRO_SEP_LIKE_STDC




#define E_PROTOTYPE(mod, type) \
OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV e_##type SEC_PROTOTYPE_1(type *, c);
#define E_(mod, type) \
OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV e_##type SEC_DECLARATION_1(type *, c) { \
} 
#define D_PROTOTYPE(mod, type) \
type SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV d_##type SEC_PROTOTYPE_1(OctetString *, asn1_string);
#define D_(mod, type) \
type SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV d_##type SEC_DECLARATION_1(OctetString *, asn1_string) \
{ \
} 


#define AUX_PRINT(type) \
RC  SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_fprint_##type SEC_DECLARATION_2(FILE *, ff, type *, token) \
{\
	char *string = aux_sprint_##type(CNULL, token);\
	if(string) {\
		fprintf(ff, "%s", string);\
		free(string);\
		return(0);\
	}\
	else return(-1);\
}\
RC  SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_print_##type SEC_DECLARATION_1(type *, token)\
{\
	return(aux_fprint_##type(stderr, token));\
}

#define AUX_PRINT_PROTOTYPE(type) \
RC  SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_fprint_##type SEC_PROTOTYPE_2(FILE *, ff, type *, token);\
RC  SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_print_##type SEC_PROTOTYPE_1(type *, token);\
char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_sprint_##type SEC_PROTOTYPE_2(char *, string, type *, token);

#define AUX_FREE_PROTOTYPE(type) \
void  SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_##type SEC_PROTOTYPE_1(type **, ptr);\


#else





#define E_PROTOTYPE(mod, type) \
OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV e_/**/type SEC_PROTOTYPE_1(type *, c);
#define E_(mod, type) \
OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV e_/**/type SEC_DECLARATION_1(type *, c) { \
} 
#define D_PROTOTYPE(mod, type) \
type SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV d_/**/type SEC_PROTOTYPE_1(OctetString *, asn1_string);
#define D_(mod, type) \
type SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV d_/**/type SEC_DECLARATION_1(OctetString *, asn1_string) \
{ \
} 

#define AUX_PRINT(type) \
RC  SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_fprint_/**/type SEC_DECLARATION_2(FILE *, ff, type *, token) \
{\
	char *string = aux_sprint_/**/type(CNULL, token);\
	if(string) {\
		fprintf(ff, "%s", string);\
		free(string);\
		return(0);\
	}\
	else return(-1);\
}\
RC  SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_print_/**/type SEC_DECLARATION_1(type *, token)\
{\
	return(aux_fprint_/**/type(stderr, token));\
}
#define AUX_PRINT_PROTOTYPE(type) \
RC  SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_fprint_/**/type SEC_PROTOTYPE_2(FILE *, ff, type *, token);\
RC  SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_print_/**/type SEC_PROTOTYPE_1(type *, token);\
char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_sprint_/**/type SEC_PROTOTYPE_2(char *, string, type *, token);

#define AUX_FREE_PROTOTYPE(type) \
void  SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_/**/type SEC_PROTOTYPE_1(type **, ptr);\

#endif


#endif /* FUNCTION_MACROS_H_ */

