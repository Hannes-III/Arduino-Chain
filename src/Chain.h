/*
Chain library for Arduino
based on Code by Anatoli Arkhipenko
Copyright (c) Hannes Morgenstern (http://www.usw.at), All rights reserved.

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 3.0 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library.
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

    void clear(bool deleteOnRemove=true);
    void addElement(ChainElement* element);
    ChainElement* removeElement(ChainElement* element, bool deleteOnRemove=true);
    ChainElement* getFirst();
    ChainElement* getLast();
    unsigned int  size();

  protected:

  private:
    ChainElement *first, *last;
    unsigned int elementCount;

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

