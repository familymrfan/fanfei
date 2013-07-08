#ifndef FAKES_FACTORY_H_
#define FAKES_FACTORY_H_

template <typename Type, typename TypeP = Type>
class FakesFactory
{
public:
    Type* NewFakes(TypeP* parent = nullptr) {
        return new Type(parent);
    }

    void DelFakes(Type* fakes) {

    }
};

#endif