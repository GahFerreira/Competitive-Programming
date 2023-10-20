#include <bits/stdc++.h>

using namespace std;

#define ff first
#define ss second

#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()

#define str_to_lower(s) transform(s.begin(), s.end(), s.begin(), ::tolower)
#define str_to_upper(s) transform(s.begin(), s.end(), s.begin(), ::toupper)

#define for_(_i, _de, _ate) for(int _i = _de; _i < (int) _ate; ++_i)
#define INF 100000L // Max int: 2147483647 & Max long long: 9223372036854775807

typedef long long ll;
typedef long double ld;

// const int dx[8] = {+1, +0, -1, +0, +1, +1, -1, -1}, 
//           dy[8] = {+0, +1, +0, -1, -1, +1, -1, +1};

#define X real()
#define Y imag()

typedef complex<ld> Ponto;

#define eps 0.000001L

bool opLess(ld a, ld b)
{
    return (b - a) > ( (fabsl(a) < fabsl(b) ? fabsl(b) : fabsl(a)) * eps);
}

bool opGreater(ld a, ld b)
{
    return (a - b) > ( (fabsl(a) < fabsl(b) ? fabsl(b) : fabsl(a)) * eps);
}

int main()
{
    int n;
    while (cin >> n and n != 0)
    {
        vector<Ponto> a(n);
        for_(i, 0, n)
        {
            ld x, y;
            cin >> x >> y;
            a[i] = {x, y};
        }
        sort(all(a), [](const Ponto& p, const Ponto& q)
        {
            return p.X < q.X;
        });

        ld d = 10000L;
        multiset<Ponto, bool(*)(const Ponto&, const Ponto&)> m(
        [](const Ponto& p, const Ponto& q)
        {
            return opLess(p.Y, q.Y);
        });

        for_(i, 0, n)
        {
            for (auto it = m.lower_bound({-INF, a[i].Y - d}); it != m.end() and !(opGreater(it->Y, a[i].Y + d)); )
            {
                if (opLess(it->X, a[i].X - d)) 
                {
                    it = m.erase(it);
                    continue;
                }

                auto cand = sqrtl( (a[i].X - it->X)*(a[i].X - it->X) + (a[i].Y - it->Y)*(a[i].Y - it->Y) );

                if (opLess(cand, d)) d = cand;

                ++it;
            }

            m.insert(a[i]);
        }

        if (!opLess(d, 10000L)) printf("INFINITY\n");
        else printf("%.4Lf\n", d);
    }

    return 0;
}