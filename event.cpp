//Adam Rodgers, 8/7/2023
//This is the base class for all the events. All the events are derived from this class.
#include "event.h"
using namespace std;

//default constructor
event::event(): name(nullptr), exp_gain(0){
}

//constructor with three arguments
event::event(const char * source): name(nullptr), exp_gain(0){
                                
	if(name) delete [] name;
        name = new char[strlen(source) + 1] {0};
        strncpy(name, source, strlen(source));
		
}

//destructor
event::~event() {
	if(name){
		delete [] name;
	}
	name = nullptr;

	exp_gain = 0;
}

//copy constructor
event::event(const event & source){
	*this = source;
}

//assignment operator
event & event::operator=(const event & source) {
	
	if(this == &source) return *this; //No exception handling here since I think we woudlnt want to just give an error rather have the program still work

        if(name){
                delete [] name;
                name = nullptr;
        }
        name = new char[strlen(source.name) + 1] {0};
        strncpy(name, source.name, strlen(source.name));

        return *this;

	exp_gain = source.exp_gain;

}

//display function
int event::display() const{
	cout << endl;
	cout << "EVENT NAME: " << name << endl;
	return 1;
}



