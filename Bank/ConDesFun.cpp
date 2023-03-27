#include <iostream>
#include "Class.h"

using namespace std;

Bank::Bank(int _K, int _L) : L(_L), K(_K), cashiernumber(5), last_customer(1), curr_serving(1), open_cashier_counter(0), next_cashier(-1){ //Initialize
    this->cashier = new Cashier*[cashiernumber]; // Allocate space for the cashiers
    for(int i = 0; i < cashiernumber; i++){
        this->cashier[i] = new Cashier(i, L);
    }

    open(0); //Opening the first cashier
}
Bank::~Bank(){
    for(int i = 0; i < cashiernumber; i++){
        delete cashier[i]; // Deallocation
    }
    delete[] cashier;
}

Cashier::Cashier(int id, int _L):L(_L), ID(++id), open_flag(false), serving_flag(false), customer_served(0){ //Initialize
}

/* Methods */

bool Bank::enter(){
    if(check_to_open() == true){                        // Checking if we need to open another cashier
        for(int i = 0; i < this->cashiernumber; i++){   // and if this is true then open it
            if(cashier[i]->is_open() == false){         // and return true to main to add the 
                open(i);                                // customers that are in the bank to
                last_customer++;                        // serve them. If not returning false to
                return true;                            // keep them to out variable to serve them 
            }                                           // whenever we can
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
        open(0);                                                // If there is no open cashier the open the first cashier but...
        next_cashier = 0;
        cout << "Next " << next_cashier  << endl;
    }else{
        next_cashier = (next_cashier+1) % cashiernumber;        // Go to the next cashier and if it is
        while(cashier[next_cashier]->is_open() == false){       // close then go to the next onw until you find 
            next_cashier = (next_cashier+1) % cashiernumber;    // one open
        }
        cout << "Next " << next_cashier  << endl;
    }

    cout << "Customer no : " << curr_serving << " by cashier no : " << next_cashier+1 << endl;
    cashier[next_cashier]->serve();

    if(cashier[next_cashier]->free() == true){  // Just serve and if the cashier we locked is about to close 
        --open_cashier_counter;                 // because of hardwork or must be closed just close it and 
    }                                           // inform us by abstract the variable
    exit();
}

void Bank::exit(){
    this->curr_serving++;
    if(check_to_close() == true){
        for(int i = 0; i < this->cashiernumber; i++){   // If true then close the first one and break from the loop
            if(cashier[i]->is_open() == true){
                close(i);
                break;
            }
        }
    }
}

bool Bank::check_to_open(){
    if((last_customer-curr_serving) > open_cashier_counter * K){  // Just the check_to_open
        return true;
    }else{
        return false;
    }
}
bool Bank::check_to_close(){
    if((last_customer-curr_serving) <= (open_cashier_counter-1) * K){  // Just the check_to_close
        return true;
    }else{
        return false;
    }
}

void Bank::open(int i){
    ++open_cashier_counter;
    int id = cashier[i]->open();
    cout << "Cashier no : " << id << " just opened." << endl;
}

void Bank::close(int i){
    --open_cashier_counter;
    int id = cashier[i]->close();
    cout << "Cashier no : " << id << " just closed." << endl;
}

int Cashier::open(){
    this->open_flag = true;
    this->customer_served = 0;
    return ID;
}

int Cashier::close(){
    this->open_flag = false;
    this->serving_flag = false;
    this->customer_served = 0;
    return ID;
}

void Cashier::serve(){
    this->serving_flag = true;
}

bool Cashier::free(){
    this->serving_flag = false;
    this->customer_served++;                // Closing the cashier if
    if(this->customer_served == this->L){   // served = L
        cout << "The cashier " << ID << " just closed because of hardwork" << endl;
        close();
        return true;    // Also return true if it is about to close
    }
    return false;
}

bool Cashier::is_open(){
    if(this->open_flag == true){
        return true;
    }else{
        return false;
    }
}

bool Cashier::is_free(){
    if(this->serving_flag == true){
        return false;
    }else{
        return true;
    }
}