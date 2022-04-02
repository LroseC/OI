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

const int N = 1e5 + 10;

int n, m;
char str[N];

bool check(int l, int r, int L, int R)
{
	if (r - l + 1 > R - L + 1)
		return 0;
	for (int i = L; i + r - l <= R; ++i) {
		bool flag = 1;
		for (int j = 0; j < r - l + 1; ++j)
			if (str[i + j] != str[l + j]) {
				flag = 0;
				break;
			}
		if (flag)
			return 1;
	}
	return 0;
}

int main(void)
{
//	freopen("cutting.in", "r", stdin);
//	freopen("cutting.out", "w", stdout);
	read >> n >> m;
	scanf("%s", str + 1);
	for (int t = 1; t <= m; ++t) {
		int L, R, res = 0;
		read >> L >> R;
		for (int i = 1; i <= n; ++i)
			for (int j = i + 2; j <= n; ++j)
				res += (check(L, R, 1, i) || check(L, R, i + 1, j - 1) || check(L, R, j, n));
		printf("%d\n", res);
	}
	return 0;
}
