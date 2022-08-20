#include<bits/stdc++.h>
using namespace std;
// #define int long long
#define gc() getchar()
#define pc(a) putchar(a)
inline int read()
{
	int x=0,f=1;
	char c=gc();
	while(c<'0'||c>'9')
	{
		if(c=='-') f=-f;
		c=gc();
	}
	while(c>='0'&&c<='9') x=x*10+c-'0',c=gc();
	return x*f;
}
int nnu[25];
inline void write(int x)
{
	if(x<0) pc('-'),x=-x;
	if(!x)
	{
		pc('0');
		return;	
	}
	int tp=0;
	while(x) nnu[++tp]=x%10,x/=10;
	while(tp) pc(nnu[tp--]+'0');
	return;
}
#define ma 200005

int s[ma<<3],ls[ma<<3],rs[ma<<3],tag[ma<<3],root,tot;
inline void New(int &i){i=++tot;}
inline void push_up(int i){s[i]=min(s[ls[i]],s[rs[i]]);}
inline void push_down(int i)
{
    if(!ls[i]) New(ls[i]);
    if(!rs[i]) New(rs[i]);
    s[ls[i]]+=tag[i],tag[ls[i]]+=tag[i];
    s[rs[i]]+=tag[i],tag[rs[i]]+=tag[i];
    tag[i]=0;
    return;
}
void add(int &i,int l,int r,int L,int R,int val)
{
    if(!i) New(i);
    if(L<=l&&r<=R){s[i]+=val,tag[i]+=val;return;}
    push_down(i);
    int mid=(l+r)>>1;
    if(L<=mid) add(ls[i],l,mid,L,R,val);
    if(mid+1<=R) add(rs[i],mid+1,r,L,R,val);
    push_up(i);
    return;
}
int qry(int i,int l,int r)
{
    if(!i) return r;
    if(s[i]) return -1;
    if(l==r) return l;
    int mid=(l+r)>>1;
    push_down(i);
    if(s[rs[i]]==0) return qry(rs[i],mid+1,r);
    return qry(ls[i],l,mid);
}
int qry(int i,int l,int r,int L,int R)
{
    if(L<=l&&r<=R) return qry(i,l,r);
    push_down(i);
    int mid=(l+r)>>1,ans=-1;
    if(mid+1<=R&&s[rs[i]]==0) ans=max(ans,qry(rs[i],mid+1,r,L,R));
    if(~ans) return ans;
    if(L<=mid&&s[ls[i]]==0) ans=max(ans,qry(ls[i],l,mid,L,R));
    return ans;
}
int A[ma];
inline void work()
{
    int n=read();
    for(int i=1;i<=n;i++) A[i]=read();
    for(int i=1;i<=n;i++) if(A[i]<i) add(root,1,n,A[i]+1,i,1);
    int q=read();
    while(q--)
    {
        int op=read(),x=read();
        if(op==1)
        {
            int y=read();
            if(A[x]<x) add(root,1,n,A[x]+1,x,-1);
            A[x]=y;
            if(A[x]<x) add(root,1,n,A[x]+1,x,1);
        }
        else write(qry(root,1,n,1,x)),pc('\n');
    }
    for(int i=1;i<=tot;i++) ls[i]=rs[i]=tag[i]=s[i]=0;
    root=tot=0;
    return;
}
/*
1
6
1 3 2 5 4 4
5
2 4
2 6
1 5 3
2 4
2 6

*/
signed main()
{
 //   freopen("graph.in","r",stdin);
 //   freopen("graph.out","w",stdout);
    // double cl=clock();
    int T=read();
    while(T--) work();
    // cerr<<(clock()-cl)/CLOCKS_PER_SEC<<endl;
}





/*
1.  数组开够了没
2.  文件名写对了没，文件夹建了吗
3.  内存会不会MLE
4.  多测清空？
5.  调试删干净了没
6.  取模有没有溢出
7.  快速幂底数要取模，幂对 mod-1 取模
8.  前向星和欧拉序要开2倍数组
9.  比较函数如果值相同的话有没有第二优先级
10.  线段树 4 倍空间，线段树合并和可持久化线段树 32 倍空间
11.  看清楚 log 的底数是啥，log后面的数是啥
12.  long long 只有正负 2^63-1   
*/
