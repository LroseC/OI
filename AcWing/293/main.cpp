#include <set>
#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 1e5 + 10;

int n, m;
int A, B;
int h[N];
int x0;
int s[N], x[N];
int dista[2][20][N], distb[2][20][N];
set<int> st;

void init_dist0(void)
{
	vector<int> tmp;
	st.insert(h[n]);
	for (int i = n - 1; i; --i) {
		tmp.clear();
		auto it = st.lower_bound(h[i]);
		if (it != st.end()) tmp.push_back(*it);
		auto jt = it;
		if (jt != st.begin()) --jt, tmp.push_back(*jt);
		sort(tmp.begin(), tmp.end());
		distb[1][0][i] = tmp[0];
		// for (auto x : tmp) printf("%d ", x);
		// puts("???");
		if (it != st.end()) ++it, tmp.push_back(*it);
		if (jt != st.begin()) --jt, tmp.push_back(*jt);
		sort(tmp.begin(), tmp.end());
		dista[0][0][i] = tmp[1];
		st.insert(h[i]);
	}
}

void get_dist(void)
{
	init_dist0();
	for (int i = 1; i <= 17; ++i) {
		for (int j = 1; j + (1 << i) <= n; ++j) {
			if (i == 1) {
				dista[0][i][j] = dista[0][i - 1][j];
				dista[1][i][j] = dista[0][i - 1][j + 1];
				distb[0][i][j] = distb[1][i - 1][j + 1];
				distb[1][i][j] = distb[1][i - 1][j];
			}
			else {
				dista[0][i][j] = dista[0][i - 1][j] + dista[0][i - 1][j + (1 << j - 1)];
				dista[1][i][j] = dista[1][i - 1][j] + dista[1][i - 1][j + (1 << j - 1)];
				distb[0][i][j] = distb[0][i - 1][j] + distb[0][i - 1][j + (1 << j - 1)];
				distb[1][i][j] = distb[1][i - 1][j] + distb[1][i - 1][j + (1 << j - 1)];
			}
		}
	}
}

void calc(int s, int x)
{
	int res = 0;
	A = B = 0;
	for (int i = 17; i >= 0; --i) {
		if (dista[0][i][s] + distb[0][i][s] + res <= x) {
			res += dista[0][i][s] + distb[0][i][s];
			A += dista[0][i][s], B += distb[0][i][s];
		}
	}
}

int main(void)
{
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) scanf("%d", &h[i]);
	scanf("%d%d", &x0, &m);
	for (int i = 1; i <= m; ++i)
		scanf("%d%d", &s[i], &x[i]);
	
	get_dist();

	int ans = 0;
	for (int i = 1, res = 2; i <= n; ++i) {
		calc(i, x0);
		if (A * 1.0 / B < res) {
			res = A * 1.0 / B;
			ans = i;
		}
	}
	printf("%d\n", ans);

	for (int i = 1; i <= m; ++i) {
		calc(s[i], x[i]);
		printf("%d %d\n", A, B);
	}
}