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

i32 n, m;
i32 v[N];

namespace sub1
{
	i32 main(void)
	{
		while (m--) {
			i32 op, l, r;
			read >> op >> l >> r;
			if (op == 1) {
				i32 x; read >> x;
				for (int i = l; i <= r; ++i)
					v[i] &= x;
			}
			else if (op == 2) {
				i32 x; read >> x;
				for (int i = l; i <= r; ++i)
					v[i] |= x;
			}
			else {
				i32 mx = 0;
				for (int i = l; i <= r; ++i)
					mx = std::max(mx, v[i]);
				printf("%d\n", mx);
			}
		}
		return 0;
	}
}

int main(void)
{
#ifndef DEBUG
	freopen("sequence.in", "r", stdin);
	freopen("sequence.out", "w", stdout);
#endif
	//Think twice, code once.
	read >> n >> m;
	i32 maxv = 0;
	for (int i = 1; i <= n; ++i) {
		read >> v[i];
		maxv = std::max(maxv, v[i]);
	}
	if (n * m <= 3e7) {
		sub1::main();
		return 0;
	}
	/*
	for (int i = 1; i <= m; ++i) {
		read >> cg[i].op >> cg[i].l >> cg[i].r;
		if (cg[i].op != 3) {
			read >> cg[i].v;
			maxv = std::max(maxv, cg[i].v);
		}
	}
	*/
	return 0;
}
