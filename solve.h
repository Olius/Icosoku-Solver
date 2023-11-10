typedef int num;
typedef struct {
	const num n[3];
	unsigned int q;
} tiledef;
typedef tiledef *tile;
typedef struct {
	num *n[3];
	tile t;
	int r;
} face;

int solve(size_t k, tiledef td[], num n[12], face fs[20]);
