// vjudge.net/problem/UVA-10099
// onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=12&page=show_problem&problem=1040

#include <bits/stdc++.h>

using namespace std;

#define for_(_i, _de, _ate) for(int _i = _de; _i < (int) _ate; _i++)
#define INF 9223372036854775807 // Max int: 2147483647 & Max long long: 9223372036854775807

typedef long long ll;

ll BMF(vector<tuple<ll, ll, ll>> gar, ll ini, ll ult, ll n)
{
    vector<ll> min_t(n+1, -1);
    vector<bool> descoberto(n+1, false);
    vector<ll> prev(n+1, -1);

    min_t[ini] = INF;
    descoberto[ini] = true;

    // Funciona com `passo <= n`, com certeza, mas passa com `<= n-1` também.
    //for (ll passo = 1; passo <= n-1; passo++)
    for (;;)    // Funciona otimizando também!
    {
        bool relaxou = false;

        for (auto& ar : gar)
        {
            ll a, b, w;
            tie(a, b, w) = ar;

            if (!descoberto[a]) continue;

            // Para cada vértice `a` já descoberto, você oferece ao vizinho `b` o menor
            // entre: a qtd de turistas até `a` e a qtd de turistas de `a` a `b`.
            if (min_t[b] < min(min_t[a], w))
            {
                if (!descoberto[b]) descoberto[b] = true;

                min_t[b] = min(min_t[a], w);
                prev[b] = a;

                relaxou = true;
            }
        }

        if (!relaxou) break;
    }

    ll ret = INF;
    ll v = ult;

    // O problema restringe sempre ter caminho de ini a ult.
    while (v != ini)
    {
        ret = min(ret, min_t[v]);
        v = prev[v];
    }

    return ret;
}

int main()
{
    ll n, r, tc = 1;
    while ((cin >> n >> r) and n+r != 0)
    {
        vector<tuple<ll, ll, ll>> gar;
        for_(i, 0, r)
        {
            ll a, b, w;
            cin >> a >> b >> w;
            // w-1 porque o MOTORISTA precisa de um assento.
            gar.push_back({a, b, w-1});
            gar.push_back({b, a, w-1});
        }
        ll ini, ult, t;
        cin >> ini >> ult >> t;

        ll min_estrada = BMF(gar, ini, ult, n);

        cout << "Scenario #" << tc++ << '\n';
        cout << "Minimum Number of Trips = ";

        if (t % min_estrada == 0) cout << t / min_estrada << "\n\n";
        else cout << (t/min_estrada)+1 << "\n\n";
    }
}