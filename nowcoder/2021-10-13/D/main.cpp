#include <cctype>
#include <cstdio>
#include <cstring>

using namespace std;

typedef long long LL;
const int N = 1e5 + 10;

int n;
LL ans[N];
int nex[N];
char str[N];

inline LL calc(int n, char str[])
{
	memset(nex, 0, 4 * n);
	memset(ans, 0, 8 * n);
	for (int i = 1, j; i < n; ++i) {
		j = i - 1;
		while (j > 0 && str[nex[j]] != str[i])
			j = nex[j] - 1;
		if (j <= 0 && str[0] != str[i]) {
			ans[i] = 0;
			nex[i] = 0;
		}
		else {
			ans[i] = ans[nex[j]] + nex[j] + 1;
			nex[i] = nex[j] + 1;
		}
	}
	LL res = 0;
	for (int i = 0; i < n; ++i) res += ans[i];
	return res;
}

int main(void)
{
	scanf("%d%s", &n, str);
	LL res = 0;
	for (int i = n, j = 0; i >= 1; --i, ++j) {
		res += calc(i, str + j);
	}
	printf("%lld\n", res);
	return 0;
}
