#include <iostream>
#include <string>
#include <set>

using namespace std;

class IObserver;

class ISubject
{
public:
    virtual void RegisterObserver(IObserver *o) = 0;
    virtual void RemoveObserver(IObserver *o) = 0;
    virtual void NotifyObservers() = 0;
};

class IObserver
{
protected:
    IObserver() {
      
    }
    
public:
    
    virtual void Update(float temp, float humidity, float pressure) = 0;
    
};

class IDisplay
{
protected:
    IDisplay() {
      
    }
    
public:
    virtual void Display() = 0;
    
};


typedef set<IObserver *> ObserverList;
typedef set<IObserver *>::iterator ObserverListIter;

class WeatherData : public ISubject
{
private:
    ObserverList observers_;
    float temp_;
    float humidity_;
    float pressure_;
    
public:
    virtual void RegisterObserver(IObserver* o) {
	observers_.insert(o);
    }
    
    virtual void RemoveObserver(IObserver* o) {
	ObserverListIter iter = observers_.find(o);
	if(iter != observers_.end()) {
	    observers_.erase(iter);
	}
    }
    
    virtual void NotifyObservers() {
	for(auto o:observers_) {
	    o->Update(temp_, humidity_, pressure_);
	}
    }
    
    void Changed(float temp, float humidity, float pressure) {
	temp_ = temp;
	humidity_ = humidity;
	pressure = pressure_;
	NotifyObservers();
    }
};

class FirstDisplay:public IObserver,public IDisplay
{
    float temp_;
    float humidity_;

public:
    
    virtual void Update(float temp, float humidity, float pressure) {
	temp_ = temp;
	humidity_ = humidity;
	Display();
    }
    
    virtual void Display() {
	cout<<"FirstDisplay:"<<temp_<<","<<humidity_<<endl;
    }
};

class SecondDisplay:public IObserver,public IDisplay
{
    float temp_;

public:
    
    virtual void Update(float temp, float humidity, float pressure) {
	temp_ = temp;
	Display();
    }
    
    virtual void Display() {
	cout<<"SecondDisplay:"<<temp_<<endl;
    }
};

int main() {
    FirstDisplay fd;
    SecondDisplay sd;
    
    WeatherData data;
    data.RegisterObserver(&fd);
    data.RegisterObserver(&sd);
    
    data.RemoveObserver(&sd);
    
    data.Changed(2,1,0);
    
    system("pause");
    
    return 0;
}

