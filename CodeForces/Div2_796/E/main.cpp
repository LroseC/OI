#include <cctype>
#include <cstdio>
#include <algorithm>
#include <functional>

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
const int N = 210, M = 510;

int n, m, totW;
int w[M], e[M];
char str[M];

int main(void)
{
	read >> n >> m;
	for (int i = 1; i <= m; ++i) {
		printf("? ");
		for (int j = 1; j <= m; ++j) {
			putchar(j == i ? '1' : '0');
		}
		putchar('\n');
		fflush(stdout);
		read >> w[i];
	}
	printf("? ");
	for (int i = 1; i <= m; ++i) {
		putchar('1');
	}
	putchar('\n');
	fflush(stdout);
	read >> totW;
	for (int i = 1; i <= m; ++i) {
		e[i] = i;
	}
	auto cmp = [](int a, int b) { return w[a] > w[b]; };
	std::sort(e + 1, e + 1 + m, cmp);
	for (int i = 1; i <= m; ++i) {
		str[i] = '1';
	}
	for (int i = 1; i < m; ++i) {
		str[e[i]] = '0';
		printf("? %s\n", str + 1);
		fflush(stdout);
		int tmp; read >> tmp;
		if (tmp != totW - w[e[i]]) {
			totW = tmp;
		}
		else {
			str[e[i]] = '1';
		}
	}
	printf("! %d\n", totW);
	fflush(stdout);
	return 0;
}
