#include <vector>
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

const int B = 448, N = 2e5 + 10;

int n, mode, res;

void calc1(int x, std::vector<int> &a)
{
	std::vector<int> first(n * 2);
	std::fill(first.begin(), first.end(), -2);
	int now = n;
	first[now] = -1;
	for (int i = 0; i < n; ++i) {
		if (a[i] == mode) ++now;
		if (a[i] == x) --now;
		if (first[now] == -2)
			first[now] = i;
		else
			res = std::max(res, i - first[now]);
	}
}
void calc2(int x, std::vector<int> &a)
{
	std::vector<int> cnt(n + 1);
	int maxCnt = 0;
	for (int l = 0, r = 0; r < n; ++r) {
		++cnt[a[r]];
		if (cnt[a[r]] == x)
			++maxCnt;
		while (cnt[a[r]] > x) {
			if (cnt[a[l]] == x)
				--maxCnt;
			--cnt[a[l++]];
		}
		if (maxCnt >= 2) res = std::max(res, r - l + 1);
	}
}

int main(void)
{
	read >> n;
	if (n == 1) {
		puts("0");
		return 0;
	}
	std::vector<int> a(n), cnt(n + 1);
	for (int i = 0; i < n; ++i) {
		read >> a[i];
		++cnt[a[i]];
		if (cnt[a[i]] > cnt[mode])
			mode = a[i];
	}
	for (int i = 1; i <= n; ++i)
		if (cnt[i] >= B && i != mode) calc1(i, a);
	for (int i = 1; i <= std::min(n, B); ++i)
		calc2(i, a);
	printf("%d\n", res);
	return 0;
}
