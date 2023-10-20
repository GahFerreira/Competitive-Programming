#include <bits/stdc++.h>

using namespace std;

#define for_(_i, _de, _ate) for(int _i = _de; _i < (int) _ate; ++_i)

int main()
{
    ios::sync_with_stdio(false); cin.tie(0);

    int n, k, e, esq, dir;
    cin >> n >> k >> e;

    esq = e;
    dir = n - (k+e);

    bool csg[2][esq+1][dir+1];
    for_(i, 0, 2)
        for_(i_esq, 0, esq+1)
            for_(i_dir, 0, dir+1)
                csg[i][i_esq][i_dir] = false;
    csg[0][0][0] = true;

    bool pecas[n+1];
    for_(i, 1, n+1) pecas[i] = true;
    pecas[0] = pecas[k] = false;

    int mx = 0;
    for_(i, 1, max(esq, dir)+1)
    {
        for_(i_a, 0, esq+1)
        {
            for_(i_b, 0, dir+1)
            {
                csg[i&1][i_a][i_b] = csg[(i+1)&1][i_a][i_b] ||
                                     (!pecas[i] ? false : (
                                        (!(i <= i_a) ? false : csg[(i+1)&1][i_a-i][i_b]) ||
                                        (!(i <= i_b) ? false : csg[(i+1)&1][i_a][i_b-i]))
                                     );

                if (csg[i&1][i_a][i_b]) mx = max(mx, i_a+i_b);
            }
        }
    }

    cout << n-(k+mx) << '\n';

    return 0;
}