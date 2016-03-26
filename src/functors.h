#ifndef FUNCTORS_H_
#define FUNCTORS_H_

#include "World.h"

int Getx(int index){
  x = index/sizey;
  return x;
}

int Gety(int index){
  y = index - (index/sizey);
  return y;
}

struct NewState {
  const grid_type old_grid;
  const bool alive;
  const bool dead;

  NewState(grid_type old_grid): old_grid(old_grid),alive(true),dead(false){

  }

  aliveness operator(aliveness cell, int index){
    int newstate;
    int alive_neighbors = 0;
    int xn; // Neighbor x index
    int yn; // Neighbor y index

    int x = Getx(index);
    int y = Gety(index);

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

        if(old_grid.GetGridVal(xn,yn)==alive){alive_neighbors += 1;}
      }
    }

    if(cell==alive){
      if((alive_neighbors==2)||(alive_neighbors==3)){newstate = alive;}
      else{newstate = dead;}
    }else if(cell==dead){
      if(alive_neighbors==3){newstate = alive;}
      else{newstate = dead;}
    }else{
      throw logic_error("A lifeform on the grid has an aliveness which is neither alive or dead!");
    }
    return newstate;
  }

};

#endif /* FUNCTORS_H_ */
