//#include <bits/stdc++.h>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <algorithm>
#include <climits>
#include <functional>
#include <cstring>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <vector>
#include <stack>
#include <queue>
#include <deque>
#include <map>
#include <set>
#include <bitset>
#include <complex>
//#include <random>
//#include <ext/pb_ds/assoc_container.hpp>
//#include <ext/pb_ds/priority_queue.hpp>
#define itn int
#define nit int
#define ll long long
#define ms multiset
#define F(i,a,b) for(register int i=a,i##end=b;i<=i##end;++i)
#define UF(i,a,b) for(register int i=a,i##end=b;i>=i##end;--i)
#define re register
#define ri re int
#define il inline
#define pii pair<int,int>
#define cp complex<double>
#define vi vector<int>
#define ull unsigned long long
#define mem0(x) memset(x,0,sizeof(x))
#define mem0x3f(x) memset(x,0x3f,sizeof(x))
using namespace std;
//using namespace __gnu_pbds;
const double Pi=acos(-1);
namespace fastIO {
	template<class T>
	inline void read(T &x) {
		x=0;
		bool fu=0;
		char ch=0;
		while(ch>'9'||ch<'0') {
			ch=getchar();
			if(ch=='-')fu=1;
		}
		while(ch<='9'&&ch>='0') x=(x*10-48+ch),ch=getchar();
		if(fu)x=-x;
	}
	inline int read() {
		int x=0;
		bool fu=0;
		char ch=0;
		while(ch>'9'||ch<'0') {
			ch=getchar();
			if(ch=='-')fu=1;
		}
		while(ch<='9'&&ch>='0') x=(x*10-48+ch),ch=getchar();
		return fu?-x:x;
	}
	template<class T,class... Args>
	inline void read(T& t,Args&... args) {
		read(t);
		read(args...);
	}
	char _n_u_m_[40];
	template<class T>
	inline void write(T x) {
		if(x==0) {
			putchar('0');
			return;
		}
		T tmp = x > 0 ? x : -x ;
		if( x < 0 ) putchar('-') ;
		register int cnt = 0 ;
		while( tmp > 0 ) {
			_n_u_m_[ cnt ++ ] = tmp % 10 + '0' ;
			tmp /= 10 ;
		}
		while( cnt > 0 ) putchar(_n_u_m_[ -- cnt ]) ;
	}
	template<class T>
	inline void write(T x ,char ch) {
		write(x);
		putchar(ch);
	}
}
using namespace fastIO;
int a[12],b[12],px,py,ans=-1,qwq[12],qaq[12],n,m,qwert;
char c[1000002];
int orz[1000002],sto[1000002],cnt,tot,fuck[1000002],ccf[1000002],asdf,fdsa,qwer[1000002];
inline int calc() {
	memcpy(qwq,a,sizeof(qwq));
	memcpy(qaq,b,sizeof(qaq));
	int rt=0;
	UF(i,8,1) {
		F(j,9-i,9) {
			if(qwq[i]&&qaq[j]) {
				int temp=min(qwq[i],qaq[j]);
				rt+=temp;
				qwq[i]-=temp;
				qaq[j]-=temp;
			}
		}
	}
	F(i,9,9){
		F(j,1,9) {
			if(qwq[i]&&qaq[j]) {
				int temp=min(qwq[i],qaq[j]);
				rt+=temp;
				qwq[i]-=temp;
				qaq[j]-=temp;
			}
		}
	}
	if(n>m)rt+=min(n-m,qwq[9]);
	if(n<m)rt+=min(m-n,qaq[9]);
	return rt;
}
inline void getans(int x,int y) {
	--a[x];
	--b[y];
	orz[cnt=1]=x;
	sto[tot=1]=y;
	UF(i,8,1) {
		F(j,9-i,9) {
			if(a[i]&&b[j]) {
				int temp=min(a[i],b[j]);//cerr<<i<<" "<<j<<endl;
				a[i]-=temp;
				b[j]-=temp;
				if(i+j==9) {
					F(k,1,temp)orz[++cnt]=i;
					F(k,1,temp)sto[++tot]=j;
				} else {
					F(k,1,temp)fuck[++asdf]=i;
					F(k,1,temp)ccf[++fdsa]=j;
				}
			}
		}
	}
	F(i,9,9){
		F(j,1,9) {
			if(a[i]&&b[j]) {
				int temp=min(a[i],b[j]);//cerr<<i<<" "<<j<<endl;
				a[i]-=temp;
				b[j]-=temp;
				if(i+j==9) {
					F(k,1,temp)orz[++cnt]=i;
					F(k,1,temp)sto[++tot]=j;
				} else {
					F(k,1,temp)fuck[++asdf]=i;
					F(k,1,temp)ccf[++fdsa]=j;
				}
			}
		}
	}
	if(n>m){
		while(n>m+a[9]){
			F(i,1,8){
				if(a[i]){
				putchar(i+'0'),a[i]--;--n;
				break;	
				}
			}
			
		}
		while(a[9]&&n>m)putchar('9'),a[9]--,n--;
	}else{
		while(m>n+b[9]){
			F(i,1,8){
				if(b[i]){
				qwer[++qwert]=i+'0',b[i]--;--m;
				break;	
				}
			}
		}
		while(b[9]&&m>n)qwer[++qwert]='9',b[9]--,--m;
	}
	F(i,1,9)while(a[i]--)putchar(i+'0');
	UF(i,asdf,1)putchar(fuck[i]+'0');
	UF(i,cnt,1)putchar(orz[i]+'0');
	puts("");
	F(i,1,qwert)putchar(qwer[i]);
	F(i,1,9)while(b[i]--)putchar(i+'0');
	UF(i,fdsa,1)putchar(ccf[i]+'0');
	UF(i,tot,1)putchar(sto[i]+'0');
	puts("");
	return;
}
int main() {
//	freopen("03_large_random_01.txt","r",stdin);
	scanf("%s",c+1);
	F(i,1,strlen(c+1))++a[c[i]-'0'];n=strlen(c+1);
	scanf("%s",c+1);
	F(i,1,strlen(c+1))++b[c[i]-'0'];m=strlen(c+1);
	F(i,1,9)F(j,10-i,9)if(a[i]&&b[j]) {
		--a[i];
		--b[j];
		if(calc()>ans)ans=calc(),px=i,py=j;
		++a[i];
		++b[j];
	}
	if(ans<0) {
		F(i,1,9)while(a[i]--)putchar(i+'0');
		puts("");
		F(i,1,9)while(b[i]--)putchar(i+'0');
		puts("");
		return 0;
	}
	getans(px,py);
	return 0;
}