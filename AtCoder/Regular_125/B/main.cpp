#include <bits/stdc++.h>

using namespace std;

typedef long long LL;
const int Mod = 998244353;

LL n;
LL ans;

LL get(LL x)
{
	LL a = sqrt(x * x - n), b = sqrt(x * x - 1);
	if (a * a != x * x - n) ++a;
	a = max(a, (LL)0);
	return b - a + 1;
}

int main(void)
{
	long long tmp;
	scanf("%lld", &tmp); n = tmp;
	// while (l < r) {
	// 	printf("l = %d, r = %d\n", l, r);
	// 	mid = l + r >> 1;
	// 	LL tmp = get(mid), tmpl = get(mid - 1), tmpr = get(mid + 1);
	// 	if (tmp > tmpr && tmp > tmpl) {
	// 		l = r = mid;
	// 		break;
	// 	}
	// 	if (tmpl > tmpr) r = tmpr;
	// 	else l = tmpl;
	// }
	LL maxid = sqrt(n);
	LL a = maxid;
	int cnt = 0;
	for (LL L = 1, R; L <= maxid; L = R + 1) {
		++cnt;
		LL l = L;
		LL r = maxid;
		LL mid;
		while (l < r) {
			mid = l + r + 1 >> 1;
			if (get(mid) == get(L)) l = mid;
			else r = mid - 1;
		}
		R = l;
		ans = (ans + (R - L + 1) * get(L) % Mod) % Mod;
	}
	cnt = 0;
	for (LL L = maxid + 1, R; L <= n; L = R + 1) {
		++cnt;
		if (get(L) == 0) break;
		LL l = L, r = n, mid;
		while (l < r) {
			mid = l + r + 1 >> 1;
			if (get(mid) == get(L)) l = mid;
			else r = mid - 1;
		}
		R = l;
		ans = (ans + (R - L + 1) * get(L) % Mod) % Mod;
	}
	printf("%d\n", (int)(ans % Mod));
	return 0;
}