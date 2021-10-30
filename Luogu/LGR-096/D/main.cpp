#include <map>
#include <vector>
#include <string>
#include <cctype>
#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 5e3 + 10;

using vecint = vector<int>;

template<typename T = int>
T read(void)
{
	T res = 0, f = 1; char ch = getchar();
	while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
	while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
	return res * f;
}

int n;
bool isans[N];
vecint G[N];

inline vecint maxx(const vecint &a, const vecint &b)
{
	for (int i = 0; i < a.size(); ++i) {
		if (a[i] > b[i]) return a;
		if (a[i] < b[i]) return b;
	}
	return a;
}
struct cmpnum
{
	bool operator()(const vecint &a, const vecint &b)
	{
		if (a.size() == b.size()) {
			for (int i = 0; i < a.size(); ++i) {
				if (a[i] > b[i]) return 1;
				if (a[i] < b[i]) return 0;
			}
			return 0;
		}
		return a.size() < b.size();
	}
};
struct PII
{
	int x, y;
	PII() {}
	PII(int _x, int _y) : x(_x), y(_y) {}
	bool operator<(const PII &b) const
	{
		if (x != b.x) return x < b.x;
		return y < b.y;
	}
};
map<PII, vecint> M;

vecint dfs(int u, int fa)
{
	auto it = M.find(PII(u, fa));
	if (it != M.end()) return it->second;
	vecint res;
	vector<vecint> tmp;
	res.clear();
	tmp.clear();
	res.emplace_back(1);
	int cnt = 1;
	for (int v : G[u]) {
		if (fa == v) continue;
		tmp.emplace_back(dfs(v, u));
		cnt += tmp.back().size();
	}
	sort(tmp.begin(), tmp.end(), cmpnum());
	for (auto x : tmp) {
		cnt -= x.size();
		for (auto y : x)
			res.emplace_back(y + cnt);
	}
	return M[PII(u, fa)] = res;
}


int main(void)
{
	n = read();
	for (int i = 1; i < n; ++i) {
		int u = read(), v = read();
		G[u].emplace_back(v);
		G[v].emplace_back(u);
	}
	for (int i = 1; i <= n; ++i)
		if (G[i].size() == 1)
			for (int v : G[i]) {
				isans[v] = 1;
			}
	vecint res = dfs(1, -1);
	for (int i = 2; i <= n; ++i)
		if (isans[i])
			res = maxx(res, dfs(i, -1));
	for (int x : res) printf("%d ", x);
	return 0;
}