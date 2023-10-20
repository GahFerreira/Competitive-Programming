#include <bits/stdc++.h>

using namespace std;

#define for_(_i, _de, _ate) for(ll _i = _de; _i < (ll) _ate; ++_i)

using ll = long long;

int main()
{
    ios::sync_with_stdio(false); cin.tie(0);

    int b, p, m;
    while (cin >> b >> p >> m)
    {
        if (p == 0) { cout << "1\n"; continue; }

        int resp = 1;
        ll u = b;
        while (p > 0)
        {
            if (p & 1) resp = resp * u % m;
            u *= u;
            if (u >= m) u %= m;
            p >>= 1;
        }

        cout << resp << '\n';
    }

    return 0;
}