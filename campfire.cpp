//Adam Rodgers, 8/7/2023
//This is one of the derived class of event. And one of the three event classes. 
//This class class has three diffrent types of events depending on the players choice.

#include "event.h"
using namespace std;

//default constructor
campfire::campfire(): event( (char*) "CAMPFIRE ENCOUNTER"){
}

//constructor with argumnets
campfire::campfire(char * a_name): event(a_name){
}

//randomly chooses an event to happen
void campfire::events(player * hero) {

	cout << endl << endl; //Information for the player
	cout << "You have run into a "<< name << "!" << endl;
	cout << "You find a strange mystical campfire on the ground." << endl;
	cout << "It burns green, blue, and red" << endl;
	cout << "You feel the three powers beckoning you, but you can only chose one" << endl;
	cout << "What power will you chose?" << endl;
	cout << endl;
	cout << "       -1- Green" << endl;
	cout << "       -2- Blue" << endl;
	cout << "       -3- Red" << endl;

	char temp = 0;
	cin >> temp;
	cin.ignore(100, '\n');
	


	switch(temp){   //PLayer can chose one of three options

		case '1': // If green is chosen it heals the player to max health
			cout << endl << "YOU CHOSE THE GREEN POWER!" << endl;
			cout << "YOU FEEL THE POWER OF LIFE FLOWING THROUGH YOU! YOU FEEL HEALTHIER, ALIVE, AS IF YOU COULD VANQUISH ANY MONSTER THAT DARES TO OPPOSE YOU!" << endl;
			cout << "YOUR HEALTH HAS BEEN FULLY RESTORED!" << endl;
			cout << "you gained 10 score" << endl;
			hero->health = hero->max_health;
			exp_gain = 10;
			hero->score += exp_gain;
			break;
		
		case '2': //If blue is chosen it doubles a random health item 
			cout << endl << "YOU CHOSE THE BLUE POWER!" << endl;
			if(hero->health_items[0].name == "empty"){
				throw 0;
			}
			cout << "THE FLAME SURGES INTO A HEALTH ITEM YOU CARRY! YOU CAN FEEL ITS NEW STRENGTH! ITS POWER HAS BEEN DOUBLED!" << endl;
			double_item(hero);
			cout << "you gained 10 score" << endl;
			exp_gain = 10;
			hero->score += exp_gain;
			break;

		case '3': //If red is chosen it halves a random health item
			cout << endl << "YOU CHOSE THE RED POWER!" << endl;
			if(hero->health_items[0].name == "empty"){
				throw 0;
			}
			cout << "THE FLAME SURGES INTO A RANDOM HEALTH ITEM YOU CARRY! YOU CAN FEEL THE STRENGTH OF THAT ITEM GET WEAKER! ITS POWER IS HALF ITS ORIGINAL POWER!" << endl;
			half_item(hero);
			cout << "you gained 10 score" << endl;
			exp_gain = 10;
			hero->score += exp_gain;
			break;

	}
}


//This code will double the strength of a random item
void campfire::double_item(player * hero){
	random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<> dis(0, hero->num_items);
  int x = dis(gen);
	cout << "Your" << hero->health_items[x].name << "'s power has been doubled! " << endl;
	hero->health_items[x].health_bonus *= 2;

}

//This code will half the strength of a random item
void campfire::half_item(player * hero){
	random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<> dis(0, hero->num_items);
  int x = dis(gen);
	cout << "Your " << hero->health_items[x].name << "'s power has been halved! " << endl;
	hero->health_items[x].health_bonus *= 0.5;
}

