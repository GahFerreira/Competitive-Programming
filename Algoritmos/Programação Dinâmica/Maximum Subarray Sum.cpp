/*
Objetivo: encontrar a subarray contígua de `vetor` com a maior soma.
Compl.: O(n)
*/

#include <bits/stdc++.h>

using namespace std;

int maximumSubarraySum(vector<int>& vetor)
{
    // Se subarray não vazia, inicia com vetor[0] e começa o for do 1.
    int soma = 0, melhor = 0;

    for (int i = 0; i < (int) vetor.size(); i++)
    {
        // Vai somando os números da array.
        // Quando encontrar um número cujo valor seja maior que a soma atual + ele,
        // é melhor escolher ele sozinho para compor uma nova subarray de maior soma.
        soma = max(soma + vetor[i], vetor[i]);

        if (soma > melhor) melhor = soma;
    }

    return melhor;
}