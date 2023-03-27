//Project2
#include <iostream>
#include "Class.h"

using namespace std;

/*Constructors/Destructors*/

//Bank's C/D
Bank::Bank(int _K, int _L):L(_L), K(_K), cashiernumber(5), last_customer(1), curr_serving(1), open_cashier_counter(0), next_cashier(-1){ //Initialize
    this->cashier = new Cashier*[cashiernumber]; //Taking space for the cashiers
    for(int i=0; i<cashiernumber; i++){
        this->cashier[i] = new Cashier(i, L);    //Calling the cashier constructor
    }
    open(0); //Opening the first cashier
}
Bank::~Bank(){
    for(int i=0; i<cashiernumber; i++){
        delete cashier[i];              //Delete all the allocs i did
    }
    delete[] cashier;
}

//Cahier's C/D
Cashier::Cashier(int id, int _L):L(_L), ID(++id), open_flag(false), serving_flag(false), customer_served(0){ //Initialize
}
Cashier::~Cashier(){
}

/*Functions*/

//Bank's functions
bool Bank::enter(){
    if(check_to_open() == true){                        //Checking if we need to open another cashier
        for(int i=0; i<this->cashiernumber; i++){       //and if this is true then open it
            if(cashier[i]->is_open() == false){         //and return true to main to add the 
                open(i);                                //customers that are in the bank to
                last_customer++;                        //serve them. If not returning false to
                return true;                            //keep them to out variable to serve them 
            }                                           //whenever we can
        }
        if(open_cashier_counter == cashiernumber){
            cout << "Sorry you cannot enter until some customers are served!" << endl;
            return false;
        }
    }else{
        last_customer++;       
    }
    return true;
}
void Bank::serve(){
    if(open_cashier_counter == 0){
        open(0);                                                //If there is no open open the first cashier but...
        next_cashier = 0;
        cout << "Next " << next_cashier  << endl;
    }else{
        next_cashier = (next_cashier+1) % cashiernumber;        //Go to the next cashier and if it is
        while(cashier[next_cashier]->is_open() == false){       //close then go to the next onw until you find 
            next_cashier = (next_cashier+1) % cashiernumber;    //one open
        }
        cout << "Next " << next_cashier  << endl;
    }
    cout << "Customer no : " << curr_serving << " by cashier no : " << next_cashier+1 << endl;
    cashier[next_cashier]->serve();
    if(cashier[next_cashier]->free() == true){  //Just serve and if the cashier we locked is about to close 
        --open_cashier_counter;                 //because of hardwork or must be closed just close it and 
    }                                           //inform us by abstract the variable
    exit();
}

void Bank::exit(){
    this->curr_serving++;
    if(check_to_close() == true){
        for(int i=0; i<this->cashiernumber; i++){   //If true then close the first one and break from the loop
            if(cashier[i]->is_open() == true){
                close(i);
                break;
            }
        }
    }
}

bool Bank::check_to_open(){
    if((last_customer-curr_serving) > open_cashier_counter*K){  //Just the check_to_open
        return true;
    }else{
        return false;
    }
}
bool Bank::check_to_close(){
    if((last_customer-curr_serving) <= (open_cashier_counter-1)*K){  //Just the check_to_close
        return true;
    }else{
        return false;
    }
}

void Bank::open(int i){
    ++open_cashier_counter;
    int id = cashier[i]->open();                                //If this functions gets called it means a cashier opened 
    cout << "Cashier no : " << id << " just opened." << endl;
}
void Bank::close(int i){
    --open_cashier_counter;
    int id = cashier[i]->close();                               //If this functions gets called it means a cashier closed
    cout << "Cashier no : " << id << " just closed." << endl;
}

//Cashier's functions
int Cashier::open(){
    this->open_flag = true;     //Project's variables
    this->customer_served = 0;  //
    return ID;                  //Return the id of the shelf that opened
}
int Cashier::close(){
    this->open_flag = false;        //
    this->serving_flag = false;     //Project's variables
    this->customer_served = 0;      //
    return ID;                      //Return the id of the shelf that closed
}
void Cashier::serve(){
    this->serving_flag = true;
}
bool Cashier::free(){
    this->serving_flag = false;
    this->customer_served++;                                                        //Free function, closing the cashier if
    if(this->customer_served == this->L){                                           //served = L
        cout << "The cashier " << ID << " just closed because of hardwork" << endl;
        close();
        return true;                                                                //Also return true if it is about to close
    }
    return false;
}

bool Cashier::is_open(){
    if(this->open_flag == true){
        return true;    //If the cashier is open a customer i return true
    }else{
        return false;   //If not false
    }
}
bool Cashier::is_free(){
    if(this->serving_flag == true){
        return false;    //If the cashier is serving a customer i return false
    }else{
        return true;     //If not true
    }
}