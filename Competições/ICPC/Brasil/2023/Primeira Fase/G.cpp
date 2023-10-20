/*
    O tema central desse problema é que uma capital só tem reino infinita
    se ela não é envelopada por outras capitais.

    Assim, podemos usar o algoritmo de casco convexo, e os pontos que fazem
    parte da resposta são as capitais de reino infinito.
    
    Atenção para INCLUIR pontos colineares!

    Nota: estranhamente, double/long double não passa no CF (TLE), mas passou no dia. ¯\_(ツ)_/¯
*/

#include <bits/stdc++.h>

using namespace std;

#define all(x) x.begin(), x.end()
#define for_(_i, _de, _ate) for(int _i = _de; _i < (int) _ate; ++_i)

typedef long long ll;
typedef long double ld;

// Código de Convex Hull do CPAlgorithms.
struct pt
{
    int x, y;
};

int orientation(pt a, pt b, pt c) 
{
    int v = a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y);
    if (v < 0) return -1;
    if (v > 0) return +1;
    return 0;
}

bool cw(pt a, pt b, pt c) 
{
    int o = orientation(a, b, c);
    return o <= 0;
}

bool collinear(pt a, pt b, pt c) 
{ 
    return orientation(a, b, c) == 0; 
}

void convex_hull(vector<pt>& a) 
{
    pt p0 = *min_element(a.begin(), a.end(), [](pt _a, pt _b) 
    {
        return make_pair(_a.y, _a.x) < make_pair(_b.y, _b.x);
    });

    sort(a.begin(), a.end(), [&p0](const pt& _a, const pt& _b) 
    {
        int o = orientation(p0, _a, _b);
        if (o == 0)
        {
            return (p0.x-_a.x)*(p0.x-_a.x) + (p0.y-_a.y)*(p0.y-_a.y)
                    < (p0.x-_b.x)*(p0.x-_b.x) + (p0.y-_b.y)*(p0.y-_b.y);

        }
        return o < 0;
    });

    int i = (int)a.size()-1;
    while (i >= 0 && collinear(p0, a[i], a.back())) i--;
    reverse(a.begin()+i+1, a.end());

    vector<pt> st;
    for (i = 0; i < (int)a.size(); i++) 
    {
        while (st.size() > 1 && !cw(st[st.size()-2], st.back(), a[i]))
        {
            st.pop_back();
        }

        st.push_back(a[i]);
    }

    a = st;
}

vector<pt> pontos;

int main()
{
    ios::sync_with_stdio(false); cin.tie(0);

    int n;
    cin >> n;
    map<pair<int, int>, int> mapa;
    for_(i, 0, n)
    {
        int x, y;
        cin >> x >> y;
        pontos.push_back({x, y});
        mapa[{pontos[i].x, pontos[i].y}] = i+1;
    }

    convex_hull(pontos);

    vector<int> resps;

    for_(i, 0, pontos.size())
    {
        resps.push_back(mapa[{pontos[i].x, pontos[i].y}]);
    }

    sort(all(resps));

    for_(i, 0, resps.size())
    {
        cout << resps[i] << ' ';
    }

    cout << '\n';

    return 0;
}