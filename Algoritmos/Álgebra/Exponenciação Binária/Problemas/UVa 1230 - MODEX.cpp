// uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=3671

#include <bits/stdc++.h>

using namespace std;

#define for_(_i, _de, _ate) for(ll _i = _de; _i < (ll) _ate; ++_i)

using ll = long long;

int main()
{
    ios::sync_with_stdio(false); cin.tie(0);

    int t;
    while (cin >> t and t != 0)
    {
        for_(i, 0, t)
        {
            int x, y, n;
            cin >> x >> y >> n;

            int resp = 1;
            ll u = x;
            while (y > 0)
            {
                if (y & 1) resp = resp * u % n;
                u *= u;
                if (u >= n) u %= n;
                y >>= 1;
            }

            cout << resp << '\n';
        }
    }

    return 0;
}