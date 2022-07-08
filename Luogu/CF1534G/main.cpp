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
using vint = std::vector<int>;
using PII = std::pair<int, int>;
const int N = 1e6 + 10;

int n;
PII a[N];

int main(void)
{
	//Think twice, code once.
	read >> n;
	for (int i = 1; i <= n; ++i) {
		read >> a[i].first >> a[i].second;
	}
	auto cmp = [](const PII &a, const PII &b)
	{ return a.first + a.second < b.first + b.second; };
	std::sort(a + 1, a + 1 + n, cmp);
	i64 ans = 0, tagR = 0;
	std::priority_queue<i64> L;
	std::priority_queue<i64, std::vector<i64>, std::greater<i64>> R;
	L.emplace(a[1].first); R.emplace(a[1].first);
	for (int i = 2; i <= n; ++i) {
		tagR += a[i].first + a[i].second - a[i - 1].first - a[i - 1].second;
		int left = L.top(), right = R.top() + tagR;
		if (a[i].first <= left) {
			L.emplace(a[i].first);
			L.emplace(a[i].first);
			ans += left - a[i].first;
			L.pop(); R.emplace(left - tagR);
		}
		else if (a[i].first >= right) {
			R.emplace(a[i].first - tagR);
			R.emplace(a[i].first - tagR);
			ans += a[i].first - right;
			R.pop(); L.emplace(right);
		}
		else {
			L.emplace(a[i].first);
			R.emplace(a[i].first - tagR);
		}
	}
	printf("%lld\n", ans);
	return 0;
}
