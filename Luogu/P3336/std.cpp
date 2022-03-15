#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=19940417,Maxn=1e6+5;
inline int read(){
	int s=0,w=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')s=(s<<1)+(s<<3)+ch-'0',ch=getchar(); 
	return s*w;
}
struct node{
	int x,y;
}a[Maxn];	
bool operator<(node a,node b){return a.x<b.x;}
bool operator==(node a,node b){return a.x==b.x&&a.y==b.y;}
int n,k,f[Maxn][2],ans;
inline int power(int a,int b){
	int dat=1;
	for(;b;b>>=1){
		if(b&1)dat=dat*a%mod;
		a=a*a%mod;
	}
	return dat;
}
signed main(){
	n=read(),k=read();
	for(int i=1;i<=k;i++)a[i].x=read(),a[i].y=read();
	k++,a[k].x=0,a[k].y=0;
	k++,a[k].x=n,a[k].y=0;
	sort(a+1,a+k+1);
	k=unique(a+1,a+k+1)-a-1;
	f[1][1]=1;
	for(int i=1;i<k;i++){
		int w=(a[i+1].x-a[i].x-a[i+1].y-a[i].y)>>1;
		if(a[i+1].y-a[i].y==a[i+1].x-a[i].x)
			f[i+1][0]=(f[i][0]+(a[i].y?0:f[i][1]))%mod;
		else if(a[i+1].y-a[i].y==a[i].x-a[i+1].x)
			f[i+1][1]=(f[i][1]+f[i][0])%mod;
		else if(w<0)
			f[i+1][1]=(f[i][0]+(a[i].y?0:f[i][1]))%mod;
		else if(w==0)
			f[i+1][0]=(f[i][1]+f[i][0])%mod,f[i+1][1]=f[i][0];
		else{
			int p=power(2,w-1);
			if(a[i+1].y)f[i+1][0]=(f[i][1]+2*f[i][0])%mod*p%mod;
			f[i+1][1]=(f[i][1]+2*f[i][0])%mod*p%mod;
		}
		if(f[i+1][1]||a[i+1].y==0)ans=max(ans,(a[i+1].x-a[i].x+a[i].y+a[i+1].y)>>1);
	}
	printf("%lld %lld",f[k][1],ans);
	return 0;
}