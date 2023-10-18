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

    int tt;
    cin >> tt;
    while (tt--)
    {
        int n;
        cin >> n;
        vector<int> a(n), b(n);
        vector<pair<int, int>> p(n);
        for_(i, 0, n) cin >> a[i];
        for_(i, 0, n) cin >> b[i];

        for_(i, 0, n) p[i] = {a[i]-b[i], i};
        sort(all(p));
        reverse(all(p));
        int mx = p[0].first;

        vector<int> resp;
        for_(i, 0, p.size())
        {
            if (p[i].first < mx) break;
            resp.push_back(p[i].second);
        }
        sort(all(resp));
        cout << resp.size() << '\n';
        for_(i, 0, resp.size())
        {
            cout << resp[i]+1 << " ";
        }
        cout << '\n';
    }

    return 0;
}