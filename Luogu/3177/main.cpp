#include <vector>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

#define int long long

inline int read(void)
{
	int res = 0, f = 1; char ch;
	while (!isdigit(ch = getchar())) if (ch == '-') f = -1;
	do res = res * 10 + ch - '0'; while (isdigit(ch = getchar()));
	return res * f;
}

const int N = 2010;
typedef long long ll;

struct Edge
{
	int v, w;
};

int n, m;
int sz[N];
int f[N][N];
vector<Edge> G[N];

void dfs(int u, int fa)
{
	sz[u] = 1;
	f[u][0] = f[u][1] = 0;
	for (auto x : G[u]) {
		int v = x.v;
		if (v == fa) continue;
		dfs(v, u);
		sz[u] += sz[v];
		for (int j = min(sz[u], m); j >= 0; --j) {
			if (f[u][j] != -1)
				f[u][j] += f[v][0] + sz[v] * (n - m - sz[v]) * x.w;
			for (int k = 1; k <= min(sz[v], j); ++k) {
				if (f[u][j - k] == -1) continue;
				int tot = k * (m - k) + (sz[v] - k) * (n - m - sz[v] + k);
				f[u][j] = max(f[u][j], f[u][j - k] + f[v][k] + tot * x.w);
			}
		}
	}
}
// void dfs(int u,int fa){
// 	sz[u]=1;f[u][0]=f[u][1]=0;
// 	for (auto x : G[u]) {
// 		int v = x.v;
// 		if(v==fa)continue;
// 		dfs(v,u);sz[u]+=sz[v];
// 		for(int j=min(m,sz[u]);j>=0;--j){   //此处倒序枚举是为了避免重复选取
// 			if(f[u][j]!=-1)    //在DP前应先加上当前子节点的子树纯白色的情况，这是下面也倒序枚举的前提
// 				f[u][j]+=f[v][0]+(ll)sz[v]*(n-m-sz[v])*x.w;
// 			for(int k=1;k<=min(j,sz[v]);++k){
// 				if(f[u][j-k]==-1)continue;
// 				ll val=(ll)(k*(m-k)+(sz[v]-k)*(n-m-sz[v]+k))*x.w;   //当前情况下连接子节点的边的贡献
// 				f[u][j]=max(f[u][j],f[u][j-k]+f[v][k]+val);
// 			}
// 		}
// 	}
// }

signed main(void)
{
	memset(f, -1, sizeof f);
	n = read(), m = read();
	for (int i = 1; i < n; ++i) {
		int u = read(), v = read(), w = read();
		G[u].emplace_back(Edge({v, w}));
		G[v].emplace_back(Edge({u, w}));
	}
	dfs(1, -1);
	printf("%lld\n", f[1][m]);
	return 0;
}