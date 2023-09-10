//Adam Rodgers, 8/7/2023
//This is one of the derived class of event. And one of the three event classes. 
//This file stores a player function, all the operator overloads for the combat class, and all the function for the combat class. 
#include "event.h"
using namespace std;

//This is a function to show the players current stats and is vital to the game.
void player::status(){
	cout << endl; //Information output
	cout << "*********PLAYER STATUS************" << endl;
	cout << "Current Health: " << health << endl;
	cout << "Current Damage: " << damage << endl;
	cout << "Current Score: " << score << endl;
	cout << "Current Max Health: " << max_health << endl;
	cout << "Current Health Items: " << endl;

	for(int i = 0; i < 10; ++i){ //loop for health items
		if(health_items[i].name == "empty") break;
		cout << health_items[i].name << ": +" << health_items[i].health_bonus << " max_health" << endl;
	}

	cout << endl << "Cureent Damage Items: " << endl; //loop for damage items
	set<item>::iterator s;
	for(s = damage_items.begin(); s != damage_items.end(); ++s){
		cout << s->name << ": +" << s->damage_bonus << " damage" << endl;
	}
	cout << endl;
	cout << "**********************************" << endl;
}

bool operator<(const player & hero, const combat & monster){
	if(hero.health < monster.monster_health) return 1;
	else return 0;
}
bool operator<(const combat & monster, const player & hero){
	if(hero.health > monster.monster_health) return 1;
	else return 0;
}
bool operator<=(const player & hero, const combat & monster){
	if(hero.health <= monster.monster_health) return 1;
	else return 0;
}
bool operator<=(const combat & monster, const player & hero){
	if(hero.health >= monster.monster_health) return 1;
	else return 0;
}
bool operator>(const player & hero, const combat & monster){
	if(hero.health > monster.monster_health) return 1;
	else return 0;
}
bool operator>(const combat & monster, const player & hero){
	if(hero.health < monster.monster_health) return 1;
	else return 0;
}
bool operator>=(const player & hero, const combat & monster){
	if(hero.health >= monster.monster_health) return 1;
	else return 0;
}
bool operator>=(const combat & monster, const player & hero){
	if(hero.health <= monster.monster_health) return 1;
	else return 0;
}
bool operator==(const player & hero, const combat & monster){
	if(hero.health == monster.monster_health) return 1;
	else return 0;
}
bool operator==(const combat & monster, const player & hero){
	if(hero.health == monster.monster_health) return 1;
	else return 0;
}
bool operator!=(const player & hero, const combat & monster){
	if(hero.health != monster.monster_health) return 1;
	else return 0;
}
bool operator!=(const combat & monster, const player & hero){
	if(hero.health != monster.monster_health) return 1;
	else return 0;
}
combat combat::operator + (const combat & monster2) const {
  combat monster3(monster_health, monster2.monster_health);
  return monster3;
}

ostream & operator << (ostream & out, const combat & monster){ //outputs the monsters info
	out << "Monster name is: " << monster.monster_name << endl
			<< "Monster health is: " << monster.monster_health << endl
			<< "Monster damage is: " << monster.monster_damage << endl;
 return out;
}

istream & operator >> (istream & in, combat & monster){
	in >> monster.monster_health;
 return in;
}

//minuses the monsters health based off of the input.
combat & combat::operator -= (const int & val){
  monster_health -= val;
	if(monster_health < 0){
		throw -1;
	}
  return *this;
}

//default constructor
combat::combat(): event( (char*) ("COMBAT ENCOUNTER")), monster_name(nullptr), monster_health(0), monster_damage(0) {
}

//constructor with int arguments for the + operator
combat::combat(int health1, int health2): event( (char*) ("COMBAT ENCOUNTER")), monster_name(nullptr), monster_health(health1 + health2), monster_damage(0) {
}

//constructor with char * argumnets
combat::combat(char * a_name, char * source): event(a_name), monster_name(nullptr), monster_health(0), monster_damage(0)  {
	if(monster_name) delete [] monster_name;
  monster_name = new char[strlen(source) + 1] {0};
  strncpy(monster_name, source, strlen(source));
}

//copy constructor
combat::combat(const combat & source){
	*this = source;
}

//desructor
combat::~combat(){
	if(monster_name){
		delete [] monster_name;
	}
	monster_name = nullptr;
	monster_damage = 0;
	monster_health = 0;
}

//assignmnet operator
combat & combat::operator=(const combat & source){
	if(this == &source) return *this; //No exception handling here since I think we woudlnt want to just give an error rather have the program still work
	event::operator=(source);

	if(source.monster_name){
		if(monster_name){
      delete monster_name;
      monster_name = nullptr;
    }
    monster_name = new char[strlen(source.monster_name) + 1] {0};
    strncpy(monster_name, source.monster_name, strlen(source.monster_name));
	} else {
		monster_name = nullptr;
	}			

	monster_health = source.monster_health;
	monster_damage = source.monster_damage;
  return *this;

}

//display function 
int combat::display() const {
	event::display();	
	return 1;
}

//randomly chooses an event to happen
void combat::events(player * hero) {
	random_device rd; //Randomization code
  mt19937 gen(rd());
  uniform_int_distribution<> dis(1, 7);
  int x = dis(gen);	
	cout << endl << endl;
	cout << "You have run into a "<< name << "! You will need to defeat the monster if you want to progress!" << endl;
	


	switch(x){ // This loop will check the random number then run the event depending on the number //Some monsters are stornger then others. 

		case 1:
			cout << "You ran into a LITTLE SLIME monster! It has 7 health and 5 damage!" << endl;
			set_info( (char *) "LITTLE SLIME", 7, 5, 3); //sets the monster info
			check_win(hero); //battles and checks win
			break;
		
		case 2:
			cout << "You ran into a BIG SLIME monster! It has 17 health and 10 damage!" << endl;
			set_info( (char *) "BIG SLIME", 17, 10, 9);
			check_win(hero);
			break;

		case 3:
			cout << "You ran into a SKELETON monster! It has 13 health and 15 damage!" << endl;
			set_info( (char *) "SKELETON", 13, 15, 14);
			check_win(hero);
			break;
		case 4:
			cout << "You ran into a GOBLIN monster! It has 27 health and 4 damage!" << endl;
			set_info( (char *) "GOBLIN", 27, 4, 16);
			check_win(hero);
			break;
		case 5:
			cout << "You ran into a ORC monster! It has 37 health and 11 damage!" << endl;
			set_info( (char *) "ORC", 37, 11, 20);
			check_win(hero);
			break;
		case 6: 
			cout << "You ran into a SPIDER monster! It has 25 health and 16 damage!" << endl;
			set_info( (char *) "SPIDER", 25, 16, 27);
			check_win(hero);
			break;
		case 7:
			cout << "OH NO THIS IS BAD! YOU RAN INTO A DRAGON!!! IT HAS 100 HEALTH AND 35 DAMAGE!" << endl;
			set_info( (char *) "DRAGON", 100, 35, 100);
			check_win(hero);
			break;
	}
}

//set the monsters info
void combat::set_info(char * source, int hp, int dps, int gain){
	if(monster_name) delete [] monster_name;
  monster_name = new char[strlen(source) + 1] {0};
  strncpy(monster_name, source, strlen(source));
	monster_health = hp;
	monster_damage = dps;
	exp_gain = gain;
}

//checks if player wins
int combat::check_win(player * hero) {
	cout << endl << endl;
	cout << "The " << monster_name << " attacks you with |" << monster_health << "| health and *" << monster_damage << "* damage!" << endl; //This is just to give the user information
	cout << "You charge the monster with |" << hero->health << "| health and *" << hero->damage << "* damage!" << endl;
	cout << "You do *" << hero->damage << "* damge to the " << monster_name << endl;
	cout << "The " << monster_name << " does *" << monster_damage << "* damage to you!" << endl;
	monster_health -= hero->damage; //Check the damage
	hero->health -= monster_damage;
	if(hero->health <= 0){ //If player dies
		cout << endl << endl;
		cout << "*************** OH NO  YOU HAVE DIED *************" << endl;
		cout << "*************** FINAL GAME SCORE: " << hero->score << " *************" <<  endl;
		cout << endl << endl;
	}
	else if (monster_health <= 0){ //If player wins
		cout << "You have defeated the monster!!" << endl;
		cout << "Current health: " << hero->health << endl;
		cout << "Game score increased by " << exp_gain << endl;
		hero->score += exp_gain;
	}
	else{ //If neither die the first time
		cout << "Neither of you have fallen! So you attack eachother again!" << endl;
		check_win(hero);
	}

	return 0;
}


//This function test to see if the operator overloads work as intended.
void combat::test_operators(player * hero){
	random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<> dis(1, 100);
  int x = dis(gen);
	int y = dis(gen);

	hero->health = x;
	monster_health = y;

	cout << endl << "Hero Health is: " << hero->health << endl;
	cout << "Monster Health is: " << monster_health << endl;

	cout << "*************OPERATOR TESTS*************" << endl; //These are all tests 

	cout << "< :";
	if(*hero < *this) cout << "Monster Health is Higher" << endl;
	else cout << "Hero Health is Higher" << endl;
	cout << "< :";
	if(*this < *hero) cout << "Hero Health is Higher" << endl;
	else cout << "Monster Health is Higher" << endl;

	cout << "> :";
	if(*hero > *this) cout << "Hero Health is Higher" << endl;
	else cout << "Monster Health is Higher" << endl;
	cout << "> :";
	if(*this > *hero) cout << "Monster Health is Higher" << endl;
	else cout << "Hero Health is Higher" << endl;

	cout << "<= :";
	if(*hero <= *this) cout << "Monster Health is Higher or equal" << endl;
	else cout << "Hero Health is Higher or equal" << endl;
	cout << "<= :";
	if(*this <= *hero) cout << "Hero Health is Higher or equal" << endl;
	else cout << "Monster Health is Higher or equal" << endl;

	cout << ">= :";
	if(*hero >= *this) cout << "Hero Health is Higher or equal" << endl;
	else cout << "Monster Health is Higher or equal" << endl;
	cout << ">= :";
	if(*this >= *hero) cout << "Monster Health is Higher or equal" << endl;
	else cout << "Hero Health is Higher or equal" << endl;

	cout << "== :";
	if(*this == *hero) cout << "They have the same health" << endl;
	else cout << "They have diffrent health" << endl;
	cout << "== :";
	if(*hero == *this) cout << "They have the same health" << endl;
	else cout << "They have diffrent health" << endl;

	cout << "!= :";
	if(*this != *hero) cout << "They have diffrent health" << endl;
	else cout << "They have the same health" << endl;
	cout << "!= :";
	if(*hero != *this) cout << "They have diffrent health" << endl;
	else cout << "They have the same health" << endl;

	cout << endl << "<<: (This test makes a new monster with the name 'GIANT SPIDER!' with 0 health and 0 damage" << endl;
	combat temp((char *)"COMBAT EVENT", (char *) "GIANT SPIDER!");
	cout << temp;

	cout << endl << ">>: " << endl; //The user enter the monster health
	cout << "Enter a number: ";
	cin >> *this;
	cout << "Monster new health: " << monster_health << endl;

	cout << endl << "-=: (testing with -5)" << endl; // Since this is just a test i felt the static 5 was ok 
	try{
		*this -= 5;
	}
	catch(int ex){
		cout << "You cannot have monster health less then 0" << endl;
		return;
	}

	cout << "Monster new health: " << monster_health << endl;


	cout << endl << "+: " << endl; //This function basically adds to monster's health together. This is just to test if it works.
	cout << "Expected output 100" << endl;
	cout << "Current health:" << monster_health << endl;
	combat test(20, 20);
	combat test2(30, 30);
	*this = test + test2;
	cout << "New health: " << monster_health << endl;
}
