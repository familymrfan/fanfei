#include <iostream>
// http://blog.chinaunix.net/uid-20385936-id-3554976.html
enum CoreType
{
	CORE_A,
	CORE_B
};

class Core
{
public:
	virtual void Show() = 0;
};

class CoreA : public Core
{
public:
	virtual void Show() {
		std::cout<< "This is A Core A" <<std::endl;
	}
};

class CoreB : public Core
{
public:
	virtual void Show() {
		std::cout<< "This is A Core B" <<std::endl;
	}
};

class Factory
{
public:
	Core* CreateCore(CoreType core_type) {
		switch(core_type) {
			case CORE_A:
				return new CoreA;
			case CORE_B:
				return new CoreB;
			default:
				return NULL;
		}
	}
	
};

int main() {
	Factory f;
	Core *coreA = f.CreateCore(CORE_A);
	coreA->Show();
	Core *coreB = f.CreateCore(CORE_B);
	coreB->Show();
	return 0;
}

