/*
    A esperança deste problema pode ser resolvida se conseguirmos contar
    quantas vezes aparece um determinado valor de máximo ao jogarmos o dado
    'n' vezes em sequência.

    Tomando como ponto de partida n = 2 e m = 6.
        - Ou seja, um dado de 6 lados jogado 2 vezes.

    Conseguimos montar uma tabela que representa todas as possíveis possibilidades:
        - Cada posição xᵢⱼ da tabela representa o máximo entre os dois lançamentos,
        sendo 'i' o valor obtido no primeiro lançamento e 'j' o valor do segundo.

    + + 1 2 3 4 5 6 -> Valor obtido no primeiro lançamento.
    + + — — — — — —
    1 | 1 2 3 4 5 6
    2 | 2 2 3 4 5 6
    3 | 3 3 3 4 5 6
    4 | 4 4 4 4 5 6
    5 | 5 5 5 5 5 6
    6 | 6 6 6 6 6 6
    ↓
    Valor obtido no segundo lançamento.

    Note que o máximo é 1 apenas quando tiramos 1 em ambos os lançamentos.
    Note que o máximo é 2 apenas quando não tiramos um número maior que 2, e ambos não são 1.

    A observação de maior ajuda desse problema é que cada valor 'i' aparece como máximo
    'i² - (i-1)²' vezes.
        - Uma maneira de enxergar isso na tabela é notar que conseguimos formar como máximo
        valores até 'i' em um quadrado de tamanho 'i' x 'i' que começa de x₁₁.
        - Para obter exatamente a quantidade de 'i' retiramos desse quadrado citado um novo
        quadrado de tamanho 'i-1' x 'i-1' que também começa de x₁₁.

    Com essa observação, temos que cada valor 'i' (no exemplo, de 1 a 6), aparece
    'i² - (i-1)²' vezes.
        - Para simplificar, seja L = 'i² - (i-1)²'.
    
    Portanto, cada valor 'i' tem 'L / m²' de chance de acontecer.
    Logo, cada valor 'i' contribui para a esperança um total de 'i * (L / m²)'.

    Assim, resolvemos o problema para n = 2 e m = 6 !!

    Como já pode imaginar, essa forma de resolver para este exemplo pode ser generalizada para
    qualquer 'n', 'm'.
        - A ideia é a mesma da tabela, mas fica difícil de desenhar para m=3 e impraticável para m>3.
        
    Para um dado de 'm' lados, lançado 'n' vezes:
        - O máximo 'i' aparecerá 'iⁿ - iⁿ⁻¹' vezes.
        - Cada 'i' contribuirá 'i * (iⁿ - iⁿ⁻¹) / mⁿ'.
        - Por fim, basta somar a contribuição para cada 'i' e obtemos a resposta.

    Um possível problema ao desenvolver o algoritmo é lidarmos com número elevados a 'n'.
        - Em relação ao tempo elevar a 'n' ingenuamente é O(n).
            - Para isso, usamos exponenciação binária que é O(log(n)).
        - Se elevarmos cada termo individualmente a 'n', teremos overflow.
            - Calculamos '(i/m)ⁿ' que é equivalente a 'iⁿ / mⁿ', e guardamos em 'a[i]'.
                - Note que 'i/m' está no intervalo [0, 1].
                - Portanto, elevar isso a qualquer número positivo gerará um número
                ainda no intervalo [0, 1].
            - Assim, para calcular a esperança de 'i', fazemos 'i * (a[i] - a[i-1])'.
*/

#include <bits/stdc++.h>

using namespace std;

float exp(float a, int n)
{
    float u = a;
    float resp = 1;

    while (n > 0)
    {
        if (n & 1)
        {
            resp *= u;
        }

        u *= u;
        n >>= 1;
    }

    return resp;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(0);

    int n, m;
    cin >> m >> n;

    float lado[m+1];
    lado[0] = 0;
    for (int i = 1; i <= m; ++i)
    {
        lado[i] = exp((float) i / m, n);
    }

    float soma = 0;

    for (int i = 1; i <= m; ++i)
    {
        soma += i * (lado[i]-lado[i-1]);
    }

    cout << fixed << setprecision(4) << soma << '\n';

    return 0;
}