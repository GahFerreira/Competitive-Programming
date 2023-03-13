#include <bits/stdc++.h>
using namespace std;

#define MAX_N 10010
#define INF 1000000000000000000

typedef long long ll;

vector<pair<ll, ll>> adj[MAX_N];
vector<ll> dist(MAX_N, INF);
vector<bool> perc(MAX_N, false);

vector<ll> vem_de_quem(MAX_N, -1);

void dijkstra(ll ini)
{
    dist[ini] = 0;
    priority_queue<pair<ll, ll>> q;

    q.push({0, ini});

    while (!q.empty())
    {
        ll at = q.top().second; 
        q.pop();

        if (perc[at]) continue;
        perc[at] = true;
        
        for (auto a : adj[at])
        {
            int viz = a.first, w = a.second;

            if (dist[at] + w < dist[viz])
            {
                vem_de_quem[viz] = at;
                dist[viz] = dist[at] + w;
                q.push({ -dist[viz], viz });
            }
        }
    } 
}

int main()
{
    int n, m;
    cin >> n >> m;

    for(int i = 0; i < m; i++)
    {
        int a, b, w;
        cin >> a >> b >> w;

        adj[a].push_back({b, w});
        adj[b].push_back({a, w});
    }

    dijkstra(1);

    if (dist[n] == INF) cout << -1 << '\n';
    
    else
    {
        stack<int> s;
        int ult = n;

        while (ult != 1)
        {
            s.push(vem_de_quem[ult]);
            ult = vem_de_quem[ult];
        }

        while (!s.empty())
        {
            cout << s.top() << " ";
            s.pop();
        }

        cout << n << '\n';
    }

    return 0;
}