#include <vector>
#include <iostream>
#include <algorithm>

using i64 = long long;
using vint = std::vector<int>;
using PII = std::pair<int, int>;
const int mod = 998244353;
inline int Mod(int x) { return x >= mod ? x - mod : x; }

struct ModInt
{
	int val;
	ModInt(void) { val = 0; }
	ModInt(int x) { val = x; }
	ModInt operator+(const ModInt &other) const
	{ return Mod(val + other.val); }
	ModInt operator-(const ModInt &other) const
	{ return Mod(val + mod - other.val); }
	ModInt operator*(const ModInt &other) const
	{ return 1ll * val * other.val % mod; }
};

int main(void)
{
	//Think twice, code once.
	std::ios::sync_with_stdio(false);
	int n, x, y;
	std::cin >> n >> x >> y;
	vint a(n);
	for (int i = 0; i < n; ++i) {
		std::cin >> a[i];
	}
	if (x <= y) {
		bool fail = 1;
		for (int i = 0; i < n; ++i) {
			if (a[i] % (x + y) >= x) fail = 0;
		}
		puts(fail ? "Second" : "First");
	}
	else {
		bool fail = 0;
		for (int i = 0; i < n; ++i) {
			if (a[i] % (x + y) >= y && (a[i] - x) % (x + y) >= y)
				fail = 1;
		}
		for (int i = 0; i < n; ++i)
			if (a[i] % (x + y) < x) fail = 1;
		puts(fail ? "Second" : "First");
	}
	return 0;
}
