#include "stdio.h"
#include <vector>

class Originator;
class Memento
{
private:
    friend class Originator;
    void SetState(int state) {
        state_ = state;
    }

    int GetState() const {
        return state_;
    }
private:
    int state_;
};

class Originator
{
public:
    Originator(int state) {
        state_ = state;
    }

    void SetState(int state) {
        state_ = state;
    }

    int GetState() const {
        return state_;
    }

    void RestoreMemento(Memento* memento) {
        state_ = memento->GetState();
    }

    Memento* CreateMemento() {
        Memento* memento = new Memento;
        memento->SetState(state_);
        return memento;
    }

    void Show() {
        printf("State:%d\n", state_);
    }
private:
    int state_;
};



class CareTaker
{
public:
    void Push(Memento* memento) {
        mementos_.push_back(memento);
    }

    Memento* Get(int index) {
        return mementos_[index];
    }
private:
    std::vector<Memento*> mementos_;
};

int main() {
    Originator o1(0);
    o1.Show();

    CareTaker taker;
    taker.Push(o1.CreateMemento());

    o1.SetState(1);
    o1.Show();

    o1.RestoreMemento(taker.Get(0));
    o1.Show();

    return 0;
}
