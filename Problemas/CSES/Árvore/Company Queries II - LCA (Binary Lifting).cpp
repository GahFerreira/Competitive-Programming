#include <bits/stdc++.h>
 
using namespace std;
 
#define for_(_i, _de, _ate) for(int _i = _de; _i < (int) _ate; ++_i)
 
typedef long long ll;
 
#define MAXN 200'010
#define LGMAXN 20
 
ll chefe[MAXN][LGMAXN];
ll abre[MAXN], fecha[MAXN];
vector<ll> g[MAXN];
ll tempo = 0;
 
void dfs(ll at)
{
    abre[at] = tempo++;
 
    for (ll viz : g[at]) dfs(viz);
 
    fecha[at] = tempo++;
}
 
bool eh_antec(ll a, ll b)
{
    return (abre[a] <= abre[b] and fecha[a] >= fecha[b]);
}
 
int main()
{
    ll n, q;
    cin >> n >> q;
    ll chefe_do_atual;
    for_(at, 0 +2, n-1 +2)
    {
        cin >> chefe_do_atual;
 
        chefe[at][0] = chefe_do_atual;
        g[ chefe_do_atual ].push_back(at);
    }
    for_(i_nivel, 0, LGMAXN) chefe[0][i_nivel] = 0;
    for_(i_nivel, 0, LGMAXN) chefe[1][i_nivel] = 0;
 
    for_(i_nivel, 1, LGMAXN)
    {
        for_(at, 0 + 2, n-2 + 2)
        {
            chefe[at][i_nivel] = chefe[ chefe[at][i_nivel-1] ][i_nivel-1];
        }
    }
    dfs(1);
 
    abre[0] = -1;
    fecha[0] = ++tempo;
    
    ll a, b, resp, salto, at;
    for_(iq, 0, q)
    {
        cin >> a >> b;
 
        if (eh_antec(a, b)) resp = a;
        else if (eh_antec(b, a)) resp = b;
        else
        {
            salto = LGMAXN-1;
            at = a;
 
            while (salto >= 0)
            {
                while ( !eh_antec(chefe[at][salto], b) ) at = chefe[at][salto];
                --salto;
            }
 
            resp = chefe[at][0];
        }
 
        cout << resp << '\n';
    }
 
    return 0;
}