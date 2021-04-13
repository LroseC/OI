#include <cstdio>
#include <string>
#include <cstring>
#include <iostream>

using namespace std;

#define reg register
#define ll long long
const int N = 24;

int T;
int center[] = {6, 7, 8, 11, 12, 15, 16, 17};
int op[8][7] = {
	{0, 2, 6, 11, 15, 20, 22},
	{1, 3, 8, 12, 17, 21, 23},
	{10, 9, 8, 7, 6, 5, 4},
	{19, 18, 17, 16, 15, 14, 13},
	{23, 21, 17, 12, 8, 3, 1},
	{22, 20, 15, 11, 6, 2, 0},
	{13, 14, 15, 16, 17, 18, 19},
	{4, 5, 6, 7, 8, 9, 10}
};
/*
      0     1
      2     3
4  5  6  7  8  9  10
      11    12
13 14 15 16 17 18 19
      20    21
      22    23
*/
int sum[4];
int a[N], b[N];
string ans;

inline int max(int, int);

namespace IDA_star
{
	int f(void);
	void Work(int);
	bool DFS(int, int);
}
void Print(void);

int main()
{
	while (1) {
		scanf("%d", &a[0]);
		if (!a[0]) break;
		for (int i = 1; i < 24; ++i) scanf("%d", &a[i]);

		int dep = 0;
		while (!IDA_star::DFS(dep, 0)) ++dep;
		if (!dep) {
			puts("No moves needed");
			cout << a[center[0]] << endl;
			continue;
		}
		cout << ans << endl;
		cout << a[center[0]] << endl;
		ans.clear();
	}

	return 0;
}
inline int max(int a, int b)
{
	return a > b ? a : b;
}
int IDA_star::f(void)
{
	memset(sum, 0, sizeof sum);
	for (int i = 0; i < 8; ++i) ++sum[a[center[i]]];
	int res = 0;
	for (int i = 1; i < 4; ++i) res = max(res, sum[i]);
	return 8 - res;
}
void IDA_star::Work(int x)
{
	int t = a[op[x][0]];
	for (int i = 0; i < 6; ++i) a[op[x][i]] = a[op[x][i + 1]];
	a[op[x][6]] = t;
	return;
}
bool IDA_star::DFS(int lim, int dep)
{
	int b[24];
	using namespace IDA_star;
	if (dep > lim) return 0;
	int fi = f();
	if (!fi) return 1;
	if (fi + dep > lim) return 0;
	for (int i = 0; i < 8; ++i) {
		memcpy(b, a, sizeof b);
		ans.push_back(i + 'A');
		Work(i);
		if(DFS(lim, dep + 1)) return 1;
		memcpy(a, b, sizeof a);
		ans.pop_back();
	}
	return 0;
}
void Print(void)
{
	int idx = 0;
	for (int r = 0; r < 7; ++r) {
		if (r == 2 || r == 4) {
			for (int j = 0; j < 7; ++j) printf("%3d", a[idx++]);
			putchar('\n');
		}
		else {
			for (int i = 0; i < 6; ++i) putchar(' ');
			printf("%3d", a[idx++]);
			for (int i = 0; i < 3; ++i) putchar(' ');
			printf("%3d", a[idx++]);
			putchar('\n');
		}
	}
	return;
}
/*
      0     1
      2     3
4  5  6  7  8  9  10
      11    12
13 14 15 16 17 18 19
      20    21
      22    23
*/
