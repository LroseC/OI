#include <cctype>
#include <cstdio>

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
const int N = 1e5 + 10;

int n, m;
i64 cnt[N];

int main(void)
{
	read >> n >> m;
	for (int i = 1; i <= n; ++i)
		read >> type[i];
	for (int i = 1; i <= m; ++i) {
		q[i].id = i;
		read >> q[i].l >> q[i].r;
	}
	std::sort(q + 1, q + 1 + m);

	int L, R; i64 res;
	for (int i = 1; i <= m; ++i) {
		if (i == 1 || q[i].l / B != q[i - 1].l / B) {
			res = 0;
			L = q[i].l / B * B + B;
			R = L - 1;
		}
		if (q[i].l / B == q[i].r / B) {
			i64 res = 0;
			for (int j = q[i].l; j <= q[i].r; ++j)
				Add(j, res);
			ans[q[i].id] = res;
			for (int j = q[i].l; j <= q[i].r; ++j)
				Dec(j);
		}
		else {
			while (R < q[i].r) Add(++R, res);
			i64 tmp = res;
			for (int j = L; j >= q[i].l; --j) Add(j, res);
			ans[q[i].id] = res;
			res = tmp;
		}
	}
	return 0;
}
