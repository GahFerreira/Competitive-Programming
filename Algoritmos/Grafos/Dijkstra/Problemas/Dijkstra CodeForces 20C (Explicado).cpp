// Link Problema: https://codeforces.com/contest/20/problem/C
// Dijkstra com Priority Queue: O(n log(n) + m log(n)) ^ m = n -> O(n log(n))

#include <iostream>
#include <vector>
#include <map>
#include <queue> // priority_queue

using namespace std;

#define INF 1000000000000000000 // 10^18, por causa de long long

using ll = long long;

vector<pair<ll, int>> dijkstra(vector<map<int, ll>>& vizinhos, int n_vertices, int ini)
{
    // 'vertices[i]' guarda <distância_de_ini_a_atual, vertice_anterior_no_caminho_ini_atual>
    vector<pair<ll, int>> vertices(n_vertices + 1, {INF, -1});
    
    // 'fila' guarda em ordem crescente um par <dist_ini_v, v> onde 'v' é o id do vértice
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> fila;

    vertices[ini].first = 0;
    fila.push({0, ini});

    // São colocados até m elementos na fila
    while(!fila.empty())
    {
        int vertice_atual = fila.top().second;
        ll dist_ini_atual = fila.top().first;

        fila.pop();

        // Caso já tenhamos encontrado um caminho mais curto até o vértice do início da fila, saltamos a possibilidade atual
        if (dist_ini_atual > vertices[vertice_atual].first) continue;

        // Passamos por cada aresta uma vez, logo passamos no total por m arestas
        // Ao acessarmos 'vizinhos[vertice_atual]', gastamos log(n), pois é um map com até n elementos
        // Isso porque um vértice pode ter até n-1 vizinhos
        for (auto aresta : vizinhos[vertice_atual])
        {
            int prox_vertice = aresta.first;
            ll dist_atual_prox_vertice = aresta.second;

            if (dist_ini_atual + dist_atual_prox_vertice < vertices[prox_vertice].first)
            {
                vertices[prox_vertice].first = dist_ini_atual + dist_atual_prox_vertice;
                vertices[prox_vertice].second = vertice_atual;

                // Caso achamos uma melhoria na distância de ini até um vértice
                // Colocamos ele na fila, que gasta log(n)
                fila.push({vertices[prox_vertice].first, prox_vertice});
            }
        } // Dessa forma, para cada aresta gastamos log(n) para acessar + log(n) para pôr na fila
    }

    // Retornar 'vertices' é uma opção viável, mas ...
    // gerar resp aqui gasta menos memória
    return vertices;
}

int main()
{
    int n_vertices, n_arestas;

    cin >> n_vertices >> n_arestas;

    vector<map<int, ll>> vizinhos(n_vertices + 1);

    for(int i_aresta = 0; i_aresta < n_arestas; i_aresta++)
    {
        int v1, v2, peso_aresta;

        cin >> v1 >> v2 >> peso_aresta;

        if (vizinhos[v1].count(v2) == 0 || (ll) peso_aresta < vizinhos[v1][v2])
        {
            vizinhos[v1][v2] = peso_aresta;
            vizinhos[v2][v1] = peso_aresta;
        }
    }

    int vertice_inicial = 1;    
    int vertice_final = n_vertices;

    auto vertices = dijkstra(vizinhos, n_vertices, vertice_inicial);

    vector<int> resp;
 
    int vertice_anterior_atual = vertice_final;
 
    while (vertice_anterior_atual >= vertice_inicial)
    {
        resp.push_back(vertice_anterior_atual);
        vertice_anterior_atual = vertices[vertice_anterior_atual].second;
    }

    if (resp.back() != vertice_inicial) cout << "-1\n";

    else
    {
        for(int i = (int) resp.size() - 1; i >= 0; i--)
        {
            cout << resp[i] << " ";
        }

        cout << '\n';
    }

    return 0;
}