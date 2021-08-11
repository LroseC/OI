#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <map>
#include <vector>

#define x first
#define y second

using namespace std;

typedef long double LD;
typedef pair<int, int> PII;
typedef pair<LD, LD> PDD;
const int N = 10010;
const LD eps = 1e-18;

int n, cnt;
struct Line
{
    PDD st, ed;
    vector<int> ids;
}line[N];
int ki[N], vi[N];
int q[N], ans[N];

PDD operator-(PDD a, PDD b)
{
    return {a.x - b.x, a.y - b.y};
}

int sign(LD x)
{
    if (fabs(x) < eps) return 0;
    if (x < 0) return -1;
    return 1;
}

int dcmp(LD x, LD y)
{
    if (fabs(x - y) < eps) return 0;
    if (x < y) return -1;
    return 1;
}

LD cross(PDD a, PDD b)
{
    return a.x * b.y - a.y * b.x;
}

LD area(PDD a, PDD b, PDD c)
{
    return cross(b - a, c - a);
}

LD get_angle(const Line& a)
{
    return atan2(a.ed.y - a.st.y, a.ed.x - a.st.x);
}

bool cmp(const Line& a, const Line& b)
{
    LD A = get_angle(a), B = get_angle(b);
    if (!dcmp(A, B)) return area(a.st, a.ed, b.ed) < 0;
    return A < B;
}

PDD get_line_intersection(PDD p, PDD v, PDD q, PDD w)
{
    auto u = p - q;
    LD t = cross(w, u) / cross(v, w);
    return {p.x + v.x * t, p.y + v.y * t};
}

PDD get_line_intersection(Line& a, Line& b)
{
    return get_line_intersection(a.st, a.ed - a.st, b.st, b.ed - b.st);
}

// 判断bc的交点是否在a的右侧
bool on_right(Line& a, Line& b, Line& c)
{
    auto o = get_line_intersection(b, c);
    return area(a.st, a.ed, o) < 0;
}

void half_plane_intersection()
{
    sort(line, line + cnt, cmp);
    int hh = 0, tt = -1;
    for (int i = 0; i < cnt; i ++ )
    {
        if (i && !dcmp(get_angle(line[i - 1]), get_angle(line[i]))) continue;
        while (hh + 1 <= tt && on_right(line[i], line[q[tt - 1]], line[q[tt]])) tt -- ;
        while (hh + 1 <= tt && on_right(line[i], line[q[hh]], line[q[hh + 1]])) hh ++ ;
        q[ ++ tt] = i;
    }
    while (hh + 1 <= tt && on_right(line[q[hh]], line[q[tt - 1]], line[q[tt]])) tt -- ;
    while (hh + 1 <= tt && on_right(line[q[tt]], line[q[hh]], line[q[hh + 1]])) hh ++ ;

    int k = 0;
    for (int i = hh; i <= tt; i ++ )
        for (auto id: line[q[i]].ids)
            ans[k ++ ] = id;
    sort(ans, ans + k);

    printf("%d\n", k);
    for (int i = 0; i < k; i ++ ) printf("%d ", ans[i]);
    puts("");
}

int main()
{
    map<PII, vector<int>> ids;
    scanf("%d", &n);
    for (int i = 1; i <= n; i ++ ) scanf("%d", &ki[i]);
    for (int i = 1; i <= n; i ++ ) scanf("%d", &vi[i]);
    for (int i = 1; i <= n; i ++ )
        ids[{ki[i], vi[i]}].push_back(i);

    line[cnt ++ ] = {{0, 10000}, {0, 0}};
    line[cnt ++ ] = {{0, 0}, {10000, 0}};
    for (auto& [k, v]: ids)
        line[cnt ++ ] = {{0, k.x}, {1, k.x + k.y}, v};

    half_plane_intersection();
    return 0;
}