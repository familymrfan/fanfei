#include <iostream>
#include "my_string.h"
using namespace std;

int main() {
    String s;
    s = "123123";
    cout<<s.Find("23")<<endl;
    s.Fail();
    cout<<s.KmpFind("23")<<endl;
    system("pause");
    return 0;
}