import std.stdio;

int fib(int x) {
    if (x < 2) return x;
    return fib(x - 1) + fib(x - 2);
}
void main() {
    for(int x = 1; x <= 10; x++) {
        writeln(fib(x));
    }
}
