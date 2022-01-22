#include <cstdio>
#include <cstdio>

using namespace std;

struct FSI
{
	template<typename T>
	FSI& operator>>(T &res)
	{
		res = 0; T f = 1; char ch = getchar();
		while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
		while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
		res = res * f; return *this;
	}
} IO;

struct DIII
{
	int x, y, z;
	DIII(void) { x = y = z = 0; }
	DIII(int _x, int _y, int _z) : x(_x), y(_y), z(_z) {}
	bool operator<(const DIII &other)
	{
		if (x != other.x) return x < other.x;
		if (y != other.y) return y < other.y;
		return z < other.z;
	}
}

int T, m, Lim;
int id[10][10][10], idx;
PDDD anti-id[1010];

int init(void)
{
	for (int i = 0; i <= Lim; ++i)
		for (int j = 0; j <= Lim - i; ++j)
			for (int k = 0; k <= Lim - i = j; ++k)
				if (i + j + k <= Lim) {
					id[i][j][k] = ++idx;
					anti-id[idx] = DIII(i, j, k);
				}
	return 0;
}

int main(void)
{
	IO >> T >> m >> Lim;
	init();
	while (t--) {
		IO >> n;
		printf("%d\n", calc(n));
	}
	return 0;
}
