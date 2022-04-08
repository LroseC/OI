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
const int N = 1e6 + 10;
inline int lowbit(int x) { return x & -x; }

template<int SIZE>
struct BIT
{
	int tr[SIZE];

	void add(int x, int val)
	{
		x += 2;
		for (int i = x; i < SIZE; i += lowbit(i))
			tr[i] += val;
	}
	int query(int x)
	{
		x += 2;
		int res = 0;
		for (int i = x; i; i -= lowbit(i))
			res += tr[i];
		return res;
	}
};
BIT<(int)1e5 + 10> bit1, bit2;
int n, val[N], ans[N];

int main(void)
{
	read >> n;
	for (int i = 1; i <= n; ++i) {
		read >> val[i];
		val[i] = std::abs(val[i]);
	}
	for (int i = 1; i <= n; ++i) {
		ans[i] = bit1.query(val[i] - 1);
		bit1.add(val[i], 1);
	}
	i64 res = 0;
	for (int i = n; i >= 1; --i) {
		res += std::min(ans[i], bit2.query(val[i] - 1));
		bit2.add(val[i], 1);
	}
	printf("%lld\n", res);
	return 0;
}
