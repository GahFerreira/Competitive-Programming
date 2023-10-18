/*
    Ideia:
        Um grafo resposta não pode ter nenhuma aresta 'A' de forma que o caminho de 'u->v' com
        'A' seja mais curto que 'u->v' usando apenas as arestas da AGM.

        Para garantir isso, começamos com um grafo com os vértices da AGM sem arestas. 
        Cada vértice é inicialmente uma componente (ou conjunto, abreviado para 'conj.').
        
        Para unirmos duas componentes, escolhermos sempre a aresta de menor custo não tratada.

        Como olhamos para duas componentes distintas, antes de tratar a aresta atual, não há caminho
        entre nenhum vértice das duas componentes.
        Ademais, ao adicionar a aresta, agora há caminho entre todo par de vértices das duas componentes,
        e a aresta de maior custo é o custo da aresta atual.

        Assim, conseguimos adicionar arestas entre todo par de vértices das duas componentes com peso
        igual ao da aresta atual +1 (e também tratar o caso de não pôr aresta entre o par).
            - O único par que não podemos adicionar aresta é o próprio par [u, v] que determina a
            aresta atual.
        
        Assim, ao olharmos para duas componentes distintas:
            1. Calculamos quantos pares conseguimos formar entre elas:
                - Seja 'vertices_u' o da 1ª componente e 'vertices_v' o da 2ª.
            2. Calculamos quantas possibilidades cada aresta pode ter.
                - Seja 'w' o peso da aresta atual: 'S-w+1' é o número de possibilidades.
            3. Multiplicamos a resposta atual por: '(S-w+1) ^ (vertices_u * vertices_v - 1)'.

        Para tratar as componentes, usamos DSU e para o cálculo da resposta, exponenciação binária.
*/

#include <bits/stdc++.h>

using namespace std;

#define all(x) x.begin(), x.end()

#define for_(_i, _de, _ate) for(int _i = _de; _i < (int) _ate; _i++)

using ll = long long;

const ll MOD = 998244353;

ll exp_bin(ll a, ll p)
{
    ll ret = 1;

    a %= MOD;

    while (p)
    {
        if (p&1) ret = ret * a % MOD;
        a = a * a % MOD;

        p >>= 1;
    }

    return ret;
}

int achar_ancestral(int u, int ancestral[])
{
    if (ancestral[u] == u) return u;

    return (ancestral[u] = achar_ancestral(ancestral[u], ancestral));
}

void unir(int u, int v, int ancestral[], int subt[])
{
    int anc_u = achar_ancestral(u, ancestral);
    int anc_v = achar_ancestral(v, ancestral);

    // Conj. de 'anc_u' maior que o de 'anc_v'. Isso para que o ancestral da folha fique menos longe.
    if (subt[anc_u] < subt[anc_v]) swap(anc_u, anc_v);

    subt[anc_u] += subt[anc_v];
    ancestral[anc_v] = anc_u;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(0);

    int t;
    cin >> t;
    while (t--)
    {
        ll n, s;
        cin >> n >> s;

        vector<tuple<int, int, int>> arestas;

        for_(i, 0, n-1)
        {
            int u, v, w;
            cin >> u >> v >> w;
            --u; --v; // 0-based
            arestas.push_back({w, u, v});
        }

        sort(all(arestas)); // Prioriza o 'w', porque ele vem primeiro na tupla.

        int ancestral[n];
        int subt[n];

        for_(i, 0, n)
        {
            ancestral[i] = i;
            subt[i] = 1;
        }

        ll resp = 1;

        for_(i, 0, arestas.size())
        {
            auto [w, u, v] = arestas[i];

            ll subt_u = subt[achar_ancestral(u, ancestral)];
            ll subt_v = subt[achar_ancestral(v, ancestral)];

            ll possibilidades = s-w+1;

            ll n_pares = subt_u*subt_v-1;

            resp = resp * exp_bin(possibilidades, n_pares) % MOD;

            // Combina as componentes.
            unir(u, v, ancestral, subt);
        }

        cout << resp << '\n';
    }

    return 0;
}