#include <cctype>
#include <cstdio>
#include <algorithm>

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
} IO;

const int N = 2e5 + 10, M = 2e5 + 10, Q = 2e5 + 10;

struct Edge
{
	int id, u, v, w;
	bool operator<(const Edge &other) const
	{
		return w < other.w;
	}
};

int n, m, q;
int idx;
int fa[N];
int ans[Q];
Edge edge[M + Q];

int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }

int main(void)
{
	// CHECK YOUR ARRAY TO MAKE SRUE YOUR CODE WON'T RE
	IO >> n >> m >> q;
	for (int i = 1; i <= n; ++i)
		fa[i] = i;
	for (int i = 1; i <= m; ++i) {
		int u, v, w;
		IO >> u >> v >> w;
		edge[++idx] = {0, u, v, w};
	}
	for (int i = 1; i <= q; ++i) {
		int u, v, w;
		IO >> u >> v >> w;
		edge[++idx] = {i, u, v, w};
	}
	sort(edge + 1, edge + 1 + idx);
	for (int i = 1; i <= idx; ++i) {
		int u = edge[i].u, v = edge[i].v;
		if (edge[i].id) {
			u = find(u), v = find(v);
			ans[edge[i].id] = u != v;
		}
		else {
			u = find(u), v = find(v);
			if (u != v)
				fa[u] = v;
		}
	}
	for (int i = 1; i <= q; ++i)
		puts(ans[i] ? "Yes" : "No");
	return 0;
}
