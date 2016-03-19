#include <iostream>
#include <fstream>
#include <ctime>
#include "World.h"

using namespace std;

int main(int argc, char **argv){

  int sizex = 300;
  int sizey = 300;
  int EndOfDays = 50;
  bool Pseudorandom = false;
  bool verbose = false;

  int seed;
  ofstream outfile("output.txt");

  cout << "Running the Game of Life!" << endl;

  if(Pseudorandom){
    seed = 100; // Pseudorandom seed
  }else{
    seed = static_cast<int>(time(NULL)); // Random seed
  }

  World world(sizex,sizey);
  world.Populate(seed);

  world.WriteHeader(outfile,EndOfDays);
  while(world.Day() < EndOfDays){
    if(verbose){cout << "Day: " << world.Day() << endl;}
    world.Record(outfile);
    world.Update();
  }
}
