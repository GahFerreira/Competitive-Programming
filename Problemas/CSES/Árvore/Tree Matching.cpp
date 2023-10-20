/*
    A ideia é salvar para cada vértice qual o melhor que você consegue
    incluindo uma aresta que incide nele na resposta, e não incluindo nenhuma aresta.

    Partindo de um vértice raiz, para cada vértice você pode:
        1. Não escolher nenhuma aresta que incide nele.
        2. Escolher exatamente uma aresta que incide nele.

    Para o caso 1, para cada vizinho dele, você pega o máximo entre escolher aquele
    vizinho e não escolhê-lo.

    Para o caso 2, você parte inicialmente da resposta do caso 1, mas testa para cada
    vértice vizinho adicionar 1 à resposta, e ao invés de pegar o máximo entre
    escolher aquele vizinho e não escolhê-lo, agora você é forçado a pegar o valor
    de não escolhê-lo.

    Parte uma dfs da raiz, calcula para todos os vértices os valores, e no final,
    a resposta será o melhor entre escolher ou não o próprio vértice da raiz.
*/

#include <bits/stdc++.h>

using namespace std;

#define ff first
#define ss second

#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()

#define str_to_lower(s) transform(s.begin(), s.end(), s.begin(), ::tolower)
#define str_to_upper(s) transform(s.begin(), s.end(), s.begin(), ::toupper)

#define for_(_i, _de, _ate) for(int _i = _de; _i < (int) _ate; ++_i)
#define INF 1000000000 // Max int: 2147483647 & Max long long: 9223372036854775807

typedef long long ll;

#define MAXN 200'010

vector<ll> g[MAXN];
ll pd[MAXN][2];

void dfs(ll at, ll prev)
{
    ll soma_n_escolher = 0;
    ll mx_escolher = 0;
    for (ll viz : g[at])
    {
        if (viz == prev) continue;

        dfs(viz, at);
        soma_n_escolher += max(pd[viz][0], pd[viz][1]);
    }

    ll candidato;
    for (ll viz : g[at])
    {
        if (viz == prev) continue;

        candidato = 1 + soma_n_escolher - max(pd[viz][0], pd[viz][1]) + pd[viz][1];
        mx_escolher = max(mx_escolher, candidato);
    }

    pd[at][0] = mx_escolher;
    pd[at][1] = soma_n_escolher;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(0);

    ll n;
    cin >> n;
    for_(i, 0, n-1)
    {
        ll u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfs(1, -1);
    cout << max(pd[1][0], pd[1][1]) << '\n';

    return 0;
}