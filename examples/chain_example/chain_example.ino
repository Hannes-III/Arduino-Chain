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
  o("! "+String(c.size())+" >> all added");

  showChain(c, "  ");
  o("! "+String(c.size())+" >> all elements in the Chain");

  Xxx *e=(Xxx*)c.getFirst();
  while(e != NULL){
    e->setName("-"+e->getName()+"-");
    Serial.print(" "+e->getName()+" ");
    e=(Xxx*)e->getNext();
  }
  o("! "+String(c.size())+" >> all names changed (added '-')");

  showChain(c, " ");
  o("! "+String(c.size())+" >> all elements in the Chain are pointers");

  c.removeElement(&xs[2], false);
  showChain(c, " ");
  o("      ! "+String(c.size())+" >> element 2 removed but not deleted!");

  c.addElement(&xs[2]);
  showChain(c, " ");
  o("! "+String(c.size())+" >> element 2 reappended to the end.");

  xs[4].remove();
  showChain(c, " ");
  o("      ! "+String(c.size())+" >> element 4 has removed and deleted itself.");


if(0){
  ChainElement* curr = c.getFirst();
  while (curr != NULL) {
    curr = c.removeElement(curr);
  }
}else{
  c.clear();
}

  showChain(c, " ");
  Serial.print("                             ! ");
  Serial.print(c.size());
  Serial.println(" >> NOW EMPTY!");
  o("");
  o("Danke, das wars. Bis zum naechsten Mal ...");
}

void loop() {}

void o(String x) {Serial.println(x);}
void o(int x) {Serial.println(x);}

void showChain(Chain c, String s){
  if (c.getFirst()==NULL){
    Serial.print(" Empty!");
    return;
  }
  Xxx* curr = (Xxx*)c.getFirst();
  while (curr != NULL) {
    Serial.print(s+curr->getName()+s);
    curr = (Xxx*)curr->getNext();
  }
}

