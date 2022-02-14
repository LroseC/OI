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
} read;

const int N = 1e6 + 10;
const int mod = 19930726;

using LL = long long;

LL K, cnt[N];
int n;
int d[N];
char str[N];

int qpow(int base, LL k)
{
	int res = 1;
	while (k) {
		if (k & 1) res = 1ll * res * base % mod;
		k >>= 1;
		base = 1ll * base * base % mod;
	}
	return res;
}

void manacher(void)
{
	int mid = 0, mr = 0;
	for (int i = 1; i <= n; ++i) {
		d[i] = i >= mr ? 1 : min(d[mid * 2 - i], mr - i);
		while (i - d[i] >= 1 && i + d[i] <= n && str[i - d[i]] == str[i + d[i]])
			++d[i];
		if (i + d[i] > mr) {
			mid = i;
			mr = i + d[i];
		}
	}
}

int main(void)
{
	read >> n >> K;
	scanf("%s", str + 1);
	manacher();
	for (int i = 1; i <= n; ++i)
		++cnt[d[i] * 2 - 1];

	int res = 1;
	for (int i = n; i >= 1; --i) {
		LL tmp = min(K, cnt[i]);
		K -= tmp;
		res = 1ll * res * qpow(i, tmp) % mod;
		cnt[i - 2] += cnt[i];
	}
	printf("%d\n", K ? -1 : res);
	return 0;
}
