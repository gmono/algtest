#include <iostream>
#include <iomanip>
#include <algorithm>
#include <stack>
#include <cstdio>
#include <vector>
#include <climits>
#include <string.h>
using namespace std;
const int base {1000000000};
#define WIDTH 9
typedef unsigned int uint;
int main(void)
{
    ios::sync_with_stdio(false);
    string str;
    vector<uint> a, b, c;

    while (cin >> str)
    {
        int x, len_a = (str.length() - 1) / WIDTH + 1;
               a.clear();
               for(int i = 0;i < len_a; ++i)
               {
                   int end =str.length() - i*WIDTH;
                   int start =max(0,end - WIDTH);
                   sscanf(str.substr(start,end-start).c_str(),"%d",&x);
                   a.push_back(x);
               }
               b.clear();
               cin >> str;
               int len_b = (str.length() - 1) / WIDTH + 1;
               for (int i = 0; i != len_b; ++i)
               {
                   int end = str.length() - i * WIDTH;
                   int start = max(0, end - WIDTH);
                   sscanf(str.substr(start, end - start).c_str(), "%d", &x);
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
                   if(carry)
                   {
                       c[i+j]+=carry;
                   }
               }
               while (c.size() > 1 && c[c.size() - 1] == 0)
                   c.pop_back();

        int len = c.size();
        cout << c[--len];
        while (len > 0)
            cout << setw(WIDTH) << setfill('0') << c[--len];
        cout << endl;
    }


}
