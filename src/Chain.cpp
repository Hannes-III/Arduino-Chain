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

#include "Chain.h"

// -- Chain ------------------------------------------------------------

/** Default constructor.
 * Creates an empty chain.
 */
Chain::Chain() { // Chain, Chain, Chain ...
  first  =NULL;
  last   =NULL;
  elementCount=0;
}


/** Removes all elements from the Chain.
 * @param deleteOnRemove - As the Element most probably has been created
 *        with 'new ...' someone has to take care, that the Element will free
 *        its memory space. If you need the element later, you have to provide false,
 *        because true is default.
 */
void Chain::clear(bool deleteOnRemove) {
  ChainElement* remove = first;
  while(remove!=NULL){
    remove = removeElement(remove, deleteOnRemove);
  }
}

/** Appends ChainElement element to the tail of the chain.
 * @param &element - reference to the element to be appended.
 * @note ChainElement can only be part of one chain once.
 *       And only part of one Chain.
 */
void Chain::addElement(ChainElement* element) {
  if(element->myChain!=NULL) return;
  elementCount++;

  element->myChain=this;

	if(first == NULL){// First element situation:
		first = element;
		element->prev = NULL;
	}else{ // This element gets linked back to the previous last one and last element gets linked to this one
		element->prev = last;
		last->next = element;
	}
	// new element becomes the last one
	element->next = NULL;
	last = element;
}

/** Deletes specific ChainElement from the chain
 * @param *element - reference to the element to be deleted from the chain
 * @param deleteOnRemove - As the Element most probably has been created
 *        with 'new ...' someone has to take care, that the Element will free
 *        its memory space. If you need the element later, you have to provide false,
 *        because true is default.
 *
 * @return the next element from the Chain. Or NULL if there is none.
 */
ChainElement* Chain::removeElement(ChainElement* element, bool deleteOnRemove){
  elementCount--;

  ChainElement* back = element->next;
	if(element->prev == NULL){
		if(element->next == NULL){
			first = NULL;
			last = NULL;
		}else{
		  element->next->prev = NULL;
		  first = element->next;
		}
	}else if(element->next == NULL){
		element->prev->next = NULL;
		last = element->prev;
	}else{
    element->prev->next = element->next;
    element->next->prev = element->prev;
  }

  if(deleteOnRemove){
    delete element;
  }else{
    element->prev = NULL;
    element->next = NULL;
    element->myChain=NULL;
  }
	
	return back;
}

/** get the first element of the chain
 */
ChainElement* Chain::getFirst(){return first;}
/** get the last element of the chain
 */
ChainElement* Chain::getLast(){return last;}
/** get size of the chain
 */
unsigned int Chain::size(){return elementCount;}


// -- ChainElement ------------------------------------------------------------
ChainElement::ChainElement(){
  prev=NULL;
  next=NULL;
  myChain=NULL;
}

/** remove this element from its chain
 * @return the next element from the Chain. Or NULL if there is none.
 */
ChainElement* ChainElement::remove(bool deleteOnRemove){return myChain->removeElement(this, deleteOnRemove);}
/** get the next element from the chain
 */
ChainElement* ChainElement::getNext(){return next;}
/** get the previous element from the chain
 */
ChainElement* ChainElement::getPrev(){return prev;}
/** get the chain this element is member of.
 */
Chain* ChainElement::getChain(){return myChain;}

