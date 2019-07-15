/*
- 德州扑克

序号：#45
难度：困难
时间限制：1000ms
内存限制：10M

描述
德州扑克是风靡全球的一种扑克游戏。扑克有四种花色，分别为黑桃（S）、
红桃（H）、梅花（C）、方片（D）。每种花色有13张牌，从小到大分别为
2、3、4、5、6、7、8、9、10、J、Q、K、A。

考虑德州扑克中的如下三种牌形： 同花顺（Straight Flush）：同一花色，
并且连续的五张牌。 例如：{SK SQ SJ S10 S9} 对于连续的五张牌，
有一个特例，即 {A、2、3、4、5} 也算作连续的五张牌。但 {K、A、2、3、4}，
{Q、K、A、2、3}，{J、Q、K、A、2} 不算作连续的五张牌。

同花（Flush）：同一花色但不连续的五张牌。 例如：{H10 H7 H4 H3 H2}

顺子（Straight）：连续但不是同一花色的五张牌。 例如：{SA H2 D3 C4 D5}

这三种牌形的大小关系是：顺子 < 同花 < 同花顺。 现在，我们为了游戏的
趣味性，在扑克中加入了5张魔术牌（用M表示），你可以将每张魔术牌变成你想
要的任何一张牌。 你从牌堆里随机抽了五张牌，请你给出最大可能的牌形。如果
三种牌形都无法组成，请输出GG。

输入
一行字符串，表示使用空格分隔的五张牌，每张牌由花色与点数组成(或使用M
来表示魔术牌)。

输出
单组输入。 一行字符串，表示能够组成的最大牌形。 只有Flush、Straight、
Straight Flush、GG四种结果。

输入样例
H10 H7 H4 H3 H2
M SA H2 D3 C4
M M M M D4
S8 HJ DA H8 H5

输出样例
Flush
Straight
Straight Flush
GG
*/

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
    for (int i = 0; i < data.size() - 1; i++)
        cout << data[i] << ' ';
    cout << data.back() << endl;
}


bool IsFlush(vector<int> color)
{
    if (color.size() != 5)
        return false;

    int i, j, n = color.size();

    for (i = 0; i < n && color[i] == 0; i++) ;

    // all magic
    if (i == n)
        return true;

    for (j = i + 1; j < n; j++)
        if (color[j] != 0 && color[j] != color[i])
            return false;

    return true;
}


bool IsStraight(vector<int> point)
{
    if (point.size() != 5)
        return false;

    sort(point.begin(), point.end());

    bool straight = false, repeat = false;
    int n = point.size(), i, j;

    // first non-magic
    for (i = 0; i < n && point[i] == 0; i++) ;

    // all magic
    if (i == n)
        return true;

    // check repeat
    for (j = i; j < n - 1; j++)
        if (point[j] == point[j + 1])
            return false;
    
    // not all magic, not repeated

    return point.back() - point[i] + 1 <= n;
}


string TexasHoldem(vector<string> &data)
{
    if (data.size() != 5)
        return "GG";

    // convert string to index
    int n = data.size();
    char colors[5] = {'M', 'S', 'H', 'C', 'D'};
    string points[15] = {
        "", "1", "2", "3", "4", "5", "6", "7", "8", "9",
        "10", "J", "Q", "K", "A"};
    vector<int> color(n);
    vector<int> point(n);
    map<char, int> color2id;
    map<string, int> point2id;
    int i, j;
    string t;

    for (i = 0; i < 5; i++)
        color2id[colors[i]] = i;

    for (i = 0; i < 15; i++)
        point2id[points[i]] = i;

    for (i = 0; i < n; i++)
    {
        t = data[i];
        color[i] = color2id[t[0]];
        point[i] = point2id[t.substr(1)];
    }


    // flush and straight
    bool flush = IsFlush(color);
    bool straight = IsStraight(point);

    // convert 'A' to '1', check straight
    if (!straight)
    {
        for (i = 0; i < n; i++)
            if (point[i] == 14)
                point[i] = 1;
        straight = IsStraight(point);
    }

    if (straight && flush)
        return "Straight Flush";

    if (straight)
        return "Straight";

    if (flush)
        return "Flush";

    return "GG";
}


int main(int argc, char *argv[])
{
    string line;
    string x;
    string res;

    // input case
    while (getline(myfile, line))
    {
        stringstream ss(line);
        vector<string> data;
        while (ss >> x)
            data.push_back(x);

        PrintVec(data);

        // result
        res = TexasHoldem(data);
        cout << res << endl;
    }

    return 0;
}