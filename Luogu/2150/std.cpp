#include<bits/stdc++.h>
#include<algorithm>
#define int long long
using namespace std;
const int prime[9]= {2,3,5,7,11,13,17,19};
int g[3][1<<9][1<<9],f[1<<9][1<<9];
int bin[30];
pair<int,int> a[555];
int n,p;
void pre() {
	bin[0]=1;
	for(int i=1; i<=20; ++i) bin[i]=bin[i-1]*2;
	for(int i=2; i<=n; ++i) {
		int x=i;
		for(int j=0; j<=7; ++j) {
			if(x%prime[j]==0) a[i].second|=bin[j];
			while(x%prime[j]==0) x/=prime[j];
		}
		a[i].first=x;
	}
	sort(a+2,a+1+n);
}
signed main() {
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	cin>>n>>p;
	pre();
	memset(f,0,sizeof(f));
	f[0][0]=1;
	for(int i=2; i<=n; ++i) {
		if(a[i].first==1 || a[i].first!=a[i-1].first) {
			memcpy(g[1],f,sizeof(g[1]));
			memcpy(g[2],f,sizeof(g[2]));
		}
		for(int s1=255; s1>=0; --s1) {
			for(int s2=255; s2>=0; --s2) {
				if(s1&s2) continue;
				if(!(s2&a[i].second)) g[1][s1|a[i].second][s2]=(g[1][s1|a[i].second][s2]+g[1][s1][s2])%p;
				if(!(s1&a[i].second)) g[2][s1][s2|a[i].second]=(g[2][s1][s2|a[i].second]+g[2][s1][s2])%p;
			}
		}
		if((i==n) || (a[i].first!=a[i+1].first) ||(a[i].first==1)) {
			for(int s1=255; s1>=0; --s1) {
				for(int s2=255; s2>=0; --s2) {
					if(s1&s2) continue;
					f[s1][s2]=(g[1][s1][s2]%p+g[2][s1][s2]%p-f[s1][s2]%p+p)%p;
				}
			}
		}
	}
	int ans=0;
	for(int s1=255; s1>=0; --s1)
		for(int s2=255; s2>=0; --s2)
			ans=(ans+f[s1][s2])%p;
	cout<<(ans%p+p)%p;
	return 0;
}
