#include <cctype>
#include <cstdio>
#include <cstdint>

struct FSI
{
	template<typename T>
	FSI& operator>>(T &res)
	{
		res = 0; T f = 1; char ch = getchar();
		while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
		while (isdigit(ch)) { res = res * 10 + (ch - '0') * f; ch = getchar(); }
		return *this;
	}
} read;
struct FSO
{
	template<typename T>
	FSO& operator<<(const T &res)
	{
		static char buf[1024]; int p = -1; T x = res;
		if (x == 0) putchar('0');
		if (x < 0) { putchar('-'); x = -x; }
		while (x) { buf[++p] = x % 10; x /= 10; }
		while (~p) { putchar(buf[p] + '0'); --p; }
		return *this;
	}
	FSO& operator<<(const char ch) { putchar(ch); return *this; }
} write;

using i32 = int32_t;
using i64 = int64_t;
using i128 = __int128;
const int mod = 998244353, B = 1e6;

i32 x[5][B];

i32 bpow(i128 y)
{
	i32 res = 1;
	for (int i = 0; i < 4; ++i) {
		i32 yy = y % B; y /= B;
		res = 1ll * res * x[i][yy];
	}
	return res;
}

int main(void)
{
	//Think twice, code once.
	i32 n, m;
	i128 y;
	read >> n;
	for (int i = 1; i <= n; ++i) {
		read >> x[0][1] >> m;
		for (int j = 0; j < 4; ++j) {
			x[j][0] = 1;
			for (int k = 1; k < B - 1; ++k)
				x[j][k + 1] = 1ll * x[j][k] * x[j][1] % mod;
			x[j + 1][1] = 1ll * x[j][B - 1] * x[j][1] % mod;
		}
		for (int j = 1; j <= m; ++j) {
			read >> y;
			write << bpow(y) << '\n';
		}
	}
	return 0;
}
