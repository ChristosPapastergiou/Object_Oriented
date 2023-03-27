#include <iostream>
#include "Class.h"
#include <time.h> 

using namespace std;

int main(int argc, char* argv[]){
  if((argc != 5)){
    cout << "Too many arguments or not enough. Try again" << endl;
    return 0;
  }

  srand(time(NULL));

  int N = atoi(argv[1]);
  int NSegs = atoi(argv[2]);
  int K = atoi(argv[3]);
  int Percent = atoi(argv[4]);
  
  if(Percent > 100 || Percent < 0){
    cout << "The percentage you gave is not valid. Try again." << endl;
    return 0;
  }

  Attiki* attiki = new Attiki(K, NSegs);

  for(int i=0; i<N; i++){
    attiki->operate(Percent);
  }

  delete attiki;
  
  return 0;
}