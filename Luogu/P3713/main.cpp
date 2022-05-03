#include <map>
#include <cctype>
#include <cstdio>
#include <string>
#include <iostream>

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
const int mod = 1e9 + 9;
inline int Mod(int x) { return x >= mod ? x - mod : x; }

int n, m, ans;
std::map<std::string, int> cnt;
char G[20][20];
bool vis[20][20];

void initAns(int i, int j, int u, int v, std::string s)
{
	s.push_back(G[i][j]);
	if (i == u && j == v) {
		++cnt[s];
		return;
	}
	if (i != u) {
		int t = i < u;
		initAns(i + (t ? 1 : -1), j, u, v, s);
	}
	if (j != v) {
		int t = j < v;
		initAns(i, j + (t ? 1 : -1), u, v, s);
	}
	if (i != u && j != v) {
		int a = i < u ? 1 : -1, b = j < v ? 1 : -1;
		initAns(i + a, j + b, u, v, s);
	}
}

int main(void)
{
	read >> n >> m;
	for (int i = 1; i <= n; ++i)
		scanf("%s", G[i] + 1);
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			for (int u = 1; u <= n; ++u)
				for (int v = 1; v <= m; ++v) {
					if (i == u && j == v) continue;
					initAns(i, j, u, v, "");
				}
	for (auto t : cnt) {
		ans = Mod(ans + 1ll * t.second * t.second % mod);
	}
	printf("%d\n", ans);
	return 0;
}
