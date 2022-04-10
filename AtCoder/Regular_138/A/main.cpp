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
		while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
		res = res * f; return *this;
	}
} read;

using i64 = long long;
const int N = 4e5 + 10;
inline int lowbit(int x) { return x & -x; }

int n, K;
int val[N], tr[N];
std::vector<int> nums;

void add(int x, int v)
{
	for (int i = x; i < N; i += lowbit(i))
		tr[i] = std::max(tr[i], v);
}
int query(int x)
{
	int res = 0;
	for (int i = x; i; i -= lowbit(i))
		res = std::max(res, tr[i]);
	return res;
}

int main(void)
{
	read >> n >> K;
	for (int i = 1; i <= n; ++i) {
		read >> val[i];
		nums.emplace_back(val[i]);
	}
	std::sort(nums.begin(), nums.end());
	nums.erase(std::unique(nums.begin(), nums.end()), nums.end());
	for (int i = 1; i <= n; ++i)
		val[i] = std::lower_bound(nums.begin(), nums.end(), val[i]) - nums.begin() + 1;
	for (int i = 1; i <= K; ++i)
		add(val[i], i);
	bool flag = 0;
	int ans = 0x3f3f3f3f;
	for (int i = K + 1; i <= n; ++i) {
		int t = query(val[i] - 1);
		if (t) {
			flag = 1;
			ans = std::min(ans, i - t);
		}
	}
	printf("%d\n", flag ? ans : -1);
	return 0;
}
