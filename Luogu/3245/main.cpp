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
const int N = 2e5 + 10, B = 210;

struct Query
{
	int id, l, r;
	bool operator<(const Query &other) const
	{
		if (l / B != other.l / B) return l < other.l; 
		return (l / B & 1) ? r < other.r : r > other.r;
	}
};

int n, m;
int mod;
i64 ans[N];
char str[N];
i64 s[N], cnt[N];
Query q[N];

int Mod(int x) { return x >= mod ? x - mod : x; }
void calc1(void)
{
	for (int i = 1; i <= n; ++i) {
		cnt[i] = cnt[i - 1] + (s[i] % mod == 0);
		s[i] = s[i - 1] + ((s[i] % mod == 0) ? i : 0);
	}
	for (int i = 1; i <= m; ++i)
		printf("%lld\n", s[q[i].r] - s[q[i].l - 1] - (cnt[q[i].r] - cnt[q[i].l - 1]) * (q[i].l - 1));
}
void Add(int x, i64 &res)
{
	res += cnt[s[x]];
	++cnt[s[x]];
}
void Dec(int x, i64 &res)
{
	--cnt[s[x]];
	res -= cnt[s[x]];
}
void calc2(void)
{
	std::vector<int> nums(n + 1);
	for (int i = n, j = 1; i >= 1; --i, j = 10ll * j % mod)
		s[i] = 1ll * s[i] * j % mod;
	for (int i = 1; i <= n; ++i)
		s[i] = Mod(s[i] + s[i - 1]);
	for (int i = 1; i <= n; ++i)
		nums[i - 1] = s[i];
	nums[n] = 0;
	std::sort(nums.begin(), nums.end());
	nums.erase(std::unique(nums.begin(), nums.end()), nums.end());
	for (int i = 1; i <= n; ++i)
		s[i] = lower_bound(nums.begin(), nums.end(), s[i]) - nums.begin();

	std::sort(q + 1, q + 1 + m);
	int L = 1, R = 0; i64 res = 0;
	for (int i = 1; i <= m; ++i) {
		while (R < q[i].r) Add(++R, res);
		while (L > q[i].l) Add(--L, res);
		while (R > q[i].r) Dec(R--, res);
		while (L < q[i].l) Dec(L++, res);
		Add(--L, res);

		ans[q[i].id] = res;
	}
	for (int i = 1; i <= m; ++i)
		printf("%lld\n", ans[i]);
}

int main(void)
{
	read >> mod;
	scanf("%s", str + 1);
	n = strlen(str + 1);
	for (int i = 1; i <= n; ++i)
		s[i] = str[i] - '0';
	read >> m;
	for (int i = 1; i <= m; ++i) {
		q[i].id = i;
		read >> q[i].l >> q[i].r;
	}

	if (mod == 2 || mod == 5) calc1();
	else calc2();
	return 0;
}
