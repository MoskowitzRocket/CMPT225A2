#ifndef QUADRATIC_PROBING_H
#define QUADRATIC_PROBING_H

#include <vector>
#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
using namespace std;

int nextPrime(int n);

// QuadraticProbing Hash table 
//
// CONSTRUCTION: an approximate initial size or default of 101
//
// ******************PUBLIC OPERATIONS*********************
// bool insert( x )       --> Insert x
// bool removeKey( x )       --> Remove x
// bool containsKey( x )     --> Return true if x is present
// void makeEmpty( )      --> Remove all items
// int hashCode( string str ) --> Global method to hash strings

template <typename KeyType, typename ValType>
class BiMap
{
public:

    //Constructor
    //Sizes array to next prime greater than size -> default 101
    //Then sets all entries to 0

    explicit BiMap(int size = 11) : array(nextPrime(size)), valArray(nextPrime(size))
    {
        makeEmpty();
    }

    //sets current size to 0 and sets all array firsts to EMPTY
    void makeEmpty()
    {
        currentSize = 0;
        for (auto& entry : array)
            entry.info = EMPTY;

        for (auto& entry : valArray)
            entry.info = EMPTY;
    }

    int getSize() const
    {
        return currentSize;
    }

    bool insert(const KeyType& x, const ValType& y)
    {
        // Insert x as active
        int currentPos = findPosKey(x);
        int currentPosVal = findPosVal(y);

        //int currentPosVal = findPosVal( y );

        if (isActive(currentPos, array) || isActive(currentPosVal, valArray))
        {
            return false;
        }

        if (array[currentPos].info != DELETED && valArray[currentPosVal].info != DELETED) {
            ++currentSize;
        }


        array[currentPos].first = x;
        array[currentPos].second = y;
        array[currentPos].info = ACTIVE;

        valArray[currentPosVal].first = x;
        valArray[currentPosVal].second = y;
        valArray[currentPosVal].info = ACTIVE;

        // Rehash; see Section 5.5
        if (currentSize > array.size() / 2) {
            rehash();
        }

        return true;
    }

    //calls find pos to find index of x
    //uses is active to make sure its ACTIVE -> not deleted or empty

    bool containsKey(const KeyType& x) const
    {
        int pos = findPosKey(x);
        return isActive(pos, array);
    }

    bool containsVal(const ValType& y) const
    {
        //TODO
        int pos = findPosVal(y);
        return isActive(pos, valArray);
    }

    bool removeKey(const KeyType& x)
    {
        int currentPos = findPosKey(x);
        if (!isActive(currentPos, array))
            return false;

        // Remove value associated with the key
        ValType temp = array[currentPos].second;
        array[currentPos].info = DELETED;  // Mark the key as DELETED first

        // Now, safely remove the value from valArray
        removeVal(temp);
        
        return true;
    }

    bool removeVal(const ValType& y)
    {
        int currentPos = findPosVal(y);
        if (!isActive(currentPos, valArray))
            return false;

        // Remove key associated with the value
        KeyType temp = valArray[currentPos].first;
        valArray[currentPos].info = DELETED;  // Mark the value as DELETED first

        // Now, safely remove the key from array
        removeKey(temp);
        currentSize--;
        return true;
    }

    const ValType& getVal(const KeyType& x) const
    {
        int pos = findPosKey(x);
        return array[pos].second;
    }

    const KeyType& getKey(const ValType& y) const
    {
        int pos = findPosVal(y);
        return valArray[pos].first;
    }

    enum EntryType { ACTIVE, EMPTY, DELETED };

    void display()
        {
            for (const auto &entry : array)
            {
                if (entry.info == ACTIVE)
                    cout << "(" << entry.first << "," << entry.second << ") ";
            }
            cout << endl;
        }

    void ddisplay() const
    {
        cout << "KeyArray\n";
        cout << "Index\tStatus\tFirst\tSecond" << endl;
        for (size_t i = 0; i < array.size(); ++i)
        {
            cout << i << "\t";
            switch (array[i].info)
            {
            case ACTIVE:
                cout << "ACTIVE\t" << array[i].first << "\t" << array[i].second;
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
        for (size_t i = 0; i < valArray.size(); ++i)
        {
            cout << i << "\t";
            switch (valArray[i].info)
            {
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
    }

private:
    struct HashEntry
    {
        KeyType first;
        ValType second;
        EntryType info;

        HashEntry(const KeyType& e = KeyType{ }, EntryType i = EMPTY)
            : first{ e }, info{ i } {
        }

        HashEntry(KeyType&& e, EntryType i = EMPTY)
            : first{ std::move(e) }, info{ i } {
        }
    };

    vector<HashEntry> array;
    vector<HashEntry> valArray;
    int currentSize;

    bool isActive(int currentPos, const vector<HashEntry>& arr) const
    {
        return arr[currentPos].info == ACTIVE;
    }

    int findPosKey(const KeyType& x) const
    {
        int offset = 1;
        // int currentPos = myhashKey(x);
        int currentPos = myhash(x);
        while (array[currentPos].info != EMPTY &&
            array[currentPos].first != x)
        {
            currentPos += offset;  // Compute ith probe
            offset += 2;
            if (currentPos >= array.size())
                currentPos -= array.size();
        }

        return currentPos;
    }

    int findPosVal(const ValType& y) const
    {
        int offset = 1;
        //int currentPos = myhashVal(y);
        int currentPos = myhash(y);
        while (valArray[currentPos].info != EMPTY &&
            valArray[currentPos].second != y)
        {
            currentPos += offset;  // Compute ith probe
            offset += 2;
            if (currentPos >= valArray.size())
                currentPos -= valArray.size();
        }

        return currentPos;
    }



    void rehash()
    {
        vector<HashEntry> oldArray = array;
        vector<HashEntry> oldValArray = valArray;


        // Create new double-sized, empty table
        array.resize(nextPrime(2 * oldArray.size()));
        valArray.resize(nextPrime(2 * oldValArray.size()));

        for (auto& entry : array)
            entry.info = EMPTY;

        for (auto& entry : valArray)
            entry.info = EMPTY;

        // Copy table over
        currentSize = 0;
        for (auto& entry : oldArray)
            if (entry.info == ACTIVE)
                insert(std::move(entry.first), std::move(entry.second));

        for (auto& entry : oldValArray)
            if (entry.info == ACTIVE)
                insert(std::move(entry.first), std::move(entry.second));
    }

    size_t myhashKey(const KeyType& x) const
    {
        static hash<KeyType> hf;
        return hf(x) % array.size();
    }

    size_t myhashVal(const ValType& y) const
    {
        static hash<ValType> hf;
        return hf(y) % array.size();
    }
    //best way need to fix
    template <typename T>
    size_t myhash(const T& y) const
    {
        static hash<T> hf;
        return hf(y) % array.size();
    }

};

#endif
