#include <queue>
#include <vector>
#include <cstring>
#include <iostream>

using namespace std;

const int N = 1e5;

template<typename Int> inline void read(Int &x)
{
	x = 0; char ch = getchar();
	while (!isdigit(ch)) ch = getchar();
	while (isdigit(ch)) {
		x = x * 10 + (ch ^ '0');
		ch = getchar();
	}
}
template<typename Int> inline void writet(Int x)
{
	static char buf[20]; int p = -1;
	if (!x) putchar('0');
	if (x < 0) { putchar('-'); x = -x; }
	while (x) { buf[++p] = x % 10 ^ '0'; x /= 10; }
	while (p >= 0) { putchar(buf[p]); --p; }
}

struct Edge
{
	int v, w;
};

int n, m, k, p;
vector<Edge> oriG[N], invG[N];
int d[N];
int f[N][60];
bool inque[N];
bool instk[N];
queue<int> q;

inline void SPFA()
{
	#define G oriG
	while(q.size()) q.pop();
	memset(d, 0x3f, sizeof d);
	memset(inque, 0, sizeof inque);
	d[1] = 0;
	q.push(1);
	while (q.size()) {
		int u = q.front(); q.pop();
		inque[u] = 0;
		for (auto e : G[u]) {
			int v = e.v, w = e.w;
			if (d[u] + w < d[v]) {
				d[v] = d[u] + w;
				if (!inque[v]) q.push(v);
				inque[v] = 1;
			}
		}
	}
	#undef G
}

int dp(int u, int len)
{
	#define G invG
	if (len < 0 || len > k) return 0;
	if (~f[u][len]) return f[u][len];
	if (instk[u]) {
		instk[u] = 0;
		return -1;
	}
	instk[u] = 1;
	for (auto t : invG[u]) {
		int v = t.v;
		int tmp = dp(v, d[u] + len - d[v] - t.w);
		if (tmp == -1) {
			instk[u] = 0;
			return -1;
		}
		f[u][len] = (f[u][len] + tmp) % p;
	}
	instk[u] = 0;
	if (u == 1 && len == 0) ++f[u][len];
	++f[u][len];
	return f[u][len];
	#undef G
}

int Work(void)
{
	memset(f, -1, sizeof f);
	memset(inque, 0, sizeof inque);
	memset(instk, 0, sizeof instk);
	read(n), read(m), read(k), read(p);
	for (int i = 1; i <= n; ++i) {
		oriG[i].clear();
		invG[i].clear();
	}
	for (int i = 0; i < m; ++i) {
		int u, v, w; read(u), read(v), read(w);
		oriG[u].emplace_back(Edge({v, w}));
		invG[v].emplace_back(Edge({u, w}));
	}
	SPFA();
	int ans = 0;
	for (int i = 0; i <= k; ++i) {
		int tmp = dp(n, i);
		if (tmp == -1) {
			ans = -1;
			break;
		}
		else ans = (ans + tmp) % p;
	}
	writet(ans); putchar('\n');
	return 0;
}

int main(void)
{
	int T;
	read(T);
	while (T--) Work();
	return 0;
}