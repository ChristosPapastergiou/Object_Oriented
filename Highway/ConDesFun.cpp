#include <iostream>
#include <vector>
#include <list>
#include "Class.h"

#define MinTolls 3     // Minimun and maximum amount 
#define MaxTolls 4     // of tolls in ever entrance.
#define MinSegCap 10   // Minimun and maximum segment
#define MaxSegCap 20   // capacity of vehicles.

using namespace std;

Attiki::Attiki(int k, int nsegs) : NSegs(nsegs), Total_Vehicles(0){
    cout << "Highway in use." << endl;
    this->segment = new Segment*[NSegs];

    for(int i = 0; i < this->NSegs; i++){
        this->segment[i] = new Segment(k, NSegs, i+1);
    }

    for(int i = 0; i < this->NSegs; i++){
        if(i == 0){
            Segment* next_seg = segment[i+1];               //
            this->segment[i]->set_next(next_seg);           // Linking the previous or
        }else if(i > 0 && i < NSegs-1){                     // the next segment to the
            Segment* next_seg = segment[i+1];               // current segment we are.
            this->segment[i]->set_next(next_seg);           // If it is the first one
            Segment* previous_seg = segment[i-1];           // it has only 1 next link
            this->segment[i]->set_previous(previous_seg);   // if it is at the middle
        }else{                                              // it has both directions
            Segment* previous_seg = segment[i-1];           // and the last only 1 previous
            this->segment[i]->set_previous(previous_seg);   //
        }
    }
}

Attiki::~Attiki(){
    for(int i = 0; i < this->NSegs; i++){
        delete segment[i];              
    }
    delete[] segment;
}

Segment::Segment(int k, int NSegs, int id) : ID(id), segment_capacity(rand()%((MaxSegCap) - (MinSegCap+1) + 1) + (MinSegCap)), random_cars_in_segment(rand()%segment_capacity + 1), last(NSegs), ready_to_pass(0), vehicles_passed(0){ //Initialize
    for(int i = 0; i < this->random_cars_in_segment; i++){ //Segment has a capacity but it doesnt mean that i have to fill it with vehicles
        int range = NSegs-ID+1;
        int random_exit_juction = rand()%range+ID; //Making the random juction (entrance) a vehicle wants to exit
        Segment_Vehicle.push_back(Vehicle(ID, random_exit_juction)); //Making a vector of vehicles and calling the constructor to make them
    }
    this->entrance = new Entrance(k, NSegs, id-1); //i-1 = Entrance's ID (Segment(NSeg) -> Entrance(NSeg-1))
}

Segment::~Segment(){
    delete entrance;
}

Entrance::Entrance(int k, int NSegs, int id) : ID(id), total_tolls(rand()%((MaxTolls - MinTolls) + 1) + MinTolls){
    this->toll = new Toll*[total_tolls]; //Allocate memory for the total amount of tolls attiki highway has

    for(int i = 0; i < 2; i++){
        if(i == 0){                                             //
            this->toll[i] = new Worker_Toll(k, ID, i, NSegs);   //Making at least 1
        }else{                                                  //worker toll and 
            this->toll[i] = new eToll(k, ID, i, NSegs);         //1 e-toll
        }                                                       //
    }

    for(int i = 2; i < this->total_tolls; i++){
        int random_toll = rand()%2;                             //
        if(random_toll == 0){                                   //Making all the other 
            this->toll[i] = new Worker_Toll(k, ID, i, NSegs);   //tolls randomly....
        }else{                                                  //if random is 0 i will make workertoll
            this->toll[i] = new eToll(k, ID, i, NSegs);         //and if random is 1 i will make e-toll
        }                                                       //
    }
}

Entrance::~Entrance(){
    for(int i = 0; i < this->total_tolls; i++){ //Freeing the allocs i did for the n segments
        delete toll[i];
    }
    delete[] toll;
}

// Toll parent class
Worker_Toll::Worker_Toll(int k, int EntranceID, int TollID, int nsegs) : Entrance_ID(EntranceID), K(k), Vehicles_served(0), Toll(){ //Initialize
    int range = (2*K) - K + 1;
    int waiting_cars =rand()%range + K; //The cars that the tolls will create is K to 2*K

    for(int i = 0; i < waiting_cars; i++){ //Every toll may have different amount of vehicles
        int range = nsegs-(Entrance_ID+1)+1;
        int random_exit_juction =rand()%range + (Entrance_ID+1); //Making the random juction (entrance) a vehicle wants to exit
        Toll_Vehicle.push_back(Vehicle(-1, random_exit_juction)); //Making a list of vehicles and calling the constructor to make them
    }
}

eToll::eToll(int k, int EntranceID, int TollID, int nsegs) : Entrance_ID(EntranceID), K(2*k), Vehicles_served(0), Toll(){ //Initialize
    int range = (2*K) - K + 1;
    int waiting_cars = rand()%range + K; //The cars that the tolls will create is K to 2*K

    for(int i = 0; i < waiting_cars; i++){ //Every toll may have different amount of vehicles
        int range = nsegs-(Entrance_ID+1)+1;
        int random_exit_juction = rand() % range + (Entrance_ID+1); //Making the random juction (entrance) a vehicle wants to exit
        Toll_Vehicle.push_back(Vehicle(-1, random_exit_juction)); //Making a list of vehicles and calling the constructor to make them
    }
}

/*Methods*/

void Attiki::operate(int percentage){
    Total_Vehicles = 0;

    for(int i = 0; i < NSegs; i++){
        Total_Vehicles = Total_Vehicles + segment[i]->get_no_of_vehicles(); //Calculating the total vehicles attiki highway has
    }

    cout << "There are " << Total_Vehicles << " vehicles in attiki highway." << endl;
    
    for(int i = NSegs-1; i >= 0; i--){
        segment[i]->operate(i+1, percentage); //Segment[NSegs] so we need NSeg number for the array
    }
}

void Segment::operate(int current_segment, int exit_percent){
    if(Segment_Vehicle.size() > 0){ //If there are no vehicles then it has no meaning to select random vehicle
        int exit_percentage = (int)((double)Segment_Vehicle.size()*(double)exit_percent)/100;
        int random_vehicle = rand()%Segment_Vehicle.size(); //Select one random vehicle*
        int loop = 0, not_ready_vehicles = 0;

        for(int i = 0; i < Segment_Vehicle.size(); i++){
            if(Segment_Vehicle[i].get_exit_status() == false){
                not_ready_vehicles++;
            }
        }

        while(loop < exit_percentage){ 
            if(loop == not_ready_vehicles){ //There is a chance that we dont have exit_percentage amount of vehicles that are ready //90%->10 = 9...we may have*
                break;                      //Instead we may have less...so we need to stop when those vehicles is ready            //011001111...we need to stop at 3
            }
            if(Segment_Vehicle[random_vehicle].get_exit_status() == false){ //*see if it is possible to assign the new value**
                Segment_Vehicle[random_vehicle].set_exit_status();
                random_vehicle = (random_vehicle+1)%Segment_Vehicle.size(); //**and then go to the next one
                ++loop;
            }else{
                random_vehicle = (random_vehicle+1)%Segment_Vehicle.size();
            }
        }
        this->exit(current_segment); //All segments have exits but there must be at least 1 vehicle to exit the segment
    }
    if(current_segment > 1){ //First segment doesnt have a segment before it....it has only 1 segment after
        previous->pass(current_segment-1);
    }

    this->enter(last, segment_capacity, current_segment, &Segment_Vehicle); //Passing the vector's address to Toll::operate via Entrance::operate

    if((entrance->get_delay() == true) && (get_ready_to_pass() > get_passed())){
        cout << "Delays in the entrance of the junction " << entrance->get_id() << ". Delays after the junction " << entrance->get_id() << endl;
    }else if(entrance->get_delay() == true){
        cout << "Delays in the entrance of the junction " << entrance->get_id() << endl;
    }else{
        cout << "Maintain safety distances in the section after the junction " << entrance->get_id() << endl;
    }
    set_passed(false);          //false = variable goes back to zero to be 
    set_ready_to_pass(false);   //ready for the next loop**
}

void Segment::exit(int current_segment){
    for(it = Segment_Vehicle.begin(); it != Segment_Vehicle.end(); it++){ //Start from the vector's beggining at stop at the end
        if((it->get_exit_status() == true) && (it->get_exit_juction() == current_segment)){ //it = pointer that showing the vector's obgject
            Segment_Vehicle.erase(it); //Delete vector's object wherever it is pointing to
            --it; //Return back to the begin
        }
    }
}

void Segment::pass(int current_segment){
    for(it = Segment_Vehicle.begin(); it != Segment_Vehicle.end(); it++){ //Start from the vector's beggining at stop at the end
        if((it->get_exit_status() == true) && (it->get_exit_juction() > current_segment)){
            set_ready_to_pass(true); //Calculating how many are ready before the pass so we can show the message in Segment::operate....**true = ++ the variable
        }
    }
    for(it = Segment_Vehicle.begin(); it!=Segment_Vehicle.end(); it++){ //Start from the vector's beggining at stop at the end
        if(next->Segment_Vehicle.size() < next->segment_capacity){  //Dont extend segment capacity
            if((it->get_exit_status() == true) && (it->get_exit_juction() > current_segment)){
                set_passed(true); //Calculating how many passes so we can show the message in Segment::operate....**true = ++ the variable
                next->Segment_Vehicle.push_back(*it);  //Need to insert the specific it vehicle to the next vehicle array (vector)
                next->Segment_Vehicle.back().set_moving_seg(current_segment+1); //After the pass to the next seg the vehicle is moving to the new one
                next->Segment_Vehicle.back().set_exit_status(); //When a vehicle is ready to pass from seg to seg it doesnt mean its ready to pass to the next one
                Segment_Vehicle.erase(it); //Delete vector's object wherever it is pointing to
                --it; //Return back to the begin
            }
        }
    }
}

void Segment::enter(int nsegs, int segment_capacity, int current_segment, vector<Vehicle>* Segment_Vehicle){ //Here is the pointer that shows the vector
    this->entrance->operate(nsegs, segment_capacity, current_segment, Segment_Vehicle); //Passing this pointer to Entrance::operate
}

void Entrance::operate(int nsegs, int segment_capacity, int current_segment, vector<Vehicle>* Segment_Vehicle){
    int vehicles_passes = 0, max_number = 0, waiting_vehicles = 0, x=0; //Some variables we need in this scope

    for(int i = 0; i < total_tolls; i++){
        toll[i]->set_vehicles_served();
        waiting_vehicles = waiting_vehicles + toll[i]->get_list_size();
        max_number = max_number + toll[i]->get_k();
    } 

    while((*Segment_Vehicle).size() < segment_capacity){
        if(toll[x]->get_vehicles_served() == toll[x]->get_k()){ //
            if(vehicles_passes == max_number){                  //If you served K vehicles you are done
                break;                                          //Next please.
            }else{                                              //But if all tolls served the maximum
                x = (x+1)%(total_tolls);                        //amount of vehicles (max_number)
                continue;                                       //then stop it all..you cant serve more vehicles
            }                                                   //
        } 

        toll[x]->operate(nsegs, current_segment, Segment_Vehicle); //Passing pointer to vector to Toll::operate
        vehicles_passes++;
        x = (x+1)%(total_tolls); //Go to the next toll to serve a vehicle
    }

    if(vehicles_passes < max_number){
        for(int i = 0; i < total_tolls; i++){
            if(toll[i]->get_k() != 0){ //We cant decrease K more than 0
                toll[i]->set_k(true); //true = --K
            }
        }
    }else{
        for(int i = 0; i < total_tolls; i++){
            toll[i]->set_k(false); //false = ++K
        }
    }
    if(vehicles_passes < waiting_vehicles){
        set_delay(true);        //
    }else{                      //True = show the messages at Segment::operate
        set_delay(false);       //
    }
}

void Worker_Toll::operate(int nsegs, int current_segment, vector<Vehicle>* Segment_Vehicle){
    it = Toll_Vehicle.begin();
    (*Segment_Vehicle).push_back(*it);  //Need to insert the specific it vehicle to the next vehicle array (vector)
    Toll_Vehicle.erase(it); //Delete list's object wherever it is pointing to
    (*Segment_Vehicle).back().set_moving_seg(current_segment); //When a vehicle enters we need to set the moving segment
    ++Vehicles_served;
    int range = nsegs-(Entrance_ID+1)+1;
    int random_exit_juction =rand()%range + (Entrance_ID+1); //Making the random juction (entrance) a vehicle wants to exit
    Toll_Vehicle.push_back(Vehicle(-1, random_exit_juction)); //Inserting in the list of vehicles and calling the constructor to make the vehicle
}

void eToll::operate(int nsegs, int current_segment, vector<Vehicle>* Segment_Vehicle){
    it = Toll_Vehicle.begin();
    (*Segment_Vehicle).push_back(*it);  //Need to insert the specific it vehicle to the next vehicle array (vector)
    Toll_Vehicle.erase(it); //Delete list's object wherever it is pointing to
    (*Segment_Vehicle).back().set_moving_seg(current_segment); //When a vehicle enters we need to set the moving segment
    ++Vehicles_served;
    int range = nsegs-(Entrance_ID+1)+1;
    int random_exit_juction =rand()%range + (Entrance_ID+1); //Making the random juction (entrance) a vehicle wants to exit
    Toll_Vehicle.push_back(Vehicle(-1, random_exit_juction)); //Inserting in the list of vehicles and calling the constructor to make the vehicle
}