#include <iostream>
using namespace std;

class Chess
{
protected:
    char name_;
public:
    virtual Chess* Clone() = 0;
    virtual void Show() {
      cout<< name_ <<endl;
    }
};

class ChessA : public Chess
{

public:
    ChessA(char name) {
      name_ = name;
    }
    
    ChessA(const ChessA& chess) {
      name_ = chess.name_;
    }
    
    virtual Chess* Clone() override {
      return new ChessA(*this);
    }
};

class ChessB : public Chess
{
public:
    ChessB(char name) {
      name_ = name;
    }
    
    ChessB(const ChessB& chess) {
      name_ = chess.name_;
    }
    
    virtual Chess* Clone() override {
      return new ChessB(*this);
    }
};

int main() {
    Chess *a = new ChessA('A');
    a->Clone()->Show();
    Chess *b = new ChessB('B');
    b->Clone()->Show();
    return 0;
}
