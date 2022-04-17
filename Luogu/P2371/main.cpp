#include <queue>
#include <vector>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <algorithm>

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
const int N = 5e5 + 10;

struct Edge
{
	int v, w;

	Edge(void) {}
	Edge(int _v, int _w) { v = _v, w = _w; }
};

int n;
i64 l, r;
int a[20];
i64 dis[N];
bool inque[N];
std::vector<Edge> G[N];

void SPFA(void)
{
	std::queue<int> q;
	std::memset(dis, 0x3f, sizeof dis);
	dis[0] = 0;
	q.emplace(0);
	while (q.size()) {
		int u = q.front(); q.pop();
		inque[u] = 0;
		for (auto t : G[u])
			if (dis[t.v] > dis[u] + t.w) {
				dis[t.v] = dis[u] + t.w;
				if (!inque[t.v]) {
					inque[t.v] = 1;
					q.emplace(t.v);
				}
			}
	}
}
int main(void)
{
	read >> n >> l >> r;
	for (int i = 1; i <= n; ++i)
		read >> a[i];
	std::sort(a + 1, a + 1 + n);
	for (int i = 0; i < a[1]; ++i)
		for (int j = 2; j <= n; ++j)
			G[i].emplace_back((i + a[j]) % a[1], a[j]);
	SPFA();
	i64 res = 0;
	for (int i = 0; i < a[1]; ++i) {
		if (r - dis[i] >= 0)
			res += (r - dis[i]) / a[1] + 1;
		if (l - 1 - dis[i] >= 0)
			res -= (l - 1 - dis[i]) / a[1] + 1;
	}
	printf("%lld\n", res);
	return 0;
}
