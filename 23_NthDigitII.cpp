# include <iostream>
# include <cstdlib>
# include <fstream>
# include <sstream>
# include <vector>
# include <climits>
using namespace std;


ifstream myfile("a.txt");


template <typename T> void PrintVec(vector<T> &data)
{
    for (int i = 0; i < data.size() - 1; i++)
        cout << data[i] << ',';
    cout << data.back() << endl;
}


int NumDigits(unsigned long long k)
{
    int count = 0;
    for (; k > 0; k /= 10)
        count++;
    return count;
}


int NthDigitII(unsigned long long n)
{
    if (n <= 0)
        return 0;

    // find k-th string where n-th character lies
    unsigned long long a = 1, s = 1, last_s = 0, last_a = 0;
    unsigned long long k;
    for (k = 1; k <= ULLONG_MAX && s < n; k++)
    {
        last_s = s; last_a = a;
        a += NumDigits(k + 1);
        s += a;
    }

    // find i-th number where r-th character lies
    unsigned long long r = n - last_s;
    unsigned long long i;
    s = 1, last_s = 0;
    for (i = 1; i <= k && s < r; i++)
    {
        last_s = s;
        s += NumDigits(i + 1);
    }

    // find l-th character in number i
    unsigned long long l = r - last_s;
    int num_digits = NumDigits(i), t = i;
    for (int j = 0; j < num_digits - l; j++, t /= 10) ;
    t = t % 10;

    return t;
}


int main(int argc, char *argv[])
{
    string str;
    unsigned long long n;
    int res;

    // input case
    while (getline(myfile, str))
    {
        stringstream ss(str);
        ss >> n;

        cout << n << endl;

        // result
        res = NthDigitII(n);
        cout << res << endl << endl;
    }

    return 0;
}