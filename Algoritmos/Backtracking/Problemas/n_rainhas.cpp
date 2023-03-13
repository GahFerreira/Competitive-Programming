// leetcode.com/problems/n-queens/

#include <bits/stdc++.h>
using namespace std;

class Solution 
{
public:
    vector<vector<string>> solveNQueens(int n) 
    {
        coluna.resize(n, false);
        diag_prin.resize(n+n-1, false);
        diag_sec.resize(n+n-1, false);

        backtracking(0, n);

        return resp;
    }   

private:
    vector<vector<string>> resp;
    vector<string> tentativa;
    vector<bool> coluna, diag_prin, diag_sec;

    // A ideia é colocar uma rainha em cada linha na iteração.
    // Para colocar a rainha, checa se aquela casa é válida.
    // Se for, marca o tabuleiro de forma a não deixar uma nova rainha numa casa inválida.
    void backtracking(int lin_at, int n)
    {
        if (lin_at == n)
        {
            resp.push_back(tentativa);
        }

        else
        {
            for (int col_at = 0; col_at < n; col_at++)
            {                  
                if (coluna[col_at] or 
                    // Essas funções nos colchetes permitem identificar as diagonais.
                    diag_prin[col_at + lin_at] or 
                    diag_sec[col_at - lin_at + n-1]) continue;

                coluna[col_at] = true;
                diag_prin[col_at + lin_at] = true;
                diag_sec[col_at - lin_at + n-1] = true;

                string representao_linha(n, '.');
                representao_linha[col_at] = 'Q';
                tentativa.push_back(representao_linha);

                backtracking(lin_at+1, n);

                tentativa.pop_back();
                coluna[col_at] = false;
                diag_prin[col_at + lin_at] = false;
                diag_sec[col_at - lin_at + n-1] = false;
            }
        }
    }
};

/*int main()
{
    int n, soma = 0;
    cin >> n;

    Solution s;
    auto sols = s.solveNQueens(n);
    for (auto& sol : sols)
    {
        for (auto& s : sol)
        {
            cout << s << '\n';
        }

        soma++;

        cout << '\n';
    }

    cout << "Soma: " << soma << '\n';
}*/