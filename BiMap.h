#ifndef QUADRATIC_PROBING_H
#define QUADRATIC_PROBING_H

#include <vector>
#include <algorithm>
#include <functional>
#include <string>
#include <iostream>
using namespace std;

int nextPrime( int n );

// QuadraticProbing Hash table class
//
// CONSTRUCTION: an approximate initial size or default of 101
//
// ******************PUBLIC OPERATIONS*********************
// bool insertKey( x )       --> Insert key X
// bool removeKey( x )       --> Remove key X
// bool contains( x )     --> Return true if x is present
// void makeEmpty( )      --> Remove all items
// int hashCode( string str ) --> Global method to hash strings

template <typename KeyType, typename ValType>
class BiMap
{
  public:

    //Constructor
    //Sizes keyArray to next prime greater than size -> default 11
    //Then sets all entries to 0
    
    explicit BiMap( int size = 11 ) : keyArray( nextPrime( size ) ), valueArray( nextPrime( size ) )
      { makeEmpty( ); }


    //calls find pos to find index of x
    //uses is active to make sure its ACTIVE -> not deleted or empty

    bool containsKey( const KeyType & x ) const
    {
        return isActive( findKeyPos( x ) );
    }

    //TODO
    bool containsVal( const ValType & x) const
    {
        // return isActive( findValPos( x ) );
        for (const auto &entry : valueArray) {
            if (entry.info == ACTIVE && entry.second == x) {
                return true;
            }
        }
        return false;
    }
    

    //sets current size to 0 and sets all array info to EMPTY
    void makeEmpty( )
    {
        currentSize = 0;
        for( auto & entry : keyArray )
            entry.info = EMPTY;
        for( auto & entry : valueArray )
            entry.info = EMPTY;
    }

    int getSize() const 
    {
        return currentSize;
    }

    //
    bool insert( const KeyType & x , const ValType & y)
    {
            // Insert x as active
        int currentPos = findKeyPos( x );
        if( isActive( currentPos ) )
            return false;

        if( keyArray[ currentPos ].info != DELETED )
            ++currentSize;

        keyArray[ currentPos ].first = x;
        keyArray[ currentPos ].info = ACTIVE;
        keyArray[ currentPos ].second = y;

        valueArray[ currentPos ].first = x;
        valueArray[ currentPos ].info = ACTIVE;
        valueArray[ currentPos ].second = y;

            // Rehash; see Section 5.5
        if( currentSize > keyArray.size( ) / 2 )
            rehash( );

        return true;
    }
    
    // bool insert( KeyType && x , ValType && y )
    // {
    //         // Insert x as active
    //     int currentPos = findKeyPos( x );
    //     if( isActive( currentPos ) )
    //         return false;

    //     if( keyArray[ currentPos ].info != DELETED )
    //         ++currentSize;

    //     keyArray[ currentPos ].first = std::move( x );
    //     keyArray[ currentPos ].info = ACTIVE;
    //     keyArray[ currentPos ].second = std::move( y );

    //     valueArray[ currentPos ].first = std::move( x );
    //     valueArray[ currentPos ].info = ACTIVE;
    //     valueArray[ currentPos ].second = std::move( y );
        


    //         // Rehash; see Section 5.5
    //     if( currentSize > keyArray.size( ) / 2 )
    //         rehash( );

    //     return true;
    // }

    bool removeKey( const KeyType & x )
    {
        int currentPos = findKeyPos( x );
        if( !isActive( currentPos ) )
            return false;

        keyArray[ currentPos ].info = DELETED;
        valueArray[currentPos].info = DELETED;

        return true;
    }

    //TODO
    bool removeVal (const ValType & x)
    {
        int currentPos = findValPos( x );
        if( !isActive(currentPos)) 
            return false;
        keyArray[ currentPos ].info = DELETED;
        valueArray[currentPos].info = DELETED;
        return true;

    }

    enum EntryType { ACTIVE, EMPTY, DELETED };

    const ValType& getVal( const KeyType & x ) const 
    {
        int pos = findKeyPos( x );

        return keyArray[ pos ].second;
    }

    const KeyType& getKey( const ValType & x) const
    {
        int pos = findValPos( x );

        return valueArray[ pos ].first;
    }

    
    

    void ddisplay() const
    {
        cout << "Index\tStatus\tFirst\tSecond" << endl;
        for (size_t i = 0; i < keyArray.size(); ++i)
        {
            cout << i << "\t";
            switch (keyArray[i].info)
            {
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
        cout << "VALUE ARRAY:\n";
        cout << "Index\tStatus\tFirst\tSecond" << endl;
        for (size_t i = 0; i < valueArray.size(); ++i)
        {
            cout << i << "\t";
            switch (valueArray[i].info)
            {
            case ACTIVE:
                cout << "ACTIVE\t" << valueArray[i].first << "\t" << valueArray[i].second;
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
        EntryType info;
        ValType second;

        HashEntry( const KeyType & first = KeyType{ }, EntryType i = EMPTY, const ValType & second = ValType{ } )
          : first{ first }, info{ i }, second{ second} { }
        
          HashEntry(KeyType &&first, EntryType i, ValType &&second)
          : first{std::move(first)}, info{i}, second{std::move(second)} {}
  
        HashEntry(KeyType &&first, EntryType i = EMPTY)     
          : first{std::move(first)}, info{i}, second{} {}
    };
    
    vector<HashEntry> keyArray;

    vector<HashEntry> valueArray;

    

    int currentSize;

    bool isActive( int currentPos ) const
      { return keyArray[ currentPos ].info == ACTIVE; }


    int findKeyPos( const KeyType & x ) const
    {
        int offset = 1;
        int currentPos = myhash( x , keyArray);

        while( keyArray[ currentPos ].info != EMPTY &&
               keyArray[ currentPos ].first != x )
        {
            currentPos += offset;  // Compute ith probe
            offset += 2;
            if( currentPos >= keyArray.size( ) )
                currentPos -= keyArray.size( );
        }

        return currentPos;
    }

    int findValPos(const ValType & x) const
    {
        
        int offset = 1;
        int currentPos = myhash( x , valueArray);

        while( valueArray[ currentPos ].info != EMPTY &&
            valueArray[ currentPos ].second != x )
        {
            currentPos += offset;  // Compute ith probe
            offset += 2;
            if( currentPos >= valueArray.size( ) )
                currentPos -= valueArray.size( );
        }

        return currentPos;
    }

    void rehash( )
    {
        vector<HashEntry> oldKeyArray = keyArray;
        vector<HashEntry> oldValueArray = valueArray;

            // Create new double-sized, empty table
        keyArray.resize( nextPrime( 2 * oldKeyArray.size( ) ) );
        for( auto & entry : keyArray )
            entry.info = EMPTY;

        valueArray.resize( nextPrime( 2 * oldValueArray.size( ) ) );
        for( auto & entry : valueArray )
            entry.info = EMPTY;

            // Copy table over
        currentSize = 0;
        for( auto & entry : oldKeyArray )
            if( entry.info == ACTIVE )
                insert( std::move( entry.first), std::move( entry.second ) );

        for (auto & entry : oldValueArray)
            if (entry.info == ACTIVE ) 
                insert( std::move( entry.first), std::move( entry.second ) );
        
    }
    template <typename T>
    size_t myhash( const T & x, const vector<HashEntry> &arr) const
    {
        static hash<T> hf;
        return hf( x ) % arr.size( );
    }
};

#endif
