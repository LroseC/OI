#include <cctype>
#include <cstdio>
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

int n, ans;
bool vis[20];
int A[20][20];

void dfs(int id, int res)
{
	if (id > n) {
		ans = max(ans, res);
		return;
	}
	if (vis[id]) {
		dfs(id + 1, res);
		return;
	}
	vis[id] = 1;
	for (int i = id + 1; i <= n; ++i)
		if (!vis[i]) {
			vis[i] = 1;
			res ^= A[id][i];
			dfs(id + 1, res);
			res ^= A[id][i];
			vis[i] = 0;
		}
	vis[id] = 0;
}

int main(void)
{
	// CHECK YOUR ARRAY TO MAKE SRUE YOUR CODE WON'T RE
	IO >> n;
	n = n * 2;
	for (int i = 1; i <= n; ++i)
		for (int j = i + 1; j <= n; ++j)
			IO >> A[i][j];
	dfs(1, 0);
	printf("%d\n", ans);
	return 0;
}
