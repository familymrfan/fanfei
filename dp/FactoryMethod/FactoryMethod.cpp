#include <iostream>
using namespace std;

class IProduct
{
public:
    virtual void ShowDescribe() = 0;
};

class IPad : public IProduct
{
public:
    virtual void ShowDescribe() override {
        cout<< "IPad" << endl;
    }
};

class IPhone : public IProduct
{
public:
    virtual void ShowDescribe() override {
        cout<< "IPhone" << endl;
    }
};

class IFactory
{
public:
    virtual IProduct* Create() = 0;
};

class IPadFactory : public IFactory
{
public:
    virtual IProduct* Create() override {
        return new IPad();
    }
};

class IPhoneFactory : public IFactory
{
public:
    virtual IProduct* Create() override {
        return new IPhone();
    }
};

int main() {
    IFactory* ipad_factory= new IPadFactory();
    ipad_factory->Create()->ShowDescribe();
    IFactory* iphone_factory= new IPhoneFactory();
    iphone_factory->Create()->ShowDescribe();
    system("pause");
    return 0;
}
