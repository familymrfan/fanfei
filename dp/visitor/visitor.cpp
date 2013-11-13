#include <iostream>
#include <vector>
using namespace std;

class RaiesHr;
class RewardHr;
class Employee
{
public:
    virtual void VisitRaies(RaiesHr* raies) = 0;
    virtual void VisitReward(RewardHr* reward) = 0;
};

class Employee1 : public Employee
{
public:
    virtual void VisitRaies(RaiesHr* raies);
    virtual void VisitReward(RewardHr* reward);
};

class Employee2 : public Employee
{
public:
    virtual void VisitRaies(RaiesHr* raies);
    virtual void VisitReward(RewardHr* reward);
};

class Hr
{
public:
    virtual void Accept(Employee* employee) = 0;
};

class RaiesHr : public Hr
{
public:
    RaiesHr():number_(0.5f) {

    }

    float Get() const {
        return number_;
    }

    virtual void Accept(Employee* employee) {
        employee->VisitRaies(this);
    }
private:
    float number_;
};

class RewardHr : public Hr
{
public:
    RewardHr():number_(500) {

    }

    int Get() const {
        return number_;
    }

    virtual void Accept(Employee* employee) {
        employee->VisitReward(this);
    }
private:
    int number_;
};

class Hrs
{
public:

    void Push(Hr* hr) {
        hrs_.push_back(hr);
    }

    void Accept(Employee* employee) {
        for(Hr* hr : hrs_) {
            hr->Accept(employee);
        }
    }

private:
    std::vector<Hr*> hrs_;
};


void Employee1::VisitRaies(RaiesHr* raies) {
    std::cout<<"Employee1"<<std::endl;
    std::cout<<5000 + 5000* raies->Get()<<std::endl;
}

void Employee1::VisitReward(RewardHr* reward) {
    std::cout<<"Employee1"<<std::endl;
    std::cout<<5000 + reward->Get()<<std::endl;
}

void Employee2::VisitRaies(RaiesHr* raies) {
    std::cout<<"Employee2"<<std::endl;
    std::cout<<6000 + 6000* raies->Get()<<std::endl;
}

void Employee2::VisitReward(RewardHr* reward) {
    std::cout<<"Employee2"<<std::endl;
    std::cout<<6000 + reward->Get()<<std::endl;
}

int main() {
    Hrs hrs;
    hrs.Push(new RaiesHr());
    hrs.Push(new RewardHr());

    Employee1 e1;
    Employee2 e2;

    hrs.Accept(&e1);
    hrs.Accept(&e2);
   
    return 0;
}