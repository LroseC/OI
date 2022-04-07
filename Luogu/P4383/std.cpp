// luogu-judger-enable-o2
#include<cstdio>
#include<algorithm>
using namespace std;const int N=3*1e5+10;typedef long long ll;
int v[2*N];int x[2*N];int ct;int al[N];ll val[2*N];bool book[N];int n;int k;
inline void add(int u,int V,ll va){v[++ct]=V;x[ct]=al[u];al[u]=ct;val[ct]=va;}
struct data//dp的结构体 
{
    ll v;int k;
    friend bool operator <(data a,data b){return (a.v==b.v)?a.k>b.k:a.v<b.v;}//重载< 
    friend data operator +(data a,data b){return (data){a.v+b.v,a.k+b.k};}
}dp[N][3];data tr[3];ll mid;
inline void dfs(int u)//树形dp 
{
    book[u]=true;
    for(int i=al[u];i;i=x[i])
    {
        if(book[v[i]])continue;dfs(v[i]);ll va=val[i];
        for(int j=0;j<3;j++)tr[j]=(data){-0x7f7f7f7f7f,0x3f3f3f3f};
        for(int j=0;j<3;j++)tr[0]=max(tr[0],dp[u][0]+dp[v[i]][j]);
        tr[1]=max(tr[1],dp[u][0]+dp[v[i]][0]+(data){va-mid,1});
        tr[1]=max(tr[1],dp[u][0]+dp[v[i]][1]+(data){va,0});
        for(int j=0;j<3;j++)tr[1]=max(tr[1],dp[u][1]+dp[v[i]][j]);
        tr[2]=max(tr[2],dp[u][1]+dp[v[i]][0]+(data){va,0});
        tr[2]=max(tr[2],dp[u][1]+dp[v[i]][1]+(data){va+mid,-1});
        for(int j=0;j<3;j++)tr[2]=max(tr[2],dp[u][2]+dp[v[i]][j]);
        for(int j=0;j<3;j++)dp[u][j]=tr[j];
    }book[u]=false;
}
inline void ih()//初始化边界条件 
{
    for(int i=1;i<=n;i++)
        dp[i][0]=(data){0,0},dp[i][1]=(data){-0x7f7f7f7f7f,0x3f3f3f3f},
        dp[i][2]=(data){-mid,1};
}
int main()
{
    scanf("%d%d",&n,&k);
    for(int i=1,u,v,va;i<n;i++){scanf("%d%d%d",&u,&v,&va);add(u,v,va);add(v,u,va);}
    ll l=-1e12;ll r=1e12;
    while(l<r)
    {
        mid=l+r>>1;ih();dfs(1);
        data jud=max(dp[1][0],max(dp[1][1],dp[1][2]));
        if(jud.k>(k+1)){l=mid+1;}else r=mid;//二分斜率 
    }mid=l;ih();dfs(1);data jud=max(dp[1][0],max(dp[1][1],dp[1][2]));
    printf("%lld",jud.v+(k+1)*mid);return 0;//带入直线方程求值 
}
