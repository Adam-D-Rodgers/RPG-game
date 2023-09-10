//Adam Rodgers, 8/7/2023
//This program is a journey through an rpg game. It ends when the plaer dies of chosses to quite.
//If the player chosses to keep going on the journey it makes a new node of the randomly chosen event. It then runs the event and depending on that stats
//Of the player the events happens. 

//There are three events
//A combat event in whitch the player will battle a random monster and try to beat it. This is the most common event.
//A treasure event in whitch the player get a random treasure, these treasures can either be health or damage items. They are stored in a STL array and STL set. 
//A campfire event, in these events the player will chose from three options (without context). The player will then either be healed, double the strength of an item or half the strength of an item. 
//It is ok for a plyer to get more then one fo teh same item. 

#include <iostream>
#include "node.h"
using namespace std;

char menu();
void status(player *);


 //Main function, it is used to give the user information and is the main loop of the rpg game.
 //The menu function and is callled to ask for user input, and the random number regerator genrates the type of event.
 
int main(){
		
	cout << "HELLO AND WELCOME THE GRAND ADVENTURE!" << endl;
	cout << "IN THIS ADVENTURE YOU ARE A PLAYER THAT WILL BE PROGRESSING THROUGH THEIR JOURNEY!" << endl;
	cout << "YOU WILL BE FIGHTING MONSTERS! FINDING TRESAURE! AND RESTING AT CAMPFIRES!" << endl;
	cout << "THE GOAL OF THIS GAME IS TO GET AS HIGH SCORE AS POSSIBLE!" << endl;
	cout << "WITHOUT FURTHUR ADO! LET THE GAME BEGIN!" << endl;

	player hero;
	DLL<combat> combat_events; //Each DLL stores data of each event type
	DLL<treasure> treasure_events;
	DLL<campfire> campfire_events;
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dis(1, 6);
	int x = 0;

	char input = '1';
	//Main while loop and menu
	while(hero.health > 0 && (input = menu()) != '0'){
		switch(input){
			case '1':
				x = dis(gen);

				switch (x)
				{
					case 1: 
					case 2:
					case 3:
						combat_events.add_node(&hero); //Combat events are the most common
						break;
					case 4:
					case 5:
						treasure_events.add_node(&hero);
						break;
					case 6:
						try {
							campfire_events.add_node(&hero);
						}
						catch(int ex){
							cout << "nothing happened...? maybe it is because you dont have any health items?" << endl;
						}
						break;
					default:
						break;
				}
				break;
			case '2':
				hero.status();
				break;
			case '3':
				combat test;
				test.test_operators(&hero);
		}
	}

	//DLL<combat> test(combat_events); operator overload test
	return 0;
}


//Menu function to make code cleaner
char menu(){

	cout << endl << endl << "Please enter option number you wish to use: " << endl;
	cout << endl;
	cout << "       -1- Kepp Going!" << endl;
	cout << "       -2- Show Player Status" << endl;
	cout << "       -3- Test Operator Overloads" << endl;
	cout << "       -0- Exit program" << endl;

	char temp = 0;
	cin >> temp;
	cin.ignore(100, '\n');
	return temp;
}



