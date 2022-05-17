#include <deque>
#include <cctype>
#include <cstdio>
#include <cstring>

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
using PII = std::pair<int, int>;
const int N = 1e6 + 10;

int n, maxC;
int per[N], t[N];
int gap[N], cost[N];
int dis[N];
std::deque<PII> q[12][12];

inline double getIntersect(PII a, PII b)
{ return (0.0 + b.second - a.second) / (a.first - b.first); }
void insert(int k, int b, std::deque<PII>& q)
{
	auto now = std::make_pair(k, b);
	if (q.size() == 1) {
		if (q[0].first == k)
			q[0].second = std::min(q[0].second, b);
		else
			q.emplace_back(now);
		return;
	}
	int sz = q.size();
	while (sz >= 2 && getIntersect(q[sz - 2], q[sz - 1]) >= getIntersect(q[sz - 2], now)) {
		--sz;
		q.pop_back();
	}
	q.emplace_back(now);
}
void CDQ(int l, int r)
{
	if (l == r)
		return;
	int mid = l + r >> 1;
	CDQ(l, mid);
	for (int i = 1; i <= maxC; ++i)
		for (int j = 0; j < i; ++j)
			q[i][j].clear();
	for (int i = l; i <= mid; ++i) {
		int x = per[i];
		insert(cost[x], dis[x] - cost[x] * (x / gap[x]), q[gap[x]][x % gap[x]]);
	}
	for (int i = mid + 1; i <= r; ++i) {
		int x = per[i];
		for (int j = 1; j <= maxC; ++j) {
			auto &t = q[j][x % j];
			while (t.size() > 1 && getIntersect(t[0], t[1]) < x / j)
				t.pop_front();
			if (t.size())
				dis[x] = std::min(dis[x], t[0].first * (x / j) + t[0].second);
		}
	}
	CDQ(mid + 1, r);
	int i = l, j = mid + 1, k = l;
	while (i <= mid && j <= r) {
		if (cost[per[i]] >= cost[per[j]])
			t[k++] = per[i++];
		else
			t[k++] = per[j++];
	}
	while (i <= mid)
		t[k++] = per[i++];
	while (j <= r)
		t[k++] = per[j++];
	for (int i = l; i <= r; ++i)
		per[i] = t[i];
}

int main(void)
{
	read >> n >> maxC;
	for (int i = 0; i < n; ++i)
		read >> gap[i] >> cost[i];
	std::memset(dis, 0x3f, sizeof dis);
	dis[0] = 0;
	for (int i = 0; i <= n; ++i)
		per[i] = i;
	CDQ(0, n);
	for (int i = 1; i <= n; ++i)
		printf("%d\n", dis[i] == dis[N - 1] ? -1 : dis[i]);
	puts("");
	return 0;
}
