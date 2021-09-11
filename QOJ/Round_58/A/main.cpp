#include <cctype>
#include <cstdio>
#include <algorithm>

using namespace std;

typedef long long LL;

inline LL read(void)
{
	LL res = 0, f = 1; char ch;
	while (!isdigit(ch = getchar())) if (ch == '-') f = -1;
	do res = res * 10 + ch - '0'; while (isdigit(ch = getchar()));
	return res * f;
}

const int N = 4e6 + 10;


int n;
LL a[N];
int id[N];
bool vis[N];
int ans;

inline bool cmp(int x, int y)
{
	return a[x] < a[y];
}

int main(void)
{
	n = read();
	for (int i = 1; i <= n; ++i) {
		id[i] = i;
		a[i] = read();
	}
	sort(id + 1, id + 1 + n, cmp);
	for (int i = 1; i <= n; ++i) {
		if (vis[id[i]]) continue;
		int p = id[i];
		int l = p, r = p;
		while (r <= n && !(a[r] % a[p])) ++r;
		while (l >= 1 && !(a[l] % a[p])) --l;
		--r, ++l;
		ans = max(ans, r - l + 1);
		for (int i = l; i <= r; ++i) vis[i] = 1;
	}
	printf("%d\n", ans);
	return 0;
}