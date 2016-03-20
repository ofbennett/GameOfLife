#include <iostream>
#include <fstream>
#include <ctime>
#include <cassert>
#include <string>
#include "World.h"

using namespace std;

float time_calc(clock_t begin, clock_t end){
  float total_time = (end - begin)/static_cast<float>(CLOCKS_PER_SEC);
  return total_time;
}

int main(int argc, char **argv){

  int sizex;
  int sizey;
  int EndOfDays;
  bool Pseudorandom;
  bool verbose;

  if(argc == 1){
    sizex = 100;
    sizey = 100;
    EndOfDays = 100;
    Pseudorandom = false;
    verbose = false;
  }else{
    string config_path = argv[1];
    ifstream config_file(config_path.c_str());

    string label;
    config_file >> label >> sizex;
    assert(label=="sizex:");
    config_file >> label >> sizey;
    assert(label=="sizey:");
    config_file >> label >> EndOfDays ;
    assert(label=="EndOfDays:");
    config_file >> label >> Pseudorandom;
    assert(label=="Pseudorandom:");
    config_file >> label >> verbose ;
    assert(label=="verbose:");
  }

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
