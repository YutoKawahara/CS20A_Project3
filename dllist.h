#ifndef CS20A_DLLIST_H
#define CS20A_DLLIST_H

#include<iostream>
#include<assert.h>
using std::cout;
using std::endl;


// Linked DLList object that maintains both head and tail pointers
// and the size of the list.  Note that you have to keep the head,
// tail and size consistent with the intended state of the DLList 
// otherwise very bad things happen. 
template<typename Item>
class DLList {
public:

	DLList();

	DLList(const DLList<Item>& other);

	DLList<Item>& operator=(const DLList<Item>& other);

	~DLList();

	void	print() const;
	bool	empty() const;

	void	push_front(const Item& item);
	void	push_rear(const Item& item);
	void	push_at(int idx, const Item& item);

	// Note that the user must first ensure the list is not empty
	// prior to calling these functions. 
	Item	front() const;
	Item	rear() const;
	Item	at(int idx) const;

	int		count() const;
	int		find(const Item& item) const;

	bool	pop_front();
	bool	pop_rear();
	bool	pop_at(int idx);
	int		pop_item(const Item& item);

#ifndef MAKE_MEMBERS_PUBLIC
private:
#endif
	// Forward declare the nodes for our DLList.
	// Will be implemented along with list
	// member functions
	struct Node;

	// We'll have both head and tail points for 
	// Fast insertion/deletion from both ends.
	Node* head;
	Node* tail;

	// Keep track of number of nodes in the list
	int		size;
};


/* DLList Implementation
//
//  Since DLList is a template class (which is not an actual
//  class yet, not until we actually instantiate the list)
//  we need to keep the implementation together with
//  the definition.  There are ways to simulate having
//  separate "implementation/definition" with templates,
//  but they aren't necessary and can be confusing.
*/

/* Node definition
//		Already implemented, nothing to do here but to use it.
*/
template<typename Item>
struct DLList<Item>::Node {
	Node() :next(nullptr), prev(nullptr) {}
	Node(Item it, Node* p, Node* n) : item(it), next(n), prev(p) {}

	Item  item;
	Node* next;
	Node* prev;
};

/* DLList default constructor
//		Set head and tail pointer to point to nothing, size is zero
//		Already implemented, nothing to do.
*/
template<typename Item>
DLList<Item>::DLList() :head(nullptr), tail(nullptr), size(0) {
	/*  DONE  */
}


/* Copy constructor
*/
template<typename Item>
DLList<Item>::DLList(const DLList<Item>& other) {
	if (other.head == nullptr) {
		head = nullptr;
		tail = nullptr;
		size = 0;
	}
	else {
		size = 0;
		head = nullptr;
		tail = nullptr;
		push_at(0, other.at(0));
		for (int i = 1; i < other.count(); i++) {
			push_rear(other.at(i));
		}
	}

}
/* Overloaded assignment operator
*/
template<typename Item>
DLList<Item>& DLList<Item>::operator=(const DLList<Item>& other) {
  if (this != &other) {
        
        Node* p = head;
        
        while (p != nullptr) {
            Node* n = p->next;
            delete p;
            p = n;
        }
        
        head = nullptr;
        tail = nullptr;
        size = 0;
        
        Node* copy = other.head;
        
        while (copy != nullptr) {
            push_rear(copy->item);
            copy = copy->next;
        }
    }
    return *this;

}


/* DLList destructor
*/
template<typename Item>
DLList<Item>::~DLList() {
	Node* ptr = head;
	while (ptr != nullptr) {
		Node* n = ptr->next;
		delete ptr;
		ptr = n;
	}
  
}

/* DLList print
*/
template<typename Item>
void DLList<Item>::print() const {
	Node* printNode = head;
    
    while (printNode != nullptr) {
        
        cout << printNode->item << " ";
            
        printNode = printNode->next;
        
    if (printNode != nullptr) {
        cout << " ";
    }
        
    }

}

/* DLList empty
*/
template<typename Item>
bool DLList<Item>::empty() const {
	return (size == 0);
}


/* DLList push_front
*/
template<typename Item>
void DLList<Item>::push_front(const Item& item) {
	Node* p = new Node;
	p->item = item;
	p->next = head;
	p->prev = nullptr;
	if (empty()) {
		tail = p;
	}
	else {
		head->prev = p;
	}
	head = p;
	size += 1;


}

/* DLList push_rear
*/
template<typename Item>
void DLList<Item>::push_rear(const Item& item) {
  Node *ptr = new Node;
  ptr -> item = item;
  ptr -> prev = tail;
  ptr -> next = nullptr;
  if(empty()){
    head = ptr;
  }
  else{
    tail -> next = ptr;
  }
  tail = ptr;
  size ++;
  

}

/* DLList push_at
*/
template<typename Item>
void DLList<Item>::push_at(int idx, const Item& item) {
	if(idx <= 0){
    push_front(item);
  }
  else if(count() <= idx){
    push_rear(item);
  }
  else{
    Node * p = head;
    int num = 0;
    while (num != idx){
      p = p->next;
      num++;
    }
    Node * q= new Node;
    q->item = item;
    q->prev = p->prev;
    q->next = p;
    p->prev->next = q;
    p->prev = q;
    size+=1;
  }
	/*  TODO  */

}

/*  DLList front
*/
template<typename Item>
Item DLList<Item>::front() const {

	// This should never be tripped, this is just here to let
	// you know that you messed up with your usage, this function
	// is never called on an empty list.
	assert(head != nullptr);


	return head->item;

}

/* DLList rear
*/
template<typename Item>
Item DLList<Item>::rear() const {

	// This should never be tripped, this is just here to let
	// you know that you messed up with your usage, this function
	// is never called on an empty list.
	assert(tail != nullptr);

	return tail->item;

}

/* DLList at
*/
template<typename Item>
Item DLList<Item>::at(int idx) const {

	// Assert that index is correct before getting the Item
	assert(idx >= 0 && idx < size);

	
  Node *p = head;
  int num = 0;
  while(idx != num){
    p = p->next;
    num+=1;
  }
  return p->item;
}

/* DLList count
*/
template<typename Item>
int DLList<Item>::count() const {
  return size;
}

/* DLList find
*/
template<typename Item>
int DLList<Item>::find(const Item& item) const {
  int num = 0;
  Node *ptr = head;
  while(ptr != nullptr){
    if(ptr -> item == item){
      return num;
    }
    else{
      ptr = ptr -> next;
      num += 1;
    }
  }
  return -1;
}

/* DLList pop_front
*/
template<typename Item>
bool DLList<Item>::pop_front() {
  Node*ptr = head;
  if(empty()){
    return false;
  }
  else if(size > 1){
    head = ptr->next;
    head -> prev = nullptr;
    size -=1;
  }
  else{
    head = nullptr;
    tail = nullptr;
    size -=1;
  }
  delete ptr;
  return true;
}
/* DLList pop_rear
*/
template<typename Item>
bool DLList<Item>::pop_rear() {
  Node *ptr = tail;
  if(empty()){
    return false;
  }
  else if(size > 1){
    tail = ptr -> prev;
    tail -> next = nullptr;
    size -= 1;
    
  }
  else{
    head = nullptr;
    tail = nullptr;
    size -= 1;
  }
  delete ptr;
  return true;
}

/* DLList pop_at on index
*/
template<typename Item>
bool DLList<Item>::pop_at(int idx) {
  int num = 0;
  Node *ptrPop = head;
  if (idx < 0 || idx >= size || size == 0) {
       return false;
   } 
  if (idx == 0) {
       pop_front();
       return true;
   } else if (idx > 0 && idx == size-1){
       pop_rear();
       return true;
   } else {
       while(idx != num){
         ptrPop = ptrPop->next;
         num ++;
       }
    ptrPop->prev->next = ptrPop->next;
    ptrPop->next->prev = ptrPop->prev;
    size--;
    return true;
   }
}

/* DLList pop_item on item
*/
template<typename Item>
int DLList<Item>::pop_item(const Item& item) {
  if (head == nullptr) {
    return -2;
  }
  int p = find(item);
    
    if (p == -1) {
        return -1;
    }
    else {
        pop_at(p);
        return p;
    }
}

#endif

// _X_XMXXII