#include <iostream>
#include "Class.h"

using namespace std;

int main(int argc, char* argv[]){
    if(argc != 5){
        cout << "Too many arguments. Try again" << endl;
        return 0;
    }

    int K = atoi(argv[1]);
    int M = atoi(argv[2]);
    int N = atoi(argv[3]);
    int L = atoi(argv[4]);

    Bank* bank = new Bank(K, L);

    int in = 0, out = 0;
    for(int i = 0; i < M; i++){
        for(int j = 0; j < N; j++){
            if(bank->enter() == true){  // Enter customers in the ban
                ++in;
            }else{
                ++out;
            }
        }

        for(int j = 0; j < in; j++){    // Serve the customers in the bank
            bank->serve();
            bank->waiting_customers();
            bank->open_cashiers();
        }
        in = 0;
    }

    while(out > 0){
        int out1 = out;
        out = 0;
        for(int i = 0; i < out1; i++){
            if(bank->enter() == true){  // Enter the rest customers in the bank
                ++in;
            }else{
                ++out;
            }
        }
        for(int j=0; j<in; j++){        // Serve the rest customers in the bank
            bank->serve();
            bank->waiting_customers();
            bank->open_cashiers();
        }
        in = 0;
    }

    delete bank;

    return 0;
}