#include <vector>
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
const int N = 6e4 + 10, B = 244, S = 1 << 26;

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
char str[N];
int s[N];
int cnt[S];

void Add(int x, i64 &res)
{
	res += cnt[s[x]];
	for (int i = 0; i < 26; ++i)
		res += cnt[s[x] ^ (1 << i)];
	++cnt[s[x]];
}
void Dec(int x, i64 &res)
{
	--cnt[s[x]];
	for (int i = 0; i < 26; ++i)
		res -= cnt[s[x] ^ (1 << i)];
	res -= cnt[s[x]];
}

int main(void)
{
	read >> n >> m;
	scanf("%s", str + 1);
	for (int i = 1; i <= n; ++i)
		s[i] = s[i - 1] ^ (1 << str[i] - 'a');
	std::vector<Query> q(m);
	for (int i = 0; i < m; ++i) {
		q[i].id = i;
		read >> q[i].l >> q[i].r;
	}
	std::sort(q.begin(), q.end());

	int L = 1, R = 0; i64 res = 0;
	std::vector<i64> ans(m);
	for (int i = 0; i < m; ++i) {
		while (L > q[i].l) Add(--L, res);
		while (R < q[i].r) Add(++R, res);
		while (L < q[i].l) Dec(L++, res);
		while (R > q[i].r) Dec(R--, res);

		Add(--L, res);
		ans[q[i].id] = res;
	}
	for (int i = 0; i < m; ++i)
		printf("%lld\n", ans[i]);
	return 0;
}
