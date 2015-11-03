// Chain library for Arduino version 1.6
// Copyright (c) 2015 Hannes Morgenstern
//

/* ============================================
Chain library code is placed under the MIT license
Copyright (c) 2015 Hannes Morgenstern
based on Code by Anatoli Arkhipenko

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
===============================================
*/

#include "Chain.h"

// -- Chain ------------------------------------------------------------

/** Default constructor.
 * Creates an empty chain.
 */
Chain::Chain() { // Chain, Chain, Chain ...
  first  =NULL;
  last   =NULL;
}

/** Appends ChainElement element to the tail of the chain.
 * @param &element - reference to the element to be appended.
 * @note ChainElement can only be part of the chain once.
 *       And only part of one Chain.
 */
 void Chain::addElement(ChainElement* element) {
  if(element->myChain!=NULL) return;
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

