#include <bits/stdc++.h>

using namespace std;

#define ff first
#define ss second

#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()

#define str_to_lower(s) transform(s.begin(), s.end(), s.begin(), ::tolower)
#define str_to_upper(s) transform(s.begin(), s.end(), s.begin(), ::toupper)

#define for_(_i, _de, _ate) for(int _i = _de; _i < (int) _ate; ++_i)
#define INF 1000000000 // Max int: 2147483647 & Max long long: 9223372036854775807

typedef long long ll;

// const int dx[8] = {+1, +0, -1, +0, +1, +1, -1, -1}, 
//           dy[8] = {+0, +1, +0, -1, -1, +1, -1, +1};

#define MAXN 200'010

vector<ll> g[MAXN];

ll subt[MAXN];

void dfs(ll at, ll prev)
{
    subt[at] = 1;

    for (ll viz : g[at])
    {
        if (viz == prev) continue;

        dfs(viz, at);
        subt[at] += subt[viz];
    }
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(0);

    ll n;
    cin >> n;
    for_(i, 2, n+1)
    {
        ll chefe;
        cin >> chefe;
        g[chefe].push_back(i);
    }
    dfs(1, 0);
    for_(i, 1, n+1)
    {
        cout << subt[i]-1 << '\n';
    }

    return 0;
}