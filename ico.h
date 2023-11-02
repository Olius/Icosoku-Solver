typedef struct Tile Tile;
struct Tile {
	const int dots[3];
	int qty;
};

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

enum { kinds = sizeof(tiles)/sizeof(Tile) };

typedef struct Face Face;
struct Face {
	Tile *tile;
	int rot;
	int *const vert[3];
};
