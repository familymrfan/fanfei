#include "ADTStack.h"
#include <string>
#include <iostream>

int main() {
	std::string input;
	std::cin>>input;
	Stack<char> stack;

	for(char c:input) {
		if(stack.Top() != nullptr) {
			if(*stack.Top() == '(' && ')' ==  c
				|| *stack.Top() == '[' && ']' == c
				|| *stack.Top() == '{' && '}' == c)
			stack.Pop();
			continue;
		}
		stack.Push(c);
	}
	if(stack.IsEmpty()) {
		std::cout<< "Yes" <<std::endl;
	} else {
		std::cout<< "No" <<std::endl;
	}
	system("pause");
	return 0;
}