# include <iostream>
# include <cstdlib>
# include <fstream>
# include <sstream>
# include <vector>
# include <string>
# include <codecvt>
# include <algorithm>
using namespace std;


ifstream myfile("a.txt");


template <typename T> void PrintVec(vector<T> &data)
{
    for (int i = 0; i < data.size() - 1; i++)
        cout << data[i] << ',';
    cout << data.back() << endl;
}


string NumToChinese(string &num)
{
    string res;

    if (num.size() <= 0)
        return res;

    string seg_weight[] = {"个", "万", "亿"};
    string pos_weight[] = {"个", "拾", "佰", "仟"};
    string chinese_digits[] = {
        "零", "壹", "贰", "叁", "肆", "伍", "陆", "柒", "捌", "玖"};

    int num_seg = (num.size() - 1) / 4 + 1;
    int seg_size = 4;
    int i, j, last, index, digit;
    bool empty;

    // segment
    for (i = 0; i < num_seg; i++)
    {
        if (i > 0)
            res.append(seg_weight[i]);

        // position
        last = 0; empty = true;
        for (j = 0; j < seg_size; j++)
        {
            index = num.size() - 1 - (i * seg_size + j);
            if (index < 0)
                break;

            digit = num[index] - '0';

            if (digit > 0)  // not 0
            {
                empty = false;
                if (j > 0)
                    res.append(pos_weight[j]);
                res.append(chinese_digits[digit]);
            }
            else if (last > 0)  // 0, not duplicate
                res.append(chinese_digits[digit]);

            last = digit;
        }

        if (i > 0 && empty)  // segment empty
            res.erase(res.end() - 3, res.end());
    }

    if (res.empty())
        res.append("零");

    reverse(res.begin(), res.end());
    for (int i = 0; i < res.size(); i += 3)
        swap(res[i], res[i + 2]);

    res.append("元整");

    return res;
}


int main(int argc, char *argv[])
{
    string str;
    string res;

    // input case
    while (getline(myfile, str))
    {
        cout << str << endl;

        // result
        res = NumToChinese(str);
        cout << res << endl;
    }

    return 0;
}