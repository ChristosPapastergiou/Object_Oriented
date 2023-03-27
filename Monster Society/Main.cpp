//Project3
#include <iostream>
#include <string>
#include "Class.h"

using namespace std;

int main(int argc, char* argv[]){
  if(argc != 6){
    cout << "Too many arguments or not enough. Try again" << endl;
    return 0;
  }

  srand(time(NULL)); //Need this for my rand actions and the random creature pick

  int N = atoi(argv[1]);          //
  int M = atoi(argv[2]);          //Project's
  int L = atoi(argv[3]);          //variables
  int good_thrsh = atoi(argv[4]); //
  int bad_thrsh = atoi(argv[5]);  //

  Creature_society* creature_society = new Creature_society(N, L, good_thrsh, bad_thrsh); //Making the creature society and the creatures

  for(int i=0; i<M; i++){   
    int random_seat = rand()%N;   //Picking random creature to bless or beat it,
    int random_act = rand()%2;    //the 0 means i beat the creature and 1 im blessing it
    if(random_act == 0){
      creature_society->beating_the_creature(random_seat);  //Just
    }else{                                                  //the
      creature_society->blessing_the_creature(random_seat); //functions
    }
  }

  if(creature_society->no_of_good() == N){            //
    cout << "Good Dominates in the world" << endl;    //
  }else if(creature_society->no_of_zombies() == N){   //Project's 
    cout << "This is a dead society" << endl;         //sentences
  }else{                                              //
    cout << "Try again to improve the world" << endl; //
  }

  delete creature_society; //Freeing the allocation i did to make the society

  return 0;
}