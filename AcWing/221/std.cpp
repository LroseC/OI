#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int phi(int x)
{
    int ans=x;
    for(int i=2;(ll)i*i<=x;++i)
        if(x%i==0)
        {
            ans=(ll)ans*(i-1)/i;
            while(x%i==0) x/=i;
        }
    if(x>1) ans=(ll)ans*(x-1)/x;
    return ans;
}

int main()
{
    int n; scanf("%d",&n);
    ll ans=0;
    for(int i=1;(ll)i*i<=n;++i)
        if(n%i==0)
        {
            ans+=(n/i)*phi(i);
            if(i*i!=n) ans+=i*phi(n/i);
        }
    printf("%lld",ans);
    return 0;
}