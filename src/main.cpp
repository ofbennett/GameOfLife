#include <iostream>
#include <ctime>
#include "World.h"

using namespace std;

int main(int argc, char **argv){

  int EndOfDays = 10;
  bool SeedLife = false;

  int seed;

  cout << "Starting the Game of Life!" << endl;
  
  if(SeedLife){
    seed = 100;
  }else{
    seed = static_cast<int>(time(NULL));
  }

  World world(10,10);
  world.Populate(seed);

  while(world.Day() < EndOfDays){
    cout << "Day: " << world.Day() << endl;
    world.Record();
    world.Update();
  }
}
