#include <stddef.h>

#include "solve.h"
#include "corners.h"

static int try(const size_t k, tiledef ds[k], face fs[20], face *f)
{
	if (f == fs+20)
		return 1;
	for (f->t = ds; f->t < ds+k; f->t++) {
		if (f->t->q == 0)
			continue;
		f->t->q--;
		for (f->r = 0; f->r < 3; f->r++) {
			for (int c = 0; c < 3; c++)
				*f->n[c] -= f->t->n[(c+f->r)%3];
			int c;
			for (c = 0; c < 3; c++)
				if (*f->n[c] < 0)
					break;
			if (c == 3 && try(k,ds,fs,f+1))
				return 1;
			for (int c = 0; c < 3; c++)
				*f->n[c] += f->t->n[(c+f->r)%3];
		}
		f->t->q++;
	}
	return 0;
}

int solve(size_t k, tiledef ds[k], num n[12], face fs[20])
{
	for (face *f = fs; f < fs+20; f++)
		for (int c = 0; c < 3; c++)
			f->n[c] = n + corners[f-fs][c];
	return try(k,ds,fs,fs);
}
