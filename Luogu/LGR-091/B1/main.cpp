#include <cctype>
#include <cstdio>
#include <algorithm>
#include <functional>

using namespace std;

const int N = 10010;
typedef long long LL;

inline int read(void)
{
	int res = 0, f = 1; char ch = getchar();
	while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
	while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
	return res * f;
}

int n, m;
int a[N];

int main(void)
{
	int t = read();
	int T = read();
	while (T--) {
		n = read(), m = read();
		for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
		sort(a + 3, a + 1 + n, greater<int>());
		LL ans = 0;
		for (int i = 1; i <= m; ++i) ans += a[i];
		printf("%lld\n", ans);
	}
	return 0;
}