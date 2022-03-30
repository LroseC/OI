#include <cctype>
#include <cstdio>
#include <cstring>
#include <algorithm>

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
} read;

using i64 = long long;
const int N = 3e5 + 10;

struct fireNode
{
	int pos, hap, t;
};

int n, m, d;
i64 f[2][N];
int q[N];
fireNode fire[N];

int main(void)
{
	read >> n >> m >> d;
	fire[0].t = 1;
	for (int i = 1; i <= m; ++i)
		read >> fire[i].pos >> fire[i].hap >> fire[i].t;

	f[0][1] = 0;
	for (int i = 1; i <= m; ++i) {
		int deltaTime = fire[i].t - fire[i - 1].t;
		int hh = 1, tt = 0;
		for (int j = 1; j < 1ll * deltaTime * d; ++j) {
			if (j > n) break;
			while (hh <= tt && f[(i & 1) ^ 1][q[tt]] <= f[(i & 1) ^ 1][j])
				--tt;
			q[++tt] = j;
		}
		for (int j = 1; j <= n; ++j) {
			if (j + 1ll * deltaTime * d <= n) {
				while (hh <= tt && f[(i & 1) ^ 1][q[tt]] <= f[(i & 1) ^ 1][j + deltaTime * d])
					--tt;
				q[++tt] = j + deltaTime * d;
			}
			while (hh <= tt && j - q[hh] > 1ll * deltaTime * d)
				++hh;
			f[i & 1][j] = f[(i & 1) ^ 1][q[hh]] + fire[i].hap - std::abs(fire[i].pos - j);
		}
	}
	i64 ans = 0xcfcfcfcfcfcfcfcf;
	for (int i = 1; i <= n; ++i)
		ans = std::max(ans, f[m & 1][i]);
	printf("%lld\n", ans);
	return 0;
}
