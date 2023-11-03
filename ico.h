enum {
	V = 12, F = 20,
};

extern int vert[V];

typedef struct Tile Tile;
struct Tile {
	const int dots[3];
	int qty;
};

extern const int kinds;
extern Tile tiles[];
