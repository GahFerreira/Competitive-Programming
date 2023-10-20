#include <iostream>
#include <vector>

using namespace std;

template <class T>
struct ArvoreSegmentos
{
    public:
    
    vector<T> arvore;
    int tamanho_vetor;
    T (*merge)(T, T);

    T& operator[] (unsigned indice) { return arvore[indice]; }
    unsigned size() { return arvore.size(); }

    ArvoreSegmentos(T vetor[], int tamanho_vetor, T (merge)(T, T) = [](int x, int y) { return max(x, y); })
    {
        this->tamanho_vetor = tamanho_vetor;
        this->merge = merge;

        arvore.resize(2 * tamanho_vetor);

        for(int i = 0; i < tamanho_vetor; i++)
        {
            arvore[i + tamanho_vetor] = vetor[i];
        }

        for(int i_arvore = tamanho_vetor - 1; i_arvore >= 1; i_arvore--)
        {
            arvore[i_arvore] = merge(arvore[2 * i_arvore], arvore[2 * i_arvore + 1]);
        }
    }

    void atualizar(int posicao, T valor)
    {
        int i_arvore = posicao + tamanho_vetor;
        arvore[i_arvore] = valor;

        while(i_arvore > 1)
        {
            i_arvore /= 2;
            arvore[i_arvore] = merge(arvore[2 * i_arvore], arvore[2 * i_arvore + 1]);
        }
    }

    T pesquisar(int inicio, int final, T resultado_base = 0)
    {
        inicio += tamanho_vetor;
        final += tamanho_vetor;

        T resultado = resultado_base;

        while (inicio < final)
        {
            if (inicio %2 != 0) resultado = merge(resultado, arvore[inicio++]);
            if (final %2 != 0) resultado = merge(resultado, arvore[--final]);

            inicio /= 2;
            final /= 2;
        }

        return resultado;
    }
};