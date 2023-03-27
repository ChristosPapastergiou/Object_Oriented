#include <iostream>

using namespace std;

class Bank{
private:
    int last_customer, curr_serving, cashiernumber, K, L, open_cashier_counter, next_cashier;
    class Cashier** cashier;
public:
    Bank(int, int);
    ~Bank();
    bool enter();
    void serve();
    void exit();
    bool check_to_open();
    bool check_to_close();
    void open(int);
    void close(int); 
    void waiting_customers(){cout << "There are " << this->last_customer-this->curr_serving << " customers that are waiting." << endl;}
    void open_cashiers(){cout << "There are " << open_cashier_counter << " cashiers open right now." << endl;}
};

class Cashier{
private:
    int customer_served, ID, L, cashiernumber;
    bool open_flag, serving_flag;
public:
    Cashier(int, int);
    ~Cashier(){}
    int open();
    void serve();
    int close();
    bool free();
    bool is_open();
    bool is_free();
};
