#include <string>
#include <iostream>

using namespace std;

class Books{
private:
    int ISBN;
    string title;
    string author;
public:
    Books::Books(string Title, string Author, int isbn):author(Author), title(Title), ISBN(isbn){}
    ~Books(){}
    void printdetails(){cout << "Book details : " << title << " by " << author << " with ISBN number " << ISBN << endl;}
};

class Shelves{
private:
    int NMAX, ID, counterbooks;
    class Books** books; // Link to have books in the shelves
public:
    Shelves(int, int);
    ~Shelves();
    bool shelf_place_book(Books*, int);
    bool shelf_take_book(int);
    void print_shelf(); // How many books there are in the shelf
};

class Cupboard{
private:
    int NMAX, ShelfNumber;
    class Shelves** shelves; // Link with shelves
public:
    Cupboard(int, int, int);
    ~Cupboard();
    bool cupboard_place_book(int, Books*); 
    bool cupboard_take_book(int);
    void print_cupboards_shelf();  // Print how many books there are in cupboard's n shelf

};

class Library{
private:
    int BookNumber, ShelfNumber, CupboardNumber, CupboardShelfNumber, ID, maxlibrary;
    class Shelves** shelves;    // Need to Link
    class Cupboard** cupboard;  // library with all the 
    class Base** base;          // other classes
public:
    Library(int);
    ~Library();
    bool place_book(int, Books*);
    bool take_book(int, Books*);
    void print();
    int total_library_books(){return BookNumber;}
};

class Base{
public:
    Base(){cout << "A base has been created" << endl;}
    ~Base(){cout << "The base has been destroyed" << endl;}
};

string StringGenerator(); // The functions that making random strings 
int ISBNGenerator();      // nd numbers as details for every single book