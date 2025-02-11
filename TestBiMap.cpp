#include <iostream>
#include "BiMap.h"
using namespace std;

    // Simple main
int main( )
{
    BiMap<int,std::string> h1;
    BiMap<int,std::string> h2;

    h1.ddisplay();

    h1.insert(5,"Five");
    h1.ddisplay();

    cout << h1.containsKey(5) << endl;
    cout << h1.getSize() << endl;
    cout << "Val corresponding to key 5: " << h1.getVal(5) << endl;

    cout << "Key corresponding to Five: " << h1.getKey("Five") << endl;

    cout << "TEST";

    BiMap<int,int> p;

    p.insert(5,5);
    p.ddisplay();
    cout << "Val corresponding to key 5: " << p.getVal(5) << endl;
    cout << "Key corresponding to val 5: " << p.getKey(5) << endl;

    p.insert(3,3);
    p.insert(23,23);
    cout << p.getSize() << endl;

    p.ddisplay();
    cout <<"Removing 23\n";
    p.removeKey(23);
    //can still get val after removing key 
    cout << p.getVal(23) << endl;

    p.ddisplay();

    cout << "removing value 3\n";
    p.removeVal(3);
    p.ddisplay();
    cout << p.getSize() << endl;
    return 0;
}
