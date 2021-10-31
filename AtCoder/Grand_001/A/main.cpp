#include <vector>
#include <cstdio>
#include <algorithm>

using namespace std;

int n;
vector<int> num;

int main(void)
{
	scanf("%d", &n);
	for (int i = 1; i <= n * 2; ++i) {
		int x; scanf("%d", &x);
		num.emplace_back(x);
	}
	sort(num.begin(), num.end());
	int res = 0;
	for (int i = 0; i < n; ++i) {
		res += num[i * 2];
	}
	printf("%d\n", res);
	return 0;
}