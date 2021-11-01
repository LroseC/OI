#include <queue>
#include <vector>
#include <cctype>
#include <cstdio>
#include <climits>
#include <cstring>
#include <algorithm>

struct FastStreamInput
{
	template<typename T>
	FSI& operator>>(T &res)
	{
		res = 0; T f = 1; char ch = getchar();
		while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
		while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
		res *= f; return *this;
	}
} cin;

using namespace std;

const int N = 2010;

int n, k;
int MostDis;
int cnt[2][N];
std::vector<int>G[N];

void GetDis(int u, int fa, int dist)
{
	for (int v : G[u]) {
		if (v == fa) continue;
		GetDis(v, u, dist + 1);
	}
}

int main(void)
{
	cin >> n >> k;
	for (int i = 1; i < n; ++i) {
		int u, v; cin >> u >> v;
		G[u].emplace_back(v);
		G[v].emplace_back(u);
	}
	int ans = INT_MAX;
	printf("%d\n", ans);
	return 0;
}