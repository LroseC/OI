#include <vector>
#include <cstdio>
#include <cstring>

using namespace std;

#define reg register
#define ll long long
const int N = 100;

int T;
int n, m;
vector<int> sq[N];
bool br[N], brt[N];

namespace IDA_star
{
	bool check(vector<int> &);
	int f(void);
	bool DFS(int);
}

int main()
{
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);

		m = 0;
		for (int i = 1; i <= n; ++i)
			for (int a = 1; a + i - 1 <= n; ++a)
				for (int b = 1; b + i - 1 <= n; ++b) {
					sq[m].clear();
					for (int j = 0; j < i; ++j) {
						int d = 2 * n + 1;
						sq[m].push_back((a - 1) * d + b + j);
						sq[m].push_back((a - 1 + i) * d + b + j);
						sq[m].push_back(n + 1 + (a - 1) * d + b - 1 + j * d);
						sq[m].push_back(n + 1 + (a - 1) * d + b - 1 + j * d + i);
					}
					++m;
				}

		memset(br, 0, sizeof br);
		int k;
		scanf("%d", &k);
		for (int i = 0, t; i < k; ++i) {
			scanf("%d", &t);
			br[t] = 1;
		}

		int dep = 0;
		while (!IDA_star::DFS(dep)) ++dep;
		printf("%d\n", dep);
	}

	return 0;
}
bool IDA_star::check(vector<int> &s)
{
	for (int i = 0; i < s.size(); ++i)
		if (br[s[i]]) return 0;
	return 1;
}
int IDA_star::f(void)
{
	using namespace IDA_star;
	int res = 0;
	memcpy(brt, br, sizeof brt);
	for (int i = 0; i < m; ++i) {
		auto &s = sq[i];
		if (check(s))
		{
			++res;
			for (int i = 0; i < s.size(); ++i) br[s[i]] = 1;
		}
	}
	memcpy(br, brt, sizeof br);
	return res;
}
bool IDA_star::DFS(int dep)
{
	using namespace IDA_star;
	if (f() > dep) return 0;

	for (int i = 0; i < m; ++i) {
		auto &s = sq[i];
		if (!check(s)) continue;
		for (int j = 0; j < s.size(); ++j) {
			br[s[j]] = 1;
			if (DFS(dep - 1)) return 1;
			br[s[j]] = 0;
		}
		return 0;
	}
	return 1;
}
