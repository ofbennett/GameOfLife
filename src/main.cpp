#include <iostream>
#include "World.h"

using namespace std;

int main(int argc, char **argv){

  int EndOfDays = 10;

  cout << "Starting the Game of Life!" << endl;

  World world(10,10);
  world.Populate();

  while(world.Day() < EndOfDays){
    cout << "Day: " << world.Day() << endl;
    world.Record();
    world.Update();
  }
}
