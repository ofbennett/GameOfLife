#include <iostream>
#include <fstream>
#include <ctime>
#include <cassert>
#include <string>
#include <mpi.h>
#include <sstream>
#include "World.h"

using namespace std;

double time_calc(double begin, double end){
  double total_time = (end - begin);
  return total_time;
}

void Find_MPI_Dimentions(int sizex, int sizey, int mpi_size, int* mpi_dimentions){

  assert(mpi_size!=0);

  if(mpi_size%5==0){
    mpi_dimentions[0] = 5;
    mpi_dimentions[1] = mpi_size/5;
  }else if(mpi_size%4==0){
    if(mpi_size!=4){
      mpi_dimentions[0] = 4;
      mpi_dimentions[1] = mpi_size/4;
    }else{
      mpi_dimentions[0] = 2;
      mpi_dimentions[1] = 2;
    }
  }else if(mpi_size%3==0){
    mpi_dimentions[0] = 3;
    mpi_dimentions[1] = mpi_size/3;
  }else if(mpi_size%2==0){
    mpi_dimentions[0] = 2;
    mpi_dimentions[1] = mpi_size/2;
  }else{
    mpi_dimentions[0] = 1;
    mpi_dimentions[1] = mpi_size;
  }

  assert(sizey%mpi_dimentions[0]==0); // No remainders
  assert(sizex%mpi_dimentions[1]==0); // No remainders
}

int main(int argc, char **argv){

  MPI_Init (&argc, &argv);
  // Need to barrier before measuring time to make sure all nodes start together
  MPI_Barrier(MPI_COMM_WORLD);
  double start = MPI_Wtime();
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
    sizex = 120;
    sizey = 120;
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

  int mpi_dimentions[] = {0,0};
  Find_MPI_Dimentions(sizex,sizey,mpi_size,mpi_dimentions);
  World world(sizex,sizey,rank,mpi_size,mpi_dimentions);
  // world.Populate(seed);
  //
  // world.WriteHeader(outfile,EndOfDays);
  // while(world.Day() < EndOfDays){
  //   world.Record(outfile);
  //   world.Update();
  // }

  // Need to barrier before measuring time to make sure all nodes are finished
  MPI_Barrier(MPI_COMM_WORLD);
  double finish = MPI_Wtime();
  if(verbose){
    cout << "The total time taken by rank " << rank << " was " << time_calc(start,finish) << " seconds\n";
  }
  if(rank==0){
    ofstream timefile("time.txt");
    timefile << time_calc(start,finish);
  }
  MPI_Finalize();
  return EXIT_SUCCESS;
}
