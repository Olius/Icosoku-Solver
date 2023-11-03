#include <stdio.h>
#include <stdlib.h>

#include "ico.h"
#include "solve.h"

Vert vert[V];
Face *sface[F];
static Face face[F] = {
	{.vert={vert+0,vert+1,vert+2}},
	{.vert={vert+0,vert+2,vert+3}},
	{.vert={vert+0,vert+3,vert+4}},
	{.vert={vert+0,vert+4,vert+5}},
	{.vert={vert+0,vert+5,vert+1}},
	{.vert={vert+1,vert+6,vert+2}},
	{.vert={vert+2,vert+6,vert+7}},
	{.vert={vert+2,vert+7,vert+3}},
	{.vert={vert+3,vert+7,vert+8}},
	{.vert={vert+3,vert+8,vert+4}},
	{.vert={vert+4,vert+8,vert+9}},
	{.vert={vert+4,vert+9,vert+5}},
	{.vert={vert+5,vert+9,vert+10}},
	{.vert={vert+5,vert+10,vert+1}},
	{.vert={vert+1,vert+10,vert+6}},
	{.vert={vert+6,vert+11,vert+7}},
	{.vert={vert+7,vert+11,vert+8}},
	{.vert={vert+8,vert+11,vert+9}},
	{.vert={vert+9,vert+11,vert+10}},
	{.vert={vert+10,vert+11,vert+6}},
};

void printgame(void)
{
	for (Face *f = face; f < face+F; f++) {
		for (int c = 0; c < 3; c++)
			printf("%X", f->tile->dots[(c+f->rot)%3]);
		putchar('\n');
	}
}

int facecmp(const void *p1, const void *p2)
{
	Face *f1 = *(Face **)p1, *f2 = *(Face **)p2;
	int d = 0;
	for (int c = 0; c < 3; c++)
		d += f1->vert[c]->val - f2->vert[c]->val;
	return d;
}

void setup(Face *f)
{
	Face **next[V];
	for (int i = 0; i < V; i++)
		next[i] = vert[i].incid;
	for (f = face; f < face+F; f++) {
		f->tile = NULL;
		for (int c = 0; c < 3; c++)
			*next[f->vert[c]-vert]++ = f;
	}
	for (int i = 0; i < F; i++)
		sface[i] = &face[i];
	qsort(sface, F, sizeof(*sface), facecmp);
}

int solve(Face **sf)
{
	//printf("%c: ", 'A'+(char)(f-face));
	//printvert();
	if (sf == NULL) {
		setup(face);
		sf = sface;
	}
	else if (sf == sface+F)
		return 1;
	Face *f = *sf;
	for (f->tile = tiles; f->tile < tiles+kinds; f->tile++) {
		if (f->tile->qty <= 0)
			continue;
		f->tile->qty--;
		for (f->rot = 0; f->rot < 3; f->rot++) {
			int c;
			for (c = 0; c < 3; c++)
				f->vert[c]->val -= f->tile->dots[(c+f->rot)%3];
			for (c = 0; c < 3; c++) {
				if (f->vert[c]->val < 0)
					break;
				int i;
				for (i = 0; i < 5; i++)
					if (f->vert[c]->incid[i]->tile == NULL)
						break;
				if (i == 5 && f->vert[c]->val > 0)
					break;
			}
			if (c == 3 && solve(sf+1))
				return 1;
			for (c = 0; c < 3; c++)
				f->vert[c]->val += f->tile->dots[(c+f->rot)%3];
		}
		f->tile->qty++;
	}
	f->tile = NULL;
	return 0;
}
