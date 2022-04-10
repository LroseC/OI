#include<bits/stdc++.h>
using namespace std;
const int N=1005,M=10005;
int ne[N<<1],tot,fi[N],zz[N<<1],val1[N],val2[N],n,a[N],b[N],out[N],m,flag[N],size[N],dp[N][M],ans,x,y,fa[N];
vector<int> g;
void jb(int x,int y){
	ne[++tot]=fi[x];
	fi[x]=tot;
	zz[tot]=y;
}
void dfs1(int x,int y){
	size[x]=1;g.push_back(x);fa[x]=y;
	for (int i=fi[x];i;i=ne[i])
		if (zz[i]!=y&&!flag[zz[i]]){
			dfs1(zz[i],x);
			size[x]+=size[zz[i]];
		}
}
void dfs2(int x,int y){
	tot++;val1[tot]=a[x];val2[tot]=b[x];
	int now=tot;
	for (int i=fi[x];i;i=ne[i])
		if (zz[i]!=y&&!flag[zz[i]])dfs2(zz[i],x);
	out[now]=tot;
}
int findroot(int x){
	g.clear();
	dfs1(x,0);
	for (int i:g){
		int cnt=g.size()-1,Flag=1;
		for (int j=fi[i];j;j=ne[j])
			if (zz[j]!=fa[i]&&!flag[zz[j]]){
				if (size[zz[j]]>(int)g.size()/2)Flag=0;
				cnt-=size[zz[j]];
			}
		if (cnt>(int)g.size()/2)Flag=0;
		if (Flag)return i;
	}
	assert(0);
	return -1;
}
void solve(int x){
	x=findroot(x);
	flag[x]=1;
	tot=0;
	dfs2(x,0);
	memset(dp[tot+1],0,sizeof dp[tot+1]);
	for (int i=tot;i>1;i--)
		for (int j=0;j<=m;j++){
			dp[i][j]=dp[out[i]+1][j];
			if (j>=val1[i])dp[i][j]=max(dp[i][j],dp[i+1][j-val1[i]]+val2[i]);
		}
	ans=max(ans,dp[2][m-val1[1]]+val2[1]);
	for (int i=fi[x];i;i=ne[i])
		if (!flag[zz[i]])solve(zz[i]);
}
int main(){
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++)scanf("%d%d",&a[i],&b[i]);
	for (int i=1;i<n;i++){
		scanf("%d%d",&x,&y);
		jb(x,y);jb(y,x);
	}
	tot=0;
	solve(1);
	printf("%d\n",ans);
}
