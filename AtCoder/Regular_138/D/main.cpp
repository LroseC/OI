#include <vector>
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
		while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
		res = res * f; return *this;
	}
} read;

using i64 = long long;

class LinearBasis
{
private:
	int sz;
	int base[30];
public:
	LinearBasis(void)
	{
		sz = 0;
		std::memset(base, 0, sizeof base);
	}
	int size(void)
	{ return sz; }
	void insert(int x)
	{
		int t = x;
		for (int i = 29; i >= 0; --i)
			if (t >> i & 1) {
				if (!base[i]) {
					++sz;
					base[i] = x;
					return;
				}
				else t ^= base[i];
			}
	}
	const int operator[](const int x) const
	{ return base[x]; }
} base;
class GrayCode
{
private:
	int n;
	std::vector<int> unit;
public:
	void build(int _n)
	{
		n = _n;
		unit.resize(1 << n);
		unit[0] = 0, unit[1] = 1;
		for (int k = 2, bit = 1; bit < n; k <<= 1, ++bit) {
			for (int j = 0; j < k; ++j) {
				unit[j + k] = unit[j] | 1 << bit;
			}
			std::reverse(unit.begin() + k, unit.begin() + (k << 1));
		}
	}
	const int operator[](const int x) const
	{ return unit[x]; }
} gray;


int main(void)
{
	int n, K;
	read >> n >> K;
	for (int i = 0; i < 1 << n; ++i) {
		if (__builtin_popcount(i) == K) {
			base.insert(i);
		}
	}
	if (base.size() != n) {
		puts("No");
		return 0;
	}
	else {
		std::vector<int> res(1 << n);
		puts("Yes");
		gray.build(n);
		for (int i = 0; i < 1 << n; ++i) {
			for (int j = 0; j < n; ++j)
				if (gray[i] >> j & 1) res[i] ^= base[j];
		}
		for (int i = 0; i < 1 << n; ++i) {
			printf("%d ", res[i]);
		}
		puts("");
	}
	return 0;
}
