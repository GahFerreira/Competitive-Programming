/*
    Ideia: só precisamos testar até valores de p até 2*n-1.

    Isso porque f(2*n-1) é:
        (2*n-1) * 2n / 2 = n * (2*n-1)
    Ou seja, um número divisível por n.

    Os valores de p após esse número começam a repetir módulo n.

    2*n % n = 0
    2*n +1 % n = 1
    2*n +2 % n = 2
    2*n +3 % n = 3
    2*n +4 % n = 4
    ...

    Note que 2*n % n = 0 é uma repetição, pois 2*n -1 %n = 0 também.

    Isso porque f dos dois geram números divisíveis por n.
        1. f(2*n)    = 2*n * (2*n +1) / 2 = n * (2*n +1)
        2. f(2*n -1) = (2*n -1) * 2*n / 2 = n * (2*n -1)

        - Ambos %n são 0, já que ambos são múltiplos de n.

    Obs.: Uma pequena alteração no argumento de testar até 2*n (ao invés de 2*n -1)
          poderia facilitar o argumento, sendo equivalente.
*/

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll f(int x)
{
    return (ll) x * (x+1) / 2;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(0);

    int t;
    cin >> t;
    while (t--)
    {
        int n, x, p;
        cin >> n >> x >> p;

        bool csg = false;
        for (int i = 1; i <= min(2*n-1, p); ++i)
        {
            if ((x + f(i)) % n == 0) { csg = true; break; }
        }

        if (csg) cout << "yes\n";
        else cout << "no\n";
    }

    return 0;
}