# include <iostream>
# include <cstdlib>
# include <fstream>
# include <sstream>
# include <vector>
# include <string>
# include <map>
using namespace std;


ifstream myfile("a.txt");


template <typename T> void PrintVec(vector<T> &data)
{
    for (int i = 0; i < data.size(); i++)
        cout << data[i] << ' ';
    cout << endl;
}


bool IsShortString(string s, string l)
{
    if (s.size() <= 0 || l.size() <= 0 || s.size() > l.size())
        return false;

    // count characters in long string
    map<char, int> count;
    int i;
    char c;
    for (i = 0; i < l.size(); i++)
        if (count.find(l[i]) == count.end())
            count[l[i]] = 1;
        else
            count[l[i]] += 1;

    // check each character in short string
    for (i = 0; i < s.size(); i++)
        if (count.find(s[i]) == count.end() || count[s[i]] == 0)
            return false;
        else
            count[s[i]] -= 1;

    return true;
}


int main(int argc, char *argv[])
{
    string str;
    string s, l;
    bool res;

    // input case
    while (getline(myfile, str))
    {
        stringstream ss(str);
        ss >> s; ss >> l;

        cout << s << ' ' << l << endl;

        // result
        res = IsShortString(s, l);
        cout << (res ? "true" : "false") << endl;
    }

    return 0;
}