#include "stdio.h"

class Abstraction
{
public:
    virtual void Handle() = 0;
};

class AbstractionImpl
{
public:
    virtual void Handle() = 0;
};

class DefinedAbstraction : public Abstraction
{
public:
    DefinedAbstraction(AbstractionImpl* impl):impl_(impl) {

    }

    virtual void Handle() {
        impl_->Handle();
    }
private:
    AbstractionImpl* impl_;
};

class ConcreteAbstractionImplement1 : public AbstractionImpl
{
public:
    virtual void Handle() {
        printf("impl 1 handle\n");
    }
};

class ConcreteAbstractionImplement2 : public AbstractionImpl
{
public:
    virtual void Handle() {
        printf("impl 2 handle\n");
    }
};

int main() {
    ConcreteAbstractionImplement1* impl1 = new ConcreteAbstractionImplement1;
    ConcreteAbstractionImplement2* impl2 = new ConcreteAbstractionImplement2;
    DefinedAbstraction* defined1 = new DefinedAbstraction(impl1);
    defined1->Handle();

    DefinedAbstraction* defined2 = new DefinedAbstraction(impl2);
    defined2->Handle();

    return 0;
}
