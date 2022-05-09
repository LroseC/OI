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

i64 pw10[11];

int calc(int L, int R)
{
	int res = 0;
	int mid;
	for (int i = 1; i <= 10; ++i)
		if (pw10[i - 1] <= R && R < pw10[i]) {
			mid = pw10[i - 1];
			break;
		}
	if (R / mid > 1)
		return R - std::max(L, mid) + 1;
	int left = std::max(R / 10 + 1, R - mid + 1);
	L = std::max(L, left);
	return R - L + 1;
}

int main(void)
{
	int T; read >> T;
	pw10[0] = 1;
	for (int i = 1; i <= 10; ++i)
		pw10[i] = pw10[i - 1] * 10;
	while (T--) {
		int L, R;
		read >> L >> R;
		printf("%d\n", calc(L, R));
	}
	return 0;
}
