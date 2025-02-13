#ifndef QUADRATIC_PROBING_H
#define QUADRATIC_PROBING_H

#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Function template for nextPrime
/*
    Purpose:
        returns next prime number greater than or equal to input 'n'

        used when rehashing the table.
*/
int nextPrime(int n);

// -----------------------------------------------------------------------------
// Class: BiMap
//
// Purpose:
//   Implements a bijective mapping between keys (KeyType) and values (ValType)
//   using two hash tables with quadratic probing. One table (keyArray) maps
//   keys to values, while the other (valArray) maps values back to keys. This
//   design enforces one-to-one correspondence between keys and values.
//
// Public Operations:
//   - makeEmpty()   : Clears all entries in the BiMap.
//   - getSize()     : Returns the number of active key-value pairs.
//   - insert(x, y)  : Inserts a unique key-value pair into the map.
//   - containsKey(x): Checks if the key exists in the map.
//   - containsVal(y): Checks if the value exists in the map.
//   - removeKey(x)  : Removes a key (and its associated value) from the map.
//   - removeVal(y)  : Removes a value (and its associated key) from the map.
//   - getVal(x)     : Returns the value associated with a key.
//   - getKey(y)     : Returns the key associated with a value.
//   - display()     : Displays active key-value pairs in a simple format.
//   - ddisplay()    : Displays detailed internal state of both hash tables.

template <typename KeyType, typename ValType> class BiMap {
public:
  // Constructor
  // Sizes keyArray and valArray to next prime greater than size -> default 101
  // Then sets all entries to 0

  explicit BiMap(int size = 11)
      : keyArray(nextPrime(size)), valArray(nextPrime(size)) {
    makeEmpty();
  }

  // Function: makeEmpty
  // sets current size to 0 and sets all keyArray elements to EMPTY
  void makeEmpty() {
    currentSize = 0;
    for (auto &entry : keyArray)
      entry.info = EMPTY;

    for (auto &entry : valArray)
      entry.info = EMPTY;
  }

  // Function: getSize
  // returns number of elements in the biMap
  int getSize() const { return currentSize; }

  // function insert
  /*
      Inserts a new key-value pair (x, y) into the BiMap if both the key and
     value are unique. True if the insertion is successful, false if either the
     key or value already exists.
  */
  bool insert(const KeyType &x, const ValType &y) {
    // Insert x as active
    int currentPos = findPosKey(x);
    int currentPosVal = findPosVal(y);

    // int currentPosVal = findPosVal( y );

    if (isActive(currentPos, keyArray) || isActive(currentPosVal, valArray)) {
      return false;
    }

    if (keyArray[currentPos].info != DELETED &&
        valArray[currentPosVal].info != DELETED) {
      ++currentSize;
    }

    keyArray[currentPos].first = x;
    keyArray[currentPos].second = y;
    keyArray[currentPos].info = ACTIVE;

    valArray[currentPosVal].first = x;
    valArray[currentPosVal].second = y;
    valArray[currentPosVal].info = ACTIVE;

    // Rehash; see Section 5.5
    if (currentSize > static_cast<int>(keyArray.size() / 2)) {
      rehash();
    }

    return true;
  }

  // function: containsKey
  // checks to see if the BiMap contains the key x
  bool containsKey(const KeyType &x) const {
    int pos = findPosKey(x);
    return isActive(pos, keyArray);
  }

  // function: containsVal
  // checks to see if the BiMap contains the val y
  bool containsVal(const ValType &y) const {
    // TODO
    int pos = findPosVal(y);
    return isActive(pos, valArray);
  }

  // Function: removeVal
  /*
      removes the (key, val) pair with key x
  */
  bool removeKey(const KeyType &x) {
    int currentPos = findPosKey(x);
    if (!isActive(currentPos, keyArray))
      return false;

    // Remove value associated with the key
    ValType temp = keyArray[currentPos].second;
    keyArray[currentPos].info = DELETED; // Mark the key as DELETED first

    // Now, safely remove the value from valArray
    removeVal(temp);

    return true;
  }

  // Function: removeKey
  /*
      removes the (key, val) pair with val y
  */
  bool removeVal(const ValType &y) {
    int currentPos = findPosVal(y);
    if (!isActive(currentPos, valArray))
      return false;

    // Remove key associated with the value
    KeyType temp = valArray[currentPos].first;
    valArray[currentPos].info = DELETED; // Mark the value as DELETED first

    // Now, safely remove the key from keyArray
    removeKey(temp);
    currentSize--;
    return true;
  }

  // function: getVal
  /*
      returns the corresponding val to key input x
  */
  const ValType &getVal(const KeyType &x) const {
    int pos = findPosKey(x);
    return keyArray[pos].second;
  }

  // function: getKey
  /*
      returns the corresponding key to val input y
  */
  const KeyType &getKey(const ValType &y) const {
    int pos = findPosVal(y);
    return valArray[pos].first;
  }

  // Enum: EntryType
  /*
      represents status of each slot in hashtable
      Active -> value held
      Empty -> neverused
      DELETED -> used to have element but it was removed

  */
  enum EntryType { ACTIVE, EMPTY, DELETED };

  // Function: display
  /*
      prints out all (key, val) pairs in the map
  */
  void display() {
    for (const auto &entry : keyArray) {
      if (entry.info == ACTIVE)
        cout << "(" << entry.first << "," << entry.second << ") ";
    }
    cout << endl;
  }

  // function: ddisplay()
  /*
      shows entire contents of keyArray -> prints out status, key and value or
     all
  */
  void ddisplay() const {
    cout << "KeyArray\n";
    cout << "Index\tStatus\tFirst\tSecond" << endl;
    for (size_t i = 0; i < keyArray.size(); ++i) {
      cout << i << "\t";
      switch (keyArray[i].info) {
      case ACTIVE:
        cout << "ACTIVE\t" << keyArray[i].first << "\t" << keyArray[i].second;
        break;
      case EMPTY:
        cout << "EMPTY\t-\t-";
        break;
      case DELETED:
        cout << "DELETED\t-\t-";
        break;
      }
      cout << endl;
    }
    cout << "ValArray\n";
    cout << "Index\tStatus\tFirst\tSecond" << endl;
    for (size_t i = 0; i < valArray.size(); ++i) {
      cout << i << "\t";
      switch (valArray[i].info) {
      case ACTIVE:
        cout << "ACTIVE\t" << valArray[i].first << "\t" << valArray[i].second;
        break;
      case EMPTY:
        cout << "EMPTY\t-\t-";
        break;
      case DELETED:
        cout << "DELETED\t-\t-";
        break;
      }
      cout << endl;
    }
    cout << "Current Size:\t" << currentSize << endl;
  }

private:
  // struct: HashEntry
  /*
      represents single element in hash table -> keyArray is filled with
     hashEntries

      element -> stored element
      info -> its status, ACTIVE, EMPTY, or DELETED
  */
  struct HashEntry {
    KeyType first;
    ValType second;
    EntryType info;

    HashEntry(const KeyType &e = KeyType{}, EntryType i = EMPTY)
        : first{e}, info{i} {}

    HashEntry(KeyType &&e, EntryType i = EMPTY)
        : first{std::move(e)}, info{i} {}
  };

  vector<HashEntry> keyArray; // contains keyArray with pairs hashed by key
  vector<HashEntry> valArray; // contains valArray with pairs hashed by val
  int currentSize;            // # of pairs in BiMap

  // Function: isActive
  /*
      checks to see if slot at input index is active in input array
  */
  bool isActive(int currentPos, const vector<HashEntry> &arr) const {
    return arr[currentPos].info == ACTIVE;
  }

  // Function: findPosKey
  /*
      locates position in keyArray of provided element x
  */
  int findPosKey(const KeyType &x) const {
    int offset = 1;
    int currentPos = myhash(x);
    while (keyArray[currentPos].info != EMPTY &&
           keyArray[currentPos].first != x) {
      currentPos += offset; // Compute ith probe
      offset += 2;
      if (currentPos >= static_cast<int>(keyArray.size()))
        currentPos -= static_cast<int>(keyArray.size());
    }

    return currentPos;
  }

  // Function: findPosVal
  /*
      locates position in valArray of provided element x
  */
  int findPosVal(const ValType &y) const {
    int offset = 1;
    int currentPos = myhash(y);
    while (valArray[currentPos].info != EMPTY &&
           valArray[currentPos].second != y) {
      currentPos += offset; // Compute ith probe
      offset += 2;
      if (currentPos >= static_cast<int>(valArray.size()))
        currentPos -= static_cast<int>(valArray.size());
    }

    return currentPos;
  }

  // function: rehash
  /*
      Resizes the hash table to a larger size (next prime after doubling) and
    re-inserts all active elements from the old table into the new table.
  */
  void rehash() {
    vector<HashEntry> oldArray = keyArray;
    vector<HashEntry> oldValArray = valArray;

    // Create new double-sized, empty table
    keyArray.resize(nextPrime(2 * oldArray.size()));
    valArray.resize(nextPrime(2 * oldValArray.size()));

    for (auto &entry : keyArray)
      entry.info = EMPTY;

    for (auto &entry : valArray)
      entry.info = EMPTY;

    // Copy table over
    currentSize = 0;
    for (auto &entry : oldArray)
      if (entry.info == ACTIVE)
        insert(std::move(entry.first), std::move(entry.second));

    for (auto &entry : oldValArray)
      if (entry.info == ACTIVE)
        insert(std::move(entry.first), std::move(entry.second));
  }

  // function: myHash
  /*
      Computes the hash value for the element x using the standard hash function
      setup as a template so that it can take in either a KeyType or a ValType

  */
  template <typename T> size_t myhash(const T &y) const {
    static hash<T> hf;
    return hf(y) % keyArray.size();
  }
};

#endif
