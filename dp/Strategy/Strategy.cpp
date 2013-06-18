#include <iostream>
using namespace std;

class FlyBehavior
{
public:
    virtual void Fly() = 0; //pure virtual function
};
class FlyBehavior0 : public FlyBehavior //can not fly
{
public:
    virtual void Fly() override {
	cout<<"I can not fly."<<endl;
    }
};

class FlyBehavior1 : public FlyBehavior //fly: ^%^
{
public:
    virtual void Fly() override {
	cout<<"I can fly with ^%^."<<endl;
    }
};

class FlyBehavior2 : public FlyBehavior //fly: ^&^
{
public:
    virtual void Fly() override {
	cout<<"I can fly with ^&^."<<endl;
    }
};

class FlyBehavior3 : public FlyBehavior //fly: ^@^
{
public:
    virtual void Fly() override {
	cout<<"I can fly with ^@^."<<endl;
    }
};

class Duck
{
public:
    Duck(FlyBehavior *behavior) : behavior_(behavior) {
    
      
    }
    void Fly() {
        behavior_->Fly();
    }
private:
    FlyBehavior *behavior_;
};

int main() {
    Duck duck1(new FlyBehavior0);
    Duck duck2(new FlyBehavior1);
    Duck duck3(new FlyBehavior2);
    Duck duck4(new FlyBehavior3);
    
    duck1.Fly();
    duck2.Fly();
    duck3.Fly();
    duck4.Fly();
    return 0;
}
