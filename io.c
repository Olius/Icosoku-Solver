#include <stdio.h>

#include "solve.h"
#include "io.h"

int printface(face *f)
{
	for (int c = 0; c < 3; c++)
		if (printf("%1X", f->t->n[(c+f->r)%3]) == 0)
			return 1;
	return putchar('\n') == EOF;
}

int print(face fs[20])
{
	for (face *f = fs; f < fs+20; f++)
		if (printface(f))
			return 1;
	return 0;
}
