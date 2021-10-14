#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10;

template<typename T = int>
inline T read(void)
{
	T res = 0, f = 1; char ch = getchar();
	while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
	while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
	return res * f;
}
template<typename T>
inline void write(T x, char end = '\n')
{
	static char buf[50]; int p = -1;
	if (x == 0) putchar('0');
	if (x < 0) { putchar('-'); x = -x; }
	while (x) { buf[++p] = x % 10; x /= 10; }
	while (~p) { putchar(buf[p] + '0'); --p; } putchar(end);
}

int a[N];
int b[N];
int cnt[N];
bool vis[N];
vector<int> nums;

inline bool cmp(int a, int b)
{
	return cnt[a] > cnt[b];
}

inline int init(void)
{
	memset(a, 0, sizeof a);
	memset(b, 0, sizeof b);
	memset(cnt, 0, sizeof cnt);
	memset(vis, 0, sizeof vis);
	nums.clear();
	return 0;
}
inline int work(void)
{
	int n = read(), x = read();
	for (int i = 1; i <= n; ++i) a[i] = read();
	if (x < 0) {
		puts("yes");
		sort(a + 1, a + 1 + n);
		for (int i = 1; i <= n; ++i) write(a[i], i == n ? '\n' : ' ');
	}
	else if (x == 0) {
		nums.clear();
		for (int i = 1; i <= n; ++i) nums.emplace_back(a[i]);
		sort(nums.begin(), nums.end());
		nums.erase(unique(nums.begin(), nums.end()), nums.end());
		memset(cnt, 0, sizeof cnt);
		for (int i = 1; i <= n; ++i)
			++cnt[lower_bound(nums.begin(), nums.end(), a[i]) - nums.begin()];
		for (int i = 0; i < nums.size(); ++i) b[i] = i;
		sort(b, b + nums.size(), cmp);
		if (cnt[b[0]] > n - cnt[b[0]] + 1) puts("no");
		else {
			puts("yes");
			for (int i = 0, j = 1; i < nums.size(); ++i) {
				if (!cnt[b[i]])
					continue;
				if (i == j) ++j;
				while (cnt[b[i]] > 1) {
					while (!cnt[b[j]]) ++j;
					--cnt[b[i]];
					--cnt[b[j]];
					write(nums[b[i]], ' ');
					write(nums[b[j]], ' ');
				}
				--cnt[b[i]];
				write(nums[b[i]], ' ');
			}
			putchar('\n');
		}
	}
	else {
		sort(a + 1, a + 1 + n, greater<int>());
		if (x != a[1]) {
			puts("yes");
			for (int i = 1; i <= n; ++i) write(a[i], i == n ? '\n' : ' ');
		}
		else {
			bool sec = 0;
			int special = -1;
			for (int i = 1; i <= n; ++i)
				if (a[i] != x && a[i] != 0) {
					sec = 1;
					special = i;
					break;
				}
			if (!sec) puts("no");
			else {
				puts("yes");
				write(a[special], ' ');
				for (int i = 1; i <= n; ++i)
					if (i != special)
						write(a[i], ' ');
				putchar('\n');
			}
		}
	}
	return 0;
}
int main(void)
{
	int T = read();
	while (T--) {
		init();
		work();
	}
	return 0;
}
