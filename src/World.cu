#include "World.h"

World::World(int sizex, int sizey):
day(0),
sizex(sizex),
sizey(sizey),
grid(sizex*sizey),
next_grid(sizex*sizey),
d_grid(sizex*sizey),
d_next_grid(sizex*sizey),
index(sizex*sizey),
alive(1),
dead(0)
{
  for (int i=0;i<sizex*sizey;i++) {
    index[i] = i;
  }
}

void World::Populate(int seed){
  srand(seed);
  for (int x=0;x<sizex;x++) {
    for (int y=0;y<sizey;y++) {
        this->SetGrid(x,y,rand()%2);
    }
  }
}

void World::PopulateFromArray(aliveness data[],int array_length){
  assert(sizex*sizey == array_length);

  for (int x=0;x<sizex;x++) {
    for (int y=0;y<sizey;y++) {
        this->SetGrid(x,y,data[y + (sizey*x)]);
    }
  }
}

void World::WriteHeader(ostream &out, int EndOfDays) const{
  out << sizex << " , " << sizey << " , " << EndOfDays << endl;
}

void World::Record(ostream &out) const{

  for (int x=0;x<sizex;x++) {
    for (int y=0;y<sizey;y++) {
       out << this->GetGridVal(x,y) << " , ";
    }
    out << endl;
  }
  out << endl;
}

void World::Update(){

  // UpdateKernel<<<1,64>>>(d_grid,index,d_next_grid,sizex,sizey);
  UpdateKernel(d_grid,index,d_next_grid,grid,sizex,sizey);

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

host_grid_type World::Grid() const{
  return grid;
}

int World::Size() const{
  return sizex*sizey;
}

void World::SetGrid(int x, int y, aliveness val){
  grid[y + x*sizey] = val;
}

void World::SetNextGrid(int x, int y, aliveness val){
  next_grid[y + x*sizey] = val;
}

aliveness World::GetGridVal(int x, int y) const{
  aliveness val = grid[y + x*sizey];
  return val;
}
