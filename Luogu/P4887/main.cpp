#include <vector>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <functional>

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
const int S = 1 << 14, N = 1e5 + 10, B = 316;
inline int lowbit(int x) { return x & -x; }

struct Scan
{
	int id, l, r, f;
	Scan(int _id, int _l, int _r, int _f) { id = _id, l = _l, r = _r, f = _f; }
};
struct Query
{
	int id, l, r;
	bool operator<(const Query &other)
	{
		if (l / B != other.l / B) return l < other.l;
		return (l / B & 1) ? r < other.r : r > other.r;
	}
};

int n, m, K;
int a[N];
i64 cnt[N], prefix[N], ans[N], res[N];
std::vector<Scan> scan[N];
std::vector<int> Knum;

int popcount(int x)
{
	int res = 0;
	while (x) {
		++res;
		x -= lowbit(x);
	}
	return res;
}

void init(void)
{
	for (int i = 1; i <= n; ++i) {
		prefix[i] = cnt[a[i]];
		for (int t : Knum)
			++cnt[a[i] ^ t];
	}
	memset(cnt, 0, sizeof cnt);
}
void calc(void)
{
	for (int i = 1; i <= n; ++i) {
		for (int t : Knum)
			++cnt[a[i] ^ t];
		for (auto t : scan[i]) {
			for (int j = t.l; j <= t.r; ++j)
				ans[t.id] += t.f * cnt[a[j]];
		}
	}
	memset(cnt, 0, sizeof cnt);
	for (int i = 1; i < m; ++i) ans[i] += ans[i - 1];
}

int main(void)
{
	read >> n >> m >> K;
	if (K >= 14) {
		for (int i = 1; i <= m; ++i)
			puts("0");
		return 0;
	}
	for (int i = 1; i <= n; ++i)
		read >> a[i];
	for (int i = 0; i < S; ++i)
		if (popcount(i) == K) Knum.emplace_back(i);
	init();

	std::vector<Query> q(m);
	for (int i = 0; i < m; ++i) {
		q[i].id = i;
		read >> q[i].l >> q[i].r;
	}
//	std::sort(q.begin(), q.end());
	int L = 1, R = 0;
	for (int i = 0; i < m; ++i) {
		if (L > q[i].l) {
			scan[q[i].r].emplace_back(i, q[i].l, L - 1, +1);
			while (L > q[i].l)
				ans[i] -= prefix[--L];
		}
		if (R < q[i].r) {
			scan[q[i].l - 1].emplace_back(i, R + 1, q[i].r, -1);
			while (R < q[i].r)
				ans[i] += prefix[++R];
		}
		if (L < q[i].l) {
			scan[q[i].r].emplace_back(i, L, q[i].l - 1, -1);
			while (L < q[i].l)
				ans[i] += prefix[L++];
		}
		if (R > q[i].r) {
			scan[q[i].l - 1].emplace_back(i, q[i].r + 1, R, +1);
			while (R > q[i].r)
				ans[i] -= prefix[R--];
		}
	}
	for (int i = 0; i < m; ++i)
		printf("%lld ", ans[i]);
	puts("");
	calc();
	for (int i = 0; i < m; ++i)
		res[q[i].id] = ans[i];
	for (int i = 0; i < m; ++i)
		printf("%lld\n", res[i]);
	return 0;
}
