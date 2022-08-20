#include <cctype>
#include <cstdio>
#include <cstdint>
#include <cstring>
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

using i32 = int32_t;
using i64 = int64_t;
using u64 = uint64_t;
using PII = std::pair<i32, i32>;
const int N = 5e5 + 10;
const int SZ = 10000019;

struct hashMap
{
};

i32 n;
char str[N];
i64 f[N][35];
u64 hash[N], pw[N];
std::unordered_map<u64, i32> cnt;

inline u64 getHash(i32 l, i32 r)
{ return hash[r] - hash[l - 1] * pw[r - l + 1]; }
inline int getCnt(i32 l, i32 r)
{ return cnt[getHash(l, r)]; }
int main(void)
{
#ifndef DEBUG
	freopen("string.in", "r", stdin);
	freopen("string.out", "w", stdout);
#endif
	//Think twice, code once.
	scanf("%s", str + 1);
	n = strlen(str + 1);
	pw[0] = 1;
	for (int i = 1; i <= n; ++i) {
		hash[i] = hash[i - 1] * 131 + str[i] - 'a' + 1;
		pw[i] = pw[i - 1] * 131;
	}
	for (int i = 1; i <= n; ++i)
		for (int j = 0; i + j <= n && j <= 30; ++j) {
			++cnt[getHash(i, i + j)];
		}
	for (int i = 1; i <= n; ++i) f[i][1] = getCnt(i, i);
	for (int len = 2; len <= 30; ++len) {
		for (int l = 1, r = l + len - 1; r <= n; ++l, ++r) {
			f[l][len] = std::max(f[l + 1][len - 1], f[l][len - 1]) + getCnt(l, r);
		}
	}
	if (n <= 30) printf("%ld\n", f[1][n]);
	else {
		i64 res = 0;
		for (int i = 1; i <= n; ++i) res = std::max(res, f[i][30]);
		printf("%ld\n", res + (n - 30));
	}
	return 0;
}
