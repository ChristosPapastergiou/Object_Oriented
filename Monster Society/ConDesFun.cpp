#include <string>
#include <iostream>

#include "Class.h"

using namespace std;

Creature_society::Creature_society(int N, int L, int good_threshold, int bad_threshold) : total(N), total_zombies(0), total_good(0){
    static const string names_for_good[5] = {"Aragorn", "Arwen", "Bilbo", "Boromir", "Eomer"}; // I declare the 2 arrays of the good and bad names as static const 
    static const string names_for_bad[5] = {"Sauron", "Saruman", "Shelob", "Gollum", "Smaug"}; // inside the creature society constructor to be able to use it

    cout << "The creature society has been made" << endl;
    this->creature = new Creature*[total];

    for(int i = 0; i < this->total; i++){
        int random_good_or_bad = rand()%2;
        int random_name_pick = rand()%5;

        if(random_good_or_bad == 0){ 
            string Bad_Name = names_for_bad[random_name_pick];
            string Name = Bad_Name += to_string(i+1); // Connect name with the unique number that describes each creature
            this->creature[i] = new Bad_creature(L, this, Name, bad_threshold);
        }else{
            string Good_Name = names_for_good[random_name_pick];
            string Name = Good_Name += to_string(i+1); // Connect name with the unique number that describes each creature
            this->creature[i] = new Good_creature(L, this, Name, good_threshold);
        }
    }
}

Creature_society::~Creature_society(){
    for(int i=0; i<this->total; i++){
        delete creature[i];
    }
    delete[] creature;
    cout << "The creature society has been destroyed" << endl;
}

Creature::Creature(const Creature& the_clone){ //Copy constructor of creature
    this->Name = the_clone.Name;    // Copying all the
    this->Life = the_clone.Life;    // informations that describes
    this->index = the_clone.index;  // each creature
}

Good_creature::Good_creature(const int L, Creature_society* index, string name, const int Thresh) : threshold(Thresh), Creature(L, index, name){
    cout << this->get_name() << ", a good creature just created." << endl;
}

Good_creature::Good_creature(const Good_creature& the_good_clone) : Creature(the_good_clone){
    this->threshold = the_good_clone.threshold; //Copying the threshold to the new creature
    cout << this->get_name() << "'s good clone just created with name : " << this->get_name() << " and life of " << this->get_life() << " points."<< endl;
}

Good_creature::~Good_creature(){
    cout << this->get_name() << ", good creature just destroyed." << endl;
}

Bad_creature::Bad_creature(const int L, Creature_society* index, string name, const int Thresh) : threshold(Thresh), Creature(L, index, name){
    cout << this->get_name()  << ", a bad creature just created." << endl;
}

Bad_creature::Bad_creature(const Bad_creature& the_bad_clone):Creature(the_bad_clone){
    this->threshold = the_bad_clone.threshold; // Copying the threshold to the new creature
    cout << this->get_name()  << "'s bad clone just made with name : " << this->get_name() << " and life of " << this->get_life() << " points."<< endl;
}

Bad_creature::~Bad_creature(){
    cout << this->get_name() << ", bad creature just destroyed." << endl;
}

void Creature_society::beating_the_creature(int seat){
    if((creature[seat]->is_a_good() == true) && (creature[seat]->is_a_zombie() == false)){          // When beating the creature
        creature[seat]->beat();                                                                     // just calling creature's 
    }else if((creature[seat]->is_a_good() == false) && (creature[seat]->is_a_zombie() == false)){   // beat (inline function) and i only decrease
        creature[seat]->beat();                                                                     // the life of this exact creature
    }
}

void Creature_society::blessing_the_creature(int seat){
    if((creature[seat]->is_a_good() == true) && (creature[seat]->is_a_zombie() == false)){          // When blessing the creature calling creature's
        creature[seat]->bless(seat);                                                                // bless function and passing the exact  
    }else if((creature[seat]->is_a_good() == false) && (creature[seat]->is_a_zombie() == false)){   // creature as an argument into the bless
        creature[seat]->bless(seat);                                                                // (need it to call other functions)
    }
}

int Creature_society::no_of_good(){
    for(int i = 0; i < total; i++){
        if(creature[i]->is_a_good() == true) ++total_good;
    }
    return total_good;
}

int Creature_society::no_of_zombies(){
    for(int i = 0; i < total; i++){
        if(creature[i]->is_a_zombie() == true) ++total_zombies;
    }
    return total_zombies;
}

void Creature_society::clone_next(int ID){
    int next_seat = 0;
    if(ID == total-1){
        Creature** ptr = &creature[next_seat]; // Making this pointer (ptr) to have access in creature society private members (creature array)
        creature[ID]->clone(ptr);              // and clone the creature i need to clone in ptr position
    }else{
        next_seat = ID + 1;
        Creature** ptr = &creature[next_seat]; // Making this pointer (ptr) to have access in creature society private members (creature array)
        creature[ID]->clone(ptr);              // and clone the creature i need to clone in ptr position
    }
}

void Creature_society::clone_zombies(int ID){
    if(ID == total){
        cout << "You cannot clone at the end of the society. There are no more zombies beyond." << endl;
    }else{
        for(int i = ID + 1; i < total; i++){
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

void Good_creature::bless(int ID){
    if(get_life() > 0){ // If the creature isnt a zombie increase his life and check if it is greater than the threshold*
        set_life();
        cout << "Blessing the " << this->get_name() << ", a good creature and the current life is " << this->get_life() << " points."<< endl;
        if(is_good_healthy() == true){ // *if it is then clone it
            get_index()->clone_next(ID); // Index is a pointer and the type is creature society. This pointer is the link to call clone next that is a creature society member
        }
    }
}

void Good_creature::clone(Creature** next_creature){ // next_creature = ptr pointer
    delete *next_creature; // Deleting the next seat of the array to place the new creature aka clone
    *next_creature = new Good_creature(*this); // Calling the good creature's copy constructor
}

void Bad_creature::bless(int ID){
    if(get_life() > 0){
        set_life();
        cout << "Blessing the " << this->get_name() << ", a bad creature and the current life is " << this->get_life() << " points."<< endl;
        if(is_bad_healthy() == true){
            get_index()->clone_zombies(ID);
        }
    }
}

void Bad_creature::clone(Creature** next_creature){
    delete *next_creature;
    *next_creature = new Bad_creature(*this);
}