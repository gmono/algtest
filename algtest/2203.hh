#include <iostream>
using namespace std;
int *makenext(string &format)
{
    int *next=new int[format.length()];
    next[0]=0;
    int i=1,j=0;
    while(i<format.length())
    {
        if(format[i]==format[j])
        {
            next[i]=j+1;
            j++;
            i++;
        }
        else if(j==0)
        {
            next[i]=0;
            i++;
        }
        else
        {
            j=next[j-1];
        }
    }
    return next;
}
bool search(string &str,string &format,int *next)
{
    int s=0,i=0;
    while(s<str.length())
    {
        for(;i<format.length();++i)
        {
            if(format[i]!=str[s+i])
                break;
        }
        if(i==format.length()) return true;
        if(i==0)
        {
            s++;
        }
        else
        {
            if(next[i-1]) s+=next[i-1];
            else s+=1;
            i=next[i-1];
        }

    }
    return false;
}

int main()
{
    string str;
    string format;
    while(cin>>str>>format)
    {
        string fstr=str+str;
        int *next=makenext(format);
        bool ishas=search(fstr,format,next);
        cout<<(ishas? "yes":"no")<<endl;
        delete next;
    }
}
