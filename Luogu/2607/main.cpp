#include <vector>
#include <cctype>
#include <cstdio>
#include <climits>
#include <algorithm>

using namespace std;

inline int read(void)
{
	int res = 0, f = 1; char ch;
	while (!isdigit(ch = getchar())) if (ch == '-') f = -1;
	do res = res * 10 + ch - '0'; while (isdigit(ch = getchar()));
	return res * f;
}

typedef long long LL;
const int N = 1e6 + 10;

int n;
LL ans;
int v[N];
vector<int> G[N];
LL f1[N][2], f2[N][2];
bool vis[N], instk[N];

void calc(int u, int ban, int rt, LL f[N][2])
{
	f[u][1] = v[u];
	for (int v : G[u]) {
		if (v == rt) continue;
		calc(v, ban, rt, f);
		f[u][0] += max(f[v][0], f[v][1]);
		f[u][1] += f[v][0];
	}
	if (u == ban) f[u][1] = LONG_LONG_MIN;
}

void get_root(int u)
{
	vis[u] = 1, instk[u] = 1;
	for (int v : G[u]) {
		if (instk[v]) {
			calc(v, u, v, f1);
			calc(v, -1, v, f2);
			ans += max(f1[v][1], f2[v][0]);
		}
		if (vis[v]) continue;
		get_root(v);
	}
	instk[u] = 0;
}

int main(void)
{
	n = read();
	for (int i = 1; i <= n; ++i) {
		v[i] = read();
		int u = read();
		G[u].emplace_back(i);
	}
	for (int i = 1; i <= n; ++i)
		if (!vis[i])
			get_root(i);
	printf("%lld\n", ans);
	return 0;
}