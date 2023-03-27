#include <string>
#include <iostream>

#include "Class.h"

using namespace std;

int main(int argc, char* argv[]){
  if(argc != 6){
    cout << "Too many arguments or not enough. Try again" << endl;
    return 0;
  }

  srand(time(NULL));

  int N = atoi(argv[1]);
  int M = atoi(argv[2]);
  int L = atoi(argv[3]);
  int good_thrsh = atoi(argv[4]);
  int bad_thrsh = atoi(argv[5]);

  Creature_society* creature_society = new Creature_society(N, L, good_thrsh, bad_thrsh);

  for(int i = 0; i < M; i++){   
    int random_seat = rand() % N;   // Pick random creature to bless or beat it,
    int random_act = rand() % 2;

    if(random_act == 0){
      creature_society->beating_the_creature(random_seat);
    }else{
      creature_society->blessing_the_creature(random_seat);
    }
  }

  if(creature_society->no_of_good() == N){
    cout << "Good Dominates in the world" << endl;
  }else if(creature_society->no_of_zombies() == N){
    cout << "This is a dead society" << endl;
  }else{
    cout << "Try again to improve the world" << endl;
  }

  delete creature_society;

  return 0;
}