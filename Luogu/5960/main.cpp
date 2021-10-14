#include <queue>
#include <vector>
#include <cctype>
#include <cstdio>
#include <cstring>

using namespace std;

const int N = 5e3 + 10;

template<typename T = int>
inline T read(void)
{
	T res = 0, f = 1; char ch = getchar();
	while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
	while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
	return res * f;
}
template<typename T>
inline void write(T x, char end = '\n')
{
	static char buf[50]; int p = -1;
	if (x == 0) putchar('0');
	if (x < 0) { putchar('-'); x = -x; }
	while (x) { buf[++p] = x % 10; x /= 10; }
	while (~p) { putchar(buf[p] + '0'); --p; } putchar(end);
}

struct Edge
{
	int v, w;
	Edge(void) { v = w = 0; }
	Edge(int _v, int _w) : v(_v), w(_w) {}
};

int n, m;
int dis[N];
int cnt[N];
bool inque[N];
vector<Edge> G[N];

inline int SPFA(void)
{
	static queue<int> q;
	while (q.size()) q.pop();
	memset(cnt, 0, (n + 1) * sizeof(int));
	memset(dis, 0x3f, (n + 1) * sizeof(int));
	memset(inque, 0, (n + 1) * sizeof(bool));
	for (int i = 1; i <= n; ++i) {
		dis[0] = 0;
		inque[0] = 1;
		q.emplace(0);
		G[0].emplace_back(Edge(i, 0));
	}
	while (q.size()) {
		int u = q.front(); q.pop();
		inque[u] = 0;
		for (auto e : G[u])
			if (dis[e.v] > dis[u] + e.w) {
				dis[e.v] = dis[u] + e.w;
				if (cnt[e.v] >= n) return -1;
				if (!inque[e.v]) {
					++cnt[e.v];
					inque[e.v] = 1;
					q.emplace(e.v);
				}
			}
	}
	return 0;
}

int main(void)
{
	n = read(), m = read();
	for (int i = 1; i <= m; ++i) {
		int v = read(), u = read(), w = read();
		G[u].emplace_back(Edge(v, w));
	}
	if (~SPFA()) {
		for (int i = 1; i <= n; ++i) write(dis[i], i == n ? '\n' : ' ');
	}
	else {
		puts("NO");
	}
	return 0;
}