#include <cstdio>

using namespace std;

#define reg register
#define ll long long
#define max(a, b) (a > b ? a : b)
#define min(a, b) (a < b ? a : b)
const int N = 1e5 + 10;

int n;
int a[N];
int f[N][2];

int main()
{
    scanf("%d", &n);
    f[0][1] = -1e9;
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
        f[i][0] = max(f[i - 1][0], f[i - 1][1] + a[i]);
        f[i][1] = max(f[i - 1][1], f[i - 1][0] - a[i]);
    }
    printf("%d\n", f[n][0]);
    return 0;
}
