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
	int tt; read >> tt;
	while (tt--) {
		int x; read >> x;
		int res = x & -x;
		if (res != x) {
			printf("%d\n", res);
		}
		else {
			if (res == 1)
				printf("%d\n", 3);
			else
				printf("%d\n", res | 1);
		}
	}
	return 0;
}
