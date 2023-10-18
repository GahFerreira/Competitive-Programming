/*
    onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2629

    Ideia:
        [Fib(i-1)%n, Fib(i)%n] repete depois de um tempo.
        Sabendo o tamanho do ciclo de repetição, conseguimos calcular o fib(a^b) % n.

        Até o início do ciclo, temos 'ini' iterações de fib.
        Depois, descobrimos o tamanho do ciclo: 'tam'.

        O tamanho do ciclo é no máximo n*n, pois há somente n*n diferentes pares possíveis
        para [Fib(i-1)%n, Fib(i)%n].

        Assim, '(a^b - ini) % tam' é o valor a ser exponenciado pela matriz base para encontrarmos
        o Fib(a^b).

        Seja 'r' = '(a^b - ini) % tam'.
        Manipulando:
        'r + ini' = '(a^b) % tam'

        Portanto, exponenciando a matriz base de Fib a 'r+ini' chegamos na resposta.

        Usamos exponenciação binária para descobrir 'r+ini' e também para descobrirmos 'base'^(r+ini)'.
*/

#include <bits/stdc++.h>

using namespace std;

#define for_(_i, _de, _ate) for(ull _i = _de; _i < (ull) _ate; ++_i)

#define INF 1'000'000'000 // Max int: 2'147'483'647 & Max long long: 9'223'372'036'854'775'807

using ull = unsigned long long;

struct Matriz
{
    ull mat[2][2] =
    {
        {0, 0},
        {0, 0}
    };
};

Matriz mul_mat(Matriz a, Matriz b, ull MOD)
{
    Matriz ret;
    for_(i, 0, 2)
        for_(j, 0, 2)
            for_(k, 0, 2)
            {
                ret.mat[i][j] += ((a.mat[i][k]%MOD) * (b.mat[k][j]%MOD))%MOD;
                ret.mat[i][j] %= MOD;
            }

    return ret;
}

Matriz exp_mat(Matriz a, ull p, ull MOD)
{
    Matriz ret;
    for_(i, 0, 2)
        ret.mat[i][i] = 1;

    while (p)
    {
        if (p&1) ret = mul_mat(ret, a, MOD);
        a = mul_mat(a, a, MOD);
        p >>= 1;
    }

    return ret;
}

ull exp_bin(ull a, ull p, ull MOD)
{
    ull ret = 1;

    a %= MOD;

    while (p)
    {
        if (p&1) ret = ret * a % MOD;
        a = a * a % MOD;
        p >>= 1;
    }

    return ret;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(0);

    int t;
    cin >> t;
    while (t--)
    {
        ull a, b, n;
        cin >> a >> b >> n;

        set<tuple<ull, ull, ull>> s;
        ull prev = 0, at = 1, i_at = 1;
        s.insert({prev, at, i_at});

        ull tam_ciclo;

        while(true)
        {
            swap(prev, at);
            at = (at+prev)%n;
            ++i_at;
            
            auto it = s.lower_bound({prev, at, 0});

            if (it != s.end())
            {
                auto [_prev, _at, _i_at] = *it;

                if (_prev == prev and _at == at)
                {
                    tam_ciclo = i_at - _i_at;
                    break;
                }
            }

            s.insert({prev, at, i_at});
        }

        Matriz base;
        base.mat[0][1] = 1;
        base.mat[1][0] = 1;
        base.mat[1][1] = 1;

        Matriz fib_ini;
        fib_ini.mat[1][0] = 1;

        ull r_mais_ini = exp_bin(a, b, tam_ciclo);

        base = exp_mat(base, r_mais_ini, n);
        
        Matriz resp = mul_mat(fib_ini, base, n);

        // cout << "Base:\n";
        // cout << base.mat[0][0] << ' ';
        // cout << base.mat[0][1] << '\n';
        // cout << base.mat[1][0] << ' ';
        // cout << base.mat[1][1] << '\n';
        // cout << '\n';

        // cout << "Resp:\n";
        // cout << resp.mat[0][0] << ' ';
        // cout << resp.mat[0][1] << '\n';
        // cout << resp.mat[1][0] << '\n';
        cout << resp.mat[1][1] << '\n';
        // cout << '\n';
    }

    return 0;
}