# include <iostream>
# include <cstdlib>
# include <fstream>
# include <sstream>
# include <vector>
# include <string>
using namespace std;


ifstream myfile("a.txt");


template <typename T> void PrintVec(vector<T> &data)
{
    for (int i = 0; i < data.size(); i++)
        cout << data[i] << ' ';
    cout << endl;
}


int Fibonacci(int n)
{
    if (n <= 1)
        return 1;

    int fib1 = 1, fib2 = 1;
    for (int i = 1; i < n; i++)
    {
        fib2 = fib1 + fib2;
        fib1 = fib2 - fib1;
    }

    return fib2;
}


int main(int argc, char *argv[])
{
    string str;
    int n;
    int res;

    // input case
    while (getline(myfile, str))
    {
        stringstream ss(str);
        ss >> n;

        cout << n << endl;

        // result
        res = Fibonacci(n);
        cout << res << endl;
    }

    return 0;
}