#include <vector>
#include <climits>
#include <iostream>
#include <algorithm>

#define read std::cin
using i64 = long long;
using vint = std::vector<int>;
using PII = std::pair<int, int>;
const int mod = 1e9 + 7;
inline int Mod(int x) { return x >= mod ? x - mod : x; }

struct Query
{
	int l, r, x;
	Query(void) {}
	Query(int _l, int _r, int _x)
	{ l = _l, r = _r, x = _x; }
	bool operator<(const Query &other) const
	{ return l < other.l; }
};

int main(void)
{
	//Think twice, code once.
#ifndef DEBUG
	std::ios::sync_with_stdio(false);
#endif
	int tt; read >> tt;
	while (tt--) {
		int n, m;
		read >> n >> m;
		vint val(n + 1, (1 << 30) - 1), sum(n + 1);
		std::vector<Query> q(m);
		for (int i = 0; i < m; ++i) {
			int l, r, x;
			read >> l >> r >> x;
			q[i] = Query(l, r, x);
		}
		std::sort(q.begin(), q.end());
		for (int i = 1; i <= n; ++i)
			sum[i] = sum[i - 1] ^ val[i];
		int res = 0;
		for (int i = 0; i < 31; ++i) {
			int cnt[2];
			cnt[0] = 1, cnt[1] = 0;
			std::vector<Query> tq;
			for (auto t : q) {
				if ((t.x >> i & 1) == 0)
					tq.emplace_back(t);
			}
			int p = 0;
			for (int j = 1; j <= n; ++j) {
				while (p < tq.size() && tq[p].l <= j && tq[p].r < j) ++p;
				if (p < tq.size() && tq[p].l <= j && j <= tq[p].r) sum[j] = sum[j - 1];
				else sum[j] = sum[j - 1] ^ 1;
				int v = sum[j];
				res = Mod(res + (1ll << i) * cnt[v ^ 1] % mod);
				int c[2];
				c[0 ^ v] = cnt[0];
				c[1 ^ v] = cnt[1];
				cnt[0] = Mod(cnt[0] + c[0]);
				cnt[1] = Mod(cnt[1] + c[1]);
			}
		}
		printf("%d\n", res);
	}
	return 0;
}
