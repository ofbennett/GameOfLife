#ifndef WORLD_H_
#define WORLD_H_

#include <vector>
#include <cmath>
#include <iostream>
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
  vector< vector< int > > Grid() const;


private:
  int day;
  const int sizex;
  const int sizey;
  vector< vector< int > > grid;
};

#endif /* WORLD_H_ */
