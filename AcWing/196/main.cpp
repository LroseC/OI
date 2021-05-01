#include <cstdio>
#include <climits>
#include <cstring>

using namespace std;

#define reg register
#define ll long long
#define int long long
const int N = 1e5 + 10, M = 1e6 + 10;

int l, r;

bool vis[M];
int pr[N], idx, v[N];
int bigprime[M], cnt;

inline int max(int a, int b)
{
	return a > b ? a : b;
}
void get_prime(int);

signed main()
{
	get_prime(50000);
	while(~scanf("%lld%lld", &l, &r)) {
		memset(vis, 0, sizeof vis);
		cnt = 0;
		for (int i = 1; i <= idx; ++i) {
			int p = pr[i];
			for (int j = (l + p - 1) / p * p; j <= r; j += p) {
				if (j == p) continue;
//				printf("%lld\n", j);
				vis[j - l] = 1;
			}
		}

		for (int i = max(l, 2); i <= r; ++i)
			if (!vis[i - l]) bigprime[++cnt] = i;

		if (cnt < 2) puts("There are no adjacent primes.");
		else {
			int minn = INT_MAX, maxn = INT_MIN;
			int minx, maxx;
			for (int i = 1; i < cnt; ++i) {
				int tmp = bigprime[i + 1] - bigprime[i];
				if (tmp > maxn) {
					maxn = tmp;
					maxx = i;
				}
				if (tmp < minn) {
					minn = tmp;
					minx = i;
				}
			}

			printf("%lld,%lld are closest, %lld,%lld are most distant.\n", bigprime[minx], bigprime[minx + 1], bigprime[maxx], bigprime[maxx + 1]);
		}
	}

	return 0;
}
void get_prime(int a)
{
	for (int i = 2; i <= a; ++i) {
		if (!v[i]) v[i] = i, pr[++idx] = i;
		for (int j = 1; j <= idx; ++j) {
			if (pr[j] * i > a || pr[j] > v[i]) break;
			v[pr[j] * i] = pr[j];
		}
	}
	return;
}
