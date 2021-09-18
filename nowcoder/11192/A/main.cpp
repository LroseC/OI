#include <map>
#include <vector>
#include <cctype>
#include <cstdio>
#include <algorithm>
#include <functional>

using namespace std;

typedef long long LL;
const int N = 1e5 + 10;
typedef pair<int, int> PII;

inline int read(void)
{
	int res = 0, f = 1; char ch = getchar();
	while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
	while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
	return res * f;
}

int n, m;
int a[N];
int mp[N];

int main(void)
{
	n = read(), m = read();
	for (int i = 1; i <= n; ++i) a[i] = read();
	sort(a + 1, a + 1 + n);
	while (m--) {
		int x = read(), y = read();
		++mp[x], --mp[y];
	}
	vector<int> tmp1, tmp2;
	for (int i = 1; i <= n; ++i) {
		if (mp[i] < 0)
			tmp1.emplace_back(mp[i]);
		else if (mp[i] > 0)
			tmp2.emplace_back(mp[i]);
	}
	sort(tmp1.begin(), tmp1.end());
	sort(tmp2.begin(), tmp2.end(), greater<int>());
	int i = n;
	LL ans = 0;
	for (int t : tmp1) {
		ans += t * a[i--];
	}
	i = 1;
	for (int t : tmp2) {
		ans += t * a[i++];
	}
	printf("%lld\n", ans);
	return 0;
}