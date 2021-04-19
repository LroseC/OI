#include <cstdio>
#include <cstring>

using namespace std;

#define reg register
#define ll long long
const int mod = 1e4;

struct Matrix
{
    #define MA Matrix
    int r, c;
    int f[5][5];
    Matrix(void) {}
    Matrix (int r, int c) : r(r), c(c)
    {
        memset(f, 0, sizeof f);
    }
    Matrix (int r, int c, int num) : r(r), c(c)
    {
        for (int i = 0; i < r; ++i)
            for (int j = 0; j < c; ++j) f[i][j] = i == j ? num : 0;
    }
    MA operator*(const MA &b) const
    {
        MA New(r, b.c);
        for (int i = 0; i < r; ++i)
            for (int k = 0; k < c; ++k) {
                int tmp = f[i][k];
                for (int j = 0; j < b.c; ++j) New.f[i][j] = (New.f[i][j] + tmp * b.f[k][j] % mod) % mod;
            }
        return New;
    }
    MA operator^(int k)
    {
        MA res(r, r, 1), base = *this;
        while (k) {
            if (k & 1) res = res * base;
            base = base * base;
            k >>= 1;
        }
        return res;
    }
    #undef MA
};

int n;

int main()
{
    scanf("%d", &n);
    while (~n) {
        if (n == 0) {
            puts("0");
            scanf("%d", &n);
            continue;
        }
        Matrix base(2, 2), ans(1, 2);
        base.f[0][0] = 0, base.f[1][0] = base.f[0][1] = base.f[1][1] = ans.f[0][0] = ans.f[0][1] = 1;
        base = base ^ (n - 1);
        ans = ans * base;
        printf("%d\n", ans.f[0][0]);
        scanf("%d", &n);
    }
}
