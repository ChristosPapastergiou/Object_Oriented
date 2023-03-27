#include <string>
#include <iostream>
#include "Class.h"

using namespace std;

int main(int argc, char* argv[]){
  if(argc != 5){
    cout << "Too many arguments. Try again" << endl;
    return 0;
  }

  srand(time(NULL));

  int NMAX = atoi(argv[1]);
  int L = atoi(argv[2]);
  int K1 = atoi(argv[3]);
  int K2 = atoi(argv[4]);
  
  Library* library = new Library(NMAX); //Start to build the library

  Books** books = new Books*[L]; //Making room for L books

  for(int k=0; k<L; k++){
    string title = StringGenerator();           //Making the books
    string author = StringGenerator();          //with all the details
    int isbn = ISBNGenerator();                 //i need and calling the
    books[k] = new Books(title, author, isbn);  //constructor to make them
  }

  for(int i=0; i<K1; i++){
    if(i >= L){   //L = books so if K1 is greater than L the place will stop
      cout << "There is no books to place in the library or the placements you want are done." << endl;
      break;
    }
    int RandomShelf = (rand()%5)+1; //picks random shelve to place the book
    if(library->place_book(RandomShelf, books[i]) == true){
      cout << "We placed the book" << endl;
    }else{
      cout << "We did not placed the book" << endl;
    }
  }
  for(int j=0; j<K2; j++){
    if(j >= library->total_library_books()){ //Taking from library the total books i have and if K2 is greater then it will stop
      cout << "There is no books to take from the library or the removals you wanted are done." << endl;
      break;
    }
    int RandomShelf = (rand()%5)+1; //picks random shelve to place the book
    if(library->take_book(RandomShelf, books[j]) == true){
      cout << "We removed the book" << endl;
    }else{
      cout << "We did not remove the book" << endl;
    }
  }

  library->print();

  for(int k=0; k<L; k++){  //delete all the memory 
    delete books[k];       //allocations i did for the L books
  }

  delete[] books;
  delete library; //delete and the destructors are called
  
  return 0;
}