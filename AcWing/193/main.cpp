#include <cstdio>

using namespace std;

#define reg register
#define ll long long

int p, dep;

int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }
inline int max(int a, int b) { return a > b ? a : b; }
inline int min(int a, int b) { return a < b ? a : b; }
inline void swap(int &a, int &b) { int t = a; a = b; b = t; }
bool dfs(int lim, int dep, int a, int b);

int main()
{
	scanf("%d", &p);
	while(!dfs(dep, 0, 1, 0)) ++dep;

	printf("%d\n", dep);

	return 0;
}
bool dfs(int lim, int dep, int a, int b)
{
//	printf("a = %d, b = %d, lim = %d, dep = %d\n", a, b, lim, dep);
	if (a == p || b == p) return 1;
	if (dep == lim) return 0;
	if (p % (gcd(a, b))) return 0;
	if (a << lim - dep < p) return 0;

	int aa = a + a, bb = b;
	if (bb && dfs(lim, dep + 1, aa, bb)) return 1;
	aa = a + b, bb = b;
	if (bb && dfs(lim, dep + 1, aa, bb)) return 1;
	aa = a + a, bb = a;
	if (bb && dfs(lim, dep + 1, aa, bb)) return 1;
	aa = a + b, bb = a;
	if (bb && dfs(lim, dep + 1, aa, bb)) return 1;
	aa = a, bb = a - b;
	if (bb && dfs(lim, dep + 1, aa, bb)) return 1;
	aa = b, bb = a - b; if (aa < bb) swap(aa, bb);
	if (bb && dfs(lim, dep + 1, aa, bb)) return 1;

	return 0;
}
