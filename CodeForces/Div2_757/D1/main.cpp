#include <vector>
#include <climits>
#include <iostream>
#include <algorithm>

#define read std::cin
using i64 = long long;
using vint = std::vector<int>;
using PII = std::pair<int, int>;
const int N = 5e6 + 10;

int prime[N], v[N], idx;

void getPrime(void)
{
	for (int i = 2; i < N; ++i) {
		if (!v[i]) {
			v[i] = i;
			prime[++idx] = i;
		}
		for (int j = 1; j <= idx && i * prime[j] < N; ++j) {
			v[i * prime[j]] = prime[j];
			if (v[i] == prime[j]) break;
		}
	}
}

int n;
int val[N];
int cnt[N];
i64 f[N];

template<typename T>
void maxx(T &a, T b)
{ a = std::max(a, b); }
int main(void)
{
	//Think twice, code once.
	std::ios::sync_with_stdio(false);
	getPrime();
	read >> n;
	int maxv = 0;
	for (int i = 1; i <= n; ++i) {
		read >> val[i];
		maxv = std::max(maxv, val[i]);
		for (int j = 1; j * j <= val[i]; ++j)
			if (val[i] % j == 0) {
				++cnt[j];
				if (j * j != val[i]) ++cnt[val[i] / j];
			}
	}
	for (int i = maxv; i >= 1; --i) {
		f[i] = 1ll * i * cnt[i];
	}
	for (int i = maxv; i >= 1; --i) {
		for (int t = i; t != 1; t /= v[t]) {
			maxx(f[i / v[t]], f[i] + 1ll * (i / v[t]) * (cnt[i / v[t]] - cnt[i]));
		}
	}
	i64 res = 0;
	for (int i = 1; i <= maxv; ++i)
		if (cnt[i] == n) maxx(res, f[i]);
	printf("%lld\n", res);
	return 0;
}
