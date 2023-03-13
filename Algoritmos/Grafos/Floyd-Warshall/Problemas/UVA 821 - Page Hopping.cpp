// onlinejudge.org/index.php?option=com_onlinejudge&Itemid=9

#include <bits/stdc++.h>

using namespace std;

#define for_(_i, _de, _ate) for(int _i = _de; _i < (int) _ate; _i++)
#define INF 1000000000 // Max int: 2147483647 & Max long long: 9223372036854775807

typedef long long ll;
typedef long double ld;

// bool sort_cmp(int a, int b)
// {
//     return (a < b);
// }

double fw(vector<vector<int>> adj, int n)
{
    int dist[n+1][n+1];

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (i == j) dist[i][j] = 0;
            else if (adj[i][j]) dist[i][j] = adj[i][j];
            else dist[i][j] = INF;
        }
    }

    for (int v_at = 1; v_at <= n; v_at++)
    {
        for (int viz_in = 1; viz_in <= n; viz_in++)
        {
            for (int viz_out = 1; viz_out <= n; viz_out++)
            {
                dist[viz_in][viz_out] = min(dist[viz_in][viz_out],
                                            dist[viz_in][v_at] + dist[v_at][viz_out]);
            }
        }
    }

    int soma = 0, qtd_links = 0;

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (dist[i][j] != INF and dist[i][j] != 0) 
            {
                soma += dist[i][j];
                qtd_links++;
            }
        }
    }

    return (double) (soma / (double) qtd_links);
}

int main()
{
    //ios::sync_with_stdio(false); cin.tie(0);

    for (int tc = 1; ; tc++)
    {
        int a, b;
        cin >> a >> b;

        if (a+b == 0) break;

        vector<vector<int>> adj(101, vector<int>(101, 0));

        adj[a][b] = 1;

        while (cin >> a >> b)
        {
            if (a+b == 0) break;

            adj[a][b] = 1;
        }

        cout << "Case " << tc << ": average length between pages = ";
        printf("%.3lf", fw(adj, 100));    
        cout << " clicks\n";
    }

    return 0;
}