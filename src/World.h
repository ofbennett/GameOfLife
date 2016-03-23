#ifndef WORLD_H_
#define WORLD_H_

#include <vector>
#include <cmath>
#include <iostream>
#include <cassert>
#include <cstdlib>
#include <stdexcept>
#include <mpi.h>

using namespace std;

typedef int aliveness;
typedef vector< vector< aliveness > > grid_type;

class World {
public:
  World(int sizex, int sizey, int rank, int mpi_size,int* mpi_dimentions,int* node_coord);
  void Populate(int seed);
  void PopulateFromArray(aliveness data[], int array_length);
  void WriteHeader(ostream &out, int EndOfDays) const;
  void Record(ostream &out) const;
  void UpdateGrid();
  int Day() const;
  int Sizex() const;
  int Sizey() const;
  int Size() const;
  grid_type Grid() const;
  aliveness NewState(int x, int y) const;
  void UpdateBuffers();
  void Communicate();
  void UnpackBuffers();
  void UpdateLeftBuffer();
  void UpdateRightBuffer();
  void UpdateUpBuffer();
  void UpdateDownBuffer();
  void UpdateCornerBuffers();
  void UnpackLeftBuffer();
  void UnpackRightBuffer();
  void UnpackUpBuffer();
  void UnpackDownBuffer();
  void UnpackCornerBuffers();
  void SetGrid(int x, int y, aliveness val);

private:
  int day;
  const int sizex;
  const int sizex_local;
  const int sizex_halo;
  const int sizey;
  const int sizey_local;
  const int sizey_halo;
  const int rank;
  const int mpi_size;
  const int mpi_rows;
  const int mpi_cols;
  const int mpi_row_coord;
  const int mpi_col_coord;
  unique_ptr<aliveness[]> send_right_buffer;
  unique_ptr<aliveness[]> send_left_buffer;
  unique_ptr<aliveness[]> send_up_buffer;
  unique_ptr<aliveness[]> send_down_buffer;
  unique_ptr<aliveness[]> send_corner_buffer;
  unique_ptr<aliveness[]> receive_right_buffer;
  unique_ptr<aliveness[]> receive_left_buffer;
  unique_ptr<aliveness[]> receive_up_buffer;
  unique_ptr<aliveness[]> receive_down_buffer;
  unique_ptr<aliveness[]> receive_corner_buffer;
  grid_type grid;
  grid_type next_grid;
  aliveness alive;
  aliveness dead;
};

#endif /* WORLD_H_ */
