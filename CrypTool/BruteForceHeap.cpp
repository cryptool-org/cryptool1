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

	strncpy(list[heapsize-1].key, key, keybytes*2);
	list[heapsize-1].key[keybytes*2] = '\0';
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
