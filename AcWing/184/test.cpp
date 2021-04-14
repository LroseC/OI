#include <cstdio>
#include <cstring>

using namespace std;

#define reg register
#define ll long long
const int N = 26;

int n;
char f[3][N];
int p[N];
bool vis[N];

void Init(void);
void DFS(int c, int k);

int main()
{
	scanf("%d", &n);
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < n; ++j) cin >> f[i][j];
	DFS(n - 1);
	for (int i = 0; i < n; ++i) cout << p[i] << ' ';
	return 0;
}
void Init(void)
{
	memset(0xff, p, sizeof p);
}
void DFS(int c, int k)
{
	if (~p[f[k][c]]) 
