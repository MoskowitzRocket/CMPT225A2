#include <vector>
#include <algorithm>
#include <functional>
#include <string>
#include <iostream>
using namespace std;

int nextPrime(int n );

// Bijective Map class
// Implemented with two hash tables.
template <typename KeyType, typename ValType> //
class BiMap
{
public:
    BiMap() : keyToVal(), valToKey()
    {
    }
    // constructor
    void makeEmpty()
    {
        keyToVal.makeEmpty();
        valToKey.makeEmpty();
    }
    // remove all pairs
    int getSize() const
    {
        return keyToVal.getSize(); // Return instead of printing
    }

    // returns the current number of pairs
    bool insert(const KeyType &x, const ValType &y)
    {
        if (keyToVal.contains(x) || valToKey.contains(y))
            return false; // Prevent duplicate keys/values

        keyToVal.insert(x, y);
        valToKey.insert(y, x);
        return true;
    }

    // insert pair <x,y>, provided x is not the
    // key of a current pair and y is not the value of
    // a current pair.  Return true iff <x,y> was inserted.
    bool containsKey(const KeyType &x) const
    {
        return keyToVal.contains(x); // Return the result
    }

    bool containsVal(const ValType &x) const
    {
        return valToKey.contains(x); // Return the result
    }

    bool removeKey(const KeyType &x)
    {
        if (!keyToVal.contains(x)) // Check if key exists
            return false;

        ValType val = keyToVal.getValue(x); // Get the associated value
        keyToVal.remove(x);                 // Remove from key-to-value map
        valToKey.remove(val);               // Remove from value-to-key map

        return true;
    }

    bool removeVal(const ValType &x)
    {
        if (!valToKey.contains(x)) // Check if value exists
            return false;

        KeyType key = valToKey.getValue(x); // Get the associated key
        valToKey.remove(x);                 // Remove from value-to-key map
        keyToVal.remove(key);               // Remove from key-to-value map

        return true;
    }

    const ValType &getVal(const KeyType &x) const
    {
        if (!keyToVal.contains(x))
            throw runtime_error("Key not found!");

        return keyToVal.getValue(x); // Assuming HMap provides getValue()
    }

    const KeyType &getKey(const ValType &x) const
    {
        if (!valToKey.contains(x))
            throw runtime_error("Value not found!");

        return valToKey.getValue(x); // Assuming HMap provides getValue()
    }

    void display()
    {
        keyToVal.display();
    }

    void ddisplay()
    {
        cout << "Key to Val Array\n";
        keyToVal.ddisplay();
        cout << "Val to Key Array\n";
        valToKey.ddisplay();
    }

private:

    template <typename kt, typename vt>
    class HMap
    {
    public:
        explicit HMap(int size = 11) : array(nextPrime(size))
        {
            makeEmpty();
        }

        bool contains(const kt &x) const
        {
            return isActive(findPos(x));
        }

        void makeEmpty()
        {
            currentSize = 0;
            for (auto &entry : array)
                entry.info = EMPTY;
        }

        int getSize() const
        {
            return currentSize;
        }

        bool insert(const kt &x, const vt &y)
        {
            // Insert x as active
            int currentPos = findPos(x);
            if (isActive(currentPos))
                return false;

            if (array[currentPos].info != DELETED)
                ++currentSize;

            array[currentPos].key = x;
            array[currentPos].value = y;
            array[currentPos].info = ACTIVE;

            // Rehash; see Section 5.5
            if (currentSize > array.size() / 2)
                rehash();

            return true;
        }

        bool insert(kt &&x)
        {
            // Insert x as active
            int currentPos = findPos(x);
            if (isActive(currentPos))
                return false;

            if (array[currentPos].info != DELETED)
                ++currentSize;

            array[currentPos] = std::move(x);
            array[currentPos].info = ACTIVE;

            // Rehash; see Section 5.5
            if (currentSize > array.size() / 2)
                rehash();

            return true;
        }

        bool remove(const kt &x)
        {
            int currentPos = findPos(x);
            if (!isActive(currentPos))
                return false;

            array[currentPos].info = DELETED;
            return true;
        }

        const vt &getValue(const kt &x) const
        {
            int pos = findPos(x); // Find the index of the key in the hash table
            return array[pos].value;
        }

        enum EntryType
        {
            ACTIVE,
            EMPTY,
            DELETED
        };

        void display()
        {
            for (const auto &entry : array)
            {
                if (entry.info == ACTIVE)
                    cout << "(" << entry.key << "," << entry.value << ") ";
            }
            cout << endl;
        }

        void ddisplay()
        {
            {
                cout << "Index\tStatus\tFirst\tSecond" << endl;
                for (size_t i = 0; i < array.size(); ++i)
                {
                    cout << i << "\t";
                    switch (array[i].info)
                    {
                    case ACTIVE:
                        cout << "ACTIVE\t" << array[i].key << "\t" << array[i].value;
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
        }

    private:
        struct HashEntry
        {
            kt key;
            vt value;
            EntryType info;

            HashEntry(const kt &e = kt{}, EntryType i = EMPTY)
                : key{e}, info{i} {}

            HashEntry(kt &&e, EntryType i = EMPTY)
                : key{std::move(e)}, info{i} {}
        };

        vector<HashEntry> array;
        int currentSize;

        bool isActive(int currentPos) const
        {
            return array[currentPos].info == ACTIVE;
        }

        int findPos(const kt &x) const
        {
            int offset = 1;
            int currentPos = myhash(x);

            while (array[currentPos].info != EMPTY &&
                   array[currentPos].key != x)
            {
                currentPos += offset; // Compute ith probe
                offset += 2;
                if (currentPos >= array.size())
                    currentPos -= array.size();
            }

            return currentPos;
        }

        void rehash()
        {
            vector<HashEntry> oldArray = array;

            // Create new double-sized, empty table
            array.resize(nextPrime(2 * oldArray.size()));
            for (auto &entry : array)
                entry.info = EMPTY;

            // Copy table over
            currentSize = 0;
            for (auto &entry : oldArray)
                if (entry.info == ACTIVE)
                    insert(std::move(entry.key));
        }

        size_t myhash(const kt &x) const
        {
            static hash<kt> hf;
            return hf(x) % array.size();
        }
    };

    HMap<KeyType, ValType> keyToVal;
    HMap<ValType, KeyType> valToKey;

    int currentSize;
};
