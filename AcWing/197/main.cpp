#include <cstdio>

using namespace std;

#define int long long

int n, idx;
bool vis[(int)1e6 + 10];
int prime[(int)1e6 + 10], ans[(int)1e6 + 10];

int qpow(int, int);

signed main()
{
	scanf("%d", &n);
	for (int i = 2; i <= n; ++i) {
		if (vis[i]) continue;
		prime[++idx] = i;
		for (int j = 1; j * i <= n; ++j) {
			vis[i * j] = 1;
		}
		for (int j = i; j <= n; j = j * i)
			ans[idx] += n / j;
	}

	for (int i = 1; i <= idx; ++i)
		printf("%d %d\n", prime[i], ans[i]);

	return 0;
}
int qpow(int base, int k)
{
	int res = 1;
	while (k) {
		if (k & 1) res *= base;
		k >>= 1;
		base = base * base;
	}
	return res;
}
