#include <iostream>
#include <vector>

using namespace std;

struct ArvoreSegmentos
{
    public:
    
    vector<int> arvore;
    int tamanho_vetor;
    int (*merge)(int, int);

    // 'operator[]' permite que acessemos nossa estrutura como um vetor 'a[i]' ao invés de 'a.arvore[i]'
    // 'size' é só por conveniência também 'a.size()' ao invés de 'a.arvore.size()'
    int& operator[] (unsigned indice) { return arvore[indice]; }
    unsigned size() { return arvore.size(); }

    // Note que precisa-se de uma função 'merge', que no nosso exemplo é por padrão o máximo
    ArvoreSegmentos(int vetor[], int tamanho_vetor, int (merge)(int, int) = [](int x, int y) { return max(x, y); })
    {
        this->tamanho_vetor = tamanho_vetor;
        this->merge = merge;

        // Inicializa arvore com o tamanho adequado (2 * tamanho_vetor). 'resize' > 'reserve', pois muda o .size().
        arvore.resize(2 * tamanho_vetor);

        // Copia o vetor para a segunda metade da árvore
        for(int i = 0; i < tamanho_vetor; i++)
        {
            arvore[i + tamanho_vetor] = vetor[i];
        }

        // Calcula os nós da árvore de intervalos de tamanho 2 ou mais 
        for(int i_arvore = tamanho_vetor - 1; i_arvore >= 1; i_arvore--)
        {
            arvore[i_arvore] = merge(arvore[2 * i_arvore], arvore[2 * i_arvore + 1]);
        }
    }

    void atualizar(int posicao, int valor)
    {
        int i_arvore = posicao + tamanho_vetor;
        arvore[i_arvore] = valor;

        // A ideia é que o pai de um nó é 'índice_nó / 2'. Então atualiza todos os pais, até o nó 1.
        while(i_arvore > 1)
        {
            i_arvore /= 2;
            arvore[i_arvore] = merge(arvore[2 * i_arvore], arvore[2 * i_arvore + 1]);
        }
    }

    // [inicio, final)
    int pesquisar(int inicio, int final, int resultado_base = 0)
    {
        inicio += tamanho_vetor;
        final += tamanho_vetor;

        int resultado = resultado_base;

        while (inicio < final)
        {
            // Magia
            if (inicio % 2 != 0) resultado = merge(resultado, arvore[inicio++]);
            if (final % 2 != 0) resultado = merge(resultado, arvore[--final]);

            inicio /= 2;
            final /= 2;
        }

        return resultado;
    }
};