#include <stdio.h>

#include "readhex.h"
#include "corners.h"

int main()
{
	int ns[12];
	for (int v = 0; v < 12; v++)
		ns[v] = readhex();
	for (int f = 0; f < 20; f++)
		for (int c = 0; c < 3; c++)
			ns[corners[f][c]] -= readhex();
	for (int v = 0; v < 12; v++)
		if (ns[v] != 0) {
			fprintf(stderr, "check: incorrect solution\n");
			return 1;
		}
	return 0;
}
