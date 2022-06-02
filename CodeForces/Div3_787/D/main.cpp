#include <vector>
#include <cctype>
#include <cstdio>

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
const int N = 2e5 + 10;

int n, root;
int fa[N];
int stk[N], top;
std::vector<int> G[N];

void print(int u)
{
	stk[++top] = u;
	if (!G[u].size()) {
		printf("%d\n", top);
		for (int i = 1; i <= top; ++i)
			printf("%d ", stk[i]);
		puts("");
		top = 0;
		return;
	}
	for (int v : G[u])
		print(v);
}

void work(void)
{
	read >> n;
	for (int i = 1; i <= n; ++i) {
		read >> fa[i];
		if (fa[i] == i)
			root = i;
		else
			G[fa[i]].emplace_back(i);
	}
	int cnt = 0;
	for (int i = 1; i <= n; ++i)
		if (G[i].size() == 0) ++cnt;
	printf("%d\n", cnt);
	print(root);
	puts("");
}
void clear(void)
{
	for (int i = 1; i <= n; ++i)
		G[i].clear();
}

int main(void)
{
	int T; read >> T;
	while (T--) {
		work();
		clear();
	}
	return 0;
}
