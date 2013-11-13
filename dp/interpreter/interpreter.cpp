#include "stdio.h"
#include <string>
#include <vector>

class Context
{
public:
    Context(std::string context) {
        context_ = context;
        index_ = 0;
    }

    char Get() {
        return context_[index_++];
    }

private:
    std::string context_;
    int index_;
};

class Expression
{
public:
    virtual void Interpreter(Context* context) = 0;
};

class Expression0 : public Expression
{
public:
    virtual void Interpreter(Context* context) {
        printf("%c = 0\n", context->Get());
    }
};

class Expression1 : public Expression
{
public:
    virtual void Interpreter(Context* context) {
        printf("%c = 1\n", context->Get());
    }
};

int main() {
    std::string s = "12345678";
    Context context(s);
    for (int i=0; i<s.size()/2; i++) {
        Expression0 exp0;
        exp0.Interpreter(&context);
        Expression1 exp1;
        exp1.Interpreter(&context);
    }

    return 0;
}
