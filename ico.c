#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "ico.h"
#include "solve.h"

Tile tiles[] = {
	{0,0,0, 1},
	{0,0,1, 1},
	{0,0,2, 1},
	{0,0,3, 1},
	{0,1,1, 1},
	{0,1,2, 3},
	{0,2,1, 3},
	{0,2,2, 1},
	{0,3,3, 1},
	{1,1,1, 1},
	{1,2,3, 2},
	{1,3,2, 2},
	{2,2,2, 1},
	{3,3,3, 1},
};
const int kinds = sizeof(tiles)/sizeof(Tile);

void printhex(int n, int buf[n])
{
	for (int *p = buf; p < buf+n; p++)
		printf("%X", *p);
	putchar('\n');
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

int main()
{
	int buf[V];
	if (readhex(V,buf)) {
		fprintf(stderr, "ico: expected hex character, "
			"not '%c'\n", getchar());
		exit(EXIT_FAILURE);
	}
	for (int v = 0; v < V; v++)
		vert[v].val = buf[v];
	if (solve(NULL))
		printgame();
}
