/**************************************************************************

  Copyright [2009] [CrypTool Team]

  This file is part of CrypTool.

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

**************************************************************************/

#include "ZZ_helpers.h"


int HEXdec(char v){
	if(v>=48 && v<=57) // 0-9
		return v-48;
	if(v>=65 && v<=70) // A-F
		return v-55;
	if(v>=97 && v<=102)// a-f
		return v-87;
	return 16; //error
}

char HEXenc(int v){
	char* tab = "0123456789ABCDEF";
	if (v>=0 && v<16)
		return tab[v];
	else
		return 0;
}

ZZ setToStringValue(CString value, int base){
	int vlength=value.GetLength();
	int tmp;
	int sign=1;
	ZZ thisref;
	if(value.Left(1)=="-")
		sign=-1;
	if(vlength==0)
		thisref = 0;
	else
		if(base > 1 && base <17){
			for(int i=0; i<vlength; i++)
				if((tmp=HEXdec(value.GetAt(i)))<base){
					thisref*=base;
					thisref+=tmp;
				}
		}else
			if(base==256)
				for(int i=0; i<vlength; i++)
					if((tmp=value.GetAt(i))<256){
						if(tmp<0)
							tmp+=256;
						thisref*=256;
						thisref+=tmp;
					}
	return sign*thisref;
}

// Returns readable representation of the value.
// "base" must be in [2..16] or 256.
// If groupBy>0 then space-seperated Blocks 
// of length groupBy are returned.
// e.g.: base=16 groupBy=2 returns "12 34 EF"

CString toString(ZZ value, int base, int groupBy){
	CString retval="";
	CString sign="";
	if(value<0){
		sign="-";
		value*=-1;
	}
	ZZ zTmp(value);
	char tmp=' ';
	if (base>1 && base < 17){
		int groupcount=0;
		while(zTmp>0){
			if(groupBy>0 && groupcount==groupBy){
				groupcount=0;
				retval =" "+retval;
			}
			tmp = HEXenc(to_int(zTmp % to_ZZ(base)));
			if(tmp!=0)
				retval = tmp + retval;
			zTmp /= base;
			groupcount ++;
		}
		if(value==0)
			return "0";
	}else 
		if (base== 256){
			int groupcount=0;
			while(zTmp>0){
				if(groupBy>0 && groupcount==groupBy){
					groupcount=0;
					retval =" "+retval;
				}
				tmp = to_int(zTmp % 256);
				retval = tmp + retval;
				zTmp /= base;
				groupcount ++;
			}
		}
	return sign+retval;
}

CString toString(ZZ value, int base, int groupBy, int groupOffset, int minLength){
	CString retval="";
	CString sign="";
	if(value<0){
		sign="-";
		value*=-1;
	}
	ZZ zTmp(value);
	char tmp=' ';
	if (base>1 && base < 17){
		int figureCount=groupOffset;
		while(zTmp>0||figureCount<minLength){
			if(groupBy>0&&figureCount!=0&&figureCount%groupBy==0)
				retval =" "+retval;
			tmp = HEXenc(to_int(zTmp % to_ZZ(base)));
			if(tmp!=0)
				retval = tmp + retval;
			zTmp /= base;
			figureCount++;
		}
	if(value==0)
		return "0";
	}else 
		if (base== 256){
			int groupcount=0;
			while(zTmp>0){
				if(groupBy>0 && groupcount==groupBy){
					groupcount=0;
					retval =" "+retval;
				}
				tmp = to_int(zTmp % 256);
				retval = tmp + retval;
				zTmp /= base;
				groupcount ++;
			}
		}
	return sign+retval;
}
// Simple function to calculate f(x)

ZZ evalF(ZZX f, ZZ x){
	NTL::ZZ retval;
	retval = coeff(f,0);
	for(int i=1; i<=deg(f); i++){
		retval+=(coeff(f,i)* power(x, i));
	}
	return retval;
}

ZZX differentiate(ZZX f){
	ZZX retval;
	for(int i=1; i<=deg(f); i++){
		SetCoeff(retval,i-1,coeff(f,i)*i);
	}
	return retval;
}

CString readable(ZZX t1){
	if(IsZero(t1))
		return "0";
	CString retval;
	CString exponent;
	for(int i = deg(t1);i>=0; i--){
		ZZ tmp = coeff(t1,i);
		if(tmp!=0){
			CString sign="+";
			if(tmp<0){
				sign="-";
				tmp=0-tmp;
			}
			retval+=sign;
			retval+=toString(tmp,10,0);
			if(i>0)
				retval+="*x";
			if(i>1){
				exponent.Format("%d",i);
				retval+="^" + exponent;
			}
			retval+=" ";
		}
	}
	return retval;
}

ZZX power(ZZX a, int e){
	ZZX retval;
	if(e>=0)
		SetCoeff(retval,0,to_ZZ(1));
	for(int i=0; i<e; i++)
		retval=retval*a;
	return retval;
}