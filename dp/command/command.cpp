#include "stdio.h"
#include <vector>

class Receiver;

class Command
{
public:
    Command(Receiver* receiver):receiver_(receiver) {

    }
    virtual ~Command() {}
    virtual void Execute() = 0;
protected:
    Receiver* receiver_;
};

class Receiver
{
public:
    Receiver(char* name) : name_(name) {}

    void Action() {
        printf("receiver %s action\n", name_);
    }
private:
    char* name_;
};

class ConcreteCommand1 : public Command
{
public:
    ConcreteCommand1(Receiver* receiver) : Command(receiver) {

    }

    virtual void Execute() {
        printf("Command1\n");
        receiver_->Action();
    }
};

class ConcreteCommand2 : public Command
{
public:
    ConcreteCommand2(Receiver* receiver) : Command(receiver) {

    }

    virtual void Execute() {
        printf("Command2\n");
        receiver_->Action();
    }
};

class Invoker
{
public:
    Invoker(){

    }

    void SetCommand(Command* command) {
        command_ = command;
    }

    void Invoke() {
        command_->Execute();
    }
private:
    Command* command_;
};

int main() {
    Receiver receiver1("A"), receiver2("B");
    ConcreteCommand1 command1(&receiver1);
    ConcreteCommand2 command2(&receiver2);
    Invoker invoker;
    invoker.SetCommand(&command1);
    invoker.Invoke();
    invoker.SetCommand(&command2);
    invoker.Invoke();

    return 0;
}
