//Project2
#include <iostream>
#include "Class.h"

using namespace std;

int main(int argc, char* argv[]){
    if(argc != 5){
        cout << "Too many arguments. Try again" << endl;
        return 0;
    }

    int K = atoi(argv[1]); //
    int M = atoi(argv[2]); //Project's variables
    int N = atoi(argv[3]); //
    int L = atoi(argv[4]); //

    Bank* bank = new Bank(K, L); //Calling bank's constructor

    int in = 0, out = 0;
    for(int i=0; i<M; i++){
        for(int j=0; j<N; j++){
            if(bank->enter() == true){  //The loop to enter customers
                ++in;                   //in the bank
            }else{
                ++out;
            }
        }
        for(int j=0; j<in; j++){        //The loop to serve
            bank->serve();              //the customers in the bank
            bank->waiting_customers();
            bank->open_cashiers();
        }
        in = 0;
    }
    while(out > 0){
        int out1 = out;
        out = 0;
        for(int i=0; i<out1; i++){
            if(bank->enter() == true){  //The loop to enter the rest 
                ++in;                   //customers in the bank
            }else{
                ++out;
            }
        }
        for(int j=0; j<in; j++){        //The loop to serve
            bank->serve();              //the rest customers in the bank
            bank->waiting_customers();
            bank->open_cashiers();
        }
        in = 0;
    }

    delete bank; //Delete the alloc i did for the bank when i called the constructor

    return 0;
}