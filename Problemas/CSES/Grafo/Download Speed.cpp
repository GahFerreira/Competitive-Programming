#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#define watch(x) cerr << "\n" << (#x) << " is " << (x) << endl;
#else
#define watch(x)
#endif

#define for_(_i, _de, _ate) for(ll _i = _de; _i < (ll) _ate; ++_i)

#define ff first
#define ss second

#define all(x) x.begin(), x.end()

#define str_to_lower(s) transform(s.begin(), s.end(), s.begin(), ::tolower)
#define str_to_upper(s) transform(s.begin(), s.end(), s.begin(), ::toupper)

#define INF 1'000'000'000 // Max int: 2'147'483'647 & Max long long: 9'223'372'036'854'775'807

typedef long long ll;
typedef long double ld;

// const int dx[8] = {+1, +0, -1, +0, +1, +1, -1, -1}, 
//           dy[8] = {+0, +1, +0, -1, -1, +1, -1, +1};

int main()
{
    //ios::sync_with_stdio(false); cin.tie(0);

    ll n, m;
    cin >> n >> m;
    ll g[n+1][n+1];
    for_(i, 0, n+1)
        for_(j, 0, n+1)
            g[i][j] = 0;

    for_(i, 0, m)
    {
        ll a, b, w;
        cin >> a >> b >> w;
        g[a][b] += w;
    }

    ll prev[n+1];
    ll flow = 0;
    while (true)
    {
        // cout << "Flow: " << flow << '\n';

        fill(prev, prev+n+1, -1);

        queue<ll> q;
        q.push(1);
        prev[1] = -2;

        bool csg = false;
        while (!q.empty())
        {
            ll at = q.front(); q.pop();

            if (at == n)
            {
                csg = true;
                ll min_w = INF;

                while (at != 1)
                {
                    min_w = min(min_w, g[prev[at]][at]);
                    at = prev[at];
                }

                at = n;
                while (at != 1)
                {
                    g[prev[at]][at] -= min_w;
                    g[at][prev[at]] += min_w;
                    at = prev[at];
                }

                flow += min_w;

                break;
            }

            for (ll viz = 1; viz <= n; ++viz)
            {
                if (prev[viz] != -1 or g[at][viz] == 0) continue;
                
                q.push(viz);
                prev[viz] = at;
            }
        }

        if (csg == false) break;
    }

    cout << flow << '\n';

    return 0;
}