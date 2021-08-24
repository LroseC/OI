#include <iostream>

using namespace std;

typedef long long LL;

int n, m;

int gcd(int a, int b)
{
	return b ? gcd(b, a % b) : a;
}
int qpow(LL base, int k)
{
	LL res = 1;
	while (k) {
		if (k & 1) res = res * base;
		k >>= 1;
		base = base * base;
	}
	return res;
}

int main(void)
{
	while (cin >> m >> n, m || n) {
		LL res = 0;
		for (int i = 0; i < n; ++i) {
			int d = gcd(i, n);
			res += qpow(m, d);
		}
		if (n & 1) res += n * qpow(m, n + 1 >> 1);
		else {
			res += n / 2 * (qpow(m, n / 2 + 1) + qpow(m, n / 2));
		}
		cout << res / n / 2 << endl;
	}
	return 0;
}