#include <cmath>
#include <cstdio>
#include <climits>
#include <cstring>
#include <algorithm>
#include <unordered_map>

using namespace std;

int exgcd(int a, int b, int &x, int &y)
{
	if (!b) {
		x = 1, y = 0;
		return a;
	}
	int d = exgcd(b, a % b, y, x);
	y -= a / b * x;
	return d;
}

int bsgs(int a, int b, int p)
{
	if (1 % p == b % p) return 0;
	unordered_map<int, int> hash;
	int k = sqrt(p) + 1;
	for (int i = 0, j = b % p; i < k; ++i, j = 1ll * j * a % p)
		hash[j] = i;
	int ak = 1;
	for (int i = 0; i < k; ++i) ak = 1ll * ak * a % p;
	for (int i = 1, j = ak; i <= k; ++i, j = 1ll * j * ak % p)
		if (hash.count(j)) return 1ll * i * k - hash[j];
	return INT_MIN;
}
int exbsgs(int a, int b, int p)
{
	b = (b % p + p) % p;
	if (1 % p == b % p) return 0;
	int x, y;
	int d = exgcd(a, p, x, y);
	if (d == 1) return bsgs(a, b, p);
	if (b % d) return INT_MIN;
	exgcd(a / d, p / d, x, y);
	return exbsgs(a, 1ll * b / d * x % (p / d), p / d) + 1;
}

int main(void)
{
	int a, b, p;
	while (scanf("%d%d%d", &a, &p, &b), a || b || p) {
		int tmp = exbsgs(a, b ,p);
		if (tmp >= 0) printf("%d\n", tmp);
		else puts("No Solution");
	}
	return 0;
}