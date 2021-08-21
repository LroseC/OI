#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <unordered_map>

#define int long long

using namespace std;

int qpow(int base, int k, int p)
{
	int res = 1;
	while (k) {
		if (k & 1) res = 1ll * res * base % p;
		base = 1ll * base * base % p;
		k >>= 1;
	}
	return res;
}
int inv(int a, int p)
{
	return qpow(a, p - 2, p);
}
int exgcd(int a, int b, int &x, int &y)
{
	if (!b) {
		x = 1, y = 0;
		return a;
	}
	int d = exgcd(b, a % b, y, x);
	y -= a / b * x;
	return d;
}
int bsgs(int a, int b, int p)
{
	if (1 % p == b % p) return 0;
	int k = sqrt(p) + 1;
	unordered_map<int, int> hash;
	for (int i = 0, j = b % p; i < k; ++i, j = 1ll * j * a % p)
		hash[j] = i;
	int ak = 1;
	for (int i = 0; i < k; ++i) ak = 1ll * ak * a % p;
	for (int i = 1, j = ak; i <= k; ++i, j = 1ll * j * ak % p) {
		if (hash.count(j)) return i * k - hash[j];
	}
	return -2;
}

int T;

signed main(void)
{
	scanf("%lld", &T);
	while (T--) {
		int p, a, b, x1, t;
		scanf("%lld%lld%lld%lld%lld", &p, &a, &b, &x1, &t);
		if (a == 0) {
			if (x1 == t) puts("1");
			else if (b == t) puts("2");
			else puts("-1");
		}
		else if (a == 1) {
			if (b == 0) puts(x1 == t ? "1" : "-1");
			else {
				int x, y;
				exgcd(b, p, x, y);
				x = (1ll * x * (t - x1)) % p;
				x = (x + p) % p;
				printf("%lld\n", x + 1);
			}
		}
		else {
			int c = 1ll * b * inv(a - 1, p) % p;
			if ((x1 + c) % p == 0) {
				int u = (-c + p) % p;
				puts(u == t ? "1" : "-1");
			}
			else {
				int tmp = 1ll * (t + c) * inv(x1 + c, p) % p;
				printf("%lld\n", bsgs(a, tmp, p) + 1);
			}
		}
	}
	return 0;
}
