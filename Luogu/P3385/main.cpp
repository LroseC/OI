#include <queue>
#include <vector>
#include <cctype>
#include <cstdio>
#include <cstdint>
#include <cstring>
#include <algorithm>

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

using i32 = int32_t;
using i64 = int64_t;
using u32 = uint32_t;
using u64 = uint64_t;
using vi32 = std::vector<i32>;
using PII = std::pair<i32, i32>;
const int N = 2e3 + 10;

i32 n, m;
i32 cnt[N], dis[N], inque[N];
std::vector<PII> G[N];

bool SPFA(void)
{
	std::queue<i32> q;
	std::memset(cnt, 0, sizeof cnt);
	std::memset(dis, 0x3f, sizeof dis);
	cnt[1] = 1;
	dis[1] = 0;
	q.emplace(1);
	while (q.size()) {
		i32 u = q.front(); q.pop();
		inque[u] = 0;
		for (auto e : G[u]) {
			if (dis[e.first] > dis[u] + e.second) {
				cnt[e.first] = cnt[u] + 1;
				if (cnt[e.first] > n) return 1;
				dis[e.first] = dis[u] + e.second;
				if (!inque[e.first]) {
					inque[e.first] = 1;
					q.emplace(e.first);
				}
			}
		}
	}
	return 0;
}

void work(void)
{
	read >> n >> m;
	for (int i = 1; i <= m; ++i) {
		i32 u, v, w;
		read >> u >> v >> w;
		G[u].emplace_back(v, w);
		if (w >= 0) {
			G[v].emplace_back(u, w);
		}
	}
	puts(SPFA() ? "YES" : "NO");
	for (int i = 1; i <= n; ++i) {
		G[i].clear();
	}
	std::fill(inque + 1, inque + 1 + n, 0);
}

int main(void)
{
	//Think twice, code once.
	i32 tt; read >> tt;
	while (tt--) {
		work();
	}
	return 0;
}
