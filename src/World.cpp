#include <iostream>
#include "World.h"

World::World():day(0){

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
