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

const int N = 1e5 + 10;

int n, K;
int res;
int to[N];
bool vis[N];
int dis[N];
vector<int> G[N];

int dfs(int u, int fa)
{
	int dep = 0;
	for (int v : G[u]) {
		if (v == fa) continue;
		dep = max(dep, dfs(v, u));
	}
	if (dep == K - 1 && u != 1 && to[u] != 1) {
		++res;
		dep = -1;
	}
	return dep + 1;
}

int main(void)
{
	// CHECK YOUR ARRAY TO MAKE SRUE YOUR CODE WON'T RE
	io >> n >> K;
	for (int i = 1; i <= n; ++i) {
		io >> to[i];
		if (i != 1)
			G[to[i]].emplace_back(i);
	}
	res = to[1] != 1;
	dfs(1, 1);
	io << res << endl;
	return 0;
}