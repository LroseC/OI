#include <vector>
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

const int N = 2e5 + 10;

int n;
vector<int> G[N];
int L[N], R[N], dfnidx;

void dfs(int u, int fa)
{
	L[u] = dfnidx;
	bool flag = 0;
	for (int v : G[u])
		if (v != fa) {
			dfs(v, u);
			++dfnidx;
			flag = 1;
		}
	if (flag) --dfnidx;
	R[u] = dfnidx;
}

int main(void)
{
	// CHECK YOUR ARRAY TO MAKE SRUE YOUR CODE WON'T RE
	IO >> n;
	for (int i = 1; i < n; ++i) {
		int u, v; IO >> u >> v;
		G[u].emplace_back(v);
		G[v].emplace_back(u);
	}
	dfs(1, 1);
	vector<int> nums;
	for (int i = 1; i <= n; ++i) {
		nums.emplace_back(L[i]);
		nums.emplace_back(R[i]);
	}
	sort(nums.begin(), nums.end());
	nums.erase(unique(nums.begin(), nums.end()), nums.end());
	for (int i = 1; i <= n; ++i) {
		L[i] = lower_bound(nums.begin(), nums.end(), L[i]) - nums.begin();
		R[i] = lower_bound(nums.begin(), nums.end(), R[i]) - nums.begin();
		printf("%d %d\n", L[i] + 1, R[i] + 1);
	}
	return 0;
}
