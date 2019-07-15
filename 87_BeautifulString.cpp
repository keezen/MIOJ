/*
- 美丽字符串

序号：#87
难度：困难
时间限制：1000ms
内存限制：10M

描述
定义一个美丽字符串，对于字符串S，S中只包含小写的a-z字符，存在2条规则： 
规则1：S中每个字符出现的次数一样，如abc，每个字符出现1次，aabbcc，
每个字符出现2次 
规则2：添加或删除S中的一个字符后，使得S中每个字符出现的次数一样，
如abca，删除一个字符a，则变为abc后每个字符出现1次 又例如aabcbbcc,
添加一个字符a，则变为aabcbbcca，每个字符出现3次 
对于字符串S，若满足规则1，2中任意一条规则，则称为美丽的字符串

输入
一个字符串S，只包含a-z的小写字符

输出
判断该字符串是否为美丽的字符串，若是则输出YES，若不是则输出NO

输入样例
abc
aabbccc
aaccbd

输出样例
YES
YES
NO
*/

# include <iostream>
# include <cstdlib>
# include <fstream>
# include <sstream>
# include <vector>
# include <cmath>
using namespace std;


ifstream myfile("a.txt");


template <typename T> void PrintVec(vector<T> &data, char sep = ' ', char eol = '\n')
{
    for (int i = 0; i < data.size() - 1; i++)
        cout << data[i] << sep;
    cout << data.back() << eol;
}


string BeautifulString(string s)
{
    // whether string is beautiful

    if (s.size() <= 0)
        return "NO";

    bool res = false;
    vector<int> freq(26, 0);
    int i;

    // count frequency
    for (i = 0; i < s.size(); i++)
        freq[s[i] - 'a']++;

    // average frequency
    int sum = 0, avg, num = 0;
    for (i = 0; i < 26; i++)
        if (freq[i] > 0)
        {
            sum += freq[i]; num++;
        }

    avg = sum / num;
    
    if (avg * num != sum && avg * num + 1 != sum && (avg + 1) * num - 1 != sum)
        return "NO";

    if ((avg + 1) * num - 1 == sum)
        avg++;

    // check beauty
    int abs_error_sum = 0;
    for (i = 0; i < 26; i++)
        if (freq[i] > 0)
            abs_error_sum += abs(freq[i] - avg);

    if (abs_error_sum > 1)
        return "NO";

    return "YES";
}


int main(int argc, char *argv[])
{
    string line;
    string res;

    // input case
    while (getline(myfile, line))
    {
        cout << line << endl;

        // result
        res = BeautifulString(line);
        cout << res << endl;
    }

    return 0;
}