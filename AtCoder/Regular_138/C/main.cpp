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
		while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
		res = res * f; return *this;
	}
} read;

using i64 = long long;

int main(void)
{
	int n; read >> n;
	std::vector<int> a(n + 1), b(n), sum(n + 1);
	for (int i = 0; i < n; ++i) {
		read >> a[i];
		b[i] = i;
	}
	auto cmp = [&](int x, int y) { return a[x] > a[y]; };
	std::nth_element(b.begin(), b.begin() + n / 2, b.end(), cmp);
	i64 res = 0;
	for (int i = 0; i < n / 2; ++i) {
		sum[b[i] + 1] = 1;
		res += a[b[i]];
	}
	int max = -1;
	for (int i = 1; i <= n; ++i) {
		a[i] = sum[i] = sum[i] ? 1 : -1;
		sum[i] += sum[i - 1];
		max = std::max(max, sum[i - 1]);
	}
	for (int k = 0; k < n; ++k) {
		if (max <= 1) {
			printf("%d %lld\n", k, res);
			return 0;
		}
		max -= a[k + 1];
	}
	return 0;
}
