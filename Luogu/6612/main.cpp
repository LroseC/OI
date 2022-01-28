#include <cstdio>

using namespace std;

int f[15][10][30010];

extern "C" int _opt(int n, int x, int y)
{
	if (x + y >= n) return 0;
	int cnt2 = 0, cnt3 = 0;
	int tx = x;
	while (!(tx & 1)) {
		++cnt2;
		tx >>= 1;
	}
	while (tx != 1) {
		++cnt3;
		tx /= 3;
	}
	if (f[cnt2][cnt3][y])
		return f[cnt2][cnt3][y] == -1 ? 0 : f[cnt2][cnt3][y];
	if (!_opt(n, 1, x + y))
		return f[cnt2][cnt3][y] = 1;
	if (!_opt(n, x * 2, y))
		return f[cnt2][cnt3][y] = 2;
	if (!_opt(n, x * 3, y))
		return f[cnt2][cnt3][y] = 3;
	f[cnt2][cnt3][y] = -1;
	return 0;
}
