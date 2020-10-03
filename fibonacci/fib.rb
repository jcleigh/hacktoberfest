def fib(x)
  if x < 2
    return x
  end
  return fib(x - 1) + fib(x - 2)
end

for i in 1..10
  puts fib(i)
end
