// Obj.: Encontrar a subarray contígua de `vetor` com a maior soma menor ou igual a k.
// Compl.: O(n log(n))

#include <bits/stdc++.h>
using namespace std;

#define INF 1000000000

/*
Mantém uma soma a cada passo do vetor e adiciona ela a um set.
A cada passo, procura no set um valor tal que soma - valor_set = p <= k,
tal que p seja o maior valor possível.
*/
int maximum_subarray_sum_less_than_k(vector<int>& vetor, int k)
{
    // Se valer subarray vazia, iniciar com 0.
    int melhor = -INF;

    set<int> somas_cumulativas;
    somas_cumulativas.insert(0);

    for (int i = 0, soma = 0; i < (int) vetor.size(); i++)
    {
        soma += vetor[i];

        auto menor_valor_maior_que_soma_menos_k = 
            lower_bound(somas_cumulativas.begin(), somas_cumulativas.end(), soma - k);

        if (menor_valor_maior_que_soma_menos_k != somas_cumulativas.end())
        {
            if (soma - *menor_valor_maior_que_soma_menos_k > melhor)
            {
                melhor = soma - *menor_valor_maior_que_soma_menos_k;
            }
        }

        somas_cumulativas.insert(soma);
    }

    return melhor;
}