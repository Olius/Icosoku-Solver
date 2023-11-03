#include <stdio.h>

#include "ico.h"
#include "solve.h"

int vert[V];
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
static Face *incid[V][5];

void printgame(void)
{
	for (Face *f = face; f < face+F; f++) {
		for (int c = 0; c < 3; c++)
			printf("%X", f->tile->dots[(c+f->rot)%3]);
		putchar('\n');
	}
}

void setup(Face *f)
{
	Face **next[V];
	for (int v = 0; v < V; v++)
		next[v] = &incid[v][0];
	for (f = face; f < face+F; f++)
		for (int c = 0; c < 3; c++)
			*next[f->vert[c]-vert]++ = f;
}

int solve(Face *f)
{
	//printf("%c: ", 'A'+(char)(f-face));
	//printvert();
	if (f == NULL)
		setup(f = face);
	else if (f == face+F)
		return 1;
	for (f->tile = tiles; f->tile < tiles+kinds; f->tile++) {
		if (f->tile->qty <= 0)
			continue;
		f->tile->qty--;
		for (f->rot = 0; f->rot < 3; f->rot++) {
			int c;
			for (c = 0; c < 3; c++)
				*f->vert[c] -= f->tile->dots[(c+f->rot)%3];
			for (c = 0; c < 3; c++)
				if (*f->vert[c] < 0)
					break;
			if (c == 3 && solve(f+1))
				return 1;
			for (c = 0; c < 3; c++)
				*f->vert[c] += f->tile->dots[(c+f->rot)%3];
		}
		f->tile->qty++;
	}
	return 0;
}
