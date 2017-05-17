#include <iostream>
#include <iomanip>
#include <algorithm>
#include <stack>
#include <cstdio>
#include <vector>
#include <climits>
using namespace std;
namespace walg {
const int base {1000000000};
#define WIDTH 9
void mul(string &str1,string &str2)
{
    vector<int> a, b, c;
    int x, len_a = (str1.length() - 1) / WIDTH + 1;
    a.clear();
    for(int i = 0;i < len_a; ++i)
    {
        int end =str1.length() - i*WIDTH;
        int tstart =max(0,end - WIDTH);
        sscanf(str1.substr(tstart,end-tstart).c_str(),"%d",&x);
        a.push_back(x);
    }
    b.clear();
    int len_b = (str2.length() - 1) / WIDTH + 1;
    for (int i = 0; i != len_b; ++i)
    {
        int end = str2.length() - i * WIDTH;
        int tstart = max(0, end - WIDTH);
        sscanf(str2.substr(tstart, end - tstart).c_str(), "%d", &x);
        b.push_back(x);
    }
    c.resize(len_a + len_b);
    fill(c.begin(), c.end(), 0);
    long long temp = 0, carry = 0;
    for (int i = 0; i != len_a; ++i)
    {
        carry = 0;
        int j;
        for (j = 0; j != len_b; ++j)
        {
            temp = (long long)a[i] * b[j] + c[i + j] + carry;       //这里要注意，不用long long会溢出
            carry = temp / base;
            c[i + j] = temp % base;
        }
        while (carry)
        {
            temp = c[i + j] + carry;
            carry = temp / base;
            c[i + j] = temp;
            ++j;
        }
    }
    while (c.size() > 1 && c[c.size() - 1] == 0)
        c.pop_back();

}

}
