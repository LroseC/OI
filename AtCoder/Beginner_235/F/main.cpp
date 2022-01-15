#include <cctype>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
using LL = long long;
const char endl = '\n';

struct FastStreamInputOutput
{
	using FSIO = FastStreamInputOutput;
	template<typename T>
	FSIO& operator>>(T &res)
	{
		res = 0; T f = 1; char ch = getchar();
		while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
		while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
		res *= f; return *this;
	}
	FSIO& operator<<(char x)
	{
		putchar(x);
		return *this;
	}
	FSIO& operator<<(const char x[])
	{
		for (int i = 0; x[i]; ++i) putchar(x[i]);
		return *this;
	}
	template<typename T>
	FSIO& operator<<(const T &res)
	{
		static char buf[50]; int p = -1; T x = res;
		if (x == 0) putchar('0');
		if (x < 0) { putchar('-'); x = -x; }
		while (x) { buf[++p] = x % 10; x /= 10; }
		while (~p) { putchar(buf[p] + '0'); --p; }
		return *this;
	}
} IO;

const int N = 1e4 + 10, S = 1 << 10, mod = 998244353;

int n, m;
int ans = 0;
char str[N];
int pw10[N];
int digit[N];
int f[N][2][S];
int g[N][2][S];

int dfs(int pos, bool lim, int state)
{
	if (f[pos][lim][state] != -1) {
		return f[pos][lim][state];
	}
	if (pos == 1) {
		if (state == 0)
			g[pos][lim][state] = 0;
		return state == 0;
	}
	int sum = 0;
	int sumt = 0;
	int ed = 9;
	if (lim) ed = digit[pos - 1];
	for (int i = 0; i <= ed; ++i) {
		int tmp = state;
		if (state >> i & 1) tmp ^= (1 << i);
		sum = (sum + dfs(pos - 1, lim && i == ed, tmp)) % mod;
		sumt = (sumt + g[pos - 1][lim && i == ed][tmp]) % mod;
		sumt = (sumt + 1ll * dfs(pos - 1, lim && i == ed, tmp) * i % mod * pw10[pos - 2] % mod) % mod;
	}
	g[pos][lim][state] = sumt;
	return f[pos][lim][state] = sum;
}

int main(void)
{
	// CHECK YOUR ARRAY TO MAKE SRUE YOUR CODE WON'T RE
	pw10[0] = 1;
	for (int i = 1; i < N; ++i)
		pw10[i] = 1ll * pw10[i - 1] * 10 % mod;
	memset(f, -1, sizeof f);
	scanf("%s", str + 1);
	n = strlen(str + 1);
	for (int i = 1; i <= n; ++i)
		digit[i] = str[i] - '0';
	reverse(digit + 1, digit + 1 + n);
	IO >> m;
	int limit = 0;
	for (int i = 1; i <= m; ++i) {
		int x; IO >> x;
		limit |= 1 << x;
	}
	int res = 0;
	for (int l = 1; l < n; ++l)
		for (int i = 1; i < 10; ++i) {
			int tmp = limit;
			if (limit >> i & 1) tmp ^= (1 << i);
			res = (res + dfs(l, 0, tmp)) % mod;
			ans = (ans + g[l][0][tmp]) % mod;
			ans = (ans + 1ll * i * pw10[l - 1] % mod * dfs(l, 0, tmp) % mod) % mod;
		}
	for (int i = 1; i < digit[n]; ++i) {
		int tmp = limit;
		if (limit >> i & 1) tmp ^= (1 << i);
		res = (res + dfs(n, 0, tmp)) % mod;
		ans = (ans + g[n][0][tmp]) % mod;
		ans = (ans + 1ll * i * pw10[n - 1] % mod * dfs(n, 0, tmp) % mod) % mod;
	}
	int tmp = limit;
	if (limit >> digit[n] & 1) tmp ^= (1 << digit[n]);
	res = (res + dfs(n, 1, tmp)) % mod;
	ans = (ans + g[n][1][tmp]) % mod;
	ans = (ans + 1ll * digit[n] * pw10[n - 1] % mod * dfs(n, 1, tmp) % mod) % mod;
	printf("%d\n", ans);
	return 0;
}
