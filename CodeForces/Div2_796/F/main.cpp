#include <set>
#include <queue>
#include <vector>
#include <cctype>
#include <cstdio>
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

using i64 = long long;
using PII = std::pair<int, int>;
const int N = 2e5 + 10;

std::vector<int> pt[N];

int main(void)
{
	int tt; read >> tt;
	while (tt--) {
		int n, m;
		read >> n >> m;
		std::vector<int> a(n + 1), b(n + 1), cnt(m);
		std::vector<i64> sum(n + 1);
		std::vector<PII> line(m);
		std::set<int> S;
		for (int i = 1; i <= n; ++i) {
			read >> a[i];
		}
		for (int i = 1; i <= n; ++i) {
			read >> b[i];
			sum[i] = sum[i - 1] + a[i] - b[i];
		}
		for (int i = 0; i < m; ++i) {
			read >> line[i].first >> line[i].second;
			pt[line[i].first - 1].emplace_back(i);
			pt[line[i].second].emplace_back(i);
			cnt[i] = 2;
		}
		std::queue<int> q;
		for (int i = 0; i <= n; ++i) {
			if (sum[i] == 0) {
				for (int o : pt[i]) {
					--cnt[o];
					if (cnt[o] == 0) {
						q.emplace(o);
					}
				}
			}
			else S.insert(i);
		}
		while (q.size()) {
			int u = q.front(); q.pop();
			int l = line[u].first, r = line[u].second;
			int o;
			while (S.size()) {
				auto it = S.lower_bound(l);
				if (it == S.end() || (o = *it) > r) break;
				for (int t : pt[o]) {
					--cnt[t];
					if (cnt[t] == 0) {
						q.emplace(t);
					}
				}
				S.erase(o);
			}
		}
		puts(S.empty() ? "Yes" : "No");
		for (int i = 0; i <= n; ++i) {
			pt[i].clear();
		}
	}
	return 0;
}
