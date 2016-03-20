#include <iostream>
#include <fstream>
#include <ctime>
#include "World.h"

using namespace std;

float time_calc(clock_t begin, clock_t end){
  float total_time = (end - begin)/static_cast<float>(CLOCKS_PER_SEC);
  return total_time;
}

int main(int argc, char **argv){

  int sizex = 100;
  int sizey = 100;
  int EndOfDays = 100;
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

  clock_t start = clock();
  World world(sizex,sizey);
  world.Populate(seed);

  world.WriteHeader(outfile,EndOfDays);
  while(world.Day() < EndOfDays){
    if(verbose){cout << "Day: " << world.Day() << endl;}
    world.Record(outfile);
    world.Update();
  }
  clock_t finish = clock();
  cout << "The total time taken was " << time_calc(start,finish) << " seconds\n";
  return EXIT_SUCCESS;
}
