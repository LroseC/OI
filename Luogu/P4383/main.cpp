#include <vector>
#include <cctype>
#include <cstdio>
#include <climits>
#include <algorithm>

struct FSI
{
	template<typename T>
	FSI& operator>>(T &res)
	{
		res = 0; T f = 1; char ch = getchar();
		while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
		while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
		res = res * f; return *this;
	}
} read;

using i64 = long long;
const int N = 3e5 + 10;

struct Edge
{
	int v;
	i64 w;
	Edge(void) {};
	Edge(int _v, i64 _w) { v = _v, w = _w; }
};
struct data
{
	i64 val;
	int cnt;

	data(void) {}
	data(i64 _v, int _c) { val = _v, cnt = _c; }
	bool operator<(const data &other) const { return val < other.val; }
	data operator+(const data &other) const { return data(val + other.val, cnt + other.cnt); }
};

int n, K;
data f[N][3];
std::vector<Edge> G[N];

void dp(int u, int fa, i64 delta)
{
	f[u][0] = data(0ll, 0);
	f[u][1] = data(-2e18, 0);
	f[u][2] = data(-delta, 1);
	for (auto t : G[u])
		if (t.v != fa) {
			data res[3];
			for (int i = 0; i < 3; ++i)
				res[i] = data(LLONG_MIN, 0);

			dp(t.v, u, delta);
			for (int i = 0; i < 3; ++i)
				for (int j = 0; j < 3; ++j)
					res[i] = std::max(res[i], f[u][i] + f[t.v][j]);
			res[1] = std::max(res[1], f[u][0] + f[t.v][0] + data(t.w - delta, 1));
			res[1] = std::max(res[1], f[u][0] + f[t.v][1] + data(t.w, 0));
			res[2] = std::max(res[2], f[u][1] + f[t.v][0] + data(t.w, 0));
			res[2] = std::max(res[2], f[u][1] + f[t.v][1] + data(t.w + delta, -1));

			for (int i = 0; i < 3; ++i)
				f[u][i] = std::max(f[u][i], res[i]);
		}
}

bool check(i64 delta, data &res)
{
	dp(1, 0, delta);
	res = std::max(f[1][0], std::max(f[1][1], f[1][2]));
	return res.cnt > K + 1;
}

int main(void)
{
	read >> n >> K;
	for (int i = 1; i < n; ++i) {
		int u, v, w;
		read >> u >> v >> w;
		G[u].emplace_back(v, w);
		G[v].emplace_back(u, w);
	}
	data ans;
	i64 l = -1e12, r = 1e12;
	while (l < r) {
		i64 mid = l + r >> 1;
		if (check(mid, ans)) l = mid + 1;
		else r = mid;
	}
	check(l, ans);
	printf("%lld\n", ans.val + l * ans.cnt);
	return 0;
}
