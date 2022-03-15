#include <vector>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>

using namespace std;

inline int read(void)
{
	int res = 0, f = 1; char ch = getchar();
	while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
	while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
	return res * f;
}

int T;
int n;
int f[25010];
vector<int> a;

int main(void)
{
	T = read();
	while (T--) {
		n = read();
		a.resize(n);
		memset(f, 0, sizeof f);
		for (int i = 0; i < n; ++i) a[i] = read();
		sort(a.begin(), a.end());
		f[0] = 1;
		int ans = n;
		for (int i = 0; i < n; ++i) {
			if (f[a[i]]) { --ans; continue; }
			for (int j = a[i]; j <= 25000; ++j) 
				f[j] += f[j - a[i]];
		}
		printf("%d\n", ans);
	}
	return 0;
}