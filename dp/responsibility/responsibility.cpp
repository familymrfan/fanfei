#include "stdio.h"

class Handle
{
public:
    void SetSuccessor(Handle* handle) {
        handle_ = handle;
    }

    Handle* GetSuccessor() const {
        return handle_;
    }

    virtual void HandleRequest(int request) = 0;

private:
    Handle* handle_;
};

class ConcreteHandleA : public Handle
{
public:
    virtual void HandleRequest(int request) {
        if(request >= 0 && request <= 500) {
            printf("ConcreteHandleA Handle \n");
        } else {
            GetSuccessor()->HandleRequest(request);
        }
    }
};

class ConcreteHandleB : public Handle
{
    virtual void HandleRequest(int request) {
        if(request >500) {
            printf("ConcreteHandleB Handle \n");
        } 
    }       
};

int main() {
    
    ConcreteHandleA a;
    ConcreteHandleB b;
    a.SetSuccessor(&b);

    a.HandleRequest(100);
    a.HandleRequest(600);
    a.HandleRequest(500);

    return 0;
}
