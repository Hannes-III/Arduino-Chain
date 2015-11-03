#include "Xxx.h"

Xxx::Xxx(String name):
    ChainElement()
  , name(name)
  {
}

String Xxx::getName(){
  return name;
}

void Xxx::setName(String n){
  name=n;
}

