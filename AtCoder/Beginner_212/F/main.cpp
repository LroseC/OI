#include <vector>
#include <cstdio>

using namespace std;

struct Edge
{
	int u, v, s, t;
};

const int N = 1e5 + 10;

int n, m, q;
Edge edge[N];
int bus[N];
vector<int> out[N], in[N];

struct cmps
{
	bool operator()(const int &a, const int &b)
	{
		return edge[a].s < edge[b].s;
	}
};
struct cmpt
{
	bool operator()(const int &a, const int &b)
	{
		return edge[a].t > edge[b].t;
	}
};


int main(void)
{
	scanf("%d%d%d", &n, &m, &q);
	for (int i = 1; i <= m; ++i) {
		int u, v, s, t;
		scanf("%d%d%d%d", &u, &v, &s, &t);
		edge[i] = {u, v, s, t};
		out[u].push_back(i);
	}
	for (int i = 1; i <= m; ++i) bus[i] = i;
	sort(bus + 1, bus + 1 + m, cmpt);
	for (int i = 1; i <= n; ++i)
		sort(out[i].begin(), out[i].end(), cmps());

	for (int i = 1; i <= m; ++i) {
		int x = bus[i];
		int u = edge[x].u, v = bus[x].v, s = bus[x].s, t = bus[x].t;
		edge[x].s = t;
		int y;
		iterator<vector<int>> it = lower_bound(out[v].begin(), out[v].end(), x, cmps());
		if (it != out[v].end()) {
			y = *it;
			edge[x].v = edge[y].v;
		}
		edge[x].s = s;
	}

	for (int i = 1; i <= q; ++i) {
		int x, y, z;
		scanf("%d%d%d", &x, &y, &z);
