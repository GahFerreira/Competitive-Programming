#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#define watch(x) cerr << (#x) << " is " << (x) << endl;
#else
#define watch(x)
#endif

#define for_(_i, _de, _ate) for(int _i = _de; _i < (int) _ate; ++_i)

#define ff first
#define ss second

#define all(x) x.begin(), x.end()

#define str_to_lower(s) transform(s.begin(), s.end(), s.begin(), ::tolower)
#define str_to_upper(s) transform(s.begin(), s.end(), s.begin(), ::toupper)

#define INF 1'000'000'000 // Max int: 2'147'483'647 & Max long long: 9'223'372'036'854'775'807

typedef unsigned long long ull;

const int dx[8] = {+1, +2, +2, +1, -1, -2, -2, -1}, 
          dy[8] = {-2, -1, +1, +2, +2, +1, -1, -2};

int main()
{
    ios::sync_with_stdio(false); cin.tie(0);

    int n;
    cin >> n;

    ull resp = 0;
    ull exceto;
    int nl, nc;

    for_(k, 0, n)
    {
        for_(il, 0, k)
            for_(ic, 0, k)
            {
                exceto = 1;

                for_(dir, 0, 8)
                {
                    nl = il + dy[dir];
                    nc = ic + dx[dir];
                    
                    if (!(nl < 0 or nl >= k or
                        nc < 0 or nc >= k)) ++exceto;
                }

                resp += k*k - 9;
            }
        
        cout << resp/2 << '\n';
    }

    return 0;
}