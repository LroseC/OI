#include <map>
#include <queue>
#include <vector>
#include <cstring>
#include <climits>
#include <iostream>
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

using i32 = int;
using i64 = long long;
using u64 = unsigned long long;
using vi32 = std::vector<i32>;
using PII = std::pair<i32, i32>;

i32 n, ans = 100;
u64 x;
u64 pw10[20];

bool check(i32 n, u64 x)
{
	int len = 0;
	int max = 0;
	while (x) {
		len += 1;
		max = std::max(max, int(x % 10));
		x /= 10;
	}
	if (len < n && max <= 1) return 0;
	return 1;
}
inline i32 getLen(u64 x)
{
	for (int i = 0; i < 20; ++i)
		if (x < pw10[i]) {
			return i;
		}
	return 20;
}
void BFS(u64 s)
{
	std::map<u64, i32> dis;
	std::queue<u64> q;
	q.emplace(s);
	dis[s] = 0;
	while (q.size()) {
		u64 u = q.front(); q.pop();
		i32 len = getLen(u);
		if (len == n) {
			ans = dis[u];
			return;
		}
		for (int i = 0; i < 20; ++i) {
			if (u / pw10[i]) {
				u64 v = u * (u / pw10[i] % 10);
				if (!dis.count(v)) {
					dis[v] = dis[u] + 1;
					q.emplace(v);
				}
			}
		}
	}
}

int main(void)
{
	//Think twice, code once.
	std::ios::sync_with_stdio(false);
	read >> n >> x;
	pw10[0] = 1;
	for (int i = 1; i < 20; ++i)
		pw10[i] = pw10[i - 1] * 10;
	BFS(x);
	printf("%d\n", ans == 100 ? -1 : ans);
	return 0;
}
