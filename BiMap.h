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
    //Sizes array to next prime greater than size -> default 11
    //Then sets all entries to 0
    
    explicit BiMap( int size = 11 ) : array( nextPrime( size ) )
      { makeEmpty( ); }


    //calls find pos to find index of x
    //uses is active to make sure its ACTIVE -> not deleted or empty

    bool containsKey( const KeyType & x ) const
    {
        return isActive( findPos( x ) );
    }

    //sets current size to 0 and sets all array firsts to EMPTY
    void makeEmpty( )
    {
        currentSize = 0;
        for( auto & entry : array )
            entry.info = EMPTY;
    }

    //
    bool insert( const KeyType & x , const ValType & y)
    {
            // Insert x as active
        int currentPos = findPos( x );
        if( isActive( currentPos ) )
            return false;

        if( array[ currentPos ].info != DELETED )
            ++currentSize;

        array[ currentPos ].first = x;
        array[ currentPos ].info = ACTIVE;
        array[ currentPos ].second = y;

            // Rehash; see Section 5.5
        if( currentSize > array.size( ) / 2 )
            rehash( );

        return true;
    }
    
    bool insert( KeyType && x , ValType && y )
    {
            // Insert x as active
        int currentPos = findPos( x );
        if( isActive( currentPos ) )
            return false;

        if( array[ currentPos ].info != DELETED )
            ++currentSize;

        array[ currentPos ].first = std::move( x );
        array[ currentPos ].info = ACTIVE;
        array[ currentPos ].second = std::move( y );
        


            // Rehash; see Section 5.5
        if( currentSize > array.size( ) / 2 )
            rehash( );

        return true;
    }

    bool removeKey( const KeyType & x )
    {
        int currentPos = findPos( x );
        if( !isActive( currentPos ) )
            return false;

        array[ currentPos ].info = DELETED;
        return true;
    }

    enum EntryType { ACTIVE, EMPTY, DELETED };

    const ValType& getVal( const KeyType & x ) const 
    {
        int pos = findPos( x );

        return array[ pos ].second;
    }
    

    void ddisplay() const
    {
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
    }

  private:
    struct HashEntry
    {
        KeyType first;
        EntryType info;
        ValType second;

        HashEntry( const KeyType & e = KeyType{ }, EntryType i = EMPTY )
          : first{ e }, info{ i } { }
        
        HashEntry( KeyType && e, EntryType i = EMPTY )
          : first{ std::move( e ) }, info{ i } { }
    };
    
    vector<HashEntry> array;
    int currentSize;

    bool isActive( int currentPos ) const
      { return array[ currentPos ].info == ACTIVE; }

    int findPos( const KeyType & x ) const
    {
        int offset = 1;
        int currentPos = myhash( x );

        while( array[ currentPos ].info != EMPTY &&
               array[ currentPos ].first != x )
        {
            currentPos += offset;  // Compute ith probe
            offset += 2;
            if( currentPos >= array.size( ) )
                currentPos -= array.size( );
        }

        return currentPos;
    }

    void rehash( )
    {
        vector<HashEntry> oldArray = array;

            // Create new double-sized, empty table
        array.resize( nextPrime( 2 * oldArray.size( ) ) );
        for( auto & entry : array )
            entry.info = EMPTY;

            // Copy table over
        currentSize = 0;
        for( auto & entry : oldArray )
            if( entry.info == ACTIVE )
                insert( std::move( entry.first), std::move( entry.second) );
    }

    size_t myhash( const KeyType & x ) const
    {
        static hash<KeyType> hf;
        return hf( x ) % array.size( );
    }
};

#endif
