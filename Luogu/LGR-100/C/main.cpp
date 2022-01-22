#include <vector>
#include <cctype>
#include <cstdio>
#include <algorithm>

using namespace std;

struct FSI
{
	template<typename T>
	FSI& operator>>(T &res)
	{
		res = 0; T f = 1; char ch = getchar();
		while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
		while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
		res = res * f; return *this;
	}
} IO;

struct Edge
{
	int u, v;
	Edge(void) { u = v = 0; }
	Edge(int _u, int _v) : u(_u), v(_v) {}
};
struct E
{
	int id, v;
	E(void) { id = v = 0; }
	E(int _id, int _v) : id(_id), v(_v) {}
};

const int N = 1e6 + 10, M = 1e6 + 10;

int n, m;
bool vis[N];
bool edgevis[M];
Edge edge[M];
vector<E> G[N];
vector<int> res;
vector<int> del[N];

void DelPoint(int u)
{
	vector<int> tmp;
	for (int id : del[u]) {
		edgevis[id] = 1;
		tmp.emplace_back(id);
	}
	for (auto t : G[u]) {
		if (vis[t.v]) continue;
		vis[t.v] = 1;
		if (!edgevis[t.v])
			del[t.v].emplace_back(t.id);
	}
	sort(tmp.begin(), tmp.end());
	for (int t : tmp)
		res.emplace_back(t);
}

int main(void)
{
	IO >> n >> m;
	for (int i = 1; i <= m; ++i) {
		IO >> edge[i].u >> edge[i].v;
		G[edge[i].u].emplace_back(i, edge[i].v);
		G[edge[i].v].emplace_back(i, edge[i].u);
	}
	for (int i = 1; i <= m; ++i) {
		if (vis[edge[i].u] && vis[edge[i].v])
			continue;
		printf("i = %d\n", i);
		vector<int> tmp;
		if (vis[edge[i].u])
			DelPoint(edge[i].v);
		else if (vis[edge[i].v])
			DelPoint(edge[i].u);
		else {
			DelPoint(edge[i].u);
			DelPoint(edge[i].v);
		}
	}
	long long ans = 0;
	for (int i = 0; i < res.size(); ++i)
		printf("%d ", res[i]);
	puts("");
	for (int i = 1; i <= m; ++i)
		ans ^= 1ll * i * res[i - 1];
	printf("%lld\n", ans);
	return 0;
}
