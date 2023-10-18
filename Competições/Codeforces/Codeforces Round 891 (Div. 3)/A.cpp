#include <bits/stdc++.h>

using namespace std;

#define ff first
#define ss second

#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()

#define str_to_lower(s) transform(s.begin(), s.end(), s.begin(), ::tolower)
#define str_to_upper(s) transform(s.begin(), s.end(), s.begin(), ::toupper)

#define for_(_i, _de, _ate) for(int _i = _de; _i < (int) _ate; _i++)
#define INF 1000000000 // Max int: 2147483647 & Max long long: 9223372036854775807

typedef long long ll;

// const int dx[8] = {+1, +0, -1, +0, +1, +1, -1, -1}, 
//           dy[8] = {+0, +1, +0, -1, -1, +1, -1, +1};

int main()
{
    ios::sync_with_stdio(false); cin.tie(0);

    ll tt;
    cin >> tt;
    while (tt--)
    {

        ll n;
        cin >> n;
        ll soma = 0;
        for_(i, 0, n)
        {
            ll x;
            cin >> x;
            soma += x;
        }

        if (soma % 2 == 0) cout << "yes\n";
        else cout << "no\n";
    }

    return 0;
}