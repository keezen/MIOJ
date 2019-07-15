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


bool IsValidGap(int k, int m)
{
    if (k <= 0 || m <= 0)
        return false;

    int s = 0, e = k - 1, i, r;
    for (i = 2 * k; i > k; i--)
    {
        // select a fruit
        r = (m - 1) % i;
        if (s <= r && r <= e)
            return false;

        s = ((s - m) % i + i) % i;
        e = ((e - m) % i + i) % i;
    }

    return true;
}


int MinimalGap(int k)
{
    if (k <= 0)
        return 0;

    int m = k + 1;
    while (m <= INT_MAX)
    {
        if (IsValidGap(k, m))
            return m;

        if (m % (2 * k) == 0)
            m += (k + 1);
        else
            m++;
    }
    
    return 0;
}


int main(int argc, char *argv[])
{
    string str;
    int k;
    int res;

    // input case
    while (getline(myfile, str))
    {
        stringstream ss(str);
        ss >> k;

        cout << k << endl;

        // result
        res = MinimalGap(k);
        cout << res << endl;
    }

    return 0;
}