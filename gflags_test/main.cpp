#pragma warning(disable:4251) 
#pragma warning(disable:4996) 


#include "gflags/gflags.h"


DEFINE_string(languages, "english,french,german",
              "comma-separated list of languages to offer in the 'lang' menu");

#include <iostream>

int main(){
    
    std::cout<<FLAGS_languages<<std::endl;

    getchar();
    return 0;
}

