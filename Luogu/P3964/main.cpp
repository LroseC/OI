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
		while (isdigit(ch)) { res = res * 10 + (ch - '0') * f; ch = getchar(); }
		return *this;
	}
} read;

using i64 = long long;
using PII = std::pair<int, int>;
const int N = 1e5 + 10;

struct BIT
{
	int sz[N];
	i64 sum[N];

	inline int lowbit(int x) { return x & -x; }
	inline void insert(int x, int v)
	{
		for (int i = x; i < N; i += lowbit(i)) {
			sz[i] += 1;
			sum[i] += v;
		}
	}
	inline std::pair<int, i64> query(int x)
	{
		std::pair<int, i64> res;
		res.first = res.second = 0;
		for (int i = x; i; i -= lowbit(i)) {
			res.first += sz[i];
			res.second += sum[i];
		}
		return res;
	}
} bit1, bit2;

int n;
PII p[N];
i64 totX, totY;
std::vector<int> numsX, numsY;

inline int getX(int x)
{ return std::lower_bound(numsX.begin(), numsX.end(), x) - numsX.begin() + 1; }
inline int getY(int x)
{ return std::lower_bound(numsY.begin(), numsY.end(), x) - numsY.begin() + 1; }

inline i64 query(int x, int y)
{
	auto t1 = bit1.query(getX(x));
	auto t2 = bit2.query(getY(y));
	i64 X = (1ll * x * t1.first - t1.second) +
			((totX - t1.second) - 1ll * x * (n - t1.first));
	i64 Y = (1ll * y * t2.first - t2.second) +
			((totY - t2.second) - 1ll * y * (n - t2.first));
	return X + Y;
}

int main(void)
{
	read >> n;
	for (int i = 1, x, y; i <= n; ++i) {
		read >> x >> y;
		p[i].first = x + y;
		p[i].second = x - y;
	}
	for (int i = 1; i <= n; ++i) {
		numsX.emplace_back(p[i].first);
		numsY.emplace_back(p[i].second);
	}
	std::sort(numsX.begin(), numsX.end());
	numsX.erase(std::unique(numsX.begin(), numsX.end()), numsX.end());
	std::sort(numsY.begin(), numsY.end());
	numsY.erase(std::unique(numsY.begin(), numsY.end()), numsY.end());
	for (int i = 1; i <= n; ++i) {
		totX += p[i].first;
		totY += p[i].second;
		bit1.insert(getX(p[i].first), p[i].first);
		bit2.insert(getY(p[i].second), p[i].second);
	}
	i64 ans = LLONG_MAX;
	for (int i = 1; i <= n; ++i)
		ans = std::min(ans, query(p[i].first, p[i].second) / 2);
	printf("%lld\n", ans);
	return 0;
}
