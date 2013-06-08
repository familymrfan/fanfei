#include "ADTStack.h"
#include <iostream>
using namespace std;

int main() {
	Stack<int> stack;

	for(int i=0;i<2000;i++) {
		stack.Push(123);
	}
	cout<< stack.size_ <<endl;
	for(int i=0;i<500;i++) {
		stack.Pop();
	}
	cout<< stack.size_ <<endl;
	//cout<< stack <<endl;
	getchar();
	return 0;
}