#include <iostream>
using namespace std;


class IUser
{
public:
    virtual void GetUser() = 0;
};

class IDepartment
{
public:
    virtual void GetDepartment() = 0;
};

class CAccessUser : public IUser
{
public:
    virtual void GetUser() { cout << "Access GetUser" << endl; }
};

class CAccessDepartment : public IDepartment
{
public:
    virtual void GetDepartment() { cout << "Acces GetDepartment" << endl; }
};

class CSqlUser : public IUser
{
public:
    virtual void GetUser() { cout << "Sql GetUser" << endl; }
};

class CSqlDepartment : public IDepartment
{
public:
    virtual void GetDepartment() { cout << "Sql GetDepartment" << endl; }
};

class IFactory
{
public:
    virtual IUser* CreateUser() = 0;
    virtual IDepartment* CreateDepartment() = 0;
};

class AccessFactory : public IFactory
{
public:
    virtual IUser* CreateUser() { return new CAccessUser(); }
    virtual IDepartment* CreateDepartment() { return new CAccessDepartment(); }
};

class SqlFactory : public IFactory
{
public:
    virtual IUser* CreateUser() { return new CSqlUser(); }
    virtual IDepartment* CreateDepartment() { return new CSqlDepartment(); }
};

int main()
{
    IFactory* factory1 = new SqlFactory();
    IUser* user1 = factory1->CreateUser();
    IDepartment* depart1 = factory1->CreateDepartment();
    user1->GetUser();
    depart1->GetDepartment();
    IFactory* factory2 = new AccessFactory();
    IUser* user2 = factory2->CreateUser();
    IDepartment* depart2 = factory2->CreateDepartment();
    user2->GetUser();
    depart2->GetDepartment();
    system("pause");
    return 0;
}