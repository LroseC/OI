#include <vector>
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
using PII = std::pair<int, int>;
const int N = 110;

char a[N], b[N];

int main(void)
{
	int tt; read >> tt;
	while (tt--) {
		int n, m, K;
		read >> n >> m >> K;
		scanf("%s", a + 1);
		scanf("%s", b + 1);
		std::sort(a + 1, a + 1 + n);
		std::sort(b + 1, b + 1 + m);
		int i = 1, j = 1;
		int tima = 0, timb = 0;
		while (i <= n && j <= m) {
			bool flg = a[i] < b[j];
			if (flg && tima == K) flg = 0;
			if (!flg && timb == K) flg = 1;
			if (flg) {
				putchar(a[i]);
				++i;
				++tima;
				timb = 0;
			}
			else {
				putchar(b[j]);
				++j;
				++timb;
				tima = 0;
			}
		}
		putchar('\n');
	}
	return 0;
}
