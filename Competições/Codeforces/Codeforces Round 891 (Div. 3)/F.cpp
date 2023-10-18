#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

bool eq(ld a, ld b)
{
    return (fabsl(a-b) < 1e-9L);
}

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        map<ll, ll> mapa;
        for (int i = 0; i < n; ++i) 
        {
            int x;
            cin >> x;
            ++mapa[x];
        }
        int q;
        cin >> q;
        for (int i = 0; i < q; ++i)
        {
            ll b, c;
            cin >> b >> c;

            b = -b;
            
            ll delta = (b * b) - (4 * c);

            ll resp;
            
            if (delta < 0) resp = 0; // Sem raízes.

            else if (delta == 0) // Raízes iguais.
            {
                ld x = (-b + sqrtl((long double) delta)) / 2;

                if (eq(x, (ll)x)) resp = (mapa[x] * (mapa[x]-1)) / 2;
                else resp = 0;
            }

            else // Duas raízes distintas.
            {
                ld x1 = (-b + sqrtl((long double) delta)) / 2;
                ld x2 = (-b - sqrtl((long double) delta)) / 2;

                if (eq(x1, (ll)x1) and eq(x2, (ll)x2)) resp = mapa[x1] * mapa[x2];
                else resp = 0;
            }

            cout << resp << ' ';
        }
        
        cout << '\n';
    }

    return 0;
}