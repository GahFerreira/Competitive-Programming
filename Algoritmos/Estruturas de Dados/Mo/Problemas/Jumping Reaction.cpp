// codeforces.com/gym/104375/problem/J

#include <bits/stdc++.h>

using namespace std;

#define all(x) x.begin(), x.end()

#define for_(_i, _de, _ate) for(int _i = _de; _i < (int) _ate; ++_i)

typedef long long ll;

#define MOD 1'000'000'007 

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
    ll ord;

    void calcular_ordem()
    {
        ord = hilbert(l, r);
    }
};

int main()
{
    ios::sync_with_stdio(false); cin.tie(0);

    int n, q;
    cin >> n >> q;
    ll a[n];
    for_(i, 0, n) cin >> a[i];
    query qs[q];
    for_(i, 0, q)
    {
        int l, r;
        cin >> l >> r;
        qs[i] = { l-1, r-1, i, 0 };
        qs[i].calcular_ordem();
    }
    
    sort(qs, qs+q, [](const query& q1, const query& q2)
    {
        return q1.ord < q2.ord;
    });

    ll resp = 0, soma = 0, l = 0, r = -1, lq, rq;
    int z[q];
    for_(i_q, 0, q)
    {
        lq = qs[i_q].l, rq = qs[i_q].r;

        while (l < lq)
        {
            soma -= a[l];
            if (soma < 0) soma += MOD;

            resp -= (a[l] * soma) % MOD;
            if (resp < 0) resp += MOD;

            ++l;
        }

        // Add
        while (l > lq)
        {
            --l;

            resp += (a[l] * soma) % MOD;
            if (resp >= MOD) resp -= MOD;

            soma += a[l];
            if (soma >= MOD) soma -= MOD;
        }

        // Add
        while (r < rq)
        {
            ++r;

            resp += (a[r] * soma) % MOD;
            if (resp >= MOD) resp -= MOD;

            soma += a[r];
            if (soma >= MOD) soma -= MOD;
        }

        while (r > rq)
        {
            soma -= a[r];
            if (soma < 0) soma += MOD;

            resp -= (a[r] * soma) % MOD;
            if (resp < 0) resp += MOD;

            --r;
        }

        z[qs[i_q].idx] = resp;
    }

    for_(i, 0, q) cout << z[i] << '\n';

    return 0;
}