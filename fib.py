def fib(x):
    if x < 2:
        return x
    return fib(x - 1) + fib(x - 2)

for x in range(1, 11):
    print(fib(x))
