#include <cmath>
#include <cstdio>
#include <climits>
#include <cstring>
#include <algorithm>
#include <unordered_map>

using namespace std;

int bsgs(int a, int b, int p)
{
	if (1 % p == b % p) return 0;
	unordered_map<int, int> hush;
	int k = sqrt(p) + 1;
	for (int i = 0, j = b; i < k; ++i, j = 1ll * j * a % p) hush[j] = i;
	int ak = 1;
	for (int i = 1; i <= k; ++i) ak = 1ll * a * ak % p;
	for (int i = 1, j = ak; i <= k; ++i, j = 1ll * j * ak % p)
		if (hush.count(j)) return i * k - hush[j];
	return -1;
}

int main(void)
{
	int a, b, p;
	while (~scanf("%d%d%d",&p, &a, &b)) {
		int tmp = bsgs(a, b, p);
		if (~tmp) printf("%d\n", tmp);
		else puts("no solution");
	}
	return 0;
}