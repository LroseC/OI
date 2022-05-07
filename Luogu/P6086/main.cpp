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
const int N = 5e6 + 10;

int n, m, fa[N], d[N], pru[N];
std::vector<int> ans;

void remove(int u, int root)
{
	if (!u) return;
	--d[u];
	ans.emplace_back(u);
	if (!d[u] && u < root)
		remove(fa[u], root);
}

int main(void)
{
	read >> n >> m;
	if (m == 1) {
		for (int i = 1; i < n; ++i) {
			read >> fa[i];
			++d[fa[i]];
		}
		for (int j = 1; j <= n; ++j)
			if (!d[j])
				remove(fa[j], j);
		i64 res = 0;
		for (int i = 0; i < n - 2; ++i)
			res ^= 1ll * (i + 1) * ans[i];
		printf("%lld\n", res);
	}
	else {
		for (int i = 1; i <= n - 2; ++i) {
			read >> pru[i];
			++d[pru[i]];
		}
		pru[n - 1] = n;
		for (int i = 1, j = 1; i <= n - 1; ++j)
			if (!d[j]) {
				fa[j] = pru[i];
				while (i < n && --d[pru[i]] == 0 && pru[i] < j) {
					++i;
					fa[pru[i - 1]] = pru[i];
				}
				++i;
			}
		i64 res = 0;
		for (int i = 1; i < n; ++i)
			res ^= 1ll * i * fa[i];
		printf("%lld\n", res);
	}
	return 0;
}
