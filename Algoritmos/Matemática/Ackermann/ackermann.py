''' 
Obj.: Calcular a função Ack:
        A(m, n) = {  n+1               se m = 0
                     A(m-1, 1)         se m > 0 e n = 0
                     A(m-1, A(m, n-1)) se m > 0 e n > 0
                  }

Compl.: O(1)
'''

def fun(M, N):
   return (N + 1)   if M == 0 else (
          (N + 2)   if M == 1 else (
          (2*N + 3) if M == 2 else (
          (8*(2**N - 1) + 5) if M == 3 else (
          fun(M-1, 1) if N == 0 else fun(M-1, fun(M, N-1))))))