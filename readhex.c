#include <stdio.h>
#include <stdlib.h>

#include "readhex.h"

int readhex(void)
{
	char s[] = "0";
	s[0] = getchar();
	return strtol(s, NULL, 16);
}
