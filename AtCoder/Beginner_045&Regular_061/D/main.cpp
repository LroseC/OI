#include <set>
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
} io;

using LL = long long;
using PII = pair<int, int>;

int H, W;
int n;
set<PII> S;
LL ans[10];

int main(void)
{
	io >> H >> W >> n;
	for (int i = 1; i <= n; ++i) {
		int x, y; io >> x >> y;
		S.insert(make_pair(x, y));
	}
	for (auto t : S) {
		for (int ddx = -1; ddx <= 1; ++ddx)
			for (int ddy = -1; ddy <= 1; ++ddy) {
				int cnt = 0;
				int x = t.first + ddx, y = t.second + ddy;
				if (x <= 1 || y <= 1 || x >= H || y >= W) continue;
				for (int dx = -1; dx <= 1; ++dx)
					for (int dy = -1; dy <= 1; ++dy)
						if (S.find(make_pair(x + dx, y + dy)) != S.end())
							++cnt;
				++ans[cnt];
			}
	}
	for (int i = 1; i <= 9; ++i) ans[i] /= i;
	ans[0] = 1ll * (W - 2) * (H - 2);
	for (int i = 1; i <= 9; ++i) ans[0] -= ans[i];
	for (int i = 0; i <= 9; ++i)
		printf("%lld\n", ans[i]);
	return 0;
}