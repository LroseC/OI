#include <cstdio>
#include <algorithm>

using namespace std;

const int N = 2e5 + 10;

int n;
struct Node
{
	int id, val;
	bool operator<(const Node &b) const
	{
		return val > b.val;
	}
}a[N];

int main(void)
{
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		a[i].id = i;
		scanf("%d", &a[i].val);
	}
	sort(a + 1, a + 1 + n);
	printf("%d\n", a[2].id);
	return 0;
}
