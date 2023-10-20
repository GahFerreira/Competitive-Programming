#include <bits/stdc++.h>

using namespace std;

#define for_(_i, _de, _ate) for(int _i = _de; _i < (int) _ate; ++_i)

typedef long long ll;

#define MAXN 200'010
#define LGMAXN 20

ll chefe[MAXN][LGMAXN];

int main()
{
    ll n, q;
    cin >> n >> q;
    for_(at, 0 +2, n-1 +2)
    {
        cin >> chefe[at][0];
    }
    for_(i, 0, LGMAXN) chefe[0][i] = 0;
    for_(i, 0, LGMAXN) chefe[1][i] = 0;

    for_(i, 1, LGMAXN)
    {
        for_(at, 0 +2, n-1 +2)
        {
            chefe[ at ][i] = chefe[ chefe[at][i-1] ][i-1];
        }
    }

    ll funcionario_at, niveis_acima;
    for_(iq, 0, q)
    {
        cin >> funcionario_at >> niveis_acima;

        for(int cand = (1 << LGMAXN); cand >= 1; cand >>= 1)
        {
            if (cand & niveis_acima)
            {
                funcionario_at = chefe[funcionario_at][(ll) log2(cand)];
            }
        }

        if (funcionario_at == 0) --funcionario_at;
        cout << funcionario_at << '\n';
    }

    return 0;
}