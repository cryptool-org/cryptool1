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

#include "ZZXY.h"

NTL_CLIENT


ZZXY& ZZXY::operator=(const ZZXY& f1){
	kill();
	data=f1.data;
	yDegree=f1.yDegree;
	return(*this);
}

const ZZXY ZZXY::operator +(ZZXY &B)
{
	ZZXY retval;
	int m=getYDegree();
	int n=B.getYDegree();
	if(m==-1){
		retval=B;
		return retval;
	}
	if(n==-1){
		retval=(*this);
		return retval;
	}
	if(m>=n){
		int i;
		retval.data.SetLength(m+1);
		for(i=m; i>n; i--)
			retval.data[i]=data[i];
		for(i=n; i>=0; i--)
			retval.data[i]=data[i]+B.data[i];
	}else{
		int i;
		retval.data.SetLength(n+1);
		for(i=n; i>m; i--)
			retval.data[i]=B.data[i];
		for(i=m; i>=0; i--)
			retval.data[i]=data[i]+B.data[i];
	}
	return retval;
}


const ZZXY ZZXY::operator -(ZZXY &B)
{
	ZZXY retval;
	int m=getYDegree();
	int n=B.getYDegree();
	if(n==-1){
		retval=(*this);
		return retval;
	}
	if(m>=n){
		retval.data.SetLength(m+1);
		int i;
		for(i=m; i>n; i--)
			retval.data[i]=data[i];
		for(i=n; i>=0; i--)
			retval.data[i]=data[i]-B.data[i];
	}else{
		retval.data.SetLength(n+1);
		int i;
		for(i=n; i>m; i--)
			retval.data[i]=(-1)*B.data[i];
		for(i=m; i>=0; i--)
			retval.data[i]=data[i]-B.data[i];
	}
	return retval;

}

const ZZXY ZZXY::operator *(ZZXY &B)
{
	ZZXY retval;
	int m=getYDegree();
	int n=B.getYDegree();
	if(m==-1||n==-1)
		return retval;
	for(int i=0; i<= m; i++)
		for(int j=0; j<= n; j++){
			ZZXY tmp;
			tmp.data.SetLength(i+j+1);
			tmp.data[i+j] = data[i]*B.data[j];
			retval = retval + tmp;
		}
	return retval;
}

ZZXY ZZXY::operator *(ZZX &B)
{
	ZZXY retval;
	retval.data.SetLength(1);
	retval.data[0] = B;
	retval = (*this) * retval;
	return retval;
}

ZZXY ZZXY::operator *(ZZ &B)
{
	ZZXY retval;
	retval.data.SetLength(1);
	retval.data[0] = B;
	retval = (*this) * retval;
	return retval;
}

		

ZZ ZZXY::norm(){
	ZZ retval=to_ZZ(0);
	for(int i = getYDegree();i>=0; i--)
		for(int j=deg(data[i]); j>=0; j--)
			retval+=coeff(data[i],j)*coeff(data[i],j);
	return SqrRoot(retval);
}


ZZ ZZXY::eval(ZZ x, ZZ y){
	ZZ retval;
	for(int i = getYDegree();i>=0; i--)
		for(int j=deg(data[i]); j>=0; j--)
			retval+=coeff(data[i],j)*power(x,j)*power(y,i);
	return retval;
}
ZZX ZZXY::resultant(ZZXY b,int* status){
	return subresultant(b, status);


}

ZZX ZZXY::setX(ZZ x){
	ZZX retval;
	for(int i = getYDegree();i>=0; i--)
		SetCoeff(retval, i, evalF(data[i],x));
	return retval;
}

ZZX ZZXY::setY(ZZ y){
	ZZX retval;
	for(int i = getYDegree();i>=0; i--)
		retval+=power(y, i)*data[i];
	return retval;
}



void ZZXY::pseudoDiv(ZZXY &B, ZZXY &Q, ZZXY &R,int* status)
{
	CString Ss,Qs,Rs, Bs;
	ZZXY &A=(*this);
	ZZXY S;
	int m=A.getYDegree();
	int n=B.getYDegree();
	ZZX d = B.data[n]; 
	Q.kill();

	if(m>=n){
		R = A;
		int e=m-n+1;
		while(R.getYDegree()>=B.getYDegree()&&(*status)!=0){
			S.kill();
			S.data.SetLength(R.getYDegree()-B.getYDegree()+2);
			S.data[R.getYDegree()-B.getYDegree()]=R.data[R.getYDegree()];
			Q = Q * d + S;
			R = R * d;
			S = S * B;
			R = R - S;
			e = e - 1;
		}
		ZZX q;
		SetCoeff(q,0,to_ZZ(1));
		for(int i=0; i<e; i++)
			q=q*d;

		Q = Q * q;
		R = R * q;
	}
			
}

void ZZXY::changeXY(){
	ZZXY tmp;
	for(int i =0;i <= getYDegree();i++)
		for(int j=0; j<=deg(data[i]); j++)
			tmp.setCoeff(i,j,getCoeff(j,i));
	(*this)=tmp;
}

void ZZXY::setCoeff(int x, int y, ZZ a){
	if(y>=data.length())
		data.SetLength(y+1);
	SetCoeff(data[y], x, a);
}
ZZ ZZXY::getCoeff(int x, int y){
	ZZ retval;
	if(y<data.length()&&y>=0)
		retval = coeff(data[y], x);
	return retval;
}
int ZZXY::getYDegree(){
	int m = data.length()-1;
	while(m>0&&IsZero(data[m])) m--;
	return m;
}

void ZZXY::kill(){
	data.kill();
	yDegree=0;
}

CString ZZXY::print(){
	CString retval;
	CString exponent;
	for(int i = getYDegree();i>=0; i--)
		for(int j=deg(data[i]); j>=0; j--){
		ZZ tmp = coeff(data[i],j);
		if(tmp!=0){
			CString sign="+";
			if(tmp<0){
				sign="-";
				tmp=0-tmp;
			}
			retval+=sign;
			//if(tmp!=1||j==0)
				retval+=toString(tmp,10,0);
			if(j>0)
				retval+="*x";
			if(j>1){
				exponent.Format("%d",j);
				retval+="^" + exponent;
			}
			if(i>0)
				retval+="*y";
			if(i>1){
				exponent.Format("%d",i);
				retval+="^" + exponent;
			}
			retval+=" ";
		}
	}
	return retval;
}


NTL_vector_impl(vec_ZZX, vec_vec_ZZX)

NTL_matrix_impl(ZZX, vec_ZZX, vec_vec_ZZX, mat_ZZX)

NTL_vector_impl(vec_ZZ_pX, vec_vec_ZZ_pX)

NTL_matrix_impl(ZZ_pX, vec_ZZ_pX, vec_vec_ZZ_pX, mat_ZZ_pX)

ZZX ZZXY::subresultant(ZZXY B, int* status)
{
	ZZX retval;
	ZZXY A = (*this);
	int m=A.getYDegree();
	int n=B.getYDegree();
	if(m==-1||n==-1)
		return retval;
	ZZ a = A.content();
	ZZ b = B.content();
	A=A/a;
	B=B/b;
	ZZ t = power(a,n)*power(b,m);
	int s=1;
	ZZX g;
	SetCoeff(g,0,to_ZZ(1));
	ZZX h;
	SetCoeff(h,0,to_ZZ(1));
	ZZXY Q,R;
	CString As,Bs,Qs,Rs;
	if(m<n){
		ZZXY swap;
		swap=A;
		A=B;
		B=swap;
		if(m%2==1&&n%2==1)
			s=-1;
	}
	do{
		int delta=A.getYDegree()-B.getYDegree();
		if(A.getYDegree()%2==1&&B.getYDegree()%2==1)
			s=-s;
		A.pseudoDiv(B,Q,R, status);
		if(*status!=0){
		A=B;
		ZZX d=power(h, delta);
		B=R/d;
		B=B/g;
		g=A.data[A.getYDegree()];
		ZZX tmpG=power(g, delta);
		if(*status!=0)
			h=h*tmpG;
		if(*status!=0)
			h=h/d;
		}
		
	}while(B.getYDegree()>0&& *status!=0);
	if(A.getYDegree()==0)
		return s*t*h*B.data[B.getYDegree()];
	else
		return s*t*B.data[B.getYDegree()];
}

ZZ ZZXY::content()
{
	ZZ retval;
	retval= to_ZZ(1);
	for(int i = getYDegree();i>=0; i--)
		for(int j=deg(data[i]); j>=0; j--)
			retval=GCD(retval,coeff(data[i],j));
	return retval;
}

const ZZXY ZZXY::operator /(ZZ d)
{
	ZZXY retval;
	retval.data.SetLength(getYDegree()+1);
	for(int i = getYDegree();i>=0; i--)
		retval.data[i]=data[i]/d;
	return retval;
}

const ZZXY ZZXY::operator /(ZZX b)
{
	ZZXY retval;
	retval.data.SetLength(getYDegree()+1);
	for(int i = getYDegree();i>=0; i--)
		retval.data[i]=data[i]/b;
	return retval;
}

ZZ ZZXY::norm(ZZ X, ZZ Y)
{
	ZZ retval=to_ZZ(0);
	ZZ tmp;
	for(int i = getYDegree();i>=0; i--)
		for(int j=deg(data[i]); j>=0; j--){
			tmp=power(Y,i)*power(X,j)*coeff(data[i],j);
			tmp=tmp*tmp;
			retval+=tmp;
		}
	return SqrRoot(retval);
}

int ZZXY::monomCount()
{
	int c=0;
	for(int i = getYDegree();i>=0; i--)
		for(int j=deg(data[i]); j>=0; j--)
			if(!IsZero(coeff(data[i],j)))
				c++;
	return c;
}

