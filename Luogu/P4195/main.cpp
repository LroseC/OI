#include <cmath>
#include <vector>
#include <cctype>
#include <cstdio>
#include <algorithm>
#include <unordered_map>

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
using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;
using vint = std::vector<int>;
using PII = std::pair<int, int>;

i32 exgcd(i32 a, i32 b, i32 &x, i32 &y)
{
	if (b == 0) {
		x = 1, y = 0;
		return a;
	}
	i32 d = exgcd(b, a % b, y, x);
	y -= a / b * x;
	return d;
}
i32 getInv(i32 a, i32 p)
{
	i32 x, y;
	exgcd(a, p, x, y);
	x = x % p + p;
	return x >= p ? x - p : x;
}
i32 BSGS(i32 a, i32 b, i32 p)
{
	i32 B = std::sqrt(p) + 1;
	i32 base = 1;
	std::unordered_map<i32, i32> mp;
	for (int y = 0; y < B; ++y) {
		mp[i32(1ll * base * b % p)] = y;
		base = 1ll * base * a % p;
	}
	i32 t = base;
	for (int x = 1; x <= B; ++x) {
		if (mp.count(t)) return x * B - mp[t];
		t = 1ll * t * base % p;
	}
	return -1;
}
i32 exBSGS(i32 a, i32 b, i32 p)
{
	b %= p;
	if (p == 1 || b == 1) return 0;
	int d = std::__gcd(a, p);
	if (d == 1) return BSGS(a, b, p);
	if (b % d != 0) return -1;
	int res = exBSGS(a, 1ll * (b / d) * getInv(a / d, p / d) % (p / d), p / d);
	return res + (res != -1);
}

int main(void)
{
	//Think twice, code once.
	while (true) {
		i32 a, b, p;
		read >> a >> p >> b;
		if (a == 0 && b == 0 && p == 0) break;
		int res = exBSGS(a, b, p);
		if (res == -1) puts("No Solution");
		else printf("%d\n", res);
	}
	return 0;
}
