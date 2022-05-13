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

int n, m;
char str[10][10];

int main(void)
{
	int T; read >> T;
	while (T--) {
		read >> n >> m;
		for (int i = 1; i <= n; ++i)
			scanf("%s", str[i] + 1);
		std::pair<int, int> robot = std::make_pair(-1, -1);
		bool have = 1;
		for (int i = 1; i <= n; ++i)
			if (have)
				for (int j = 1; j <= m; ++j)
					if (str[i][j] == 'R') {
						robot.first = i;
						robot.second = j;
						have = 0;
						break;
					}
		if (robot.first == -1) {
			puts("NO");
			continue;
		}
		bool flag = 1;
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= m; ++j)
				if (i < robot.first || j < robot.second)
					if (str[i][j] == 'R') {
						flag = 0;
						break;
					}
		puts(flag ? "YES" : "NO");
	}
	return 0;
}
