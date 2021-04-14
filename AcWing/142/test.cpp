#include<bits/stdc++.h>
using namespace std;
#define reg register
#define ll long long
#define ull unsigned long long
const int N = 1e6 + 10;


int n,m,len,idx;
char str[N];
struct node
{
    int num,nex[26];
    int f;
}tree[N];


void build(void);
void solve(void);


int main()
{
    scanf("%d%d",&n,&m);
    for(int i = 1; i <= n; ++i){
        scanf("%s",str + 1);
        len = strlen(str + 1);
        build();
    }
    for(int i = 1; i <= m; ++i){
        scanf("%s",str + 1);
        len = strlen(str + 1);
        solve();
    }
    return 0;
}
void build(void)
{
    reg int now = 0;
    for(reg int i = 1; i <= len; ++i){
        if(tree[now].nex[str[i] - 'a']){
            now = tree[now].nex[str[i] - 'a'];
        }
        else{
            tree[now].nex[str[i] - 'a'] = ++idx;
            now = idx;
        }
    }
    ++tree[now].f;
    return;
}
void solve(void)
{
    reg int now = 0;
    reg int ans = 0;
    for(reg int i = 1; i <= len; ++i){
        if(tree[now].nex[str[i] - 'a']){
            now = tree[now].nex[str[i] - 'a'];
            if(tree[now].f)ans += tree[now].f;
        }
        else{
            printf("%d\n",ans);
            return;
        }
    }
    printf("%d\n",ans);
    return;
}
