#include <vector>
#include <cctype>
#include <cstdio>
#include <algorithm>
#include <unordered_set>

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
const int N = 50;
const i32 m1 = 1e9 + 7, m2 = 1e9 + 9;
const int md = 1e7 + 19;

struct HashMap
{

	i32 cnt0 = 0;
	std::vector<i32> v[md];
	inline i32 getHash(i64 key)
	{ return key % md; }
	void insert(i64 key)
	{
		if (key == 0) ++cnt0;
		i32 hsh = getHash(key);
		bool flg = 0;
		for (auto t : v[hsh])
			if (t == key) flg = 1;
		if (!flg)
			v[hsh].emplace_back(key);
	}
	i32 exist(i64 key)
	{
		if (key == 0) return cnt0;
		i32 hsh = getHash(key);
		for (auto t : v[hsh])
			if (t == key) return 1;
		return 0;
	}
} mp;

i64 cnt;
i32 n, ALL, ans[N];
i64 mod, a[N], pur;
inline i64 Mod(i64 x) { return x >= mod ? x - mod : x; }

bool dfs(i32 id, i32 lim, i32 op, i64 sum, i32 allzero)
{
	if (id > lim) {
		if (op == 0) {
			++cnt;
			mp.insert(sum);
		}
		else if (op == 1) {
			if (sum == 0) {
				if (allzero) {
					if (mp.exist(0) > 1) {
						pur = sum;
						ALL = allzero;
						return 1;
					}
					return 0;
				}
				else {
					if (mp.exist(0)) {
						pur = sum;
						ALL = allzero;
						return 1;
					}
					return 0;
				}
			}
			if (mp.exist(mod - sum)) {
				pur = sum;
				ALL = allzero;
				return 1;
			}
			return 0;
		}
		else {
			if (Mod(mod - sum) == pur) {
				if (ALL == 1 && allzero == 1) return 0;
				for (int i = 1; i <= n; ++i)
					printf("%d ", ans[i]);
				puts("");
				exit(0);
			}
		}
		return 0;
	}
	ans[id] = 0;
	if (dfs(id + 1, lim, op, sum, allzero)) return 1;
	ans[id] = 1;
	if (dfs(id + 1, lim, op, Mod(sum + a[id]), 0)) return 1;
	ans[id] = -1;
	if (dfs(id + 1, lim, op, Mod(sum + mod - a[id]), 0)) return 1;
	return 0;
}	

int main(void)
{
	//Think twice, code once.
	read >> n >> mod;
	for (int i = 1; i <= n; ++i)
		read >> a[i];
	if (n == 1) {
		if (a[1] == 0) {
			puts("1");
		}
		else {
			puts("IMPOSSIBLE");
		}
		return 0;
	}
	i32 nn = n / 2;
	dfs(1, nn, 0, 0, 1);
	dfs(nn + 1, n, 1, 0, 1);
	dfs(1, nn, 2, 0, 1);
   	puts("IMPOSSIBLE");
	return 0;
}
