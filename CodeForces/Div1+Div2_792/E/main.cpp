#include <set>
#include <map>
#include <queue>
#include <cctype>
#include <cstdio>

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

std::set<int> vis;
std::map<int, int> cnt;

void solve(void)
{
	read >> n >> K;
	vis.clear();
	cnt.clear();
	std::priority_queue<int> del;
	for (int i = 1; i <= n; ++i) {
		read >> a[i];
		++cnt[a[i]];
	}
	for (int i = 1; i <= n; ++i)
		if (a[i] > n && vis.find(a[i]) == vis.end()) {
			vis.insert(a[i]);
			del.emplace(cnt[a[i]]);
		}
	int space = 0;
	for (int i = 1; i <= n; ++i)
		if (!cnt.count(i)) ++space;
	for (int MEX = n; MEX >= 0; --MEX) {
	}
}

int main(void)
{
	int T; read >> T;
	while (T--) {
		solve();
	}
	return 0;
}
