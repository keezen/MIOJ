/*
- 不一样的排序

序号：#128
难度：一般
时间限制：1000ms
内存限制：32M

描述
有一天利姆鲁想教他的哥布林部下学数学，因为他之前教过因子，现在想考考他们。

利姆鲁问现在有 n 个数，需要用因子个数的多少进行排序，因子个数多的排在
后面，因子个数少的排在前面，如果因子个数相同那么就比较这个数的大小，数
大的放在后面，数小的放在前面。现在让你说出排序之后第 K 个位置的数字是多少。

输入
第 1 个整数为整数 K，1≤K≤10^6；

第 2 个为整数 n，表示数字的数量，n<10^7；

接下来有 n 个整数，每个数的大小不超过 10^6.

输出
输出排序之后的第 K 位置的数值。

输入样例
4 6 1 2 3 4 5 6

输出样例
5
*/

# include <iostream>
# include <cstdlib>
# include <fstream>
# include <sstream>
# include <vector>
# include <cmath>
using namespace std;


ifstream myfile("a.txt");


ostream & operator<<(ostream &os, pair<int, int> &rhs)
{
    cout << rhs.first << ',' << rhs.second;
    return os;
}


template <typename T> void PrintVec(vector<T> &data, char sep = ' ', char eol = '\n')
{
    for (int i = 0; i < data.size() - 1; i++)
        cout << data[i] << sep;
    cout << data.back() << eol;
}


const int maxn = 1000000;
vector<bool> is_prime(maxn, true);
vector<int> primes;
vector<int> nfacs(maxn, 0);  // number of factors


void ComputePrime()
{
    // compute primes no larger than max number

    int i, j;

    is_prime[0] = is_prime[1] = false;
    for (i = 2; i <= maxn; i++)
        if (is_prime[i])  // current is prime, sieve
        {
            primes.push_back(i);
            for (j = i * 2; j <= maxn; j += i)
                is_prime[j] = false;
        }
}


void ComputeFactor()
{
    // compute number of factors of every number

    nfacs[1] = 1;
    for (int i = 1; i < maxn; i++)
    {
        if (is_prime[i])
            nfacs[i] = 2;
        else
            for (int j = 0; j < primes.size() && primes[j] <= i; j++)
            {
                if (i % primes[j] == 0)
                {
                    int expo = 0, p = primes[j], t;
                    for (t = i; t > 1 && t % p == 0; t /= p)
                        expo++;
                    nfacs[i] = (expo + 1) * nfacs[t];
                    break;
                }
            }
    }
        
}


bool CompareFactor(int a, int b)
{
    // compare number of factors
    int faca = nfacs[a], facb = nfacs[b];
    return faca < facb || (faca == facb && a < b);
}


int Partition(vector<int> &data, int start, int end)
{
    // partition array according to last element

    if (data.size() <= 0 || start < 0 || end >= data.size() || start > end)
        return -1;

    int i = start, j = end - 1;
    int v = data[end];

    while (i <= j)
    {
        if (CompareFactor(data[i], v))
            i++;
        else
            swap(data[i], data[j--]);
    }
    swap(data[end], data[i]);

    return i;
}


int KthMinElement(vector<int> &data, int k)
{
    // k-th min element

    if (data.size() <= 0 || k <= 0 || k > data.size())
        return -1;

    // partition until k-th element
    int n = data.size(), i;
    int s = 0, e = n - 1, p;

    while (s <= e)
    {
        p = Partition(data, s, e);
        if (p == k - 1)
            return data[p];
        else if (p < k - 1)
            s = p + 1;
        else
            e = p - 1;
    }

    return -1;
}


int main(int argc, char *argv[])
{
    string line;
    int res;

    ComputePrime();
    ComputeFactor();

    // input case
    while (getline(myfile, line))
    {
        stringstream ss(line);
        int k, n, x;
        ss >> k >> n;
        vector<int> data;
        while (ss >> x)
            data.push_back(x);

        cout << line << endl;

        // result
        res = KthMinElement(data, k);
        cout << res << endl;
    }

    return 0;
}