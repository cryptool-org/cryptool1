#include <NTL/ZZX.h>
#include <afx.h>

using namespace NTL;

CString toString(ZZ zTmp, int base, int groupBy);
CString toString(ZZ zTmp, int base, int groupBy, int groupOffset, int minLength);
ZZ setToStringValue(CString value, int base);
ZZ evalF(ZZX f, ZZ x);
CString readable(ZZX t1);
ZZX differentiate(ZZX f);
ZZX power(ZZX a, int e);
 