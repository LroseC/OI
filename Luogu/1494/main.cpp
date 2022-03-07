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

const int N = 5e4 + 10, B = 223;
using i64 = long long;
inline int getid(int x) { return x / B; }

struct Query
{
	int id, l, r;
	bool operator<(const Query &other)
	{
		if (getid(l) == getid(other.l))
			return r < other.r;
		return l < other.l;
	}
};

int n, m;
int color[N], cnt[N];
Query q[N];
std::pair<int, int> ans[N];

i64 gcd(i64 a, i64 b) { return b ? gcd(b, a % b) : a; }
void Add(int x, i64 &son)
{
	son += cnt[color[x]];
	++cnt[color[x]];
}
void Dec(int x, i64 &son)
{
	--cnt[color[x]];
	son -= cnt[color[x]];
}

int main(void)
{
	read >> n >> m;
	for (int i = 1; i <= n; ++i)
		read >> color[i];
	for (int i = 1; i <= m; ++i) {
		q[i].id = i;
		read >> q[i].l >> q[i].r;
	}
	std::sort(q + 1, q + m + 1);
	int L = 1, R = 0;
	i64 son = 0;
	for (int i = 1; i <= m; ++i) {
		while (L > q[i].l) Add(--L, son);
		while (R < q[i].r) Add(++R, son);
		while (L < q[i].l) Dec(L++, son);
		while (R > q[i].r) Dec(R--, son);
		if (son == 0)
			ans[q[i].id] = std::make_pair(0ll, 1ll);
		else {
			i64 len = R - L + 1;
			i64 mother = len * (len - 1) / 2;
			i64 d = gcd(son, mother);
			ans[q[i].id] = std::make_pair(son / d, mother / d);
		}
	}
	for (int i = 1; i <= m; ++i)
		printf("%lld/%lld\n", ans[i].first, ans[i].second);
	return 0;
}
