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

/////////////////////////////////////////////////////////////////
//
// Diese Datei ist Bestandteil der Diplomarbeit
// "Eine C++-Bibliothek zur informationstheoretischen Kryptanalyse 
// von Stromchiffren und PZ-Folgen" am Europaeischen Institut fuer
// Systemsicherheit, Prof. Dr. Th. Beth
//
// von und (c) 1997-98 Michael Friedrich
//
/////////////////////////////////////////////////////////////////

#include "Chi2.h"

#include "mymath.h"
#if !defined(_MSC_VER) || _MSC_VER <= 1200
#include <iostream.h>
#else
#include <iostream>
using namespace std;
#endif

const int Chi2::alphacount=14;
const int Chi2::lines=30;
int Chi2::quantile30 = 0; 

/////////////////////////////////////////////////////////////////////
// Chi2 Constructors


Chi2::Chi2(const NTuple<long>& H)
// R=H.GetSize() Klassen mit absoluter Haeufigkeit H[i], 
// gleichverteilt mit P(x)=1/R
{
	int R=H.GetSize();
	m_r=R;
	double s=0.0;
	long n=0;
	for (int i=0; i<R; i++) {
		n+=H[i];
		double t=H[i];
		s+=t*t;	
	}
	m_V= ((double)(R*s)/n-n);
}
Chi2::Chi2(const NTuple<long>& H, const NTuple<double>& P)
// R=H.GetSize() Klassen mit absoluter Haeufigkeit H[i], 
// verteilt mit P[i]
{
	int R=H.GetSize();
	m_r=R;
	double s=0.0;
	long n=0;

	for (int i=0; i<R; i++) {
		n+=H[i];
		double t=H[i];
		s+=t*t/P[i];
	}
	m_V= s/n-n;
}

Chi2::Chi2(const NTuple<double>& H, long totalcount /*=100000*/)
// R=H.GetSize() Klassen mit absoluter Haeufigkeit H[i]*totalcount, 
// gleichverteilt mit P(x)=1/R
{
	int R=H.GetSize();
	m_r=R;
	double s=0.0;
	for (int i=0; i<R; i++) {
		double t=H[i]*totalcount;
		s+=t*t;	
	}
	m_V=((double)(R*s)/totalcount-totalcount);
}


/////////////////////////////////////////////////////////////////////
// Chi2 Static Functions
void Chi2::PrepareTable(int v)
{
	if (v>=lines) { // calculate entries for v>=30
		if (v!=quantile30) {
			quantile30=v;
			for (int i=0; i<alphacount; i++) {
				double xp=double(quantiletable[lines][i])/100000;
				quantiletable[lines+1][i]=long(pow(1.0-2.0/(9*v)+xp*sqrt(2.0/(9*v)),3.0)*v*10000);	// Bosch, formula 1
				//quantiletable[lines+1][i]=long((v+sqrt(double(v)*2.0)*xp)*10000);				// Bosch, formula 2
				//quantiletable[lines+1][i]=long((v+2*sqrt(double(v))*xp+xp*xp*4/3-2/3)*10000);	// Knuth
			} /* for */
		}
		v=lines+1;
	}
}

double Chi2::GetChi2(double x, int v)
{
	if (v>=lines) { // calculate entries for v>=30
		PrepareTable(v);
		v=lines+1;
	}

	long l=(long)(x*1000);
	int i;
	double r;
	for (i=0;i<alphacount && quantiletable[0][i]<l;i++) ;
	if (i==alphacount) return 1e300;
	if (i==0) r=quantiletable[v][i];
	else {
		ASSERT(quantiletable[0][i-1]<l && quantiletable[0][i]>=l);
		r=quantiletable[v][i-1]+(double(quantiletable[v][i]-quantiletable[v][i-1]))/(quantiletable[0][i]-quantiletable[0][i-1])*(l-quantiletable[0][i-1]);
	}
	r/=10000.0;
	if (v==1) r/=10000.0;
	return r;
}


int Chi2::GetAlpha(double x, int v)
{
	if (v>=lines) { // calculate entries for v>=30
		PrepareTable(v);
		v=lines+1;
	}
	
	long l=(long)(x*10000); if (v==1) l*=10000;
	int i;
	for (i=0;i<alphacount && quantiletable[v][i]<l;i++) ;
	if (i==alphacount) return 1000;
	if (i==0) return quantiletable[0][i];
	ASSERT(quantiletable[v][i-1]<l && quantiletable[v][i]>=l);
	return quantiletable[0][i-1]+int( (double(quantiletable[0][i]-quantiletable[0][i-1]))/(quantiletable[v][i]-quantiletable[v][i-1])*(l-quantiletable[v][i-1]));
}

int Chi2::Check()
{
	for (int i=2;i<30;i++) { // line 1 is special, ommit! 
		for (int j=0;j<alphacount;j++) {
			if (j!=0 && quantiletable[i][j]<quantiletable[i][j-1]) cout << "ERROR1 " << i << " " << j << endl;
			if (i!=2 && quantiletable[i][j]<quantiletable[i-1][j]) cout << "ERROR2 " << i << " " << j << endl;
		}
	}
	return 0;
}


/////////////////////////////////////////////////////////////////////
// Chi2 Static Data

long Chi2::quantiletable[lines+2][alphacount]=
{
// alpha in 1/1000
	{      5,    10,    25,    50,   100,   250,   500,   750,   900,   950,   975,   990,   995,   999},
// 1: *10000 [in 1/(10000*10000) ]
	{     393,    1571,   98210,  393200, 1579100,10150000,45490000,132300000,270600000,384100000,502400000,663500000,787900000,1082800000},
// 2 - all in 1/10000
	{   100,  0201,  0506,  1026,  2107,  5754, 13863, 27730, 46050, 59910, 73780, 92100,105970,138160},
	{   717,  1148,  2158,  3518,  5844, 12125, 23360, 41080, 62510, 78150, 93480,113450,128380,162660},
	{  2070,  2971,  4844,  7107, 10640, 19226, 33567, 53850, 77790, 94880,111430,122770,148600,184670},
// 5
	{  4117,  5543,  8312, 11450, 16100, 26750, 43510, 66260, 92360,110700,128330,150860,167500,205150},
	{  6757,  8721, 12370, 16350, 22040, 34550, 53480, 78410,106450,125920,144490,168120,185480,224580},
	{  9893, 12390, 16900, 21670, 28830, 42550, 63460, 90370,120170,140670,160130,184750,202780,243220},
	{ 13440, 16470, 21800, 27730, 34900, 50710, 73440,102190,133620,155070,175350,200900,219550,261240},
	{ 17350, 20880, 27000, 33250, 41680, 58990, 83430,113890,146840,169190,190230,216660,235890,278770},
// 10
	{  21560, 25580, 32470, 39400, 48650, 67370, 93420,125490,159870,183070,204830,232090,251880,295880},
	{ 26030, 30530, 38160, 45750, 55780, 75840,103410,137010,172450,196750,219200,247250,267570,312640},
	{ 30740, 35710, 44040, 52260, 63040, 84380,113400,148450,185490,210260,233370,262170,283000,329090},
	{ 35650, 41070, 50090, 59820, 70420, 92990,123400,159840,198120,223620,247360,276880,298190,345280},
	{ 40750, 46600, 56290, 65710, 77900,101650,133990,171170,210640,236850,261190,291410,313190,361230},
	{ 46010, 52290, 62620, 72610, 85470,110370,143390,182450,223070,249960,274880,305780,328010,376970},
	{ 51420, 58120, 69080, 79620, 93120,119120,153380,193690,235420,262960,288450,320000,342670,392520},
	{ 56970, 64080, 75640, 86720,100850,127920,163380,204890,247690,275870,301910,334090,357190,407900},
	{ 62650, 70150, 82310, 93900,108650,136750,173380,216050,259890,288690,315260,348050,371560,423120},
	{ 68440, 76330, 89070,101170,116510,145620,183380,227180,272040,301440,328520,361910,385820,438200},
//20
	{ 74340, 82600, 95910,108510,124430,154520,193370,238280,284120,314100,341700,375660,399970,453150},
	{ 80340, 88970,102830,115910,132400,163440,203370,249350,296150,326710,354790,389320,414010,467970},
	{ 86430, 95420,109820,123380,140410,172400,213370,260390,308130,339240,367810,402890,427960,482680},
	{ 92600,101960,116890,130910,148480,181370,223370,271410,320070,351720,380760,416380,441810,497280},
	{ 98860,108560,124010,138480,155690,190370,233370,282410,331960,364150,393640,429800,455590,511790},
	{ 105200,115240,131200,146110,164730,199400,243370,293390,343820,376520,406460,443140,469280,526200},
	{ 111600,121980,138440,153790,172920,208430,253360,304350,355630,388850,419230,456420,482900,540520},
	{ 118080,128790,145730,161510,181140,217490,263360,315280,367410,401130,431950,469630,496450,554760},
	{ 124610,135650,153080,169280,189390,226570,273360,326200,379160,413370,444610,482780,509930,568920},
	{ 131210,142560,160470,177080,197680,235570,283360,337110,390870,425570,457220,495880,523360,583010},
// 30: z(1-alpha)*100000
	{ -257583,-232635,-195966,-164485,-128155,-67449,0,67449,128155,164485,195996,232635,257583,309023},
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};




