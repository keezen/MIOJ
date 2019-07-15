/*
- 寻找最大主对角线的和

序号：#39
难度：一般
时间限制：1000ms
内存限制：10M

描述
任意给一个m*n矩阵(m>=2, n>=2)，元素均为非负数，请找出其中主对角线和
最大的二阶子矩阵，求出主对角线和。（主对角线：一个n维矩阵的主对角线为
所有第k行第k列元素的全体，k=1, 2, 3… n，即从左上到右下的一条斜线）

举例： 有一个3*5的矩阵如下： 3 3 1 3 4 5 5 7 10 1 2 9 5 3 3 
其中，主对角线和最大的二阶子矩阵是: 5 5 2 9 可得出其主对角线和为14

输入
单组数据。 输入一个 m*n (1 < m < 50, 1 < n < 50)矩阵，每行有 
n 个整数，共 m 行.

输出
一个整数，表示最大的主对角线和

输入样例
3 3 1 3 4
5 5 7 10 1
2 9 5 3 3

输出样例
14
*/

# include <iostream>
# include <cstdlib>
# include <fstream>
# include <sstream>
# include <vector>
using namespace std;


ifstream myfile("a.txt");


template <typename T> void PrintVec(vector<T> &data)
{
    for (int i = 0; i < data.size() - 1; i++)
        cout << data[i] << ',';
    cout << data.back() << endl;
}


int MaxDiagonalSum(vector<vector<int> > &matrix)
{
    // maximum diagonal sum of 2-order sub-matrix of 
    // given matrix

    if (matrix.size() < 2 || matrix[0].size() < 2)
        return 0;

    int m = matrix.size(), n = matrix[0].size();
    int i, j;
    int sum = matrix[0][0] + matrix[1][1], t;
    for (i = 0; i < m - 1; i++)
        for (j = 0; j < n - 1; j++)
            sum = max(matrix[i][j] + matrix[i + 1][j + 1], sum);
    
    return sum;
}


int main(int argc, char *argv[])
{
    string str;
    int x;
    int res;

    // input case
    vector<vector<int> > matrix;
    while (getline(myfile, str))
    {
        stringstream ss(str);
        vector<int> row;
        while (ss >> x)
            row.push_back(x);
        matrix.push_back(row);

        PrintVec(row);
    }

    // result
    res = MaxDiagonalSum(matrix);
    cout << res << endl;

    return 0;
}