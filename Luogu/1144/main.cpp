#include <queue>
#include <vector>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 1000010, mod = 100003;

inline int read(void)
{
	int res = 0, f = 1; char ch = getchar();
	while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
	while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
	return res * f;
}

vector<int> G[N];
int n, m;
int f[N];
int dis[N];
queue<int> q;

int main(void)
{
	n = read(), m = read();
	for (int i = 1; i <= m; ++i) {
		int u = read(), v = read();
		G[u].emplace_back(v);
		G[v].emplace_back(u);
	}
	memset(dis, -1, sizeof dis);
	f[1] = 1;
	dis[1] = 0;
	q.emplace(1);
	while (q.size()) {
		int u = q.front(); q.pop();
		for (int v : G[u]) {
			if (dis[v] == dis[u] + 1 || dis[v] == -1) {
				if (dis[v] == -1) {
					dis[v] = dis[u] + 1;
					q.emplace(v);
				}
				f[v] = (f[v] + f[u]) % mod;
			}
		}
	}
	for (int i = 1; i <= n; ++i) printf("%d\n", f[i]);
	return 0;
}