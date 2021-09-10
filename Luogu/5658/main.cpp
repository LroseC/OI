#include <vector>
#include <cctype>
#include <cstdio>
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
const int N = 5e5 + 10;

int n;
char str[N];
int match[N], fa[N];
LL f[N];
vector<int> G[N];

void dfs(int u, int father)
{
	match[u] = match[fa[u]];
	if (str[u] == '(') match[u] = u;
	else {
		if (match[u]) f[u] = f[fa[match[u]]] + 1;
		match[u] = match[fa[match[u]]];
	}
	for (int v : G[u])
		if (v != father) dfs(v, u);
}

int main(void)
{
	n = read(); scanf("%s", str + 1);
	for (int i = 2; i <= n; ++i) {
		int u = read();
		G[u].emplace_back(i);
		fa[i] = u;
	}
	dfs(1, -1);
	LL ans = 0;
	for (int i = 1; i <= n; ++i) {
		f[i] += f[fa[i]];
		ans ^= i * f[i];
	}
	printf("%lld\n", ans);
	return 0;
}