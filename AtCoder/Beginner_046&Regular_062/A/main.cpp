#include <vector>
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

vector<int> x;

int main(void)
{
	for (int i = 1; i <= 3; ++i) {
		int y; io >> y;
		x.emplace_back(y);
	}
	sort(x.begin(), x.end());
	printf("%d\n", unique(x.begin(), x.end()) - x.begin());
	return 0;
}