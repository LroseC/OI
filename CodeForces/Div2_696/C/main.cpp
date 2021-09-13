#include <set>
#include <vector>
#include <cctype>
#include <cstdio>
#include <algorithm>

using namespace std;

const int N = 2010;
typedef pair<int, int> PII;
inline int read(void)
{
	int res = 0, f = 1; char ch;
	while (!isdigit(ch = getchar())) if (ch == '-') f = -1;
	do res = res * 10 + ch - '0'; while (isdigit(ch = getchar()));
	return res * f;
}

int n;
int a[N];
int top;
PII ans[N];
bool vis[N];
multiset<int> S;

bool dfs(int sum)
{
	if (S.empty()) return 1;
	auto it = S.end(); --it;
	int tmp = *it;
	S.erase(it);
	auto jt = S.find(sum - tmp);
	if (jt == S.end()) {
		S.insert(tmp);
		return 0;
	}
	ans[++top] = {tmp, *jt};
	S.erase(jt);
	if (dfs(max(ans[top].first, ans[top].second))) return 1;
	S.insert(ans[top].first);
	S.insert(ans[top].second);
	--top;
	return 0;
}

int main(void)
{
	int T = read();
	while (T--) {
		n = read();
		S.clear();
		bool fail = 1;
		int nn = n << 1;
		for (int i = 1; i <= nn; ++i) {
			a[i] = read();
			S.insert(a[i]);
		}
		sort(a + 1, a + 1 + nn);
		S.erase(S.find(a[nn]));
		for (int i = 1; i < nn; ++i) {
			top = 0;
			S.erase(S.find(a[i]));
			vis[i] = 1;
			if (dfs(a[nn])) {
				puts("YES");
				printf("%d\n", a[i] + a[nn]);
				printf("%d %d\n", a[i], a[nn]);
				for (int i = 1; i <= top; ++i)
					printf("%d %d\n", ans[i].first, ans[i].second);
				fail = 0;
				break;
			}
			vis[i] = 0;
			S.insert(a[i]);
		}
		if (fail) puts("NO");
	}
}