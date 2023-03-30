/*
Entrada: Um vetor de números inteiros quaisquer.
Saída: A maior soma entre todas subarray contíguas do vetor.
Compl.: O(n), n = |vetor|
*/

#include <bits/stdc++.h>

using namespace std;

int kadane(vector<int>& vetor)
{
    // Soma, melhor e i = 0, se puder subarray vazia.
    int soma = vetor[0], melhor = vetor[0];

    for (int i = 1; i < (int) vetor.size(); i++)
    {
        // Vai somando os números da array.
        // Ao encontrar um número cujo valor seja maior que a soma atual + ele,
        // escolhe ele sozinho para compor uma nova subarray de maior soma.
        soma = max(soma + vetor[i], vetor[i]);  

        if (soma > melhor) melhor = soma;
    }

    return melhor;
}