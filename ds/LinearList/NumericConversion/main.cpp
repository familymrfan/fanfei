#include "ADTStack.h"

//10����ת���ͽ���
void ConvertNAry(int x, int ary) {
	Stack<int> stack;
	while(x) {
		stack.Push(x % ary);
		x = x/ary;
	}
	int *p = nullptr;
	while(p = stack.Top()) {
		std::cout<< *p;
		stack.Pop();
	}
}

int main() {
	ConvertNAry(16,2);
	getchar();
	return 0;
}