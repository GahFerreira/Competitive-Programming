/*
    Para checar a simetria, para cada posição 'i', se 'a[i] = x',
    chegamos se há exatamente 'x' valores > 'i' no vetor.

    Por exemplo, se na posição 0 tivermos 5 (ou seja 'a[0] = 5'),
    precisamos de ter exatamente 5 valores em 'a' maiores que 0 para a simetria valer.

    Se a simetria valer para todos os 'i', a cerca é simétrica.
*/

#include <bits/stdc++.h>

using namespace std;

#define all(x) x.begin(), x.end()

#define for_(_i, _de, _ate) for(int _i = _de; _i < (int) _ate; ++_i)

typedef long long ll;

int main()
{
    ios::sync_with_stdio(false); cin.tie(0);

    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        vector<int> a(n);
        for_(i, 0, n) 
        {
            cin >> a[i];
        }
        vector<int> b(a);
        reverse(all(b));
        bool csg = true;
        for_(i, 0, n)
        {
            auto it = upper_bound(all(b), i);
            if (n - (it - b.begin()) != a[i])
            {
                csg = false;
                break;
            }
                
        }
        if (csg) cout << "yes\n";
        else cout << "no\n";
    }

    return 0;
}