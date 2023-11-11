typedef int num;
typedef struct {
	const num n[3];
	unsigned int q;
} tiledef;
typedef tiledef *tile;
typedef struct vertex vertex;
typedef struct face face;
struct vertex {
	face *fs[5];
	num n;
};
struct face {
	vertex *vs[3];
	tile t;
	int r;
};

int solve(size_t k, tiledef td[], vertex vs[12], face fs[20]);
