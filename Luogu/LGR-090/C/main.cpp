#include <vector>
#include <cstdio>
#include <algorithm>

using namespace std;

const int N = 1e6;
int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }

int n;
int v[N];
int fa[N];
int yinshu[N];
bool cunzai[N];
int root;
bool haveroot[N];
vector<int> a;

bool cmp(int a, int b)
{
	return v[a] < v[b];
}

int main(void)
{
	scanf("%d", &n);
	bool flag = 1;
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &v[i]);
		cunzai[v[i]] = 1;
		if (i > 1 && v[i] != v[i - 1]) flag = 0;
		a.emplace_back(i);
	}
	sort(a.begin(), a.end(), cmp);
	if (n == 1) {
		puts("0");
		return 0;
	}
	else if (n == 2) {
		int tmp = gcd(v[1], v[2]);
		if (tmp == v[1]) puts("0 1");
		else if (tmp == v[2]) puts("2 0");
		else puts("-1");
		return 0;
	}
	else if (flag) {
		for (int i = 1; i <= n; ++i) printf("%d ", i - 1);
		return 0;
	}
	else {
		for (auto i : a) {
			if (!haveroot) {
				root = i;
				continue;
			}
			if (!yinshu[v[i]]) {
				if (v[a[0]] == 1 && a[0] != i) fa[i] = a[0];
				else if (i != a[0]) {
					puts("-1");
					return 0;
				}
			}
			if (!fa[i]) fa[i] = yinshu[v[i]];
			for (int j = 2; j * v[i] < N; ++j) {
				int k = j * v[i];
				if (yinshu[k]) {
					if (v[yinshu[k]] != 1 && gcd(v[yinshu[k]], v[i]) <= v[yinshu[k]] && cunzai[k]) {
						puts("-1");
						return 0;
					}
					else yinshu[k] = i;
				}
				else yinshu[k] = i;
			}
		}
		for (int i = 1; i <= n; ++i) printf("%d ", fa[i]);
	}
	return 0;
}