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
		while (isdigit(ch)) { res = res * 10 + (ch - '0') * f; ch = getchar(); }
		return *this;
	}
} read;

using i64 = long long;
const int N = 2e5, LG = 18;

struct stTable
{
	int size;
	int st[LG][N], lg2[N];
	void build(std::vector<int> &o)
	{
		size = o.size();
		lg2[1] = 0;
		for (int i = 2; i < size; ++i) {
			lg2[i] = lg2[i >> 1] + 1;
		}
		for (int i = 0; i < size; ++i) {
			st[0][i] = o[i];
		}
		for (int j = 1; j < LG; ++j) {
			for (int i = 0; i + (1 << j) - 1 < size; ++i)
				st[j][i] = std::__gcd(st[j - 1][i], st[j - 1][i + (1 << j - 1)]);
		}
	}
	int query(int L, int R)
	{
		int o = lg2[R - L + 1];
		return std::__gcd(st[o][L], st[o][R - (1 << o) + 1]);
	}
} sta, stb;

int main(void)
{
	int n, m;
	read >> n >> m;
	std::vector<int> a(n), b(n), decA(n - 1), decB(n - 1);
	for (int i = 0; i < n; ++i) {
		read >> a[i];
	}
	for (int i = 0; i < n; ++i) {
		read >> b[i];
	}
	for (int i = 0; i < n - 1; ++i) {
		decA[i] = abs(a[i + 1] - a[i]);
		decB[i] = abs(b[i + 1] - b[i]);
	}
	sta.build(decA);
	stb.build(decB);
	for (int i = 0; i < m; ++i) {
		int l1, r1, l2, r2;
		read >> l1 >> r1 >> l2 >> r2;
		--l1, --r1, --l2, --r2;
		int res = a[l1] + b[l2];
		if (l1 < r1)
			res = std::__gcd(res, sta.query(l1, r1 - 1));
		if (l2 < r2)
			res = std::__gcd(res, stb.query(l2, r2 - 1));
		printf("%d\n", res);
	}
	return 0;
}
