#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 110, M = 10, S = 1 << M;
inline int lowbit(int x) { return x & -x; }

int n, m;
int f[2][S][S];
int cnt[S];
int g[N];
vector<int> state;

bool check(int x)
{
	for (int i = 0; i < m; ++i)
		if ((x >> i & 1) && ((x >> i + 1 & 1) || (x >> i + 2 & 1))) return 0;
	return 1;
}
int count(int x)
{
	int res = 0;
	while (x) x -= lowbit(x), ++res;
	return res;
}

int main(void)
{
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; ++i) {
		char str[20];
		scanf("%s", str);
		for (int j = 0; j < m; ++j)
			if (str[j] == 'H')
				g[i] += 1 << j;
	}
	for (int i = 0; i < 1 << m; ++i)
		if (check(i)) {
			state.push_back(i);
			cnt[i] = count(i);
		}
	
	for (int line = 0; line < n + 1; ++line) {
		for (auto i : state) {
			for (auto j : state) {
				for (auto k : state) {
					if ((i & j) || (j & k) || (i & k)) continue;
					if (k & g[line]) continue;
					f[line & 1][j][k] = max(f[line & 1][j][k], f[line - 1 & 1][i][j] + cnt[k]);
				}
			}
		}
	}
	printf("%d\n", f[n & 1][0][0]);
	return 0;
}