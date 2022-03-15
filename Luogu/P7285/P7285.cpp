#include<stdio.h>
using namespace std;
#define reg register
#define ll long long
#define ull unsigned long long

inline int read()
{
	reg int f = 1,res = 0;
	reg char ch = getchar();
	while (ch > '9' || ch < '0'){
		if (ch == '-') f = -1;
		ch = getchar();
	}
	while (ch <= '9' && ch >= '0'){
		res = res * 10 + ch - '0';
		ch = getchar();
	}
	return res;
}

int T;
int n;
int a[100010];


int main()
{
	T = read();
	while (T--){
		reg int ans = 0;
		n = read();
		for (reg int i = 1; i <= n; ++i){
			a[i] = read();
			if (a[i] == 1)++ans;
		}
		printf("%d\n",ans);
		for (reg int i = 1; i <= n; ++i)
			printf("1 ");
	}
	return 0;
}
