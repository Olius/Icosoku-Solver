typedef int num;
typedef struct {
	const num n[3];
	unsigned int q;
} tiledef;
typedef tiledef *tile;
typedef struct {
	tile *ts[5];
	num n;
} vertex;
typedef struct {
	vertex *vs[3];
	tile t;
	int r;
} face;

int solve(size_t k, tiledef td[], vertex vs[12], face fs[20]);
