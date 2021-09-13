#include <vector>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 20, M = 1 << 12;
const int mod = 1e8;

inline int read(void)
{
	int res = 0, f = 1; char ch;
	while (!isdigit(ch = getchar())) if (ch == '-') f = -1;
	do res = res * 10 + ch - '0'; while (isdigit(ch = getchar()));
	return res * f;
}

int n, m;
int mp[N];
int f[N][M];
vector<int> states;

bool check(int x)
{
	for (int i = 0, cnt = 1; i < m; ++i) {
		if (x >> i & 1) {
			if (!cnt) return 0;
			cnt = 0;
		}
		else ++cnt;
	}
	return 1;
}
void Print(int x)
{
	for (int i = 0; i < m; ++i) putchar('0' + (x >> i & 1));
}

int main(void)
{
	n = read(), m = read();
	for (int j = 0; j < 1 << m; ++j)
		if (check(j)) states.emplace_back(j);

	for (int i = 1; i <= n; ++i)
		for (int j = 0; j < m; ++j) {
			int x = read();
			if (!x) {
				mp[i] |= (1 << j);
			}
		}
	f[0][0] = 1;
	for (int i = 1; i <= n; ++i)
		for (int k : states) {
			if (k & mp[i]) continue;
			for (int j : states) {
				if (k & j) continue;
				f[i][k] = (f[i][k] + f[i - 1][j]) % mod;
			}
		}
	int ans = 0;
	for (int i : states) {
		if (i & mp[n]) continue;
		ans = (ans + f[n][i]) % mod;
	}
	printf("%d\n", ans);
	return 0;
}