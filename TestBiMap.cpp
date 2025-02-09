#include "BiMap.h"
#include <iostream>


int main(){

    BiMap<int,std::string> h1;

    h1.insert(1,"One");

    h1.ddisplay();

    cout << h1.getSize() << endl;
    
    h1.makeEmpty();
    h1.ddisplay();
    
    h1.insert(1,"One");
    h1.insert(2,"Two");
    h1.insert(3,"Three");

    h1.ddisplay();

    cout << (h1.containsKey(1) ? "contains one" : "doesn't") << endl;

    cout << (h1.containsKey(4) ? "contains one" : "doesn't") << endl;

    cout << (h1.containsVal("One") ? "contains one" : "doesn't") << endl;
    cout << (h1.containsVal("Two") ? "contains one" : "doesn't") << endl;
    cout << (h1.containsVal("Three") ? "contains one" : "doesn't") << endl;

    h1.removeKey(1);
    h1.removeVal("Two");
    h1.insert(11,"Eleven");
    h1.ddisplay();

    cout << h1.getVal(11) << endl;
    cout << h1.getKey("Three") << endl;

    h1.insert(69,"Sixty-Nine");
    h1.ddisplay();

    cout << h1.getVal(69) << endl;
    cout << h1.getKey("Sixty-Nine") << endl;



    return 0;
    
}