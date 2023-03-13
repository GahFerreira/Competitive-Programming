// eolymp.com/en/problems/1453

#include <bits/stdc++.h>

using namespace std;

#define for_(_i, _de, _ate) for(int _i = _de; _i < (int) _ate; _i++)
#define INF 30000 // Max int: 2147483647 & Max long long: 9223372036854775807

typedef long long ll;

// `gar`: Grafo de ARestas.
vector<int> bmf(vector<tuple<int, int, int>>& gar, int ini, int n_vertices)
{
    vector<int> dist(n_vertices+1, INF);
    vector<bool> descoberto(n_vertices+1, false);

    dist[ini] = 0;
    descoberto[ini] = true;

    for (int passo = 1; passo <= n_vertices-1; passo++)
    {
        for (auto& ar : gar)
        {
            int a, b, w;
            tie(a, b, w) = ar;

            if (!descoberto[a]) continue;

            if (dist[a] + w < dist[b])
            {
                if (!descoberto[b]) descoberto[b] = true;
                dist[b] = dist[a] + w;
            }
        }
    }

    return dist;
}

int main()
{
    int n, m;
    cin >> n >> m;

    vector<tuple<int, int, int>> gar(m);

    for (int i = 0; i < m; i++)
    {
        int a, b, w;
        cin >> a >> b >> w;

        gar[i] = {a, b, w};
    }

    auto dist = bmf(gar, 1, n);

    cout << dist[1];

    for (int i = 2; i < dist.size(); i++)
    {
        cout << " " << dist[i];
    }
    
    cout << '\n';

    return 0;
}