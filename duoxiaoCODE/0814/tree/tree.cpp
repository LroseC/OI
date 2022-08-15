#include<bits/stdc++.h>
using namespace std;
#define int long long
typedef long long ll;
const int N1=200010,M=400010,N2=N1*44;
int n,k;
int idx=1,e[M],ne[M],head[N1];
ll w[M];
inline void add(int x,int y,int z)
{
	e[++idx]=y;
	ne[idx]=head[x];
	head[x]=idx;
	w[idx]=z;
}
bool st[N1];//是否已经作为重心删除
int get_sz(int u,int fa)
{
	if(st[u]) return 0;
	int sz=1;
	for(int i=head[u];i;i=ne[i])
	{
		int v=e[i];
		if(v==fa) continue;
		sz+=get_sz(v,u);
	}
	return sz;
}
int get_wc(int u,int fa,int &wc,int tot)
/*
当前考虑节点U，它的父节点是FA，重心是WC(weight center)，树总大小是tot
会求出重心并且返回子树大小
*/
{
	if(st[u]) return 0;
	int sz=1,max_son_sz=0;
	for(int i=head[u];i;i=ne[i])
	{
		int v=e[i];
		if(v==fa) continue;
		int v_sz=get_wc(v,u,wc,tot);
		max_son_sz=max(max_son_sz,v_sz);
		sz+=v_sz;
	}
	if(max(max_son_sz,tot-sz)<=(tot/2)) wc=u;
	return sz;
}
ll dis[N2];
int L,R,id;//把点分树拍成一个序列
int lmx,nmx;
struct node//类似超级钢琴的存储
{
	ll val;
	int i;
	int l,r;
	int pos;
	bool operator<(const node &t)const{return val<t.val;}
};
priority_queue<node> heap;
void calc(int u,int fa,int d)
{
	dis[++id]=d;
	heap.push(node{dis[id]+dis[lmx],id,L,R,lmx});
	if(dis[id]>dis[nmx]) nmx=id;
	for(int i=head[u];i;i=ne[i])
	{
		int v=e[i];
		if(st[v]||v==fa) continue;
		calc(v,u,d+w[i]);
	} 
}
inline void work(int u)
{
	dis[++id]=0;
	L=R=id;
	lmx=nmx=L;//取到最大值的位置 当前只能取L，所以是L
	//lmx是当前左端点可以取的范围内的最大值的位置 nmx是所有的(即nmx可能在当前子树内)
	for(int i=head[u];i;i=ne[i])
	{
		int v=e[i];
		if(st[v]) continue;
		calc(v,u,w[i]);
		R=id;//注意calc出来再改R，因为v的对应的右端点取值区间是不能在自己子树的
		lmx=nmx;//类似地
	}
}
void solve(int u)
{
	st[u]=1;
	work(u);
	for(int i=head[u];i;i=ne[i])
	{
		int v=e[i];
		if(st[v]) continue;
		int wc=u;
		get_wc(v,u,wc,get_sz(v,0));
		solve(wc);
	}
}
int f[N2][25];
void build_ST()
{
	for(int i=1;i<=id;i++) f[i][0]=i;
	for(int j=1;j<=22;j++)
		for(int i=1;i+(1<<(j-1))<=id;i++)
			if(dis[f[i][j-1]]<dis[f[i+(1<<(j-1))][j-1]]) f[i][j]=f[i+(1<<(j-1))][j-1];
			else f[i][j]=f[i][j-1];
}
int LOG2[N2];
int ask_ST(int l,int r)
{
	int k=LOG2[r-l+1];
	if(dis[f[l][k]]>dis[f[r-(1<<k)+1][k]]) return f[l][k];
	else return f[r-(1<<k)+1][k];
}
signed main()
{
	// freopen("tree.in","r",stdin);
	// freopen("tree.out","w",stdout);
	scanf("%d%d",&n,&k);
	LOG2[1]=0;
	for(int i=2;i<=n*22;i++) LOG2[i]=LOG2[i>>1]+1;
	for(int i=2,x,y,l;i<=n;i++)
	{
		scanf("%d%d%d",&x,&y,&l);
		add(x,y,l); add(y,x,l);
	}
	int rt;
	get_wc(1,0,rt,n);
	solve(rt);
	build_ST();
	while(k--)
	{
		auto t=heap.top(); heap.pop();
		printf("%lld\n",t.val);
		if(t.l<t.pos)
		{
			int chs=ask_ST(t.l,t.pos-1);
			heap.push({dis[t.i]+dis[chs],t.i,t.l,t.pos-1,chs});
		}
		if(t.pos<t.r) 
		{
			int chs=ask_ST(t.pos+1,t.r);
			heap.push({dis[t.i]+dis[chs],t.i,t.pos+1,t.r,chs});
		}
	}
	return 0;
}
