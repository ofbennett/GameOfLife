#ifndef TOOLS_H_
#define TOOLS_H_

double time_calc(double begin, double end){
  double total_time = (end - begin);
  return total_time;
}

void Find_MPI_Dimentions(int sizex, int sizey, int mpi_size, int* mpi_dimentions){

  assert(mpi_size!=0);

  if(mpi_size%7==0){
    mpi_dimentions[1] = 7;
    mpi_dimentions[0] = mpi_size/7;
  }else if(mpi_size%5==0){
    mpi_dimentions[1] = 5;
    mpi_dimentions[0] = mpi_size/5;
  }else if(mpi_size%4==0){
    if(mpi_size!=4){
      mpi_dimentions[1] = 4;
      mpi_dimentions[0] = mpi_size/4;
    }else{
      mpi_dimentions[1] = 2;
      mpi_dimentions[0] = 2;
    }
  }else if(mpi_size%3==0){
    mpi_dimentions[1] = 3;
    mpi_dimentions[0] = mpi_size/3;
  }else if(mpi_size%2==0){
    mpi_dimentions[1] = 2;
    mpi_dimentions[0] = mpi_size/2;
  }else{
    mpi_dimentions[1] = 1;
    mpi_dimentions[0] = mpi_size;
  }

  assert(sizey%mpi_dimentions[0]==0); // No remainders
  assert(sizex%mpi_dimentions[1]==0); // No remainders
}

void Find_Node_Coord(int rank,int* mpi_dimentions,int* node_coord){
  // Rank increases (+1) down first column, then second, etc.
  int rows = mpi_dimentions[0];
  int cols = mpi_dimentions[1];
  node_coord[1] = (rank)/rows;
  node_coord[0] = rank - (node_coord[1]*rows);
}

#endif /* TOOLS_H_ */
