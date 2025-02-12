#include <iostream>
#include "BiMap.h"
using namespace std;


void testBiMap()
{
    // Char to Int BiMap (updated b3)
    BiMap<char, int> b3;
    b3.insert('A', 10);
    b3.insert('B', 20);
    b3.insert('C', 30);

    cout << "\nb3 after initial insertions (display):\n";
    b3.display();  // Simple display
    cout << "b3 after initial insertions (ddisplay):\n";
    b3.ddisplay(); // Detailed display

    // Add more values to trigger rehashing and array expansion
    b3.insert('D', 40);
    cout << "\nAdded 'D' to b3 (display):\n";
    b3.display();
    b3.ddisplay();

    b3.insert('E', 50);
    cout << "\nAdded 'E' to b3 (display):\n";
    b3.display();
    b3.ddisplay();

    b3.insert('F', 60);
    cout << "\nAdded 'F' to b3 (display):\n";
    b3.display();
    b3.ddisplay();

    cout << "\nAfter adding several items, check internal structure (ddisplay):\n";
    b3.ddisplay(); // Detailed display, showing internal hash table structure

    cout << "Contains key 'B'? " << b3.containsKey('B') << endl;
    cout << "Contains value 30? " << b3.containsVal(30) << endl;

    cout << "Value for key 'A': " << b3.getVal('A') << endl;
    cout << "Removing key 'C'..." << endl;
    b3.removeKey('C');
    cout << "b3 after removal (display):\n";
    b3.display();  // Simple display
    cout << "b3 after removal (ddisplay):\n";
    b3.ddisplay(); // Detailed display
}

    // Simple main
int main( )
{

    testBiMap();
    // BiMap<int,std::string> h1;
    // BiMap<int,std::string> h2;

    // h1.ddisplay();

    // h1.insert(5,"Five");
    // h1.ddisplay();

    // cout << h1.containsKey(5) << endl;
    // cout << h1.getSize() << endl;
    // cout << "Val corresponding to key 5: " << h1.getVal(5) << endl;

    // cout << "Key corresponding to Five: " << h1.getKey("Five") << endl;

    // cout << "TEST";

    // BiMap<int,int> p;

    // p.insert(5,5);
    // p.ddisplay();
    // cout << "Val corresponding to key 5: " << p.getVal(5) << endl;
    // cout << "Key corresponding to val 5: " << p.getKey(5) << endl;

    // p.insert(3,3);
    // p.insert(23,23);
    // cout << p.getSize() << endl;

    // p.ddisplay();
    // cout <<"Removing 23\n";
    // p.removeKey(23);
    // //can still get val after removing key 
    // cout << p.getVal(23) << endl;

    // p.ddisplay();

    // cout << "removing value 3\n";
    // p.removeVal(3);
    // p.ddisplay();
    // cout << p.getSize() << endl;
    return 0;
}
