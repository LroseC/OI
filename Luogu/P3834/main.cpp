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
const int N = 2e5 + 10;

struct node
{
	i32 l, r;
	i32 sum;
};

i32 n, m, idx;
node tr[N << 5];
i32 root[N];

i32 clone(i32 u)
{
	idx += 1;
	tr[idx] = tr[u];
	return idx;
}
i32 insert(i32 u, i32 pos, i32 v, i32 l = -1e9, i32 r = 1e9)
{
	u = clone(u);
	if (l == r) {
		tr[u].sum += v;
		return u;
	}
	i32 mid = l + r >> 1;
	if (pos <= mid) {
		tr[u].l = insert(tr[u].l, pos, v, l, mid);
	}
	else {
		tr[u].r = insert(tr[u].r, pos, v, mid + 1, r);
	}
	tr[u].sum = tr[tr[u].l].sum + tr[tr[u].r].sum;
	return u;
}
i32 query(i32 u, i32 v, i32 k, i32 l = -1e9, i32 r = 1e9)
{
	if (l == r) {
		return l;
	}
	i32 mid = l + r >> 1;
	if (tr[tr[u].l].sum - tr[tr[v].l].sum >= k) {
		return query(tr[u].l, tr[v].l, k, l, mid);
	}
	else {
		k -= tr[tr[u].l].sum - tr[tr[v].l].sum;
		return query(tr[u].r, tr[v].r, k, mid + 1, r);
	}
}

int main(void)
{
	//Think twice, code once.
	read >> n >> m;
	for (int i = 1; i <= n; ++i) {
		i32 x; read >> x;
		root[i] = insert(root[i - 1], x, 1);
	}
	while (m--) {
		i32 l, r, k;
		read >> l >> r >> k;
		printf("%d\n", query(root[r], root[l - 1], k));
	}
	return 0;
}
