//Project
#include <iostream>
#include <vector>
#include <list>

using namespace std;

class Vehicle{
private:
    int exit_junction, moving_seg;
    bool exit_status;
public:
    Vehicle(int segment_position, int exit):moving_seg(segment_position), exit_junction(exit), exit_status(false){} //Initialize
    ~Vehicle(){}
    bool get_exit_status(){return exit_status;}                                            //
    int get_exit_juction(){return exit_junction;}                                          //Inline
    void set_exit_status(){(exit_status == true)? exit_status=false : exit_status=true;}   //
    void set_moving_seg(int current_segment){moving_seg = current_segment;}                //
};

class Toll{
protected:
    list<Vehicle> Toll_Vehicle; //List of vehicles that are waiting to enter attiki highway
    list<Vehicle>::iterator it;
public:
    Toll(){}
    virtual ~Toll(){}
    virtual int get_k() = 0;                                //
    virtual void set_k(bool) = 0;                           //Pure virtual
    virtual int get_list_size() = 0;                        //methods
    virtual int get_vehicles_served() = 0;                  //
    virtual void set_vehicles_served() = 0;                 //
    virtual void operate(int, int, vector<Vehicle>*) = 0;   //
};

class Worker_Toll: public Toll{
private:
    int Entrance_ID, K, random_cars_in_toll, Vehicles_served;
public:
    Worker_Toll(int, int, int, int);
    ~Worker_Toll(){}
    void operate(int, int, vector<Vehicle>*); //Project's method
    int get_k(){return K;}                                  //
    int get_list_size(){return Toll_Vehicle.size();}        //Inline
    int get_vehicles_served(){return Vehicles_served;}      //methods
    void set_vehicles_served(){Vehicles_served = 0;}        //
    void set_k(bool number){(number == true)? --K : ++K;}   //
    
};

class eToll: public Toll{
private:
    int Entrance_ID, K, random_cars_in_toll, Vehicles_served;
public:
    eToll(int, int, int, int);
    ~eToll(){}
    void operate(int, int, vector<Vehicle>*); //Project's method
    int get_k(){return K;}                                  //
    int get_list_size(){return Toll_Vehicle.size();}        //Inline
    int get_vehicles_served(){return Vehicles_served;}      //methods
    void set_vehicles_served(){Vehicles_served = 0;}        //
    void set_k(bool number){(number == true)? --K : ++K;}   //
};

class Entrance{
private:
    bool delay;
    int ID, total_tolls;
    class Toll** toll;
public:
    Entrance(int, int, int);
    ~Entrance();
    void operate(int, int, int, vector<Vehicle>*); //Project's method
    int get_id(){return ID;}                                //
    void set_delay(bool i){delay = i;}                      //Inline
    bool get_delay(){return (delay == true)? true: false;}  //
};

class Segment{
private:
    int ID, segment_capacity, random_cars_in_segment, last, ready_to_pass, vehicles_passed;
    class Entrance* entrance;
    vector<Vehicle> Segment_Vehicle;
    vector<Vehicle>::iterator it;
    Segment* next;
    Segment* previous;
public:
    Segment(int, int, int);
    ~Segment();
    void exit(int);
    void pass(int);
    void operate(int, int);
    void enter(int, int, int, vector<Vehicle>*);
    int get_passed(){return vehicles_passed;}                                           //
    int get_ready_to_pass(){return ready_to_pass;}                                      //
    int get_no_of_vehicles(){return Segment_Vehicle.size();}                            //Inline
    void set_next(Segment* next_seg){this->next = next_seg;}                            //
    void set_previous(Segment* previous_seg){this->previous = previous_seg;}            //
    void set_passed(bool i){(i == true)? ++vehicles_passed: vehicles_passed = 0;}       //
    void set_ready_to_pass(bool i){(i == true)? ++ready_to_pass: ready_to_pass = 0;}    //
};

class Attiki{
private:
    int NSegs, Total_Vehicles;
    class Segment** segment;
public:
    Attiki(int, int);
    ~Attiki();
    void operate(int); //Project's method
};