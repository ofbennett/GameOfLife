#ifndef WORLD_H_
#define WORLD_H_

#include <vector>
#include <cmath>
#include <iostream>

typedef bool aliveness;

using namespace std;

class World {
public:
  World(int sizex, int sizey);
  void Populate(int seed);
  void Record(ostream &out) const;
  void Update();
  int Day() const;
  int Sizex() const;
  int Sizey() const;
  int Size() const;
  vector< vector< aliveness > > Grid() const;
  aliveness NewState(int x, int y) const;

private:
  int day;
  const int sizex;
  const int sizey;
  vector< vector< aliveness > > grid;
  vector< vector< aliveness > > next_grid;
  aliveness alive;
  aliveness dead;
};

#endif /* WORLD_H_ */
