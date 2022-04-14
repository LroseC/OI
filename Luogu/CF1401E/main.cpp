#include <vector>
#include <cctype>
#include <cstdio>
#include <algorithm>

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
const int M = 1e6 + 10;
inline int lowbit(int x) { return x & -x; }

int n, m;
std::vector< std::pair<int, int> > op[M], q[M];
int tr[M];

void add(int pos, int x)
{
	++pos;
	for (int i = pos; i < M; i += lowbit(i))
		tr[i] += x;
}
int query(int pos)
{
	++pos;
	int res = 0;
	for (int i = pos; i; i -= lowbit(i))
		res += tr[i];
	return res;
}

int main(void)
{
	read >> n >> m;
	i64 res = 1;
	for (int i = 1; i <= n; ++i) {
		int pos, l, r;
		read >> pos >> l >> r;
		res += (l == 0 && r == 1e6);
		op[l].emplace_back(pos, 1);
		op[r + 1].emplace_back(pos, -1);
	}
	for (int i = 1; i <= m; ++i) {
		int pos, l, r;
		read >> pos >> l >> r;
		res += (l == 0 && r == 1e6);
		q[pos].emplace_back(std::make_pair(l, r));
	}
	for (int i = 0; i <= 1e6; ++i) {
		for (auto t : op[i])
			add(t.first, t.second);
		for (auto t : q[i])
			res += query(t.second) - query(t.first - 1);
	}
	printf("%lld\n", res);
	return 0;
}
