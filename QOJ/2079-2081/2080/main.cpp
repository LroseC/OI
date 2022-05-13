#include <cctype>
#include <cstdio>
#include <climits>
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
const int N = 1010;

int n;
bool isFull[N];
char str[N][N];

int main(void)
{
	read >> n;
	for (int i = 1; i <= n; ++i)
		scanf("%s", str[i] + 1);

	int blackCnt = 0;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			if (str[i][j] == '#') ++blackCnt;
	if (blackCnt == 0) {
		puts("-1");
		return 0;
	}

	int fullCnt = 0;
	for (int j = 1; j <= n; ++j) {
		isFull[j] = 1;
		for (int i = 1; i <= n; ++i)
			if (str[i][j] != '#') isFull[j] = 0;
		if (isFull[j])
			++fullCnt;
	}
	int ans = INT_MAX;
	for (int i = 1; i <= n; ++i) {
		bool haveBlack = 0;
		for (int j = 1; j <= n; ++j)
			if (str[j][i] == '#') {
				haveBlack = 1;
				break;
			}
		int res = 0;
		if (!haveBlack) ++res;
		for (int j = 1; j <= n; ++j)
			if (str[i][j] != '#') ++res;
		res += (n - fullCnt);
		ans = std::min(ans, res);
	}
	printf("%d\n", ans);
	return 0;
}
