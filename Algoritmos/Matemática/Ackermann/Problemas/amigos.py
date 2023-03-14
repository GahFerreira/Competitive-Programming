# beecrowd.com.br/judge/pt/problems/view/1280

def fun(M, N):
   return (N + 1)   if M == 0 else (
          (N + 2)   if M == 1 else (
          (2*N + 3) if M == 2 else (
          (8*(2**N - 1) + 5) if M == 3 else (
          fun(M-1, 1) if N == 0 else fun(M-1, fun(M, N-1))))))

num = int(input())

for i in range(0, num):
    a, b = [int(n) for n in input().split()]

    print(fun (a, b))
