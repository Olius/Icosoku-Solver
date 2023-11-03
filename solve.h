typedef struct Vert Vert;
typedef struct Face Face;
struct Vert {
	int val;
	Face */*const*/ incid[5];
};
struct Face {
	Tile *tile;
	int rot;
	Vert *const vert[3];
};

extern Vert vert[V];
int solve(Face *f);
void printgame(void);
