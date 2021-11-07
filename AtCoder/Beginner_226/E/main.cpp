#include <cctype>
#include <cstdio>

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

const int N = 2e5 + 10, mod = 998244353;

int n, m;
bool vis[N];
int fa[N], sz[N], esz[N];

int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }

int main(void)
{
	io >> n >> m;
	for (int i = 1; i <= n; ++i) {
		fa[i] = i;
		sz[i] = 1;
	}
	for (int i = 1; i <= m; ++i) {
		int u, v; io >> u >> v;
		u = find(u), v = find(v);
		if (u != v) {
			fa[u] = v;
			sz[v] += sz[u];
			esz[v] += esz[u] + 1;
		}
		else ++esz[u];
	}
	int ans = 1;
	for (int i = 1; i <= n; ++i) {
		int u = find(i);
		if (!vis[u]) {
			vis[u] = 1;
			if (esz[u] != sz[u]) {
				puts("0");
				return 0;
			}
			ans = 2ll * ans % mod;
		}
	}
	io << ans << endl;
	// CHECK YOUR ARRAY TO MAKE SRUE YOUR CODE WON'T RE
	return 0;
}