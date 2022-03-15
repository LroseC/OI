#include<iostream>
#include<stdio.h>
#include<algorithm>
#include<queue>
using namespace std;
#define reg register
#define ll long long
#define ull unsigned long long


struct node
{
	int x,y,height;
}f[110][110];
bool operator<(node a,node b){return a.height > b.height;}
int n,m;
int ff[110][110];
int gox[] = {0,0,1,-1};
int goy[] = {1,-1,0,0};
priority_queue<node> heap;

int main()
{
	scanf("%d%d",&n,&m);
	for (reg int i = 1; i <= n; ++i)
		for (reg int j = 1; j <= m; ++j){
			scanf("%d",&f[i][j].height);
			f[i][j].x = i;
			f[i][j].y = j;
			heap.push(f[i][j]);
			ff[i][j] = 1;
		}

	reg int ans = 0;
	while (heap.size()){
		reg int x = heap.top().x;
		reg int y = heap.top().y;
		heap.pop();
		for (reg int i = 0; i < 4; ++i){
			reg int xx = x + gox[i];
			reg int yy = y + goy[i];
			if (f[xx][yy].height < f[x][y].height)
				ff[x][y] = max(ff[x][y],ff[xx][yy] + 1);
		}
	}

	for (reg int i = 1; i <= n; ++i){
		for (reg int j = 1; j <= m; ++j)
			ans = max(ans,ff[i][j]);
	}

	printf("%d\n",ans);
	return 0;
}
