#include <vector>
#include <cctype>
#include <cstdio>

using namespace std;

struct FastStreamInput
{
	using FSI = FastStreamInput;
	template<typename T>
	FSI& operator >> (T &res)
	{
		res = 0; T f = 1; char ch = getchar();
		while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
		while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
		res = res * f; return *this;
	}
} cin;

const int N = 1e5 + 10;
using PII = pair<int, int>;

int n, L;
int a[N];
vector<PII> knots;

int main(void)
{
	cin >> n >> L;
	int maxn = -1, maxid = -1;
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
		if (i != 1) {
			int tmp = a[i - 1] + a[i];
			if (tmp > maxn) {
				maxid = i - 1;
				maxn = tmp;
			}
		}
	}
	if (maxn >= L) {
		puts("Possible");
		for (int i = 1; i < maxid; ++i) printf("%d\n", i);
		for (int i = n - 1; i > maxid; --i) printf("%d\n", i);
		printf("%d\n", maxid);
	}
	else puts("Impossible");
	return 0;
}