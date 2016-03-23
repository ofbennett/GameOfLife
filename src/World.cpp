#include "World.h"

World::World(int sizex, int sizey, int rank, int mpi_size, int* mpi_dimentions,int* node_coord):
day(0),
sizex(sizex),
sizey(sizey),
sizex_local(sizex/mpi_dimentions[1]),
sizey_local(sizey/mpi_dimentions[0]),
sizex_halo((sizex/mpi_dimentions[1])+2),
sizey_halo((sizey/mpi_dimentions[0])+2),
rank(rank),
mpi_size(mpi_size),
mpi_rows(mpi_dimentions[0]),
mpi_cols(mpi_dimentions[1]),
mpi_row_coord(node_coord[0]),
mpi_col_coord(node_coord[1]),

send_right_buffer(new aliveness[sizey_local]),
send_left_buffer(new aliveness[sizey_local]),
send_up_buffer(new aliveness[sizex_local]),
send_down_buffer(new aliveness[sizex_local]),
send_corner_buffer(new aliveness[4]),
receive_right_buffer(new aliveness[sizey_local]),
receive_left_buffer(new aliveness[sizey_local]),
receive_up_buffer(new aliveness[sizex_local]),
receive_down_buffer(new aliveness[sizex_local]),
receive_corner_buffer(new aliveness[4]),

grid(sizex_local+2,vector<aliveness>(sizey_local+2)),
next_grid(sizex_local+2,vector<aliveness>(sizey_local+2)),
alive(true),
dead(false)
{

}

void World::Populate(int seed){
  srand(seed);
  for (int x=0;x<sizex_halo;x++) {
    for (int y=0;y<sizey_halo;y++) {
        grid[x][y] = rand()%2;
    }
  }
}

// To be MPI updated
void World::PopulateFromArray(aliveness data[],int array_length){
  assert(sizex*sizey == array_length);

  for (int x=0;x<sizex;x++) {
    for (int y=0;y<sizey;y++) {
        grid[x][y] = data[y + (sizey*x)];
    }
  }
}

void World::WriteHeader(ostream &out, int EndOfDays) const{
  out << sizex_local << " , " << sizey_local << " , " << EndOfDays << " , " << mpi_row_coord << " , " << mpi_col_coord << endl;
}

void World::Record(ostream &out) const{
  for (int x=1;x<sizex_local+1;x++) {
    for (int y=1;y<sizey_local+1;y++) {
       out << grid[x][y] << " , ";
    }
    out << endl;
  }
  out << endl;
}

void World::UpdateGrid(){
    for (int x=1;x<sizex_local+1;x++) {
      for (int y=1;y<sizey_local+1;y++) {
        next_grid[x][y] = NewState(x,y);
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

void World::UpdateBuffers(){
  UpdateLeftBuffer();
  UpdateRightBuffer();
  UpdateUpBuffer();
  UpdateDownBuffer();
  UpdateCornerBuffers();
}

void World::Communicate(){

}

void World::UnpackBuffers(){
  UnpackLeftBuffer();
  UnpackRightBuffer();
  UnpackUpBuffer();
  UnpackDownBuffer();
  UnpackCornerBuffers();
}

void World::UpdateLeftBuffer(){
  for (int y=1;y<sizey_local+1;y++){
    send_left_buffer[y-1] = grid[1][y];
  }
}
void World::UpdateRightBuffer(){
  for (int y=1;y<sizey_local+1;y++){
    send_right_buffer[y-1] = grid[sizex_halo-2][y];
  }
}
void World::UpdateUpBuffer(){
  for (int x=1;x<sizex_local+1;x++){
    send_up_buffer[x-1] = grid[x][1];
  }
}
void World::UpdateDownBuffer(){
  for (int x=1;x<sizex_local+1;x++){
    send_down_buffer[x-1] = grid[x][sizey_halo-2];
  }
}
void World::UpdateCornerBuffers(){
  send_corner_buffer[0] = grid[1][1];
  send_corner_buffer[1] = grid[sizex_halo-2][1];
  send_corner_buffer[2] = grid[1][sizey_halo-2];
  send_corner_buffer[3] = grid[sizex_halo-2][sizey_halo-2];
}

void World::UnpackLeftBuffer(){

}
void World::UnpackRightBuffer(){

}
void World::UnpackUpBuffer(){

}
void World::UnpackDownBuffer(){

}
void World::UnpackCornerBuffers(){

}

void World::SetGrid(int x, int y, aliveness val){
  grid[x][y] = val;
}
