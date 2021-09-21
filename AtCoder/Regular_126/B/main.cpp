#include <vector>
#include <cctype>
#include <cstdio>
#include <algorithm>

using namespace std;

typedef pair<int, int> PII;

inline int read(void)
{
	int res = 0, f = 1; char ch = getchar();
	while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
	while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
	return res * f;
}

int n, m;
vector<int> a;
vector<int> b;
vector<PII> tmp;

int main(void)
{
	n = read(), m = read();
	while (m--) {
		int a = read(), b = read();
		tmp.emplace_back(PII({a, b}));
	}
	sort(tmp.begin(), tmp.end());
	for (auto t : tmp) a.emplace_back(t.second);
	for (int x : a) {
		auto it = lower_bound(b.begin(), b.end(), x);
		if (it == b.end()) b.emplace_back(x);
		else *it = x;
	}
	printf("%d\n", b.size());
	return 0;
}