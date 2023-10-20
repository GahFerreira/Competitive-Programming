/*
    Primeiramente, calculamos a distância mínima de todos os vértices para todos os vértices.

    Se houver vértices 'x', 'y' tal que a distância mínima entre eles seja menor que a aresta 'x''y',
    respondemos -1.

    Caso contrário, não há distância mínima melhor que apenas usar a aresta 'x''y'.
    
    Assim, caso removamos a aresta 'x''y', a distância mínima entre 'x' e 'y' não pode diminuir,
    mas continuar igual ou aumentar.

    Assim, para cada aresta do grafo que conecte vértices 'x' e 'y', calculamos a distância mínima
    entre 'x' e 'y' sem a aresta 'x''y'. 
        - Se a distância final for igual, adicionamos 1 à resposta.
            - Ou seja, aquela "rota" (aresta 'x''y') pode ser removida 
            sem aumentar a distância entre 'x' e 'y'.
        - Se a distância final for maior, não fazemos nada.
            - Ou seja, aquela "rota" é a única menor rota entre 'x' e 'y', 
            e removê-la aumentaria o custo da viagem entre 'x' e 'y'.

    Algoritmo:
        1. Rodamos um Floyd-Warshall para calcular as distâncias mínimas entre todos os vértices. O(n^3)
        2. Para cada aresta do grafo, rodamos um Dijkstra entre os vértices incididos por ela, removendo-a
           temporariamente do grafo durante o Dijkstra. O( m * (n logn + m) )
        
        Seja g um grafo completo -> m = O(n^2).
        Complexidade final: O( n^4 + n^3 logn ) = O(n^4).
*/

#include <bits/stdc++.h>

using namespace std;

#define for_(_i, _de, _ate) for(int _i = _de; _i < (int) _ate; ++_i)

#define INF 1'000'000'000

int main()
{
    ios::sync_with_stdio(false); cin.tie(0);

    int n;
    cin >> n;

    int g[n][n];
    int d[n][n];
    for_(i, 0, n)
        for_(j, 0, n)
        {
            cin >> g[i][j];
            d[i][j] = g[i][j];
        }

    for_(k, 0, n)
        for_(i, 0, n)
            for_(j, 0, n)
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);

    for_(i, 0, n)
        for_(j, 0, n)
            if (g[i][j] != d[i][j])
            {
                cout << "-1\n";
                return 0;
            }

    int resp = 0;

    for_(i, 0, n)
        for_(j, i+1, n)
        {
            g[i][j] = INF;

            vector<int> dist(n, INF);
            vector<bool> proc(n, false);
            priority_queue<pair<int, int>> q;

            q.push({0, i});
            dist[i] = 0;
            
            while (!q.empty())
            {
                int at = q.top().second; q.pop();

                if (at == j) break;

                if (proc[at]) continue;
                proc[at] = true;

                for (int viz = 0; viz < n; ++viz)
                {
                    if (proc[viz]) continue;

                    int cand = dist[at] + g[at][viz];

                    if (cand < dist[viz])
                    {
                        dist[viz] = cand;
                        q.push({-cand, viz});
                    }
                }
            }

            g[i][j] = d[i][j];

            if (dist[j] == g[i][j]) ++resp;
        }

    cout << resp << '\n';

    return 0;
}