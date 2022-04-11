#include <set>
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
const int N = 1e5 + 10;

int n, m;
int a[N], b[2][N];
std::set<int> S;

int getAns(bool flag)
{
	int t = n;
	for (int i = 1; i <= n * 2 - 1; ++i)
		b[0][i] = a[i];
	if (flag) {
		for (int i = 1; i <= n * 2 - 1; ++i)
			printf("%d ", a[i]);
		puts("");
	}
	for (int i = 1; i < n; ++i) {
		if (flag)
			for (int j = 1; j <= i; ++j)
				printf("  ");
		for (int j = 1 + i; j <= n * 2 - 1 - i; ++j) {
			std::vector<int> tmp;
			for (int k = j - 1; k <= j + 1; ++k)
				tmp.emplace_back(b[i & 1 ^ 1][k]);
			std::sort(tmp.begin(), tmp.end());
			b[i & 1][j] = tmp[1];
			if (flag) printf("%d ", b[i & 1][j]);
		}
		if (flag) puts("");
	}
	return b[n & 1][n];
}

int main(void)
{
	read >> n >> m;
	for (int i = 1; i <= n * 2 - 1; ++i)
		a[i] = i;
	S.insert(getAns(1));
	while (std::next_permutation(a + 1, a + n * 2)) {
		int tmp = getAns(0);
		if (S.count(tmp) == 0) {
			getAns(1);
			S.insert(tmp);
		}
	}
	printf("S.size() = %d\n", S.size());
	return 0;
}
