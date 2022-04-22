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
	int T; read >> T;
	while (T--) {
		int n; read >> n;
		double res = 1;
		for (int i = 1; i < n; ++i)
			res += 1.0 * n / (n - i);
		printf("%.2lf\n", res);
	}
	return 0;
}
