//Project3
#include <iostream>
#include <string>
#include "Class.h"

using namespace std;

/*Constructors/Destructors*/

//Creature society's C/D
Creature_society::Creature_society(int N, int L, int good_threshold, int bad_threshold):total(N), total_zombies(0), total_good(0){
    static const string names_for_good[5] = {"Aragorn", "Arwen", "Bilbo", "Boromir", "Eomer"}; //I declare the 2 arrays of the good and bad names as static const 
    static const string names_for_bad[5] = {"Sauron", "Saruman", "Shelob", "Gollum", "Smaug"}; //inside the creature society constructor to be able to use it
    cout << "The creature society has been made" << endl;
    this->creature = new Creature*[total]; //Allocation for N creatures inside the society
    for(int i=0; i<this->total; i++){
        int random_good_or_bad = rand()%2;  //Picking randomly what creature
        int random_name_pick = rand()%5;    //i will create inside the society
        if(random_good_or_bad == 0){        //0 then bad creature and 1 a good creature
            string Bad_Name = names_for_bad[random_name_pick];
            string Name = Bad_Name += to_string(i+1); //Connect name with the unique number that describes each creature
            this->creature[i] = new Bad_creature(L, this, Name, bad_threshold); //Calling the bad creature constructor 
        }else{
            string Good_Name = names_for_good[random_name_pick];
            string Name = Good_Name += to_string(i+1); //Connect name with the unique number that describes each creature
            this->creature[i] = new Good_creature(L, this, Name, good_threshold); //Calling the good creature constructor
        }
    }
}
Creature_society::~Creature_society(){
    for(int i=0; i<this->total; i++){ //
        delete creature[i];           //Freeing all the allocations
    }                                 //i did for the N creatures
    delete[] creature;                //
    cout << "The creature society has been destroyed" << endl;
}

//Creature's C/D
Creature::Creature(const Creature& the_clone){ //Copy constructor of creature
    this->Name = the_clone.Name;    //Copying all the
    this->Life = the_clone.Life;    //informations that describes
    this->index = the_clone.index;  //each creature
}

//Good creature's C/D
Good_creature::Good_creature(const int L, Creature_society* index, string name, const int Thresh):threshold(Thresh), Creature(L, index, name){
    cout << this->get_name() << ", a good creature just created." << endl;
}
Good_creature::Good_creature(const Good_creature& the_good_clone): Creature(the_good_clone){ //Copy constructor of good creature
    this->threshold = the_good_clone.threshold; //Copying the threshold to the new creature
    cout << this->get_name() << "'s good clone just created with name : " << this->get_name() << " and life of " << this->get_life() << " points."<< endl;
}
Good_creature::~Good_creature(){
    cout << this->get_name() << ", good creature just destroyed." << endl;
}

//Bad creature's C/D
Bad_creature::Bad_creature(const int L, Creature_society* index, string name, const int Thresh):threshold(Thresh), Creature(L, index, name){
    cout << this->get_name()  << ", a bad creature just created." << endl;
}
Bad_creature::Bad_creature(const Bad_creature& the_bad_clone):Creature(the_bad_clone){ //Copy constructor of bad creature
    this->threshold = the_bad_clone.threshold; //Copying the threshold to the new creature
    cout << this->get_name()  << "'s bad clone just made with name : " << this->get_name() << " and life of " << this->get_life() << " points."<< endl;
}
Bad_creature::~Bad_creature(){
    cout << this->get_name() << ", bad creature just destroyed." << endl;
}

/*Functions*/

//Creature society's functions
void Creature_society::beating_the_creature(int seat){
    if((creature[seat]->is_a_good() == true) && (creature[seat]->is_a_zombie() == false)){          //When beating the creature
        creature[seat]->beat();                                                                     //i just calling creature's 
    }else if((creature[seat]->is_a_good() == false) && (creature[seat]->is_a_zombie() == false)){   //beat (inline function) and i only decrease
        creature[seat]->beat();                                                                     //the life of this exact creature
    }
}
void Creature_society::blessing_the_creature(int seat){
    if((creature[seat]->is_a_good() == true) && (creature[seat]->is_a_zombie() == false)){          //When blessing the creature calling creature's
        creature[seat]->bless(seat);                                                                //bless function and passing the exact  
    }else if((creature[seat]->is_a_good() == false) && (creature[seat]->is_a_zombie() == false)){   //creature as an argument into the bless
        creature[seat]->bless(seat);                                                                //(i will need it to call other functions)
    }
}

int Creature_society::no_of_good(){ //Just calculating how many good creatures there are in the society
    for(int i=0; i<total; i++){
        if(creature[i]->is_a_good() == true){
            ++total_good;
        }
    }
    return total_good;
}
int Creature_society::no_of_zombies(){ //Just calculating how many zombies there are in the society
    for(int i=0; i<total; i++){
        if(creature[i]->is_a_zombie() == true){
            ++total_zombies;
        }
    }
    return total_zombies;
}

void Creature_society::clone_next(int ID){
    int next_seat = 0;
    if(ID == total-1){
        Creature** ptr = &creature[next_seat]; //Making this pointer (ptr) cause i dont have access in creature society private members (creature array)
        creature[ID]->clone(ptr);              //and clone the creature i need to clone in ptr position
    }else{
        next_seat = ID + 1;
        Creature** ptr = &creature[next_seat]; //Making this pointer (ptr) cause i dont have access in creature society private members (creature array)
        creature[ID]->clone(ptr);              //and clone the creature i need to clone in ptr position
    }
}
void Creature_society::clone_zombies(int ID){
    if(ID == total){
        cout << "You cannot clone at the end of the society. There are no more zombies beyond." << endl;
    }else{
        for(int i=ID+1; i<total; i++){
            if((ID < total) && (creature[ID+1]->is_a_zombie() == true)){
                Creature** ptr = &creature[i];
                creature[ID]->clone(ptr);
            }else{
                cout << "There is no zombie after you to clone." << endl;
                break;
            }
        }
    }
}

//Good creature's functions
void Good_creature::bless(int ID){
    if(get_life() > 0){ //If the creature isnt a zombie i will increase hes life and i will check if he's life is greater than the threshold*
        set_life();
        cout << "Blessing the " << this->get_name() << ", a good creature and the current life is " << this->get_life() << " points."<< endl;
        if(is_good_healthy() == true){ //*if it is then i will clone it
            get_index()->clone_next(ID); //Index is a pointer and the type is creature society. This pointer is the link to call clone next that is a creature society member
        }
    }
}
void Good_creature::clone(Creature** next_creature){ //next_creature = ptr pointer
    delete *next_creature; //Deleting the next seat of the array to place the new creature aka clone
    *next_creature = new Good_creature(*this); //Calling the good creature's copy constructor
}

//Bad creatures functions
void Bad_creature::bless(int ID){
    if(get_life() > 0){ //If the creature isnt a zombie i will increase hes life and i will check if he's life is greater than the threshold*
        set_life();
        cout << "Blessing the " << this->get_name() << ", a bad creature and the current life is " << this->get_life() << " points."<< endl;
        if(is_bad_healthy() == true){ //*if it is then i will clone it
            get_index()->clone_zombies(ID); //Index is a pointer and the type is creature society. This pointer is the link to call clone next that is a creature society member
        }
    }
}
void Bad_creature::clone(Creature** next_creature){ //next_creature = ptr pointer
    delete *next_creature; //Deleting the next seat of the array to place the new creature aka clone
    *next_creature = new Bad_creature(*this); //Calling the bad creature's copy constructor
}