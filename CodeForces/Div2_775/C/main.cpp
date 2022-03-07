#include <vector>
#include <cctype>
#include <cstdio>
#include <cstring>

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

int n, m;
std::vector< std::vector<int> > color;
i64 a[100010], cnt[100010], last[100010];

int main(void)
{
	read >> n >> m;
	color.resize(n);
	for (int i = 0; i < n; ++i) {
		color[i].resize(m);
		for (int j = 0; j < m; ++j)
			read >> color[i][j];
	}
	i64 ans = 0;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			int c = color[i][j];
			a[c] += (i - last[c]) * cnt[c];
			last[c] = i;
			ans += a[color[i][j]];
		}
		for (int j = 0; j < m; ++j)
			++cnt[color[i][j]];
	}
	memset(a, 0, sizeof a);
	memset(cnt, 0, sizeof cnt);
	memset(last, 0, sizeof last);
	for (int j = 0; j < m; ++j) {
		for (int i = 0; i < n; ++i) {
			int c = color[i][j];
			a[c] += (j - last[c]) * cnt[c];
			last[c] = j;
			ans += a[color[i][j]];
		}
		for (int i = 0; i < n; ++i)
			++cnt[color[i][j]];
	}
	printf("%lld\n", ans);
	return 0;
}
