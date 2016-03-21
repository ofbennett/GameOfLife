#include <iostream>
#include <fstream>
#include <ctime>
#include <cassert>
#include <string>
#include <omp.h>
#include "World.h"

using namespace std;

float time_calc(double begin, double end){
  float total_time = (end - begin);
  return total_time;
}

int main(int argc, char **argv){
  double start = omp_get_wtime();

  int sizex;
  int sizey;
  int EndOfDays;
  bool Pseudorandom;
  bool verbose;

  if(argc == 1){
    sizex = 500;
    sizey = 500;
    EndOfDays = 100;
    Pseudorandom = false;
    verbose = true;
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

  if(verbose){cout << "Running the Game of Life!" << endl;}

  if(Pseudorandom){
    seed = 100; // Pseudorandom seed
  }else{
    seed = static_cast<int>(time(NULL)); // Random seed
  }

  World world(sizex,sizey);
  world.Populate(seed);

  world.WriteHeader(outfile,EndOfDays);
  while(world.Day() < EndOfDays){
    world.Record(outfile);
    world.Update();
  }
  double finish = omp_get_wtime();
  if(verbose){
    cout << "The total time taken was " << time_calc(start,finish) << " seconds\n";
  }else{
    cout << time_calc(start,finish) << endl;
  }
  return EXIT_SUCCESS;
}
