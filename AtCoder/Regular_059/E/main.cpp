#include <vector>
#include <cctype>
#include <cstdio>
#include <cstring>

using namespace std;
using LL = long long;
const char endl = '\n';

struct FastStreamInputOutput
{
	using FSIO = FastStreamInputOutput;
	template<typename T>
	FSIO& operator>>(T &res)
	{
		res = 0; T f = 1; char ch = getchar();
		while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
		while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
		res *= f; return *this;
	}
	FSIO& operator<<(char x)
	{
		putchar(x);
		return *this;
	}
	FSIO& operator<<(const char x[])
	{
		for (int i = 0; x[i]; ++i) putchar(x[i]);
		return *this;
	}
	template<typename T>
	FSIO& operator<<(const T &res)
	{
		static char buf[50]; int p = -1; T x = res;
		if (x == 0) putchar('0');
		if (x < 0) { putchar('-'); x = -x; }
		while (x) { buf[++p] = x % 10; x /= 10; }
		while (~p) { putchar(buf[p] + '0'); --p; }
		return *this;
	}
} io;

const int N = 410;
const int mod = 1e9 + 7;

int n, c;
vector<int> a, b;

namespace pts400
{
	int pw[N][N];
	int memery[N][N];
	bool check(void)
	{
		for (int i = 0; i < n; ++i)
			if (a[i] != b[i]) return 0;
		return 1;
	}
	/*
	x -> n;
	y -> c;
	*/
	int dp(int x, int y)
	{
		if (~memery[x][y]) return memery[x][y];
		if (x + 1 == n) return memery[x][y] = pw[x][y];
		memery[x][y] = 0;
		for (int ty = 0; ty <= y; ++ty) {
			memery[x][y] = (memery[x][y] + 1ll * pw[x][y - ty] * dp(x + 1, ty) % mod) % mod;
		}
		return memery[x][y];
	}
	int main(void)
	{
		for (int i = 0; i < n; ++i)
			for (int t = a[i]; t <= b[i]; ++t) {
				int tmp = 1;
				for (int j = 0; j <= c; ++j) {
					pw[i][j] = (pw[i][j] + tmp) % mod;
					tmp = 1ll * tmp * t % mod;
				}
			}
		memset(memery, -1, sizeof memery);
		int ans = dp(0, c);
		return ans;
	}
}
namespace pts800
{
	int main(void)
	{
		return 0;
	}
}

int main(void)
{
	io >> n >> c;
	a.resize(n); b.resize(n);
	for (int i = 0; i < n; ++i) io >> a[i];
	for (int i = 0; i < n; ++i) io >> b[i];
	printf("%d\n", pts400::main());
	return 0;
}