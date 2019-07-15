# include <iostream>
# include <cstdlib>
# include <fstream>
# include <sstream>
using namespace std;


string BigNumSubtract(string num1, string num2)
{
    if (num1.size() <= 0 || num2.size() <= 0 || num1.size() < num2.size())
        return string();

    string res(num1);
    int carry = 0, diff;
    int i = num1.size() - 1, j = num2.size() - 1;
    while (i >= 0)
    {
        diff = num1[i] - (j >= 0 ? num2[j] : '0') + carry;
        carry = 0;
        if (diff < 0)
        {
            diff += 10;
            carry = -1;
        }

        res[i] = diff + '0';

        i--;
        if (j >= 0)
            j--;
    }

    for (i = 0; i <= res.size() && res[i] == '0'; i++) ;

    return string(res.begin() + i, res.end());
}


int main(int argc, char *argv[])
{
    ifstream myfile("a.txt");
    string str, num1, num2;
    string res;

    // input
    while (myfile >> str)
    {
        str[str.find('-')] = ' ';
        stringstream ss(str);
        ss >> num1 >> num2;
        cout << num1 << endl;
        cout << num2 << endl;

        res = BigNumSubtract(num1, num2);
        cout << res << endl;
    }

    myfile.close();

    return 0;
}