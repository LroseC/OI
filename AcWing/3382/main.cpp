#include <cstdio>

using namespace std;

const int N = 1e6 + 10;
const int mod = 1e9;

int n;
int f[N];

int main()
{
	scanf("%d", &n);
	f[0] = 1;
	for (int i = 1; i <= n; i <<= 1)
		for (int j = i; j <= n; ++j) f[j] = (f[j] + f[j - i]) % mod;
	printf("%d\n", f[n]);
	return 0;
}
