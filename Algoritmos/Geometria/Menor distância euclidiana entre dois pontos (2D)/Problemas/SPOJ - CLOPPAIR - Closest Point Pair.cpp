// Closest Point Pair
// spoj.com/problems/CLOPPAIR/

#include <bits/stdc++.h>

using namespace std;

#define ff first
#define ss second

#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()

#define str_to_lower(s) transform(s.begin(), s.end(), s.begin(), ::tolower)
#define str_to_upper(s) transform(s.begin(), s.end(), s.begin(), ::toupper)

#define for_(_i, _de, _ate) for(int _i = _de; _i < (int) _ate; ++_i)
#define INF 1000000000 // Max int: 2147483647 & Max long long: 9223372036854775807

typedef long long ll;
typedef long double ld;

#define X real()
#define Y imag()

typedef complex<ld> Ponto;

ld dist(const Ponto& p, const Ponto& q)
{
    return (sqrtl( (p.X-q.X)*(p.X-q.X) + (p.Y-q.Y)*(p.Y-q.Y) ));
}

int main()
{
    int n;
    cin >> n;
    vector<pair<Ponto, int>> a(n);
    for_(i, 0, n)
    {
        ld x, y;
        cin >> x >> y;
        a[i] = {{x, y}, i};
    }
    sort(all(a), [](pair<Ponto, int>& pp, pair<Ponto, int>& qq)
    {
        Ponto& p = pp.first, q = qq.first;
        return p.X < q.X;
    });

    multiset<Ponto, bool(*)(const Ponto&, const Ponto&)> m(
        [](const Ponto& p, const Ponto& q)
        {
            return p.Y < q.Y;
        }
    );
    map<pair<ld, ld>, int> mapa;

    ld mn = dist(a[0].first, a[1].first);
    int i_a = 0, i_b = 1;

    for_(i, 0, n)
    {
        mapa[{a[i].first.X, a[i].first.Y}] = a[i].second;

        for (auto it = m.lower_bound({0, a[i].first.Y-mn}); it != m.end() and !(it->Y > a[i].first.Y+mn);)
        {
            if (it->X < a[i].first.X - mn) it = m.erase(it);
            else
            {
                ld d = dist(a[i].first, *it);

                if (d < mn)
                {
                    mn = d;
                    i_a = mapa[{it->X, it->Y}];
                    i_b = a[i].second;
                }

                ++it;
            }
        }

        m.insert(a[i].first);
    }

    if (i_a > i_b) swap(i_a, i_b);

    printf("%d %d %.6Lf\n", i_a, i_b, mn);

    return 0;
}