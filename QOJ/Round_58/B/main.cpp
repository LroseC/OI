#include <vector>
#include <string>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

inline int read(void)
{
	int res = 0, f = 1; char ch;
	while (!isdigit(ch = getchar())) if (ch == '-') f = -1;
	do res = res * 10 + ch - '0'; while (isdigit(ch = getchar()));
	return res * f;
}

const int N = 2010;
const int Mod = 1e9 + 7;

int a, b, c, d;
int f[60][60][60][60];

/*
f[a][b][c][d] 表示使用了 a 个 0, b 个 1，凑出 c 个 0， d 个 1 的不同方案数
性质：方案数
转移方程：
f[a][b][c][d] += f[a - 1][b][c - 1][d];
f[a][b][c][d] += f[a][b - 1][c][d - 1];
f[a][b][c][d] += f[a - 1][b][c][d];
f[a][b][c][d] += f[a][b - 1][c][d];
*/

int dp(int a, int b, int c, int d)
{
	if (a < 0 || b < 0) return 0;
	if (c > a || d > b) return 0;
	if (c == 0 && d == 0) return 1;
	if (~f[a][b][c][d]) return f[a][b][c][d];
	f[a][b][c][d] = 0;
	f[a][b][c][d] = (f[a][b][c][d] + dp(a - 1, b, c - 1, d)) % Mod;
	f[a][b][c][d] = (f[a][b][c][d] + dp(a, b - 1, c, d - 1)) % Mod;
	return f[a][b][c][d];
}

int jiecheng[N + N];

int qpow(int base, int k)
{
	int res = 1;
	while (k) {
		if (k & 1) res = 1ll * res * base % Mod;
		base = 1ll * base * base % Mod;
		k >>= 1;
	}
	return res;
}

int inv(int x)
{
	return qpow(x, Mod - 2);
}

vector<string> S1, S2;

string tmp;

void dfs(int a, int b, vector<string> &S)
{
	if (!a && !b) {
		S.emplace_back(tmp);
		return;
	}
	if (a) {
		tmp.push_back('0');
		dfs(a - 1, b, S);
		tmp.pop_back();
	}
	if (b) {
		tmp.push_back('1');
		dfs(a, b - 1, S);
		tmp.pop_back();
	}
}

int main(void)
{
	memset(f, -1, sizeof f);
	f[0][0][0][0] = 1;
	a = read(), b = read(), c = read(), d = read();
	if (c == 0) {
		jiecheng[0] = 1;
		for (int i = 1; i <= a + b; ++i)
			jiecheng[i] = 1ll * jiecheng[i - 1] * i % Mod;
		printf("%d\n", 1ll * jiecheng[a + b] * inv(jiecheng[a]) % Mod * inv(jiecheng[b]) % Mod);
		return 0;
	}
	else {
		tmp = "";
		dfs(a, b, S1);
		tmp = "";
		dfs(c, d, S2);
		int ans = 0;
		for (auto s1 : S1)
			for (auto s2 : S2) {
				int i, j;
				for (i = 0, j = 0; j < s2.size(); ++j)
					while (i < S1.size() && s1[i] != s2[j]) ++i;
				if (i < S1.size()) ++ans;
			}
		printf("%d\n", ans);
	}
	return 0;
}