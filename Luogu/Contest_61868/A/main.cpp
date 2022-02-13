#include <set>
#include <vector>
#include <cstdio>

using namespace std;

const int N = 1e5 + 10;

int n;
multiset<int> S;
int ans[N];
int sum[N];

int main(void)
{
	scanf("%d", &n);
	int m = n * (n + 1) / 2;
	for (int i = 1; i <= m; ++i) {
		int x; scanf("%d", &x);
		S.insert(x);
	}
	for (int i = 1; i <= n; ++i) {
		sum[i] = ans[i] = *S.begin();
		sum[i] += sum[i - 1];
		for (int j = 1; j <= i; ++j) {
			auto it = S.find(sum[i] - sum[j - 1]);
			S.erase(it);
		}
	}
	for (int i = 1; i <= n; ++i)
		printf("%d ", ans[i]);
	puts("");
	return 0;
}
