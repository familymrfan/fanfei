#include <iostream>
#include <string>
#include <list>
using namespace std;

class Company
{
public:
    Company(const string& name):name_(name){
    }
    virtual ~Company() {}
    virtual void Add(Company *company) = 0;
    virtual void Show() = 0;
protected:
    string name_;
};

class ConcreteCompany : public Company
{
public:
      ConcreteCompany(const string& name):Company(name){
      }
      void Add(Company* company) {
	companys.push_back(company);
      }
      void Show() {
	  for(Company* company:companys) {
	    cout<< "ConcreteCompany:" << name_<<endl; 
	    company->Show();
	  }
      }
protected:
      list<Company *> companys;
};

class FinanceDepartment : public Company
{
public:
      FinanceDepartment(const string& name):Company(name){
      }
      void Add(Company* company) {}
      void Show() {
	  cout<<"FinanceDepartment:"<<name_<<endl;
      }
};

class HRDepartment : public Company
{
public:
      HRDepartment(const string& name):Company(name){
      }
      void Add(Company* company) {}
      void Show() {
	  cout<<"HRDepartment:"<<name_<<endl;
      }
};

int main() {
    ConcreteCompany company("A");
    HRDepartment hr("A");
    FinanceDepartment f("A");
    
    company.Add(&hr);
    company.Add(&f);
    company.Show();
    
    
    return 0;
}