#include <queue>
#include <vector>
#include <cctype>
#include <cstdio>
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

using i64 = long long;

int main(void)
{
	int n; i64 m;
	read >> n >> m;
	std::vector<i64> a(n);
	std::priority_queue<i64, std::vector<i64>, std::greater<i64>> heap;
	for (int i = 0; i < n; ++i) {
		read >> a[i];
		heap.emplace(a[i]);
		m -= a[i];
	}
	if (m) heap.emplace(m);
	i64 res = 0;
	while (heap.size() > 1) {
		i64 a = heap.top(); heap.pop();
		a += heap.top(); heap.pop();
		res += a;
		heap.emplace(a);
	}
	printf("%lld\n", res);
	return 0;
}
