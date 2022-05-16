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

std::vector<int> getPer(int n)
{
	std::vector<int> res(n);
	res[0] = n / 2 + 1;
	int delta = 1, f = -1;
	for (int i = 1; i < n; ++i) {
		res[i] = res[i - 1] + delta * f;
		++delta;
		f *= -1;
	}
	return res;
}
std::vector<int> getPer2(int n)
{
	std::vector<int> res(n);
	res[0] = n / 2;
	int delta = 1, f = 1;
	for (int i = 1; i < n; ++i) {
		res[i] = res[i - 1] + delta * f;
		++delta;
		f *= -1;
	}
	return res;
}
int n, X;
int main(void)
{
	read >> n >> X;
	if (n & 1) {
		if (X == n / 2 + 1) {
			auto t = getPer(n);
			for (auto v : t)
				printf("%d ", v);
			puts("");
		}
		else {
			int m = n - 1;
			auto t = getPer(m);
			printf("%d ", X);
			for (auto v : t)
				printf("%d ", v + (v >= X));
			puts("");
		}
		return 0;
	}
	else {
		if (X == n / 2 + 1) {
			auto t = getPer(n);
			for (auto v : t)
				printf("%d ", v);
			puts("");
		}
		else if (X == n / 2) {
			auto t = getPer2(n);
			for (auto v : t)
				printf("%d ", v);
			puts("");
		}
		else {
			int m = n - 1;
			auto t = getPer(m);
			printf("%d ", X);
			for (auto v : t)
				printf("%d ", v + (v >= X));
			puts("");
		}
	}
	return 0;
}
