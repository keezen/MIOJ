/*
- 高弗雷勋爵

序号：#113
难度：有挑战
时间限制：1000ms
内存限制：10M

描述
黑暗女王希尔瓦娜斯将高弗雷复活为被遗忘者的一员。这个时候的高弗雷，
已经完全没有生前的样子，看起来阴险又狡诈，言语不再有任何礼节性的
修饰，时常将恶毒的语言挂在嘴上，谈及自己的过去，满满的只有怨恨。
高弗雷当然不愿意臣服于希尔瓦娜斯，但是为了达成毫无察觉的背叛，他
需要证明自己的“忠诚”——前去摧毁联盟第七军团的据点，等待他的奖励
不出意外是一台品罗小怪兽料理机。

第七军团的据点有数不清的敌人，高弗雷拿着一把附魔火枪，射出的子弹
会在敌人间跳跃，一发子弹就能对所有敌人造成 2 点伤害，如果该子弹
导致了任意敌人死亡（即血量小于等于 0），该子弹还会再次对所有敌人
造成2点伤害，直到没有新的敌人死亡为止。

那么，高弗雷需要打出几颗子弹才能消灭所有敌人呢？

输入
输入是每个敌人的血量，用空格分开，回车结束。0<敌人的数量<=10000; 
0<敌人的血量<=10^9

输出
输出是一个数字，是高弗雷最少需要打出的子弹的个数

输入样例
1 12 3 6 10

输出样例
2
*/

# include <iostream>
# include <cstdlib>
# include <fstream>
# include <sstream>
# include <vector>
using namespace std;


ifstream myfile("a.txt");


template <typename T> void PrintVec(vector<T> &data, char sep = ' ', char eol = '\n')
{
    for (int i = 0; i < data.size() - 1; i++)
        cout << data[i] << sep;
    cout << data.back() << eol;
}


int MinBullet(vector<int> &data)
{
    // minimum number of bullets to kill all enemies

    if (data.size() <= 0)
        return 0;

    sort(data.begin(), data.end());

    // compute min bullets
    int res = 0;
    const int step = 2;
    int thresh = 0;
    int i = 0;
    while (i < data.size())
    {
        // threshold lower than current item, shoot
        if (thresh < data[i])
        {
            int n = (data[i] - thresh - 1) / step + 1;
            res += n;
            thresh += step * n;
        }
        else // threshold higher than current, dead
        {
            while (i < data.size() && thresh >= data[i])  // clear dead
                i++;
            thresh += step;  // continue hurt
        }
    }

    return res;
}


int main(int argc, char *argv[])
{
    string line;
    int res;

    // input case
    while (getline(myfile, line))
    {
        stringstream ss(line);
        vector<int> data;
        int x;
        while (ss >> x)
            data.push_back(x);

        cout << line << endl;

        // result
        res = MinBullet(data);
        cout << res << endl;
    }

    return 0;
}