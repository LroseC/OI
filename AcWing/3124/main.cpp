#include <bits/stdc++.h>

using namespace std;

int BSGS(int a, int b, int p)
{
	if (1 % p == b % p) return 0;
	unordered_map<int, int> hash;
	int k = sqrt(p) + 1;
	for (int i = 0, j = b % p; i < k; ++i, j = 1ll * j * a % p) {
		hash[j] = i;
	}
	int ak = 1;
	for (int i = 1; i <= k; ++i) ak = 1ll * ak * a % p;
	for (int i = 1, j = ak; i <= k; ++i, j = 1ll * j * ak % p) {
		if (hash.count(j)) return 1ll * i * k - hash[j];
	}
	return -1;
}

int main(void)
{
	int a, b, p;
	while (scanf("%d%d%d", &a, &p, &b), a || b || p) {
		int tmp = BSGS(a, b, p);
		if (~tmp) printf("%d\n", tmp);
		else puts("No Solution");
	}
	return 0;
}