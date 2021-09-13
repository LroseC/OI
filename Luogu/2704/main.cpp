#include <vector>
#include <cctype>
#include <cstdio>
#include <algorithm>

using namespace std;

const int N = 110, M = 10;

inline int lowbit(int x) { return x & -x; }
inline int read(void)
{
	int res = 0, f = 1; char ch;
	while (!isdigit(ch = getchar())) if (ch == '-') f = -1;
	do res = res * 10 + ch - '0'; while (isdigit(ch = getchar()));
	return res * f;
}

int n, m;
char str[N][M + 1];
int mp[N];
int f[2][1 << M][1 << M];
int cnt[1 << M];
vector<int> states;

bool check(int x)
{
	for (int i = 0, cnt = 10; i < m; ++i) {
		if (x >> i & 1) {
			if (cnt < 2) return 0;
			cnt = 0;
		}
		else ++cnt;
	}
	return 1;
}
int getcnt(int x)
{
	int res = 0;
	while (x) { x -= lowbit(x); ++res; }
	return res;
}

int main(void)
{
	n = read(), m = read();
	for (int i = 0; i < n; ++i) {
		scanf("%s", str[i]);
		for (int j = 0; j < m; ++j)
			if (str[i][j] == 'H') mp[i] |= 1 << j;
	}
	for (int i = 0; i < 1 << m; ++i)
		if (check(i)) {
			cnt[i] = getcnt(i);
			states.emplace_back(i);
		}

	for (int line = 0; line < n + 2; ++line)
		for (int k : states) {
			if (k & mp[line]) continue;
			for (int j : states) {
				if (k & j) continue;
				f[line & 1][j][k] = 0;
				for (int i : states) {
					if ((k & i) || (j & i)) continue;
					f[line & 1][j][k] = max(f[line & 1][j][k], f[line & 1 ^ 1][i][j] + cnt[k]);
				}
			}
		}
	printf("%d\n", f[n + 1 & 1][0][0]);
	return 0;
}