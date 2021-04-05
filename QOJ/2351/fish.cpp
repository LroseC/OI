#include<cstdio>
#include<algorithm>
using namespace std;
#define reg register
#define ll long long
#define ull unsigned long long


int n,m;
int minn,maxn,last,mint,maxt;
struct node
{
	int x,y1,y2;
}wang[100010];
bool operator<(node a,node b){return a.x == b.x ? a.y1 == b.y1 ? a.y2 < b.y2 : a.y1 < b.y1 : a.x < b.x;}

int main()
{
	reg int x,y1,y2;
	scanf("%d%d",&n,&m);
	for (reg int i = 1; i <= n; ++i)
		scanf("%d%d%d",&wang[i].x,&wang[i].y1,&wang[i].y2);
	sort(wang + 1,wang + 1 + n);

	minn = 0,maxn = 0,last = 0;
	for (reg int i = 1; i <= n; ++i){
		mint = wang[i].y1 + wang[i].x + 1 >> 1;
		maxt = (wang[i].y2 + wang[i].x + 1 >> 1) - 1;
		if (minn > maxt || maxn + (wang[i].x - last) < mint){
			puts("NIE");
			return 0;
		}
		minn = max(minn,mint);
		maxn = min(maxn,maxt);
	}
	printf("%d\n",minn);
	return 0;
}
