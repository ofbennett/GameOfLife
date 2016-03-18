#include "World.h"


World::World(int sizex, int sizey):day(0),sizex(sizex),sizey(sizey),grid(sizex,vector<aliveness>(sizey)){

}

void World::Populate(int seed){
  srand(seed);
  for (int x=0;x<sizex;x++) {
    for (int y=0;y<sizey;y++) {
        grid[x][y] = rand()%2;
    }
  }
}

void World::Record(ostream &out) const{
  for (int x=0;x<sizex;x++) {
    for (int y=0;y<sizey;y++) {
       out << grid[x][y] << " , ";
    }
    out << endl;
  }
  out << endl;
}

void World::Update(){
  day += 1;
}

int World::Day() const{
  return day;
}

int World::Sizex() const{
  return sizex;
}

int World::Sizey() const{
  return sizey;
}

vector< vector< int > > World::Grid() const{
  return grid;
}

int World::Size() const{
  return sizex*sizey;
}
