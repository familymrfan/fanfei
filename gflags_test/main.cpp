#pragma warning(disable:4251) 
#pragma warning(disable:4996) 

//#define STRIP_FLAG_HELP 1
#include "gflags/gflags.h"
#include "stdint.h"
#include <stdlib.h>

using namespace GOOGLE_NAMESPACE;

DEFINE_string(languages, "english,french,german",
              "comma-separated list of languages to offer in the 'lang' menu");

static bool ValidatePort(const char* flagname, int32_t value) {
    if (value > 0 && value < 32768)   // value is ok
        return true;
    printf("Invalid value for --%s: %d\n", flagname, (int)value);
    return false;
}

DEFINE_string(name, "", "What port to listen on");
DEFINE_string(q, "", "What port to listen on");
DEFINE_string(p, "", "What port to listen on");
DEFINE_int32(port, 10, "What port to listen on");
static const bool port_dummy = RegisterFlagValidator(&FLAGS_port, &ValidatePort);

#include <iostream>

int main(int argc, char* argv[]){
    std::cout<<FLAGS_languages<<std::endl;
    std::cout<<FLAGS_port<<std::endl;
    {
      FlagSaver fs;
      SetCommandLineOption("port","20");
      std::cout<<FLAGS_port<<std::endl;
      SetCommandLineOption("port","0");
      std::cout<<FLAGS_port<<std::endl;
    }
    std::cout<<FLAGS_port<<std::endl;
    FLAGS_q = "heihei";
    
    // set environment
    setenv("FLAGS_name","fanfei",false);
    
    ParseCommandLineFlags(&argc, &argv, true);
    std::cout<<FLAGS_q<<std::endl;
    std::cout<<FLAGS_p<<std::endl;
    std::cout<<FLAGS_name<<std::endl;
    
    SetUsageMessage("happy every day");
    std::cout<<ProgramUsage()<<std::endl;
    getchar();
    return 0;
}

