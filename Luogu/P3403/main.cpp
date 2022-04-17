#include <queue>
#include <vector>
#include <cctype>
#include <cstdio>
#include <cstring>

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

using i64 = long long;

struct Edge
{
	int v, w;

	Edge(void) {}
	Edge(int _v, int _w) { v = _v, w = _w; }
};

const int N = 1e5 + 10;

i64 h;
int a, b, c;
i64 dis[N];
bool inque[N];
std::vector<Edge> G[N];

void SPFA(int S)
{
	std::queue<int> q;
	std::memset(dis, 0x3f, sizeof dis);
	dis[S] = 1;
	q.emplace(S);
	while (q.size()) {
		int u = q.front(); q.pop();
		inque[u] = 0;
		for (auto t : G[u]) {
			if (dis[t.v] > dis[u] + t.w) {
				dis[t.v] = dis[u] + t.w;
				if (!inque[t.v]) {
					inque[t.v] = 1;
					q.emplace(t.v);
				}
			}
		}
	}
}

int main(void)
{
	read >> h >> a >> b >> c;
	for (int i = 0; i <= a; ++i) {
		G[i].emplace_back((i + b) % a, b);
		G[i].emplace_back((i + c) % a, c);
	}
	SPFA(1 % a);
	i64 res = 0;
	for (int i = 0; i < a; ++i)
		if (h - dis[i] >= 0)
			res += (h - dis[i]) / a + 1;
	printf("%lld\n", res);
	return 0;
}
