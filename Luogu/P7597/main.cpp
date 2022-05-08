#include <vector>
#include <cctype>
#include <cstdio>
#include <random>

struct FSI
{
	template<typename T>
	FSI& operator>>(T &res)
	{
		res = 0; T f = 1; char ch = getchar();
		while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
		while (isdigit(ch)) { res = res * 10 + (ch - '0') * f; ch = getchar(); }
		return *this;
	}
} read;

using i64 = long long;
const int N = 5010;

int n;
std::vector<int> G[N];
bool vis[N];
int dep[N], son[N], fa[N];

inline int getDis(int u, int v)
{
	printf("? 1 %d %d\n", u, v);
	fflush(stdout);
	int res; read >> res;
	return res;
}
inline void dfs(int u);
void calc(int u, std::vector<int> &subTree);
inline void dfs(int u)
{
	int num;
	std::vector<int> subTree;
	printf("? 2 %d\n", u);
	fflush(stdout);
	read >> num;
	subTree.resize(num);
	for (int i = 0; i < num; ++i) {
		read >> subTree[i];
		if (dep[subTree[i]] == dep[u] + 1)
			G[u].emplace_back(subTree[i]);
	}
	calc(u, subTree);
}
void calc(int u, std::vector<int> &subTree) {
	vis[u] = 1;
	if (!G[u].size()) return;
	int t = subTree[rand() % subTree.size()];
	for (int v : G[u])
		if (getDis(v, t) == dep[t] - dep[v]) {
			son[u] = v;
			break;
		}
	for (int v : G[u]) {
		fa[v] = u;
		if (v != son[u])
			dfs(v);
	}
	std::vector<int> tmp;
	for (auto t : subTree)
		if (!vis[t]) {
			if (dep[t] == dep[son[u]] + 1)
				G[son[u]].emplace_back(t);
			tmp.emplace_back(t);
		}
	if (son[u]) {
		calc(son[u], tmp);
	}
}

int main(void)
{
	read >> n;
	dep[1] = 1;
	for (int i = 2; i <= n; ++i)
		dep[i] = getDis(1, i) + 1;
	dfs(1);
	printf("! ");
	for (int i = 2; i <= n; ++i)
		printf("%d ", fa[i]);
	puts("");
	fflush(stdout);
	return 0;
}
