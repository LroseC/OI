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

int digit[100];

int main(void)
{
	int T; read >> T;
	while (T--) {
		int n; read >> n;
		int len = 0;
		while (n) {
			digit[++len] = n % 10;
			n /= 10;
		}
		if (len <= 2)
			printf("%d\n", digit[1]);
		else {
			int res = 10;
			for (int i = 1; i <= len; ++i)
				res = std::min(res, digit[i]);
			printf("%d\n", res);
		}
	}
	return 0;
}
