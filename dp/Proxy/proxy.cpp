#include <iostream>
using namespace std;

class SomeOne
{
public:
    virtual void SendUmbrella() = 0;
};

class Actor : public SomeOne
{
public:
    virtual void SendUmbrella() {
      cout<< "Actor SendUmbrella"<<endl;
    }
};

class Proxy : public SomeOne
{
    SomeOne *one_;
public:
    Proxy(SomeOne *one):one_(one){
    }
  
    virtual void SendUmbrella() {
      one_->SendUmbrella();
    }
};

int main() {
    Actor a;
    Proxy p(&a);
    p.SendUmbrella();
    return 0;
}
