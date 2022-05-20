#include <cctype>
#include <cstdio>

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

int main(void)
{
	read >> n >> m;
	build();
	int op, l, r, l2, r2;
	while (m--) {
		read >> op;
		if (op == 0) {
			read >> l >> r;
			cover(0, l, r);
		}
		else if (op == 1) {
			read >> l >> r >> l2 >> r2;
			int cnt = queryCnt(l, r);
			cover(0, l, r);
			int r3 = binarySearch(l2, r2, cnt);
			cover(1, l2, r3);
		}
	}
	return 0;
}
