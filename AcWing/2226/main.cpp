#include <vector>
#include <cstdio>
#include <climits>
#include <cstring>
#include <algorithm>

using namespace std;

#define ll long long
const int N = 150010, M = N << 1;

struct Son
{
	int age;
	ll dis;
	bool operator<(const Son &b) const
	{
		return age < b.age;
	}
};
struct Father
{
	int id, k;
	ll dis;
};

int n, m, A;
int age[N];
int idx, head[N], nex[M], to[M], w[M];
int all_node;
bool vis[N];
vector<Son> son[N][3];
vector<Father> f[N];

void AddEdge(int u, int v, int wi)
{
	nex[++idx] = head[u]; to[idx] = v;
	head[u] = idx; w[idx] = wi;
}
int get_size(int u, int fa)
{
	if (vis[u]) return 0;
	int size = 1;
	for (int e = head[u]; e; e = nex[e]) {
		int v = to[e];
		if (v == fa || vis[v]) continue;
		size += get_size(v, u);
	}
	return size;
}
int get_root(int u, int fa, int &root, int &minsize)
{
	if (vis[u]) return 0;
	int maxson = 0, size = 1;
	for (int e = head[u]; e; e = nex[e]) {
		int v = to[e];
		if (v == fa || vis[v]) continue;
		int tmp = get_root(v, u, root, minsize);
		maxson = max(maxson, tmp);
		size += tmp;
	}
	maxson = max(maxson, all_node - size);
	if (maxson < minsize) {
		minsize = maxson;
		root = u;
	}
	return size;
}
void get_dis(int u, int fa, int dist, int k, int root, vector<Son> &p)
{
	if (vis[u]) return;
	p.push_back({age[u], dist});
	f[u].push_back({root, k, dist});
	for (int e = head[u]; e; e = nex[e]) {
		int v = to[e];
		if (v == fa || vis[v]) continue;
		get_dis(v, u, dist + w[e], k, root, p);
	}
}
void dfs(int u)
{
	if (vis[u]) return;
	vis[u] = 1;
	for (int e = head[u], k = 0; e; e = nex[e]) {
		int v = to[e];
		if (vis[v]) continue;
		auto &p = son[u][k];
		p.push_back({-1, 0}), p.push_back({A + 1, 0});
		get_dis(v, u, w[e], k, u, p);
		sort(p.begin(), p.end());
		for (int i = 1; i < p.size(); ++i)
			p[i].dis += p[i - 1].dis;
		++k;
	}
	for (int e = head[u]; e; e = nex[e]) {
		int v = to[e];
		if (vis[v]) continue;
		int root, minsize = INT_MAX;
		all_node = get_size(v, u);
		get_root(v, u, root, minsize);
		dfs(root);
	}
}

ll Query(int u, int l, int r)
{
	ll res = 0;
	for (int i = 0; i < f[u].size(); ++i) {
		auto p = f[u][i];
		if (age[p.id] <= r && age[p.id] >= l) res += p.dis;
		for (int k = 0; k < 3; ++k) {
			if (p.k == k) continue;
			auto &a = son[p.id][k];
			if (a.empty()) continue;
			int left = lower_bound(a.begin(), a.end(), Son({l, -1})) - a.begin();
			int right = lower_bound(a.begin(), a.end(), Son({r + 1, -1})) - a.begin();
			res += p.dis * (right - left) + (a[right - 1].dis - a[left - 1].dis);
		}
	}
	for (int k = 0; k < 3; ++k) {
		auto &a = son[u][k];
		if (a.empty()) continue;
		int left = lower_bound(a.begin(), a.end(), Son({l, -1})) - a.begin();
		int right = lower_bound(a.begin(), a.end(), Son({r + 1, -1})) - a.begin();
		res += (a[right - 1].dis - a[left - 1].dis);
	}

	return res;
}

int main(void)
{
	scanf("%d%d%d", &n, &m, &A);
	for (int i = 1; i <= n; ++i) scanf("%d", &age[i]);
	for (int i = 1; i < n; ++i) {
		int u, v, wi;
		scanf("%d%d%d", &u, &v, &wi);
		AddEdge(u, v, wi);
		AddEdge(v, u, wi);
	}
	int root, minsize = INT_MAX;
	all_node = n;
	get_root(1, -1, root, minsize);
	dfs(root);

	int u, a, b, l, r;
	ll res = 0;
	while (m--) {
		scanf("%d%d%d", &u, &a, &b);
		l = (a + res) % A, r = (b + res) % A;
		if (l > r) swap(l, r);
		res = Query(u, l, r);
		printf("%lld\n", res);
	}
}