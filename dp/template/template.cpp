#include <iostream>
using namespace std;


class SomeOneHoliday
{
public:
    void Begin() {
      Day1();
      Day2();
      Day3();
    }
    
    virtual void Day1() = 0;
    virtual void Day2() = 0;
    virtual void Day3() = 0;
};

class AHoliday : public SomeOneHoliday
{
virtual void Day1() override {
    cout<<"A day1"<<endl;
}

virtual void Day2() override {
    cout<<"A day2"<<endl;
}

virtual void Day3() override {
    cout<<"A day3"<<endl;
}

};

class BHoliday : public SomeOneHoliday
{
virtual void Day1() override {
    cout<<"B day1"<<endl;
}

virtual void Day2() override {
    cout<<"B day2"<<endl;
}

virtual void Day3() override {
    cout<<"B day3"<<endl;
}  
  
};


int main() {
    SomeOneHoliday* holiday = new AHoliday();
    holiday->Begin();
    holiday = new BHoliday();
    holiday->Begin();
      
    return 0;
}