#include <iostream>
#include <string>
using namespace std;

class Light
{
    string name_;
public:
    Light(const string& name):name_(name) {}
    virtual ~Light() {}
    virtual void Shine() {
	cout<< "light:"<< name_ <<endl;
    }
};

class LightDecorate : public Light
{
public:
    Light* Decorate(Light* light) { 
	light_ = light; 
	return this;
    } 
protected:  
    Light* light_; 
    LightDecorate() :Light(""),light_(nullptr) {}  
    virtual ~LightDecorate() {}    
    virtual void Shine() override {   
        if(light_)   
            return light_->Shine();
    }
};

class LightRed : public LightDecorate
{
public:
    virtual void Shine() override {
	cout<< "Add a little Red"<<endl;
        LightDecorate::Shine();
    }
};

class LightBule : public LightDecorate
{
public:
    virtual void Shine() override {
	cout<< "Add a little bule"<<endl;
        LightDecorate::Shine();
    }
};

class LightGreen : public LightDecorate
{
public:
    virtual void Shine() override {
	cout<< "Add a little green"<<endl;
        LightDecorate::Shine();
    }
};

int main() {
    Light light1("light1"),light2("light2");
    LightRed red;
    LightBule bule;
    LightGreen green;
    auto r1 = red.Decorate(&light1);
    auto b1 = bule.Decorate(r1);
    b1->Shine();
    
    auto r2 = red.Decorate(&light2);
    auto b2 = bule.Decorate(r2);
    auto g  = green.Decorate(b2);
    g->Shine();
    return 0;
}