#include <vector>
#include <random>
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
const int N = 1e5 + 10, M = 1e6 + 10;
std::random_device srd;
std::mt19937 rd(srd());

struct node
{
	i32 l, r;
	i32 val, sz;
};

i32 n, m, idx, root;
node tr[N + M];

i32 get(i32 val)
{
	idx += 1;
	tr[idx].sz = 1;
	tr[idx].val = val;
	tr[idx].l = tr[idx].r = 0;
	return idx;
}
void maintain(i32 u)
{ tr[u].sz = tr[tr[u].l].sz + tr[tr[u].r].sz + 1; }
PII split(i32 u, i32 val)
{
	PII t = std::make_pair(0, 0);
	if (!u) return t;
	if (tr[u].val <= val) {
		t = split(tr[u].r, val);
		tr[u].r = t.first;
		t.first = u;
	}
	else {
		t = split(tr[u].l, val);
		tr[u].l = t.second;
		t.second = u;
	}
	maintain(u);
	return t;
}
i32 merge(i32 x, i32 y)
{
	if (!x || !y) return x + y;
	i32 t = rd();
	if (std::abs(t) % (tr[x].sz + tr[y].sz) < tr[x].sz) {
		tr[x].r = merge(tr[x].r, y);
		maintain(x);
		return x;
	}
	else {
		tr[y].l = merge(x, tr[y].l);
		maintain(y);
		return y;
	}
}
void insert(i32 val)
{
	auto t = split(root, val);
	root = merge(t.first, merge(get(val), t.second));
}
void remove(i32 val)
{
	auto x = split(root, val - 1);
	auto y = split(x.second, val);
	y.first = merge(tr[y.first].l, tr[y.first].r);
	root = merge(x.first, merge(y.first, y.second));
}
i32 getRk(i32 val)
{
	auto x = split(root, val - 1);
	i32 res = tr[x.first].sz;
	root = merge(x.first, x.second);
	return res + 1;
}
i32 getVal(i32 k)
{
	i32 rk = 0, u = root;
	while (rk + tr[tr[u].l].sz + 1 != k) {
		if (rk + tr[tr[u].l].sz + 1 < k) {
			rk += tr[tr[u].l].sz + 1;
			u = tr[u].r;
		}
		else {
			u = tr[u].l;
		}
	}
	return u;
}
i32 prev(i32 val)
{
	auto t = split(root, val - 1);
	i32 u = t.first;
	while (tr[u].r) u = tr[u].r;
	root = merge(t.first, t.second);
	return tr[u].val;
}
i32 next(i32 val)
{
	auto t = split(root, val);
	i32 u = t.second;
	while (tr[u].l) u = tr[u].l;
	root = merge(t.first, t.second);
	return tr[u].val;
}

int main(void)
{
	//Think twice, code once.
	read >> n >> m;
	for (int i = 1; i <= n; ++i) {
		i32 x;
		read >> x;
		insert(x);
	}
	i32 lastans = 0;
	i32 res = 0;
	while (m--) {
		i32 op, x;
		read >> op >> x;
		x ^= lastans;
		switch (x) {
			case 1:
				insert(x);
				break;
			case 2:
				remove(x);
				break;
			case 3:
				lastans = getRk(x);
				res ^= lastans;
				break;
			case 4:
				lastans = getVal(x);
				res ^= lastans;
				break;
			case 5:
				lastans = prev(x);
				res ^= lastans;
				break;
			case 6:
				lastans = next(x);
				res ^= lastans;
				break;
		}
	}
	printf("%d\n", res);
	return 0;
}
