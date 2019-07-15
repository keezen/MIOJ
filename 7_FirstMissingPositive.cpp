# include <iostream>
# include <cstdlib>
# include <fstream>
# include <sstream>
# include <vector>
using namespace std;


ifstream myfile("a.txt");


template <typename T> void PrintVec(vector<T> &data)
{
    for (int i = 0; i < data.size(); i++)
        cout << data[i] << ' ';
    cout << endl;
}


int FirstMissingPositive_Complex(vector<int> &data)
{
    if (data.size() <= 0)
        return 0;

    int i, j, num;

    i = 0, j = data.size() - 1;
    while (i <= j)
    {
        num = data[i];
        if (num <= 0 || num - 1 > j)
            swap(data[i], data[j--]);
        else if (num == i + 1)
            i++;
        else if (data[num - 1] == num)
            swap(data[i], data[j--]);
        else
            swap(data[i], data[num - 1]);
    }

    return i + 1;
}


int FirstMissingPositive(vector<int> &data)
{
    if (data.size() <= 0)
        return 0;

    int i;

    for (i = 0; i < data.size(); i++)
        // put each number in the right place
        while (data[i] > 0 && data[i] <= data.size() && data[data[i] - 1] != data[i])
            swap(data[i], data[data[i] - 1]);

    // first place which is not right is missing
    for (i = 0; i < data.size(); i++)
        if (data[i] != i + 1)
            return i + 1;

    return data.size() + 1;
}


int main(int argc, char *argv[])
{
    string str;
    int x;
    int res;

    // input case
    while (getline(myfile, str))
    {
        // input array
        for (int i = 0; i < str.size(); i++)
            if (str[i] == ',')
                str[i] = ' ';

        stringstream ss(str);
        vector<int> data;
        while (ss >> x)
            data.push_back(x);

        // result
        res = FirstMissingPositive(data);
        cout << res << endl;
    }

    return 0;
}