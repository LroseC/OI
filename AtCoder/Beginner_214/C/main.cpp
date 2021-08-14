#include <queue>
#include <cstdio>

using namespace std;

#define int long long
const int N = 1e6 + 10;

struct PII
{
	int id, tim;
	bool operator<(const PII &b) const
	{
		return tim > b.tim;
	}
};

int n;
int s[N], t[N];
priority_queue<PII> heap;
int ans[N];

signed main(void)
{
	scanf("%lld", &n);
	for (int i = 0; i < n; ++i) scanf("%lld", &s[i]);
	for (int i = 0; i < n; ++i) {
		scanf("%lld", &t[i]);
		heap.push({i, t[i]});
	}
	while (heap.size()) {
		auto tmp = heap.top();
		heap.pop();
		if (ans[tmp.id]) continue;
		ans[tmp.id] = tmp.tim;
		heap.push({(tmp.id + 1) % n, tmp.tim + s[tmp.id]});
	}
	for (int i = 0; i < n; ++i) printf("%lld\n", ans[i]);
	return 0;
}