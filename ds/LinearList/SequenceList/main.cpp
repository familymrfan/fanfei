#include <iostream>
#include "ADTList.h"

int main() {
	ADTList<int> list;
	list.Insert(0,1);
	list.Insert(0,2);
	list.Insert(0,3);
	list.Insert(0,4);
	int a;
	list.GetValue(2,a);
	std::cout << "GetValue(2):" << a << std::endl;
	list.Delete(0);
	list.Delete(0);
	list.Delete(0);
	list.Clear();
	list.Print();
	getchar();
	return 0;
}
