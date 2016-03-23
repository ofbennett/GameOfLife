#include <iostream>
#include <fstream>
#include <ctime>
#include <cassert>
#include <string>
#include <mpi.h>
#include <sstream>
#include "World.h"

using namespace std;

float time_calc(clock_t begin, clock_t end){
  float total_time = (end - begin)/static_cast<float>(CLOCKS_PER_SEC);
  return total_time;
}

int main(int argc, char **argv){
  clock_t start = clock();

  MPI_Init (&argc, &argv);
  int rank, mpi_size;
  MPI_Comm_rank (MPI_COMM_WORLD, &rank);
  MPI_Comm_size (MPI_COMM_WORLD, &mpi_size);

  cout << "I am rank " << rank << endl;
  cout << "There are " << mpi_size << " computers being used in total" << endl;

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

  ostringstream fname;
  fname << rank << "output.txt" << flush;

  int seed;
  ofstream outfile(fname.str().c_str());

  if(verbose){cout << "Running the Game of Life!" << endl;}

  if(Pseudorandom){
    seed = 100; // Pseudorandom seed
  }else{
    seed = static_cast<int>(time(NULL)); // Random seed
  }

//  World world(sizex,sizey,rank,mpi_size);
  // world.Populate(seed);
  //
  // world.WriteHeader(outfile,EndOfDays);
  // while(world.Day() < EndOfDays){
  //   world.Record(outfile);
  //   world.Update();
  // }

  clock_t finish = clock();
  if(verbose){
    cout << "The total time taken by rank " << rank << " was " << time_calc(start,finish) << " seconds\n";
  }else{
    cout << time_calc(start,finish) << endl;
  }
  MPI_Finalize();
  return EXIT_SUCCESS;
}
