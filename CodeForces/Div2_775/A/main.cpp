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
		while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
		res = res * f; return *this;
	}
} read;

using i64 = long long;

int main(void)
{
	int T; read >> T;
	while (T--) {
		int n; read >> n;
		std::vector<int> pos(n);
		bool flag = 1;
		for (int i = 0; i < n; ++i) {
			read >> pos[i];
			if (pos[i] == 0) flag = 0;
		}
		if (flag) {
			puts("0");
			continue;
		}
		int lst = 0;
		for (int i = 0; i < n; ++i)
			if (pos[i] == 0) {
				lst = i - 1;
				break;
			}
		for (int i = n - 1; i >= 0; --i)
			if (pos[i] == 0) {
				printf("%d\n", i + 1 - lst);
				break;
			}
	}
	return 0;
}
