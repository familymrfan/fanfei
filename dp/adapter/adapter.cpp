#include "stdio.h"

class Target
{
public:
    virtual void Request() {
        printf("old request\n");
    }
};

class Adaptee
{
public:
    virtual void SpecialRequest() {
        printf("special request\n");
    }
};

class Adapter : public Target, public Adaptee
{
public:
    virtual void Request() {
        SpecialRequest();
    }
};

class Adapter2 : public Target
{
public:
    Adapter2():_adaptee(new Adaptee) {

    }

    virtual void Request() {
        _adaptee->SpecialRequest();
    }

private:
    Adaptee* _adaptee;
};

int main() {
    Target* target = new Adapter;
    target->Request();

    Target* target2 = new Adapter2;
    target2->Request();
    return 0;
}
