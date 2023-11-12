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
			int c;
			for (c = 0; c < 3; c++) {
				vertex *v = f->vs[c];
				v->n -= f->t->n[(c+f->r)%3];
				if (v->n > 0)
					continue;
				if (v->n < 0)
					break;
				int i;
				for (i = 0; i < 5; i++)
					if (v->fs[i] == NULL)
						break;
				if (i < 5)
					break;
			}
			if (c == 3 && c-- && try(k,ds,fs,f+1))
				return 1;
			for (; c >= 0; c--)
				f->vs[c]->n += f->t->n[(c+f->r)%3];
		}
		f->t->q++;
	}
	return 0;
}

int solve(size_t k, tiledef ds[k], vertex vs[12], face fs[20])
{
	face **ifs[12];
	for (int i = 0; i < 12; i++)
		ifs[i] = vs[i].fs;
	for (face *f = fs; f < fs+20; f++)
		for (int c = 0; c < 3; c++) {
			*ifs[corners[f-fs][c]]++ = f;
			f->vs[c] = vs + corners[f-fs][c];
			f->t = NULL;
		}
	return try(k,ds,fs,fs);
}
