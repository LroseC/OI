#include<bits/stdc++.h>
using namespace std;
const int INF=0x3f3f3f3f;
const int N=510,M=6010;
int n,m,q,S,T,d[N],now[N],a[N],a1[N],a2[N];
int ver[M],edge[M],ne[M],head[N],tot=1;
int vc[M],ec[M],nc[M],hc[N],tc;
int dep[N],f[N][10],mn[N][10];

void add(int x,int y,int w)
{
	ver[++tot]=y, edge[tot]=w, ne[tot]=head[x], head[x]=tot;
	ver[++tot]=x, edge[tot]=0, ne[tot]=head[y], head[y]=tot;
}

void add_tree(int x,int y,int w)
{
	vc[++tc]=y, ec[tc]=w, nc[tc]=hc[x], hc[x]=tc;
	vc[++tc]=x, ec[tc]=w, nc[tc]=hc[y], hc[y]=tc;
}

bool bfs()
{
	memset(d,0,sizeof d);
	queue<int> q;
	q.push(S); d[S]=1; now[S]=head[S];
	
	while(q.size())
	{
		int x=q.front(); q.pop();
		for(int i=head[x];i;i=ne[i])
		{
			int y=ver[i],w=edge[i];
			if(w&&!d[y])
			{
				d[y]=d[x]+1;
				now[y]=head[y];
				if(y==T) return true;
				q.push(y);
			}
		}
	}
	return false;
}

int find(int x,int limit)
{
	if(x==T) return limit;
	int flow=0;
	for(int i=now[x];i&&flow<limit;i=ne[i])
	{
		now[x]=i;
		int y=ver[i],w=edge[i];
		if(w&&d[y]==d[x]+1)
		{
			int t=find(y,min(w,limit-flow));
			if(!t) d[y]=0;
			flow+=t, edge[i]-=t, edge[i^1]+=t;
		}
	}
	return flow;
}

int dinic()
{
	for(int i=2;i<=tot;i+=2)
		edge[i]+=edge[i^1], edge[i^1]=0;
	int maxflow=0,flow;
	while(bfs()) while(flow=find(S,INF)) maxflow+=flow;
	return maxflow;
}

void solve(int l,int r)
{
	if(l==r) return;
	S=a[l],T=a[r];
	int flow=dinic(),cnt1=0,cnt2=0;
	add_tree(a[l],a[r],flow);
	for(int i=l;i<=r;i++)
	{
		if(d[a[i]]) a1[++cnt1]=a[i];
		else a2[++cnt2]=a[i];
	}
	for(int i=l;i<=l+cnt1-1;i++) a[i]=a1[i-l+1];
	for(int i=cnt1+l;i<=r;i++) a[i]=a2[i-cnt1-l+1];
	solve(l,l+cnt1-1), solve(l+cnt1,r);
}

void dfs(int x,int fa)
{
	dep[x]=dep[fa]+1;
	for(int i=1;i<=9;i++)
		f[x][i]=f[f[x][i-1]][i-1],
		mn[x][i]=min(mn[x][i-1],mn[f[x][i-1]][i-1]);
	for(int i=hc[x];i;i=nc[i])
		if(vc[i]!=fa)
		{
			f[vc[i]][0]=x, mn[vc[i]][0]=ec[i];
			dfs(vc[i],x);
		}
}

int lca_mn(int x,int y)
{
	if(dep[x]<dep[y]) swap(x,y);
	int t=INF;
	for(int i=9;i>=0;i--)
		if(dep[f[x][i]]>=dep[y])
		{
			t=min(t,mn[x][i]);
			x=f[x][i];
		}
	if(x==y) return t;
	for(int i=9;i>=0;i--)
		if(f[x][i]!=f[y][i])
		{
			t=min(t,mn[x][i]);
			t=min(t,mn[y][i]);
			x=f[x][i],y=f[y][i];
		}
	t=min(t,min(mn[x][0],mn[y][0]));
	return t;
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		int x,y,w;
		scanf("%d%d%d",&x,&y,&w);
		add(x,y,w); add(y,x,w);
	}
	for(int i=1;i<=n;i++) a[i]=i;
	solve(1,n);
	dfs(1,0);
	scanf("%d",&q);
	while(q--)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		printf("%d\n",lca_mn(x,y));
	}
	return 0;
}
