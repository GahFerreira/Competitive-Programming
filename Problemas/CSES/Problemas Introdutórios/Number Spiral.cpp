#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main()
{
    ios::sync_with_stdio(false); cin.tie(0);

    int t;
    cin >> t;
    while (t--)
    {
        ll y, x;
        cin >> y >> x;

        ll resp = 0;

        if (y == x) resp = y*y - (y-1);
        else
        {
            ll mx = max(y, x);

            if (mx & 1)
            {
                if (y < x) resp = mx * mx - (y-1);
                else resp = (mx-1) * (mx-1) + x;
            }

            else
            {
                if (y < x) resp = (mx-1) * (mx-1) + y;
                else resp = mx * mx - (x-1);
            }
        }

        cout << resp << '\n';
    }

    return 0;
}