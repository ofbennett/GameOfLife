#ifndef WORLD_H_
#define WORLD_H_

#include <vector>
#include <cmath>
#include <iostream>
#include <cassert>
#include <cstdlib>
#include <stdexcept>

using namespace std;

typedef bool aliveness;
typedef vector< aliveness > grid_type;

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
  grid_type Grid() const;
  aliveness NewState(int x, int y) const;
  void SetGrid(int x, int y, aliveness val);
  void SetNextGrid(int x, int y, aliveness val);
  aliveness GetGridVal(int x, int y) const;

private:
  int day;
  const int sizex;
  const int sizey;
  grid_type grid;
  grid_type next_grid;
  aliveness alive;
  aliveness dead;
};

#endif /* WORLD_H_ */
