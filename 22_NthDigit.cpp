# include <iostream>
# include <cstdlib>
# include <fstream>
# include <sstream>
# include <vector>
using namespace std;


ifstream myfile("a.txt");


template <typename T> void PrintVec(vector<T> &data)
{
    for (int i = 0; i < data.size() - 1; i++)
        cout << data[i] << ',';
    cout << data.back() << endl;
}


unsigned long long NthDigit_SequentialSearch(unsigned long long n)
{
    if (n == 0)
        return 0;

    // find k-th string, binary search
    unsigned long long k;
    for (k = 1; k * (k + 1) / 2 < n; k++) ;

    // remain
    unsigned long long r = n - k * (k - 1) / 2;
    r = (r - 1) % 16 + 1;
    if (r > 8)
        r = 18 - r;

    return r;    
}


unsigned long long NthDigit(unsigned long long n)
{
    if (n == 0)
        return 0;

    // find k-th string, binary search
    unsigned long long k;
    unsigned long long s = 1, e = n, limit = ((unsigned long long)1 << 32) - 1;
    if (n > limit) e = limit;
    while (s <= e)
    {
        k = (s + e) / 2;
        if (k * (k - 1) / 2 < n && n <= k * (k + 1) / 2)
            break;

        if (k * (k - 1) / 2 >= n)
            e = k - 1;
        else if (n > k * (k + 1) / 2)
            s = k + 1;
    }

    // remain
    unsigned long long r = n - k * (k - 1) / 2;
    r = (r - 1) % 16 + 1;
    if (r > 8) r = 18 - r;

    return r;    
}


int main(int argc, char *argv[])
{
    string str;
    unsigned long long n;
    unsigned long long res;

    // input case
    while (getline(myfile, str))
    {
        stringstream ss(str);
        ss >> n;

        cout << n << endl;

        // result
        res = NthDigit(n);
        cout << res << endl << endl;
    }

    return 0;
}