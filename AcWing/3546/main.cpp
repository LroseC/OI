#include <cstdio>
#include <iostream>

using namespace std;

int m;
string s, t;
string caozuo;
int l, r;

int main()
{
    cin >> s;
    cin >> m;
    for (int i = 1; i <= m; ++i) {
        cin >> caozuo;
        if (caozuo == "COPY") {
            cin >> l >> r;
            t = s.substr(l, r + 1);
        }
        if (caozuo == "CUT") {
            cin >> l >> r;
            t = s.substr(l, r + 1);
            s.erase(l, r + 1);
        }
        if (caozuo == "PASTE") {
            cin >> l;
            s = s.substr(0, l + 1) + t + s.substr(l);
        }
        cout << s << endl;
    }
    return 0;
}
