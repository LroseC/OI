#include <queue>
#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

#define reg register
#define ll long long
const int N = 510, M = 4e3 + 10;

int n, m, idx;
int head[N], nex[M], to[M], w[M];
vector<int> t[N];

namespace Dij
{
	struct PII
	{
		int time, now;
		bool operator<(const PII &b) const
		{
			return time > b.time;
		}
	};
	priority_queue<PII> q;
	bool vis[N];
	int dis[N];
	void Dij(void);
}

void Add_Edge(int, int, int);

int main()
{
	reg int sti, edi, wi;
	scanf("%d%d", &n, &m);
	for (reg int i = 0; i < m; ++i) {
		scanf("%d%d%d", &sti, &edi, &wi);
		Add_Edge(sti, edi, wi);
		Add_Edge(edi, sti, wi);
	}
	Add_Edge(0, 1, 0);
	int ki, xi;
	for (int i = 1; i < n; ++i) {
		scanf("%d", &ki);
		for (int j = 0; j < ki; ++j) {
			scanf("%d", &xi);
			t[i].push_back(xi);
		}
		sort(t[i].begin(), t[i].end());
		t[i].erase(unique(t[i].begin(), t[i].end()), t[i].end());
	}
	{
		scanf("%d", &ki);
		for (int j = 0; j < ki; ++j) scanf("%d", &xi);
	}
	Dij::Dij();

	printf("%d\n", Dij::dis[n]);
	return 0;
}
void Add_Edge(int sti, int edi, int wi)
{
	nex[++idx] = head[sti];
	head[sti] = idx;
	to[idx] = edi;
	w[idx] = wi;
}
void Dij::Dij(void)
{
	using namespace Dij;
	memset(vis, 0, sizeof vis);
	memset(dis, 0x3f, sizeof dis);
	q.push({0, 0});
	while (q.size()) {
		PII now = q.top();
		q.pop();
		if (vis[now.now]) continue;
		vis[now.now] = 1;
		dis[now.now] = now.time;
		for (int e = head[now.now]; e; e = nex[e]) {
			if (vis[to[e]]) continue;
			int ti = now.time + w[e];
			for (int i = 0; i < t[to[e]].size(); ++i)
				if (t[to[e]][i] == ti) ++ti;
			q.push({ti, to[e]});
		}
	}
	return;
}
