#include <queue>
#include <vector>
#include <cctype>
#include <cstdio>
#include <algorithm>
#include <functional>

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

using i32 = int;
using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;
using vi32 = std::vector<i32>;
using PII = std::pair<i32, i32>;

const int N = 1e5 + 10;

i32 n, m;
i32 fa[N], del[N];
std::priority_queue<PII, std::vector<PII>, std::greater<PII>> heap[N];

i32 find(i32 u)
{
	while (u != fa[u]) {
		u = fa[u];
	}
	return u;
}
int main(void)
{
	//Think twice, code once.
	read >> n >> m;
	for (int i = 1; i <= n; ++i) {
		fa[i] = i;
		i32 x; read >> x;
		heap[i].emplace(x, i);
	}
	while (m--) {
		i32 op; read >> op;
		if (op == 1) {
			i32 x, y;
			read >> x >> y;
			if (del[x] || del[y]) continue;
			if (find(x) != find(y)) {
				x = find(x), y = find(y);
				if (heap[x].size() > heap[y].size()) {
					std::swap(x, y);
				}
				fa[x] = y;
				while (heap[x].size()) {
					PII u = heap[x].top();
					heap[x].pop();
					heap[y].emplace(u);
				}
			}
		}
		else {
			i32 x;
			read >> x;
			if (del[x]) {
				puts("-1");
			}
			else {
				i32 f = find(x);
				PII pr = heap[f].top();
				del[pr.second] = 1;
				heap[f].pop();
				printf("%d\n", pr.first);
			}
		}
	}
	return 0;
}
