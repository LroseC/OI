#include <bits/stdc++.h>

using namespace std;

const int N = 1e6 + 10;
typedef pair<int, int> PII;

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
int ans[N];
bool vis[N];
vector<int> nums;
priority_queue<PII> heap;

inline bool cmp(int a, int b)
{
	return cnt[a] > cnt[b];
}

inline int init(void)
{
	return 0;
}
inline int work(void)
{
	int n = read(), x = read();
	nums.clear();
	memset(b, 0, n + 1 << 2);
	memset(cnt, 0, n + 1 << 2);
	memset(ans, 0, n + 1 << 2);
	while (heap.size()) heap.pop();
	memset(vis, 0, n + 1 * sizeof(bool));
	for (int i = 1; i <= n; ++i) a[i] = read();
	if (x < 0) {
		puts("yes");
		sort(a + 1, a + 1 + n);
		for (int i = 1; i <= n; ++i) write(a[i], ' ');
		putchar('\n');
	}
	else if (x == 0) {
		PII tmp;
		set<PII> S;
		sort(a + 1, a + 1 + n);
		for (int i = 1; i <= n; ++i) {
			if (i == 1) tmp = {1, a[i]};
			else {
				if (a[i] == a[i - 1]) ++tmp.first;
				else {
					S.insert(tmp);
					tmp = {1, a[i]};
				}
			}
		}
		S.insert(tmp);

		for (int i = 1; i <= n; ++i) {
			auto it = S.end(); --it;
			if (i > 1 && it->second == a[i - 1] && it != S.begin()) {
				--it;
				auto tmp = *it; S.erase(it);
				a[i] = tmp.second;
				--tmp.first;
				if (tmp.first) S.insert(tmp);
			}
			else {
				auto tmp = *it; S.erase(it);
				a[i] = tmp.second;
				--tmp.first;
				if (tmp.first) S.insert(tmp);
			}
		}
		bool fail = 0;
		for (int i = 1; i <= n; ++i)
			if (a[i] - a[i - 1] == x) {
				fail = 1;
				break;
			}
		if (fail) puts("no");
		else {
			puts("yes");
			for (int i = 1; i <= n; ++i) write(a[i], ' ');
			putchar('\n');
		}
	}
	else {
		sort(a + 1, a + 1 + n, greater<int>());
		bool sec = 0;
		int special = -1;
		for (int i = 1; i <= n; ++i)
			if (a[i] != x && a[i] != 0) {
				special = i;
				break;
			}
		if (special == -1) puts("no");
		else {
			puts("yes");
			write(a[special], ' ');
			for (int i = 1; i <= n; ++i)
				if (i != special)
					write(a[i], ' ');
			putchar('\n');
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