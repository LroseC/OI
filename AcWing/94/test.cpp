#include<bits/stdc++.h>
using namespace std;

int n;
int a[10010];
bool vis[10010];

void dfs(int dep)
{
	if(dep > n){
		for(int i = 1; i <= n; ++i)
		printf("%d ",a[i]);
		puts("");
	}
	else{
		for(int i = 1; i <= n; ++i){
			if(!vis[i]){
				vis[i] = 1;
				a[dep] = i;
				dfs(dep + 1);
				vis[i] = 0;
			}
		}
	}
}

int main()
{
	scanf("%d",&n);
	dfs(1);
	return 0;
}
