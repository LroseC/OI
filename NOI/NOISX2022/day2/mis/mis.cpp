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
const int N = 5010;

int n, val[N], fa[N], tval[N];
std::vector<PII> e;

int main(void)
{
	freopen("mis.in", "r", stdin);
	freopen("mis.out", "w", stdout);
	read >> n;
	for (int i = 1; i <= n; ++i)
		read >> val[i];
	for (int i = 2; i <= n; ++i) {
		read >> fa[i];
		e.emplace_back(fa[i], i);
	}
	std::vector<int> per(n - 1);
	for (int i = 0; i < n - 1; ++i)
		per[i] = i;
	int ans = 0x3f3f3f3f;
	do {
		int res = 0;
		for (int i = 1; i <= n; ++i)
			tval[i] = val[i];
		for (int i = 0; i < per.size(); ++i) {
			auto edge = e[per[i]];
			int u = edge.first, v = edge.second;
			res += tval[u] + tval[v];
			std::swap(tval[u], tval[v]);
		}
		ans = std::min(ans, res);
	} while (next_permutation(per.begin(), per.end()));
	printf("%d\n", ans);
	return 0;
}
