#include <vector>
#include <cstdio>

using namespace std;

#define int long long
const int N = 5010;
const int mod = 998244353;

int n, m, day;
vector<int> edge[N];
int f[2][N], tot[2], tmp;

void Work(void)
{
	tmp ^= 1;
	for (int i = 1; i <= n; ++i)
		f[tmp][i] = tot[tmp ^ 1];
	for (int i = 1; i <= n; ++i)
		for (int j = 0; j < edge[i].size(); ++j) {
			int v = edge[i][j];
			f[tmp][i] = (f[tmp][i] - f[tmp ^ 1][v]) % mod;
		}
	tot[tmp] = 0;
	for (int i = 1; i <= n; ++i)
		tot[tmp] = (tot[tmp] + f[tmp][i]) % mod;
	return;
}

signed main(void)
{
	scanf("%lld%lld%lld", &n, &m, &day);
	for (int i = 1; i <= n; ++i) edge[i].push_back(i);
	for (int i = 1, u, v; i <= m; ++i) {
		scanf("%lld%lld", &u, &v);
		edge[u].push_back(v);
		edge[v].push_back(u);
	}

	tot[tmp] = 1;
	f[tmp][1] = 1;
	while (day--) Work();

	printf("%lld\n", (f[tmp][1] + mod) % mod);
	
	return 0;
}
