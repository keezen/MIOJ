# include <iostream>
# include <cstdlib>
# include <fstream>
# include <vector>
using namespace std;


template <typename T> void PrintVec(vector<T> data)
{
    for (int i = 0; i < data.size(); i++)
        cout << data[i] << ' ';
    cout << endl;
}


int FindUniqueNum(vector<int> data)
{
    if (data.size() <= 0)
        return -1;

    int res = 0;
    for (int i = 0; i < data.size(); i++)
        res ^= data[i];

    return res;
}


int main(int argc, char *argv[])
{
    ifstream myfile("a.txt");
    vector<int> data;
    int x;
    int res;

    // input
    while (myfile >> x)
        data.push_back(x);
    PrintVec(data);

    // result
    res = FindUniqueNum(data);
    cout << res << endl;

    myfile.close();

    return 0;
}