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
    void printdetails(){cout << "Book details : " << title << " by " << author << " with ISBN number " << ISBN << endl;} //Inline
};

class Shelves{
private:
    int NMAX, ID, counterbooks;
    class Books** books; //Need to have it because i need books in the shelves
public:
    Shelves(int, int);
    ~Shelves();
    bool shelf_place_book(Books*, int); //My functions to place
    bool shelf_take_book(int);        //a book in a shelf
    void print_shelf(); //Printing how many books there are in n shelf
};

class Cupboard{
private:
    int NMAX, ShelfNumber;
    class Shelves** shelves; //Need to connect with the shelves
public:
    Cupboard(int, int, int);
    ~Cupboard();
    bool cupboard_place_book(int, Books*); //My functions to place
    bool cupboard_take_book(int);          //a book in a cupboard's shelf
    void print_cupboards_shelf();  //Calling cupboard's shelves to print how many books there are in cupboard's n shelf

};

class Library{
private:
    int BookNumber, ShelfNumber, CupboardNumber, CupboardShelfNumber, ID, maxlibrary;
    class Shelves** shelves;    //Need to connect
    class Cupboard** cupboard;  //library with all the 
    class Base** base;          //other classes
public:
    Library(int);
    ~Library();
    bool place_book(int, Books*); //Project functions to place book in library
    bool take_book(int, Books*);       //(calling them from the Main.cpp)
    void print();
    int total_library_books(){return BookNumber;} //Need this to return it to main function to check if there are books to take //Inline
};

class Base{
public:         //Just the
    Base(){cout << "A base has been created" << endl;} //Inline
    ~Base(){cout << "The base has been destroyed" << endl;} //Inline
};

string StringGenerator(); //The functions that making random strings 
int ISBNGenerator();      //and numbers as details for every single book