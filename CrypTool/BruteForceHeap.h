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

#pragma once

#include <algorithm>
#include <functional>

#define ENTROPY_INVERTER 10000.0

using namespace std;

struct candidate {
	double entropy;
	char *key;
	char *plain;
	int   plain_size;
};

struct less_mag : public binary_function<candidate, candidate, bool> {
	bool operator()(candidate &x, candidate &y) { return x.entropy < y.entropy; }
};

class CBruteForceHeap
{
	long max_heapsize;
	double max_entropy;

public:
	long keysize;
	long keybytes;
	long heapsize;
	long plainbytes;
	struct candidate *list;

	CBruteForceHeap(void);
	~CBruteForceHeap(void);
	int init(long _keybytes, long _plainbytes, long _max_heapsize);
    int add_candidate(double entropy, char *key, char *plain, int plainsize);
	int check_add(double entropy)
	{ return ((heapsize < max_heapsize) || (entropy < max_entropy) ); }
	int sort() {
		if ( heapsize > 1 )
		{
			sort_heap(list, list+heapsize, less_mag());
			return 1;
		}
		return 0;
	}
};


