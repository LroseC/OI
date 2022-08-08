#include <set>
#include <string>
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
const int mod = 998244353;
inline i32 Mod(i32 x) { return x >= mod ? x - mod : x; }

struct ModInt 
{
	i32 val;
	ModInt(i32 x = 0) { val = x; }
	ModInt operator+(const ModInt &other) const
	{ return Mod(val + other.val); }
	ModInt operator-(const ModInt &other) const
	{ return Mod(val + mod - other.val); }
	ModInt operator*(const ModInt &other) const
	{ return 1ll * val * other.val % mod; }
	void operator+=(const ModInt &other)
	{ val = Mod(val + other.val); }
};

i32 n, m, len, cnt;
std::set<i32> S;
char str[310];
char s[310];
ModInt f[310][310];

void dfs(int x, int cnt1, int cnt2, i32 top)
{
	if (x == n && cnt1 == m && cnt2 == m) {
		i32 t = 0;
		for (int i = 1; i <= top; ++i)
			if (s[i] == '1') t |= 1 << i;
		S.insert(t);
		return;
	}
	if (x != n) {
		s[top + 1] = str[x + 1];
		dfs(x + 1, cnt1, cnt2, top + 1);
	}
	if (cnt1 != m) {
		s[top + 1] = '0';
		dfs(x, cnt1 + 1, cnt2, top + 1);
	}
	if (cnt2 != m && cnt2 + 1 <= cnt1) {
		s[top + 1] = '1';
		dfs(x, cnt1, cnt2 + 1, top + 1);
	}
}
int main(void)
{
	//Think twice, code once.
	read >> n >> m;
	scanf("%s", str + 1);
	dfs(0, 0, 0, 0);
	printf("%d\n", S.size());
	return 0;
}
