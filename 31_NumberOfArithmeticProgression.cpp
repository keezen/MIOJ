# include <iostream>
# include <cstdlib>
# include <fstream>
# include <sstream>
using namespace std;


ifstream myfile("a.txt");


int NumArithmeticProg(int sum)
{
    // number of arithmetic progressions given common
    // difference 2 and sum
    if (sum < 2)
        return 1;

    int i, count;
    for (i = 1, count = 0; i * i <= sum; i++)
        if (sum % i == 0)
            count++;

    return count;
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
        res = NumArithmeticProg(n);
        cout << res << endl;
    }

    return 0;
}