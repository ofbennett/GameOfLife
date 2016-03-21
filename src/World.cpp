#include "World.h"

World::World(int sizex, int sizey):
day(0),
sizex(sizex),
sizey(sizey),
grid(sizex,vector<aliveness>(sizey)),
next_grid(sizex,vector<aliveness>(sizey)),
alive(true),
dead(false)
{

}

void World::Populate(int seed){
  srand(seed);
  for (int x=0;x<sizex;x++) {
    for (int y=0;y<sizey;y++) {
        grid[x][y] = rand()%2;
    }
  }
}

void World::PopulateFromArray(aliveness data[],int array_length){
  assert(sizex*sizey == array_length);

  for (int x=0;x<sizex;x++) {
    for (int y=0;y<sizey;y++) {
        grid[x][y] = data[y + (sizey*x)];
    }
  }
}

void World::WriteHeader(ostream &out, int EndOfDays) const{
  out << sizex << " , " << sizey << " , " << EndOfDays << endl;
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

  #pragma omp parallel private(temp)
  {
    #pragma omp for
    for (int x=0;x<sizex;x++) {
      for (int y=0;y<sizey;y++) {
        next_grid[x][y] = NewState(x,y);
      }
    }
  }
  grid = next_grid;
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

grid_type World::Grid() const{
  return grid;
}

int World::Size() const{
  return sizex*sizey;
}

aliveness World::NewState(int x, int y) const{
  int newstate;
  int alive_neighbors = 0;
  int xn; // Neighbor x index
  int yn; // Neighbor y index
  bool TopXEdge = false;
  bool TopYEdge = false;
  bool BottomXEdge = false;
  bool BottomYEdge = false;

  // Check if we are at a grid edge
  if(x==sizex-1){TopXEdge=true;}
  if(y==sizey-1){TopYEdge=true;}
  if(x==0){BottomXEdge=true;}
  if(y==0){BottomYEdge=true;}

  // Count alive neighbors
  for (int i=0;i<3;i++) {
    for (int j=0;j<3;j++) {
      if((i==1)&&(j==1)){continue;}

      xn = x-1+i;
      yn = y-1+j;

      // Wrap index around to other side of grid if at an edge
      if((x-1+i)==sizex){xn = 0;}
      if((y-1+j)==sizey){yn = 0;}
      if((x-1+i)==-1){xn = sizex-1;}
      if((y-1+j)==-1){yn = sizey-1;}

      if(grid[xn][yn]==alive){alive_neighbors += 1;}
    }
  }

  if(grid[x][y]==alive){
    if((alive_neighbors==2)||(alive_neighbors==3)){newstate = alive;}
    else{newstate = dead;}
  }else if(grid[x][y]==dead){
    if(alive_neighbors==3){newstate = alive;}
    else{newstate = dead;}
  }else{
    throw logic_error("A lifeform on the grid has an aliveness which is neither alive or dead!");
  }
  return newstate;
}
