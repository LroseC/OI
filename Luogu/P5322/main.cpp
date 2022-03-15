#include <vector>
#include <cctype>
#include <cstdio>
#include <algorithm>

using namespace std;

inline int read(void)
{
	int res = 0, f = 1; char ch = getchar();
	while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
	while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
	return res * f;
}

typedef long long LL;
typedef pair<int, int> PII;

int s, n, m;
LL f[100010];
vector<int> a[110];
vector<PII> b[110];

int main(void)
{
	s = read(), n = read(), m = read();
	for (int i = 1; i <= n; ++i) {
		a[i].resize(s);
		b[i].resize(s);
	}
	for (int i = 0; i < s; ++i)
		for (int j = 1; j <= n; ++j)
			a[j][i] = read();
	for (int i = 1; i <= n; ++i) sort(a[i].begin(), a[i].end());

	for (int i = 1; i <= n; ++i)
		for (int j = 0; j < s; ++j)
			b[i][j] = PII({2 * a[i][j] + 1, i * (j + 1)});
	
	for (int i = 1; i <= n; ++i)
		for (int j = m; j >= 0; --j)
			for (auto x : b[i]) {
				if (j < x.first) break;
				f[j] = max(f[j], f[j - x.first] + x.second);
			}
	printf("%lld\n", f[m]);
	return 0;
}