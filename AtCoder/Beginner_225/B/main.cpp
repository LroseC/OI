#include <cstdio>

using namespace std;

const int N = 1e5 + 10;

int cnt[N];

int main(void)
{
	int n; scanf("%d", &n);
	for (int i = 1; i < n; ++i) {
		int u, v;
		scanf("%d%d", &u, &v);
		++cnt[u]; ++cnt[v];
	}
	for (int i = 1; i <= n; ++i) {
		if (cnt[i] == n - 1) {
			puts("Yes");
			return 0;
		}
	}
	puts("No");
	return 0;
}