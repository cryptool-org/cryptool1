/*This files version number is v0*/

/* s_ecconv.c    -- contains various function to convert numbers from one representation
		    into another
*/


/* Anna-Barbara Berger, Secude GmbH */

#include"arithmet.h"
#include"s_ecconv.h"
#include "ECsecude.h"


/*******************************************************************************************************/

/*tested, 25.2.99, ABB*/
#if defined (__STDC__) || defined (__cplusplus)
int char_to_int(char argument, int *result, const int base)
#else
int char_to_int(argument,result, base)
	char argument;
	int *result;
	const int base;
#endif
{
	int number=argument-'0';
	
	if (  !( (base==8)||(base==10)||(base==16) )  ) return (0); /*the indicated base is not supported*/

	if ( (0<=number) && (7>=number) ){
		*result=number;
		return (1); /*conversion successful*/
	}
	if ( (number>7) && (number<10) && (base>8) ){
		*result=number;
		return (1); /*conversion successful*/
	}
	number = 10 + (argument-'A');
	if ( (number>9) && (number<16) && (base>10) ){
		*result=number;
		return (1); /*conversion successful*/
	}
	return (0); /*conversion failed*/
}

/*******************************************************************************************************/

/*tested, 25.3.99, ABB*/	
#if defined (__STDC__) || defined (__cplusplus)
int string_to_ln(const char *argument, L_NUMBER *result)
#else
int string_to_ln(argument,result)
	const char *argument;
	L_NUMBER *result;
#endif
{
	L_NUMBER	base[MAXLGTH],temp[MAXLGTH];
	int reptype; /*indicates representation: 10=decimal, 8=octal, 16=hexadecimal*/
	const char *runner;
	int  help, negative=0;

	runner=argument;
	while (*runner==' ') runner=runner+1;
	
	if ( *runner=='\0' ) return(-1); /*" " is not a valid string*/

	/*Negative number?*/
	if (*runner=='-'){
		negative=1;
		runner=runner+1;
	}

	while (*runner==' ') runner=runner+1;
	/*Which base?*/
	if (*runner!='0') reptype=10;
	else{
		runner=runner+1;
		while (*runner==' ') runner=runner+1;
		if (*runner=='\0'){
			inttoln(0,result);
			return 0; /*"0" is conversed succesfully*/
		}
		if ( (*runner!='x')&&(*runner!='X') ) reptype=8;
		else{
			reptype=16;
			runner=runner+1;
		}
	}
	/*Compute result*/
	inttoln(reptype, base);
	while (*runner==' ')  runner=runner+1;
	if ((char_to_int(*runner,&help,reptype))==0) return(-1);/*conversion failed*/
	else inttoln(help,result);
	runner=runner+1;
	while (*runner==' ')  runner=runner+1;
	while (*runner!='\0'){
		SECUDE(mult)(result,base,result);
		if ((char_to_int(*runner,&help,reptype))==0) return(-1);/*conversion failed*/
		else{
			inttoln(help,temp);
			SECUDE(add)(result,temp,result);
		}
		runner=runner+1;
		while (*runner==' ')  runner=runner+1;
	}
	if (negative) return-2; /*the number stored in result is the negative of the number in argument*/
	else return 0;/*conversion successful*/
}

/*******************************************************************************************************/

/*tested, 25.3.99, ABB*/
#if defined (__STDC__) || defined (__cplusplus)
int string_to_int(const char *argument, int *result)
#else
int string_to_int(argument,result)
	char *argument;
	int *result;
#endif
{
	int	base,temp;
	int reptype; /*indicates representation: 10=decimal, 8=octal, 16=hexadecimal*/
	const char *runner;
	int negative=0;


	runner=argument;
	while (*runner==' ') runner=runner+1;
	if ( *runner=='\0' ) return(-1); /*" " is not a valid string*/

	/*Negative number?*/
	if (*runner=='-'){
		negative=1;
		runner=runner+1;
	}

	/*Which base?*/	
	if (*runner!='0') reptype=10;
	else{
		runner=runner+1;
		while (*runner==' ') runner=runner+1;
		if (*runner=='\0'){
			inttoln(0,result);
			return 0; /*"0" is conversed succesfully*/
		}
		if ( (*runner!='x')&&(*runner!='X') ) reptype=8;
		else{
			reptype=16;
			runner=runner+1;
		}
	}
	/*Compute result*/
	base=reptype;
	while (*runner==' ') runner=runner+1;
	if ((char_to_int(*runner,result,reptype))==0) return(-1);/*conversion failed*/
	runner=runner+1;
	while (*runner==' ') runner=runner+1;
	while (*runner!='\0') {
		*result=*result*base;
		if ((char_to_int(*runner,&temp,reptype))==0) return(-1);/*conversion failed*/
		else{
			*result=*result+temp;
		}
		runner=runner+1;
		while (*runner==' ') runner=runner+1;
	}
	if (negative) *result=-*result;
	return 0; /*conversion succeeded*/
}

/*******************************************************************************************************/

/*tested, 26.3.99, ABB*/
#if defined (__STDC__) || defined (__cplusplus)
void uint_to_char(unsigned int argument, char *result)
#else
void uint_to_char(argument,result)
	unsigned int argument;
	char *result;
#endif
{ 
	if ( argument<10 ) *result= (char)argument + '0';
	else *result= (char)(argument-10)+'A';
}

/*******************************************************************************************************/

#if defined (__STDC__) || defined (__cplusplus)
int ln_to_string(L_NUMBER *argument, char **result, int base)
#else
int ln_to_string(argument,result,base)
	L_NUMBER *argument;
	char **result;
	int base;
#endif
{
	char *rev_res, *res, s; 
	int count=0,help,rescount=0;
	L_NUMBER temp[MAXLGTH],zero[MAXLGTH], basis[MAXLGTH],rem[MAXLGTH];

	switch (base){
		case 8:			
		case 10:
			help=3;
			break;
		case 16:
			help=4;
			break;
		default:
			return (-1);/* The chosen base is not supported*/
	}
	rev_res = calloc( SECUDE(lngtouse)(argument)/help + 1, sizeof(char));
	res = calloc( SECUDE(lngtouse)(argument)/help + 5, sizeof(char));  /*?*/
	if ( (!rev_res) || (!res) ){
		if ( (!rev_res) && res ) free(res);
		if ( rev_res && (!res) ) free(rev_res);
		return (-1); /* Memory allocation error */
	}
	/*set the right prefix*/
	*result=res;
	switch (base){
		case 8:
			*result[0]='0';
			res=(*result)+1;
			break;
		case 10:
			break;
		case 16:
			(*result)[0]='0';
			(*result)[1]='X';
			res=(*result)+2;
			break;
	}

	inttoln(0,zero);
	if ( !SECUDE(comp)(argument,zero) ){
		rev_res[0]='0';
		count=count+1;
	}
	trans(argument, temp);
	inttoln(base,basis);
	/* find the string in reversed order*/
	while ( (SECUDE(comp)(temp,zero)) ){
		SECUDE(div)(temp,basis,temp,rem);
		uint_to_char(rem[1],&s);
		rev_res[count]=s;
		count=count+1;
	}
	/* reverse the order of the string in the reversed order*/
	count=count-1;
	while (count){
		res[rescount]=rev_res[count];
		count=count-1;
		rescount=rescount+1;
	}
	res[rescount]=rev_res[count];
	res[rescount+1]='\0';
	free(rev_res);
	return (0); /*conversion succeded*/
}

/***********************************************************************************************
/* 					sint_to_ln()
/***********************************************************************************************/

/* transform a positive signed int into a L_NUMBER, return (-1) if the signed int is not positive,
   0 otherwise */

#if defined (__STDC__) || defined (__cplusplus)
int sint_to_ln(const signed long int arg, L_NUMBER *res)
#else
int sint_to_ln (arg, res)
             const signed long int arg;
			 L_NUMBER *res;
#endif

{	unsigned long int  temp;

	if (arg<0) return (-1);
	temp = (unsigned long int) arg;
	res[0] = 1;
	res[1] = temp;
	return 0;
}



/***********************************EOF*************************************************************/