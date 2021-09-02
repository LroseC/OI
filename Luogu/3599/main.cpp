#include <cstring>
#include <assert.h>
#include <iostream>
#include <iostream>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 1e5 + 10;

typedef long long LL;

int len;
int X, T;
bool vis[N];
int pcnt, prime[N], v[N];

void getprime(void)
{
	for (int i = 2; i < N; ++i) {
		if (!v[i]) {
			v[i] = i;
			prime[++pcnt] = i;
		}
		for (int j = 1; j <= pcnt; ++j) {
			if (prime[j] > v[i] || i * prime[j] >= N) break;
			v[i * prime[j]] = prime[j];
		}
	}
}

int qpow(int base, int k)
{
	int res = 1;
	while (k) {
		if (k & 1) res = 1ll * res * base % len;
		k >>= 1;
		base = 1ll * base * base % len;
	}
	return res;
}

void Solve1(void)
{
	cin >> len;
	if (len & 1 && len != 1) {
		cout << 0 << '\n';
		return;
	}
	else cout << 2 << ' ';
	if (len == 1) cout << 1 << '\n';
	else {
		for (int i = 1; i <= len; ++i) {
			if (i & 1) cout << (len - i + 1) << ' ';
			else cout << i - 1 << ' ';
		}
		cout << '\n';
	}
}
void Solve2(void)
{
	cin >> len;
	if (v[len] != len && len != 4 && len != 1) {
		cout << "0" << '\n';
		return;
	}
	else cout << 2 << ' ';
	if (len == 1) cout << "1" << '\n';
	else if (len == 4) cout << "1 3 2 4" << '\n';
	else {
		for (int i = 1, tmp = 1, mul = 1; i < len; ++i) {
			cout << tmp << ' ';
			tmp = 1ll * (i + 1) * qpow(i, len - 2) % len;
		}
		cout << len << '\n';
		return;
	}
}

int main(void)
{
	ios::sync_with_stdio(0);
	cin >> X >> T;
	if (X == 2) getprime();
	while (T--) {
		if (X & 1) Solve1();
		else Solve2();
	}
	return 0;
}