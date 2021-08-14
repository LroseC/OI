#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

#define int long long
typedef long long LL;
const int N = 1e5 + 10, M = N << 1;
const int MOD = 1e9 + 7;

int n, idx;
LL ans = 0;
LL cnt;
int head[N], nex[M], to[M], w[M];
vector<LL> nums;

LL qpow(int x, int k)
{
	LL base = x, res = 1;
	while (k) {
		if (k & 1) res = res * base % MOD;
		base = base * base % MOD;
		k >>= 1;
	}
	return res;
}

void AddEdge(int u, int v, int wi)
{
	nex[++idx] = head[u]; w[idx] = wi;
	head[u] = idx; to[idx] = v;
}

void get_sum(int u, int fa, LL dis)
{
	for (auto &x : nums) {
		LL a = x, b = dis;
		if (a > b) swap(a, b);
		cnt = (cnt + a * 2 % MOD - 1) % MOD;
		ans = (ans + b * (a * 2 % MOD - 1) % MOD) % MOD;
		ans = (ans + (a + b) * (a * 2 % MOD - 1) % MOD) % MOD;
	}
	for (int e = head[u]; e; e = nex[e]) {
		int v = to[e];
		if (v == fa) continue;
		get_sum(v, u, dis + w[e]);
	}
}
void get_dist(int u, int fa, LL dis)
{
	nums.push_back(dis);
	for (int e = head[u]; e; e = nex[e]) {
		int v = to[e];
		if (v == fa) continue;
		get_dist(v, u, dis + w[e]);
	}
}

void dp(int u, int fa)
{
	nums.clear();
	for (int e = head[u]; e; e = nex[e]) {
		int v = to[e];
		if (v == fa) continue;
		get_sum(v, u, w[e]);
		get_dist(v, u, w[e]);
	}
	for (int e = head[u]; e; e = nex[e]) {
		int v = to[e];
		if (v == fa) continue;
		dp(v, u);
	}
}

signed main(void)
{
	scanf("%lld", &n);
	for (int i = 1; i < n; ++i) {
		int u, v, w;
		scanf("%lld%lld%lld", &u, &v, &w);
		AddEdge(u, v, w);
		AddEdge(v, u, w);
	}
	dp(1, -1);
	printf("%lld\n", ans * qpow(cnt, MOD - 2) % MOD);
	return 0;
}