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

int main(void)
{
	int T; read >> T;
	while (T--) {
		int l1, r1, l2, r2;
		read >> l1 >> r1 >> l2 >> r2;
		int left = std::max(l1, l2);
		int right = std::min(r1, r2);
		if (left <= right)
			printf("%d\n", left);
		else
			printf("%d\n", l1 + l2);
	}
	return 0;
}
