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
const int N = 1010;

int n, m;
i64 ans = 0x3f3f3f3f3f3f3f3f;
int c[N], v[N], a[N], b[N], cgv[N];
std::vector<int> nums;

struct LinearBase
{
	i64 tot = 0;
	int base[64], w[64];
	void init(void)
	{
		tot = 0;
		std::memset(w, 0, sizeof w);
		std::memset(base, 0, sizeof base);
	}
	void insert(int type, int x, int wi)
	{
		for (int i = 63; i >= 0; --i)
			if (x >> i & 1) {
				if (!base[i]) {
					tot += wi;
					base[i] = x;
					w[i] = wi;
					return;
				}
				if (type == 0)
					if (wi < w[i]) {
						tot -= w[i], tot += wi;
						std::swap(base[i], x);
						std::swap(w[i], wi);
					}
				if (type == 1)
					if (wi > w[i]) {
						tot -= w[i], tot += wi;
						std::swap(base[i], x);
						std::swap(w[i], wi);
					}
				x ^= base[i];
			}
	}
} mybase;

inline i64 sq(i64 x) { return x * x; }

bool check(void)
{
	int minans = 0, maxans = 0;
	for (int i = 1; i <= m; ++i) {
		minans += cgv[a[i]];
		maxans += cgv[b[i]];
	}
	mybase.init();
	for (int i = 1; i <= n; ++i)
		mybase.insert(0, c[i], cgv[i]);
	if (mybase.tot < minans) return 0;
	mybase.init();
	for (int i = 1; i <= n; ++i)
		mybase.insert(1, c[i], cgv[i]);
	if (mybase.tot > maxans) return 0;
	return 1;
}
void dfs(int id, i64 cost)
{
	if (id > n) {
		if (check()) ans = std::min(ans, cost);
		return;
	}
	for (int nv : nums) {
		cgv[id] = nv;
		dfs(id + 1, cost + sq(v[id] - cgv[id]));
	}
}

int main(void)
{
//	freopen("shop.in", "r", stdin);
//	freopen("shop.out", "w", stdout);
	read >> n >> m;
	for (int i = 1; i <= n; ++i)
		read >> c[i];
	for (int i = 1; i <= n; ++i) {
		read >> v[i];
		nums.emplace_back(v[i]);
	}
	std::sort(nums.begin(), nums.end());
	nums.erase(std::unique(nums.begin(), nums.end()), nums.end());
	for (int i = 1; i <= m; ++i)
		read >> a[i];
	for (int i = 1; i <= m; ++i)
		read >> b[i];
	dfs(1, 0);
	printf("%d\n", ans);
	return 0;
}
