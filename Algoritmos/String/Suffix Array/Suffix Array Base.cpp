/*
Objetivo: obter todos os sufixos de uma string em ordem lexográfica.
Complexidade: O(n * log^2(n))

Resumo: 
    Dada uma string s, todos seus sufixos são univocamente identificados pelo índice em que começam. Estes são salvos no vetor 'sA'.
    No pré-processamento, adiciona-se o símbolo '$' ao final de s; este símbolo tem lexográfico -infinito e não altera nenhum sufixo.

    Inicialmente, 'sA' é ordenado a partir do primeiro caractere de cada sufixo.
    A cada índice é dada uma classe de equivalência (salva no vetor 'cE') baseado no valor lexográfico de seu caractere inicial.
    Dessa forma, conhecemos a classe de equivalência de todos os sufixos reduzidos a 1 de tamanho.

    Dobramos então, o tamanho dos sufixos (de tamanho 1 para 2).
    Para todos os sufixos atuais (intermediários), adicionamos o próximo caractere de 's' a eles.
    Considera-se 's' circular; então ao último sufixo, adiciona-se o primeiro caractere de 's'.

    A cada sufixo então são dadas duas classes de equivalência: uma para a primeira metade (p/ tamanho 2, o primeiro caractere) ...
    ... e uma para a segunda metade (p/ tamanho 2, o segundo caractere).
    Note que as classes de equivalências dadas aqui foram calculadas anteriormente, a da primeira metade está em cE[i] e a da segunda em cE[i+1].
    Ordenamos então os sufixos baseados nas classes de equivalência (primeiro comparamos a primera cE, pois se for menor, o sufixo será obrigatoriamente menor).
    Ex.: s = 'aba' -> 'aba$'. Para sufixo i = 0, atualmente 'ab'. Sabemos que a cE de 'a' é 1 e a de 'b' é 2, logo suas cEs são (1,2).
    Ex.: Para o sufixo i = 1, atualmente 'ba', sabemos que seu cE é (2,1). Logo, o primeiro é menor que o segundo.
    Ordena-se então esse vetor, e a cada índice é dada uma classe de equivalência (salva em 'cE') baseado no valor de seu par de cEs.
    Agora conhecemos a classe de equivalência de todos os sufixos reduzimos a 2 de tamanho.

    Dobra-se então e repete-se a última parte até que o tamanho dos sufixos seja pelo menos igual ao tamanho de 's'.
    Sabemos então a ordem lexográfica dos sufixos.

    Nota: é a primeira vez que descrevo um algoritmo com comentários. Essa descrição é mais focada em eu lembrar do funcionamento no futuro.
        Dessa forma, peço desculpas se for extensa demais ou não compreensível.
*/

#include <iostream> // cin, cout & endl
#include <algorithm> // sort()
#include <utility> // pair<>
#include <vector>
#include <string>

// #include <bits/stdc++.h> // Já inclui tudo

using namespace std;

// Cria e retorna a suffix array da string s
vector<int> gerar_suffix_array(string s)
{
    s+= "$";
    int tam_s = (int) s.size();
    vector<int> suffix_array(tam_s), classes_de_equivalencia(tam_s);

    // i_vetor_temp = 0
    {
        vector<pair<char, int>> p(tam_s);   // Possui a primeira letra de cada sufixo

        for (int i = 0; i < tam_s; i++) p[i] = {s[i], i};

        sort(p.begin(), p.end());

        classes_de_equivalencia[ p[0].second ] = 0;
        for (int i = 1; i < tam_s; i++)
        {
            if (p[i].first == p[i-1].first) classes_de_equivalencia[p[i].second] = classes_de_equivalencia[p[i-1].second];

            else classes_de_equivalencia[p[i].second] = classes_de_equivalencia[p[i-1].second] + 1;
        }

        for (int i = 0; i < tam_s; i++) suffix_array[i] = p[i].second;
    }
    
    int i_vetor_temp = 0;

    // i_vetor_temp -> i_vetor_temp+1

    // Antes de entrar no while meu i_vetor_temp é igual a 0
    // Se o tamanho dos sufixos já calculados (1 << i_vetor_temp) == (2 ^ i_vetor_temp) for igual ou maior que tam_s...
    // ... então já calculei todos os sufixos de tamanho pelo menos tam_s, que é suficiente para eu saber todos os sufixos de s
    // Eu entro no while se eu quiser tornar meu i_vetor_temp -> i_vetor_temp+1
    while ((1 << i_vetor_temp) < tam_s)
    {
        // 'p' possui as classes de equivalência de cada sufixo intermediário de s
        // e seu índice
        vector<pair<pair<int, int>, int>> p(tam_s);

        for (int i = 0; i < tam_s; i++) 
            p[i] = {{classes_de_equivalencia[i], classes_de_equivalencia[(i + (1 << i_vetor_temp))%tam_s]}, i};

        sort(p.begin(), p.end());

        classes_de_equivalencia[ p[0].second ] = 0;

        for (int i = 1; i < tam_s; i++)
        {
            if (p[i].first == p[i-1].first) classes_de_equivalencia[p[i].second] = classes_de_equivalencia[p[i-1].second];

            else classes_de_equivalencia[p[i].second] = classes_de_equivalencia[p[i-1].second] + 1;
        }

        // A atribuição para o suffix array pode ser feita antes ou depois de calcular as classes de equivalência
        for (int i = 0; i < tam_s; i++) suffix_array[i] = p[i].second;

        // Melhoria!
        // Se em uma iteração, a minha maior classe de equivalência for igual a tam_s - 1, ...
        // ... como as classes de equivalência se iniciam em 0, isso significa que todas são distintas.
        // Dessa forma, todos os meus sufixos intermediários já estão completamente ordenados!
        // Aumentar i_vetor_temp só ajuda a distinguir sufixos intermediários iguais, então posso apenas retornar suffix_array.
        if (classes_de_equivalencia[p[tam_s - 1].second] == tam_s - 1) break;

        i_vetor_temp++;
    }

    return suffix_array;
}

int main()
{
    string s;
    cin >> s;

    vector<int> suffix_array = gerar_suffix_array(s);

    for (int i = 0; i < (int) suffix_array.size(); i++) cout << suffix_array[i] << endl;

    return 0;
}