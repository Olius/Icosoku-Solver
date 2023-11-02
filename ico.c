#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "ico.h"

enum {
	V = 12, F = 20,
};

int vert[V];
Face face[F] = {
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

int readhex(int n, int buf[n]);
void printgame(void);
int solve(Face *f);

int main()
{
	if (readhex(V,vert)) {
		fprintf(stderr, "ico: expected hex character, "
			"not '%c'\n", getchar());
		exit(EXIT_FAILURE);
	}
	if (solve(face))
		printgame();
}

int readhex(int n, int buf[n])
{
	for (int i = 0; i < n; i++) {
		int c = getchar();
		if (c == EOF || !isxdigit(c)) {
			ungetc(c, stdin);
			return -1;
		}
		char str[] = {0,'\0'};
		str[0] = c;
		buf[i] = strtol(str, NULL, 16);
	}
	return 0;
}

void printgame(void)
{
	for (Face *f = face; f < face+F; f++) {
		for (int c = 0; c < 3; c++)
			printf("%X", f->tile->dots[(c+f->rot)%3]);
		putchar('\n');
	}
}

void printvert(void)
{
	for (int *v = vert; v < vert+V; v++)
		printf("%X", *v);
	putchar('\n');
}

int solve(Face *f)
{
	//printf("%c: ", 'A'+(char)(f-face));
	//printvert();
	if (f == face+F)
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
