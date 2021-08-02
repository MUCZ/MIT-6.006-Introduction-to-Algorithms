#include <iostream>
#include <string>
#include <vector>
#include <list>

using namespace std;

class Book
{
private:
    int id;
    float price;
    string name;
public:
    Book(int id,float price, string name):id(id),price(price),name(name){};
    int GetId ()const{return id;}
    float GetPrice ()const{return price;}
    string GetName ()const{return name;}
};

ostream& operator<<(ostream& os,const Book& b)
{
    return os<<"Name: "<<'<'<<b.GetName()<<'>'<<endl<<"Id:     "<<b.GetId()
                <<endl<<"Price:"<<"$"<<b.GetPrice()<<endl;
}

class Hash
{
private:

	int BUCKET;     // # of buckets
    int ITEM;       // # of items
	list<Book> *table;	// Pointer to an array containing buckets
    void grow();   // grow the size of slots by 2
    void shrink(); // shrink the size of slots to 1/4 of the originial size 

public:

	Hash(int b); // Constructor
    ~Hash();     

	// inserts a key into hash table
    void insertItem(const Book& b);
    void insertItem(const string& s, const Book& b);

	// deletes a key from hash table
	const bool deleteItem(const Book& b);
    const bool deleteItem(const string& s, const Book& b);

	// hash function to map values to key
	const int hashFunction(const string& s) const;

	void displayHash() const;

    Book* searchItem(const string& s,const int id) const;

};

Hash::Hash(int b)
:BUCKET(b)
{
    table = new list<Book>[b]; 
}

Hash::~Hash()
{
    delete[] table; // Memory leak?!
}

void Hash::insertItem(const Book& b)
{
	int index = hashFunction(b.GetName());
	table[index].push_back(b);
    ITEM++;
    if(ITEM > BUCKET)
        grow();
}

void Hash::insertItem(const string& s, const Book& b)
{
	int index = hashFunction(s);
	table[index].push_back(b);
    ITEM++;
    if(ITEM > BUCKET)
        grow();
}

const bool Hash::deleteItem(const Book& b)
{
    // get the hash index of key
    int index = hashFunction(b.GetName());

    // find the key in (inex)th list
    list <Book> :: iterator i;
    for (i = table[index].begin(); i != table[index].end(); i++) {
        if (i->GetId() == b.GetId())
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
        return false;
}

const bool Hash::deleteItem(const string& s,const Book& b)
{
    // get the hash index of key
    int index = hashFunction(s);

    // find the key in (inex)th list
    list <Book> :: iterator i;
    for (i = table[index].begin(); i != table[index].end(); i++) {
        if  (i->GetId() == b.GetId())
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
        return false;
}

void Hash::grow()
{
    list<Book> *tmp = table;
    table = new list<Book>[BUCKET*2];
    ITEM = 0;
    BUCKET*=2;
    for (int i = 0; i < BUCKET/2; i++) {
        for (auto x : tmp[i])
            insertItem(x);
    }
    delete[] tmp; // Memory leak?!
}

void Hash::shrink()
{
    list<Book> *tmp = table;
    table = new list<Book>[BUCKET/2];
    ITEM = 0;
    BUCKET/=2;
    for (int i = 0; i < BUCKET*2; i++) {
        for (auto x : tmp[i])
            insertItem(x);
    }
    delete[] tmp;
}

void Hash::displayHash() const
{
    cout<<"-----------------"<<endl;
    for (int i = 0; i < BUCKET; i++) {
        cout << i;
        for (auto x : table[i])
            cout << " --> <" << x.GetName() <<">";
            cout << endl;
    }
}

const int Hash::hashFunction(const string& s) const
{
    // An ill-formed hash function
    char p[20];
    strcpy(p,s.c_str());
    int count = 0;
    int sum = 0;
    while(p[count]!='\0')
    {
        sum+=p[count];
        count++;
    }
    return sum%BUCKET;
}

Book* Hash::searchItem(const string& s,const int id) const
{
    int index = hashFunction(s);
    list<Book> :: iterator i;
    for(i = table[index].begin();i!=table[index].end();i++)
    {
        if(i->GetId()==id)
            return &*i;// return the address of the reference of the current iterator
    }
    return nullptr;
}

int main()
{
    Book b1(1,33.1,"Book_1");
    Book b2(2,22.4,"Book_2");
    Book b3(3,40.2,"Book_3");
    Hash h(1);
    h.insertItem(b1);
    h.insertItem(b2);
    h.insertItem(b3);
    h.insertItem(Book(4,44.2,"Book_4"));
    h.displayHash();
    h.insertItem(Book(5,43.2,"Book_5"));
    h.displayHash();
    Book* bp = h.searchItem("Book_4",4);
    cout<< *bp << endl;
    h.deleteItem(*bp);
    h.displayHash();
    h.deleteItem(b1);
    h.deleteItem(b2);
    h.deleteItem(b3);
    h.displayHash();


}