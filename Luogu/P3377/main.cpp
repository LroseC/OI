#include <vector>
#include <cctype>
#include <cstdio>
#include <random>
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
const int N = 1e5 + 10;

struct node
{
	i32 l, r, dis;
};

i32 n, m;
node tr[N];
i32 val[N], fa[N], del[N];

i32 merge(i32 x, i32 y)
{
	if (!x || !y) return x + y;
	if (val[x] >= val[y]) std::swap(x, y);
	if (val[x] == val[y] && x > y) std::swap(x, y);
	tr[x].r = merge(tr[x].r, y);
	if (tr[tr[x].l].dis < tr[tr[x].r].dis) {
		std::swap(tr[x].l, tr[x].r);
	}
	tr[x].dis = tr[tr[x].r].dis + 1;
	return x;
}
i32 find(i32 x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
int main(void)
{
	//Think twice, code once.
	read >> n >> m;
	for (int i = 1; i <= n; ++i) {
		read >> val[i];
		fa[i] = i;
		tr[i].dis = 1;
	}
	while (m--) {
		i32 op; read >> op;
		if (op == 1) {
			i32 x, y;
			read >> x >> y;
			if (del[x] || del[y] || find(x) == find(y)) {
				continue;
			}
			x = find(x);
			y = find(y);
			fa[x] = fa[y] = merge(x, y);
		}
		else {
			i32 x; read >> x;
			if (del[x]) {
				puts("-1");
				continue;
			}
			x = find(x);
			del[x] = 1;
			printf("%d\n", val[x]);
			fa[tr[x].l] = fa[tr[x].r] = fa[x] = merge(tr[x].l, tr[x].r);
		}
	}
	return 0;
}
