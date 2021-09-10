#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cctype>
#define ll long long
#define gc getchar
#define maxn 2005
using namespace std;

inline ll read(){
	ll a=0;int f=0;char p=gc();
	while(!isdigit(p)){f|=p=='-';p=gc();}
	while(isdigit(p)){a=(a<<3)+(a<<1)+(p^48);p=gc();}
	return f?-a:a;
}

struct ahaha{
	int w,to,next;
}e[maxn<<1];int tot,head[maxn];
inline void add(int u,int v,int w){
	e[tot].w=w,e[tot].to=v,e[tot].next=head[u];head[u]=tot++;
}

int n,m,sz[maxn];
ll f[maxn][maxn];
void dfs(int u,int fa){
	sz[u]=1;f[u][0]=f[u][1]=0;
	for(int i=head[u];~i;i=e[i].next){
		int v=e[i].to;if(v==fa)continue;
		dfs(v,u);sz[u]+=sz[v];
		for(int j=min(m,sz[u]);j>=0;--j){   //此处倒序枚举是为了避免重复选取
			if(f[u][j]!=-1)    //在DP前应先加上当前子节点的子树纯白色的情况，这是下面也倒序枚举的前提
				f[u][j]+=f[v][0]+(ll)sz[v]*(n-m-sz[v])*e[i].w;
			for(int k=min(j,sz[v]);k;--k){
				if(f[u][j-k]==-1)continue;
				ll val=(ll)(k*(m-k)+(sz[v]-k)*(n-m-sz[v]+k))*e[i].w;   //当前情况下连接子节点的边的贡献
				f[u][j]=max(f[u][j],f[u][j-k]+f[v][k]+val);
			}
		}
	}
}

int main()
{
	memset(head,-1,sizeof head);
	n=read();m=read();
	if(n-m<m)m=n-m;
	for(int i=1;i<n;++i) {
		int u=read(),v=read(),w=read();
		add(u,v,w);add(v,u,w);
	}
	memset(f,-1,sizeof f);
	dfs(1,-1);
	printf("%lld",f[1][m]);
	return 0;
}