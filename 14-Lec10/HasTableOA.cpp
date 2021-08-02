#include <iostream>
#include <string>
#include <vector>
#include <list>
using namespace std;

enum OAHashState{UNUSED=0,USED,DELETED};

class Hash
{
private:

    int len;
    int num;
	pair<int,OAHashState>* table;	// Pointer to an array containing buckets
    void grow();   // grow the size of slots by 2
    void shrink(); // shrink the size of slots to 1/4 of the originial size 

public:

	Hash(const int len); // Constructor
    ~Hash();

	// inserts a key into hash table
	void insertItem(const int& key) ;

	// deletes a key from hash table
	void deleteItem(const int& key) ;

	// hash function to map values to key
	int hashFunction(const int& key, int i) const;

	void displayHash() const;

};

Hash::Hash(const int len)
:len(len),num(0)
{
    table = new pair<int,OAHashState>[len]();
}

Hash::~Hash()
{
    delete[] table;
}

void Hash::insertItem(const int& key)
{
    if(num+1 > len)
        grow();

    int index = 0;
    int count = 0;
    while(table[index].second==USED)
    {
        index = hashFunction(key,count++);
    }
	table[index] = make_pair(key,USED);
    num++;
    cout << "Insert"<< key <<endl;
}

void Hash::deleteItem(const int& key)
{
    int index;
    int count = 0;
    while(table[index].second!=USED || table[index].first!=key)
    {
        index = hashFunction(key,count++);
    }
    table[index].second = DELETED;
    num--;
    if(num < len/4)
        shrink();
    cout << "Delete"<< key <<endl;

}

void Hash::grow()
{
    auto tmp = table;
    table = new pair<int,OAHashState>[len*2]();
    int num_ = num;
    num = 0;
    len*= 2;
    cout << "Grow to "<< len <<endl;
    cout << "....Re-inserting......" <<endl;
    for (int i = 0;i < len/2 ;i++)
    {
        if(tmp[i].second==USED)
            insertItem(tmp[i].first);
    }
    delete[] tmp;
    cout << "....Grow done......"<<endl;

}

void Hash::shrink()
{
    auto tmp = table;
    table = new pair<int,OAHashState>[len/2]();
    int num_ = num;
    num = 0;
    len/=2;
    cout << "Shrink to "<<  len <<endl;
    cout << "....Re-inserting......" <<endl;
    for (int i = 0;i < len*2 ;i++)
    {
        if(tmp[i].second==USED)
            insertItem(tmp[i].first);
    }
    delete[] tmp;
    cout << "....Shrink done......"<<endl;

}

int Hash::hashFunction(const int& key, int i) const
{
    return  (key + i) % len ;
}

// function to display hash table
void Hash::displayHash() const{
    cout<<"------------------------------"<<endl;
    pair<int,OAHashState> item;
    for (int i = 0;i < len ;i++)
    {
        item = table[i];
        if(item.second==USED)
            cout << " | " << item.first;
        else if(item.second==DELETED)
            cout << " | @";
        else 
            cout << " | #";
    }
    cout << " | " << endl;
    cout<<"------------------------------"<<endl;

}

int main()
{
    // array that contains keys to be mapped
    int a[] = {15, 11, 27, 8, 12};
    int n = sizeof(a)/sizeof(a[0]);

    cout << "Initialized!" <<endl;
    // insert the keys into the hash table
    Hash h(4); 
    for (int i = 0; i < n; i++)
    {
        h.insertItem(a[i]);
        h.displayHash();
    }


    // delete 12 from hash table
    h.deleteItem(12);

    h.insertItem(1);
    h.insertItem(2);

    h.displayHash();

    h.insertItem(3);
    h.displayHash();

    h.insertItem(4);
    h.displayHash();

    h.deleteItem(3);
    h.deleteItem(4);
    h.deleteItem(1);
    h.deleteItem(2);
    h.deleteItem(8);
    h.deleteItem(15);
    h.displayHash();

    h.deleteItem(11);

    h.displayHash();

    return 0;
}
