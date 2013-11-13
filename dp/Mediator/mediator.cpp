#include "stdio.h"

class Colleage;
class Mediator
{
public:
    virtual void Send(char* msg, Colleage* colleage) = 0;
};

class Colleage
{
public:
    Colleage(Mediator* mediator):mediator_(mediator) {

    }
    virtual void Send(char* msg) = 0;
protected:
    Mediator* mediator_;
};

class ConcreteColleageA : public Colleage
{
public:
    ConcreteColleageA(Mediator* mediator):Colleage(mediator) {

    }

    void Send(char* msg) {
        mediator_->Send(msg, this);
    }

    void Get(char* msg) {
        printf("A Get Msg:%s\n", msg);
    }
};


class ConcreteColleageB : public Colleage
{
public:
    ConcreteColleageB(Mediator* mediator):Colleage(mediator) {

    }

    void Send(char* msg) {
        mediator_->Send(msg, this);
    }

    void Get(char* msg) {
        printf("B Get Msg:%s\n", msg);
    }
};

class ConcretMediator : public Mediator
{
public:
    void SetConcreteColleageA(ConcreteColleageA* colleagea) {
        colleagea_ = colleagea;
    }

    void SetConcreteColleageB(ConcreteColleageB* colleageb) {
        colleageb_ = colleageb;
    }

    void Send(char* msg, Colleage* colleage) {
        if(reinterpret_cast<Colleage*>(colleagea_) == colleage) {
            colleageb_->Get(msg);
        } else {
            colleagea_->Get(msg);
        }
        
    }
private:
    ConcreteColleageA* colleagea_;
    ConcreteColleageB* colleageb_;
};



int main() {
    
    ConcretMediator mediator;

    ConcreteColleageA a(&mediator);
    ConcreteColleageB b(&mediator);

    mediator.SetConcreteColleageA(&a);
    mediator.SetConcreteColleageB(&b);

    a.Send("123");
    b.Send("456");
    
    return 0;
}
