#ifndef FUNCTORS_H_
#define FUNCTORS_H_


typedef int aliveness;
typedef thrust::device_vector< aliveness > device_grid_type;
typedef thrust::host_vector< aliveness > host_grid_type;

int Getx(int index, int sizey){
  int x = index/sizey;
  return x;
}

int Gety(int index, int sizey){
  int y = index - (index/sizey);
  return y;
}

// aliveness GetGridVal2(int x, int y, int sizey, device_grid_type _grid){
//   aliveness val = _grid[y + x*sizey];
//   return val;
// }

aliveness GetGridVal2(int x, int y, int sizey){

  return 1;
}

struct NewState {
  // device_grid_type old_grid;
  const aliveness alive;
  const aliveness dead;
  const int sizex;
  const int sizey;
  // NewState(device_grid_type old_grid, int sizex, int sizey);
  NewState(int sizex, int sizey);
  aliveness operator()(aliveness cell, int index);

};

// NewState::NewState(device_grid_type old_grid, int sizex, int sizey): old_grid(old_grid),alive(true),dead(false),sizex(sizex),sizey(sizey){
//
// }

NewState::NewState(int sizex, int sizey): alive(1),dead(0),sizex(sizex),sizey(sizey){

}

aliveness NewState::operator()(aliveness cell, int index){
    int newstate;
    int alive_neighbors = 0;
    int xn; // Neighbor x index
    int yn; // Neighbor y index

    int x = Getx(index,sizey);
    int y = Gety(index,sizey);

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

        // if(GetGridVal2(xn,yn,sizey,old_grid)==alive){alive_neighbors += 1;}
        if(GetGridVal2(xn,yn,sizey)==alive){alive_neighbors += 1;}
      }
    }

    if(cell==alive){
      if((alive_neighbors==2)||(alive_neighbors==3)){newstate = alive;}
      else{newstate = dead;}
    }else if(cell==dead){
      if(alive_neighbors==3){newstate = alive;}
      else{newstate = dead;}
    }
    return newstate;
  }

void UpdateKernel(thrust::device_vector< int >& d_grid,thrust::device_vector< int >& index,thrust::device_vector< int >& d_next_grid,int sizex, int sizey){

  // thrust::transform(d_grid.begin(),d_grid.end(),index.begin(),d_next_grid.begin(),NewState(d_grid,sizex,sizey));
  thrust::transform(d_grid.begin(),d_grid.end(),index.begin(),d_next_grid.begin(),NewState(sizex,sizey));

};

#endif /* FUNCTORS_H_ */
