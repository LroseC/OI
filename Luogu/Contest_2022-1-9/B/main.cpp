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

using uint = unsigned int;
const int N = 1e5 + 10, M = 1e6 + 10;

int n, m;
int p[N], a[N], b[N];

int main(void)
{
	IO >> n;
	for (int i = 1; i <= n; ++i)
		IO >> p[i];
	for (int i = 1; i <= n; ++i)
		IO >> a[i];
	for (int i = 1; i <= n; ++i)
		IO >> b[i];
	IO >> m;
	for (int i = 1; i <= m; ++i) {
		int l1, r1, l2, r2;
		IO >> l1 >> r1 >> l2 >> r2;
		uint res = 0;
		for (int j = 1; j <= n; ++j)
			for (int k = l1; k <= r1; ++k)
				if (l2 <= p[k] && p[k] <= r2) {
					if (a[k] == j) {
						res += b[a[k]];
						break;
					}
				}
		printf("%u\n", res);
	}
	return 0;
}
