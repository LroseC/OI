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
} read;

const int N = 4e5 + 10;

int n, m;
int a[N], b[N], nex[N];

int main(void)
{
	read >> n >> m;
	if (m == 1) {
		printf("%d\n", n);
		return 0;
	}
	for (int i = 0; i < n; ++i)
		read >> a[i];
	for (int i = 0; i < m; ++i)
		read >> b[i];
	--n; --m;
	for (int i = 0; i < n; ++i)
		a[i] -= a[i + 1];
	for (int i = 0; i < m; ++i)
		b[i] -= b[i + 1];

	for (int i = 1, j = 0; i < m; ++i) {
		while (j && b[i] != b[j])
			j = nex[j - 1];
		if (b[i] == b[j])
			++j;
		nex[i] = j;
	}
	int ans = 0;
	for (int i = 0, j = 0; i < n; ++i) {
		while (j && a[i] != b[j])
			j = nex[j - 1];
		if (a[i] == b[j])
			++j;
		if (j == m) ++ans;
	}
	printf("%d\n", ans);
	return 0;
}
