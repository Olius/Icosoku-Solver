extern int vert[V];

typedef struct Face Face;
struct Face {
	Tile *tile;
	int rot;
	int *const vert[3];
};

int solve(Face *f);
void printgame(void);
