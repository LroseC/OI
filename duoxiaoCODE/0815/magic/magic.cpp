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
		while (isdigit(ch)) { res = res * 10 + (ch - '0') * f; ch = getchar(); }
		return *this;
	}
} read;

using i32 = int;
using i64 = long long;
using PII = std::pair<i32, i32>;
const int N = 310;

i32 n, m;
char str[N], s[N];
i32 dif[N], gdif[N], f[N], g[N];

i32 dp(i32 state)
{
	for (int i = 0; i < n; ++i) {
		dif[i] = (i == 0 ? 0 : dif[i - 1]) + (str[i] != (state >> (i % m) & 1));
		gdif[i] = (i == 0 ? 0 : gdif[i - 1]) + (str[i] == (state >> (i % m) & 1));
	}
	std::fill(f, f + n, 0x3f3f3f3f);
	std::fill(g, g + n, 0x3f3f3f3f);
	f[n] = 0;
	g[n] = 0;
	for (int i = n - 1; i >= 0; --i)
		if (i % m == 0) {
			for (int j = i + m; ; j += m) {
				if (j > n) j = n;
				f[i] = std::min(f[i], f[j] + dif[j - 1] - (i == 0 ? 0 : dif[i - 1]));
				g[i] = std::min(g[i], g[j] + gdif[j - 1] - (i == 0 ? 0 : gdif[i - 1]));

				f[i] = std::min(f[i], 1 + g[j] + gdif[j - 1] - (i == 0 ? 0 : gdif[i - 1]));
				g[i] = std::min(g[i], 1 + f[j] + dif[j - 1] - (i == 0 ? 0 : dif[i - 1]));
				if (j == n) break;
			}
		}
	return f[0];
}

int main(void)
{
#ifndef DEBUG
	freopen("magic.in", "r", stdin);
	freopen("magic.out", "w", stdout);
#endif
	//Think twice, code once.
	read >> n >> m;
	scanf("%s", str);
	for (int i = 0; i < n; ++i) str[i] -= '0';
	if (m < 18) {
		i32 ans = 0x3f3f3f3f;
		for (int i = 0; i < 1 << m; ++i) {
			ans = std::min(ans, dp(i));
		}
		printf("%d\n", ans);
	}
	else {
		i32 ans = 0x3f3f3f3f;
		i32 bCnt = (n - 1) / m + 1;
		for (int i = 0; i < 1 << bCnt; ++i) {
			i32 res = 0;
			for (int j = 0; j < n; ++j) s[j] = 0;
			for (int j = 0; j < bCnt; ++j)
				if (i >> j & 1) {
					res += 1;
					s[std::min(n, (j + 1) * m) - 1] ^= 1;
				}
			for (int j = n - 1; j >= 0; --j) {
				s[j] ^= (j == n - 1 ? 0 : s[j + 1]);
			}
			for (int j = 0; j < n; ++j) {
				s[j] ^= str[j];
			}
			for (int k = 0; k < m; ++k) {
				static i32 cnt[2];
				cnt[0] = cnt[1] = 0;
				for (int j = k; j < n; j += m) {
					cnt[s[j]] += 1;
				}
				res += std::min(cnt[0], cnt[1]);
			}
			ans = std::min(ans, res);
		}
		printf("%d\n", ans);
	}
	return 0;
}
/*
   听说南外的题很难, 我很慌, 但是貌似会 T1 了.
   好像没有非常难? 应该和 UNR T1 差不多.
   差点没想出来, 好在数据点范围的等号救了我一命.
   又卡常?????
   我不想活辣!!!!!!
*/
