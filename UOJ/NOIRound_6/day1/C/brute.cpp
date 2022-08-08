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

using i32 = int;
using i64 = long long;
using PII = std::pair<i32, i32>;
const int N = 2e5 + 10;

i32 n, m;
i32 a[N];

int main(void)
{
	//Think twice, code once.
	read >> n >> m;
	for (int i = 1; i <= n; ++i)
		read >> a[i];
	while (m--) {
		i32 L, R;
		read >> L >> R;
		std::priority_queue<i32, std::vector<i32>, std::greater<i32>> heap;
		i64 res = 0;
		for (int i = 0; L + i <= R; ++i) {
			if (i & 1) {
				if (a[i + L] > heap.top()) {
					res -= heap.top();
					res += a[i + L];
					heap.pop();
					heap.emplace(a[i + L]);
				}
			}
			else {
				res += a[i + L];
				heap.emplace(a[i + L]);
			}
		}
		printf("%lld\n", res);
	}
	return 0;
}
