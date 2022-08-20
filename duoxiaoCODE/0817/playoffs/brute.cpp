#include <cctype>
#include <cstdio>
#include <cstdint>
#include <algorithm>
#include <functional>

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
using PII = std::pair<i32, i32>;

i32 n, K;
i32 a[100], b[100], c[100];

int main(void)
{
	//Think twice, code once.
	read >> n >> K;
	for (int i = 0; i < n; ++i) {
		read >> a[i] >> b[i] >> c[i];
	}
	i32 ans = 0;
	for (int i = 0; i < 1 << n; ++i) {
		i32 res = 0;
		std::vector<PII> left(__builtin_popcount(i)), right(n - __builtin_popcount(i));
		i32 top1 = 0, top2 = 0;
		for (int j = 0; j < n; ++j) {
			if (i >> j & 1) left[top1++] = std::make_pair(a[j], c[j]);
			else right[top2++] = std::make_pair(b[j], c[j]);
		}
		std::sort(left.begin(), left.end(), std::greater<PII>());
		std::sort(right.begin(), right.end(), std::greater<PII>());
		for (int i = 0; i < K && i < left.size(); ++i)
			res += left[i].second * left[i].first;
		for (int i = 0; i < K && i < right.size(); ++i)
			res += right[i].second * right[i].first;
		ans = std::max(ans, res);
	}
	printf("%d\n", ans);
	return 0;
}
