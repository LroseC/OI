#include <cctype>
#include <cstdio>
#include <algorithm>

using namespace std;

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
} io;

const int N = 5e4 + 10;
using PII = pair<int, int>;

int n, K;
int A[N];
int left[N], right[N];
PII inter[N];

int main(void)
{
	io >> n >> K;
	for (int i = 1; i <= n; ++i) io >> A[i];
	sort(A + 1, A + 1 + n);
	for (int i = 1, j = 1; i <= n; ++i) {
		while (A[i] - A[j] > K && j <= i) ++j;
		left[i] = max(left[i - 1], i - j + 1);
	}
	for (int i = n, j = n; i >= 1; --i) {
		while (A[j] - A[i] > K && j >= i) --j;
		right[i] = max(right[i + 1], j - i + 1);
	}
	int ans = 0;
	for (int i = 1; i < n; ++i) {
		ans = max(ans, left[i] + right[i + 1]);
	}
	printf("%d\n", ans);
	return 0;
}