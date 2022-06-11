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
	int n, K;
	read >> n >> K;
	std::vector<int> a(n), b(K);
	for (int i = 0; i < n; ++i) {
		read >> a[i];
	}
	for (int i = 0; i < K; ++i) {
		read >> b[i];
	}
	int maxN = 0;
	for (int i = 0; i < n; ++i) {
		maxN = std::max(maxN, a[i]);
	}
	for (int i = 0; i < K; ++i) {
		if (a[b[i] - 1] == maxN) {
			puts("Yes");
			return 0;
		}
	}
	puts("No");
	return 0;
}
