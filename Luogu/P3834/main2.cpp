#include <vector>
#include <cctype>
#include <cstdio>
#include <cstdint>
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

using i32 = int32_t;
using i64 = int64_t;
using u32 = uint32_t;
using u64 = uint64_t;
using vi32 = std::vector<i32>;
using PII = std::pair<i32, i32>;
inline i32 lowbit(i32 x) { return x & -x; }
const int N = 2e5 + 10;

struct Query
{
	i32 id, l, r, k;
	Query(void) {}
	Query(i32 _i, i32 _l, i32 _r, i32 _k)
	{ id = _i, l = _l, r = _r, k = _k; }
};

i32 n, m;
i32 a[N], tr[N], ans[N];

void add(i32 x, i32 v)
{
	for (i32 i = x; i <= n; i += lowbit(i)) {
		tr[i] += v;
	}
}
i32 query(i32 x)
{
	i32 res = 0;
	for (i32 i = x; i; i -= lowbit(i)) {
		res += tr[i];
	}
	return res;
}
void calc(std::vector<Query> &q, std::vector<PII> &cg, i32 l, i32 r)
{
	if (!q.size()) {
		return;
	}
	if (l == r) {
		for (auto qu : q) {
			ans[qu.id] = l;
		}
		return;
	}
	i32 mid = l + r >> 1;
	std::vector<PII> cgl, cgr;
	for (auto pr : cg) {
		if (pr.second <= mid) {
			add(pr.first, 1);
			cgl.emplace_back(pr);
		}
		else {
			cgr.emplace_back(pr);
		}
	}
	std::vector<Query> ql, qr;
	for (auto qu : q) {
		i32 del = query(qu.r) - query(qu.l - 1);
		if (del >= qu.k) {
			ql.emplace_back(qu);
		}
		else {
			qu.k -= del;
			qr.emplace_back(qu);
		}
	}
	q.clear();
	cg.clear();
	for (auto pr : cgl) {
		add(pr.first, -1);
	}
	calc(ql, cgl, l, mid);
	calc(qr, cgr, mid + 1, r);
}

int main(void)
{
	//Think twice, code once.
	read >> n >> m;
	std::vector<PII> cg;
	for (int i = 1; i <= n; ++i) {
		read >> a[i];
		cg.emplace_back(i, a[i]);
	}
	std::vector<Query> q;
	for (int i = 1; i <= m; ++i) {
		i32 l, r, k;
		read >> l >> r >> k;
		q.emplace_back(i, l, r, k);
	}
	calc(q, cg, -1e9, 1e9);
	for (int i = 1; i <= m; ++i) {
		printf("%d\n", ans[i]);
	}
	return 0;
}
