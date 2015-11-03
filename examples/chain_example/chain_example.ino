#include <Chain.h>
#include "Xxx.h"

  Xxx xs[] = {
      Xxx("0a")
    , Xxx("1b")
    , Xxx("2c")
    , Xxx("3d")
    , Xxx("4e")
    , Xxx("5f")
  };
  const byte xsLength = 6;


void setup() {
  Serial.begin(9600);
  Chain c = Chain();

  o("Welcome Refugies!");


  for (int i = 0; i < xsLength; i++) {
    c.addElement( &xs[i]);
    Serial.print("  "+xs[i].getName()+"  ");
  }
  o("! >> all added");

  showChain(c, "  ");
  o("! >> all elements in the Chain");

  Xxx *e=(Xxx*)c.getFirst();
  while(e != NULL){
    e->setName("-"+e->getName()+"-");
    Serial.print(" "+e->getName()+" ");
    e=(Xxx*)e->getNext();
  }
  o("! >> all names changed (added '-')");

  showChain(c, " ");
  o("! >> all elements in the Chain are pointers");

  c.removeElement(&xs[2], false);
  showChain(c, " ");
  o("      ! >> element 2 removed but not deleted!");

  c.addElement(&xs[2]);
  showChain(c, " ");
  o("! >> element 2 reappended to the end.");

  xs[4].remove();
  showChain(c, " ");
  o("      ! >> element 4 has removed and deleted itself.");
}

void loop() {}

void o(String x) {Serial.println(x);}
void o(int x) {Serial.println(x);}

void showChain(Chain c, String s){
  Xxx* curr = (Xxx*)c.getFirst();
  while (curr != NULL) {
    Serial.print(s+curr->getName()+s);
    curr = (Xxx*)curr->getNext();
  }
}

