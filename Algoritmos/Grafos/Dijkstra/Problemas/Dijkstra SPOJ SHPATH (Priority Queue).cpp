// Link problema: https://www.spoj.com/problems/SHPATH/
// Estranhamente, só nos dá o número de vértices que é 10^4. Quadrático não passa, então fui na fé em PrioQ.

#include <iostream>
#include <vector>
#include <map>
#include <queue> // priority_queue

using namespace std;

#define for_(_i, _from, _to) for(int _i = _from; _i < (int) _to; _i++)

#define INF 1000000000000

typedef long long ll;

ll dijkstra(vector<map<int, ll>>& vizinhos, int n_vertices, int ini, int ult)
{
    vector<ll> dist_ini(n_vertices + 1, INF);

    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> fila;

    dist_ini[ini] = 0;
    fila.push({0, ini});

    while (!fila.empty())
    {
        int melhor = fila.top().second;

        if (melhor == ult) break;

        int dist_ini_melhor = fila.top().first;
        
        fila.pop();

        if (dist_ini[melhor] < dist_ini_melhor) continue;

        for (auto aresta : vizinhos[melhor])
        {
            int vizinho = aresta.first;
            ll dist_melhor_vizinho = aresta.second;

            if (dist_ini[melhor] + dist_melhor_vizinho < dist_ini[vizinho])
            {
                dist_ini[vizinho] = dist_ini[melhor] + dist_melhor_vizinho;

                fila.push({dist_ini[vizinho], vizinho});
            }
        }
    }

    return dist_ini[ult];
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(0);

    int tt;
    cin >> tt;

    while(tt--)
    {
        int n_vertices;
        cin >> n_vertices;

        vector<map<int, ll>> vizinhos(n_vertices + 1);
        map<string, int> cidades;

        for_(i_cidade_atual, 1, n_vertices + 1)
        {
            string cidade_atual;
            cin >> cidade_atual;

            cidades[cidade_atual] = i_cidade_atual;

            int n_vizinhos;
            cin >> n_vizinhos;

            for_(i_vizinho, 0, n_vizinhos)
            {
                int vizinho, peso_aresta;

                cin >> vizinho >> peso_aresta;

                if (vizinhos[i_cidade_atual].count(vizinho) == 0 or peso_aresta < vizinhos[i_cidade_atual][vizinho])
                {
                    vizinhos[i_cidade_atual][vizinho] = peso_aresta;
                }
            }
        }

        int n_consultas;

        cin >> n_consultas;

        for_(i_consulta, 0, n_consultas)
        {
            string c1, c2;

            cin >> c1 >> c2;

            ll resp = dijkstra(vizinhos, n_vertices, cidades[c1], cidades[c2]);

            cout << resp << '\n';
        }
    }

    return 0;
}