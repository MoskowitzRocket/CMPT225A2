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
    cout << "b1 after insertions (display):\n";
    b1.display();  // Simple display
    cout << "b1 after insertions (ddisplay):\n";
    b1.ddisplay(); // Detailed display

    cout << "Contains key 2? " << b1.containsKey(2) << endl;
    cout << "Contains value 300? " << b1.containsVal(300) << endl;

    cout << "Value for key 1: " << b1.getVal(1) << endl;
    cout << "Removing key 2..." << endl;
    b1.removeKey(2);
    cout << "b1 after removal (display):\n";
    b1.display();  // Simple display
    cout << "b1 after removal (ddisplay):\n";
    b1.ddisplay(); // Detailed display

    // Integer to String BiMap
    BiMap<int, std::string> b2;
    b2.insert(1, "Alice");
    b2.insert(2, "Bob");
    b2.insert(3, "Charlie");

    cout << "\nb2 after insertions (display):\n";
    b2.display();  // Simple display
    cout << "b2 after insertions (ddisplay):\n";
    b2.ddisplay(); // Detailed display

    cout << "Contains key 3? " << b2.containsKey(3) << endl;
    cout << "Contains value 'Bob'? " << b2.containsVal("Bob") << endl;

    cout << "Value for key 1: " << b2.getVal(1) << endl;
    cout << "Removing value 'Charlie'..." << endl;
    b2.removeVal("Charlie");
    cout << "b2 after removal (display):\n";
    b2.display();  // Simple display
    cout << "b2 after removal (ddisplay):\n";
    b2.ddisplay(); // Detailed display

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
    b3.insert('E', 50);
    b3.insert('F', 60);

    cout << "\nb3 after additional insertions (display):\n";
    b3.display();  // Simple display
    cout << "b3 after additional insertions (ddisplay):\n";
    b3.ddisplay(); // Detailed display

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
    
    //testBiMap();
    
    BiMap<char, int> b4;

    b4.insert('a',1);
    b4.insert('b',2);
    b4.insert('c',3);
    b4.insert('d',4);
    b4.insert('e',5);
    b4.insert('f',6);
    b4.insert('g',7);
    b4.insert('h',8);
    b4.insert('i',9);
    b4.insert('j',10);
    b4.insert('k',11);

    b4.display(); b4.ddisplay();

    return 0;
}
