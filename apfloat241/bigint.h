#if !defined(__BIGINT_H)
#define __BIGINT_H


// Functions in bigint.cpp

#if defined (USEASM)
extern "C"
{
#endif

rawtype bigadd (rawtype *d, rawtype *s, size_t n, size_t c = 0);
rawtype bigsub (rawtype *d, rawtype *s, size_t n, size_t c = 0);
rawtype bigmul (rawtype *d, rawtype *s, rawtype f, size_t n);
rawtype bigdiv (rawtype *d, rawtype *s, rawtype f, size_t n);
int bigshr (rawtype *d, rawtype *s, size_t n);
int bigcmp (rawtype *d, rawtype *s, size_t n);

#if defined (USEASM)
}
#endif

#endif  // __BIGINT_H
