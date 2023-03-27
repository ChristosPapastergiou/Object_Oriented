#include <string>
#include <iostream>

using namespace std;

class Creature_society{
private:
    int total, total_good, total_zombies;
    class Creature** creature; // Linking creature society with creature class to make the creatures
public:
    Creature_society(int, int, int, int);
    ~Creature_society();
    void beating_the_creature(int); 
    void blessing_the_creature(int);
    void clone_next(int);
    void clone_zombies(int);
    int no_of_good();
    int no_of_zombies();
};

class Creature{
private:
    int Life;
    string Name;
    Creature_society* index; // Link to Creature society
public:
    Creature(const int L, Creature_society* index, string name):Life(L), index(index), Name(name){} // Initialize
    Creature(const Creature&); // Copy constructor (creature's all the other informations that needs to clone)
    virtual ~Creature(){}
    virtual bool is_a_good() const = 0;
    virtual void bless(int) = 0;
    virtual void clone(Creature**) = 0;
    void beat(){--Life; cout << "Beating the " << this->get_name() << ", a" << ((is_a_good() == true) ? " good" : " bad") << " creature and current life of " << this->get_life() << " points."<< endl;}
    bool is_a_zombie(){if(Life == 0) return true; return false;}
    Creature_society* get_index(){return index;}
    string get_name(){return Name;}
    int get_life(){return Life;}
    void set_life(){++Life;}
};

class Good_creature: public Creature{
private:
    int threshold;
public:
    Good_creature(const int, Creature_society*, string, int);
    Good_creature(const Good_creature&); // Copy constructor (clone of the good creature)
    ~Good_creature();
    void bless(int);
    void clone(Creature**);
    bool is_a_good() const {return true;}
    bool is_good_healthy(){if(get_life() > threshold) return true; return false;}
    
};

class Bad_creature: public Creature{
private:
    int threshold;
public:
    Bad_creature(const int, Creature_society*, string, int);
    Bad_creature(const Bad_creature&); // Copy constructor (clone of the bad creature)
    ~Bad_creature();
    void bless(int);
    void clone(Creature**);
    bool is_a_good() const {return false;}
    bool is_bad_healthy(){if(get_life() > threshold) return true; return false;}
};