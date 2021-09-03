#include<bits/stdc++.h>
#define ll long long
using namespace std;

ll t,d[100001],f[100001][51],n,m,k,p;
bool working[100001][51];
struct node{
	ll to,edge;
    //to表示下一个点
    //edge表示长度
};
vector<node> head[100001],h[100001];
//head存正向边
//h存反向边

ll dfs(ll x,ll l){
	printf("x = %d, l = %d\n", x, l);
	ll ans=0;
	if(l<0||l>k) return 0;//超出范围还没走到就返回
	if(working[x][l]){//找到0环
		working[x][l]=false;
		return -1;
	}
	if(f[x][l]!=-1) return f[x][l];//这个点已经走过了
	working[x][l]=true;
	for(ll i=0; i<h[x].size(); i++){
		ll y=h[x][i].to,z=h[x][i].edge,val=dfs(y,d[x]+l-d[y]-z);
        //y表示下一个格子
        //z表示剩下的距离
		if(val==-1){//找到0环
			working[x][l]=false;
			return -1;
		}
		ans=(ans+val)%p;
	}
	working[x][l]=false;//去过了
	if(x==1&&l==0) ans++;//找到，并且距离用完
	f[x][l]=ans;//存下结果
	return ans;
}

inline void spfa(){//最短路，不讲了
	memset(d,0x3f,sizeof(d));
	memset(f,-1,sizeof(f));
	queue<ll> q;
	q.push(1);
	d[1]=0;
	while(!q.empty()){
		ll x=q.front(); q.pop();
		for(ll i=0; i<head[x].size(); i++){
			ll y=head[x][i].to,z=head[x][i].edge;
			if(d[y]>d[x]+z){
				d[y]=d[x]+z;
				q.push(y);
			}
		}
	}
}

ll work(){
	scanf("%lld%lld%lld%lld",&n,&m,&k,&p);
	for(ll i=1; i<=n; i++){
		head[i].clear(); h[i].clear();
	}
	
    while(m--){
    	ll x,y,z;
        scanf("%lld%lld%lld",&x,&y,&z);
        head[x].push_back(node{y,z});//存正边
        h[y].push_back(node{x,z});//存反边
    }
	spfa();
	ll ans=0;
	f[1][0] = 1;
	for(ll i=0; i<=k; i++){
		ll val=dfs(n,i);//调用
		if(val==-1) return -1;//找到0环直接退出
		ans=(ans+val)%p;//结果增加
	}
	return ans;
}

int main(){
	scanf("%lld",&t);
	while(t--) printf("%lld\n",work());
	return 0;
}