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

#include "FactorHint.h"
#include "resource.h"

// static status variables
int FactorHint::status = 0;
long FactorHint::reductions = 0;

void FactorHint::MSBFact(){
	status=1;// building Lattice
	reductions=0;
	p=to_ZZ(0);
	q=to_ZZ(0);
	startTime=GetTime();
	buildLatticeTime=0;
	reduceLatticeTime=0;

	CString logStringMostSignificantBitsAttackStarted;
	logStringMostSignificantBitsAttackStarted.LoadString(IDS_RSA_LOG_MOST_SIGNIFICANT_BITS_ATTACK_STARTED);
	log = timeStamp() + logStringMostSignificantBitsAttackStarted + "\r\n";

	buildMSBPolyPowers();

	CString form;
	log+="N: "+toString(N,10,0)+"\r\n";
	log+="P: "+toString(P,10,0)+"\r\n";
	
	CString logStringLatticeDimension;
	logStringLatticeDimension.LoadString(IDS_RSA_LOG_LATTICE_DIMENSION);
	form.Format(CString(logStringLatticeDimension + " %d" + "\r\n"), d);
	log += form;

	CString logStringBuildingLattice;
	logStringBuildingLattice.LoadString(IDS_RSA_LOG_BUILDING_LATTICE);
	log += timeStamp() + logStringBuildingLattice + "\r\n";

	if(status!=0)
		buildLattice();

	CString logStringReducingLattice;
	logStringReducingLattice.LoadString(IDS_RSA_LOG_REDUCING_LATTICE);
	log += timeStamp() + logStringReducingLattice + "\r\n";

	if(status!=0){
		status=3;// reducing Lattice
		reduceLattice();
	
	}
	if(status!=0){
		status=5;// calculation resultants
		getMSBSolution();
	}

	if(status!=0){
		if(N==p*q){
			CString logStringFoundSolution;
			logStringFoundSolution.LoadString(IDS_RSA_LOG_FOUND_SOLUTION);
			log += timeStamp() + logStringFoundSolution + "\r\n";
			log+="p: "+toString(p,10,0)+"\r\n";
			log+="q: "+toString(q,10,0)+"\r\n";
			status=6; // successful
		}
		else{
			CString logStringFoundNoSolution;
			logStringFoundNoSolution.LoadString(IDS_RSA_LOG_FOUND_NO_SOLUTION);
			log += timeStamp() + logStringFoundNoSolution + "\r\n";
			status=7; // failed
		}
	}else {
		CString logStringCancelledByUser;
		logStringCancelledByUser.LoadString(IDS_RSA_LOG_CANCELLED_BY_USER);
		log += timeStamp() + logStringCancelledByUser + "\r\n";
	}
}

void FactorHint::LSBFact(){
	status=1;// building Lattice
	reductions=0;
	p=to_ZZ(0);
	q=to_ZZ(0);
	startTime=GetTime();
	buildLatticeTime=0;
	reduceLatticeTime=0;

	CString logStringLeastSignificantBitsAttackStarted;
	logStringLeastSignificantBitsAttackStarted.LoadString(IDS_RSA_LOG_LEAST_SIGNIFICANT_BITS_ATTACK_STARTED);
	log = timeStamp() + logStringLeastSignificantBitsAttackStarted + "\r\n";

	buildLSBPolyPowers();

	CString form;
	log+="N: "+toString(N,10,0)+"\r\n";
	log+="P: "+toString(P,10,0)+"\r\n";

	CString dimForm;
	dimForm.Format("%d", d);
	CString logStringLatticeDimension;
	logStringLatticeDimension.LoadString(IDS_RSA_LOG_LATTICE_DIMENSION);	
	log += timeStamp() + logStringLatticeDimension + " = " + dimForm + "\r\n";

	CString logStringBuildingLattice;
	logStringBuildingLattice.LoadString(IDS_RSA_LOG_BUILDING_LATTICE);
	log += timeStamp() + logStringBuildingLattice + "\r\n";

	if(status!=0)
		buildLattice();

	CString logStringReducingLattice;
	logStringReducingLattice.LoadString(IDS_RSA_LOG_REDUCING_LATTICE);
	log += timeStamp() + logStringReducingLattice + "\r\n";

	if(status!=0){
		status=3;// reducing Lattice
		reduceLattice();
	
	}
	if(status!=0){
		status=5;// calculation resultants
		getLSBSolution();
	}
	if(status!=0){
		if(N==p*q){
			CString logStringFoundSolution;
			logStringFoundSolution.LoadString(IDS_RSA_LOG_FOUND_SOLUTION);
			log += timeStamp() + logStringFoundSolution + "\r\n";
			log+="p: "+toString(p,10,0)+"\r\n";
			log+="q: "+toString(q,10,0)+"\r\n";
			status=6; // successful
		}
		else{
			CString logStringFoundNoSolution;
			logStringFoundNoSolution.LoadString(IDS_RSA_LOG_FOUND_NO_SOLUTION);
			log += timeStamp() + logStringFoundNoSolution + "\r\n";
			status=7; // failed
		}
	}else {
		CString logStringCancelledByUser;
		logStringCancelledByUser.LoadString(IDS_RSA_LOG_CANCELLED_BY_USER);
		log += timeStamp() + logStringCancelledByUser + "\r\n";
	}
}

ZZ FactorHint::binom(int i, int j)
{
	ZZ b;
	int k;
	b=1;
	for (k=2; k<=i; k++)   b=b*k;
	for (k=2; k<=j; k++)   b=b/k;
	for (k=2; k<=i-j; k++) b=b/k;
	return b;
}

void FactorHint::buildMSBPolyPowers()
{
	buildLatticeTime=GetTime();
	n=NumBits(N);
	if(b<n/4)
		status=0;
	else{
		CString form;
		double frac=(b-((double)n)/4);
		d=(int)(n/frac);

		m=(d-1)/2;
		X=to_ZZ(1);
		X<<=(bitsOfP-b);
		ZZ tmpKoeff;
		ZZ sign;
		ZZ bino;
		delete [] polyPowers;
		polyPowers = new ZZX[m+1];
		int i,k;
		for (k=0; k<=m; k++){
			for (i=0; i<=k && status!=0; i++) {
				bino=binom(k,i);
				tmpKoeff=power(P,k-i)*power(X,i);
				SetCoeff(polyPowers[k],i,bino*tmpKoeff);
				}
		}
	}
}


void FactorHint::buildLSBPolyPowers()
{
	buildLatticeTime=GetTime();
	n=NumBits(N);
	if(b<n/4)
		status=0;
	else{
		double frac=(b-((double)n+3)/4);
		d=(int)(n/frac);
		m=(d-1)/2;
		X=to_ZZ(1);
		X<<=(bitsOfP-b);
		ZZ tmpKoeff;
		ZZ sign;
		ZZ bino;
		ZZ aP;
		ZZ a;
		ZZ R=to_ZZ(1);
		R<<=b;
		InvModStatus(a,R,N);
		//a = InvMod(R, N);
		aP = a*P;
		
		delete [] polyPowers;
		polyPowers = new ZZX[m+1];
		int i,k;
		for (k=0; k<=m; k++){
			for (i=0; i<=k && status!=0; i++) {
				bino=binom(k,i);
				tmpKoeff=power(aP,k-i)*power(X,i);
				SetCoeff(polyPowers[k],i,bino*tmpKoeff);
			}
		}
	}
}


void FactorHint::buildLattice(){
	int k,i;

	Lattice.kill();
	Lattice.SetDims(d,d);
	ZZX g;
	for(k=0;k<m;k++){
		g=polyPowers[k];
		g=g*power(N,m-k);
		for(i=0;i<=k && status!=0;i++)
			Lattice[k][i]=coeff(g,i);
		}
	for(k=0;k<d-m;k++){
		g=polyPowers[m];
		for(i=0;i<=k+m && status!=0;i++)
			Lattice[k+m][i]=coeff(g,i-k)*power(X,k);
	}
}


void FactorHint::reduceLattice(){
	// Here the LLL algorithm is called.
	// It gets the StopLLL function as parameter.
	//verbose+= "Reducing lattice (LLL)\r\n";
	reduceLatticeTime=GetTime();
	ZZ tu;
	long x = LLL_XD(Lattice, 0.99,0,StopLLL,0);
}
void FactorHint::getMSBSolution(){
	ZZX result;
	dim=Lattice.NumCols();
	vec_ZZ roots;
	
	ZZX h1;

	ZZ norm;
	for(int j=0; j< dim; j++)
		if(!IsZero(Lattice[0][j]))
			SetCoeff(h1,j,Lattice[0][j]/power(X,j));

	if(FindRoots(h1, roots))
		for(int x=0; x < roots.length()&&p*q!=N; x++){
			ZZ s=roots[x];
			p=P;
			p-=s;
			if(!IsZero(p))
				q=N/p;
			else
				q=to_ZZ(-1);
		}
}
void FactorHint::getLSBSolution(){
	ZZX result;
	dim=Lattice.NumCols();
	vec_ZZ roots;
	
	ZZX h1;

	ZZ norm;
	for(int j=0; j< dim; j++)
		if(!IsZero(Lattice[0][j]))
			SetCoeff(h1,j,Lattice[0][j]/power(X,j));

	ZZ R=to_ZZ(1);
	R<<=b;
	if(FindRoots(h1, roots))
		for(int x=0; x < roots.length()&&p*q!=N; x++){
			ZZ s=roots[x];
			p=-s*R+P;
			if(!IsZero(p))
				q=N/p;
			else
				q=to_ZZ(-1);
		}
}

bool FactorHint::FindRoots(ZZX f, vec_ZZ& r){
	vec_pair_ZZX_long factors;
	ZZ c;
	factor(c,factors,f);// factor polynomial
	r.SetLength(0);
	// look for  factors os the form (x - a)
	for(int i=0; i < factors.length(); i++)
		if(deg(factors[i].a)==1
			&&LeadCoeff(factors[i].a)==1)
			append(r, ConstTerm(factors[i].a));
	return (r.length()>0);
}

// Method to stop the attack.
void FactorHint::cancel(){
	status=0;
}
// A pointer to this function is given to the LLL.
// It is called after each reduction step and stops
// it if anything but 0 is returned
long FactorHint::StopLLL(const NTL::vec_ZZ& z){
	reductions++;
	if(status!=0) return 0;
	else return 1;

}



FactorHint::FactorHint()
{
	polyPowers = NULL;
}

FactorHint::~FactorHint()
{
	delete [] polyPowers;
}

void FactorHint::setN(ZZ N){
	this->N=N;
}
void FactorHint::setP(ZZ P){
	this->P=P;
}
void FactorHint::setB(int b){
	this->b=b;
}

ZZ FactorHint::getN(){
	return N;
}
ZZ FactorHint::getP(){
	return p;
}
ZZ FactorHint::getQ(){
	return q;
}
int FactorHint::getLatticeTime(){
	return (int)(GetTime()-buildLatticeTime)-getReductionTime();
}
int FactorHint::getReductionTime(){
	if(reduceLatticeTime<0.1)
		return 0;
	else
		return (int)(GetTime()-reduceLatticeTime);
}
int FactorHint::getOverallTime(){
	return (int)(GetTime()-startTime);
}

void FactorHint::setBitsOfP(int bop)
{
	bitsOfP=bop;
}

CString FactorHint::timeStamp()
{
	int t=(int)(GetTime()-startTime);
	CString timeFormat;
	timeFormat.Format("***%3dh%3dm%3ds*** ",
		t/3600,
		(t/60)%60,
		(t)%60);
	return timeFormat;
}
