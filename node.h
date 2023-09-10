#include "event.h"
//Adam Rodgers, 8/7/2023
//This file manages the node and DLL classes. They are both implemented using class templates. 
//Since these are implemented using class templates I decided it would be easier to define the functions inside the class prototype. 

template <class rpg>

class node {

  public:

    node(): data(), next(nullptr), prev(nullptr) {} //DEfualt contructor

    void set_data(const node <rpg> * source){ //Sets the data 
      data = source->data;
    }

    node <rpg> *& get_next(){ // get next function
      return next;
    }

    node <rpg> *& get_prev(){ // get prev function
      return prev;
    }

    void set_next(node <rpg> * input){ //set nect function
      next = input;
    }

    void set_prev(node <rpg> * input){ //set prev function
      prev = input;
    }

    void run_event(player * hero){ //runs the event
      data.events(hero);
    }

  private:
    rpg data;
    node<rpg> * next;
    node<rpg> * prev;
};


template <class rpg>
class DLL {
  public:

    DLL(): head(nullptr), tail(nullptr){}// defualt contructor

    ~DLL(){ //distructor
      del(head);
      tail = nullptr;
    }

		DLL(const DLL & source){ *this = source;} //copy constructor

		DLL& operator =(const DLL &	 source){ //assignment operator overload
      if(!source.head || this == &source) return *this; //No exception handling here since I think we woudlnt want to just give an error rather have the program still work
      if(head) del(head);
      copy(source.head, head);
      return *this;
    }

    void add_node(player * hero){ //adds a node and runs the event
      node<rpg> * new_node = new node<rpg>;
      if(!head){
        tail = new_node;
        head = new_node;
      }
      else {
        tail->set_next(new_node);
        new_node->set_prev(tail);
        tail = new_node;
      }

      new_node->run_event(hero);
      return;
    }

    void remove(){ //remove last event of the list
      node <rpg> * hold = tail->get_prev();
      hold->set_next(nullptr);
      delete tail;
      tail = hold;
    }

    void displayW(player * hero){ //displays the events
      display(head, hero);
    }

  private: 
    node<rpg> * head;
    node<rpg> * tail;

    void copy(node <rpg> * curr, node<rpg> *& my_curr){ //recursive copy function
      if(!curr) return;
      my_curr = new node<rpg>;
      my_curr->set_data(curr);
      copy(curr->get_next(), my_curr->get_next());
    }

		void del(node<rpg> *& curr){ //recursive delete function
      if(!curr) return;
      del(curr->get_next());
      delete curr;
      curr = nullptr;
    }

    void display(node <rpg> *& curr, player * hero){ //displayes events
      if(!curr) return;
      curr->run_event(hero);
      display(curr->get_next());
    }

};
