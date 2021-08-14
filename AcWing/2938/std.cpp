#include <iostream>
#include <cstring>
#include <algorithm>

#define x first
#define y second

using namespace std;

typedef pair<int, int> PII;
const int N = 50010;


int n;
PII q[N];
int stk[N], top;
bool used[N];

PII operator- (PII a, PII b)
{
    return {a.x - b.x, a.y - b.y};
}

int operator* (PII a, PII b)
{
    return a.x * b.y - a.y * b.x;
}

int area(PII a, PII b, PII c)
{
    return (b - a) * (c - a);
}

int get_dist(PII a, PII b)
{
    int dx = a.x - b.x;
    int dy = a.y - b.y;
    return dx * dx + dy * dy;
}

void get_convex()
{
    sort(q, q + n);
    for (int i = 0; i < n; i ++ )
    {
        while (top >= 2 && area(q[stk[top - 2]], q[stk[top - 1]], q[i]) <= 0)
        {
            if (area(q[stk[top - 2]], q[stk[top - 1]], q[i]) < 0)
                used[stk[ -- top]] = false;
            else top -- ;
        }
        stk[top ++ ] = i;
        used[i] = true;
    }

    used[0] = false;
    for (int i = n - 1; i >= 0; i -- )
    {
        if (used[i]) continue;
        while (top >= 2 && area(q[stk[top - 2]], q[stk[top - 1]], q[i]) <= 0)
            top -- ;
        stk[top ++ ] = i;
    }
    top -- ;
	printf("top = %d\n", top);
}

int rotating_calipers()
{
    if (top <= 2) return get_dist(q[0], q[n - 1]);

    int res = 0;
    for (int i = 0, j = 2; i < top; i ++ )
    {
        auto d = q[stk[i]], e = q[stk[i + 1]];
        while (area(d, e, q[stk[j]]) < area(d, e, q[stk[j + 1]])) j = (j + 1) % top;
        res = max(res, max(get_dist(d, q[stk[j]]), get_dist(e, q[stk[j]])));
    }
    return res;
}

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; i ++ ) scanf("%d%d", &q[i].x, &q[i].y);
    get_convex();
	for (int i = 0; i < top; ++i) printf("x = %d, y = %d\n", q[stk[i]].x, q[stk[i]].y);
    printf("%d\n", rotating_calipers());

    return 0;
}