#include <cmath>
#include <vector>
#include <cctype>
#include <cstdio>
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

using i64 = long long;
const int N = 5e5 + 10;

int n;
double K;
int sz[N], val[N], ans[N];
std::vector<int> G[N];

void getSz(int u)
{
	sz[u] = 1;
	for (int v : G[u]) {
		getSz(v);
		sz[u] += sz[v];
	}
}
void calc(int u, int L, int R)
{
	int nowR = R;
	for (int v : G[u]) {
		ans[v] = val[nowR - sz[v] + 1];
		calc(v, nowR - sz[v] + 2, nowR);
		nowR = nowR - sz[v];
	}
}

int main(void)
{
//	freopen("iiidx.in", "r", stdin);
//	freopen("iiidx.out", "w", stdout);
	read >> n;
	scanf("%lf", &K);
	for (int i = 1; i <= n; ++i)
		read >> val[i];
	std::sort(val + 1, val + 1 + n);
	for (int i = 1; i <= n; ++i)
		G[(int)std::floor(i / K)].emplace_back(i);
	getSz(0);
	calc(0, 1, n);
	for (int i = 1; i <= n; ++i)
		printf("%d ", ans[i]);
	puts("");
	return 0;
}
