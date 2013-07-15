#include <iostream>
using namespace std;

class Target
{
public:
    Target() {}
    virtual ~Target() {}
    virtual void Request() = 0;
};

class Adaptee
{
public:
    Adaptee() {}
    void SpecificRequest() {
	cout<<"got it !"<<endl;
    }
};


// class type
class AdapterClass:public Target,private Adaptee
{
public:
    AdapterClass() {}
    
    virtual void Request() override {
	this->SpecificRequest();
    }
};

class AdapterObject:public Target
{
public:
    AdapterObject(Adaptee* adaptee):adaptee_(adaptee) {
      
    }
    
    virtual void Request() override {
	adaptee_->SpecificRequest();
    }
private:
    Adaptee *adaptee_;
};

int main() {
    AdapterClass ac;
    ac.Request();
  
    Adaptee a;
    AdapterObject ao(&a);
    ao.Request();
    
    return 0;
}