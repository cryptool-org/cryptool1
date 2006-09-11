#pragma once

#include "stdafx.h"
#include "afxwin.h"

#include "EvoZahlenHai.h"

__int64 getNumberOfRounds();
int maxPoints(int upperLimit);
int getTime();
int maxPrime(int upperLimit);
bool isPrime(int upperLimit);

int getNextIntValue(CString &str, char Sep='|');
__int64 getNextInt64Value(CString &str, char Sep='|');

//extern int globalPoints;
extern int endSearch;
UINT maxPointsStatic(LPVOID param);

