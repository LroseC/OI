#include<cstdio>
#include<vector>
using namespace std;
struct good{int w,t;};
vector<good> v[61];
int n,m,a,b,c,f[32001];
int max(int x,int y){return x>y?x:y;}
int main()
{
  scanf("%d%d",&n,&m);
  for(int i=1;i<=m;i++)
    {
      scanf("%d%d%d",&a,&b,&c);
      int temp=v[c].size();//提前记录当前主件和该主件已出现的附件的总数，避免后面出现死循环
      if(!c)v[i].push_back({a,a*b});//处理主件
      else for(int k=0;k<temp;k++)
	     v[c].push_back({a+v[c][k].w,a*b+v[c][k].t});//依据题解中规则处理附件
    }
  //一维分组背包模板
  for(int i=1;i<=m;i++)
    for(int j=n;j>=0;j--)
      for(int k=0;k<v[i].size();k++)
	{
	  good now=v[i][k];
	  if(j>=now.w)f[j]=max(f[j],f[j-now.w]+now.t);
	}
  printf("%d",f[n]);
  return 0;
}