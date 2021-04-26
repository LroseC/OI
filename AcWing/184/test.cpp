#include <cstdio>
#include <cstring>

using namespace std;

#define reg register
#define ll long long
const int N = 30;

int n, idx;
char e[3][N];
int path[N], q[N];
bool st[N];

bool check(void);
bool dfs(int);

int main()
{
	scanf("%d", &n);
	for (int i = 0; i < 3; ++i) scanf("%s", e[i]);
	for (int i = n - 1; i >= 0; --i)
		for (int j = 0; j < 3; ++j)
			if (!st[e[j][i] - 'A']) {
				st[e[j][i] - 'A'] = 1;
				q[idx++] = e[j][i] - 'A';
			}

	memset(st, 0, sizeof st);
	memset(path, 0xff, sizeof path);

	dfs(0);

	for (int i = 0; i < n; ++i) printf("%d%c", path[i], i == n - 1 ? '\n' : ' ');

	return 0;
}
bool dfs(int dep)
{
	if (dep == n) return 1;
	for (int i = 0; i < n; ++i)
		if (!st[i]) {
			st[i] = 1;
			path[q[dep]] = i;
			if (check() && dfs(dep + 1)) return 1;
			st[i] = 0;
			path[q[dep]] = -1;
		}

	return 0;
}
bool check(void)
{
	for (int i = n - 1, t = 0; i >= 0; --i) {
		int a = e[0][i] - 'A', b = e[1][i] - 'A', c = e[2][i] - 'A';
		if (~path[a] && ~path[b] && ~path[c]) {
			a = path[a], b = path[b], c = path[c];
			if (~t) {
				if ((a + b + t) % n != c) return 0;
				if (!i && a + b + t >= n) return 0;
				t = (a + b + t) / n;
			}
			else {
				if ((a + b + 1) % n != c && (a + b) % n != c) return 0;
				if (!i && a + b >= n) return 0;
			}
		}
		else t = -1;
	}
	return 1;
}
