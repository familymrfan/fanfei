#include "ADTStack.h"
#include <iostream>
using namespace std;

int main() {
	Stack<int> stack;
	stack.Push(123);
	stack.Push(456);
	stack.Pop();
	cout<< stack <<endl;
	getchar();
	return 0;
}