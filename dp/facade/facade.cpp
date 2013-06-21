#include <iostream>
using namespace std;

class Scanner
{
public:
  void Scan() {
      cout<< "词法分析"<<endl;
  }
};

class Parser
{
public:
    void Parse() {
	cout<<"语法分析"<<endl;
    }
};

class GenMidCode
{
public:
    void GenCode() {
      cout<<"产生中间代码"<<endl;
    }
};

class GenMachineCode
{
public:
    void GenCode() {
	cout<<"产生机器代码"<<endl;
    }
};

class Compiler
{
public:
    void Run() {
	Scanner scanner;
	scanner.Scan();
	Parser parser;
	parser.Parse();
	GenMidCode midcode;
	midcode.GenCode();
	GenMachineCode machneCode;
	machneCode.GenCode();
    }
};  


int main() {
    Compiler compiler;
    compiler.Run();
    return 0;
}
    