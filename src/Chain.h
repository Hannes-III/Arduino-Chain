/*
DipSwitch
Copyright (C) 2015  Hannes Morgenstern http://www.usw.at
This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License
as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License at http://www.gnu.org/licenses .
*/
#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#ifndef CHAIN_H
#define CHAIN_H

class ChainElement;

class Chain{
  public:
    Chain();

    void addElement(ChainElement* element);
    ChainElement* removeElement(ChainElement* element, bool deleteOnRemove=true);
    ChainElement* getFirst();
    ChainElement* getLast();

  protected:

  private:
    ChainElement *first, *last;

};

class ChainElement{
  friend class Chain;

  public:
    virtual ~ChainElement() {} // das ist notwendig sonst funktioniert das vererben nicht.

    ChainElement();
    ChainElement* remove(bool deleteOnRemove=true);
    ChainElement* getNext();
    ChainElement* getPrev();
    Chain* getChain();

  private:
    ChainElement *prev, *next;
    Chain *myChain;
};

#endif

