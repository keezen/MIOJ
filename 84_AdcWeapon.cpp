/*
- 论 ADC 如何出装

序号：#84
难度：有挑战
时间限制：1000ms
内存限制：10M

描述
每次打 ADC 时，都会纠结是出『暗影战斧』还是『破甲弓』，现在给出
护甲的计算公式、当前英雄等级、对方英雄护甲，你可以计算出买哪个装备
单次攻击伤害更高嘛?

首先，我们计算对方英雄的 护甲值： 护甲值 = 原始护甲值 - 护甲穿透。

然后，我们计算护甲可以提供的 伤害减免，伤害减免公式为： 伤害减免 = 
(护甲值) / (602 + 护甲值)。

英雄的 攻击力 为： 100 + 装备攻击

实际英雄受的伤害为： 攻击力 x (100% - 伤害减免)

装备属性如下：

暗影战斧 axe +85 物理攻击 唯一被动（切割）：增加（100+英雄等级*10）点
护甲穿透

破甲弓 bow +80 物理攻击 唯一被动：增加 45% 护甲穿透（实际穿透的护甲值为 
原始护甲 x ( 1 - 45%) ）

输入
一行数字，每行两个数（空格隔开）：x y（己方英雄等级 对方英雄护甲）。

输出
如果『暗影战斧』伤害更高，那么输出 axe，如果『破甲弓』更优秀，那么输出 bow。 
如果两个一样，那么输出 same。

输入样例
15 100
0 1000
0 200

输出样例
axe
bow
axe
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


double Hurt(double equip_attack, double enemy_armor, double penetration)
{
    double armor = enemy_armor - penetration;
    double hurt_reduce = armor / (602 + armor);
    double attack = 100 + equip_attack;
    return attack * (1.0 - hurt_reduce);
}


string AdcEquipment(int level, int armor)
{
    // which equipment to use, given level of self and
    // armor of enemy

    double hurt_axe, hurt_bow;
    double pen_axe = 100 + level * 10, pen_bow = armor * 0.45;
    double attack_axe = 85, attack_bow = 80;
    double eps = 1e-5;

    hurt_axe = Hurt(attack_axe, armor, pen_axe);
    hurt_bow = Hurt(attack_bow, armor, pen_bow);

    if (fabs(hurt_axe - hurt_bow) < eps)
        return "same";

    if (hurt_axe > hurt_bow)
        return "axe";

    return "bow";
}


int main(int argc, char *argv[])
{
    string line;
    string res;

    // input case
    while (getline(myfile, line))
    {
        int n, m;
        cout << line << endl;
        stringstream ss(line);
        ss >> n; ss >> m;

        // result
        res = AdcEquipment(n, m);
        cout << res << endl;
    }

    return 0;
}