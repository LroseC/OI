#include <vector>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <functional>

using namespace std;

typedef long long ll;

template<typename Int>inline void read(Int &res)
{
	res = 0; char ch = getchar();
	while (!isdigit(ch)) ch = getchar();
	while (isdigit(ch)) { res = res * 10 + (ch ^ '0'); ch = getchar(); }
}
template<typename Int>inline void write(Int x)
{
	static char buf[20];
	int p = -1;
	while (x) { buf[++p] = x % 10 ^ '0'; x /= 10; }
	while (p >= 0) { putchar(buf[p]); --p; }
}

int n,m,len,ans;
int a[100010];
bool vis[100010];
ll sum;


bool dfs(int now, int last, int depth)
{
	if (depth == m) return 1;
	if (now == len) return dfs(0, 1, depth + 1);
	int fail = 0;
	for (int i = last; i <= n; ++i) {
		if (!vis[i] && now + a[i] <= len && fail != a[i]) {
			vis[i] = 1;
			if (dfs(now + a[i], i + 1, depth)) return 1;
			fail = a[i];
			vis[i] = 0;
			if (now == 0 || now + a[i] == len) return 0;
		}
	}
	return 0;
}
int main()
{
	read(n);
	sum = 0;
	for (int i = 1; i <= n; ++i){
		read(a[i]);
		if (a[i] > 50) {
			--i, --n;
			continue;
		}
		sum += a[i];
	}
	ans = sum;
	sort(a + 1, a + 1 + n, greater<int>());
	for (len = 1;len < sum; ++len) {
		if (sum % len) continue;
		m = sum / len;
		if (dfs(0,0,0)) {
			ans = len;
			break;
		}
	}
	printf("%d\n",ans);
	return 0;
}