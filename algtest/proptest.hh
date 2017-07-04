#include <iostream>
using namespace std ;
template<class ValueType>
class Prop
{
public:
    //此构造函数初始化一个自动管理数据的属性类似C#的
    //string A{get;set;}之内
    Prop(bool isself=true,bool isread=true,bool iswrite=true):
        canread(isread),
        canwrite(iswrite)
    {
        if(isself)
            this->data=new ValueType();
    }

    virtual ~Prop()
    {
        if(data) delete data;
    }

    operator const ValueType&()
    {
        return this->get();
    }
    Prop<ValueType> &operator =(const ValueType &v)
    {
        this->set(v);
        return *this;
    }

protected:
    virtual void set(const ValueType &v)
    {
        if(canwrite)
        {
            if(data)
            {
                *data=v;
            }
            else
            {
                throw "错误！必须实现set函数!";
            }
        }
        else throw "错误！此属性不支持写操作！";
    }

    virtual const ValueType &get()
    {
        if(canread)
        {
            if(data)
            {
                return *data;
            }
            else
            {
                throw "错误！必须实现get函数!";
            }
        }
        else throw "错误！此属性不支持读操作！";
    }
private:
    bool canread;
    bool canwrite;
    //self data
    ValueType *data=nullptr;
};

class Test
{
public:
    Prop<int> pa;
    Prop<double> pb;
    Prop<string> pc;
};

int main()
{
    Test a;
    a.pc=string("dfadf");
    a.tt=string("buf");
    cout<<(string)a.pc<<(string)a.tt;
}
