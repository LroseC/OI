#include <cctype>
#include <cstdio>
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
const int N = 13, M = 510;

int n, m;
int a[N];
i64 f[1 << N][N][M];

int main(void)
{
	read >> n >> m;
	std::pair<int, int> maxn = std::make_pair(0, 0);
	for (int i = 0; i < n; ++i) {
		read >> a[i];
		if (a[i] > maxn.first) {
			maxn.first = a[i];
			maxn.second = i;
		}
	}
	for (int i = 0; i < n; ++i) {
		int t = maxn.first - a[i] + (i > maxn.second);
		t *= n;
		if (t <= m)
			f[1 << i][i][t] = 1;
	}
	for (int state = 1; state < 1 << n; ++state)
		for (int i = 0; i < n; ++i)
			if (state >> i & 1)
				for (int j = 0; j <= m; ++j)
					if (f[state][i][j]) {
						for (int k = 0; k < n; ++k)
							if ((state >> k & 1) == 0) {
								int tostate = state | (1 << k);
								int toj = j;
								toj += std::max(0, a[i] - a[k] + (k > i)) * (n - __builtin_popcount(state));
								if (toj <= m)
									f[tostate][k][toj] += f[state][i][j];
							}
					}
	i64 res = 0;
	for (int i = 0; i < n; ++i)
		for (int j = 0; j <= m; ++j)
			res += f[(1 << n) - 1][i][j];
	printf("%lld\n", res);
	return 0;
}
