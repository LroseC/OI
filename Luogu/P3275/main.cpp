#include <queue>
#include <vector>
#include <cctype>
#include <cstdio>
#include <climits>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long LL;
const int N = 1e5 + 10;

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

int n, k;
int dis[N];
int cnt[N];
bool inque[N];
vector<Edge> G[N];

/*
如果 X = 1 连长度为 0 的双向边
如果 X = 2 连长度为 -1 的 B -> A 单向边
如果 X = 3 连长度为 0 的 A -> B 单向边
如果 X = 4 连长度为 -1 的 A -> B 单向边
如果 X = 3 连长度为 0 的 B -> A 单向边
*/

inline int SPFA(void)
{
	static queue<int> q;
	while (q.size()) q.pop();
	memset(cnt, 0, (n + 1) * sizeof(int));
	memset(dis, 0xcf, (n + 1) * sizeof(int));
	memset(inque, 0, (n + 1) * sizeof (bool));
	dis[0] = 1;
	inque[0] = 1;
	q.emplace(0);
	for (int i = 1; i <= n; ++i)
		G[0].emplace_back(Edge(i, 0));
	while (q.size()) {
		int u = q.front(); q.pop();
		inque[u] = 0;
		for (auto e : G[u])
			if (dis[e.v] < dis[u] + e.w) {
				dis[e.v] = dis[u] + e.w;
				if (cnt[e.v] > n) return -1;
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
	n = read(), k = read();
	while (k--) {
		int op = read(), A = read(), B = read();
		switch(op) {
			case 1:
				G[A].emplace_back(Edge(B, 0));
				G[B].emplace_back(Edge(A, 0));
				break;
			case 2:
				if (A == B) { write(-1); return 0; }
				G[A].emplace_back(Edge(B, 1));
				break;
			case 3:
				G[B].emplace_back(Edge(A, 0));
				break;
			case 4:
				if (A == B) { write(-1); return 0; }
				G[B].emplace_back(Edge(A, 1));
				break;
			case 5:
				G[A].emplace_back(Edge(B, 0));
				break;
		}
	}
	if (SPFA() == -1) write(-1);
	else {
		LL ans = 0;
		for (int i = 1; i <= n; ++i)
			ans += dis[i];
		write(ans);
	}
	return 0;
}