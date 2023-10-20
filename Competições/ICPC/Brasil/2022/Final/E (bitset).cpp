#include <bits/stdc++.h>

using namespace std;

#define for_(_i, _de, _ate) for(int _i = _de; _i < (int) _ate; ++_i)

typedef long long ll;

int esq, dir;
bitset<2*1001*1001> pd;

int idx(int i, int e, int d)
{
    return (i&1) * (esq+1) * (dir+1) + e * (dir+1) + d;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(0);

    int n, k, e;
    cin >> n >> k >> e;

    esq = e;
    dir = n - (k+e);

    pd.set(0);

    int mx = 0;
    for_(i, 1, max(esq, dir)+1)
    {
        for_(a, 0, esq+1)
        {
            for_(b, 0, dir+1)
            {
                pd[idx(i, a, b)] = pd[idx(i+1, a, b)] || 
                    (i == k ? false : (
                        (i > a ? 0 : pd[idx(i+1, a-i, b)]) ||
                        (i > b ? 0 : pd[idx(i+1, a, b-i)]))
                    );
            }
        }
    }

    int ultimo_i = max(esq, dir);
    for_(a, 0, esq+1)
    {
        for_(b, 0, dir+1)
        {
            if (pd[idx(ultimo_i, a, b)]) mx = max(mx, a+b);
        }
    }

    cout << n - (k+mx) << '\n';

    return 0;
}