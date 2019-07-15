# include <iostream>
# include <cstdlib>
# include <fstream>
# include <sstream>
using namespace std;


ifstream myfile("a.txt");


unsigned int ReverseBit(unsigned int x)
{
    // swap left and right when they are different
    unsigned int left = (unsigned int) 1 << 31;
    unsigned int right = (unsigned int ) 1;

    for (; left > right; left >>= 1, right <<= 1)
        if (((x & left) && !(x & right)) || (!(x & left) && (x & right)))
        {
            x ^= left;
            x ^= right;
        }

    return x;
}


int main(int argc, char *argv[])
{
    string str;
    unsigned int x;
    unsigned int res;

    // input case
    while (getline(myfile, str))
    {
        stringstream ss(str);
        ss >> x;

        cout << x << endl;

        // result
        res = ReverseBit(x);
        cout << res << endl;
    }

    return 0;
}