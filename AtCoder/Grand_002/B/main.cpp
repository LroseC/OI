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

int n, m;
int cnt[N];
bool vis[N];

int main(void)
{
	cin >> n >> m;
	for (int i = 1; i <= n; ++i) cnt[i] = 1;
	vis[1] = 1;
	int res = 1;
	for (int i = 1; i <= m; ++i) {
		int x, y; cin >> x >> y;
		if (vis[x]) {
			if (!vis[y]) {
				++res;
				vis[y] = 1;
			}
			if (cnt[x] == 1) {
				--res;
				vis[x] = 0;
			}
		}
		--cnt[x]; ++cnt[y];
	}
	printf("%d\n", res);
	return 0;
}