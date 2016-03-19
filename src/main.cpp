#include <iostream>
#include <fstream>
#include <ctime>
#include "World.h"

using namespace std;

int main(int argc, char **argv){

  int sizex = 10;
  int sizey = 10;
  int EndOfDays = 4;
  bool Pseudorandom = false;

  int seed;
  ofstream outfile("test.txt");

  cout << "Starting the Game of Life!" << endl;

  if(Pseudorandom){
    seed = 100; // Pseudorandom seed
  }else{
    seed = static_cast<int>(time(NULL)); // Random seed
  }

  World world(sizex,sizey);
  world.Populate(seed);

  while(world.Day() < EndOfDays){
    cout << "Day: " << world.Day() << endl;
    world.Record(outfile);
    world.Update();
  }
}
