#include <cctype>
#include <cstdio>
#include <algorithm>

using namespace std;

typedef long long LL;

inline LL read(void)
{
	LL res = 0, f = 1; char ch = getchar();
	while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
	while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
	return res * f;
}

int main(void)
{
	int T = read();
	while (T--) {
		LL ans = 0;
		LL n2 = read(), n3 = read(), n4 = read();
		LL num = min(n3 >> 1, n4);
		ans += num;
		n3 -= num << 1, n4 -= num;
		num = min(n4 >> 1, n2);
		ans += num;
		n4 -= num << 1, n2 -= num;
		num = min(n3 >> 1, n2 >> 1);
		ans += num;
		n3 -= num << 1, n2 -= num << 1;
		num = min(n4, n2 / 3);
		ans += num;
		n4 -= num, n2 -= num * 3;
		num = n2 / 5;
		ans += num;
		n2 -= num * 5;
		printf("%lld\n", ans);
	}
}