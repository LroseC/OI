#include<bits/stdc++.h>
using namespace std;
#define PII pair<int,int>

queue<PII> q;

int n,m;
char ch;

int gx[] = {1,2,2,1,-1,-2,-2,-1};
int gy[] = {2,1,-1,-2,-2,-1,1,2};
int a[210][210];
int b[210][210];
int ed[2];

int main()
{
    cin>>m>>n;
    for(int i = 1; i <= n; ++i){
        for(int j = 1; j <= m; ++j){
            cin>>ch;
            if(ch == 'K'){
                q.push(make_pair(i,j));
                a[i][j] = 1;
            }
            else if(ch == 'H'){
                a[i][j] = 1;
                ed[0] = i;
                ed[1] = j;
            }
            else if(ch == '.'){
                a[i][j] = 1;
            }
        }
    }
    while(!q.empty()){
        int x = q.front().first;
        int y = q.front().second;
        q.pop();
        for(int i = 0; i < 8; ++i){
            int xx = x + gx[i];
            int yy = y + gy[i];
            if(xx>0&&yy>0&&xx<=n&&yy<=m&&a[xx][yy]&&!b[xx][yy]){
                b[xx][yy] = b[x][y] + 1;
                q.push({xx,yy});
            }
        }
    }
    cout<<b[ed[0]][ed[1]]<<endl;
    return 0;
}
