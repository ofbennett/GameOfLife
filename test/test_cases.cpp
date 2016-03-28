#include <catch.hpp>
#include "World.h"
#include "tools.h"

TEST_CASE("Check live cells die with underpopulation using MPI"){

  aliveness data1[] = {0,0,0,0,
                       0,1,0,0,
                       0,0,0,0,
                       0,0,0,0};

  aliveness data2[] = {0,1,0,0,
                       0,1,0,0,
                       0,0,0,0,
                       0,0,0,0};
  int array1_length =  sizeof(data1) / sizeof(aliveness);
  int array2_length =  sizeof(data2) / sizeof(aliveness);

  int rank, mpi_size;
  MPI_Comm_rank (MPI_COMM_WORLD, &rank);
  MPI_Comm_size (MPI_COMM_WORLD, &mpi_size);
  assert((mpi_size == 1)||(mpi_size == 4));

  int sizex = 4*sqrt(mpi_size);
  int sizey = 4*sqrt(mpi_size);

  int mpi_dimentions[] = {0,0};
  int node_coord[] = {0,0};
  Find_MPI_Dimensions(sizex,sizey,mpi_size,mpi_dimentions);
  Find_Node_Coord(rank,mpi_dimentions,node_coord);

  World world1(sizex,sizey,rank,mpi_size,mpi_dimentions,node_coord);
  world1.PopulateFromArrayMPI(data1, array1_length);
  world1.UpdateBuffers();
  MPI_Barrier(MPI_COMM_WORLD);
  world1.Communicate();
  world1.UnpackBuffers();
  world1.UpdateGrid();

  World world2(sizex,sizey,rank,mpi_size,mpi_dimentions,node_coord);
  world2.PopulateFromArrayMPI(data2, array2_length);
  world2.UpdateBuffers();
  MPI_Barrier(MPI_COMM_WORLD);
  world2.Communicate();
  world2.UnpackBuffers();
  world2.UpdateGrid();

  for (int x=1;x<world1.Sizex_Halo()-1;x++) {
    for (int y=1;y<world1.Sizey_Halo()-1;y++) {
      REQUIRE(world1.Grid()[x][y] == 0);
    }
  }

  for (int x=1;x<world2.Sizex_Halo()-1;x++) {
    for (int y=1;y<world2.Sizey_Halo()-1;y++) {
      REQUIRE(world2.Grid()[x][y] == 0);
    }
  }

}

TEST_CASE("Check live cells die with overpopulation using MPI"){

  aliveness data1[] = {1,1,1,0,
                       1,1,1,0,
                       1,1,1,0,
                       0,0,0,0};

  aliveness data2[] = {1,1,1,0,
                       1,1,1,0,
                       1,1,0,0,
                       0,0,0,0};

  aliveness data3[] = {1,1,1,0,
                       1,1,0,0,
                       1,1,0,0,
                       0,0,0,0};

  aliveness data4[] = {1,1,0,0,
                       1,1,0,0,
                       1,1,0,0,
                       0,0,0,0};

  aliveness data5[] = {1,1,0,0,
                       1,1,0,0,
                       1,0,0,0,
                       0,0,0,0};

  int array1_length =  sizeof(data1) / sizeof(aliveness);
  int array2_length =  sizeof(data2) / sizeof(aliveness);
  int array3_length =  sizeof(data3) / sizeof(aliveness);
  int array4_length =  sizeof(data4) / sizeof(aliveness);
  int array5_length =  sizeof(data5) / sizeof(aliveness);

  int rank, mpi_size;
  MPI_Comm_rank (MPI_COMM_WORLD, &rank);
  MPI_Comm_size (MPI_COMM_WORLD, &mpi_size);
  assert((mpi_size == 1)||(mpi_size == 4));

  int sizex = 4*sqrt(mpi_size);
  int sizey = 4*sqrt(mpi_size);

  int mpi_dimentions[] = {0,0};
  int node_coord[] = {0,0};
  Find_MPI_Dimensions(sizex,sizey,mpi_size,mpi_dimentions);
  Find_Node_Coord(rank,mpi_dimentions,node_coord);

  World world1(sizex,sizey,rank,mpi_size,mpi_dimentions,node_coord);
  world1.PopulateFromArrayMPI(data1, array1_length);
  world1.UpdateBuffers();
  MPI_Barrier(MPI_COMM_WORLD);
  world1.Communicate();
  world1.UnpackBuffers();
  world1.UpdateGrid();

  World world2(sizex,sizey,rank,mpi_size,mpi_dimentions,node_coord);
  world2.PopulateFromArrayMPI(data2, array2_length);
  world2.UpdateBuffers();
  MPI_Barrier(MPI_COMM_WORLD);
  world2.Communicate();
  world2.UnpackBuffers();
  world2.UpdateGrid();

  World world3(sizex,sizey,rank,mpi_size,mpi_dimentions,node_coord);
  world3.PopulateFromArrayMPI(data3, array3_length);
  world3.UpdateBuffers();
  MPI_Barrier(MPI_COMM_WORLD);
  world3.Communicate();
  world3.UnpackBuffers();
  world3.UpdateGrid();

  World world4(sizex,sizey,rank,mpi_size,mpi_dimentions,node_coord);
  world4.PopulateFromArrayMPI(data4, array4_length);
  world4.UpdateBuffers();
  MPI_Barrier(MPI_COMM_WORLD);
  world4.Communicate();
  world4.UnpackBuffers();
  world4.UpdateGrid();

  World world5(sizex,sizey,rank,mpi_size,mpi_dimentions,node_coord);
  world5.PopulateFromArrayMPI(data5, array5_length);
  world5.UpdateBuffers();
  MPI_Barrier(MPI_COMM_WORLD);
  world5.Communicate();
  world5.UnpackBuffers();
  world5.UpdateGrid();


  REQUIRE(world1.Grid()[2][2] == 0);
  REQUIRE(world2.Grid()[2][2] == 0);
  REQUIRE(world3.Grid()[2][2] == 0);
  REQUIRE(world4.Grid()[2][2] == 0);
  REQUIRE(world5.Grid()[2][2] == 0);

}

TEST_CASE("Check live cells stay alive with correct neighbor number using MPI"){

  aliveness data1[] = {1,1,0,0,
                       1,1,0,0,
                       0,0,0,0,
                       0,0,0,0};

  aliveness data2[] = {1,1,0,0,
                       0,1,0,0,
                       0,0,0,0,
                       0,0,0,0};

  int array1_length =  sizeof(data1) / sizeof(aliveness);
  int array2_length =  sizeof(data2) / sizeof(aliveness);

  int rank, mpi_size;
  MPI_Comm_rank (MPI_COMM_WORLD, &rank);
  MPI_Comm_size (MPI_COMM_WORLD, &mpi_size);
  assert((mpi_size == 1)||(mpi_size == 4));

  int sizex = 4*sqrt(mpi_size);
  int sizey = 4*sqrt(mpi_size);

  int mpi_dimentions[] = {0,0};
  int node_coord[] = {0,0};
  Find_MPI_Dimensions(sizex,sizey,mpi_size,mpi_dimentions);
  Find_Node_Coord(rank,mpi_dimentions,node_coord);

  World world1(sizex,sizey,rank,mpi_size,mpi_dimentions,node_coord);
  world1.PopulateFromArrayMPI(data1, array1_length);
  world1.UpdateBuffers();
  MPI_Barrier(MPI_COMM_WORLD);
  world1.Communicate();
  world1.UnpackBuffers();
  world1.UpdateGrid();

  World world2(sizex,sizey,rank,mpi_size,mpi_dimentions,node_coord);
  world2.PopulateFromArrayMPI(data2, array2_length);
  world2.UpdateBuffers();
  MPI_Barrier(MPI_COMM_WORLD);
  world2.Communicate();
  world2.UnpackBuffers();
  world2.UpdateGrid();

  REQUIRE(world1.Grid()[2][2] == 1);
  REQUIRE(world2.Grid()[2][2] == 1);

}

TEST_CASE("Check dead cells stay dead unless 3 live neighbors using MPI"){

  aliveness data1[] = {0,0,0,0,
                       0,0,0,0,
                       0,0,0,0,
                       0,0,0,0};

  aliveness data2[] = {0,1,0,0,
                       0,0,0,0,
                       0,0,0,0,
                       0,0,0,0};

  aliveness data3[] = {1,1,0,0,
                       0,0,0,0,
                       0,0,0,0,
                       0,0,0,0};

  aliveness data4[] = {1,1,0,0,
                       1,0,0,0,
                       0,0,0,0,
                       0,0,0,0};


  int array1_length =  sizeof(data1) / sizeof(aliveness);
  int array2_length =  sizeof(data2) / sizeof(aliveness);
  int array3_length =  sizeof(data3) / sizeof(aliveness);
  int array4_length =  sizeof(data4) / sizeof(aliveness);

  int rank, mpi_size;
  MPI_Comm_rank (MPI_COMM_WORLD, &rank);
  MPI_Comm_size (MPI_COMM_WORLD, &mpi_size);
  assert((mpi_size == 1)||(mpi_size == 4));

  int sizex = 4*sqrt(mpi_size);
  int sizey = 4*sqrt(mpi_size);

  int mpi_dimentions[] = {0,0};
  int node_coord[] = {0,0};
  Find_MPI_Dimensions(sizex,sizey,mpi_size,mpi_dimentions);
  Find_Node_Coord(rank,mpi_dimentions,node_coord);

  World world1(sizex,sizey,rank,mpi_size,mpi_dimentions,node_coord);
  world1.PopulateFromArrayMPI(data1, array1_length);
  world1.UpdateBuffers();
  MPI_Barrier(MPI_COMM_WORLD);
  world1.Communicate();
  world1.UnpackBuffers();
  world1.UpdateGrid();

  World world2(sizex,sizey,rank,mpi_size,mpi_dimentions,node_coord);
  world2.PopulateFromArrayMPI(data2, array2_length);
  world2.UpdateBuffers();
  MPI_Barrier(MPI_COMM_WORLD);
  world2.Communicate();
  world2.UnpackBuffers();
  world2.UpdateGrid();

  World world3(sizex,sizey,rank,mpi_size,mpi_dimentions,node_coord);
  world3.PopulateFromArrayMPI(data3, array3_length);
  world3.UpdateBuffers();
  MPI_Barrier(MPI_COMM_WORLD);
  world3.Communicate();
  world3.UnpackBuffers();
  world3.UpdateGrid();

  World world4(sizex,sizey,rank,mpi_size,mpi_dimentions,node_coord);
  world4.PopulateFromArrayMPI(data4, array4_length);
  world4.UpdateBuffers();
  MPI_Barrier(MPI_COMM_WORLD);
  world4.Communicate();
  world4.UnpackBuffers();
  world4.UpdateGrid();

  REQUIRE(world1.Grid()[2][2] == 0);
  REQUIRE(world2.Grid()[2][2] == 0);
  REQUIRE(world3.Grid()[2][2] == 0);
  REQUIRE(world4.Grid()[2][2] == 1);

}

TEST_CASE("Check World edge behaviour - Direct test of MPI communication between nodes."){

  aliveness data1[] = {0,0,0,0,
                       0,0,0,0,
                       0,0,0,0,
                       0,0,0,0};

  aliveness data2[] = {0,1,0,0,
                       0,0,0,0,
                       0,0,0,0,
                       0,0,0,0};

  aliveness data3[] = {1,1,0,0,
                       0,0,0,0,
                       0,0,0,0,
                       1,1,0,0};

  aliveness data4[] = {1,1,0,1,
                       1,0,0,0,
                       0,0,0,0,
                       0,0,1,1};


  int array1_length =  sizeof(data1) / sizeof(aliveness);
  int array2_length =  sizeof(data2) / sizeof(aliveness);
  int array3_length =  sizeof(data3) / sizeof(aliveness);
  int array4_length =  sizeof(data4) / sizeof(aliveness);

  int rank, mpi_size;
  MPI_Comm_rank (MPI_COMM_WORLD, &rank);
  MPI_Comm_size (MPI_COMM_WORLD, &mpi_size);
  assert((mpi_size == 1)||(mpi_size == 4));

  int sizex = 4*sqrt(mpi_size);
  int sizey = 4*sqrt(mpi_size);

  int mpi_dimentions[] = {0,0};
  int node_coord[] = {0,0};
  Find_MPI_Dimensions(sizex,sizey,mpi_size,mpi_dimentions);
  Find_Node_Coord(rank,mpi_dimentions,node_coord);

  World world1(sizex,sizey,rank,mpi_size,mpi_dimentions,node_coord);
  world1.PopulateFromArrayMPI(data1, array1_length);
  world1.UpdateBuffers();
  MPI_Barrier(MPI_COMM_WORLD);
  world1.Communicate();
  world1.UnpackBuffers();
  world1.UpdateGrid();

  World world2(sizex,sizey,rank,mpi_size,mpi_dimentions,node_coord);
  world2.PopulateFromArrayMPI(data2, array2_length);
  world2.UpdateBuffers();
  MPI_Barrier(MPI_COMM_WORLD);
  world2.Communicate();
  world2.UnpackBuffers();
  world2.UpdateGrid();

  World world3(sizex,sizey,rank,mpi_size,mpi_dimentions,node_coord);
  world3.PopulateFromArrayMPI(data3, array3_length);
  world3.UpdateBuffers();
  MPI_Barrier(MPI_COMM_WORLD);
  world3.Communicate();
  world3.UnpackBuffers();
  world3.UpdateGrid();

  World world4(sizex,sizey,rank,mpi_size,mpi_dimentions,node_coord);
  world4.PopulateFromArrayMPI(data4, array4_length);
  world4.UpdateBuffers();
  MPI_Barrier(MPI_COMM_WORLD);
  world4.Communicate();
  world4.UnpackBuffers();
  world4.UpdateGrid();

  REQUIRE(world1.Grid()[1][2] == 0);
  REQUIRE(world2.Grid()[1][2] == 0);
  REQUIRE(world3.Grid()[1][2] == 1);
  REQUIRE(world4.Grid()[1][1] == 0);

}

TEST_CASE("Check World member functions"){

  aliveness data1[] = {0,0,0,0,
                       0,0,0,0,
                       0,0,0,0,
                       0,0,0,0};
  int array1_length =  sizeof(data1) / sizeof(aliveness);

  int rank, mpi_size;
  MPI_Comm_rank (MPI_COMM_WORLD, &rank);
  MPI_Comm_size (MPI_COMM_WORLD, &mpi_size);
  assert((mpi_size == 1)||(mpi_size == 4));

  int sizex = 4*sqrt(mpi_size);
  int sizey = 4*sqrt(mpi_size);

  int mpi_dimentions[] = {0,0};
  int node_coord[] = {0,0};
  Find_MPI_Dimensions(sizex,sizey,mpi_size,mpi_dimentions);
  Find_Node_Coord(rank,mpi_dimentions,node_coord);

  World world1(sizex,sizey,rank,mpi_size,mpi_dimentions,node_coord);
  world1.PopulateFromArrayMPI(data1, array1_length);

  for (int x=0;x<world1.Sizex_Halo();x++) {
    for (int y=0;y<world1.Sizey_Halo();y++) {
      REQUIRE(world1.Grid()[x][y] == 0);
    }
  }

  REQUIRE(world1.Day() == 0);
  REQUIRE(world1.Sizex() == 4*sqrt(mpi_size));
  REQUIRE(world1.Sizey() == 4*sqrt(mpi_size));
  REQUIRE(world1.Size() == 16*mpi_size);

}
