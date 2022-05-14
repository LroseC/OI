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
const int N = 2e5 + 10;

int n;
char str[3][N];
int f[N][3];

void solve(void)
{
	read >> n;
	scanf("%s", str[1] + 1);
	scanf("%s", str[2] + 1);
	int begin, end;
	for (int i = 1; i <= n; ++i)
		if (str[1][i] == '*' || str[2][i] == '*') {
			begin = i;
			break;
		}
	for (int i = n; i >= 1; --i)
		if (str[1][i] == '*' || str[2][i] == '*') {
			end = i;
			break;
		}
	f[begin][1] = f[begin][2] = 1;
	if (str[1][begin] == '*' && str[2][begin] == '*')
		f[begin][1] = f[begin][2] = 1;
	else {
		if (str[1][begin] == '*')
			f[begin][1] = 0;
		if (str[2][begin] == '*')
			f[begin][2] = 0;
	}
	for (int i = begin + 1; i <= end; ++i) {
		if (str[1][i] == '*' && str[2][i] == '*')
			f[i][1] = f[i][2] = std::min(f[i - 1][1], f[i - 1][2]) + 2;
		else if (str[1][i] == '.' && str[2][i] == '.') {
			f[i][1] = std::min(f[i - 1][1], f[i - 1][2] + 1) + 1;
			f[i][2] = std::min(f[i - 1][1] + 1, f[i - 1][2]) + 1;
		}
		else {
			if (str[1][i] == '*') {
				f[i][1] = std::min(f[i - 1][1], f[i - 1][2] + 1) + 1;
				f[i][2] = std::min(f[i - 1][1], f[i - 1][2]) + 2;
			}
			if (str[2][i] == '*') {
				f[i][1] = std::min(f[i - 1][1], f[i - 1][2]) + 2;
				f[i][2] = std::min(f[i - 1][1] + 1, f[i - 1][2]) + 1;
			}
		}
	}
	printf("%d\n", std::min(f[end][1], f[end][2]));
}

int main(void)
{
	int T; read >> T;
	while (T--)
		solve();
	return 0;
}
