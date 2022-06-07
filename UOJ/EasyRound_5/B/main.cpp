#include <map>
#include <queue>
#include <vector>
#include <cctype>
#include <cstdio>
#include <algorithm>

struct FSI
{
	template<typename T>
	FSI& operator>>(T &res)
	{
		res = 0; T f = 1; char ch = getchar();
		while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
		while (isdigit(ch)) { res = res * 10 + (ch - '0') * f; ch = getchar(); }
		return *this;
	}
} read;

using i64 = long long;

inline bool cmp(int a, int b)
{ return (a & 1) > (b & 1); }
void solve(int l, int r, std::vector<int> &a)
{
	if (r - l <= 1) return;
	bool flag = 1;
	for (int i = l; i < r; ++i)
		if (a[i] != 0) flag = 0;
	if (flag) return;
	std::sort(a.begin() + l, a.begin() + r, cmp);
	int mid = l;
	while (mid < r && a[mid] & 1)
		++mid;
	for (int i = l; i < r; ++i)
		a[i] >>= 1;
	solve(l, mid, a);
	solve(mid, r, a);
	for (int i = l; i < mid; ++i)
		a[i] = a[i] << 1 | 1;
	for (int i = mid; i < r; ++i)
		a[i] = a[i] << 1;
}

int main(void)
{
	int n;
	read >> n;
	std::vector<int> a(n);
	std::map<int, std::queue<int>> mp;
	for (int i = 0; i < n; ++i) {
		read >> a[i];
		mp[a[i]].emplace(i + 1);
	}
	solve(0, n, a);
	for (int i = 0; i < n; ++i) {
		printf("%d ", mp[a[i]].front());
		mp[a[i]].pop();
	}
	puts("");
	return 0;
}
