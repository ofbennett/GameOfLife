#include <catch.hpp>
#include "World.h"
#include "tools.h"

TEST_CASE("Check live cells die with underpopulation"){

  int rank, mpi_size;
  MPI_Comm_rank (MPI_COMM_WORLD, &rank);
  MPI_Comm_size (MPI_COMM_WORLD, &mpi_size);
  // assert(mpi_size == 4)

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

  int sizex = 4;
  int sizey = 4;

  int mpi_dimentions[] = {0,0};
  int node_coord[] = {0,0};
  Find_MPI_Dimentions(sizex,sizey,mpi_size,mpi_dimentions);
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
  //
  // for (int x=1;x<world2.Sizex_Halo()-1;x++) {
  //   for (int y=1;y<world2.Sizey_Halo()-1;y++) {
  //     REQUIRE(world2.Grid()[x][y] == 0);
  //   }
  // }

}

/*
TEST_CASE("Check live cells die with overpopulation"){

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

  World world1(4,4);
  world1.PopulateFromArray(data1, array1_length);
  world1.Update();

  World world2(4,4);
  world2.PopulateFromArray(data2, array2_length);
  world2.Update();

  World world3(4,4);
  world3.PopulateFromArray(data3, array3_length);
  world3.Update();

  World world4(4,4);
  world4.PopulateFromArray(data4, array4_length);
  world4.Update();

  World world5(4,4);
  world5.PopulateFromArray(data5, array5_length);
  world5.Update();

  REQUIRE(world1.Grid()[1][1] == 0);
  REQUIRE(world2.Grid()[1][1] == 0);
  REQUIRE(world3.Grid()[1][1] == 0);
  REQUIRE(world4.Grid()[1][1] == 0);
  REQUIRE(world5.Grid()[1][1] == 0);

}
TEST_CASE("Check live cells stay alive with correct neighbor number"){

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

  World world1(4,4);
  world1.PopulateFromArray(data1, array1_length);
  world1.Update();

  World world2(4,4);
  world2.PopulateFromArray(data2, array2_length);
  world2.Update();

  REQUIRE(world1.Grid()[1][1] == 1);
  REQUIRE(world2.Grid()[1][1] == 1);

}
TEST_CASE("Check dead cells stay dead unless 3 live neighbors"){

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

  World world1(4,4);
  world1.PopulateFromArray(data1, array1_length);
  world1.Update();

  World world2(4,4);
  world2.PopulateFromArray(data2, array2_length);
  world2.Update();

  World world3(4,4);
  world3.PopulateFromArray(data3, array3_length);
  world3.Update();

  World world4(4,4);
  world4.PopulateFromArray(data4, array4_length);
  world4.Update();

  REQUIRE(world1.Grid()[1][1] == 0);
  REQUIRE(world2.Grid()[1][1] == 0);
  REQUIRE(world3.Grid()[1][1] == 0);
  REQUIRE(world4.Grid()[1][1] == 1);

}
TEST_CASE("Check World edge behaviour"){

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

  World world1(4,4);
  world1.PopulateFromArray(data1, array1_length);
  world1.Update();

  World world2(4,4);
  world2.PopulateFromArray(data2, array2_length);
  world2.Update();

  World world3(4,4);
  world3.PopulateFromArray(data3, array3_length);
  world3.Update();

  World world4(4,4);
  world4.PopulateFromArray(data4, array4_length);
  world4.Update();

  REQUIRE(world1.Grid()[0][1] == 0);
  REQUIRE(world2.Grid()[0][1] == 0);
  REQUIRE(world3.Grid()[0][1] == 1);
  REQUIRE(world4.Grid()[0][0] == 0);

}
TEST_CASE("Check World member functions"){

  aliveness data1[] = {0,0,0,0,
                       0,0,0,0,
                       0,0,0,0,
                       0,0,0,0};
  int array1_length =  sizeof(data1) / sizeof(aliveness);

  World world1(4,4);
  world1.PopulateFromArray(data1, array1_length);

  for (int x=0;x<world1.Sizex();x++) {
    for (int y=0;y<world1.Sizey();y++) {
      REQUIRE(world1.Grid()[x][y] == 0);
    }
  }

  REQUIRE(world1.Day() == 0);
  REQUIRE(world1.Sizex() == 4);
  REQUIRE(world1.Sizey() == 4);
  REQUIRE(world1.Size() == 16);

}
*/
