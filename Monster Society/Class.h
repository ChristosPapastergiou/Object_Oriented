//Project3
#include <iostream>
#include <string>

using namespace std;

class Creature_society{
private:
    int total, total_good, total_zombies; //Project's variables
    class Creature** creature; //Linking creature society with creature class to make the creatures
public:
    Creature_society(int, int, int, int);
    ~Creature_society();
    void beating_the_creature(int);  //The beat and bless 
    void blessing_the_creature(int); //of the creature society (called by main)
    void clone_next(int);    //
    void clone_zombies(int); //Project's
    int no_of_good();        //functions
    int no_of_zombies();     //
};

class Creature{
private:
    int Life;    //Project's
    string Name; //variables
    Creature_society* index; //The link to Creature society
public:
    Creature(const int L, Creature_society* index, string name):Life(L), index(index), Name(name){} //Initialize
    Creature(const Creature&); //Copy constructor (creature's all the other informations that needs to clone)
    virtual ~Creature(){}
    virtual bool is_a_good() const = 0; //Pure virtual
    virtual void bless(int) = 0; //Pure virtual
    virtual void clone(Creature**) = 0; //Pure virtual
    void beat(){--Life; cout << "Beating the " << this->get_name() << ", a" << ((is_a_good() == true) ? " good" : " bad") << " creature and current life of " << this->get_life() << " points."<< endl;} //Inline
    bool is_a_zombie(){if(Life == 0) return true; return false;} //Inline
    Creature_society* get_index(){return index;} //Inline (get)
    string get_name(){return Name;} //Inline (get)
    int get_life(){return Life;} //Inline (get)
    void set_life(){++Life;} //Inline (set)
};

class Good_creature: public Creature{
private:
    int threshold; //Project's variable
public:
    Good_creature(const int, Creature_society*, string, int);
    Good_creature(const Good_creature&); //Copy constructor (clone of the good creature)
    ~Good_creature();
    void bless(int);
    void clone(Creature**);
    bool is_a_good() const {return true;} //Inline
    bool is_good_healthy(){if(get_life() > threshold) return true; return false;} //Inline
    
};

class Bad_creature: public Creature{
private:
    int threshold; //Project's variable
public:
    Bad_creature(const int, Creature_society*, string, int);
    Bad_creature(const Bad_creature&); //Copy constructor (clone of the bad creature)
    ~Bad_creature();
    void bless(int);
    void clone(Creature**);
    bool is_a_good() const {return false;} //Inline
    bool is_bad_healthy(){if(get_life() > threshold) return true; return false;} //Inline
};