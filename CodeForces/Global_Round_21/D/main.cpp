#include <vector>
#include <iostream>
#include <algorithm>

using i64 = long long;
using vint = std::vector<int>;
using PII = std::pair<int, int>;
const int N = 5e5 + 10, LG = 20;

int stk[N], top;
int max[N][LG], min[N][LG], lg2[N], nexMin[N], nexMax[N];

void buildMin(vint &a)
{
	int n = a.size();
	for (int i = 0; i < n; ++i)
		min[i][0] = i;
	for (int o = 1; o < LG; ++o)
		for (int i = 0; (i + (1 << o - 1)) < n; ++i) {
			int x = min[i][o - 1], y = min[i + (1 << o - 1)][o - 1];
			min[i][o] = a[x] < a[y] ? x : y;
		}
}
void buildMax(vint &a)
{
	int n = a.size();
	for (int i = 0; i < n; ++i)
		max[i][0] = i;
	for (int o = 1; o < LG; ++o)
		for (int i = 0; (i + (1 << o - 1)) < n; ++i) {
			int x = max[i][o - 1], y = max[i + (1 << o - 1)][o - 1];
			max[i][o] = a[x] > a[y] ? x : y;
		}
}
int queryMin(int L, int R, vint &a)
{
	int o = lg2[R - L + 1];
	int x = min[L][o], y = min[R - (1 << o) + 1][o];
	return a[x] < a[y] ? x : y;
}
int queryMax(int L, int R, vint &a)
{
	int o = lg2[R - L + 1];
	int x = max[L][o], y = max[R - (1 << o) + 1][o];
	return a[x] > a[y] ? x : y;
}

int main(void)
{
	//Think twice, code once.
	std::ios::sync_with_stdio(false);
	for (int i = 2; i < N; ++i) lg2[i] = lg2[i >> 1] + 1;
	int tt; std::cin >> tt;
	while (tt--) {
		int n; std::cin >> n;
		vint a(n);
		for (int i = 0; i < n; ++i) {
			std::cin >> a[i];
		}
		buildMax(a);
		buildMin(a);
		top = 0;
		for (int i = n - 1; i >= 0; --i) {
			while (top && a[i] > a[stk[top]]) --top;
			if (!top) nexMax[i] = n;
			else nexMax[i] = stk[top];
			stk[++top] = i;
		}
		top = 0;
		for (int i = n - 1; i >= 0; --i) {
			while (top && a[i] < a[stk[top]]) --top;
			if (!top) nexMin[i] = n;
			else nexMin[i] = stk[top];
			stk[++top] = i;
		}
		int pos = 0, res = 0;
		while (pos != n - 1) {
			if (a[pos] > a[pos + 1]) {
				++res;
				int ed = nexMax[pos];
				pos = queryMin(pos + 1, ed - 1, a);
			}
			else {
				++res;
				int ed = nexMin[pos];
				pos = queryMax(pos + 1, ed - 1, a);
			}
		}
		std::cout << res << '\n';
	}
	return 0;
}
