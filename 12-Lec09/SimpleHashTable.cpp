// CPP program to implement hashing with chaining
#include <iostream>
#include <string>
#include <vector>
#include <list>
using namespace std;


class Hash
{
private:

	int BUCKET;  // # of buckets
    int ITEM;       // # of items
	list<int> *table;	// Pointer to an array containing buckets
    void grow();   // grow the size of slots by 2
    void shrink(); // shrink the size of slots to 1/4 of the originial size 

public:

	Hash(int b); // Constructor
    ~Hash();     

	// inserts a key into hash table
	void insertItem(const int x) ;

	// deletes a key from hash table
	bool deleteItem(const int key) ;

	// hash function to map values to key
	const int hashFunction(const int x) const{ return (x % BUCKET); }

	void displayHash() const;

};

Hash::Hash(int b)
:BUCKET(b)
{
    table = new list<int>[b];
}

Hash::~Hash()
{
    delete[] table;
}

void Hash::insertItem(int key)
{
	int index = hashFunction(key);
	table[index].push_back(key);
    ITEM++;
    if(ITEM > BUCKET)
        grow();
}

bool Hash::deleteItem(int key)
{
    // get the hash index of key
    int index = hashFunction(key);

    // find the key in (inex)th list
    list <int> :: iterator i;
    for (i = table[index].begin(); i != table[index].end(); i++) {
        if (*i == key)
            break;
    }

    // if key is found in hash table, remove it
    if (i != table[index].end())
    {
        table[index].erase(i);
        ITEM--;
        if(ITEM < BUCKET/4) 
            shrink();
        return true;
    }
    else 
    {
        return false;
    }
}

void Hash::grow()
{
    list<int> *tmp = table;
    table = new list<int>[BUCKET*2];
    ITEM = 0;
    BUCKET*=2;
    for (int i = 0; i < BUCKET/2; i++) {
        for (auto x : tmp[i])
            insertItem(x);
    }
    delete[] tmp;
}

void Hash::shrink()
{
    list<int> *tmp = table;
    table = new list<int>[BUCKET/2];
    ITEM = 0;
    BUCKET/=2;
    for (int i = 0; i < BUCKET*2; i++) {
        for (auto x : tmp[i])
            insertItem(x);
    }
    delete[] tmp;
}

// function to display hash table
void Hash::displayHash() const{
    cout<<"-----------------"<<endl;
    for (int i = 0; i < BUCKET; i++) {
        cout << i;
        for (auto x : table[i])
            cout << " --> " << x;
            cout << endl;
    }
}

int main()
{
    // array that contains keys to be mapped
    int a[] = {15, 11, 27, 8, 12};
    int n = sizeof(a)/sizeof(a[0]);

    // insert the keys into the hash table
    Hash h(1); 
    for (int i = 0; i < n; i++)
        h.insertItem(a[i]);

    // delete 12 from hash table
    h.deleteItem(12);

    h.insertItem(1);
    h.insertItem(2);
    // display the Hash table
    h.displayHash();

    h.insertItem(3);
    h.insertItem(4);

    h.displayHash();

    h.deleteItem(3);
    h.deleteItem(4);
    h.deleteItem(1);
    h.deleteItem(2);
    h.deleteItem(8);
    h.deleteItem(15);
    h.deleteItem(11);

    h.displayHash();

    return 0;
}
