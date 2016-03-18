#ifndef WORLD_H_
#define WORLD_H_

#include <vector>
using namespace std;

class World {
public:
  World(int sizex, int sizey);
  void Populate();
  void Record() const;
  void Update();
  int Day() const;
  int Sizex() const;
  int Sizey() const;
  vector< vector< int > > Lifeforms() const;


private:
  int day;
  const int sizex;
  const int sizey;
  vector< vector< int > > lifeforms;
};

#endif /* WORLD_H_ */
