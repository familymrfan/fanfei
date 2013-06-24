#include <iostream>
using namespace std;

class Builder
{
public:
    virtual void BuildHead() = 0;
    virtual void BuildBody() = 0;
    virtual void BuildLeftArm() = 0;  
    virtual void BuildRightArm() = 0; 
    virtual void BuildLeftLeg() = 0;
    virtual void BuildRightLeg() = 0; 
};

class ThinBuilder : public Builder  
{  
public:  
    void BuildHead() { cout<<"build thin body"<<endl; }  
    void BuildBody() { cout<<"build thin head"<<endl; }  
    void BuildLeftArm() { cout<<"build thin leftarm"<<endl; }  
    void BuildRightArm() { cout<<"build thin rightarm"<<endl; }  
    void BuildLeftLeg() { cout<<"build thin leftleg"<<endl; }  
    void BuildRightLeg() { cout<<"build thin rightleg"<<endl; }  
}; 

class FatBuilder : public Builder  
{  
public:  
    void BuildHead() { cout<<"build fat body"<<endl; }  
    void BuildBody() { cout<<"build fat head"<<endl; }  
    void BuildLeftArm() { cout<<"build fat leftarm"<<endl; }  
    void BuildRightArm() { cout<<"build fat rightarm"<<endl; }  
    void BuildLeftLeg() { cout<<"build fat leftleg"<<endl; }  
    void BuildRightLeg() { cout<<"build fat rightleg"<<endl; }  
};

class Director
{
private:
    Builder *builder_;
public:
    Director(Builder *builder):builder_(builder) {

    }

    void Create() {
        builder_->BuildHead();
        builder_->BuildBody();
        builder_->BuildLeftArm();
        builder_->BuildRightArm();
        builder_->BuildLeftLeg();
        builder_->BuildRightLeg();
    }
};

int main() {
    FatBuilder fat;
    Director director(&fat);
    director.Create();
    system("pause");
    return 0;
}
    