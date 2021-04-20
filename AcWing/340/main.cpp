#include <queue>
#include <cstdio>
#include <cstring>

using namespace std;

#define reg register
#define ll long long
#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))
const int N = 1010, M = 20010;

struct PII
{
	int now;
	int val;
	int dep;
	PII(int now, int val, int dep) : now(now), val(val), dep(dep) {}
	bool operator<(const PII &b) const
	{
		return val > b.val;
	}
};

int n, m, k;
int idx;
int head[N], nex[M], w[M], to[M];
int dis[N][N];
bool vis[N][N];
priority_queue<PII> q, EMPTY;

void Add_Edge(int, int, int);
void Dij(void);

int main()
{
	scanf("%d%d%d", &n, &m, &k);
	int sti, edi, wi;
	for (int i = 0; i < m; ++i) {
		scanf("%d%d%d", &sti, &edi, &wi);
		Add_Edge(sti, edi, wi);
		Add_Edge(edi, sti, wi);
	}

	Dij();

	int ans = 0;
	for (int i = 0; i <= k; ++i) ans = max(ans, dis[n][k]);
	printf("%d\n", (ans == 0x3f3f3f3f ? -1 : ans));

	return 0;
}
void Add_Edge(int sti, int edi, int wi)
{
	nex[++idx] = head[sti];
	head[sti] = idx;
	to[idx] = edi;
	w[idx] = wi;
}
void Dij(void)
{
	memset(vis, 0, sizeof vis);
	memset(dis, 0x3f, sizeof dis);
	q = EMPTY;
	q.push(PII(1, 0, 0));
	while (q.size()) {
		PII now = q.top();
		q.pop();
		if (vis[now.now][now.dep]) continue;
		vis[now.now][now.dep] = 1;
		dis[now.now][now.dep] = now.val;
		for (int e = head[now.now]; e; e = nex[e]) {
			int tmp = to[e];
			if (!vis[tmp][now.dep] && dis[tmp][now.dep] > max(dis[now.now][now.dep], w[e])) {
				dis[tmp][now.dep] = max(dis[now.now][now.dep], w[e]);
				q.push(PII(tmp, max(now.val, w[e]), now.dep));
			}
			if (now.dep < k && !vis[tmp][now.dep + 1] && dis[tmp][now.dep + 1] > dis[now.now][now.dep]) {
				dis[tmp][now.dep + 1] = dis[now.now][now.dep];
				q.push(PII(tmp, now.val, now.dep + 1));
			}
		}
	}
	return;
}
