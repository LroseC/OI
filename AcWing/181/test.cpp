#include <cstdio>
#include <cstring>

using namespace std;

#define reg register
#define ll long long
const int N = 24;

int T;
int center[] = {6, 7, 8, 11, 12, 15, 16, 17};
int sum[4];
int a[N], b[N];

inline int max(int, int);

namespace IDA_star
{
	int f(void);
	void Work(int);
	bool DFS(int, int);
}

int main()
{
	scanf("%d", &T);
	while (T--) {
		for (int i = 0; i < 24; ++i) scanf("%d", &a[i]);

		if (IDA_star::DFS(0, 0)) {
			puts("No moves needed");
			continue;
		}
		int dep = 0;
		while (!IDA_star::DFS(dep, 0)) ++dep;
		if (!dep) {
			puts("No moves needed");
			continue;
		}
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
	return;
}
bool IDA_star::DFS(int lim, int dep)
{
	using namespace IDA_star;
	if (dep > lim) return 0;
	int fi = f();
	if (!fi) return 1;
	if (fi + dep > lim) return 0;
	for (int i = 0; i < 8; ++i) {
		memcpy(b, a, sizeof b);
		Work(i);
		if(DFS(lim, dep + 1)) return 1;
		memcpy(a, b, sizeof a);
	}
	return 0;
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
