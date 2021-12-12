#include <cctype>
#include <cstdio>
#include <algorithm>

using namespace std;

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
} io;

const int N = 2e5 + 10;

int n, C;
int a[N];

int main(void)
{
	io >> n >> C;
	C = abs(C);
	for (int i = 1; i <= n; ++i) io >> a[i];
	sort(a + 1, a + 1 + n);
	long long ans = 0;
	int i = 1, j = 1;
	while (i <= n) {
		int cnt1 = 0, cnt2 = 0;
		while (a[i] - a[j] > C) ++j;
		while (j <= n && a[i] - a[j] == C) {
			++j;
			++cnt1;
		}
		while (i < n && a[i + 1] == a[i]) {
			++i;
			++cnt2;
		}
		++i, ++cnt2;
		ans += 1ll * cnt1 * cnt2;
	}
	printf("%lld\n", ans);
	return 0;
}