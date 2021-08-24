#include <cstdio>
#include <algorithm>

using namespace std;

const int N = 10010;

typedef long long LL;

int n, m;
LL a[N];

int main(void)
{
	int T;
	scanf("%d", &T);
	for (int C = 1; C <= T; ++C) {
		printf("Case #%d:\n", C);
		scanf("%d", &n);
		for (int i = 0; i < n; ++i) scanf("%lld", &a[i]);
		int r, c;
		for (r = 0, c = 62; c >= 0; --c) {
			for (int i = r; i < n; ++i)
				if ((a[i] >> c) & 1) {
					swap(a[i], a[r]);
					break;
				}
			if (!((a[r] >> c) & 1)) continue;
			for (int i = 0; i < n; ++i)
				if (i != r && ((a[i] >> c) & 1))
					a[i] ^= a[r];
			if (++r == n) break;
		}
		reverse(a, a + r);

		scanf("%d", &m);
		while (m--) {
			LL x; scanf("%lld", &x);
			LL res = 0;
			if (r < n) --x;
			if (x >= (1ll << r)) {
				puts("-1");
				continue;
			}
			for (int i = 0; x >> i; ++i) {
				if ((x >> i) & 1)
					res ^= a[i];
			}
			printf("%lld\n", res);
		}
	}
	return 0;
}