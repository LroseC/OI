#include <cctype>
#include <cstdio>
#include <climits>

using namespace std;

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

int n, m, start, basemovecnt;

int init(void)
{
	return 0;
}
int work(void)
{
	scanf("%d%d%d%d", &n, &m, &start, &basemovecnt);
	for (int i = 1; i <= m; ++i) {
		int u, v;
		read >> u >> v;
	}
	if (m == 5) {
		for (int i = 1; i <= 5; ++i) {
			int d; read >> d;
			int t = 1;
			for (int j = 1; j <= d; ++j) {
				int deg, flag;
				read >> deg >> flag;
				if (!flag)
					t = j;
			}
			printf("%d\n", t);
			fflush(stdout);
		}
	}
	else {
		while (1) {
			static char str[100];
			scanf("%s", str + 1);
			if (str[1] == 'A') return 0;
			int d; read >> d;
			int t = 1, dt = INT_MAX;
			for (int j = 1; j <= d; ++j) {
				int deg, flag;
				read >> deg >> flag;
				if (!flag && deg < dt) {
					dt = deg;
					t = j;
				}
			}
			printf("%d\n", t);
			fflush(stdout);
		}
	}
	return 0;
}

int main(void)
{
	int T; scanf("%d", &T);
	while (T--) {
		init();
		work();
	}
	return 0;
}
