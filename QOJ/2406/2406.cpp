#include <cstdio>
#include <cstring>

using namespace std;

#define reg register
#define ll long long
#define max(a, b) (a > b ? a : b)
#define min(a, b) (a < b ? a : b);
const int N = 5e5 + 10;

int n, m;
char a[N];
int f[N];
int vis[N];

int main()
{
	scanf("%d\n", &n);
	scanf("%s", a + 1);
	for (int i = 1; i <= n; ++i)
		if (!vis[a[i]]) {
			vis[a[i]] = 1;
			++m;
		}

	memset(vis, 0, sizeof vis);
	int i = 0, j = 0;
	int now = 0;
	int ans = 0x3f3f3f3f;
	while (i <= n) {
		if (now != m) {
			++i;
			now += ++vis[a[i]] == 1;
		} else {
			ans = min(ans, i - j);
			++j;
			now -= --vis[a[j]] == 0;
		}
	}
	printf("%d\n", ans);
	
	return 0;
}
