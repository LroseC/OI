#include <vector>
#include <cctype>
#include <cstdio>
#include <climits>
#include <cstring>
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
using vi32 = std::vector<i32>;
using PII = std::pair<i32, i32>;
const int N = 2e5 + 10;

struct query
{
	i32 op, l, r, val;
};
struct node
{
	i32 l, r;
	i32 hisTag, tag;
	i32 hisMax, val;
	bool hvhsTg, hvTg;
};

i32 n, m, queryCnt;
i32 ans[N];
query q[N];
i32 idx;
i32 root[N];
i32 sum[N];
node tr[i32(1e7 + 10)];

i32 clone(i32 v)
{
	i32 u = ++idx;
	tr[u] = tr[v];
	return u;
}
void addMax(i32 u, i32 v)
{
	tr[u].hvhsTg = 1;
	tr[u].hisTag += v;
	tr[u].hisMax = std::max(tr[u].hisMax, tr[u].val + v);
}
void addNode(i32 u, i32 v)
{
	tr[u].hvTg = 1;
	tr[u].val += v;
	tr[u].tag += v;
	tr[u].hisMax = std::max(tr[u].hisMax, tr[u].val);
	tr[u].hisTag = std::max(tr[u].hisTag, tr[u].tag);
}
void spread(i32 u)
{
	tr[u].l = clone(tr[u].l);
	tr[u].r = clone(tr[u].r);
	if (tr[u].hvhsTg) {
		addMax(tr[u].l, tr[u].hisTag);
		addMax(tr[u].r, tr[u].hisTag);
		tr[u].hisTag = 0;
		tr[u].hvhsTg = 0;
	}
	if (tr[u].hvTg) {
		addNode(tr[u].l, tr[u].tag);
		addNode(tr[u].r, tr[u].tag);
		tr[u].tag = 0;
		tr[u].hvTg = 0;
	}
}

i32 add(i32 L, i32 R, i32 val, i32 v, i32 l = 1, i32 r = n)
{
	i32 u = clone(v);
	if (L <= l && r <= R) {
		addNode(u, val);
		return u;
	}
	i32 mid = l + r >> 1;
	spread(u);
	if (L <= mid)
		tr[u].l = add(L, R, val, tr[u].l, l, mid);
	if (R > mid)
		tr[u].r = add(L, R, val, tr[u].r, mid + 1, r);
	return u;
}
node query(i32 pos, i32 u, i32 l = 1, i32 r = n)
{
	if (l == r)
		return tr[u];
	i32 mid = l + r >> 1;
	spread(u);
	if (pos <= mid)
		return query(pos, tr[u].l, l, mid);
	else
		return query(pos, tr[u].r, mid + 1, r);
}

int main(void)
{
	//Think twice, code once.
	read >> n >> m;
	tr[0].hisMax = 0xcfcfcfcf;
	for (int i = 1; i <= m; ++i) {
		read >> q[i].op;
		if (q[i].op == 1) {
			read >> q[i].l >> q[i].r >> q[i].val;
		}
		else if (q[i].op == 2) {
			read >> q[i].l >> q[i].r;
		}
		else {
			q[i].r = ++queryCnt;
			read >> q[i].l >> q[i].val;
		}
	}
	std::reverse(q + 1, q + 1 + m);
	for (int i = 1; i <= m; ++i) {
		if (q[i].op == 1)
			root[i] = add(q[i].l, q[i].r, 1, root[i - 1]);
		else if (q[i].op == 2)
			root[i] = add(q[i].l, q[i].r, -1, root[i - 1]);
		else
			root[i] = root[i - 1];
	}
	for (int i = 1; i <= m; ++i) {
		if (q[i].op == 3) {
			if (query(q[i].l, root[m]).hisMax - query(q[i].l, root[i]).val < q[i].val)
				ans[q[i].r] = -1;
			else {
				i32 l = i, r = m;
				while (l < r) {
					i32 mid = l + r >> 1;
					if (query(q[i].l, root[mid]).hisMax - query(q[i].l, root[i]).val >= q[i].val)
						r = mid;
					else
						l = mid + 1;
				}
				ans[q[i].r] = l;
			}
		}
	}
	for (int i = 1; i <= queryCnt; ++i) {
		if (ans[i] == -1)
			puts("Error");
		else {
			if (q[ans[i]].op != 
			printf("%d\n", q[ans[i]].val);
		}
	}
	return 0;
}
