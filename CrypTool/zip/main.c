#include <stdio.h>
#include <stdlib.h>
#include "zipup.h"
#include "zunzip.h"

int main(int argc, char *argv[])
{
	FILE *fi, *fo;
	int i;

	fi = fopen(argv[1],"rb");
	fo = fopen(argv[2],"wb");

	i = zipup(fi, fo);

	fclose(fi);
	fclose(fo);

	if(i) {
		printf("returncode %d\n",i);
		return i;
	}

	fi = fopen(argv[2],"rb");
	fo = fopen(argv[3],"wb");

	i = unzip(fi, fo);

	fclose(fi);
	fclose(fo);
	if(i) {
		printf("returncode %d\n",i);
		return i;
	}

	return 0;

}
