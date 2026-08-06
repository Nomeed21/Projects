#fibonacci sequence

n = 10
def fibonacciRecursion(n):
    if n == 0:
        return 0
    elif n == 1:
        return 1
    return fibonacciRecursion(n-1) + fibonacciRecursion(n-2)

def fibonacci(n):
    x = 0
    y = 1
    for i in range(n):
        if i == 0 or i == 1:
            print(i)
        z = x + y
        print(z)
        x = y
        y = z

fibonacci(10)


