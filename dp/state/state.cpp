#include <iostream>
using namespace std;

class Context;

class IState
{
public:
    virtual void Handle(Context *con) = 0;
};

class Context
{
public:
    Context(IState *state) {
        state_ = state;
    }
    
    void Handle() {
        state_->Handle(this);
    }

    void ChangeState(IState *state) {
        state_ = state;
    }
private:
    IState *state_;
};

class ConcreteStateA : public IState
{
public:
    virtual void Handle(Context *con);
};

class ConcreteStateB : public IState
{
public:
    virtual void Handle(Context *con);
};

void ConcreteStateA::Handle(Context *con) {
    cout<<"ConcreteStateA Handle"<<endl;
    con->ChangeState(new ConcreteStateB());
}

void ConcreteStateB::Handle(Context *con) {
    cout<<"ConcreteStateB Handle"<<endl;
    con->ChangeState(new ConcreteStateA());
}

int main() {
   
    Context con(new ConcreteStateA);

    for(int i=0;i<10;i++) {
        con.Handle();
    }

   system("pause");
   return 0;
}
