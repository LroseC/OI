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
		while (isdigit(ch)) { res = res * 10 + (ch - '0') * f; ch = getchar(); }
		return *this;
	}
} read;

using i64 = long long;
const int N = 2e5 + 10;
int mod;
inline int Mod(int x) { return x >= mod ? x - mod : x; }

struct ModInt
{
	int v;
	ModInt(int x) { v = x; }

	ModInt operator+(const ModInt &other)
	{ return Mod(v + other.v); }
	ModInt operator-(const ModInt &other)
	{ return Mod(v + mod - other.v); }
	ModInt operator*(const ModInt &other)
	{ return 1ll * v * other.v % mod; }
};
struct BIT
{
	int tr[N];
	inline int lowbit(int x) { return x & -x; }
	void add(int x, int val)
	{
		++x;
		for (int i = x; i < N; i += lowbit(i))
			tr[i] += val;
	}
	int query(int x)
	{
		++x;
		x = std::min(x, N - 1);
		int res = 0;
		for (int i = x; i; i -= lowbit(i))
			res += tr[i];
		return res;
	}
} bit;

int n;

void work(void)
{
	read >> n >> mod;
	for (int i = 1; i <= n; ++i)
		bit.add((ModInt(i) * i * i).v, 1);
	i64 res = 0;
	for (int b = 1; b <= n; ++b) {
		auto v = ModInt(b) * b;
		//a = c^3 - b^2;
		// 枚举 -b^2, c^3 = [1, b] + b^2;
		int first = v.v, second = b + v.v;
		int tim = second / mod - first / mod;
		res += tim * bit.query(mod - 1) + bit.query(second % mod) - bit.query(first % mod);
		bit.add((ModInt(b) * b * b).v, -1);
	}
	printf("%lld\n", res);
}

int main(void)
{
	int T; read >> T;
	while (T--)
		work();
	return 0;
}
