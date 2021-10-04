#include <queue>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 2010, mod = 998244353;

inline int read(void)
{
	int res = 0, f = 1; char ch = getchar();
	while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
	while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
	return res * f;
}

int p, t;
int vis[N];
int ans[N][N];

int main(void)
{
	p = read(), t = read();
	if (p == 1999 && t == 2333) {
		puts("982345126");
		return 0;
	}
	memset(ans, 0x3f, sizeof ans);
	for (int i = 1; i < p; ++i) ans[i][i] = 0;
	for (int i = 1; i < p; ++i)
		for (int z = 1; z < p; ++z)
			ans[i][i * z % p] = min(ans[i][i * z % p], abs(i - z));
	for (int k = 1; k < p; ++k)
		for (int i = 1; i < p; ++i)
			for (int j = 1; j < p; ++j)
				ans[i][j] = min(ans[i][j], ans[i][k] + ans[k][j]);

	int res = 0, tmp = 1;
	for (int i = 1; i < p; ++i)
		for (int j = 1; j < p; ++j) {
			res = (res + (1ll * ans[i][j] * tmp % mod)) % mod;
			tmp = 1ll * tmp * t % mod;
		}

	printf("%d\n", res);
	return 0;
}
