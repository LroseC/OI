#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

using LL = long long;

LL l, r;
int digit[15];
LL f[12][2][2][2][2][10][10];

LL dfs(int pos, bool lim, bool four, bool eight, bool state, int last, int llast)
{
	if (four && eight) return 0;
	if (~f[pos][lim][four][eight][state][last][llast])
		return f[pos][lim][four][eight][state][last][llast];
	if (pos == 0) {
		if ((!four || !eight) && state)
			return 1;
		return 0;
	}
	int ed = lim ? digit[pos] : 9;
	LL res = 0;
	for (int i = 0; i <= ed; ++i)
		res += dfs(pos - 1, lim && i == ed, four || (i == 4), eight || (i == 8), state || ((i == last) && (i == llast)), i, last);
	return f[pos][lim][four][eight][state][last][llast] = res;
}

LL calc(LL x)
{
	int len = 0;
	while (x) {
		digit[++len] = x % 10;
		x /= 10;
	}
	if (len != 11) return 0;
	LL res = 0;
	memset(f, -1, sizeof f);
	for (int i = 1; i <= digit[len]; ++i)
		res += dfs(len - 1, i == digit[len], i == 4, i == 8, 0, i, -1);
	return res;
}

int main(void)
{
	ios::sync_with_stdio(0);
	cin >> l >> r;
	printf("%lld\n", calc(r) - calc(l - 1));
	return 0;
}