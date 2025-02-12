#include <iostream>
#include "BiMap.h"

#include <string>
using namespace std;

void testBiMap()
{
    // Integer to Integer BiMap
    BiMap<int, int> b1;
    b1.insert(1, 100);
    b1.insert(2, 200);
    b1.insert(3, 300);
    cout << "b1 after insertions:\n";
    b1.display();

    cout << "Contains key 2? " << b1.containsKey(2) << endl;
    cout << "Contains value 300? " << b1.containsVal(300) << endl;

    cout << "Value for key 1: " << b1.getVal(1) << endl;
    cout << "Removing key 2..." << endl;
    b1.removeKey(2);
    b1.display();

    // Integer to String BiMap
    BiMap<int, std::string> b2;
    b2.insert(1, "Alice");
    b2.insert(2, "Bob");
    b2.insert(3, "Charlie");

    cout << "\nb2 after insertions:\n";
    b2.display();

    cout << "Contains key 3? " << b2.containsKey(3) << endl;
    cout << "Contains value 'Bob'? " << b2.containsVal("Bob") << endl;

    cout << "Value for key 1: " << b2.getVal(1) << endl;
    cout << "Removing value 'Charlie'..." << endl;
    b2.removeVal("Charlie");
    b2.display();

    // Char to Float BiMap
    BiMap<char, float> b3;
    b3.insert('A', 3.14f);
    b3.insert('B', 2.71f);
    b3.insert('C', 1.61f);

    cout << "\nb3 after insertions:\n";
    b3.display();

    cout << "Contains key 'B'? " << b3.containsKey('B') << endl;
    cout << "Contains value 3.14? " << b3.containsVal(3.14f) << endl;

    cout << "Value for key 'A': " << b3.getVal('A') << endl;
    cout << "Removing key 'C'..." << endl;
    b3.removeKey('C');
    b3.display();
}


    // Simple main
int main( )
{
    
    testBiMap();
    // // HMap<int,std::string> h1;

    // // h1.insert(5,"Five");
    // // h1.insert(23,"Twenty-Three");

    // // h1.display();

    // // h1.ddisplay();

    // // cout << h1.getSize() << endl;

    // BiMap<int,std::string> b1;

    // b1.insert(5,"Five");

    // cout << b1.getSize() << endl;

    // b1.display();

    // b1.ddisplay();

    // cout << b1.containsKey(5) << endl;
    // cout << b1.containsVal("Five") << endl;

    // cout << b1.getKey("Five") << endl;
    // cout << b1.getVal(5) << endl;

    // b1.insert(25,"Twenty-Five");



    // b1.ddisplay();

    // b1.removeVal("Twenty-Five");
    // b1.removeKey(5);
    // b1.ddisplay();

    // for (int i = 0; i < 22; i++)
    // {
    //     b1.insert(i,std::to_string(i));
    // }
    // b1.ddisplay();

    return 0;
}
