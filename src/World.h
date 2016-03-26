#ifndef WORLD_H_
#define WORLD_H_

#include <vector>
#include <cmath>
#include <iostream>
#include <cassert>
#include <cstdlib>
#include <stdexcept>
#include <thrust/device_vector.h>
#include <thrust/host_vector.h>
#include <thrust/transform.h>
#include <thrust/copy.h>
#include "functors.h"

using namespace std;

typedef int aliveness;
typedef thrust::device_vector< aliveness > device_grid_type;
typedef thrust::host_vector< aliveness > host_grid_type;

class World {
public:
  World(int sizex, int sizey);
void Populate(int seed);
void PopulateFromArray(aliveness data[], int array_length);
void WriteHeader(ostream &out, int EndOfDays) const;
void Record(ostream &out) const;
void Update();
int Day() const;
int Sizex() const;
int Sizey() const;
int Size() const;
host_grid_type Grid() const;
void SetGrid(int x, int y, aliveness val);
void SetNextGrid(int x, int y, aliveness val);
aliveness GetGridVal(int x, int y) const;

private:
  int day;
  const int sizex;
  const int sizey;
  device_grid_type d_next_grid;
  device_grid_type d_grid;
  host_grid_type next_grid;
  host_grid_type grid;
  aliveness alive;
  aliveness dead;
  thrust::device_vector< int > index;
};

#endif /* WORLD_H_ */
