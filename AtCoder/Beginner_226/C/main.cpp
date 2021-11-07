#include <vector>
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

const int N = 2e5 + 10;

int n;
int w[N];
bool vis[N];
vector<int> G[N];

LL dfs(int u, int fa)
{
	LL res = 0;
	vis[u] = 1;
	for (int v : G[u]) {
		if (v == fa || vis[v]) continue;
		res += dfs(v, u);
	}
	return res + w[u];
}

int main(void)
{
	io >> n;
	for (int u = 1; u <= n; ++u) {
		io >> w[u];
		int x; io >> x;
		for (int j = 0; j < x; ++j) {
			int v; io >> v;
			G[u].emplace_back(v);
		}
	}
	io << dfs(n, n) << endl;
	// CHECK YOUR ARRAY TO MAKE SRUE YOUR CODE WON'T RE
	return 0;
}