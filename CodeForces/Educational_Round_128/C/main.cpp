#include <cctype>
#include <cstdio>
#include <climits>
#include <cstring>
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
const int N = 2e5 + 10;

int n;
int cnt0, cnt1;
char str[N];

int getAns(int x)
{
	if (x == 0) {
		if (cnt1 == 0)
			return 0;
		int res = 0;
		int left = 1;
		while (left <= n && str[left] == '0')
			++left, ++res;
		int right = n;
		while (right >= 1 && str[right] == '0')
			--right, ++res;
		return cnt0 - res;
	}
	int ans = INT_MAX;
	int i = 1, j = 0, cnt = 0, res = 0;
	while (i <= n) {
		while (j <= n && cnt < cnt1 - x) {
			++j;
			if (str[j] == '1') ++cnt;
			else ++res;
		}
		if (j > n) break;
		ans = std::min(ans, res);
		if (str[i] == '0') --res;
		else --cnt;
		++i;
	}
	return ans;
}
bool check(int x) { return x <= getAns(x); }

void solve(void)
{
	scanf("%s", str + 1);
	n = std::strlen(str + 1);
	cnt0 = cnt1 = 0;
	for (int i = 1; i <= n; ++i) {
		if (str[i] == '0') ++cnt0;
		else ++cnt1;
	}
	int l = 0, r = cnt1, mid;
	while (l < r) {
		int mid = l + r + 1 >> 1;
		if (check(mid))
			l = mid;
		else
			r = mid - 1;
	}
	printf("%d\n", std::min(getAns(l), l + 1));
}

int main(void)
{
	int T; read >> T;
	while (T--)
		solve();
	return 0;
}
