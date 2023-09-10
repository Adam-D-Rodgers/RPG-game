//Adam Rodgers, 8/7/2023
//This is one of the derived class of event. And one of the three event classes. 
//This class stores randomly genrates a a treasure item. They can either be a health or damage item.
//This items are then stored in the player
#include "event.h"
using namespace std;

//default constructor
treasure::treasure(): event( (char*) "TREASURE ENCOUNTER"){
}

//constructor with char argumnet
treasure::treasure(char * a_name): event(a_name){
}

//randomly chooses an event to happen
void treasure::events(player * hero) {
	random_device rd; //randomization code
  mt19937 gen(rd());
  uniform_int_distribution<> dis(1, 7);
  int x = dis(gen);	
 
	cout << endl << endl;
	cout << "You have run into a "<< name << "! You found a treasure chest on the ground! Lets see what you get!!" << endl;

	


	switch(x){ // This loop will check the random number then run the event depending on the number //Some monsters are stornger then others.

		case 1:
			cout << "You found a small piece of armor, a shoulder pad! It provides you with +7 health! " << endl;
			exp_gain = 5;
			try {//Makes sure the player is not already holding 10 items. 
				set_health_item(hero, "Shoulder Pad", 7); //Sets and makes the item
			}
			catch(int ex){ //If the player is holding to many items 
				cout << "You are holding to many health items! you cant carry anymore!" << endl;
			}
			
			display_health(hero);
			break;
		
		case 2:
			cout << "You found a large piece of armor, a black breast plate! It provides you with +17 max health! " << endl;
			exp_gain = 10;
			try {
				set_health_item(hero, "Black Breast Plate", 17); 
			}
			catch(int ex){
				cout << "You are holding to many health items! you cant carry anymore!" << endl;
			}
			 
			display_health(hero);
			break;

		case 3:
			cout << "You found a small enchanted ring! It provides you with +4 damage! " << endl;
			exp_gain = 7;
			try {
				set_damage_item(hero, "Small Enchanted Ring", 4);  
			}
			catch(int ex){
				cout << "You are holding to many health items! you cant carry anymore!" << endl;
			}
			
			display_damage(hero);
			break;

		case 4:
			cout << "You found a enchanted flame gloves! It provides you with +8 damage! " << endl;
			exp_gain = 11;
			try {
				set_damage_item(hero, "Enchanted Flame Gloves", 8);  
			}
			catch(int ex){
				cout << "You are holding to many health items! you cant carry anymore!" << endl;
			}
			
			display_damage(hero);
			break;

		case 5:
			cout << "You found a large piece of armor, guantlet of vitality! It provides you with +25 max health! " << endl;
			exp_gain = 17;
			try {
				set_health_item(hero, "Guantlet of Vitality", 25); 
			}
			catch(int ex){
				cout << "You are holding to many health items! you cant carry anymore!" << endl;
			}
			
			display_health(hero);
			break;

		case 6: 
			cout << "You found a small piece of armor, knights boots! It provides you with +9 max health! " << endl;
			exp_gain = 6;
			try {
				set_health_item(hero, "Knight's Boots", 9); 
			}
			catch(int ex){
				cout << "You are holding to many health items! you cant carry anymore!" << endl;
			}
			display_health(hero);
			break;

		case 7:
			cout << "You found a enchanted golden crown! It provides you with +12 damage! " << endl;
			exp_gain = 20;
			try {
				set_damage_item(hero, "Enchanted Golden Crown", 12); 
			}
			catch(int ex){
				cout << "You are holding to many health items! you cant carry anymore!" << endl;
			}
			 
			display_damage(hero);
			break;

		case 8:
			cout << "When you open the chest you find a sword stuck in the stone underneeth the chest" << endl; //Legendary sword i added just for fun
			cout << "You try to pull the sword out of the stone...AND WITH GREAT DIFFICULTY YOU SUCCEED!" << endl;
			cout << "YOU HAVE GOTTEN THE GREAT SWORD EXCALIBUR!!! YOU CAN DISTROY ALL FOES WITH THIS MIGHTY SWORD!" << endl;
			exp_gain = 100;
			try {
				set_damage_item(hero, "THE GREAT SWORD EXCALIBUR", 999); 
			}
			catch(int ex){
				cout << "You are holding to many health items! you cant carry anymore!" << endl;
			}
			
			display_damage(hero);
			break;

	}
}

//sets and makes the health item
void treasure::set_health_item(player * hero, string source, int hp){
	item new_item;
	if(hero->num_items >= 10){ //check if the player is carrying max items
		throw 10; 
	}
	new_item.name = source; //Setting the items data
	new_item.health_bonus = hp;
	hero->max_health += hp;
	hero->health_items[hero->num_items] = new_item;
	++hero->num_items;
	hero->score += exp_gain;
	cout << "Finding the item gave you +" << exp_gain << " score" << endl;

}

//sets and makes the damage item
void treasure::set_damage_item(player * hero, string source, int dps){
	
	hero->damage_items.insert({source, 0, dps}); //Since this is a STL set it allows me to do this
	hero->damage += dps;
	hero->score += exp_gain;
	cout << "Finding the item gave you +" << exp_gain << " score" << endl;
}

//display function to show all health items
void treasure::display_health(player * hero) const {
	cout << endl << "Your current health Items Are:" << endl << endl;
	for(int i = 0; i < 10; ++i){
		if(hero->health_items[i].name == "empty") break;
		cout << hero->health_items[i].name << ": +" << hero->health_items[i].health_bonus << " max_health" << endl;
	}
}

//display function to show all damage items
void treasure::display_damage(player * hero) const {
	cout << endl << "Your current damage Items Are:" << endl << endl;
	set<item>::iterator s;
	for(s = hero->damage_items.begin(); s != hero->damage_items.end(); ++s){
		cout << s->name << ": +" << s->damage_bonus << " damage" << endl;
	}
}
