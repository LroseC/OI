#include <cctype>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int mod = 1e9 + 7;
inline int sq(int x) { return x * x; }

inline int read(void)
{
	int res = 0, f = 1; char ch = getchar();
	while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
	while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
	return res * f;
}

int n, X, Y, D;
int C[510][510];
bool vis[510][510];

int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }

inline int Init(void)
{
	memset(vis, 0, sizeof vis);
	return 0;
}
inline int Work(void)
{
	n = read(), X = read(), Y = read(), D = read();
	int ans = 0;
	for (int dx = 0; dx <= X; ++dx)
		for (int dy = 0; dy <= Y; ++dy)
			if (gcd(dx, dy) == 1) {
				int d = gcd(dx, dy);
				int tx = dx / d, ty = dy / d;
				if (vis[tx][ty]) continue;
				vis[tx][ty] = 1;
				int pointcnt;
				if (dx != 0 && dy != 0)
					pointcnt = min(X / dx, Y / dy) + 1;
				else if (dx != 0) 
					pointcnt = X / dx + 1;
				else if (dy != 0)
					pointcnt = Y / dy + 1;
				else continue;
				if (pointcnt < n) continue;
				for (int i = n; i <= pointcnt; ++i) {
					ans = (1ll * ans + (((dx && dy) ? 2ll : 1ll) * C[pointcnt - 1][n - 2] * (X - dx * (i - 1) + 1) % mod * (Y - dy * (i - 1) + 1) % mod)) % mod;
				}
			}
	printf("%d\n", ans);
	return 0;
}

int main(void)
{
	C[0][0] = 1;
	for (int i = 1; i <= 500; ++i)
		for (int j = 0; j <= 500; ++j) {
			C[i][j] = j ? C[i - 1][j - 1] + C[i - 1][j] : 1;
		}

	int T = read();
	while (T--) {
		Init();
		Work();
	}
	return 0;
}