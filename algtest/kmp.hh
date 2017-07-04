#include <iostream>
using namespace std;
#include <string>
#include <algorithm>
int *makearr(string &format)
{
    int *ret=new int[format.length()];
    std::fill(ret,ret+format.length(),0);
    if(format.length()<=2) return ret;
}

int main()
{
    string str;
    cin>>str;

}
