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

/*
   f[i][j] 表示第 i 天手持 j 股时最多能赚多少钱
   f[i][j] = f[i - 1][j];
   f[i][j] = Ap[i] * j;
   f[i][j] + Ap[i] * j = f[i - W - 1][j - k] + Ap[i] * (j - k);
   f[i][j] + Bp[i] * j = f[i - W - 1][j + k] + Bp[i] * (j + k);
*/

using i64 = long long;

int T, maxP, W;
i64 f[2010][2010];
int q[2010];

int main(void)
{
	read >> T >> maxP >> W;
	std::memset(f, 0xcf, sizeof f);
	i64 ans = 0xcfcfcfcfcfcfcfcf;
	for (int i = 1; i <= T; ++i) {
		int Ap, Bp, As, Bs;
		read >> Ap >> Bp >> As >> Bs;
		for (int j = 0; j <= maxP; ++j)
			f[i][j] = f[i - 1][j];
		for (int j = 0; j <= As; ++j)
			f[i][j] = std::max(f[i][j], -1ll * Ap * j);

		if (i - W - 1 > 0) {
			int hh = 1, tt = 0;
			for (int j = 0; j <= maxP; ++j) {
				while (hh <= tt && j - q[hh] > As)
					++hh;
				while (hh <= tt && f[i - W - 1][j] + Ap * j >= f[i - W - 1][q[tt]] + Ap * q[tt])
					--tt;
				q[++tt] = j;
				f[i][j] = std::max(f[i][j], f[i - W - 1][q[hh]] + Ap * (q[hh] - j));
			}
			hh = 1, tt = 0;
			for (int j = maxP; j >= 0; --j) {
				while (hh <= tt && q[hh] - j > Bs)
					++hh;
				while (hh <= tt && f[i - W - 1][j] + Bp * j >= f[i - W - 1][q[tt]] + Bp * q[tt])
					--tt;
				q[++tt] = j;
				f[i][j] = std::max(f[i][j], f[i - W - 1][q[hh]] + Bp * (q[hh] - j));
			}
		}
		for (int j = 0; j <= maxP; ++j)
			ans = std::max(ans, f[i][j]);
	}
	printf("%lld\n", ans);
	return 0;
}
