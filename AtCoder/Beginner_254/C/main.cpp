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

int main(void)
{
	int n, K; read >> n >> K;
	std::vector<int> a(n);
	std::vector<std::vector<int>> arr(K);
	for (int i = 0; i < n; ++i) {
		read >> a[i];
		arr[i % K].emplace_back(a[i]);
	}
	std::sort(a.begin(), a.end());
	for (int i = 0; i < K; ++i)
		std::sort(arr[i].begin(), arr[i].end());
	for (int i = 0; i < n; ++i) {
		if (arr[i % K][i / K] != a[i]) {
			puts("No");
			return 0;
		}
	}
	puts("Yes");
	return 0;
}
