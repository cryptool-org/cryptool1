/*s_ecpX9c.c  --	Definitions for initializing the sample curves given in J.5 of the X9.62 standard
					1999, Anna-Barbara Berger*/

  

	
	  

#include "arithmet.h"
#include <string.h>
#include "s_ecFp.h"
//#include "s_ecpX9c.h" /*header file of this source code*/
#include "s_ecconv.h"
/****************************************************************************************************************/
/*																							X9_62_init_curve()
/***************************************************************************************************************/


#if defined (__STDC__) || defined (__cplusplus)
X9_62_init_curve(ecFp_curve_destptr E, ecFp_point_ac_destptr G,L_NUMBER *cofactor, L_NUMBER *primefactor, char *curve_ID)
#else
X9_62_init_curve(E, G, cofactor, primefactor, curve_ID)
	ecFp_curve_destptr E;
	ecFp_point_ac_destptr G;
	L_NUMBER *cofactor, *primefactor;
	char *curve_ID;
#endif
{	
	int help;
	L_NUMBER G_compressed[MAXLGTH];

	if (strcmp( curve_ID, "prime192v1")==0) {
		help=string_to_ln( "0X FFFFFFFF 	FFFFFFFF 	FFFFFFFF 	FFFFFFFE 	FFFFFFFF FFFFFFFC",E->a);
		if (help == -1) return (-1);
		help=string_to_ln("0X 64210519 E59C80E7 0FA7E9AB 72243049 FEB8DEEC C146B9B1" ,E->b);
		if (help == -1) return (-1);
		help=string_to_ln("627 71017 35386 68076 38357 89423 20766 64160 83908 70039 03249 61279" ,E->p);
		if (help == -1) return (-1);
		help=string_to_ln("0X 3 188DA80E B03090F6 7CBF20EB 43A18800 F4FF0AFD 82FF1012",G_compressed);
		if (help == -1) return (-1);
		ecFp_X9_decompress_point_ac(G,E,G_compressed);
		help=string_to_ln("01" ,cofactor);
		if (help == -1)	return (-1);
		help=string_to_ln("0X FFFFFFFF 	FFFFFFFF 	FFFFFFFF 	99DEF836 	146BC9B1 B4D22831" ,primefactor);
		if (help == -1) return (-1);
		return 0;
	}

	if (strcmp( curve_ID, "prime192v2")==0) {
		help=string_to_ln( "0X FFFFFFFF 	FFFFFFFF 	FFFFFFFF 	FFFFFFFE 	FFFFFFFF FFFFFFFC",E->a);
		if (help == -1) return (-1);
		help=string_to_ln("0X CC22D6DF B95C6B25 	E49C0D63 	64A4E598 	0C393AA2 1668D953" ,E->b);
		if (help == -1) return (-1);
		help=string_to_ln("627 71017 35386 68076 38357 89423 20766 64160 83908 70039 03249 61279" ,E->p);
		if (help == -1) return (-1);
		help=string_to_ln("0X 3 EEA2BAE7 E1497842 F2DE7769 CFE9C989 C072AD69 6F48034A",G_compressed);
		if (help == -1)	return (-1);
		ecFp_X9_decompress_point_ac(G,E,G_compressed);
		help=string_to_ln("01" ,cofactor);
		if (help == -1) return (-1);
		help=string_to_ln("0X FFFFFFFF 	FFFFFFFF 	FFFFFFFE 	5FB1A724 	DC804186 48D8DD31" ,primefactor);
		if (help == -1) return (-1);
		return 0;
	}
	if (strcmp( curve_ID, "prime192v3")==0) {
		help=string_to_ln( "0X FFFFFFFF 	FFFFFFFF 	FFFFFFFF 	FFFFFFFE 	FFFFFFFF FFFFFFFC",E->a);
		if (help == -1) return (-1);
		help=string_to_ln("0X 22123DC2 	395A05CA 	A7423DAE 	CCC94760 	A7D46225 6BD56916" ,E->b);
		if (help == -1) return (-1);
		help=string_to_ln("627 71017 35386 68076 38357 89423 20766 64160 83908 70039 03249 61279 " ,E->p);
		if (help == -1) return 1;
		help=string_to_ln("0X 2 7D297781 00C65A1D A1783716 588DCE2B 8B4AEE8E 228F1896",G_compressed);
		if (help == -1)	return (-1);
		ecFp_X9_decompress_point_ac(G,E,G_compressed);
		help=string_to_ln("01" ,cofactor);
		if (help == -1) return (-1);
		help=string_to_ln("0X FFFFFFFF 	FFFFFFFF 	FFFFFFFF 	7A62D031 	C83F4294 F640EC13" ,primefactor);
		if (help == -1) return (-1);
		return 0;
	}

	if (strcmp( curve_ID, "prime239v1")==0) {
	help=string_to_ln( "0X 7FFF FFFFFFFF FFFFFFFF FFFF7FFF FFFFFFFF 80000000 00007FFF FFFFFFFC",E->a);
		if (help == -1) return (-1);
		help=string_to_ln("0X 6B01 6C3BDCF1 8941D0D6 54921475 CA71A9DB 2FB27D1D 37796185 C2942C0A" ,E->b);
		if (help == -1) return (-1);
		help=string_to_ln("883423532389192164791648750360308885314476597252960362 792450860609699839" ,E->p);
		if (help == -1) return (-1);
		help=string_to_ln("0X 20FFA 963CDCA8 816CCC33 B8642BED F905C3D3 58573D3F 27FBBD3B 3CB9AAAF",G_compressed);
		if (help == -1) return (-1);
		ecFp_X9_decompress_point_ac(G,E,G_compressed);
		help=string_to_ln("01" ,cofactor);
		if (help == -1) return (-1);
		help=string_to_ln("0X 7FFF FFFFFFFF FFFFFFFF FFFF7FFF FF9E5E9A 9F5D9071 FBD15226 88909D0B" ,primefactor);
		if (help == -1) return (-1);
		return 0;
	}

	if (strcmp( curve_ID, "prime239v2")==0) {
	help=string_to_ln("0X 7FFF FFFFFFFF FFFFFFFF FFFF7FFF FFFFFFFF 80000000 00007FFF FFFFFFFC",E->a);
		if (help == -1) return (-1);
		help=string_to_ln("0X 617F AB683257 6CBBFED5 0D99F024 9C3FEE58 B94BA003 8C7AE84C 8C832F2C" ,E->b);
		if (help == -1) return (-1);
		help=string_to_ln("883423532389192164791648750360308885314476597252960362 792450860609699839" ,E->p);
		if (help == -1) return(-1);
		help=string_to_ln("0X 238AF 09D98727 705120C9 21BB5E9E 26296A3C DCF2F357 57A0EAFD 87B830E7",G_compressed);
		if (help == -1)	return(-1);		
		ecFp_X9_decompress_point_ac(G,E,G_compressed);
		help=string_to_ln("01" ,cofactor);
		if (help == -1) return(-1);
		help=string_to_ln("0X 7FFF FFFFFFFF FFFFFFFF FFFF8000 00CFA7E8 594377D4 14C03821 BC582063" ,primefactor);
		if (help == -1) return(-1);
		return 0;
	}
	if (strcmp( curve_ID, "prime239v3")==0) {
	help=string_to_ln("0X 7FFF FFFFFFFF FFFFFFFF FFFF7FFF FFFFFFFF 80000000 00007FFF FFFFFFFC",E->a);
		if (help == -1) return(-1);
		help=string_to_ln("0X 2557 05FA2A30 6654B1F4 CB03D6A7 50A30C25 0102D498 8717D9BA 15AB6D3E" ,E->b);
		if (help == -1) return(-1);
		help=string_to_ln("883423532389192164791648750360308885314476597252960362 792450860609699839" ,E->p);
		if (help == -1) return(-1);
		help=string_to_ln("0X 36768 AE8E18BB 92CFCF00 5C949AA2 C6D94853 D0E660BB F854B1C9 505FE95A",G_compressed);
		if (help == -1)	return(-1);
		ecFp_X9_decompress_point_ac(G,E,G_compressed);
		help=string_to_ln("01" ,cofactor);
		if (help == -1) return(-1);
		help=string_to_ln("0X 7FFF FFFFFFFF FFFFFFFF FFFF7FFF FF975DEB 41B3A605 7C3C4321 46526551" ,primefactor);
		if (help == -1) return(-1);
		return 0;
	}
	if (strcmp( curve_ID, "prime256v1")==0) {
	help=string_to_ln("0X FFFFFFFF 00000001 00000000 00000000 00000000 FFFFFFFF FFFFFFFF FFFFFFFC",E->a);
		if (help == -1) return(-1);
		help=string_to_ln("0X 5AC635D8 AA3A93E7 B3EBBD55 769886BC 651D06B0 CC53B0F6 3BCE3C3E 27D2604B" ,E->b);
		if (help == -1) return(-1);
		help=string_to_ln("11579208921035624876269744694940757353008614341529031419 5533631308867097853951 " ,E->p);
		if (help == -1) return(-1);
		help=string_to_ln("0X 3 6B17D1F2 E12C4247 F8BCE6E5 63A440F2 77037D81 2DEB33A0 F4A13945 D898C296",G_compressed);
		if (help == -1)	return(-1);
		ecFp_X9_decompress_point_ac(G,E,G_compressed);
		help=string_to_ln("01",cofactor);
		if (help == -1) return(-1);
		help=string_to_ln("0X FFFFFFFF 00000000 FFFFFFFF FFFFFFFF BCE6FAAD A7179E84 F3B9CAC2 FC632551" ,primefactor);
		if (help == -1) return(-1);
		return 0;	
	}
	return (-1); // the curve with the name indicated is not defined in this file 
}



