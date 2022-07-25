#include"Log.h"
#include<string>
//using namespace std

int Add(int a, int b){
    std::string params = "Add " + std::to_string(a) + "," + std::to_string(b);
    Log(params);
    return (a+b);
}

long int Mul(int a, int b){
    std::string params = "Mul " + std::to_string(a) + "," + std::to_string(b);
    Log(params);

    return (a*b);
}
