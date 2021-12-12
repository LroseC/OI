#include <vector>
#include <cctype>
#include <cstdio>
#include <algorithm>

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
} io;

const int N = 1e3 + 10;
using PII = pair<int, int>;

int n;
int S[N][N];
PII cows[N];
vector<int> numx, numy;

int main(void)
{
	io >> n;
	for (int i = 1; i <= n; ++i) {
		io >> cows[i].first >> cows[i].second;
		numx.emplace_back(cows[i].first);
		numy.emplace_back(cows[i].second);
	}
	sort(numx.begin(), numx.end());
	sort(numy.begin(), numy.end());
	numx.erase(unique(numx.begin(), numx.end()), numx.end());
	numy.erase(unique(numy.begin(), numy.end()), numy.end());
	for (int i = 1; i <= n; ++i) {
		cows[i].first = lower_bound(numx.begin(), numx.end(), cows[i].first) - numx.begin() + 1;
		cows[i].second = lower_bound(numy.begin(), numy.end(), cows[i].second) - numy.begin() + 1;
		++S[cows[i].first][cows[i].second];
	}
	for (int i = 1; i <= numx.size(); ++i)
		for (int j = 1; j <= numy.size(); ++j)
			S[i][j] = S[i][j] + S[i - 1][j] + S[i][j - 1] - S[i - 1][j - 1];
	int ans = 0x3f3f3f3f;
	for (int a = 1; a <= numx.size(); ++a)
		for (int b = 1; b <= numy.size(); ++b) {
			int res = 0;
			res = max(res, S[a][b]);
			res = max(res, S[numx.size()][b] - S[a][b]);
			res = max(res, S[a][numy.size()] - S[a][b]);
			res = max(res, S[numx.size()][numy.size()] - S[numx.size()][b] - S[a][numy.size()] + S[a][b]);
			ans = min(ans, res);
		}
	printf("%d\n", ans);
	return 0;
}