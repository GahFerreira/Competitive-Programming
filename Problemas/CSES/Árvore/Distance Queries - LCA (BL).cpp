#include <bits/stdc++.h>
 
using namespace std;
 
#define for_(_i, _de, _ate) for(int _i = _de; _i < (int) _ate; ++_i)
 
typedef long long ll;
 
#define MAXN 200'010
#define LGMAXN 20
 
vector<ll> g[MAXN];
ll antecessor[MAXN][LGMAXN];
ll altura[MAXN];
ll abre[MAXN], fecha[MAXN];
ll tempo = 0;
 
// Calcula antecessor.
void dfs_pp(ll at, ll prev, ll h)
{
    antecessor[at][0] = prev;
    altura[at] = h;
    abre[at] = ++tempo;
 
    for (ll viz : g[at])
    {
        if (viz == prev) continue;
 
        dfs_pp(viz, at, h+1);
    }
    
    fecha[at] = ++tempo;
}
 
bool eh_antec(ll a, ll b)
{
    return (abre[a] <= abre[b] and fecha[a] >= fecha[b]);
}

ll menor_antecessor_comum(ll a, ll b)
{
    if (eh_antec(a, b)) return a;
    if (eh_antec(b, a)) return b;

    ll salto = LGMAXN-1, at = a;
 
    while (salto >= 0) // Busca binária.
    {
        while (!eh_antec(antecessor[at][salto], b)) at = antecessor[at][salto];
        --salto;
    }

    at = antecessor[at][0];

    return at;
}

void pre_processamento()
{
    dfs_pp(1, 0, 0);
 
    for_(nivel, 0, LGMAXN) antecessor[0][nivel] = 0;
    for_(nivel, 0, LGMAXN) antecessor[1][nivel] = 0;
 
    for_(nivel, 1, LGMAXN)
    {
        for_(at, 2, MAXN) // n+1, caso 1-indexe e use 'n'.
        {
            antecessor[at][nivel] = antecessor[antecessor[at][nivel-1]][nivel-1];
        }
    }
 
    abre[0] = -1; fecha[0] = ++tempo;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(0);
 
    ll n, q;
    cin >> n >> q;
    for_(i, 0, n-1)
    {
        ll u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    
    pre_processamento();

    for_(iq, 0, q)
    {
        ll u, v;
        cin >> u >> v;
 
        ll lca = menor_antecessor_comum(u, v);
        cout << altura[u] + altura[v] - 2 * altura[lca] << '\n';
    }
 
    return 0;
}