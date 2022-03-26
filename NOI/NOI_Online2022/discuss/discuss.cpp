#include <bits/stdc++.h>

struct FSI
{
	template<typename T>
	FSI& operator>>(T &res)
	{
		res = 0; T f = 1; char ch = getchar();
		while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
		while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
		res = res * f; return *this;
	}
} myread;

using i64 = long long;
const int N = 1e6 + 10;

int n;
bool vis[N];
std::vector<int> pro[N], peo[N];
std::vector<int> cnt, tim;

void work(void)
{
	myread >> n;
	for (int i = 1; i <= n; ++i) {
		int cnt; myread >> cnt;
		pro[i].resize(cnt);
		for (int j = 0; j < cnt; ++j) {
			myread >> pro[i][j];
			peo[pro[i][j]].emplace_back(i);
		}
		std::sort(pro[i].begin(), pro[i].end());
	}
	for (int i = 1; i <= n; ++i)
		for (int j = i + 1; j <= n; ++j) {
			int a = i, b = j;
			if (pro[a].size() > pro[b].size())
				std::swap(a, b);
			if (pro[a].size() == pro[b].size()) {
				bool flag2 = 0;
				for (int v : pro[a]) {
					auto it = std::lower_bound(pro[b].begin(), pro[b].end(), v);
					if (it != pro[b].end() && *it == v)
						flag2 = 1;
				}
				if (flag2) {
					puts("YES");
					printf("%d %d\n", a, b);
					return;
				}
			}
			else {
				bool flag1 = 0, flag2 = 0;
				for (int v : pro[a]) {
					auto it = std::lower_bound(pro[b].begin(), pro[b].end(), v);
					if (it != pro[b].end() || *it == v)
						flag2 = 1;
					else
						flag1 = 1;
				}
				if (flag1 && flag2) {
					puts("YES");
					printf("%d %d\n", a, b);
					return;
				}
			}
		}
	puts("NO");
	/*
	auto cmp = [](int a, int b) {
		return pro[a].size() < pro[b].size();
	};
	for (int i = 1; i <= n; ++i) {
		std::sort(peo[i].begin(), peo[i].end(), cmp);
		if (peo[i].size() == 1) continue;
		int tcnt = 0;
		for (int j = peo[i].size() - 2; j >= 0; --j)
			for (int k = j - 1; k >= 0; --k) {
			}
	}
	puts("NO");
	*/
}
void clear(void)
{
	cnt.clear();
	tim.clear();
	for (int i = 1; i <= n; ++i) {
		vis[i] = 0;
		peo[i].clear();
		pro[i].clear();
	}
}

int main(void)
{
	freopen("discuss.in", "r", stdin);
	freopen("discuss.out", "w", stdout);
	int T; myread >> T;
	while (T--) {
		work();
		clear();
	}
	return 0;
}
