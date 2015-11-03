#include <MemoryFree.h>

#include <Chain.h>
#include "Xxx.h"

void setup() {
  Serial.begin(9600);
  Chain c = Chain();

  o("Welcome Refugies! (Part 2)");
  o("\nIf you create the ChainElements in a loop, you have to take care, that they");
  o("will be referenced. You have to create them using >>> new <<< !");
  o("Ex.:\n");
  o("                Xxx *x=new Xxx(\"#\"+String(i));\n\n");
  o("  This is how it has to be done!\n");
  o("");
  o("Take care, that the Memory stays under control!");
  o("Chain frees memory of removed Elements on default.");
  o("If you need the elements for further use you will have to tell.");
  o("-----------------------------------------------------------------------\n\n");

  fm();

  for (int i = 10; i < 200; i++) {
    Xxx *x=new Xxx("#"+String(i));
    if(i%50==0)o("");
    Serial.print(".");
    c.addElement(x);
  }
  o("\n  >> all added");
  fm();

  showChain(c);
  o("\n  >> all elements in the Chain");
  fm();

  {
    Xxx *e=(Xxx*)c.getFirst();
    while(e != NULL){
      e->setName("-"+e->getName()+"-");
      e=(Xxx*)e->getNext();
    }
    showChain(c);
    o("\n  >> all names changed (added '-')");
    fm();
  }
  {
    byte i=0;
    Xxx *e=(Xxx*)c.getFirst();
    while(e != NULL){
      if(i++ % 2 == 0){
        e=(Xxx*)c.removeElement(e);
      }else{
        e=(Xxx*)e->getNext();
      }
    }
    showChain(c);
    o("\n  >> every second Element deleted.");
    fm();
  }
  {
    byte i=0;
    Xxx *e=(Xxx*)c.getFirst();
    while(e != NULL){
      if(i++ % 2 == 0){
        e=(Xxx*)e->remove();
      }else{
        e=(Xxx*)e->getNext();
      }
    }
    showChain(c);
    o("\n  >> every second Element removed again.");
    fm();
  }

  o("");
  for (int i = 10; i < 32; i++) {
    Xxx *x=new Xxx(">"+String(i));
    if(i%50==0)o("");
    Serial.print(".");
    c.addElement(x);
  }
  showChain(c);
  o("\n  >> added some 22 Elements");
  fm();

  {
    byte i=0;
    Xxx *e=(Xxx*)c.getFirst();
    while(e != NULL){
      if(i++ % 2 == 0){
        e=(Xxx*)e->remove();
      }else{
        e=(Xxx*)e->getNext();
      }
    }
    showChain(c);
    o("\n  >> and every second Element removed again.");
    fm();
  }
  {
    byte i=0;
    Xxx *e=(Xxx*)c.getFirst();
    while(e != NULL){
      e=(Xxx*)e->remove();
    }
    showChain(c);
    o("\n\n>> all the rest deleted. All RAM recovered?");
    fm();
  }
  
}

void loop() {}

void o(String x) {Serial.println(x);}
void o(int x) {Serial.println(x);}

void showChain(Chain c){
  int i=0;
  Xxx* curr = (Xxx*)c.getFirst();
  while (curr != NULL) {
    if(i++%10==0)o("");
    Serial.print(curr->getName()+", ");
    curr = (Xxx*)curr->getNext();
  }
}

