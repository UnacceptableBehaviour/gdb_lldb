#include<iostream>

void Log(const char* msg){
    std::cout << msg << std::endl;
}

void Log(std::string msg){
    std::cout << msg << std::endl;
}
