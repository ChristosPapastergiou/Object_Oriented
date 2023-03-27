#include <string>
#include <iostream>

#include "Class.h"

using namespace std;

Library::Library(int _NMAX) : BookNumber(0), ShelfNumber(3), CupboardNumber(1), CupboardShelfNumber(2), maxlibrary(_NMAX*(ShelfNumber+CupboardShelfNumber)){
    this->base = new Base*[1];
    this->base[0] = new Base();

    cout << "A library has been created" << endl;

    this->shelves = new Shelves*[ShelfNumber];
    this->cupboard = new Cupboard*[CupboardNumber];

    for(int i=0; i<this->ShelfNumber; i++){
        this->shelves[i] = new Shelves(_NMAX, i);
    }
    for(int j=0; j<this->CupboardNumber; j++){
        this->cupboard[j] = new Cupboard(_NMAX, CupboardShelfNumber, j+2);
    } 
}

Library::~Library(){
    for(int i = 0; i < this->ShelfNumber; i++){
        delete shelves[i]; 
    }
    for(int j = 0; j < this->CupboardNumber; j++){
        delete cupboard[j];
    }

    delete[] shelves;
    delete[] cupboard;

    cout << "The library has been destroyed" << endl;

    delete base[0];
    delete[] base;
}

Shelves::Shelves(int _NMAX, int id):NMAX(_NMAX), counterbooks(0){
    this->ID = ++id;
    this->books = new Books*[_NMAX];
    cout << "A shelf just created with maximun capacity : " << NMAX << " and ID of : " << ID << endl;
}

Shelves::~Shelves(){
    delete[] books;
    cout << "A shelf has been destroyed" << endl;
}

Cupboard::Cupboard(int _NMAX, int _CupboardShelfNumber, int id):NMAX(_NMAX), ShelfNumber(_CupboardShelfNumber){
    this->shelves = new Shelves*[ShelfNumber];
    cout << "The cupboard has been created" << endl;

    for(int i = 0; i < this->ShelfNumber; i++){
        this->shelves[i] = new Shelves(_NMAX, ++id);
    }
}

Cupboard::~Cupboard(){
    for(int i=0; i<this->ShelfNumber; i++){
        delete shelves[i];
    }

    delete[] shelves;
    cout << "The cupboard has been destroyed" << endl;
}

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
            }else{
                ++this->BookNumber;
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

    for(int i = 0; i < this->ShelfNumber; i++){
        shelves[i]->print_shelf();          
    }
    for(int j=0; j<this->CupboardNumber; j++){
        cupboard[j]->print_cupboards_shelf();
    }
}

bool Cupboard::cupboard_place_book(int random, Books* novel){
    int i = shelves[random-4]->shelf_place_book(novel, random);
    return i;
}

bool Cupboard::cupboard_take_book(int random){
    int i = shelves[random-4]->shelf_take_book(random);
    return i;
}

void Cupboard::print_cupboards_shelf(){
    for(int i=0; i<this->ShelfNumber; i++) shelves[i]->print_shelf();
}

bool Shelves::shelf_place_book(Books* novel, int randomShelf){
    if(counterbooks < NMAX){
        ++counterbooks;
        books[counterbooks-1] = novel;
        if(randomShelf == 1){
            cout << "Placing book in upper bookcase shelf. ";
        }else if(randomShelf == 2){
            cout << "Placing book in middle bookcase shelf. ";
        }else if(randomShelf == 3){
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
            cout << "Taking book from lower bookcase shelf. ";
        }else if(randomShelf == 4){
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
        for(int i = 0; i < this->counterbooks; i++){
            books[i]->printdetails();
        }
    }
}

string StringGenerator(){
    string s;
    static const char Gen[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    for(int i = 0; i < 10; i++){
        s += Gen[rand()%(sizeof(Gen) - 1)];
    }
    return s;
}
int ISBNGenerator(){
    int i = rand() % 100;
    return i;
}