#include <set>
#include <random>
#include <climits>
#include <assert.h>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 1e5 + 10;

int n, m, idx;
int head[N << 1], nex[N << 1], to[N << 1], tx[N << 1], ty[N << 1];

random_device srd;
mt19937 rd(srd());

int myrand(int l, int r)
{
	assert(r - l + 1 > 0);
	return rd() % (r - l + 1) + l;
}

void AddEdge(int u, int v)
{
	nex[++idx] = head[u];
	head[u] = idx;
	to[idx] = v;
}

void dfs(int u, int fa, int tim)
{
	for (int e = head[u]; e; e = nex[e]) {
		int v = to[e];
		if (v == fa) continue;
		tx[e] = tim + 1;
		ty[e] = tim + 1 + myrand(1, 10);
		dfs(v, u, ty[e]);
	}
}

int main(void)
{
	ios::sync_with_stdio(false);
	n = 1000, m = 1000;
	cout << n << endl;
	for (int i = 1; i <= n / 2; ++i) {
		int u = myrand(1, i), v = i + 1;
		AddEdge(u, v);
	}
	dfs(1, -1, 1);
	for (int i = n / 2 + 1; i <= n; ++i) {
		int u = i, v = myrand(1, n / 2);
		cout << u << ' ' << v << ' ' << 1 << ' ' << 2 << endl;
	}
	for (int i = 1; i <= n * 2 + 1; ++i) {
		for (int e = head[i]; e; e = nex[e]) {
			cout << i << ' ' << to[e] << ' ' << tx[e] << ' ' << ty[e] << endl;
		}
	}
	cout << m << endl;
	for (int i = 1; i <= m; ++i) {
		int X = myrand(1, 1e8), Y = myrand(1, n * 2);
		cout << X << ' ' << Y << endl;
	}
	return 0;
}