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

//////////////////////////////////////////////////////////////////////
// NTLExpPars.cpp: Implementierung der Klasse NTLExpPars.
// 
// Author: Matthias Schneider
//
// This class provides a simple parser for arithmetical expressions.
// The method parseExp takes the expression as argument
// and returns its value or 0 if it is malformed.
//
// Example: "-2*(3+4)*5^2" returns -350
//////////////////////////////////////////////////////////////////////
#include "NTLExpPars.h"
#include "afx.h"
#include "ZZ_helpers.h"
#include <stack>



//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

NTLExpPars::NTLExpPars()
{
	lastToken=0;
}

NTLExpPars::~NTLExpPars()
{

}
//////////////////////////////////////////////////////////////////////
// This method parses the string. It gets the next token from the
// scanner method (nextToken) and maintains two stacks to
// transform the expression from infix to postfix notation.
// It evaluates the expression considering the operator precendence.
//////////////////////////////////////////////////////////////////////
ZZ NTLExpPars::parseExp(CString e)
{
	std::stack<ZZ> valueStack; // stack for the values
	std::stack<int> operatorStack; //stack for the operators
	ZZ val; // keeps the value of the token if it is a number
	int token=nextToken(e, val); // calls the scanner method
	while( token!=NTL_OP_END && token!=NTL_OP_ERROR ){ // loops the expression
		switch(token){
		case NTL_OP_NUMBER: valueStack.push(val); break; 
		case NTL_OP_OPENPAR: operatorStack.push(token); break;
		case NTL_OP_CLOSEPAR: // when parenthesis is closed...
							 //... evaluate the whole parenthesis term
			while(!operatorStack.empty()&&operatorStack.top()!=NTL_OP_OPENPAR){
				if(valueStack.size()>=2){
					ZZ a = valueStack.top();
					valueStack.pop();
					ZZ b = valueStack.top();
					valueStack.pop();
					ZZ r = calc(b,a,operatorStack.top());
					operatorStack.pop();
					valueStack.push(r);
				}else return to_ZZ(0);
			}
			if(!operatorStack.empty())
				operatorStack.pop();
			else return to_ZZ(0);
			break;
		case NTL_OP_PLUS:
		case NTL_OP_MINUS:
		case NTL_OP_POWER:
		case NTL_OP_TIMES:
		case NTL_OP_DIV: 
			// check wheter the top of the opStack has lower precendence than token
			while(!operatorStack.empty()&&lowPrecedence(token,operatorStack.top())){
				// if so evaluate the stack until higher operator is found
				if(valueStack.size()>=2){
					ZZ a = valueStack.top();
					valueStack.pop();
					ZZ b = valueStack.top();
					valueStack.pop();
					ZZ r = calc(b,a,operatorStack.top());
					operatorStack.pop();
					valueStack.push(r);
				}else return to_ZZ(0);
			}
			operatorStack.push(token);
			break;
		}
		token=nextToken(e, val);
	}
	while(!operatorStack.empty()){
	if(valueStack.size()>=2){
					ZZ a = valueStack.top();
					valueStack.pop();
					ZZ b = valueStack.top();
					valueStack.pop();
					ZZ r = calc(b,a,operatorStack.top());
					operatorStack.pop();
					valueStack.push(r);
				}else return to_ZZ(0);
	}
	// if still multiple elements on value stack
	// multiply them so that 3(1+1) = 6
	while(valueStack.size()>=2){
		ZZ a = valueStack.top();
		valueStack.pop();
		ZZ b = valueStack.top();
		valueStack.pop();
		ZZ r = a*b;
		valueStack.push(r);
	}
	if(!valueStack.empty())
		return valueStack.top();
	else return to_ZZ(0);
}
//////////////////////////////////////////////////////////////////////
// This is the scanner method. It seperates the String into tokens
// and also returns the values of the numbers.
//////////////////////////////////////////////////////////////////////
int NTLExpPars::nextToken(CString& e, ZZ& v)
{
	e.TrimLeft();
	if(e.IsEmpty())
		return NTL_OP_END; 

	if(e.Left(1)=="+"){
		e=e.Right(e.GetLength()-1);
		lastToken=NTL_OP_PLUS; 
		return NTL_OP_PLUS;
	}


	if(e.Left(1)=="*") {
		e=e.Right(e.GetLength()-1);
		lastToken=NTL_OP_TIMES;
		return NTL_OP_TIMES;	
	}
	if(e.Left(1)=="/") {
		e=e.Right(e.GetLength()-1);
		lastToken=NTL_OP_DIV;
		return NTL_OP_DIV;
	}
	if(e.Left(1)=="^") {
		e=e.Right(e.GetLength()-1);
		lastToken=NTL_OP_POWER;
		return NTL_OP_POWER;
	}
	if(e.Left(1)=="(") {
		e=e.Right(e.GetLength()-1);
		lastToken=NTL_OP_OPENPAR;
		return NTL_OP_OPENPAR;
	}
	if(e.Left(1)==")") {
		e=e.Right(e.GetLength()-1);
		lastToken=NTL_OP_CLOSEPAR;
		return NTL_OP_CLOSEPAR;
	}
	int figCount=0;
	// if the "-" comes after a number or ) it is binary
	if(e.Left(1)=="-"){
		if(lastToken==NTL_OP_CLOSEPAR
			||lastToken==NTL_OP_NUMBER){
				e=e.Right(e.GetLength()-1);
				lastToken=NTL_OP_MINUS;
				return NTL_OP_MINUS;
		}else figCount=1; 
		// else the "-" belongs to the following number (unary)
	}
	// count the figures
	while(e.Mid(figCount,1)>="0"&&e.Mid(figCount,1)<="9")
		figCount++;
	// cast ZZ to String and return the Number token
	// as well as the value
	if(figCount>0){
		v=setToStringValue(e.Left(figCount),10);
		e=e.Right(e.GetLength()-figCount);
		lastToken=NTL_OP_NUMBER;
		return NTL_OP_NUMBER;
	}

	return NTL_OP_ERROR;// if we get to here, there was a wrong character
}
//////////////////////////////////////////////////////////////////////
// Simple function to calculate the value depending on the 
// operator token
//////////////////////////////////////////////////////////////////////
ZZ NTLExpPars::calc(ZZ a, ZZ b, int op)
{
	switch(op){
	case NTL_OP_PLUS:
		return a+b;
		break;
	case NTL_OP_MINUS:
		return a-b;
		break;
	case NTL_OP_TIMES:
		return a*b;
		break;
	case  NTL_OP_DIV:
		return a/b;
		break;
	case NTL_OP_POWER:
		if(b>0)
			return power(a,to_int(b));
		break;
	}
	return to_ZZ(0);
}
//////////////////////////////////////////////////////////////////////
// Returns true if the precedence of a is higher than or 
// equal to the precedence of b
//////////////////////////////////////////////////////////////////////
bool NTLExpPars::lowPrecedence(int a, int b)
{
	if((b==NTL_OP_OPENPAR)||(b==NTL_OP_CLOSEPAR))
		return false;
	if(a==NTL_OP_PLUS||a==NTL_OP_MINUS)
		return true;
	if(a==NTL_OP_TIMES||a==NTL_OP_DIV)
		return b>=NTL_OP_TIMES;
	if(a==NTL_OP_POWER)
		return b>=NTL_OP_POWER;
	return false;
}
