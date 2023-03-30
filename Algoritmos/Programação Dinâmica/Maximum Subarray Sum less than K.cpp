/*
Entrada: Um vetor de inteiros, um inteiro k.
Saída: A maior soma de uma subarray de vetor que seja menor ou igual a k.
Compl.: (n log(n))
*/

#include <bits/stdc++.h>
using namespace std;

#define INF 1000000000

/*
Mantém uma soma a cada passo do vetor e adiciona ela a um set.
A cada passo, procura no set um valor tal que: p = soma - valor <= k.
Para que 'p' seja o maior valor possível, queremos 'valor': valor >= soma-k.
Manipulando temos: k >= soma-valor. 
Portanto, queremos o menor valor para que isso seja verdadeiro.
*/
int max_subarray_sum_less_equal_k(vector<int>& vetor, int k)
{
    // Se valer subarray vazia, iniciar com 0.
    int melhor = -INF;

    set<int> s; // Somas cumulativas
    s.insert(0);

    for (int i = 0, soma = 0; i < (int) vetor.size(); i++)
    {
        soma += vetor[i];

        // `*v` é o menor valor >= soma-k.
        auto v = lower_bound(s.begin(), s.end(), soma - k);

        if (v != s.end())
        {
            if (soma - *v > melhor)
            {
                melhor = soma - *v;

                if (melhor == k) return k; // Otimização
            }
        }

        s.insert(soma);
    }

    return melhor;
}