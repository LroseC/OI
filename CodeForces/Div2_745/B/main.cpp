#include <cstdio>

using namespace std;

#define int long long

signed main(void)
{
	int T; scanf("%lld", &T);
	while (T--) {
		int n, m, k; scanf("%lld%lld%lld", &n, &m, &k);
		int d;
		if (m > 1ll * n * (n - 1) / 2) d = 0x3f3f3f3f3f3f;
		else if (n == 1) d = 0;
		else if (m == 1ll * n * (n - 1) / 2) d = 1;
		else if (m >= n - 1) d = 2;
		else d = 0x3f3f3f3f3f3f3f;
		/*
		if (k <= 1) puts("NO");
		else if (k == 2) {
			if (n == 1) puts("YES");
			else puts("NO");
		}
		else if (k == 3) {
			if (m >= 1ll * n * (n - 1) / 2) puts("YES");
			else puts("NO");
		}
		else if (k > 3) {
			if (m >= n - 1) puts("YES");
			else puts("NO");
		}
		*/
		if (d < k - 1) puts("YES");
		else puts("NO");
	}
	return 0;
}