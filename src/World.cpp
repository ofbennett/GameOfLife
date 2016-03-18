#include "World.h"

World::World(int sizex, int sizey):day(0),sizex(sizex),sizey(sizey),lifeforms(sizex,vector<int>(sizey)){

}

void World::Populate(){

}

void World::Record() const{

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

vector< vector< int > > World::Lifeforms() const{
  return lifeforms;
}
