#include <bits/stdc++.h>

using namespace std;

#define for_(_i, _de, _ate) for(int _i = _de; _i < (int) _ate; ++_i)

int main()
{
    ios::sync_with_stdio(false); cin.tie(0);

    int t;
    cin >> t;
    while (t--)
    {

        int n, m;
        cin >> n >> m;
        vector<string> s(n);
        int V, I, K, A;
        V = I = K = A = 2*m;
        for_(i, 0, n) 
        {
            cin >> s[i];

            for_(j, 0, m)
            {
                if (s[i][j] == 'v') V = min(V, j);
            }
        }

        for_(i, 0, n)
        {
            for_(j, V+1, m)
            {
                if (s[i][j] == 'i') I = min(I, j);
            }
        }

        for_(i, 0, n)
        {
            for_(j, I+1, m)
            {
                if (s[i][j] == 'k') K = min(K, j);
            }
        }

        for_(i, 0, n)
        {
            for_(j, K+1, m)
            {
                if (s[i][j] == 'a') A = min(A, j);
            }
        }

        if (V < I and I < K and K < A and
            V < 2*m and I < 2*m and K < 2*m and A < 2*m) cout << "YES\n";
        else cout << "NO\n";
    }

    return 0;
}