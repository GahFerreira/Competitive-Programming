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
        int mx = -1;
        string s;
        cin >> s;
        reverse(all(s));

        for_(i, 0, s.size())
        {
            if (s[i] < '5') continue;

            mx = max(mx, i);

            for (i = i+1; i <= (int) s.size(); ++i)
            {
                if (i == (int) s.size())
                {
                    s += '1';
                    mx = max(mx, i-1);
                    break;
                }

                if (s[i] < '9')
                {
                    ++s[i--];
                    mx = max(mx, i);
                    break;
                }
            }
        }

        for (int i = mx; i >= 0; --i) s[i] = '0';

        reverse(all(s));

        cout << s << '\n';
    }

    return 0;
}