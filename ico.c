#include <stdio.h>
#include <stdlib.h>

#include "solve.h"
#include "print.h"

void read(num n[12])
{
	for (int i = 0; i < 12; i++) {
		char s[] = "0";
		s[0] = getchar();
		n[i] = strtol(s, NULL, 16);
	}
}

int main(void)
{
	tiledef ds[] = {
		3,3,3, 1,
		2,2,2, 1,
		1,3,2, 2,
		1,2,3, 2,
		1,1,1, 1,
		0,3,3, 1,
		0,2,2, 1,
		0,2,1, 3,
		0,1,2, 3,
		0,1,1, 1,
		0,0,3, 1,
		0,0,2, 1,
		0,0,1, 1,
		0,0,0, 1,
	};
	const int k = sizeof(ds)/sizeof(tiledef);

	num n[12];
	read(n);
	face fs[20];
	return !solve(k,ds,n,fs) || print(fs);
}
