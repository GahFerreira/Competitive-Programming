#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// Curva de Hilbert
// 'll' poderia era originalmente 'ull' - ambos funcionam.
ll hilbert(ll x, ll y) 
{
    const ll logn = __lg(max(x, y) * 2 + 1) | 1;
    const ll maxn = (1ull << logn) - 1;
    ll res = 0;
    for (ll s = 1ull << (logn - 1); s; s >>= 1) 
    {
        bool rx = x & s, ry = y & s;
        res = (res << 2) | (rx ? ry ? 2 : 1 : ry ? 3 : 0);
        if (!rx) 
        {
            if (ry) x ^= maxn, y ^= maxn;
            swap(x, y);
        }
    }
    return res;
}

struct query
{
    int l, r, idx;
    long long ord;

    void calcular_ordem()
    {
        ord = hilbert(l, r);
    }
};

