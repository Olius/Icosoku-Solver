#include <stddef.h>

#include "solve.h"

static int corner[20][3] = {
	 0,  1,  2,
	 0,  2,  3,
	 0,  3,  4,
	 0,  4,  5,
	 0,  5,  1,
	 1,  6,  2,
	 2,  6,  7,
	 2,  7,  3,
	 3,  7,  8,
	 3,  8,  4,
	 4,  8,  9,
	 4,  9,  5,
	 5,  9, 10,
	 5, 10,  1,
	 1, 10,  6,
	 6, 11,  7,
	 7, 11,  8,
	 8, 11,  9,
	 9, 11, 10,
	10, 11,  6,
};

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
			f->n[c] = n + corner[f-fs][c];
	return try(k,ds,fs,fs);
}
