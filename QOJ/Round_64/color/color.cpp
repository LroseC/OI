#include <vector>
#include <cctype>
#include <cstdio>
#include <cstring>
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
using PII = std::pair<int, int>;
const int N = 1e5 + 10;

int n, m, TYPE;
bool vis[N];
int val[N], stk[N], top;
PII line[N];
std::vector<int> nums;

int main(void)
{
//	freopen("color.in", "r", stdin);
//	freopen("color.out", "w", stdout);
	read >> n >> m >> TYPE;
	for (int i = 1; i <= n; ++i) {
		read >> val[i];
		nums.emplace_back(val[i]);
	}
	std::sort(nums.begin(), nums.end());
	nums.erase(std::unique(nums.begin(), nums.end()), nums.end());
	for (int i = 1; i <= n; ++i)
		val[i] = std::lower_bound(nums.begin(), nums.end(), val[i]) - nums.begin();

	int lastans = 0;
	for (int TIME = 1; TIME <= m; ++TIME) {
		int k; read >> k;
		for (int i = 1; i <= k; ++i) {
			int l, r; read >> l >> r;
			if (TYPE && TIME != 1) {
				l ^= lastans, r ^= lastans;
				l = l % n + 1, r = r % n + 1;
				if (l > r) std::swap(l, r);
			}
			line[i].first = l, line[i].second = r;
		}
		std::sort(line + 1, line + 1 + k);
		PII res = line[1];
		for (int i = 2; i <= k; ++i) {
			if (res.second >= line[i].first)
				res.second = std::max(res.second, line[i].second);
			else {
				for (int j = res.first; j <= res.second; ++j)
					if (!vis[val[j]]) {
						vis[val[j]] = 1;
						stk[++top] = val[j];
					}
				res = line[i];
			}
		}
		for (int j = res.first; j <= res.second; ++j)
			if (!vis[val[j]]) {
				vis[val[j]] = 1;
				stk[++top] = val[j];
			}
		printf("%d\n", lastans = top);
		while (top)
			vis[stk[top--]] = 0;
		std::memset(vis, 0, sizeof vis);
		top = 0;
	}
	return 0;
}
