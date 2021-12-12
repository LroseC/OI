#include <vector>
#include <cctype>
#include <cstdio>

using namespace std;

struct FSI
{
	template<typename T>
	FSI& operator>>(T &res) {
		res = 0; T f = 1; char ch = getchar();
		while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
		while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
		res = res * f; return *this;
	}
} io;

const int N = 3e5 + 10;

int TYPE;
int n, m;
int lastans;
vector<int> G[N];
bool vis[N];
int stk[N], top;

void dfs(int u, int fa, int dep, int &res)
{
	res = max(res, dep);
	for (int v : G[u]) {
		if (v == fa) continue;
		dfs(v, u, dep + 1, res);
	}
}

int main(void)
{
	io >> TYPE;
	io >> n >> m;
	while (m--) {
		static int op, x, y;
		io >> op >> x;
		x ^= TYPE ? lastans : 0;
		if (op == 1) {
			io >> y;
			y ^= TYPE ? lastans : 0;
			G[x].emplace_back(y);
			G[y].emplace_back(x);
		}
		else {
			lastans = 0;
			dfs(x, x, 0, lastans);
			printf("%d\n", lastans);
		}
	}
	return 0;
}