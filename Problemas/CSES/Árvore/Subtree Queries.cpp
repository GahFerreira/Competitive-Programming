#include <bits/stdc++.h>

using namespace std;

#define for_(_i, _de, _ate) for(ll _i = _de; _i < (ll) _ate; ++_i)

typedef long long ll;

#define MAXN 200'005

vector<ll> g[MAXN];
ll a[MAXN];
ll idx[MAXN], seg[2*MAXN], altura[MAXN];
ll id_at = 0;

void dfs(ll at, ll prev)
{
    cout << "At: " << at << '\n';
    idx[at] = id_at;
    ++id_at;

    altura[idx[at]] = 1;

    for (ll viz : g[at])
    {
        if (viz == prev) continue;

        dfs(viz, at);
        altura[idx[at]] += altura[idx[viz]];
    }
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(0);

    ll n, q;
    cin >> n >> q;
    for_(i, 0, n) cin >> a[i];
    for_(i, 0, n-1)
    {
        ll u, v;
        cin >> u >> v;
        --u; --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfs(0, -1);
    
    cout << "Valores:";
    for_(i, 0, n) cout << " " << a[i];
    cout << '\n';

    cout << "Ordem:";
    for_(i, 0, n) cout << " " << idx[i];
    cout << '\n';

    // Cuidado: `idx[i]` representa a posição em que o elemento `i` foi encontrado, 
    // e não o 'i-ésimo' elemento encontrado.
    for_(i, 0, n) seg[n+idx[i]] = a[i];
    for (ll i = n-1; i >= 1; --i) seg[i] = seg[2*i] + seg[2*i+1];

    cout << "Seg:";
    for_(i, n, 2*n) cout << " " << seg[i];
    cout << '\n';

    ll idq, u, x, alvo, l, r, soma;
    for_(iq, 0, q)
    {
        cin >> idq;

        if (idq == 1)
        {
            cin >> u >> x;
            --u;

            ll k = idx[u] + n;

            seg[k] = x;

            for (k /= 2; k >= 1; k /= 2) seg[k] = seg[2*k] + seg[2*k+1];
        }

        else
        {
            cin >> alvo;
            --alvo;

            l = idx[alvo] + n;
            r = l + altura[idx[alvo]] - 1;

            soma = 0;

            while (l <= r)
            {
                if (l % 2 == 1) soma += seg[l++];
                if (r % 2 == 0) soma += seg[r--];
                l /= 2; r /= 2;
            }

            cout << soma << '\n';
        }
    }

    return 0;
}