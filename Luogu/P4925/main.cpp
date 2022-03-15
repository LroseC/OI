#include <cctype>
#include <cstdio>

using namespace std;

#define int long long
typedef long long LL;

inline LL read(void)
{
	LL res = 0, f = 1; char ch;
	while (!isdigit(ch = getchar())) if (ch == '-') f = -1;
	do res = res * 10 + ch - '0'; while (isdigit(ch = getchar()));
	return res * f;
}

LL k, l;
int p;

inline int qpow(int base, LL k)
{
	int res = 1;
	while (k) {
		if (k & 1) res = 1ll * res * base % p;
		base = 1ll * base * base % p;
		k >>= 1;
	}
	return res;
}

signed main(void)
{
	k = read(), l = read(), p = read();
	LL s = read(), w = read();
	if (l == 1) {
		if (s) puts("1");
		else printf("%lld\n", k);
		return 0;
	}
	LL ans = 1;
	if (s) ans = (k - 1) % p;
	else ans = 1ll * k % p * ((k - 1) % p) % p;
	ans = 1ll * ans * qpow((k - 2) % p, l - 2) % p;
	printf("%d\n", ans);
	return 0;
}