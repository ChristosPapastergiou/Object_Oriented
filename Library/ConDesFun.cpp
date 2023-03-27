/*Project1*/
#include <iostream>
#include <string>
#include "Class.h"

using namespace std;

/*Constructors/Destructors*/

//Library's C/D
Library::Library(int _NMAX):BookNumber(0), ShelfNumber(3), CupboardNumber(1), CupboardShelfNumber(2), maxlibrary(_NMAX*(ShelfNumber+CupboardShelfNumber)){ //Initialize
    this->base = new Base*[1]; //Taking space for the base
    this->base[0] = new Base(); //Calling base constructor
    cout << "A library has been created" << endl;
    this->shelves = new Shelves*[ShelfNumber]; //Taking space for the shelves
    this->cupboard = new Cupboard*[CupboardNumber]; //Taking space for the cupboard
    for(int i=0; i<this->ShelfNumber; i++){
        this->shelves[i] = new Shelves(_NMAX, i); //Making the shelves of the library and giving i as the id of the shelve
    }
    for(int j=0; j<this->CupboardNumber; j++){
        this->cupboard[j] = new Cupboard(_NMAX, CupboardShelfNumber, j+2); //Making the cupboard and giving j+2 as the id of the shelves (1-3 in library 4-5 in cupboard)
    } 
}
Library::~Library(){
    for(int i=0; i<this->ShelfNumber; i++){
        delete shelves[i]; 
    }                                                   //Deleting all the allocs
    for(int j=0; j<this->CupboardNumber; j++){          //i did to build the 
        delete cupboard[j];                             //library (shelves, cupboard, base)
    }                                                   //and finally destroy the library
    delete[] shelves;
    delete[] cupboard;
    cout << "The library has been destroyed" << endl;
    delete base[0];
    delete[] base;
}

//Shelf's C/D
Shelves::Shelves(int _NMAX, int id):NMAX(_NMAX), counterbooks(0){ //Initialize
    this->ID = ++id;
    this->books = new Books*[_NMAX]; //Making space for the maximum amount of books each shelve can carry
    cout << "A shelf just created with maximun capacity : " << NMAX << " and ID of : " << ID << endl;
}
Shelves::~Shelves(){
    delete[] books; //Need to delete the allocs for the books
    cout << "A shelf has been destroyed" << endl;
}

//Closet's C/D
Cupboard::Cupboard(int _NMAX, int _CupboardShelfNumber, int id):NMAX(_NMAX), ShelfNumber(_CupboardShelfNumber){ //Initialize
    this->shelves = new Shelves*[ShelfNumber]; //Making space for the cupboard's shelves
    cout << "The cupboard has been created" << endl;
    for(int i=0; i<this->ShelfNumber; i++){
        this->shelves[i] = new Shelves(_NMAX, ++id); // Just like i did in library 
    }
}
Cupboard::~Cupboard(){
    for(int i=0; i<this->ShelfNumber; i++){
        delete shelves[i];                             //Delete the allocs
    }                                                  //of the shelves and 
    delete[] shelves;                                  //and destroy the cupboard
    cout << "The cupboard has been destroyed" << endl;
}

/*Functions*/

//Library's functions
bool Library::place_book(int random, Books* novel){
    ++this->BookNumber;
    if(BookNumber <= maxlibrary){
        if(random <= 3){
            if(shelves[random-1]->shelf_place_book(novel, random) == true){ //Placing book to a random shelf and returning true to main
                return true;                                                //to tell me that the placement has been done
            }else{
                --this->BookNumber;
                cout << "We did not place a book in library" << endl;       //else the placement has not been done annd booknumber must just to the previous value
                return false;
            }
        }else{
            if(cupboard[0]->cupboard_place_book(random, novel) == true){    //Placing book to a random cupboard shelf and returning true to main
                return true;                                                //to tell me that the placement has been done
            }else{
                --this->BookNumber;
                cout << "We did not place a book in library" << endl;       //else the placement has not been done annd booknumber must just to the previous value
                return false;
            }
        }
    }else{
        --this->BookNumber;
        cout << "There is no room to place another book in the library" << endl;
        return false;
    }
    return 0;
}
bool Library::take_book(int random, Books* novel){
    this->BookNumber--;
    if(BookNumber >= 1){
        if(random <= 3){
            if(shelves[random-1]->shelf_take_book(random) == true){
                return true;
            }else{                                                                  //Like place book but 
                ++this->BookNumber;                                                 //instead taking a book
                cout << "We did not remove a book from library" << endl;
                return false;
            }
        }else{
            if(cupboard[0]->cupboard_take_book(random) == true){
                return true;
            }else{
                ++this->BookNumber;
                cout << "We did not remove a book from library" << endl;
                return false;
            }
        }
    }else{
        cout << "There is no book to take" << endl;
    }
    return 0;
}
void Library::print(){
    cout << "Total books in library : " << this->BookNumber << endl;
    cout << "Total books in shelves and their details." << endl;
    for(int i=0; i<this->ShelfNumber; i++){                             //Printing book's details
        shelves[i]->print_shelf();                                      //via print_shelf
    }                                                                   //or print_cupboards_shelf
    for(int j=0; j<this->CupboardNumber; j++){
        cupboard[j]->print_cupboards_shelf();
    }
}

//Cupboard's functions//
bool Cupboard::cupboard_place_book(int random, Books* novel){
    int i = shelves[random-4]->shelf_place_book(novel, random); //Like library's place book placing on random shelf
    return i;
}
bool Cupboard::cupboard_take_book(int random){
    int i = shelves[random-4]->shelf_take_book(random); //Like library's take book taking on random shelf
    return i;
}
void Cupboard::print_cupboards_shelf(){
    for(int i=0; i<this->ShelfNumber; i++){ //Like library's print detail books but calling only print_shelf
        shelves[i]->print_shelf();
    }
}

//Shelf's functions
bool Shelves::shelf_place_book(Books* novel, int randomShelf){
    if(counterbooks < NMAX){
        ++counterbooks;
        books[counterbooks-1] = novel; //Placing book every time
        if(randomShelf == 1){
            cout << "Placing book in upper bookcase shelf. ";
        }else if(randomShelf == 2){
            cout << "Placing book in middle bookcase shelf. ";      //Just the cases for
        }else if(randomShelf == 3){                                 //every place i did
            cout << "Placing book in lower bookcase shelf. ";
        }else if(randomShelf == 4){
            cout << "Placing book in upper cupboard shelf. ";
        }else{
            cout << "Placing book in lower cupboard shelf. ";
        }
        cout << counterbooks << "/" << NMAX << " books in shelf " << ID << endl;
    }else{
        cout << "There is no room to place book in shelf " << ID << endl; 
        return false;
    }
    return true;
}
bool Shelves::shelf_take_book(int randomShelf){
    if(counterbooks > 0){
        --counterbooks;
        books[counterbooks] = NULL;
        if(randomShelf == 1){
            cout << "Taking book from upper bookcase shelf. ";
        }else if(randomShelf == 2){
            cout << "Taking book from middle bookcase shelf. ";
        }else if(randomShelf == 3){
            cout << "Taking book from lower bookcase shelf. ";  //Just the cases for
        }else if(randomShelf == 4){                             //every take i did
            cout << "Taking book from upper cupboard shelf. ";
        }else{
            cout << "Taking book from lower cupboard shelf. ";
        }
        cout << counterbooks << "/" << NMAX << " books in shelf " << ID << endl;
    }else{
        cout << "There are no books to take from shelf " << ID << endl;
        return false;
    }
    return true;
}
void Shelves::print_shelf(){
    cout << "Total books in shelf " << ID << " : " << counterbooks << endl;
    if(counterbooks != 0){
        for(int i=0; i<this->counterbooks; i++){        //Printing the details finally
            books[i]->printdetails();
        }
    }
}

//Main's functions
string StringGenerator(){
    string s;
    static const char Gen[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"; //Taking random string as book's name and author
    for(int i=0; i<10; i++){
        s += Gen[rand()%(sizeof(Gen) - 1)];
    }
    return s;
}
int ISBNGenerator(){
    int i = rand() % 100; //Taking a random number as the ISBN
    return i;
}