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
	int id, l, r, pos, f;

	Scan(int _id, int _l, int _r, int _pos, int _f) { id = _id, l = _l, r = _r, pos = _pos, f = _f; }
	bool operator<(const Scan &other) const
	{
		return pos < other.pos;
	}
	bool operator>(const Scan &other) const
	{
		return pos > other.pos;
	}
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
int a[N], cnt[N];
i64 prefix[N], ans[N], res[N];
std::vector<Scan> scan;
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
		for (int t : Knum)
			prefix[i] += cnt[a[i] ^ t];
		++cnt[a[i]];
	}
	memset(cnt, 0, sizeof cnt);
}
void calc(void)
{
	std::sort(scanpre.begin(), scanpre.end(), std::less<Scan>());
	for (int i = 1, j = 0; i <= n; ++i) {
		for (int t : Knum)
			++cnt[a[i] ^ t];
		while (j < scanpre.size() && scanpre[j].pos == i) {
			for (int k = scanpre[j].l; k <= scanpre[j].r; ++k)
				ans[scanpre[j].id] += scanpre[j].f * cnt[a[k]];
			++j;
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
	std::sort(q.begin(), q.end());
	int L = 1, R = 0;
	for (int i = 0; i < m; ++i) {
		if (L > q[i].l) {
			scan.emplace_back(i, q[i].l, L - 1, q[i].r + 1, -1);
			while (L > q[i].l)
				ans[i] += suffix[--L];
		}
		if (R < q[i].r) {
			scan.emplace_back(i, R + 1, q[i].r, q[i].l - 1, -1);
			while (R < q[i].r)
				ans[i] += prefix[++R];
		}
		if (L < q[i].l) {
			scan.emplace_back(i, L, q[i].l - 1, q[i].r + 1, +1);
			while (L < q[i].l)
				ans[i] -= suffix[L++];
		}
		if (R > q[i].r) {
			scan.emplace_back(i, q[i].r + 1, R, q[i].l - 1, +1);
			while (R > q[i].r)
				ans[i] -= prefix[R--];
		}
	}
	calc();
	for (int i = 0; i < m; ++i)
		res[q[i].id] = ans[i];
	for (int i = 0; i < m; ++i)
		printf("%lld\n", res[i]);
	return 0;
}
