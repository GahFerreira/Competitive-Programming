// Obj.: Percorrer grafos simples, obtendo menor distância entre o vértice inicial e os demais.
// Restr.: Arestas sem pesos.
// Compl.: O(v + e), v = | vértices |, e = | arestas |

#include <bits/stdc++.h>

using namespace std;

#define MAX_N 10000
#define INF 1000000

vector<int> adj[MAX_N];
vector<int> distancia(MAX_N, INF);
vector<bool> encontrados(MAX_N, false);

void bfs(int ini)
{
    queue<int> q;
    encontrados[ini] = true;
    distancia[ini] = 0;

    while (!q.empty())
    {
        int at = q.front(); q.pop();

        for (auto viz : adj[at])
        {
            if (encontrados[viz]) continue;
            q.push(viz);
            encontrados[viz] = true;
            distancia[viz] = distancia[at]+1;
        }
    }
}