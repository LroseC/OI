#include <queue>
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
		while (isdigit(ch)) { res = res * 10 + (ch - '0') * f; ch = getchar(); }
		return *this;
	}
} read;

using i64 = long long;
const int N = 2e5 + 10;

int n;
int maxDep[N];
int M[N], fa[N], stk[N];
std::vector<int> G[N];
std::priority_queue<int> heap[N];

void init(int u) {
	for (int v : G[u]) {
		init(v);
		maxDep[u] = std::max(maxDep[u], maxDep[v]);
	}
	++maxDep[u];
}
void calc(int u)
{
	if (G[u].size()) {
		calc(G[u][0]);
		std::swap(heap[u], heap[G[u][0]]);
	}
	for (int i = 1; i < G[u].size(); ++i) {
		int v = G[u][i];
		calc(v);
		int top = 0;
		while (heap[v].size()) {
			stk[++top] = std::max(heap[v].top(), heap[u].top());
			heap[v].pop();
			heap[u].pop();
		}
		for (int i = 1; i <= top; ++i)
			heap[u].emplace(stk[i]);
	}
	heap[u].emplace(M[u]);
}

int main(void)
{
	freopen("spring.in", "r", stdin);
	freopen("spring.out", "w", stdout);
	read >> n;
	for (int i = 1; i <= n; ++i)
		read >> M[i];
	for (int i = 2; i <= n; ++i) {
		read >> fa[i];
		G[fa[i]].emplace_back(i);
	}
	init(1);
	auto cmp = [](int a, int b) { return maxDep[a] > maxDep[b]; };
	for (int i = 1; i <= n; ++i)
		std::sort(G[i].begin(), G[i].end(), cmp);
	calc(1);
	i64 res = 0;
	while (heap[1].size()) {
		res += heap[1].top();
		heap[1].pop();
	}
	printf("%lld\n", res);
	return 0;
}
