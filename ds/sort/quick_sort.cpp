#include <iostream>
#include <string>
#include <vector>

int a[] = {49, 38, 65, 97, 76, 13, 27};
const unsigned int size = sizeof(a)/sizeof(int);

void QSort(int low, int hign){
    if(low > hign) {
        return ;   
    }
    
    int i = low, j = hign;
    int x = a[i];
    bool left = false;
    while(i < j) {
        if(left) {
            if(x < a[i]) {
                left = false;
                a[j] = a[i];
                j--;
                continue;
            }
            i++;
        } else {
            if(x > a[j]) {
                left = true;
                a[i] = a[j];
                i++;
                continue;
            }
            j--;
        }
    }
    a[i] = x;
    QSort(low, i-1);
    QSort(i+1, hign);
}

int main()
{
    QSort(0, size - 1);
    for(unsigned int i = 0; i<size; i++) {
     std::cout << a[i] << std::endl;
    }
   
}

------------------------------

#include <iostream>
#include <string>
#include <vector>

int a[] = {49, 38, 65, 97, 76, 13, 27};
const unsigned int size = sizeof(a)/sizeof(int);

void QSort(int low, int hign){
    if(low > hign) {
        return ;   
    }
    int i = low, j = hign;
    int x = a[i];
    while(i < j) {
       while(i < j && x <= a[j]) j--;
       a[i] = a[j];
       while(i < j && x >= a[i]) i++;
       a[j] = a[i];
    }
    a[i] = x;
    QSort(low, i-1);
    QSort(i+1, hign);
}

int main()
{
    QSort(0, size - 1);
    for(unsigned int i = 0; i<size; i++) {
     std::cout << a[i] << std::endl;
    }
   
}
