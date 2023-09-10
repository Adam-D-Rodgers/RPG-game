//Adam Rodgers, 8/7/2023
//This file stores all the .h data for all the other classes but not the DLL class and node class
//This file stores all the prototypes of the functions used for the item, player, event, combat, treasure, and campfire objects.

#pragma once
#include <iostream>
#include <string>
#include <cctype>
#include <cstring>
#include <cstdlib> 
#include <ctime>
#include <random>
#include <array>
#include <set>
using std::string;
using std::array;
using std::set;
using std::istream;
using std::ostream;


//This stores the item that the player holds
struct item {
	string name = "empty";
	int health_bonus = 0;
	int damage_bonus = 0;

	bool operator<(const item& another_item) const{
		return damage_bonus < another_item.damage_bonus;
	}
};

//This stores the data of the player and the two STL data structures that hold rewards
struct player { 
	int score = 0;
	int health = 100;
	int max_health = 100;
	int damage = 10;
	int num_items = 0;
	array<item, 10> health_items;
	set<item> damage_items;


	void status();
};


//event class
class event {
	public:
		event(); //Defualt constructor
		event(const char * source); // constructor with argument of char *
		~event(); //Distructor
		event(const event & source); //Copy contructor
		event& operator =(const event & source); //Assignment operator overload
	
		int display() const; //Display function

	protected:
		char * name;
		int exp_gain; 
};

//combat class
class combat : public event{

	public:
		combat();//Defualt constructor
		~combat();//Distructor
		combat(char *, char *);// constructor with argument of char *
		combat(int, int);// constructor with argument of int //This is for + operator
		combat(const combat & source); //Copy contructor
		combat& operator =(const combat & source);//Assignment operator overload

		void events(player *); //Main function of events
		int display() const; // Display function
		int check_win(player *); //Checks if the player won the battle
		void set_info(char *, int, int, int); //Sets the info of the monster
		void test_operators(player *); //test the operators to see if they have expected output

		//All the operators required for assignment. Many have firend since they arnt using 2 combat class inputs. 
		friend bool operator<(const player & hero, const combat & monster);
		friend bool operator<(const combat & monster, const player & hero);
		friend bool operator<=(const player & hero, const combat & monster);
		friend bool operator<=(const combat & monster, const player & hero);
		friend bool operator>(const player & hero, const combat & monster);
		friend bool operator>(const combat & monster, const player & hero);
		friend bool operator>=(const player & hero, const combat & monster);
		friend bool operator>=(const combat & monster, const player & hero);
		friend bool operator==(const player & hero, const combat & monster);
		friend bool operator==(const combat & monster, const player & hero);
		friend bool operator!=(const player & hero, const combat & monster);
		friend bool operator!=(const combat & monster, const player & hero);
		friend ostream & operator << (ostream & out, const combat & monster);
		friend istream & operator >> (istream & in, combat & monster);
		combat & operator -= (const int & val);
		combat operator + (const combat & op2) const; //I wanted to try this even if it didnt make much sense, think of it as a fusion of two monsters.

	private:
		char * monster_name;
		int monster_health;
		int monster_damage;
		
};

//treasure class
class treasure : public event {

	public:
		treasure();//Defualt constructor
		treasure(char *);// constructor with argument of char *

		void events(player *);//Main function of event
		void display_health(player * ) const; // Displayer current health items
		void display_damage(player * ) const; // Displays current damage items
		void set_health_item(player *, string, int); //Sets a new health item
		void set_damage_item(player *, string, int); //Sets a new damage item

	private:
};

//campfire Class
class campfire: public event{

	public:
		campfire();//Defualt constructor
		campfire(char *);// constructor with argument of char *
		
		void events(player *);//Main function of event
		void double_item(player * ); //Doubles the strength of a health item
		void half_item(player * ); //Halfs the strength of a health item
		
	private:
}; 
