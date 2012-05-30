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

#include "CrypToolPRNG.h"
#include "DlgCrypToolPRNGSeedCollector.h"
#include <rand.h>

// implements a very simple PRNG (based on std::rand for now)
class CrypToolPRNG {
protected:
	CrypToolPRNG() :
		initialized(false) {

	}
public:
	static CrypToolPRNG *pInstance() {
		static CrypToolPRNG instance;
		return &instance;
	}
protected:
	bool initialized;
public:
	int getRandomBit() {
		if(!initialized) {
			calculateRandomSeed();
			initialized = true;
		}
		// TODO/FIXME: is rand() good enough for our needs?
		return rand() % 2;
	}
	unsigned long getRandomInt(unsigned long _range) {
		if(!initialized) {
			calculateRandomSeed();
			initialized = true;
		}
		// TODO/FIXME: is rand() good enough for our needs?
		return rand() % _range;
	}
protected:
	void calculateRandomSeed() {
		// let the user create some 'random' data
		CDlgCrypToolPRNGSeedCollector dlg;
		dlg.DoModal();
		// use the newly created data as seed
		srand(dlg.getSeed());	
	}
};

int CrypToolPRNG_GetRandomBit() {
	return CrypToolPRNG::pInstance()->getRandomBit();
}

unsigned long CrypToolPRNG_GetRandomInt(unsigned long _range) {
	return CrypToolPRNG::pInstance()->getRandomInt(_range);
}