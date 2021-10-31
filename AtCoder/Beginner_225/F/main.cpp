#include <queue>
#include <vector>
#include <cctype>
#include <cstdio>

using namespace std;
using vchar = vector<char>;

int n, m;

struct cmp
{
	bool operator()(const vchar &a, const vchar &b)
	{
		int l = min(a.size(), b.size());
		for (int i = 0; i < l; ++i) {
			if (a[i] < b[i]) return 0;
			if (a[i] > b[i]) return 1;
		}
		return a.size() > b.size();
	}
};

int main(void)
{
	scanf("%d%d", &n, &m);
	priority_queue<vchar, vector<vchar>, cmp> heap;
	for (int i = 1; i <= n; ++i) {
		vchar tmp; char ch = getchar();
		while (isspace(ch)) ch = getchar();
		while (!isspace(ch)) { tmp.emplace_back(ch); ch = getchar(); }
		heap.emplace(tmp);
	}
	for (int i = 1; i <= m; ++i) {
		auto tmp = heap.top(); heap.pop();
		for (auto x : tmp) putchar(x);
	}
	return 0;
}