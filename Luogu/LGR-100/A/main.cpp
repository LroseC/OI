#include <cctype>
#include <cstdio>

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
} IO;

int T;

int main(void)
{
	IO >> T;
	while (T--) {
		long long x;
		IO >> x;
		while ((x & 1) == 0) x >>= 1;
		puts((x == 1 || x == 3) ? "0" : "1");
	}
	return 0;
}
