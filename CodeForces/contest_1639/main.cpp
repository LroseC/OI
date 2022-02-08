#include<bits/stdc++.h>
using namespace std;
using LL = long long;
int t,n,m,st,emt;
char op[5];
inline void Read()
{
    scanf("%d%d%d%d",&n,&m,&st,&emt);
    for(int i=1;i<=m;i++) scanf("%d%d",&emt,&emt);
}
inline LL Myrand(int l,int r)
{
    return (0ll + rand() << 32 | rand())%(r-l+1)+l;
}
const int N = 1e6 + 10;
int Deg[N], Flag[N];
inline void Work()
{
    scanf("%s",op+1);
    while(op[1]!='A'&&op[1]!='F')
    {
        int d,deg,flag,ans_pos=0,ans_deg=0,pack_pos=0,pack_deg=0;
        scanf("%d",&d);
		LL sum = 0;
        for(int i=1;i<=d;i++)
        {
            scanf("%d%d",&deg,&flag);
			Deg[i] = deg;
			sum += deg;
			Flag[i] = flag;
            if(!flag&&!ans_pos) ans_deg=deg,ans_pos=i;
            else if(!flag&&ans_deg>deg) ans_pos=i,ans_deg=deg; 
            else if(!pack_pos||pack_deg<deg) pack_pos=i,pack_deg=deg;
        }
        if(!ans_pos) {
			bool ffff = 0;
			LL t = Myrand(1, sum);
			for (int i = 1; i <= d; ++i) {
				t -= Deg[i];
				if (t <= 0) {
					printf("%d\n", t);
					fflush(stdout);
					ffff = 1;
					break;
				}
			}
			if (!ffff)
				printf("%d\n",Myrand(1,d));
		}
        else printf("%d\n",ans_pos);
        fflush(stdout);
        scanf("%s",op+1);
    }
}
int main()
{
    scanf("%d",&t);
    while(t--)
    {
        Read();
        Work();
    }
    return 0;
}
