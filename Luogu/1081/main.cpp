#include <set>
#include <vector>
#include <cctype>
#include <cstdio>
#include <algorithm>

using namespace std;

typedef long long LL;
typedef pair<LL, LL> PLL;
typedef pair<int, int> PII;
const int N = 1e5 + 10, M = 17;
const LL INF = 0x3f3f3f3f3f3f3f3f;

inline int read(void)
{
	int res = 0, f = 1; char ch = getchar();
	while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
	while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
	return res * f;
}

int h[N];
int n, m;
int nex[2][N];
int f[2][N][M];
LL dis[2][2][N][M];

inline bool cmp(const PII &a, const PII &b)
{
	if (a.first != b.first) return a.first < b.first;
	return h[a.second] < h[b.second];
}

void GetNex(void)
{
	set<PII> S;// first: This city's height, second: The id of this city
	vector<PII> tmp;// first: This city's difference between the i-th city, second: The id of this city
	for (int i = n; i; --i) {
		tmp.clear();
		auto it = S.lower_bound({h[i], i});
		auto jt = it;
		for (int j = 0; j < 2; ++j)
			if (it != S.end()) {
				tmp.emplace_back(PII({abs(it->first - h[i]), it->second}));
				++it;
			}
		for (int j = 0; j < 2; ++j)
			if (jt != S.begin()) {
				--jt;
				tmp.emplace_back(PII({abs(jt->first - h[i]), jt->second}));
			}
		sort(tmp.begin(), tmp.end(), cmp);
		if (tmp.size() > 1) nex[0][i] = tmp[1].second;
		if (tmp.size() > 0) nex[1][i] = tmp[0].second;
		S.insert({h[i], i});
	}
}
PLL Solve(int stcity, int maxdis) //Get how far will A and B go from stcity with the limit of maxdis
{
	PLL res = {0, 0};
	int now = stcity, nowdis = 0;
	for (int k = M - 1; k >= 0; --k) {
		if (f[0][now][k] && nowdis + dis[0][0][now][k] + dis[0][1][now][k] <= maxdis) {
			res.first += dis[0][0][now][k];
			res.second += dis[0][1][now][k];
			nowdis += dis[0][0][now][k] + dis[0][1][now][k];
			now = f[0][now][k];
		}
	}
	return res;
}

int main(void)
{
	n = read();
	for (int i = 1; i <= n; ++i) h[i] = read();

	GetNex();
	for (int i = 1; i <= n; ++i) {
		f[0][i][0] = nex[0][i];
		f[1][i][0] = nex[1][i];
		if (nex[0][i]) dis[0][0][i][0] = abs(h[nex[0][i]] - h[i]);
		if (nex[1][i]) dis[1][1][i][0] = abs(h[nex[1][i]] - h[i]);
	}
	for (int k = 1; k < M; ++k)
		for (int i = 1; i <= n; ++i) {
			if (k == 1) {
				f[0][i][k] = f[1][f[0][i][k - 1]][k - 1];
				f[1][i][k] = f[0][f[1][i][k - 1]][k - 1];
			}
			else {
				f[0][i][k] = f[0][f[0][i][k - 1]][k - 1];
				f[1][i][k] = f[1][f[1][i][k - 1]][k - 1];
			}
		}
	for (int k = 1; k < M; ++k)
		for (int i = 1; i <= n; ++i) {
			if (k == 1) {
				dis[0][0][i][k] = dis[0][0][i][k - 1] + dis[1][0][f[0][i][k - 1]][k - 1];
				dis[0][1][i][k] = dis[0][1][i][k - 1] + dis[1][1][f[0][i][k - 1]][k - 1];
				dis[1][0][i][k] = dis[1][0][i][k - 1] + dis[0][0][f[1][i][k - 1]][k - 1];
				dis[1][1][i][k] = dis[1][1][i][k - 1] + dis[0][1][f[1][i][k - 1]][k - 1];
			}
			else {
				dis[0][0][i][k] = dis[0][0][i][k - 1] + dis[0][0][f[0][i][k - 1]][k - 1];
				dis[0][1][i][k] = dis[0][1][i][k - 1] + dis[0][1][f[0][i][k - 1]][k - 1];
				dis[1][0][i][k] = dis[1][0][i][k - 1] + dis[1][0][f[1][i][k - 1]][k - 1];
				dis[1][1][i][k] = dis[1][1][i][k - 1] + dis[1][1][f[1][i][k - 1]][k - 1];
			}
		}
	
	int ans = 0;
	int x0 = read();
	double frac = 1e21;
	for (int i = 1; i <= n; ++i) {
		PLL tmp = Solve(i, x0);
		double fract = tmp.second ? 1.0 * tmp.first / tmp.second : 1e20;
		if (fract < frac || (fract == frac && h[i] > h[ans])) {
			frac = fract;
			ans = i;
		}
	}
	printf("%d\n", ans);

	m = read();
	while (m--) {
		int s0 = read(), x0 = read();
		PLL tmp = Solve(s0, x0);
		printf("%lld %lld\n", tmp.first, tmp.second);
	}

	return 0;
}