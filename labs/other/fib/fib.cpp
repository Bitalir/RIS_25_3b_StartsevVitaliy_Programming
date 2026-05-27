#include <iostream>
using namespace std;

int fib(int n)
{
    if (n == 1)
        return 0;
    if (n == 2)
        return 1;
    return fib(n - 2) + fib(n - 1);
}

int main()
{
    int n;
    cout << "Enter the number of Fibonacci numbers: "; cin >> n;
    for (int i = 1; i <= n; i++)
        cout << fib(i) << ' ';

    return 0;
}
