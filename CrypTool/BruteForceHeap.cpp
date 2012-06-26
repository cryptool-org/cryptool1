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

#include ".\bruteforceheap.h"



int CBruteForceHeap::init(long _keybytes, long _plainbytes, long _max_heapsize)
{
	keybytes = _keybytes;
	plainbytes = _plainbytes;

	list = new candidate[_max_heapsize];
	if ( list )
	{
		max_heapsize = _max_heapsize;
		heapsize = 0;
		for (int i=0; i<max_heapsize; i++)
		{
			list[i].key = new char[keybytes*2+1];
			list[i].plain = new char[plainbytes];
			if (!list[i].key || !list[i].plain )
			{
				// FIXME throw "mem alloc error"
			}
		}
	}
	else
	{
		// ERROR throw "mem alloc error"
	}

	return 0;
}

int CBruteForceHeap::add_candidate(double entropy, char *key, char *plain, int plainsize)
{
	if (heapsize < max_heapsize)
	{
		heapsize++;
	}
	else
	{
		if ( entropy < max_entropy )
		{
			pop_heap(list, list+heapsize, less_mag());
		}
		else
			return 0; // no candidate
	}

	memcpy(list[heapsize-1].key, key, keybytes*2);
	list[heapsize-1].key[keybytes*2] = '\0';
#if 1
	// flomar, 06/25/2012: the following lines prevent CrypTool from crashing; in 
	// case the input parameter 'plain' was too large, the 'memcpy' call below would 
	// corrupt the heap; now we're dynamically allocating (more) memory if needed
	if(list[heapsize-1].plain_size < plainsize) {
		delete []list[heapsize-1].plain;
		list[heapsize-1].plain = new char[plainsize];
		list[heapsize-1].plain_size = plainsize;
	}
#endif
	memcpy(list[heapsize-1].plain, plain, plainsize);
	list[heapsize-1].plain_size = plainsize;
	list[heapsize-1].entropy = entropy;
	push_heap(list, list+heapsize, less_mag());
	if ( heapsize >= max_heapsize )
	{
		max_entropy = list[0].entropy;
	}
	return 1; // new candidate
}


CBruteForceHeap::CBruteForceHeap(void)
{
	heapsize = max_heapsize = 0;
	max_entropy = ENTROPY_INVERTER;
}

CBruteForceHeap::~CBruteForceHeap(void)
{
	if ( heapsize )
	{
		for (int i=0; i<max_heapsize; i++)
		{
			delete []list[i].key;
			delete []list[i].plain;
		}
		delete []list;
	}
}
