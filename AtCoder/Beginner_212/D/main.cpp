#include <queue>
#include <cstdio>
#include <algorithm>

using namespace std;

#define int long long

int q;
int tag;
priority_queue< int, vector<int>, greater<int> > heap;

signed main(void)
{
	scanf("%lld", &q);
	while (q--) {
		int op, x;
		scanf("%lld", &op);
		if (op == 1) {
			scanf("%lld", &x);
			heap.push(x - tag);
		}
		if (op == 2) {
			scanf("%lld", &x);
			tag += x;
		}
		if (op == 3) {
			printf("%lld\n", heap.top() + tag);
			heap.pop();
		}
	}
	return 0;
}
