#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

int mod;

using PII = pair<int, int>;

void add(int &x, int y)
{
	x += y;
	if (x >= mod) x -= mod;
}

int n, m, k;
int nlen, mlen, klen, maxlen;
bool vis[70][2][2][2];
PII f[70][2][2][2];

PII dp(int pos, bool n1, bool m1, bool k1)
{
	if (pos < 0) return make_pair(1, 0);
	if (vis[pos][n1][m1][k1])
		return f[pos][n1][m1][k1];
	vis[pos][n1][m1][k1] = 1;
	int np = (n >> pos & 1), mp = (m >> pos & 1), kp = (k >> pos & 1);
	for (int nn = 0; nn <= (n1 ? np : 1); ++nn)
		for (int mm = 0; mm <= (m1 ? mp : 1); ++mm) {
			if (k1 && (nn ^ mm) < kp) continue;
			PII nw = dp(pos - 1, n1 && (nn == np), m1 && (mm == mp), k1 && ((nn ^ mm) == kp));
			add(f[pos][n1][m1][k1].first, nw.first);
			add(f[pos][n1][m1][k1].second, ((1ll << pos) * (nn ^ mm) % mod * nw.first % mod + nw.second) % mod);
		}
	return f[pos][n1][m1][k1];
}

int main(void)
{
	ios::sync_with_stdio(0);
	int T;
	cin >> T;
	while (T--) {
		cin >> n >> m >> k >> mod;
		--n, --m;
		memset(f, 0, sizeof f);
		memset(vis, 0, sizeof vis);

		int tmp;
		maxlen = 0;
		tmp = n;
		nlen = 0;
		while (tmp) {
			++nlen;
			tmp >>= 1;
		}
		maxlen = max(maxlen, nlen);
		tmp = m;
		mlen = 0;
		while (tmp) {
			++mlen;
			tmp >>= 1;
		}
		maxlen = max(maxlen, mlen);
		tmp = k;
		klen = 0;
		while (tmp) {
			++klen;
			tmp >>= 1;
		}
		maxlen = max(maxlen, klen);

		PII ans = dp(maxlen, 0, 0, 0);
		printf("%d\n", ans.second);
	}
	return 0;
}
