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

const int N = 5000 + 30000 + 10;
using pii = pair<int, int>;

int n, m;
pii a[N], b[N]; int idx;

int main(void)
{
	IO >> n >> m;
	build();
	for (int i = 1; i <= n; ++i) {
		IO >> a[i].first >> a[i].second;
		b[i].first = 1;
	}
	for (int i = 1; i <= m; ++i) {
		int op; IO >> op;
		if (op == 1) {
	return 0;
}
