/*
Obj.: Calcular a função Ack:
        A(m, n) = {  n+1               se m = 0
                     A(m-1, 1)         se m > 0 e n = 0
                     A(m-1, A(m, n-1)) se m > 0 e n > 0
                  }
Compl.: O(1)
Restr.: Menores valores de N para `fun` estourar ull:
        M = 0, N = 2^64 -1
        M = 1, N = 2^64 -2
        M = 2, N = 2^63 -1
        M = 3, N = 62
        M = 4, N = 2
        M = 5, N = 1 (estoura recursão em Python)
        M >= 6, N = 0 (estoura recursão em Python)
*/

#include <bits/stdc++.h>
using namespace std;

unsigned long long int fun(int M, int N)
{
    if (M == 0) return N + 1;
    else if (M == 1) return N + 2;
    else if (M == 2) return 2*N + 3;
    else if (M == 3) return 8 * (pow(2, N)-1) + 5;
    else if (N == 0) return fun (M-1, 1);
    else return fun(M-1, fun(M, N-1));
}