#include <vector>
#include <cctype>
#include <cstdio>

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

/*
   f[i][j] 表示前 i 个城市均摊了 j 次的最高水位.
   f[i][j] = (f[k][j - 1] + s[i] - s[k]) / (i - k);
   我们大胆交换数组两维
   f[i][j] 表示前 j 个城市均摊了 i 次的最高水位.
   f[i][j] = (f[i - 1][k] + s[j] - s[k]) / (j - k);
   这样不用同时维护多个单调队列了。。。
   上式可以巧妙看做点 (j, s[j]) 到(k, s[k] - f[i - 1][k]) 的斜率.
   显然有 s[k] - f[i - 1][k] < s[j];
   此时我们可以肯定地说这个决策具有单调性，可以维护一个凸包转移.
   在此基础上这道题还有非常好的性质，可以用单调队列进行斜率优化。。。
   这题太恶心了.
*/

int n, m, P;
int idx, h[N];
int f[2][N];

int main(void)
{
	read >> n >> m >> P;
	h.emplace_back(0);
	for (int i = 1; i <= n; ++i) {
		int x; read >> x;
		if (!idx || x > h[1])
			h[++idx] = x;
	}
	n = idx;
	std::sort(h + 1, h + 1 + n);
	m = std::min(n, m);
	for (int i = 1; i <= n; ++i)
		f[0][i] = h[1];
	for (int i = 1; i <= m; ++i) {
		int hh = 1, tt = 0;
		for (int j = 2; j <= n; ++j) {
			while (hh <= tt && 
		}
	return 0;
}
/*
   f[i][j] 表示前 i 个城市均摊了 j 次的最高水位.
   f[i][j] = (f[k][j - 1] + s[i] - s[k]) / (i - k);
   我们大胆交换数组两维
   f[i][j] 表示前 j 个城市均摊了 i 次的最高水位.
   f[i][j] = (f[i - 1][k] + s[j] - s[k]) / (j - k);
   这样不用同时维护多个单调队列了。。。
   上式可以巧妙看做点 (j, s[j]) 到(k, s[k] - f[i - 1][k]) 的斜率.
   显然有 s[k] - f[i - 1][k] < s[j];
   此时我们可以肯定地说这个决策具有单调性，可以维护一个下凸包转移.
*/
