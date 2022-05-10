#include <cmath>
#include <cstdio>
#include "subway.h"

using i64 = long long;

int n, m, lim;
int B, L, R = -1;

void init(int n, int m, int lim);
int solve(int l);
void init(int _n, int _m, int _lim)
{
	n = _n, m = _m, lim = _lim;
	B = sqrt(m);
}
void rebuild(int id)
{
	while (L <= R) {
		++L;
		undo();
	}
	L = R = id;
	merge(R);
	while (R < m && check(R + 1)) {
		++R;
		merge(R);
	}
}
int solve(int id)
{
	rebuild(id);
	return R;
}
