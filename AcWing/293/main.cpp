#include <set>
#include <cmath>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long LL;
typedef pair<int, int> PII;
typedef pair<LL, int> PLI;
#define int long long
const int N = 1e5 + 10, M = 17;
const double eps = 1e-6;

inline int sign(double x)
{
	if (fabs(x) < eps) return 0;
	return x < 0 ? -1 : 1;
}
inline int cmpd(double a, double b)
{
	return sign(a - b);
}

int n, m;
int h[N];
int ga[N], gb[N];
int da[N][M][2], db[N][M][2];
set<PII> S;
int f[N][M][2];

inline void calc(int s, int x, int &a, int &b)
{
	a = b = 0;
	for (int i = M - 1; i >= 0; --i) {
		if (da[s][i][0] + db[s][i][0] <= x && f[s][i][0] != s) {
			x -= da[s][i][0] + db[s][i][0];
			a += da[s][i][0];
			b += db[s][i][0];
			s = f[s][i][0];
		}
	}
}

inline void Init_g(void)
{
	for (int i = n; i; --i) {
		if (S.size() < 1) gb[i] = i;
		else {
			auto it = S.lower_bound({h[i], -1});
			if (it == S.begin()) gb[i] = it->second;
			else if (it == S.end()) {
				--it;
				gb[i] = it->second;
			}
			else {
				auto jt = it;
				--jt;
				if (abs(h[i] - jt->first) <= abs(h[i] - it->first)) gb[i] = jt->second;
				else gb[i] = it->second;
			}
		}
		if (S.size() < 2) ga[i] = i;
		else {
			auto it = S.lower_bound({h[i], -1});
			if (it == S.begin()) {
				++it;
				ga[i] = it->second;
			}
			else if (it == S.end()) {
				--it; --it;
				ga[i] = it->second;
			}
			else {
				vector<PII> tmp;
				tmp.clear();
				tmp.emplace_back(PII({abs(1ll * it->first - h[i]), it->second}));
				auto jt = it;
				++it;
				if (it != S.end())
					tmp.emplace_back(PII({abs(1ll * it->first - h[i]), it->second}));
				--jt;
				tmp.emplace_back(PII({abs(1ll * jt->first - h[i]), jt->second}));
				if (jt != S.begin()) {
					--jt;
					tmp.emplace_back(PII({abs(1ll * jt->first - h[i]), jt->second}));
				}
				sort(tmp.begin(), tmp.end());
				ga[i] = tmp[1].second;
			}
		}
		S.insert({h[i], i});
	}
}

inline void Init_f(void)
{
	for (int i = 1; i <= n; ++i) {
		f[i][0][0] = ga[i];
		f[i][0][1] = gb[i];
	}
	for (int k = 1; k < M; ++k)
		for (int i = 1; i <= n; ++i) {
			if (k == 1) {
				f[i][k][0] = f[f[i][k - 1][0]][k - 1][1];
				f[i][k][1] = f[f[i][k - 1][1]][k - 1][0];
			}
			else {
				f[i][k][0] = f[f[i][k - 1][0]][k - 1][0];
				f[i][k][1] = f[f[i][k - 1][1]][k - 1][1];
			}
		}
}

inline void Init_d(void)
{
	for (int i = 1; i <= n; ++i) {
		da[i][0][0] = abs(h[ga[i]] - h[i]);
		db[i][0][1] = abs(h[gb[i]] - h[i]);
	}
	for (int k = 1; k < M; ++k)
		for (int i = 1; i <= n; ++i) {
			if (k == 1) {
				da[i][k][0] = da[i][k - 1][0] + da[f[i][k - 1][0]][k - 1][1];
				db[i][k][0] = db[i][k - 1][0] + db[f[i][k - 1][0]][k - 1][1];
				da[i][k][1] = da[i][k - 1][1] + da[f[i][k - 1][1]][k - 1][0];
				db[i][k][1] = db[i][k - 1][1] + db[f[i][k - 1][1]][k - 1][0];
			}
			else {
				da[i][k][0] = da[i][k - 1][0] + da[f[i][k - 1][0]][k - 1][0];
				db[i][k][0] = db[i][k - 1][0] + db[f[i][k - 1][0]][k - 1][0];
				da[i][k][1] = da[i][k - 1][1] + da[f[i][k - 1][1]][k - 1][1];
				db[i][k][1] = db[i][k - 1][1] + db[f[i][k - 1][1]][k - 1][1];
			}
		}
}

signed main(void)
{
	scanf("%lld", &n);
	for (int i = 1; i <= n; ++i) scanf("%lld", &h[i]);
	Init_g();
	for (int i = 1; i <= n; ++i) {
		if (ga[i] == i) ga[i] = n + 1;
		if (gb[i] == i) gb[i] = n + 1;
	}
	h[n + 1] = 0x3f3f3f3f3f3f3f3f;
	for (int i = 1; i <= n; ++i) {
		printf("ga[%d] = %d, gb[%d] = %d\n", i, ga[i], i, gb[i]);
	}
	Init_f();
	Init_d();
	int x0;
	scanf("%lld", &x0);
	int ans = 0;
	for (int i = 1, minfroc = 1e9; i <= n; ++i) {
		int da, db;
		calc(i, x0, da, db);
		if ((cmpd(1.0 * da / db, minfroc) < 0) || (!cmpd(1.0 * da / db, minfroc) && h[i] > h[ans])) {
			minfroc = 1.0 * da / db;
			ans = i;
		}
	}
	printf("%lld\n", ans);
	scanf("%lld", &m);
	while (m--) {
		int s, x;
		scanf("%lld%lld", &s, &x);
		int da, db;
		calc(s, x, da, db);
		printf("%lld %lld\n", da, db);
	}
	return 0;
}