#include <cstdio>
#include <algorithm>

using namespace std;

const int N = 1e6 + 30;

int n, m;
char str[N];
int a[N];
int b[N];
int c[N];
int cnt[N];
int res = 0, ans = 0;

int add(int x)
{
	++res;
	// ++c;
	// cnt[x] += c;
	if (str[x] == 0) {
		++str[x];
		return x;
	}
	else {
		--str[x];
		cnt[x] = 0;
		add(x + 1);
	}
}

int main(void)
{
	scanf("%d%d", &n, &m);
	scanf("%s", str);
	for (int i = 0; i < n; ++i) str[i] -= '0';
	for (int i = 0; i < m; ++i) {
		scanf("%d", &a[i]);
		++b[a[i]];
	}
	int ans = 0;
	for (int i = 0, ccc = 0, cnt = 0; i < N; ++i) {
		ccc += b[i];
		c[i] += b[i];
		res += c[i];
		if (c[i] + str[i] > 1) {
			++cnt;
			ans = max(ans, cnt);
		}
		else cnt = 0;
		c[i + 1] += (c[i] + str[i]) >> 1;
	}
	printf("%d\n%d\n", res, ans + 1);
	return 0;
}