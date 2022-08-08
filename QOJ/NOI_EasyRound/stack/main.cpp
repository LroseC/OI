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
const int N = 4e5 + 11;

struct node
{
	i32 val, tag;
	friend node operator+(const node &a, const node &b)
	{
		node res;
		res.tag = 0;
		res.val = std::max(a.val, b.val);
		return res;
	}
};
struct query
{
	i32 id, val, pos, k;
	bool operator<(const query &other) const
	{ return pos < other.pos; }
};
struct operation
{
	i32 val, pos;
	bool operator<(const operation &other) const
	{ return pos < other.pos; }
};

i32 n, m;
i32 queryCnt, opCnt;
i32 ans[N], val[N];
node tr[N << 2];
operation op[N];
query q[N];

void addNode(i32 u, i32 val)
{
	tr[u].tag += val;
	tr[u].val += val;
}
void spread(i32 u)
{
	if (tr[u].tag) {
		addNode(u << 1, tr[u].tag);
		addNode(u << 1 | 1, tr[u].tag);
		tr[u].tag = 0;
	}
}
void add(i32 L, i32 R, i32 val, i32 u = 1, i32 l = 1, i32 r = m)
{
	if (L <= l && r <= R) {
		addNode(u, val);
		return;
	}
	spread(u);
	i32 mid = l + r >> 1;
	if (L <= mid) add(L, R, val, u << 1, l, mid);
	if (R > mid) add(L, R, val, u << 1 | 1, mid + 1, r);
	tr[u] = tr[u << 1] + tr[u << 1 | 1];
}
node query(i32 L, i32 R, i32 u = 1, i32 l = 1, i32 r = m)
{
	if (L <= l && r <= R)
		return tr[u];
	spread(u);
	i32 mid = l + r >> 1;
	if (L <= mid && R > mid)
		return query(L, R, u << 1, l, mid) + query(L, R, u << 1 | 1, mid + 1, r);
	else if (L <= mid)
		return query(L, R, u << 1, l, mid);
	else
		return query(L, R, u << 1 | 1, mid + 1, r);
}
i32 binarySearch(i32 L, i32 R, i32 K, i32 u = 1, i32 l = 1, i32 r = m)
{
	if (L <= l && r <= R) {
		if (tr[u].val < K) return -1;
		if (l == r) return l;
		i32 mid = l + r >> 1;
		spread(u);
		if (tr[u << 1 | 1].val >= K)
			return binarySearch(L, R, K, u << 1 | 1, mid + 1, r);
		else
			return binarySearch(L, R, K, u << 1, l, mid);
	}
	i32 mid = l + r >> 1;
	spread(u);
	i32 res;
	if (R > mid) {
		res = binarySearch(L, R, K, u << 1 | 1, mid + 1, r);
		if (res != -1) return res;
	}
	if (L <= mid) {
		res = binarySearch(L, R, K, u << 1, l, mid);
		if (res != -1) return res;
	}
	return -1;
}

int main(void)
{
	//Think twice, code once.
	read >> n >> m;
	for (int i = 1; i <= m; ++i) {
		int type; read >> type;
		if (type == 1) {
			i32 l, r;
			read >> l >> r >> val[i];
			opCnt += 1;
			op[opCnt].pos = l;
			op[opCnt].val = i;
			opCnt += 1;
			op[opCnt].pos = r + 1;
			op[opCnt].val = -i;
		}
		else if (type == 2) {
			i32 l, r;
			read >> l >> r;
			opCnt += 1;
			op[opCnt].pos = l;
			op[opCnt].val = -i;
			opCnt += 1;
			op[opCnt].pos = r + 1;
			op[opCnt].val = i;
		}
		else {
			queryCnt += 1;
			q[queryCnt].id = queryCnt;
			q[queryCnt].val = i;
			read >> q[queryCnt].pos >> q[queryCnt].k;
		}
	}
	std::sort(op + 1, op + 1 + opCnt);
	std::sort(q + 1, q + 1 + queryCnt);
	for (int i = 1, j = 1; i <= queryCnt; ++i) {
		while (j <= opCnt && op[j].pos <= q[i].pos) {
			if (op[j].val > 0)
				add(1, op[j].val, 1);
			else
				add(1, -op[j].val, -1);
			j += 1;
		}
		ans[q[i].id] = binarySearch(1, q[i].val, q[i].k + query(q[i].val, q[i].val).val);
	}
	for (int i = 1; i <= queryCnt; ++i) {
		if (ans[i] == -1) puts("Error");
		else printf("%d\n", val[ans[i]]);
	}
	return 0;
}
