// ===================================
//   author: M_sea
//   website: http://m-sea-blog.com/
// ===================================
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast,unroll-loops,fast-math")
using namespace std;
typedef long long ll;

ll read() {
    ll X=0,w=1; char c=getchar();
    while (c<'0'||c>'9') { if (c=='-') w=-1; c=getchar(); }
    while (c>='0'&&c<='9') X=X*10+c-'0',c=getchar();
    return X*w;
}

const int N=166+5,K=8+5;
const int mod=998244353;

int inv[N];
int qpow(int a,int b) { int c=1;
    for (;b;b>>=1,a=1ll*a*a%mod) if (b&1) c=1ll*c*a%mod;
    return c;
}

int T,m,k;
int id[K][K][K],cnt=0;

struct Matrix {
    int s[N][N];
    Matrix() { memset(s,0,sizeof(s)); }
    int* operator [](int i) { return s[i]; }
} M[70];
Matrix operator *(Matrix a,Matrix b) {
    Matrix c;
    for (int i=1;i<=cnt;++i)
        for (int j=1;j<=cnt;++j) {
            __int128 t=0;
            for (int k=1;k<=cnt;++k) t+=1ll*a[i][k]*b[k][j];
            c[i][j]=t%mod;
        }
    return c;
}
void print(Matrix x)
{
	for (int i = 1; i <= cnt; ++i, puts(""))
		for (int j = 1; j <= cnt; ++j)
			printf("%d ", x.s[i][j]);
}

int ans[N],tmp[N];
void Mul(int p) {
    for (int i=1;i<=cnt;++i) tmp[i]=0;
    for (int i=1;i<=cnt;++i) {
        __int128 t=0;
        for (int j=1;j<=cnt;++j) t+=1ll*ans[j]*M[p][j][i];
        tmp[i]=t%mod;
    }
    for (int i=1;i<=cnt;++i) ans[i]=tmp[i];
}

int main() {
    T=read(),m=read(),k=read();
    for (int i=1;i<=9;++i) inv[i]=qpow(i,mod-2);
    for (int a=0;a<=k;++a)
        for (int b=0;b<=(m>=2?k-a:0);++b)
            for (int c=0;c<=(m==3?k-a-b:0);++c)
                id[a][b][c]=++cnt;
    ++cnt; M[0][cnt][cnt]=1;
    for (int a=0;a<=k;++a)
        for (int b=0;b<=(m>=2?k-a:0);++b)
            for (int c=0;c<=(m==3?k-a-b:0);++c) {
                int i=id[a][b][c],iv=inv[a+b+c+1],add=a+b+c<k;
                if (m==1) {
                    if (a) M[0][i][id[a-1][b][c]]=1ll*a*iv%mod;
                }
                if (m==2) {
                    if (a) M[0][i][id[a-1][b][c]]=1ll*a*iv%mod;
                    if (b) M[0][i][id[a+1][b-1+add][c]]=1ll*b*iv%mod;
                }
                if (m==3) {
                    if (a) M[0][i][id[a-1][b][c]]=1ll*a*iv%mod;
                    if (b) M[0][i][id[a+1][b-1][c+add]]=1ll*b*iv%mod;
                    if (c) M[0][i][id[a][b+1][c-1+add]]=1ll*c*iv%mod;
                }
                M[0][i][i]=M[0][i][cnt]=iv;
            }
    for (int i=1;i<=60;++i) M[i]=M[i-1]*M[i-1];
	print(M[1]);
    while (T--) {
        ll n=read();
        for (int i=1;i<=cnt;++i) ans[i]=0;
        ans[id[m==1][m==2][m==3]]=1;
        for (int i=0;i<=60;++i) if (n&(1ll<<i)) Mul(i);
        printf("%d\n",ans[cnt]);
    }
    return 0;
}
