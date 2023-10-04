// onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1596

/*
    A ideia é que aⁿ+bⁿ pode ser encontrada como uma recorrência linear.

    Manipula-se a fórmula base aⁿ+bⁿ:
        (aⁿ+bⁿ) * (a+b) = aⁿ⁺¹ + aⁿb + abⁿ + bⁿ⁺¹ = aⁿ⁺¹ + bⁿ⁺¹ + aⁿb + abⁿ // Partimos daqui.

    Assim:
        (aⁿ⁻¹+bⁿ⁻¹) * (a+b) = aⁿ + aⁿ⁻¹b + abⁿ⁻¹ + bⁿ = aⁿ + bⁿ + aⁿ⁻¹b + abⁿ⁻¹

    E então, precisamos dar um jeito de tirar 'aⁿ⁻¹b + abⁿ⁻¹':
        (aⁿ⁻¹b + abⁿ⁻¹) / (ab) = aⁿ⁻² + bⁿ⁻²
    
    Ou seja:
        (aⁿ⁻² + bⁿ⁻²) * (ab) = (aⁿ⁻¹b + abⁿ⁻¹)

    Assim:
        aⁿ+bⁿ = (aⁿ⁻¹+bⁿ⁻¹) * (a+b) - (aⁿ⁻² + bⁿ⁻²) * (ab)
    
    Ou como recorrência:
        fⁿ = fⁿ⁻¹ * (a+b) - fⁿ⁻² * (ab)
        
    Como p = (a+b), q = (ab), conseguimos montar a matriz da recorrência linear:
        fⁿ = fⁿ⁻¹ * p + fⁿ⁻² * (-q)

        Base:
        [ p -q ]
        [ 1  0 ]

        Início:
        [ p ] , ou seja a¹+b¹ que é f¹
        [ 2 ] , ou seja a⁰+b⁰ que é f⁰

    E então, Baseⁿ * Início nos dá
        [ fⁿ⁺¹ ]
        [ fⁿ   ] , ou seja, o que queremos.

    Nota:
        - A manipulação da fórmula é bem artificial (me parece tentativa e erro).
        - Se você não entender porque isso funciona, é só porque multiplicar matrizes
        te dá na mão somas de vários termos da recorrência de uma só vez.
            - Tente fazer casos de teste pequenos na mão a partir dessa matriz e ver
            como funciona.
*/

#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#define watch(x) cerr << (#x) << " is " << (x) << endl;
#else
#define watch(x)
#endif

#define for_(_i, _de, _ate) for(ll _i = _de; _i < (ll) _ate; ++_i)

using ll = long long;

struct Matriz
{
    ll r, c;
    vector<vector<ll>> mat;

    Matriz(ll r_, ll c_)
    {
        r = r_; c = c_;
        mat.resize(r_, vector<ll>(c_, 0)); // Inicia zerada.
    }
};

Matriz mul_mat(const Matriz& a, const Matriz& b)
{
    Matriz ret(a.r, b.c);

    for_(i_lin, 0, a.r)
    {
        for_(i_col, 0, b.c)
        {
            for_(elem, 0, a.c)
            {
                ret.mat[i_lin][i_col] += a.mat[i_lin][elem] * b.mat[elem][i_col];
            }
        }
    }

    return ret;
}

Matriz exp_mat(Matriz a, ll p) // a^p
{
    Matriz ret(a.r, a.c);
    for_(i, 0, a.r) // Tem que ser quadrada.
        ret.mat[i][i] = 1;

    while(p)
    {
        if (p&1) ret = mul_mat(ret, a);

        a = mul_mat(a, a);
        p >>= 1;
    }

    return ret;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(0);

    ll p, q, n;
    while (cin >> p >> q >> n)
    {
        Matriz base(2, 2);
        base.mat[0][0] = p;
        base.mat[0][1] = -q;
        base.mat[1][0] = 1;
        base.mat[1][1] = 0;

        base = exp_mat(base, n);

        Matriz resp(2, 1);
        resp.mat[0][0] = p;
        resp.mat[1][0] = 2;

        resp = mul_mat(base, resp);

        cout << resp.mat[1][0] << '\n';
    }

    return 0;
}