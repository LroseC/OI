#include <vector>
#include <cctype>
#include <cstdio>
#include <cstring>
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

const int N = 2e5 + 10, B = 410;

struct Query
{
	int id, l, r;
	bool operator<(const Query &other) const
	{
		if (l / B != other.l / B) return l < other.l;
		return r < other.r;
	}
};

int n, m;
int A[N];
Query q[N];
int ans[N];
int left[N], right[N];
std::pair<int, int> stk[N]; int top = 0;

void Add(int pos, int &res)
{
	if (pos > right[A[pos]])
		right[A[pos]] = pos;
	if (pos < left[A[pos]])
		left[A[pos]] = pos;
	res = std::max(res, right[A[pos]] - left[A[pos]]);
}
void Dec(int pos)
{
	left[A[pos]] = 0x3f3f3f3f;
	right[A[pos]] = 0xcfcfcfcf;
}

int main(void)
{
	read >> n;
	std::vector<int> nums(n);
	for (int i = 1; i <= n; ++i) {
		read >> A[i];
		nums[i - 1] = A[i];
	}
	std::sort(nums.begin(), nums.end());
	nums.erase(std::unique(nums.begin(), nums.end()), nums.end());
	for (int i = 1; i <= n; ++i)
		A[i] = std::lower_bound(nums.begin(), nums.end(), A[i]) - nums.begin();

	read >> m;
	for (int i = 1; i <= m; ++i) {
		q[i].id = i;
		read >> q[i].l >> q[i].r;
	}
	std::sort(q + 1, q + 1 + m);

	int L, R, res;
	for (int i = 1; i <= m; ++i) {
		if (i == 1 || q[i].l / B != q[i - 1].l / B) {
			res = 0;
			memset(left, 0x3f, sizeof left);
			memset(right, 0xcf, sizeof right);
			L = q[i].l / B * B + B; R = L - 1;
		}
		if (q[i].l / B == q[i].r / B) {
			int res = 0;
			for (int j = q[i].l; j <= q[i].r; ++j)
				Add(j, res);
			ans[q[i].id] = res;
			for (int j = q[i].l; j <= q[i].r; ++j)
				Dec(j);
		}
		else {
			while (R < q[i].r) Add(++R, res);
			int tmp = res;
			for (int j = L - 1; j >= q[i].l; --j) {
				stk[++top] = std::make_pair(left[A[j]],right[A[j]]);
				Add(j, res);
			}
			ans[q[i].id] = res;
			for (int j = q[i].l; j <= L - 1; ++j) {
				left[A[j]] = stk[top].first;
				right[A[j]] = stk[top].second;
				--top;
			}
			res = tmp;
		}
	}
	for (int i = 1; i <= m; ++i)
		printf("%d\n", ans[i]);
	return 0;
}
