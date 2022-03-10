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
const int N = 1e5 + 10, B = 210;

struct Query
{
	int id, l, r;
	bool operator<(const Query& other)
	{
		if (l / B != other.l / B) return l < other.l;
		return (l / B & 1) ? r < other.r : r > other.r;
	}
};

int n, m, k;
int a[N], cnt[N << 1];
i64 ans[N];
Query q[N];

void Add(int x, i64 &res)
{
	res += cnt[a[x] ^ k];
	++cnt[a[x]];
}
void Dec(int x, i64 &res)
{
	--cnt[a[x]];
	res -= cnt[a[x] ^ k];
}

int main(void)
{
	read >> n >> m >> k;
	for (int i = 1; i <= n; ++i)
		read >> a[i], a[i] ^= a[i - 1];
	for (int i = 1; i <= m; ++i) {
		q[i].id = i;
		read >> q[i].l >> q[i].r;
	}
	std::sort(q + 1, q + 1 + m);

	int L = 1, R = 0; i64 res = 0;
	for (int i = 1; i <= m; ++i) {
		while (L > q[i].l) Add(--L, res);
		while (R < q[i].r) Add(++R, res);
		while (L < q[i].l) Dec(L++, res);
		while (R > q[i].r) Dec(R--, res);

		Add(--L, res);
		ans[q[i].id] = res;
	}
	for (int i = 1; i <= m; ++i)
		printf("%d\n", ans[i]);
	return 0;
}
