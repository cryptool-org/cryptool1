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


