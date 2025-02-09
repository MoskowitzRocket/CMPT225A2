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

    std::cout << h1.getSize() << std::endl;

    h1.ddisplay();

    std::cout << h1.getVal(5) << std::endl;
    std::cout << h1.containsKey(4) << std::endl;
    


    h1.makeEmpty();
    std::cout << h1.getSize() << std::endl;
    h1.ddisplay();

    system("clear");

    BiMap<std::string,int> h2;

    h2.insert("One", 1);
    h2.insert("Two", 2);
    h2.insert("Three",3);
    h2.ddisplay();
    h2.removeKey("Two");
    h2.ddisplay();
    h2.insert("Two", 2);
    h2.ddisplay();

    std::cout << h2.getVal("One") << std::endl;
    

    return 0;

    
}