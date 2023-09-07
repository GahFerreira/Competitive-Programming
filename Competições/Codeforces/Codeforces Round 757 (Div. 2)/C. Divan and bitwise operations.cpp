/*
    Nota: não tenho certeza exatamente como chegar a esse raciocínio - achei particularmente sinistro.

    Vamos considerar que já tenhamos a sequência 'a' em mãos.    
    Cada elemento pode ser representado por um inteiro de 31 bits (desconsideremos o sinal).

    Vamos olhar para a sequência, focando unicamente no i-ésimo bit de cada elemento.
    Vão possivelmente haver elementos em que esse i-ésimo bit é 1, nos demais será 0.

    Vamos separar esses elementos em dois grupos:
        1. No primeiro grupo, grupo A, colocaremos apenas os elementos que possuam 0 no i-ésimo bit.
        2. No segundo grupo, grupo B, colocaremos os que tiverem 1 no i-ésimo bit.

    Note que, se conseguirmos contar a quantidade de subconjuntos nos quais temos uma quantidade
    ÍMPAR de elementos com 1 no i-ésimo bit, sabemos exatamente o quanto esse bit vai contribuir na
    nossa resposta.
        - Seja 'x' a quantidade de subconjuntos com um número de elementos ÍMPAR com 1 no i-ésimo bit.
            - Suponha, por simplicidade, que quando vamos considerar a contribuição desse bit para
            a resposta, os demais bits sejam 0.
        - Esse bit 'i' contribuirá, sozinho, com '(1 << i) * x' para a nossa resposta.
            - Ou seja, para cada subconjunto, ele contribuirá '(1 << i)'.
                - Ex.: o 2-ésimo bit contribuirá 
                       (1 << 2) = 4 
                       para a resposta para cada subconjunto de elementos ÍMPAR com 1 no 2-ésimo bit.
                - Note que indexamos começando de 0, assim temos um 0-ésimo bit: (1 << 0) = 1.

    Assim, a nossa tarefa é determinar quantos subconjuntos possuem exatamente essa propriedade:
    uma quantidade ímpar de elementos com o i-ésimo bit igual a 1.

    Em relação aos elementos do grupo A, como eles tem o i-ésimo bit igual a 0, eles não mudam
    a paridade de elementos com o i-ésimo bit igual a 1.
    Portanto, podemos combinar 2ᴬ diferentes subconjuntos com qualquer subconjunto com número ÍMPAR
    de elementos com 1 no i-ésimo bit.

    Em relação aos elementos do grupo B, temos que escolher subconjuntos com um número ímpar de
    elementos.
        1. Se o grupo B for vazio, isso significa que não temos subconjuntos válidos e o i-ésimo bit
        contribuirá com 0 para a resposta.
            - Isso implica que ao fazer um OU-bit-a-bit entre todos os intervalos na entrada,
            o i-ésimo bit resulará em 0.
        2. Caso contrário, exatamente metade do total de subconjuntos de B terá um número ímpar de
        elementos.
            - A ideia é que, se isolarmos um elemento 'x' de B:
                - Para cada subconjunto de B com um número ímpar de elementos, temos um dual com
                um número par de elementos que inclui 'x'.
                - Para cada subconjunto de B com um número par de elementos, temos um dual com
                um número ímpar de elementos que inclui 'x'.
            - Portanto, para cada subconjunto ímpar temos um dual par e vice-versa.

    Dessa forma, temos exatamente 2ᴮ⁻¹ subconjuntos com um número ímpar de elementos com o i-ésimo
    bit igual a 1.

    Portanto, no total temos 2ᴬ * 2ᴮ⁻¹ subconjuntos com um número ímpar de elementos com o i-ésimo bit
    igual a 1.

    Entretanto, como dividimos n elementos em dois grupos, no caso, dividimos n em A e B:
        - n = |A| + |B|
    e portanto:
        - |A| + |B|-1 = n-1

    Assim, temos 2ⁿ⁻¹ subconjuntos com um número ímpar de elementos com o i-ésimo bit igual a 1.

    Dessa forma, tudo que precisamos descobrir é se existe pelo menos um elemento na sequência inicial
    que tenha o i-ésimo bit igual a 1.

    Se tirarmos o OU-bit-a-bit de todos os elementos da sequência, se pelo menos um deles tiver 1 no
    i-ésimo bit, o i-ésimo bit do resultado OU-bit-a-bit será 1.
        - Como é garantido que cada elemento da sequência vai aparecer em pelo menos um intervalo
        da entrada, tirar o OU-bit-a-bit de todos os intervalos da entrada é suficiente para saber
        se há pelo menos um elemento com 1 no i-ésimo bit.

    Portanto, se tirarmos o OU-bit-a-bit de todos os elementos da sequência, e guardarmos 
    o resultado em 'z', o resultado final que queremos descobrir se dará por:
        - 'z' * 2ⁿ⁻¹.

    Nota: não achei o símbolo de '|' superescrito para denotar |A| e |B| como potências.
          Então 2ᴬ deve ser entendido como 2 ^ |A|, e 2ᴮ⁻¹ como 2 ^ (|B| - 1).
*/

#include <bits/stdc++.h>

using namespace std;

#define for_(_i, _de, _ate) for(ll _i = _de; _i < (ll) _ate; ++_i)

#define INF 1'000'000'000

using ll = long long;

const int MOD = INF + 7;

int main()
{
    ios::sync_with_stdio(false); cin.tie(0);

    int t;
    cin >> t;
    while (t--)
    {
        int n, m;
        cin >> n >> m;
        int z = 0;
        for_(i, 0, m)
        {
            int l, r, x;
            cin >> l >> r >> x;
            z |= x;
        }

        --n;
        ll u = 2;

        // Podemos tirar o MOD antes, já que vamos tirar o MOD durante as multiplicações também.
        z %= MOD;

        // Exponenciação binária (exponenciação normal também funciona para este problema).
        while (n > 0)
        {
            if (n & 1) z = z * u % MOD;

            u *= u;
            if (u >= MOD) u %= MOD;

            n >>= 1;
        }

        cout << z << '\n';
    }

    return 0;
}