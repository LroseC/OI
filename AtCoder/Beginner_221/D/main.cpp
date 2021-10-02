#include <queue>
#include <cstdio>
#include <algorithm>

using namespace std;

const int N = 2e5 + 10;

typedef pair<int, int> PII;

int n;
int ans[N];
priority_queue< PII, vector<PII>, greater<PII> > heap;

int main(void)
{
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		int s, l, t; scanf("%d%d", &s, &l);
		t = s + l - 1;
		heap.emplace(PII({s, 1}));
		heap.emplace(PII({t + 1, -1}));
	}
	int now = 1, res = 0;
	while (heap.size()) {
		while (heap.size() && heap.top().first == now) {
			res += heap.top().second;
			heap.pop();
		}
		if (!heap.size()) break;
		ans[res] += (heap.top().first - now);
		now = heap.top().first;
		res += heap.top().second;
		heap.pop();
	}
	for (int i = 1; i <= n; ++i) printf("%d ", ans[i]);
	return 0;
}