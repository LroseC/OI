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
i32 g, mod, bl;

i32 BSGS(i32 b)
{
	if (b == 1) return 0;
	std::unordered_map<i32, i32> mp;
	i32 base = 1;
	for (i32 y = 0; y < bl; ++y) {
		mp[i32(1ll * base * b % mod)] = y;
		base = 1ll * base * g % mod;
	}
	i32 t = base;
	for (i32 x = 1; x <= bl; ++x) {
		if (mp.count(t)) {
			return 1ll * x * bl - mp[t];
		}
		t = 1ll * t * base % mod;
	}
	return -1;
}
inline i32 qpow(i32 base, i32 k)
{
	i32 res = 1;
	while (k) {
		if (k & 1) res = 1ll * res * base % mod;
		k >>= 1;
		base = 1ll * base * base % mod;
	}
	return res;
}

int main(void)
{
	//Think twice, code once.
	read >> g >> mod;
	bl = std::sqrt(mod) + 1;
	i32 Q; read >> Q;
	while (Q--) {
		i32 A, B;
		read >> A >> B;
		i32 a = BSGS(A);
		printf("%d\n", qpow(B, a));
	}
	return 0;
}
