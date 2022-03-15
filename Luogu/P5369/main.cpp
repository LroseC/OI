#include <cstdio>
#include <iostream>

using namespace std;

using LL = long long;
const int N = 20, S = 1 << 20, mod = 998244353;

int n, ans;
int a[N];
int f[S][2], g[S], sum[S];

void init(void)
{
	//init sum 
	for (int i = 0; i < 1 << n; ++i)
		for (int k = 0; k < n; ++k) {
			if (i >> k & 1)
				sum[i] += a[k];
		}
	//init g 
	g[0] = 1;
	for (int i = 0; i < 1 << n; ++i)
		for (int k = 0; k < n; ++k) {
			if (i >> k & 1 && sum[i] < 0)
				g[i] = (g[i] + g[i ^ (1 << k)]) % mod;
		}
	//init f 
	for (int i = 0; i < n; ++i) {
		if (a[i] >= 0)
			f[1 << i][0] = 1;
		f[1 << i][1] = 1;
	}
	for (int i = 1; i < 1 << n; ++i)
		for (int k = 0; k < n; ++k) {
			if (i >> k & 1 && sum[i] >= 0)
				f[i][0] = (f[i][0] + f[i ^ (1 << k)][0]) % mod;
			f[i][1] = (f[i][1] + f[i ^ (1 << k)][0]) % mod;
		}
}

int main(void)
{
	ios::sync_with_stdio(0);
	cin >> n;
	for (int i = 0; i < n; ++i)
		cin >> a[i];
	init();
	for (int state = 1; state < 1 << n; ++state) {
		int rest = (1 << n) - 1 ^ state;
		ans = (ans + (0ll + f[state][1]) * sum[state] % mod * g[rest] % mod) % mod;
	}
	printf("%d\n", (ans + mod) % mod);
	return 0;
}
