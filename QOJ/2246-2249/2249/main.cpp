#include <cctype>
#include <cstdio>
#include <cstring>
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
const int N = 1e6 + 10;

int n, maxGap;
i64 gap[N], v[N];
i64 X[N], Y[N], f[N];

struct queue
{
	int q[N], hh, tt;

	queue(void)
	{ tt = -1, hh = 0; }
	inline int size(void)
	{ return tt - hh + 1; }
	void insert(int id)
	{
		while (size() && v[q[tt]] >= v[id])
			--tt;
		if (size() < 2) {
			q[++tt] = id;
			return;
		}
		while (size() >= 2) {
			int v = q[tt], u = q[tt - 1];
			i64 delYa = Y[id] - Y[v], delXa = X[id] - X[v];
			i64 delY = Y[v] - Y[u], delX = X[v] - X[u];
			if (delYa * delX >= delY * delXa)
				--tt;
			else
				break;
		}
		q[++tt] = id;
	}
	void pop_front(void)
	{ --tt; }

	const int operator[](const int pos) const
	{ return q[tt - pos]; }
} que[11][10];

int main(void)
{
	read >> n >> maxGap;
	for (int i = 0; i < n; ++i) {
		read >> gap[i] >> v[i];
	}
	std::memset(f, 0x3f, sizeof f);
	f[0] = 0;
	X[0] = v[0];
	que[gap[0]][0].insert(0);
	for (int i = 1; i <= n; ++i) {
		for (int gp = 1; gp <= maxGap; ++gp) {
			auto &q = que[gp][i % gp];
			if (q.size()) {
				while (q.size() > 1) {
					i64 deltaX = X[q[1]] - X[q[0]];
					i64 deltaY = Y[q[1]] - Y[q[0]];
					if (deltaY >= deltaX * (i / gp))
						q.pop_front();
					else
						break;
				}
				i64 nowi = i / gp, nowj = q[0] / gp;
				int tj = q[0];
				f[i] = std::min(f[i], f[q[0]] + v[q[0]] * (nowi - nowj));
			}
		}
		if (i != n) {
			X[i] = v[i], Y[i] = 1ll * (i / gap[i]) * v[i] - f[i];
			que[gap[i]][i % gap[i]].insert(i);
		}
	}
	for (int i = 1; i <= n; ++i)
		printf("%lld ", f[i] == 0x3f3f3f3f3f3f3f3f ? -1 : f[i]);
	puts("");
	return 0;
}
