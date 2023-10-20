/*
Ideia:
  - Uma pessoa p perde dinheiro sss houver uma pessoa x, diferente de p,
  que alcançar tanto p quanto seus filhos a, b, sem usar as arestas {p, a} ou {p, b}.
    - Isso é verdade porque significa que há uma forma de pedir dinheiro para a, b antes
    de pedir dinheiro para p.
    - x diferente de p, pois se a única forma de visitar (p, a, b) for a partir de p,
    então p tem que ser a primeira pessoa a ser pedida dinheiro.
      - Entretanto, vale notar que não há como p alcançar a e b sem as arestas {p, a} e {p, b},
      dessa forma, uma pessoa p não pode ser uma pessoa x.
  - Uma forma de descobrir se, para uma pessoa p fixa, uma pessoa x existe, é iniciar 
  uma busca em cada pessoa diferente de p, e não usar as arestas {p, a} nem {p, b}.
    - Assim, se em uma busca chegarmos a {p, a, b}, sabemos que a pessoa do início da busca
    é uma pessoa x.
    - Isso nos leva a um algoritmo cúbico: 
      1. Para cada pessoa p, [O(n)]
      2. iniciar uma busca [O(n)]
      3. a partir de cada outra pessoa. [O(n)]
  - Uma forma alternativa baseia-se na observação de que, se existe caminho de x para a, b, p,
  então em um grafo com as arestas reversas, existe caminho de a, b, p para x.
    - Como no grafo inicial não usamos as arestas {p, a} nem {p, b}, no grafo com as arestas
    reversas não usamos as arestas {a, p} nem {b, p}.
    - Isso nos leva a um algoritmo quadrático:
      1. Para cada pessoa p, [O(n)]
      2. iniciar uma busca [O(n)],
      3. a partir de p, a, b. [O(1)]
    - Se chegarmos a alguma pessoa diferente de p em cada uma das buscas, essa pessoa é
    uma pessoa x, logo a pessoa p perde dinheiro.

Algoritmo:
  - Geramos o grafo com as arestas reversas.
  - Para cada pessoa p, fazemos três BFS (ou DFS), nas quais não usamos as arestas 
  {a, p} ou {b, p}:
    - Uma a partir de p
    - Outra de a
    - Outra de b
  - Marcamos cada vértice encontrado em cada uma das buscas.
  - Por fim, após as buscas, se houver algum vértice encontrado 3 vezes
  (incluindo a, b, mas não p), esse vértice é uma pessoa x, logo a pessoa p perde dinheiro.

Compl.: O(n²), pois fazemos 3n BFS. 
  - Note que a quantidade de arestas é sempre 2n, logo cada BFS é O(2n) = O(n).
*/

#include <bits/stdc++.h>

using namespace std;

#define all(x) x.begin(), x.end()
#define for_(_i, _de, _ate) for(int _i = _de; _i < (int) _ate; _i++)

int main()
{
    ios::sync_with_stdio(false); cin.tie(0);

    int n;
    cin >> n;
    vector<vector<int>> adj(n+1);
    vector<pair<int, int>> pais(n+1);
    for (int i = 1; i <= n; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(i);
        adj[v].push_back(i);
        pais[i] = {u, v};
    }

    vector<bool> perde_dinheiro(n+1, false);

    queue<int> q;
    vector<bool> visitado(n+1);
    vector<int> qtd_visitas(n+1);

    for (int p = 1; p <= n; p++)
    {
        fill(all(qtd_visitas), 0);

        int a, b;
        tie(a, b) = pais[p];

        vector<int> inis = {p, a, b};

        for (int ini : inis)
        {
            fill(all(visitado), false);

            q.push(ini);
            visitado[ini] = true;
            qtd_visitas[ini]++;

            while (!q.empty())
            {
                int at = q.front(); q.pop();
                for (int viz : adj[at])
                {
                    if (!visitado[viz] and ((at != a and at != b) or (viz != p)))
                    {
                        q.push(viz);
                        visitado[viz] = true;
                        qtd_visitas[viz]++;
                    }
                }
            }
        }

        for (int i = 1; i <= n; i++)
        {
            // Não precisa checar que i != p, pois se `qtd_visitas[i] == 3`,
            // i é uma pessoa x, e p não pode ser uma pessoa x.
            if (qtd_visitas[i] == 3)
            {
                perde_dinheiro[p] = true;
                break;
            }
        }
    }

    for (int i = 1; i <= n; i++)
    {
        if (perde_dinheiro[i] == true) cout << "Y";
        else cout << "N";
    }
    cout << '\n';

    return 0;
}