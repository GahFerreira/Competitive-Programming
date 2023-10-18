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

    int t;
    cin >> t;
    while (t--)
    {
        ll n;
        cin >> n;
        vector<ll> a(2*n);
        vector<ll> xs(n);
        for_(i, 0, n) 
        {
            cin >> a[n+i];
            xs[i] = a[n+i];
        }
        sort(a.begin()+n, a.end());
        for (ll i = n-1; i >= 1; --i) a[i] = a[2*i] + a[2*i+1];
        
        // cout << "Seg:";
        // for (ll i = 0; i < 2*n; ++i) cout << " " << a[i];
        // cout << '\n';

        for_(i, 0, n)
        {
            ll resp = n;
            // cout << "resp1: " << resp << '\n';

            auto it = upper_bound(a.begin()+n, a.end(), xs[i]);

            ll l = n, r = it-a.begin()-1;
            // cout << "l: " << l << ", r: " << r << ", it-a.begin(): " << it-a.begin() << '\n';
            resp += (r-l+1) * xs[i];
            // cout << "resp2: " << resp << '\n';
            ll soma = 0;
            while (l <= r)
            {
                if (l % 2 == 1) soma += a[l++];
                if (r % 2 == 0) soma += a[r--];
                l /= 2; r /= 2;
            }
            resp -= soma;
            // cout << "resp3: " << resp << '\n';
            
            l = it - a.begin();
            r = 2*n - 1;
            // cout << "l: " << l << ", r: " << r << '\n';
            resp -= (r-l+1) * xs[i];
            // cout << "resp4: " << resp << '\n';
            soma = 0;
            while (l <= r)
            {
                if (l % 2 == 1) soma += a[l++];
                if (r % 2 == 0) soma += a[r--];
                l /= 2; r /= 2;
            }
            resp += soma;
            // cout << "resp5: " << resp << '\n';

            cout << resp << ' ';
        }

        cout << '\n';
    } 

    return 0;
}