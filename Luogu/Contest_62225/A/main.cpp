#include <cctype>
#include <cstdio>
#include <cstring>

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

using LL = long long;
const int N = 1e5 + 10, mod = 998244353;

int n;
LL ans = 1;

struct LinearBasis
{
	int sz;
	int base[32];

	LinearBasis(void)
	{
		sz = 0;
		memset(base, 0, sizeof base);
	}
	void insert(int x)
	{
		for (int i = 31; i >= 0; --i)
			if (x >> i & 1) {
				if (!base[i]) {
					++sz;
					base[i] = x;
					break;
				}
				else
					x ^= base[i];
			}
	}
} Base;

int main(void)
{
	read >> n;
	for (int i = 1; i <= n; ++i) {
		ans = ans * ((1ll << Base.sz) % mod) % mod;

		int x; read >> x;
		Base.insert(x);
	}
	printf("%lld\n", ans);
	return 0;
}
