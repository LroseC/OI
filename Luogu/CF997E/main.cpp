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
		while (isdigit(ch))  { res = res * 10 + ch - '0'; ch = getchar(); }
		res = res * f; return *this;
	}
} IO;

const int N = 1.2e5 + 10;

int n;
int P[N];

int main(void)
{
	io >> n;
	for (int i = 1; i <= n; ++i) IO >> P[i];
	for (int i = 1; i <= n; ++i) {
	}
	return 0;
}
