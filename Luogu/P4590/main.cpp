#include <cctype>
#include <cstdio>
#include <cstring>
#include <algorithm>

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
} read;

const int mod = 1e9 + 7;
inline int Mod(int x) { return x >= mod ? x - mod : x; }

int n, m;
char str[20];
int ans[20];
int f[2][1 << 15][3];
int nex[1 << 15][3];
char ch[10] = "NOI";
int toj[3][3] = {{1, 1, 1}, {0, 2, 0}, {0, 0, 3}};

int main(void)
{
	read >> n >> m;
	scanf("%s", str + 1);
	for (int state = 0, tmp[20], res[20]; state < 1 << m; ++state) {
		tmp[0] = res[0] = 0;
		for (int i = 1; i <= m; ++i)
			tmp[i] = (state >> i - 1 & 1) + tmp[i - 1];
		for (int t = 0; t < 3; ++t)
			for (int i = 1; i <= m; ++i) {
				res[i] = ch[t] == str[i] ? tmp[i - 1] + 1 : std::max(tmp[i], res[i - 1]);
				nex[state][t] ^= (res[i] - res[i - 1]) << i - 1;
			}
	}
	f[0][0][0] = 1;
	for (int i = 0; i < n; ++i) {
		std::memset(f[(i & 1) ^ 1], 0, sizeof f[(i & 1) ^ 1]);
		for (int state = 0; state < 1 << m; ++state)
			for (int j = 0; j < 3; ++j)
				for (int k = 0; k < 3; ++k) {
					int to = nex[state][k];
					if (j == 2 && k == 2) continue;
					f[(i & 1) ^ 1][to][toj[k][j]] = Mod(f[(i & 1) ^ 1][to][toj[k][j]] + f[i & 1][state][j]);
				}
	}
	for (int state = 0; state < 1 << m; ++state)
		for (int k = 0; k < 3; ++k) {
			int tmp = __builtin_popcount(state);
			ans[tmp] = Mod(ans[tmp] + f[n & 1][state][k]);
		}
	for (int i = 0; i <= m; ++i)
		printf("%d\n", ans[i]);
	return 0;
}
