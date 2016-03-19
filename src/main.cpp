#include <iostream>
#include <fstream>
#include <ctime>
#include "World.h"

using namespace std;

int main(int argc, char **argv){

  int sizex = 30;
  int sizey = 30;
  int EndOfDays = 30;
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

  world.WriteHeader(outfile,EndOfDays);
  while(world.Day() < EndOfDays){
    cout << "Day: " << world.Day() << endl;
    world.Record(outfile);
    world.Update();
  }
}
