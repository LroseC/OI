#include <vector>
#include <cctype>
#include <cstdio>
#include <cstring>

using namespace std;

const int N = 1e6 + 10;

inline int read(void)
{
	int res = 0, f = 1; char ch = getchar();
	while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
	while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
	return res * f;
}
template<typename T>
inline void write(T x, char end = '\n')
{
	static char buf[50]; int p = -1;
	if (x == 0) putchar('0');
	if (x < 0) { putchar('-'); x = -x; }
	while (x) { buf[++p] = x % 10; x /= 10; }
	while (~p) { putchar(buf[p] + '0'); --p; } putchar(end);
}

int n;
int ans;
int f[N];
int dis[N];
int stk[N];
int STK[N];
bool vis[20];
bool isfa[20][20];
int connect[20][20];
vector<int> G[N];

int dfs(int u, int fa)
{
	if (f[u]) return f[u];
	int max1 = 0, max2 = 0;
	for (auto v : G[u]) {
		if (v == fa) continue;
		dfs(v, u);
		if (f[v] > f[max1]) {
			max2 = max1, max1 = v;
		}
		else if (f[v] >= f[max2]) {
			max2 = v;
		}
	}
	return (f[u] = f[max1] + f[max2] + 1);
}
void DFS(int cnt)
{
	ans = max(ans, cnt - 1);
	if (cnt > n) return;
	for (int i = 1; i <= n; ++i) {
		if (!vis[i] && (cnt == 1 || isfa[i][stk[cnt - 1]])) {
			stk[cnt] = i;
			vis[i] = 1;
			DFS(cnt + 1);
			vis[i] = 0;
			stk[cnt] = 0;
		}
	}
}

void GetFa(int u, int fa, int dep)
{
	STK[dep] = u;
	for (int i = 0; i < dep; ++i)
		isfa[u][STK[i]] = isfa[STK[i]][u] = 1;
	for (int v = 1; v <= n; ++v) {
		if (v == fa || !connect[u][v]) continue;
		GetFa(v, u, dep + 1);
	}
}

int main(void)
{
	int T = read();
	while (T--) {
		n = read();
		if (n <= 10) {
			ans = 0;
			memset(vis, 0, sizeof vis);
			memset(connect, 0, sizeof connect);
			for (int i = 1; i < n; ++i) {
				int u = read(), v = read();
				connect[u][v] = connect[v][u] = 1;
			}
			GetFa(1, -1, 0);
			DFS(1);
			write(ans);
		}
		else {
			memset(f, 0, sizeof f);
			for (int i = 1; i <= n; ++i) G[i].clear();
			for (int i = 1; i < n; ++i) {
				int u = read(), v = read();
				G[u].emplace_back(v);
				G[v].emplace_back(u);
			}
			write(dfs(1, -1));
		}
	}
	return 0;
}
