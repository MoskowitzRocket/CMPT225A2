#ifndef QUADRATIC_PROBING_H
#define QUADRATIC_PROBING_H

#include <vector>
#include <algorithm>
#include <functional>
#include <string>
using namespace std;

//Function template for nextPrime
/*
    Purpose:
        returns next prime number greater than or equal to input 'n'
    
        used when rehashing the table.
*/
int nextPrime( int n );

// QuadraticProbing Hash table 
//
// CONSTRUCTION: an approximate initial size or default of 101
//
// ******************PUBLIC OPERATIONS*********************
// bool insert( x )       --> Insert x
// bool remove( x )       --> Remove x
// bool contains( x )     --> Return true if x is present
// void makeEmpty( )      --> Remove all items
// int hashCode( string str ) --> Global method to hash strings

template <typename HashedObj>
class HashTable
{
  public:

    //Constructor
    //Sizes array to next prime greater than size -> default 101
    //Then sets all entries to 0
    
    explicit HashTable( int size = 101 ) : array( nextPrime( size ) )
      { makeEmpty( ); }


    //Function: contains
    /*
        Purpose: checks to see if hash table contains element x
        returns true if found, false otherwise

    */
    bool contains( const HashedObj & x ) const
    {
        return isActive( findPos( x ) );
    }

    //Function: makeEmpty
    //sets current size to 0 and sets all array elements to EMPTY
    void makeEmpty( )
    {
        currentSize = 0;
        for( auto & entry : array )
            entry.info = EMPTY;
    }

    // Function: insert 
    /*
        inserts element X into hash table if not already present.

        returns true with succesful insert
    */
    bool insert( const HashedObj & x )
    {
            // Insert x as active
        int currentPos = findPos( x );
        if( isActive( currentPos ) )
            return false;

        if( array[ currentPos ].info != DELETED )
            ++currentSize;

        array[ currentPos ].element = x;
        array[ currentPos ].info = ACTIVE;

            // Rehash; see Section 5.5
        if( currentSize > array.size( ) / 2 )
            rehash( );

        return true;
    }
     // Function: insert 
    /*
        alternate implementation
        inserts element X into hash table if not already present.

        returns true with succesful insert
    */

    bool insert( HashedObj && x )
    {
            // Insert x as active
        int currentPos = findPos( x );
        if( isActive( currentPos ) )
            return false;

        if( array[ currentPos ].info != DELETED )
            ++currentSize;

        array[ currentPos ] = std::move( x );
        array[ currentPos ].info = ACTIVE;

            // Rehash; see Section 5.5
        if( currentSize > array.size( ) / 2 )
            rehash( );

        return true;
    }

    //fFunction: remove
    /*
        removes element x from the hash table by marking its slot as DELETED

        returns true if succesfully removing.
    
    
    */
    bool remove( const HashedObj & x )
    {
        int currentPos = findPos( x );
        if( !isActive( currentPos ) )
            return false;

        array[ currentPos ].info = DELETED;
        return true;
    }


    //Enum: EntryType
    /*
        represents status of each slot in hashtable
        Active -> value held 
        Empty -> neverused
        DELETED -> used to have element but it was removed

    */
    enum EntryType { ACTIVE, EMPTY, DELETED };

  private:
    //struct: HashEntry
    /*
        represents single element in hash table -> array is filled with hashEntries

        element -> stored element
        info -> its status, ACTIVE, EMPTY, or DELETED
    */
    struct HashEntry
    {
        HashedObj element;
        EntryType info;

        HashEntry( const HashedObj & e = HashedObj{ }, EntryType i = EMPTY )
          : element{ e }, info{ i } { }
        
        HashEntry( HashedObj && e, EntryType i = EMPTY )
          : element{ std::move( e ) }, info{ i } { }
    };
    

    vector<HashEntry> array; //array for hash table
    int currentSize;        //number of active elements in table

    //Function: isActive 
    /*
        checks to see if slot at input index is active

    */
    bool isActive( int currentPos ) const
      { return array[ currentPos ].info == ACTIVE; }

    //Function: findPos
    /*
        locates position in array of provided element x
    */
    int findPos( const HashedObj & x ) const
    {
        int offset = 1;
        int currentPos = myhash( x );

        while( array[ currentPos ].info != EMPTY &&
               array[ currentPos ].element != x )
        {
            currentPos += offset;  // Compute ith probe
            offset += 2;
            if( currentPos >= array.size( ) )
                currentPos -= array.size( );
        }

        return currentPos;
    }

    //function: rehash
    /*
        Resizes the hash table to a larger size (next prime after doubling) and re-inserts
      all active elements from the old table into the new table.
    */
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
                insert( std::move( entry.element ) );
    }


    //function: myHash
    /*
        Computes the hash value for the element x using the standard hash function
    */
    size_t myhash( const HashedObj & x ) const
    {
        static hash<HashedObj> hf;
        return hf( x ) % array.size( );
    }
};

#endif
