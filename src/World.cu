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
//thrust::copy(d_grid.begin(), d_grid.end(), grid.begin());
}

void World::PopulateFromArray(aliveness data[],int array_length){
  assert(sizex*sizey == array_length);

  for (int x=0;x<sizex;x++) {
    for (int y=0;y<sizey;y++) {
        this->SetGrid(x,y,data[y + (sizey*x)]);
    }
  }
//thrust::copy(d_grid.begin(), d_grid.end(), grid.begin());
}

void World::WriteHeader(ostream &out, int EndOfDays) const{
  out << sizex << " , " << sizey << " , " << EndOfDays << endl;
}

void World::Record(ostream &out) const{
//  thrust::copy(d_grid.begin(), d_grid.end(), grid.begin());
  for (int x=0;x<sizex;x++) {
    for (int y=0;y<sizey;y++) {
       out << this->GetGridVal(x,y) << " , ";
    }
    out << endl;
  }
  out << endl;
}

void World::Update(){

  // for (int x=0;x<sizex;x++) {
  //   for (int y=0;y<sizey;y++) {
  //     this->SetNextGrid(x,y,NewState(x,y));
  //   }
  // }
  // grid = next_grid;

  // UpdateKernel<<<1,64>>>(d_grid,index,d_next_grid,sizex,sizey);
  UpdateKernel(d_grid,index,d_next_grid,sizex,sizey);

//  thrust::copy(d_next_grid.begin(), d_next_grid.end(), d_grid.begin());

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

// aliveness World::NewState(int x, int y) const{
//   int newstate;
//   int alive_neighbors = 0;
//   int xn; // Neighbor x index
//   int yn; // Neighbor y index
//
//   // Count alive neighbors
//   for (int i=0;i<3;i++) {
//     for (int j=0;j<3;j++) {
//       if((i==1)&&(j==1)){continue;}
//
//       xn = x-1+i;
//       yn = y-1+j;
//
//       // Wrap index around to other side of grid if at an edge
//       if((x-1+i)==sizex){xn = 0;}
//       if((y-1+j)==sizey){yn = 0;}
//       if((x-1+i)==-1){xn = sizex-1;}
//       if((y-1+j)==-1){yn = sizey-1;}
//
//       if(this->GetGridVal(xn,yn)==alive){alive_neighbors += 1;}
//     }
//   }
//
//   if(this->GetGridVal(x,y)==alive){
//     if((alive_neighbors==2)||(alive_neighbors==3)){newstate = alive;}
//     else{newstate = dead;}
//   }else if(this->GetGridVal(x,y)==dead){
//     if(alive_neighbors==3){newstate = alive;}
//     else{newstate = dead;}
//   }else{
//     throw logic_error("A lifeform on the grid has an aliveness which is neither alive or dead!");
//   }
//   return newstate;
// }

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
