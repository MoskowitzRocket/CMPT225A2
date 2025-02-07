// Bijective Map class 
// Implemented with two hash tables.
template < typename KeyType, typename ValType >  // 
class BiMap
{
  public:
    BiMap () 
	// constructor
    void makeEmpty( ) 
        // remove all pairs 
    int  getSize() const
        // returns the current number of pairs
    bool insert( const KeyType & x, const ValType & y )
        // insert pair <x,y>, provided x is not the 
	// key of a current pair and y is not the value of 
	// a current pair.  Return true iff <x,y> was inserted.
    bool containsKey( const  & KeyType x ) const 
        // returns true if x is the key of a current pair.
    bool containsVal( const  & ValType x ) const
        // returns true if x is the value of a current pair.
    bool removeKey( const KeyType & x )
        // removes the pair with key x if it exists.
    bool removeVal( const ValType & x )
        // removes the pair with values x if it exists.
    const & ValType getVal( const KeyType & x ) const 
        // returns the value associated with key x.
    const & KeyType getKey( const ValType & x ) const
        // returns the key associated with value x.


    private:

    
};