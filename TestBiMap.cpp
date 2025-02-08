#include "BiMap.h"
#include <iostream>


int main(){

    BiMap<int,std::string> h1;

    std::cout << "Test"  << std::endl;

    h1.ddisplay();

    h1.insert(5,"hello");
    h1.insert(3,"test");
    h1.insert(67,"sixty-seven");
    h1.insert(67-11,"sixty-seven/2");
    h1.insert(45,"third");
    h1.insert(34,"fourth");


    h1.ddisplay();


    return 0;
}