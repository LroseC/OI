#include <vector>
#include <cctype>
#include <cstdio>
#include <algorithm>

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
		res *= f; return *this;
	}
} cin;

int n, k;
int vis[11];
int stk[1000];

bool check(int x)
{
	while (x) {
		if (vis[x % 10]) return 0;
		x /= 10;
	}
	return 1;
}

int main(void)
{
	cin >> n >> k;
	for (int i = 0; i < k; ++i) {
		int x; cin >> x;
		vis[x] = 1;
	}
	while (!check(n)) ++n;
	printf("%d\n", n);
	return 0;
}