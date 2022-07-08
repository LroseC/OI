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

int main(void)
{
	//Think twice, code once.
	int n; read >> n;
	std::priority_queue<int> heap;
	i64 k = 0, b = 0;
	for (int i = 1; i <= n; ++i) {
		int x; read >> x;
		x -= i;

		heap.emplace(x);
		heap.emplace(x);
		k += 1, b -= x;

		i64 posx = heap.top();
		i64 posy = k * posx + b;
		heap.pop();
		k = 0, b = posy;
	}
	printf("%lld\n", b);
	return 0;
}
