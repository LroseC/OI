#include <vector>
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
		int n; read >> n;
		std::vector<int> a(n);
		int oddCnt = 0;
		for (int i = 0; i < n; ++i) {
			read >> a[i];
			if (a[i] & 1) ++oddCnt;
		}
		int o = 0x3f3f3f;
		int res = n - oddCnt - (oddCnt == 0);
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < 31; ++j)
				if (a[i] >> j & 1) {
					o = std::min(o, j);
					break;
				}
		}
		printf("%d\n", res + o);
	}
	return 0;
}
