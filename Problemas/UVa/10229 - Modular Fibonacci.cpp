// onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1170

/*
    Exponenciação binária em cima da matriz que representa Fibonacci.

    Matriz de Fib [MFib]:
      [ 1 1 ]
      [ 1 0 ]
    A primeira linha de MFib representa que a primeira linha da resposta será a soma de:
        1x o valor da 1ª linha de MIni + 1x o valor da 2ª linha de MIni.

    Matriz de Início [MIni] (no código usamos a segunda coluna, mas ela não pode ser ignorada).
      [ 1 ] -> Fib(1)
      [ 0 ] -> Fib(0)

    A ideia é que MFib * MIni avança uma computação do cálculo de Fib(n).

    Por exemplo:
      MFib * MIni = [ 2 ] -> Fib(2)
                    [ 1 ] -> Fib(1)

    E assim, MFibⁿ * MIni = [ Fib(n+1) ]
                            [ Fib(n)   ]
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
    ll mat[2][2] = {
        {0, 0},
        {0, 0}
    };
};

Matriz mat_mul(Matriz a, Matriz b, const ll MOD)
{
    Matriz ret;

    for_(i_lin, 0, 2)
    {
        for_(i_col, 0, 2)
        {
            for_(elem, 0, 2)
            {
                ret.mat[i_lin][i_col] += ((a.mat[i_lin][elem]%MOD) * (b.mat[elem][i_col]%MOD)) % MOD;
                ret.mat[i_lin][i_col] %= MOD;
            }
        }
    }

    return ret;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(0);

    int n, m;
    while (cin >> n >> m)
    {
        const ll MOD = 1LL << m;

        Matriz at, resp;

        at.mat[0][0] = 1;
        at.mat[0][1] = 1;
        at.mat[1][0] = 1;
        at.mat[1][1] = 0;

        resp.mat[0][0] = 1;
        resp.mat[1][1] = 1;

        while (n)
        {
            if (n&1)
            {
                resp = mat_mul(resp, at, MOD);
            }

            at = mat_mul(at, at, MOD);

            n >>= 1;
        }

        cout << resp.mat[1][0] << '\n';
    }

    return 0;
}